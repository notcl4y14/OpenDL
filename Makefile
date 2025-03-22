source = source/DL.c
include = source
output_dir = bin
output_file = DL.o
flags = -Wall --pedantic
# flags = -w

build:
	gcc -c source/DL.c -Isource -o ${output_dir}/DL_DL.o ${flags}
	gcc -c source/DLSL.c -Isource -o ${output_dir}/DL_DLSL.o ${flags}
	gcc -r ${output_dir}/DL_DL.o ${output_dir}/DL_DLSL.o -o ${output_dir}/DL.o ${flags}