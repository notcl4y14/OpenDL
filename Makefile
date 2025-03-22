# Output Directory
output_dir = bin

# Default Warning Flags
flags_warnings = -Wall -Wextra --pedantic

# No Warning Flags
# flags_warnings = -w

build:
	gcc -c source/DL.c -Isource -o ${output_dir}/DL.o ${flags_warnings}