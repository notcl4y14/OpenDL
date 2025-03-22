#include <stdio.h>
#include <DL.h>

int main ()
{
	dlInit();

	loc_dl vertex_buffer = dlCreateBuffer(32, sizeof(int));
	loc_dl texture_buffer = dlCreateBuffer(32 * 16, sizeof(int));

	size_dl texture_buffer_width = 32;
	size_dl texture_buffer_height = 16;
	size_dl texture_buffer_size = 32 * 16;

	int vertex_buffer_data[32] =
	{
		16, 0,
		0,  15,
		31, 15,
	};

	int texture_buffer_data[32 * 16] = {0};

	dlBufferLoadData(vertex_buffer, &vertex_buffer_data);

	// Since DLSL is yet to be implemented, we're going to manage buffers directly
	for (int i = 0; i < texture_buffer_size; i++)
	{
		loc_dl coord_x = i % texture_buffer_width;
		loc_dl coord_y = i / texture_buffer_width;

		char is_vert_point = 0;
		char is_fill = 0;

		for (int j = 0; j < 6; j += 2)
		{
			is_vert_point = coord_x == vertex_buffer_data[j]
			             && coord_y == vertex_buffer_data[j + 1];
			if (is_vert_point)
				break;
		}

		is_fill = is_vert_point;

		if (is_fill)
			texture_buffer_data[i] = 1;
	}

	dlBufferLoadData(texture_buffer, &texture_buffer_data);

	// Render the Texture Buffer, directly
	for (int i = 0; i < texture_buffer_size; i++)
	{
		if (i != 0 && i % texture_buffer_width == 0)
		{
			printf("\n");
		}

		if (texture_buffer_data[i] == 0)
		{
			printf(".");
		}
		else
		{
			printf("#");
		}
	}

	dlTerminate();
	return 0;
}