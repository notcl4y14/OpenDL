source = source/DL.c
include = source
output_dir = bin
output_file = DL.o
flags = -Wall

build:
	gcc -c source/DL.c -Isource -o ${output_dir}/DL.o ${flags}
	gcc -c source/DLSL.c -Isource -o ${output_dir}/DLSL.o ${flags}
	gcc -r bin/DL.o bin/DLSL.o -o ${output_dir}/lDL.o