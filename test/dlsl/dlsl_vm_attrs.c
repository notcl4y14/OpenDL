#include <stdio.h>
#include <stdlib.h>
#include <DL.h>
#include <DLSL.h>

int main ()
{
	printf("Creating DLSL VM...\n\n");
	struct DLSLVM* vm = malloc(sizeof(struct DLSLVM));
	*vm = DLSL_createVM(16);

	printf("Creating Attrs... (2 int elements)\n\n");
	struct DLAttrs* attrs = malloc(sizeof(struct DLAttrs));
	*attrs = DL_createAttrs(2);

	DL_bindAttribType(attrs, 0, DL_INT);
	DL_bindAttribType(attrs, 1, DL_INT);

	printf("Creating VM code...\n\n");
	double vm_code[32] =
	{
		DLSL_ALD, 0,
		DLSL_PUSH, 10,
		DLSL_IMUL,
		DLSL_AST, 0,

		DLSL_ALD, 1,
		DLSL_PUSH, 20,
		DLSL_IMUL,
		DLSL_AST, 1,

		DLSL_QUIT,
	};

	printf("Creating Attrs Array Data... [21, 72]\n\n");
	int attrs_buffer[2] = { 21, 72 };

	printf("Loading Code into VM...\n\n");
	DLSL_vmLoadCode(vm, &vm_code, sizeof(vm_code) / sizeof(double));

	printf("Loading Array Data into Attrs...\n\n");
	DL_attrsLoadArray(attrs, &attrs_buffer, sizeof(int));

	printf("Binding Attrs to VM...\n\n");
	vm->attrs = attrs;

	printf("Starting VM...\n\n");
	DLSL_vmRun(vm);

	printf("ATTRS: [%d, %d]\n\n",
	       *(int*)(attrs->v_values[0]),
	       *(int*)(attrs->v_values[1]));

	printf("Done!\n");
	return 0;
}