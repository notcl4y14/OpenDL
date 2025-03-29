# Output Directory
output_dir = bin

# Default Warning Flags
flags_warnings = -Wall -Wextra --pedantic

# No Warning Flags
# flags_warnings = -w

build:
	gcc -c source/DL_system.c -Isource -o ${output_dir}/_DL_system.o ${flags_warnings}
	gcc -c source/DL_public.c -Isource -o ${output_dir}/_DL_public.o ${flags_warnings}
	gcc -c source/DL_core.c -Isource -o ${output_dir}/_DL_core.o ${flags_warnings}
	gcc -r bin/_DL_system.o bin/_DL_public.o bin/_DL_core.o -Isource -o ${output_dir}/DL.o