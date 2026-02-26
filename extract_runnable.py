import json
import os

# --- Configuration ---
JSONL_FILE = 'data_0_time1677794311_default.jsonl'
OUTPUT_DIR = '/home/rootsh/Major_Project/exebench_Cprogs' 

def clean_exebench_garbage(code_str):
    if not code_str:
        return ""
    lines = code_str.split('\n')
    cleaned_lines = [line for line in lines if '/tmp/pytmpfile' not in line]
    return '\n'.join(cleaned_lines)

def extract_executable_c_files(jsonl_path, output_dir):
    os.makedirs(output_dir, exist_ok=True)
    extracted_count = 0
    skipped_count = 0

    print(f"Reading from {jsonl_path}...")
    
    with open(jsonl_path, 'r', encoding='utf-8') as file:
        for i, line in enumerate(file):
            try:
                raw_data = json.loads(line)
                data = raw_data.get('text', raw_data)
                
                fname = data.get('fname', f'func_{i}')
                func_def = data.get('func_def', '')
                
                # Extract code components
                deps = data.get('real_deps') or data.get('synth_deps') or ""
                wrapper = data.get('real_exe_wrapper') or data.get('synth_exe_wrapper') or ""
                
                # Extract the JSON test data (I/O pairs)
                io_pairs = data.get('real_io_pairs') or data.get('synth_io_pairs') or []
                
                deps = clean_exebench_garbage(deps)
                wrapper = clean_exebench_garbage(wrapper)
                
                # If there is no wrapper OR no input data, we can't benchmark it
                if not wrapper or not io_pairs:
                    skipped_count += 1
                    continue
                    
                full_c_code = (
                    "/* --- 1. Dependencies & Includes --- */\n"
                    f"{deps}\n\n"
                    "/* --- 2. Function Definition --- */\n"
                    f"{func_def}\n\n"
                    "/* --- 3. Execution Wrapper (main) --- */\n"
                    f"{wrapper}\n"
                )
                
                base_filename = os.path.join(output_dir, f"{i}_{fname}")
                
                # 1. Save the C Code
                with open(f"{base_filename}.c", 'w', encoding='utf-8') as f:
                    f.write(full_c_code)
                    
                # 2. Save the JSON Input Data
                with open(f"{base_filename}.json", 'w', encoding='utf-8') as f:
                    json.dump(io_pairs, f)
                    
                extracted_count += 1
                if extracted_count % 1000 == 0:
                    print(f"Extracted {extracted_count} ready-to-benchmark pairs...")
                    
            except Exception as e:
                print(f"Error processing line {i}: {e}")

    print("\n--- Extraction Complete ---")
    print(f"Successfully extracted: {extracted_count} C files with matching JSON inputs.")
    print(f"Skipped: {skipped_count} files (Missing wrapper or missing I/O data).")

if __name__ == "__main__":
    extract_executable_c_files(JSONL_FILE, OUTPUT_DIR)
