#include <stdio.h>
#include <stdlib.h>
#include <DL.h>
#include <DLSL.h>

int main ()
{
	printf("Creating DLSL VM...\n\n");
	struct DLSLVM* vm = malloc(sizeof(struct DLSLVM));
	*vm = DLSL_createVM(16);

	printf("Creating Attrs... (2 double elements)\n\n");
	struct DLAttrs* attrs = malloc(sizeof(struct DLAttrs));
	*attrs = DL_createAttrs(2);

	printf("Creating VM code...\n\n");
	double vm_code[32] =
	{
		DLSL_OPCODE_ALD, 0,
		DLSL_OPCODE_PUSH, 10,
		DLSL_OPCODE_IMUL,
		DLSL_OPCODE_AST, 0,

		DLSL_OPCODE_ALD, 1,
		DLSL_OPCODE_PUSH, 20,
		DLSL_OPCODE_IMUL,
		DLSL_OPCODE_AST, 1,

		DLSL_OPCODE_QUIT,
	};

	printf("Creating Attrs Array Data... [21, 72]\n\n");
	double attrs_buffer[2] = { 21, 72 };

	printf("Loading Code into VM...\n\n");
	DLSL_vmLoadCode(vm, &vm_code, sizeof(vm_code) / sizeof(double));

	printf("Loading Array Data into Attrs...\n\n");
	DL_attrsLoadArray(attrs, &attrs_buffer, sizeof(double));

	printf("Binding Attrs to VM...\n\n");
	vm->attrs = attrs;

	printf("Starting VM...\n\n");
	DLSL_vmRun(vm);

	printf("ATTRS: [%f, %f]\n\n",
	       *(double*)(attrs->data[0]),
	       *(double*)(attrs->data[1]));

	printf("Done!\n");
	return 0;
}