# Output Directory
output_dir = bin

# Default Warning Flags
flags_warnings = -Wall -Wextra --pedantic

# No Warning Flags
# flags_warnings = -w

build:
	gcc -c source/DL.c -Isource -o ${output_dir}/DL.o ${flags_warnings}

build-all:
	gcc -c source/DL.c -Isource -o ${output_dir}/lDL.o ${flags_warnings}
	gcc -c source/DLSL.c -Isource -o ${output_dir}/lDLSL.o ${flags_warnings}
	gcc -r ${output_dir}/lDL.o ${output_dir}/lDLSL.o -o ${output_dir}/DL.o

build-dlsl:
	gcc -c source/DLSL.c -Isource -o ${output_dir}/DL.o ${flags_warnings}