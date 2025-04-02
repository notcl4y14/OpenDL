#include <DL/DL.h>

#include <stdio.h>
// #include <windows.h>

void shader_func (uint32_t coord[2], void* color) {
	char* _color = (char*)(color);
	_color[0] = coord[0] * 5;
	_color[1] = (coord[0] + coord[1]) /*/ 2*/ * 5;
	_color[2] = coord[1] * 5;
	_color[3] = 255;
}

int main () {
	// Create Texture
	DLTexture* texture = DL_CreateTexture(100, 100, DL_TYPE_BYTE, sizeof(char) * 4);

	// Print Texture information
	printf("Texture:\n");
	printf("Dimensions: %dx%d\n", texture->width, texture->height);
	printf("Data Size: %d\n", texture->data_capacity * texture->data_unit_size);
	printf("Data Capacity: %d\n", texture->data_capacity);
	printf("Unit Size: %d\n", texture->data_unit_size);
	printf("Unit Type: %d\n", texture->data_unit_type);
	printf("Total Size: %fKB\n", ((float)texture->data_capacity * texture->data_unit_size + sizeof(*texture)) / 1024);

	// Create and initialize Shader
	DLShader* shader = DL_CreateShader();
	shader->func = shader_func;

	// Use Shader on Texture
	DL_TextureUseShader(texture, shader);

	// Draw on Terminal with characters
	for (int i = 0; i < texture->data_capacity; i++) {
		if (i != 0 && i % texture->width == 0)
		{
			printf("\n");
		}

		// unsigned char* color = DL_TextureGetPixelPI(texture, i);
		// printf("(%d,%d,%d,%d) ", color[0], color[1], color[2], color[3]);

		// int* color = DL_TextureGetPixelPI(texture, i);
		// printf("%x ", *color);

		uint8_t* color = DL_TextureGetPixelPI(texture, i);
		uint32_t rgb_sum = color[0] + color[1] + color[2];
		float rgb_mid = (float)rgb_sum / 3;

		if (rgb_mid == 0)
		{
			printf(" ");
		}
		else if (rgb_mid < 255 / 5)
		{
			printf(".");
		}
		else if (rgb_mid < 255 / 5 * 2)
		{
			printf(":");
		}
		else if (rgb_mid < 255 / 5 * 3)
		{
			printf("!");
		}
		else if (rgb_mid < 255 / 5 * 4)
		{
			printf("#");
		}
		else if (rgb_mid <= 255)
		{
			printf("@");
		}
	}

	// Draws the Texture onto the Command Prompt window
	// {
	// 	HWND hwnd = GetConsoleWindow();
	// 	HDC hdc = GetDC(hwnd);

	// 	for (int x = 0; x < texture->width; x++)
	// 	{
	// 		for (int y = 0; y < texture->height; y++)
	// 		{
	// 			uint8_t* t_color = DL_TextureGetPixelP(texture, x, y);
	// 			COLORREF w_color = RGB(t_color[0], t_color[1], t_color[2]);
	// 			SetPixel(hdc, x, y + 100, w_color);
	// 		}
	// 	}

	// 	ReleaseDC(hwnd, hdc);
	// 	DeleteDC(hdc);
	// }

	// Freeing Texture and Shader
	DL_DeleteTexture(texture);
	DL_DeleteShader(shader);
	return 0;
}