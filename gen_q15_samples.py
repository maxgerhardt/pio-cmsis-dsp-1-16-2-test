import numpy as np
import argparse

# Constants
SAMPLE_COUNT = 2048
SAMPLING_FREQUENCY = 48000  # Typical audio sample rate
SIGNAL_FREQUENCY = 10000  # 10 kHz sine wave

# Generate time values
t = np.arange(SAMPLE_COUNT) / SAMPLING_FREQUENCY

# Generate sine wave samples
sine_wave = np.sin(2 * np.pi * SIGNAL_FREQUENCY * t)

# Convert to q15 format (range -32768 to 32767)
q15_sine_wave = np.round(sine_wave * 32767).astype(np.int16)

# Generate formatted C array output
def format_c_array(data, values_per_line=16):
    lines = [', '.join(map(str, data[i:i+values_per_line])) for i in range(0, len(data), values_per_line)]
    return ",\n    ".join(lines)

# Argument parsing
parser = argparse.ArgumentParser(description="Generate a q15 sine wave C array.")
parser.add_argument("output_file", type=str, help="Output file to save the C array.")
args = parser.parse_args()

c_array = format_c_array(q15_sine_wave)
c_code = f"""#include <arm_math_types.h>\n\nconst q15_t sine_wave_q15[{SAMPLE_COUNT}] = {{\n    {c_array}\n}};"""

# Write to file in UTF-8 format
with open(args.output_file, "w", encoding="utf-8") as f:
    f.write(c_code)

print(f"C array written to {args.output_file}")
