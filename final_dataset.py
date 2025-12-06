import os
import glob
import torch
import ast
import pprint
from torch_geometric.data import Data # This import is necessary for torch.load

# --- Configuration ---
BENCHMARK_FILE = 'best_flags_for_program.txt'
GRAPH_DATA_DIR = 'graph_data'
FINAL_DATASET_FILE = 'final_dataset.pt'

# Our 5 classes
LABEL_MAP = {
    "-O0": 0, # Added -O0 just in case
    "-O1": 1,
    "-O2": 2,
    "-O3": 3,
    "-Ofast": 4  # Adjusted to 6 classes to include -O0 and -Os
}
# --- End Configuration ---

def load_benchmark_results(filepath: str) -> dict:
    """
    Safely reads the 'best_flags_for_program.txt' file 
    and parses the dictionary.
    """
    print(f"Loading benchmark results from: {filepath}")
    try:
        with open(filepath, 'r') as f:
            content = f.read()
            
        # Find the '=' and take the text after it
        dict_str = content[content.find('=') + 1:]
        
        # Use ast.literal_eval to safely parse the dictionary string
        benchmark_map = ast.literal_eval(dict_str)
        
        print(f"  -> Found {len(benchmark_map)} benchmark results.")
        return benchmark_map
        
    except FileNotFoundError:
        print(f"  [Error] Benchmark file not found: {filepath}")
        return None
    except Exception as e:
        print(f"  [Error] Failed to parse benchmark file: {e}")
        return None

def main():
    # 1. Load the "Ground Truth" (the answers)
    best_flags_map = load_benchmark_results(BENCHMARK_FILE)
    if best_flags_map is None:
        print("Exiting.")
        return

    # 2. Find all the "Inputs" (the graphs)
    graph_files = glob.glob(os.path.join(GRAPH_DATA_DIR, '*.pt'))
    if not graph_files:
        print(f"Error: No graph .pt files found in '{GRAPH_DATA_DIR}'.")
        return
        
    print(f"Found {len(graph_files)} graph files in '{GRAPH_DATA_DIR}'.")
    
    final_dataset_list = []
    labeled_count = 0
    skipped_count = 0

    # 3. Loop, Match, and Label
    print("Matching graphs to labels...")
    for graph_file_path in graph_files:
        # e.g., "program_100_...c.pt" -> "program_100_...c"
        base_name = os.path.basename(graph_file_path)
        program_name = base_name.replace('.pt', '')

        # Check if we have a benchmark result for this graph
        if program_name in best_flags_map:
            try:
                # Get the flag string (e.g., "-O3")
                flag_str = best_flags_map[program_name]
                
                # Check if this flag is one we are training for
                if flag_str in LABEL_MAP:
                    # Load the unlabeled Data object
                    # We MUST use weights_only=False to load Data objects
                    data = torch.load(graph_file_path, weights_only=False)
                    
                    # Map the string flag to an integer
                    label_int = LABEL_MAP[flag_str]
                    
                    # Create the tensor label and add it
                    data.y = torch.tensor([label_int], dtype=torch.long)
                    
                    # Add the labeled graph to our final list
                    final_dataset_list.append(data)
                    labeled_count += 1
                else:
                    print(f"  -> Skipping {program_name}: Flag '{flag_str}' not in LABEL_MAP.")
                    skipped_count += 1
                    
            except Exception as e:
                print(f"  [Error] Failed to load {graph_file_path}: {e}")
                skipped_count += 1
        else:
            # This will happen for files like 'program_32...pt' from your example
            print(f"  -> Skipping {base_name}: No matching label found in {BENCHMARK_FILE}.")
            skipped_count += 1

    # 4. Save the Final Dataset
    if final_dataset_list:
        print(f"\nSaving {labeled_count} labeled graphs to {FINAL_DATASET_FILE}...")
        
        # Save the *entire list* of labeled Data objects to one file
        torch.save(final_dataset_list, FINAL_DATASET_FILE)
        
        print("\n--- ✅ Success! ---")
        print(f"  Final dataset created: {FINAL_DATASET_FILE}")
        print(f"  Total graphs labeled: {labeled_count}")
        print(f"  Total graphs skipped: {skipped_count}")
    else:
        print("\nNo labeled graphs were created. Please check your file paths and names.")

if __name__ == "__main__":
    main()
