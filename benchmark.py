import os
import glob
import subprocess
import time
import pprint

# --- Configuration ---

# 1. Directory where your .c files are located
SOURCE_DIR = '/home/rootsh/Major_Project/Cprogs' 

# 2. The optimization flags to test
OPT_FLAGS = ['-O0', '-O1', '-O2', '-O3', '-Ofast']

# 3. Directory to store the compiled binaries (will be created)
BINARY_DIR = 'benchmark_binaries'

# 4. How many times to run each binary to get a good average
#    (Higher is more accurate but slower)
NUM_RUNS = 10 

# 5. The final output file
OUTPUT_FILE = 'best_flags_for_program.txt'

# --- End Configuration ---


def run_and_time_binary(binary_path: str, num_runs: int) -> float:
    """
    Runs a compiled binary 'num_runs' times and returns the average runtime.
    Returns float('inf') if an error occurs.
    """
    runtimes = []
    
    for _ in range(num_runs):
        try:
            # Start the timer
            start_time = time.perf_counter()
            
            # Run the binary. 
            # We add a timeout (e.g., 20s) to prevent hanging programs.
            # We hide stdout/stderr from the program to keep the console clean.
            subprocess.run(
                [binary_path], 
                check=True, 
                timeout=20,
                stdout=subprocess.DEVNULL,
                stderr=subprocess.DEVNULL
            )
            
            # Stop the timer
            end_time = time.perf_counter()
            
            runtimes.append(end_time - start_time)
            
        except subprocess.TimeoutExpired:
            print(f"      [Error] Program timed out.")
            return float('inf') # Give it an "infinitely bad" score
        except subprocess.CalledProcessError:
            print(f"      [Error] Program crashed or returned a non-zero exit code.")
            return float('inf')
        except Exception as e:
            print(f"      [Error] An unexpected error occurred: {e}")
            return float('inf')

    # Return the average time of all successful runs
    if runtimes:
        return sum(runtimes) / len(runtimes)
    else:
        return float('inf')

def main():
    """
    Main function to compile, benchmark, and save results.
    """
    # Create the directory for compiled binaries if it doesn't exist
    os.makedirs(BINARY_DIR, exist_ok=True)
    
    # Find all .c files in the source directory
    source_files = glob.glob(os.path.join(SOURCE_DIR, '*.c'))
    
    if not source_files:
        print(f"Error: No .c files found in '{SOURCE_DIR}' directory.")
        return

    print(f"Found {len(source_files)} C programs to benchmark...")
    
    # This dictionary will hold our final results
    best_flags_map = {}

    # Loop over each C program
    for source_file in source_files:
        base_name = os.path.basename(source_file)
        print(f"\nBenchmarking: {base_name}")
        
        # Store results for this specific file (flag -> avg_time)
        results_for_this_file = {}
        
        # Loop over each optimization flag
        for flag in OPT_FLAGS:
            print(f"  Testing {flag}...")
            
            # Create a unique name for the binary, e.g., "program1_O3"
            binary_name = f"{base_name.replace('.c', '')}_{flag}"
            binary_path = os.path.join(BINARY_DIR, binary_name)
            
            # --- 1. Compile ---
            try:
                # Compile the program with the current flag
                subprocess.run(
                    ['gcc', flag, source_file, '-o', binary_path],
                    check=True,
                    capture_output=True, # Capture stdout/stderr
                    text=True
                )
            except subprocess.CalledProcessError as e:
                print(f"      [Error] Compilation failed for {flag}.")
                print(f"      [stderr]: {e.stderr}")
                continue # Skip to the next flag
            
            # --- 2. Run & Time ---
            avg_time = run_and_time_binary(binary_path, NUM_RUNS)
            
            if avg_time != float('inf'):
                print(f"      -> Avg. Runtime: {avg_time:.6f}s")
                results_for_this_file[flag] = avg_time

        # --- 3. Find the Best Flag for this File ---
        if results_for_this_file:
            # Find the key (flag) with the minimum value (time)
            best_flag = min(results_for_this_file, key=results_for_this_file.get)
            print(f"  -> Best flag for {base_name}: {best_flag}")
            
            # Add to our final results map
            best_flags_map[base_name] = best_flag
        else:
            print(f"  -> No successful runs for {base_name}, skipping.")

    # --- 4. Save Results to File ---
    print(f"\nBenchmark complete. Saving results to {OUTPUT_FILE}...")
    
    with open(OUTPUT_FILE, 'w') as f:
        # Use pprint.pformat to get the nice dictionary formatting
        formatted_results = pprint.pformat(best_flags_map, indent=4)
        f.write(f"best_flags_for_program = {formatted_results}\n")

    print("Done.")

if __name__ == "__main__":
    main()
