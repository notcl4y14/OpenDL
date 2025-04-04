#include <DL/DL.h>

#include <stdio.h>
#include <stdlib.h>

void shader_code (DLAttrList* attrlist)
{
	uint32_t *attr_coord = DL_AttrListGetAttr(attrlist, 0)->value;
	uint8_t  *attr_color = DL_AttrListGetAttr(attrlist, 1)->value;
	uint32_t *attr_value = DL_AttrListGetAttr(attrlist, 2)->value;

	uint32_t value = *attr_value;

	attr_color[0] = value;
}

int main () {
	DLShader* shader = DL_CreateShader(NULL, NULL);

		DLAttrList* attrlist = malloc(sizeof(DLAttrList));
		DL_InitAttrList(attrlist, 3);

			DL_AttrListBindAttr(attrlist, 0, 1, DL_TYPE_INT, sizeof(uint32_t) * 2, sizeof(uint32_t));
			DL_AttrListBindAttr(attrlist, 1, 1, DL_TYPE_BYTE, sizeof(uint8_t) * 4, sizeof(uint8_t));
			DL_AttrListBindAttr(attrlist, 2, 0, DL_TYPE_INT, sizeof(uint32_t), sizeof(uint32_t));

			DL_AttrListBindAttrType(attrlist, 0, DL_SHADER_ATTR_COORD);
			DL_AttrListBindAttrType(attrlist, 1, DL_SHADER_ATTR_COLOR);

		DLCode* code = malloc(sizeof(DLCode));
		DL_InitCode(code, shader_code);

		DL_ShaderBindAttrList(shader, attrlist);
		DL_ShaderBindCode(shader, code);

	printf("Shader AttrList Capacity: %d\n", shader->attrlist.data_capacity);
	printf("Shader AttrList Shader Coord Attribute: %d\n", shader->attrlist.shader_attr_coord);
	printf("Shader AttrList Shader Color Attribute: %d\n", shader->attrlist.shader_attr_color);
	printf("Shader AttrList Path Texture Attribute: %d\n", shader->attrlist.path_attr_texture);
	printf("Shader AttrList Attribute[0]:\n");
	printf("\tPointer: %d\n\tType: %d\n\tSize: %d\n\tStride: %d\n",
		shader->attrlist.data_v[0].value_ptr,
		shader->attrlist.data_v[0].value_type,
		shader->attrlist.data_v[0].value_size,
		shader->attrlist.data_v[0].value_stride);
	printf("Shader AttrList Attribute[1]:\n");
	printf("\tPointer: %d\n\tType: %d\n\tSize: %d\n\tStride: %d\n",
		shader->attrlist.data_v[1].value_ptr,
		shader->attrlist.data_v[1].value_type,
		shader->attrlist.data_v[1].value_size,
		shader->attrlist.data_v[1].value_stride);
	printf("Shader AttrList Attribute[2]:\n");
	printf("\tPointer: %d\n\tType: %d\n\tSize: %d\n\tStride: %d\n",
		shader->attrlist.data_v[2].value_ptr,
		shader->attrlist.data_v[2].value_type,
		shader->attrlist.data_v[2].value_size,
		shader->attrlist.data_v[2].value_stride);

	DLTexture* texture = DL_CreateTexture(4, 1, DL_TYPE_BYTE, sizeof(uint8_t) * 4, sizeof(uint8_t));

	uint32_t value = 32;
	DL_AttrSetValue( DL_AttrListGetAttr( DL_ShaderGetAttrList(shader), 2 ), &value);
	DL_TextureUseShader(texture, shader);

	uint8_t* texture_data = texture->data;
	printf("Texture[0-3]: %d, %d, %d, %d\n",
		texture_data[0], texture_data[1], texture_data[2], texture_data[3]);
	printf("Texture[4-7]: %d, %d, %d, %d\n",
		texture_data[4], texture_data[5], texture_data[6], texture_data[7]);
	printf("Texture[8-11]: %d, %d, %d, %d\n",
		texture_data[8], texture_data[9], texture_data[10], texture_data[11]);
	printf("Texture[12-15]: %d, %d, %d, %d\n",
		texture_data[12], texture_data[13], texture_data[14], texture_data[15]);

	DL_DeleteShader(shader);
	DL_DeleteAttrList(attrlist);
	DL_DeleteCode(code);
	DL_DeleteTexture(texture);

	free(attrlist);
	free(code);

	return 0;
}