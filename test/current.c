#include <DL/DL.h>

#include <stdio.h>

int main () {
	DLTexture* texture;

	// Before DL System

	DL_Hint(DL_TEXTURE_DEF_UNIT_TYPE, DL_TYPE_BYTE);
	DL_Hint(DL_TEXTURE_DEF_UNIT_SIZE, sizeof(uint8_t));
	DL_Hint(DL_TEXTURE_DEF_UNIT_STRIDE, sizeof(uint8_t));

	texture = DL_CreateTextureD(100, 100);

	printf("\n");
	printf("Texture Address: 0x%p\n", texture);
	printf("Texture Unit Type: %d\n", texture->data_unit_type);
	printf("Texture Unit Size: %d\n", texture->data_unit_size);
	printf("Texture Unit Stride: %d\n", texture->data_unit_stride);

	DL_DeleteTexture(texture);

	// After DL System Initialized

	DL_Hint(DL_OBJECT_ARRAYS_ENABLED, DL_TRUE);
	DL_Hint(DL_OBJECT_ARRAYS_CAPACITY, 8);

	DL_Init();

	texture = DL_CreateTextureD(100, 100);

	printf("Texture Address: 0x%p\n", texture);
	printf("Texture Unit Type: %d\n", texture->data_unit_type);
	printf("Texture Unit Size: %d\n", texture->data_unit_size);
	printf("Texture Unit Stride: %d\n", texture->data_unit_stride);

	DL_Terminate();

	// After DL System Freed

	texture = DL_CreateTextureD(100, 100);

	printf("Texture Address: 0x%p\n", texture);
	printf("Texture Unit Type: %d\n", texture->data_unit_type);
	printf("Texture Unit Size: %d\n", texture->data_unit_size);
	printf("Texture Unit Stride: %d\n", texture->data_unit_stride);

	DL_DeleteTexture(texture);
	return 0;
}