import torch
from torch_geometric.data import Data
import subprocess
import os
import glob # Used for finding files

def get_graph_from_bitcode(bitcode_file, pass_so_file):
    """
    Runs the LLVM pass on a bitcode file and parses its output
    to create a PyTorch Geometric Data object.
    
    Returns a 'Data' object or 'None' if an error occurred.
    """
    
    # --- 1. Run the LLVM Pass ---
    # We capture both stdout and stderr for better error checking
    process = subprocess.run(
        [
            'opt',
            '-load-pass-plugin', pass_so_file,
            '-passes=feature-extractor',
            bitcode_file,
            '-disable-output'
        ],
        capture_output=True, text=True
    )
    
    # --- Check for errors from the 'opt' command ---
    if process.returncode != 0:
        print(f"  [Error] 'opt' pass failed for {bitcode_file}.")
        print(f"  [stderr]: {process.stderr}")
        return None

    output = process.stdout
    if not output:
        print(f"  [Warning] 'opt' pass produced no output for {bitcode_file}.")
        return None
        
    node_features = {}
    edge_list_pairs = []

    # --- 2. Parse the Text Output ---
    try:
        for line in output.splitlines():
            if line.startswith('NODE:'):
                parts = line.strip('NODE:').split(',')
                node_id = int(parts[0])
                features = [float(f) for f in parts[1:]]
                node_features[node_id] = features
                
            elif line.startswith('EDGE:'):
                parts = line.strip('EDGE:').split(',')
                source_id = int(parts[0])
                dest_id = int(parts[1])
                edge_list_pairs.append((source_id, dest_id))
    except Exception as e:
        print(f"  [Error] Failed to parse pass output for {bitcode_file}: {e}")
        return None

    # --- 3. Convert to Tensors ---
    
    # Check if we actually found any nodes
    if not node_features:
        print(f"  [Warning] No 'NODE:' features found in output for {bitcode_file}.")
        return None
        
    # Sort features by node_id to ensure correct order
    node_features_list = [node_features[i] for i in sorted(node_features.keys())]
    
    x_tensor = torch.tensor(node_features_list, dtype=torch.float)
    
    if edge_list_pairs:
        edge_index_tensor = torch.tensor(edge_list_pairs, dtype=torch.long).t().contiguous()
    else:
        edge_index_tensor = torch.empty((2, 0), dtype=torch.long)
        
    # --- 4. Create the final Data object ---
    data = Data(x=x_tensor, edge_index=edge_index_tensor)
    
    return data

# --- Main execution ---
if __name__ == "__main__":
    
    # --- 1. Define Paths ---
    PASS_FILE = './build/libFeatureExtractor.so'
    
    # This is the directory where your .c and .cpp files are
    SOURCE_DIR = '/home/rootsh/Major_Project/Cprogs' 
    
    # We will create these directories to store our results
    BITCODE_DIR = 'bitcode_files'
    GRAPH_DIR = 'graph_data'
    
    os.makedirs(BITCODE_DIR, exist_ok=True)
    os.makedirs(GRAPH_DIR, exist_ok=True)

    # Check if the pass file exists
    if not os.path.exists(PASS_FILE):
        print(f"Error: Pass file not found at {PASS_FILE}")
        print("Please compile the LLVM pass first.")
        exit(1)

    # --- 2. Find all C/C++ files ---
    # This finds all files ending in .c, .cpp, .cxx, etc.
    source_files = glob.glob(os.path.join(SOURCE_DIR, '*.c*'))
    
    if not source_files:
        print(f"No C/C++ files found in '{SOURCE_DIR}'.")
        print("Please run the synthetic data generator or add your C files.")
        exit(0)

    print(f"Found {len(source_files)} source files. Starting processing...")
    
    graphs_created = 0

    # --- 3. Loop over each source file ---
    for source_file in source_files:
        print(f"\nProcessing: {source_file}")
        
        # Get the base name (e.g., "program1.c")
        base_name = os.path.basename(source_file)
        
        # Create output paths
        bc_file = os.path.join(BITCODE_DIR, base_name + '.bc')
        graph_file = os.path.join(GRAPH_DIR, base_name + '.pt')

        # --- 4. Compile C/C++ to Bitcode ---
        compile_process = subprocess.run(
            [
                'clang++', # Use clang++ to handle both C and C++
                '-O0', '-Xclang', '-disable-O0-optnone', # The crucial flags
                '-c', '-emit-llvm',
                source_file,
                '-o', bc_file
            ],
            capture_output=True, text=True
        )

        if compile_process.returncode != 0:
            print(f"  [Error] Clang compilation failed for {source_file}.")
            print(f"  [stderr]: {compile_process.stderr}")
            continue # Skip to the next file
            
        print(f"  -> Compiled to {bc_file}")

        # --- 5. Run the LLVM Pass and get Graph ---
        graph_data = get_graph_from_bitcode(bc_file, PASS_FILE)
        
        if graph_data:
            # --- 6. Save the Unlabeled Graph Object ---
            graph_data.program_name = base_name # Store the name for later
            torch.save(graph_data, graph_file)
            print(f"  -> Saved graph to {graph_file}")
            graphs_created += 1

    print(f"\n--- Processing Complete ---")
    print(f"Successfully generated {graphs_created} graph files in '{GRAPH_DIR}'.")
