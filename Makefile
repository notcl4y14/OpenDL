out_dir = bin
source_dir = source
include_dir = include

setup:
	@echo Creating required directories...
	@echo ================
	mkdir ${out_dir}

build:
	@echo Building DL...
	@echo ================
	gcc -c ${source_dir}/DL.c -o ${out_dir}/DL.o -I${include_dir}