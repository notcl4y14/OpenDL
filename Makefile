# Output Directory
output_dir = bin

# Default Warning Flags
flags_warnings = -Wall -Wextra --pedantic

# No Warning Flags
# flags_warnings = -w

all: build-o

setup:
	@echo Creating required directories...
	@mkdir bin

build-o:
	@echo Building .o files...
	@echo ================
	gcc -c source/dlcore.c -Iinclude -o ${output_dir}/dlcore.o ${flags_warnings}
	gcc -c source/dlsystem.c -Iinclude -o ${output_dir}/dlsystem.o ${flags_warnings}
	gcc -c source/dlsl.c -Iinclude -o ${output_dir}/dlsl.o ${flags_warnings}
	gcc -c source/dlutil.c -Iinclude -o ${output_dir}/dlutil.o ${flags_warnings}
	gcc -r ${output_dir}/dlcore.o ${output_dir}/dlsystem.o ${output_dir}/dlsl.o ${output_dir}/dlutil.o -Iinclude -o ${output_dir}/DL.o

build-dll:
	@echo Building .dll file...
	@echo ================
	gcc -shared ${output_dir}/DL.o -o ${output_dir}/DL.dll

build-so:
	@echo Building .so file...
	@echo ================
	gcc -shared ${output_dir}/DL.o -o ${output_dir}/DL.so