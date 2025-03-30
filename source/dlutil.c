#include <string.h>

#include <DL/dlutil.h>

// If you're going to scroll down, remember:
// do NOT be horrified by what you are going to see.

// Nevermind, I used the (probably) better option by casting each variable,
// instead of checking all of them in nested switch statements.

// Which sounds less performant but I don't thinks casting is that heavy.

void DLutil_copydt (DLvoid_p dest_v, DLtype dest_t, DLvoid_p source_v, DLtype source_t)
{
	DLbyte v_byte;
	DLshort v_short;
	DLint v_int;
	DLfloat v_float;
	DLdouble v_double;

	switch (source_t)
	{
		case DL_BYTE:
			memcpy(&v_byte, source_v, sizeof(DLbyte));
			v_byte = v_byte;
			v_short = v_byte;
			v_int = v_byte;
			v_float = v_byte;
			v_double = v_byte;
			break;

		case DL_SHORT:
			memcpy(&v_short, source_v, sizeof(DLshort));
			v_byte = v_short;
			v_short = v_short;
			v_int = v_short;
			v_float = v_short;
			v_double = v_short;
			break;

		case DL_INT:
			memcpy(&v_int, source_v, sizeof(DLint));
			v_byte = v_int;
			v_short = v_int;
			v_int = v_int;
			v_float = v_int;
			v_double = v_int;
			break;

		case DL_FLOAT:
			memcpy(&v_float, source_v, sizeof(DLfloat));
			v_byte = v_float;
			v_short = v_float;
			v_int = v_float;
			v_float = v_float;
			v_double = v_float;
			break;

		case DL_DOUBLE:
			memcpy(&v_double, source_v, sizeof(DLdouble));
			v_byte = v_double;
			v_short = v_double;
			v_int = v_double;
			v_float = v_double;
			v_double = v_double;
			break;
	}

	switch (dest_t)
	{
		case DL_BYTE:
			memcpy(dest_v, &v_byte, sizeof(DLbyte));
			break;

		case DL_SHORT:
			memcpy(dest_v, &v_short, sizeof(DLshort));
			break;

		case DL_INT:
			memcpy(dest_v, &v_int, sizeof(DLint));
			break;

		case DL_FLOAT:
			memcpy(dest_v, &v_float, sizeof(DLfloat));
			break;

		case DL_DOUBLE:
			memcpy(dest_v, &v_double, sizeof(DLdouble));
			break;
	}
}

void DLutil_copydts (DLvoid_p dest_v, DLtype dest_t, DLuint dest_sz, DLuint dest_st,
                     DLvoid_p source_v, DLtype source_t, DLuint source_sz, DLuint source_st)
{
	DLuint loop_loc = -1;
	DLuint loop_max = source_sz / sizeof(source_st);

	while (++loop_loc < loop_max)
	{
		DLvoid_p dest_ptr = (DLchar_p)(dest_v) + (loop_loc * dest_st);
		DLvoid_p source_ptr = (DLchar_p)(source_v) + (loop_loc * source_st);
		DLutil_copydt(dest_ptr, dest_t, source_ptr, source_t);
	}
}