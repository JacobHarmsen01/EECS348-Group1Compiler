import csv
import subprocess
import re
import math
import os

BINARY_PATH = "../exprparser" 
CSV_INPUT = "tests.csv"
CSV_OUTPUT = "test_results.csv"

def run_test(expression):
    try:
        process = subprocess.run(
            [BINARY_PATH],
            input=f"{expression}\nexit\n",
            text=True,
            capture_output=True,
            timeout=2 
        )
        return process.stdout + process.stderr
    except FileNotFoundError:
        print(f"Error: Could not find the binary at '{BINARY_PATH}'.")
        exit(1)
    except subprocess.TimeoutExpired:
        return "TIMEOUT"
    except Exception as e:
        return f"CRASH: {str(e)}"

def parse_output(output):
    if output == "TIMEOUT" or output.startswith("CRASH:"):
        return output

    # Strip ANSI escape codes (color formatting)
    ansi_escape = re.compile(r'\x1b\[[0-9;]*m')
    clean_output = ansi_escape.sub('', output)

    if re.search(r'\berror\b', clean_output, re.IGNORECASE):
        return "ERR"
    
    match = re.search(r'result\s+.*?=\s*([-\d.]+)', clean_output)
    if match:
        return match.group(1).strip()
    
    return "UNKNOWN_OUTPUT"

def check_pass_fail(expected, actual):
    expected = str(expected).strip()
    actual = str(actual).strip()

    if expected == "ERR" and actual == "ERR":
        return "Pass"
    if expected == "ERR" or actual == "ERR":
        return "Fail"

    try:
        exp_val = float(expected)
        act_val = float(actual)
        # Using math.isclose to account for floating point inaccuracies
        if math.isclose(exp_val, act_val, rel_tol=1e-5, abs_tol=1e-8):
            return "Pass"
        else:
            return "Fail"
    except ValueError:
        # Fallback to strict string comparison if float conversion fails
        return "Pass" if expected == actual else "Fail"

def main():
    if not os.path.exists(CSV_INPUT):
        print(f"Error: Cannot find input file '{CSV_INPUT}'")
        return

    tested_rows = []
    pass_count = 0
    fail_count = 0
    total_tests = 0

    with open(CSV_INPUT, mode='r', newline='', encoding='utf-8') as infile:
        reader = csv.reader(infile)
        headers = next(reader)
        tested_rows.append(headers)

        for row in reader:
            # Skip empty rows or rows that don't have enough columns
            if not row or len(row) < 4 or not row[0].startswith("TC"):
                tested_rows.append(row)
                continue

            test_id = row[0]
            expression = row[2].replace('\xa0', ' ').strip('\t\r\n"')
            expected = row[3].replace('\xa0', ' ').strip('\t\r\n"')

            raw_output = run_test(expression)
            actual = parse_output(raw_output)
            
            status = check_pass_fail(expected, actual)

            new_row = [
                test_id,
                row[1] if len(row) > 1 else "",
                expression,
                expected,
                actual,
                status
            ]
                
            tested_rows.append(new_row)

            total_tests += 1
            if status == "Pass":
                pass_count += 1
                print(f"[\033[92mPASS\033[0m] {test_id}: {expression} -> {actual}")
            else:
                fail_count += 1
                print(f"[\033[91mFAIL\033[0m] {test_id}: {expression} | Expected: {expected}, Actual: {actual}")
                if actual == "UNKNOWN_OUTPUT":
                    print(f"RAW OUTPUT: {repr(raw_output)}")


    with open(CSV_OUTPUT, mode='w', newline='', encoding='utf-8') as outfile:
        writer = csv.writer(outfile)
        writer.writerows(tested_rows)

    print("-" * 40)
    print("Results:")
    print(f"Total Tests: {total_tests}")
    print(f"Passed:      {pass_count}")
    print(f"Failed:      {fail_count}")
    print(f"\nResults saved to '{CSV_OUTPUT}'")

if __name__ == "__main__":
    main()