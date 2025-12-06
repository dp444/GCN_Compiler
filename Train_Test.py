# --- 0. Basic Imports & Environment Detection ---
import os
import sys
import random
import subprocess

import torch
import matplotlib.pyplot as plt
import networkx as nx


try:
    from google.colab import files  # type: ignore
    IN_COLAB = True
    print("Running in: Google Colab")
except ImportError:
    IN_COLAB = False
    files = None
    print("Running in: Local / VS Code / Jupyter")

print(f"PyTorch version: {torch.__version__}")

# --- 1. Install PyTorch Geometric ---
def ensure_torch_geometric():
    try:
        import torch_geometric  # noqa: F401
        print(" torch-geometric already installed.")
    except ImportError:
        print("Installing torch-geometric (minimal, no extra CUDA extensions)...")
        subprocess.check_call([
            sys.executable, "-m", "pip", "install", "torch-geometric"
        ])
        print(" torch-geometric installation complete.")

ensure_torch_geometric()

# Now safe to import PyG
import torch.nn.functional as F
from torch.nn import Linear
from torch_geometric.data import Data, Batch
from torch_geometric.nn import GCNConv, global_mean_pool
from torch_geometric.loader import DataLoader
from torch_geometric.utils import to_networkx
from matplotlib.patches import Patch

print("-" * 50)
print("PyG, NetworkX, and Matplotlib ready.")
print("-" * 50)

# --- 2. Configuration (Matches create_labeled_dataset.py) ---

NUM_NODE_FEATURES = 3  

# This must match the LABEL_MAP from'create_labeled_dataset.py' file
LABEL_MAP = {
    "-O0": 0,
    "-O1": 1,
    "-O2": 2,
    "-O3": 3,
    "-Ofast": 4,
}
INV_LABEL_MAP = {v: k for k, v in LABEL_MAP.items()}  # For plotting
NUM_CLASSES = len(LABEL_MAP)  # Should be 5 for the map above

print("Configuration loaded:")
print(f"  - Node Features: {NUM_NODE_FEATURES}")
print(f"  - Num Classes: {NUM_CLASSES} ({list(LABEL_MAP.keys())})")
print("-" * 50)

# --- 3. Load  REAL DATASET (Colab vs Local) ---

if IN_COLAB:
    print("Please upload your 'final_dataset.pt' file.")
    uploaded = files.upload()  # opens file picker in Colab UI
    OUTPUT_FILE = list(uploaded.keys())[0]
else:
   
    OUTPUT_FILE = "final_dataset.pt"
    if not os.path.exists(OUTPUT_FILE):
        raise FileNotFoundError(
            f"Could not find '{OUTPUT_FILE}'. "
            "Place your final_dataset.pt in the current working directory."
        )

if OUTPUT_FILE != "final_dataset.pt":
    print(f"Warning: Uploaded file is named '{OUTPUT_FILE}', not 'final_dataset.pt'. Proceeding anyway.")

print(f"✅ Success! Using dataset file: '{OUTPUT_FILE}'")
print("-" * 50)

# --- 4. Setup Training (90/10 split) ---

# Set seeds for reproducibility
random.seed(42)
torch.manual_seed(42)

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
print(f"Using device: {device}")

# Load the dataset uploaded / placed locally
all_data = torch.load(OUTPUT_FILE, weights_only=False)

# Shuffle and split (90/10)
random.shuffle(all_data)
split_point = int(len(all_data) * 0.9)
train_dataset = all_data[:split_point]
test_dataset = all_data[split_point:]

# Handle the case where the test set is empty (if dataset < 10 programs)
if not test_dataset:
    print("Warning: Dataset is too small. Using 1 program for testing.")
    if len(all_data) > 1:
        train_dataset = all_data[:-1]
        test_dataset = all_data[-1:]
    else:  # Cannot split
        train_dataset = all_data
        test_dataset = all_data

print(f"Total graphs:    {len(all_data)}")
print(f"Training graphs: {len(train_dataset)}")
print(f"Testing graphs:  {len(test_dataset)}")

# Create DataLoaders
train_loader = DataLoader(train_dataset, batch_size=32, shuffle=True)
test_loader = DataLoader(test_dataset, batch_size=32, shuffle=False)

# --- 5. GNN Model (MODIFIED to return intermediate fingerprint) ---

class GCN_Optimizer(torch.nn.Module):
    def __init__(self, hidden_channels):
        super().__init__()
        torch.manual_seed(12345)
        self.conv1 = GCNConv(NUM_NODE_FEATURES, hidden_channels)
        self.conv2 = GCNConv(hidden_channels, hidden_channels)
        self.conv3 = GCNConv(hidden_channels, hidden_channels)
        self.lin = Linear(hidden_channels, NUM_CLASSES)

    def forward(self, x, edge_index, batch, return_fingerprint=False):
        # 1. Node Embedding
        x = self.conv1(x, edge_index).relu()
        x = self.conv2(x, edge_index).relu()
        x = self.conv3(x, edge_index).relu()

        # 2. Readout (Graph "Fingerprint")
        fingerprint = global_mean_pool(x, batch)

        # 3. Classifier
        x = F.dropout(fingerprint, p=0.5, training=self.training)
        out = self.lin(x)

        if return_fingerprint:
            return out, fingerprint
        return out


model = GCN_Optimizer(hidden_channels=64).to(device)
optimizer = torch.optim.Adam(model.parameters(), lr=0.001)
criterion = torch.nn.CrossEntropyLoss()

# --- 6. Train & Test Functions ---

def train(loader):
    model.train()
    total_loss = 0.0
    for data in loader:
        data = data.to(device)
        optimizer.zero_grad()
        out = model(data.x, data.edge_index, data.batch)
        loss = criterion(out, data.y)
        loss.backward()
        optimizer.step()
        total_loss += loss.item() * data.num_graphs
    return total_loss / len(loader.dataset)


def test(loader):
    model.eval()
    correct = 0
    with torch.no_grad():
        for data in loader:
            data = data.to(device)
            out = model(data.x, data.edge_index, data.batch)
            pred = out.argmax(dim=1)
            correct += int((pred == data.y).sum())
    return correct / len(loader.dataset)


# --- 7. Run the Training Loop ---

history = {"train_acc": [], "test_acc": [], "loss": []}
num_epochs = 200

print("\nStarting training (on REAL data)...")
for epoch in range(1, num_epochs + 1):
    loss = train(train_loader)
    train_acc = test(train_loader)
    test_acc = test(test_loader)

    history["loss"].append(loss)
    history["train_acc"].append(train_acc)
    history["test_acc"].append(test_acc)

    if epoch % 10 == 0 or epoch == 1:
        print(
            f"Epoch: {epoch:03d}, "
            f"Loss: {loss:.4f}, "
            f"Train Acc: {train_acc:.4f}, "
            f"Test Acc: {test_acc:.4f}"
        )

print("Training complete.")
print("-" * 50)

# --- 8. VISUALIZATION ---

if not test_dataset:
    print("Cannot visualize: No graphs in the test set.")
else:
    print("Generating visualization for one test graph...")

    # Put model in evaluation mode
    model.eval()

    # Select the very first graph from the test set
    data_to_visualize = test_dataset[4]

    # Try to get program_name, default to "Unknown"
    program_name = getattr(data_to_visualize, "program_name", "Unknown Program")

    # Prepare data for the model
    data_batch = Batch.from_data_list([data_to_visualize]).to(device)

    # Get the model's prediction and the true answer
    with torch.no_grad():
        scores_tensor, _ = model(
            data_batch.x,
            data_batch.edge_index,
            data_batch.batch,
            return_fingerprint=True,
        )
        scores = scores_tensor.cpu().numpy()[0]
        prediction_index = scores.argmax()
        prediction_label = INV_LABEL_MAP.get(prediction_index, "Unknown")

    # Get the true answer
    ground_truth_index = data_to_visualize.y.item()
    ground_truth_label = INV_LABEL_MAP.get(ground_truth_index, "Unknown")

    print(f"Program: {program_name}")
    print(f"  - Ground Truth:     {ground_truth_label} (Class {ground_truth_index})")
    print(f"  - Model Prediction: {prediction_label} (Class {prediction_index})")

    # Create the plots
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(20, 7))

    # --- PLOT 1: The Input Graph (CFG) ---
    ax1.set_title(
        f'Input: CFG for "{program_name}"\n({data_to_visualize.num_nodes} nodes)'
    )
    g = to_networkx(data_to_visualize, to_undirected=False)

    # Get labels from the first feature (e.g., Arithmetic)
    if data_to_visualize.x is not None and data_to_visualize.x.shape[1] > 0:
        labels = {
            i: f"F0:{f[0].item():.0f}" for i, f in enumerate(data_to_visualize.x)
        }
    else:
        # Just use node index
        labels = {i: str(i) for i in range(data_to_visualize.num_nodes)}

    nx.draw_kamada_kawai(
        g,
        ax=ax1,
        with_labels=True,
        node_color="#cde7f6",
        labels=labels,
        node_size=1000,
        font_size=9,
    )

    # --- PLOT 2: The Output Layer (Prediction) ---
    ax2.set_title("Output: Final Layer Scores")
    class_names = list(LABEL_MAP.keys())
    bar_colors = ["#cccccc"] * len(class_names)
    bar_colors[prediction_index] = "#f57a7a"
    bar_colors[ground_truth_index] = "#77dd77"
    if ground_truth_index == prediction_index:
        bar_colors[ground_truth_index] = "#62c662"

    ax2.bar(class_names, scores, color=bar_colors)
    ax2.set_ylabel("Raw Score (Logits)")
    ax2.set_xlabel("Optimization Flag")

    # Add legend
    legend_elements = [
        Patch(facecolor="#77dd77", label=f"Ground Truth ({ground_truth_label})"),
        Patch(facecolor="#f57a7a", label=f"Model Prediction ({prediction_label})"),
    ]
    ax2.legend(handles=legend_elements, loc="upper right")

    plt.tight_layout()
    plt.show()
