import os
import glob
import subprocess
import time
import pprint

# --- Configuration ---
SOURCE_DIR = '/home/rootsh/Major_Project/exebench_Cprogs' 
OPT_FLAGS = ['-O0', '-O1', '-O2', '-O3', '-Ofast']
BINARY_DIR = 'benchmark_binaries'
NUM_RUNS = 10 
OUTPUT_FILE = 'best_flags_for_program.txt'
# --- End Configuration ---

def run_and_time_binary(binary_path: str, json_input_path: str, num_runs: int) -> float:
    runtimes = []
    
    # ExeBench wrappers require an output file path to write results to. 
    dummy_output = binary_path + "_dummy_out.json"

    for _ in range(num_runs):
        try:
            start_time = time.perf_counter()
            
            subprocess.run(
                [binary_path, json_input_path, dummy_output], 
                check=True, 
                timeout=20,
                capture_output=True,
                text=True
            )
            
            end_time = time.perf_counter()
            runtimes.append(end_time - start_time)
            
        except subprocess.TimeoutExpired:
            print(f"      [Error] Program timed out.")
            break 
        except subprocess.CalledProcessError as e:
            print(f"      [Error] Execution crashed (Exit Code {e.returncode}).")
            if e.stderr:
                print(f"      [Crash Log]: {e.stderr.strip()[:150]}...")
            break 
        except Exception as e:
            print(f"      [Error] Unexpected runtime error: {e}")
            break

    if os.path.exists(dummy_output):
        try:
            os.remove(dummy_output)
        except OSError:
            pass

    if len(runtimes) == num_runs:
        return sum(runtimes) / len(runtimes)
    return float('inf')

def main():
    os.makedirs(BINARY_DIR, exist_ok=True)
    source_files = glob.glob(os.path.join(SOURCE_DIR, '*.c'))
    
    if not source_files:
        print("Error: No .c files found.")
        return

    clib_cpp_files = glob.glob(os.path.join(SOURCE_DIR, 'clib', '*.cpp'))
    
    print(f"Found {len(source_files)} C programs to benchmark...")
    best_flags_map = {}

    for source_file in source_files:
        base_name = os.path.basename(source_file)
        json_file = source_file.replace('.c', '.json')
        
        if not os.path.exists(json_file):
            print(f"\nSkipping {base_name}: Missing matching .json input file.")
            continue
            
        print(f"\nBenchmarking: {base_name}")
        results_for_this_file = {}
        
        for flag in OPT_FLAGS:
            print(f"  Testing {flag}...")
            binary_name = f"{base_name.replace('.c', '')}_{flag}"
            binary_path = os.path.join(BINARY_DIR, binary_name)
            
            # --- 1. Compile ---
            compile_cmd = ['gcc', '-x', 'c++', flag, source_file] + clib_cpp_files + ['-o', binary_path, f'-I{SOURCE_DIR}', '-lstdc++']
            
            try:
                subprocess.run(compile_cmd, check=True, capture_output=True, text=True)
            except subprocess.CalledProcessError as e:
                print(f"      [Error] Compilation failed for {flag}.")
                print(f"      [GCC Says]: {e.stderr.strip()[:300]}...") 
                
                # --- TIME SAVER: IF BASELINE FAILS TO COMPILE, SKIP REST ---
                if flag == '-O0':
                    print("      -> Baseline (-O0) failed to compile. Skipping remaining flags.")
                    break
                continue 
            
            # --- 2. Run & Time ---
            avg_time = run_and_time_binary(binary_path, json_file, NUM_RUNS)
            
            if avg_time != float('inf'):
                print(f"      -> Avg. Runtime: {avg_time:.6f}s")
                results_for_this_file[flag] = avg_time
            else:
                # --- TIME SAVER: IF BASELINE CRASHES, SKIP REST ---
                if flag == '-O0':
                    print("      -> Baseline (-O0) crashed during execution. Skipping remaining flags.")
                    break

        # --- 3. Save Results ---
        if results_for_this_file:
            best_flag = min(results_for_this_file, key=results_for_this_file.get)
            print(f"  -> Best flag for {base_name}: {best_flag}")
            best_flags_map[base_name] = best_flag
        else:
            print(f"  -> No successful runs for {base_name}.")

    print(f"\nBenchmark complete. Saving results to {OUTPUT_FILE}...")
    with open(OUTPUT_FILE, 'w') as f:
        formatted_results = pprint.pformat(best_flags_map, indent=4)
        f.write(f"best_flags_for_program = {formatted_results}\n")

if __name__ == "__main__":
    main()
