#include <stdio.h>
#include <stdlib.h>
#include <DL.h>
#include <DLSL.h>

int main ()
{
	printf("Creating DLSL VM...\n\n");
	struct DLSLVM* vm = malloc(sizeof(struct DLSLVM));
	*vm = DLSL_createVM(16);

	printf("Creating Buffer... (4 double elements)\n\n");
	struct DLBuffer* buffer = malloc(sizeof(struct DLBuffer));
	*buffer = DL_createBuffer(4, sizeof(double));

	printf("Creating VM code...\n\n");
	double vm_code[32] =
	{
		DLSL_OPCODE_BLD, 0,
		DLSL_OPCODE_PUSH, 2,
		DLSL_OPCODE_IMUL,
		DLSL_OPCODE_BST, 0,

		DLSL_OPCODE_BLD, 1,
		DLSL_OPCODE_PUSH, 4,
		DLSL_OPCODE_IMUL,
		DLSL_OPCODE_BST, 1,

		DLSL_OPCODE_BLD, 2,
		DLSL_OPCODE_PUSH, 8,
		DLSL_OPCODE_IMUL,
		DLSL_OPCODE_BST, 2,

		DLSL_OPCODE_BLD, 3,
		DLSL_OPCODE_PUSH, 16,
		DLSL_OPCODE_IMUL,
		DLSL_OPCODE_BST, 3,

		DLSL_OPCODE_QUIT,
	};

	printf("Creating Buffer Data... [4, 4, 4, 4]\n\n");
	double buffer_data[4] = { 4, 4, 4, 4 };

	printf("Loading Code into VM...\n\n");
	DLSL_vmLoadCode(vm, &vm_code, sizeof(vm_code) / sizeof(double));

	printf("Loading Buffer Data into Buffer...\n\n");
	DL_bufferLoadData(buffer, &buffer_data);

	printf("Binding Buffer to VM...\n\n");
	vm->buffer = buffer;

	printf("Starting VM...\n\n");
	DLSL_vmRun(vm);

	printf("BUFFER: [%f, %f, %f, %f]\n\n",
	       ((double*)(buffer->data))[0],
	       ((double*)(buffer->data))[1],
	       ((double*)(buffer->data))[2],
	       ((double*)(buffer->data))[3]);

	printf("Done!\n");
	return 0;
}