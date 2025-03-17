source = source/DL.c
include = source
output_dir = bin
output_file = DL.o
flags = -Wall --pedantic
# flags = -w

build:
	gcc -c source/DL.c -Isource -o ${output_dir}/DL.o ${flags}