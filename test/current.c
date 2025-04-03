#include <DL/DL.h>

#include <stdio.h>

int main () {
	DLAttr attr;
	DLAttrList attrlist;

	// DLAttr
	{
		DL_InitAttr(&attr, DL_TYPE_INT, sizeof(uint32_t) * 2, sizeof(uint32_t));

		// Setting DLAttr value
		{
			uint32_t value[2] = {10, 20};
			DL_AttrSetValue(&attr, value);
		}

		uint32_t attr_value[2];
		DL_AttrGetValue(&attr, &attr_value);

		printf("Attribute Value: %d, %d\n", attr_value[0], attr_value[1]);
	}

	// DLAttrList
	{
		uint32_t a_coord, a_color;
		uint32_t coord_v[2] = {50, 25};
		uint8_t color_v[4] = {255, 0, 128, 255};
		DL_InitAttrList(&attrlist, 2);
		DL_AttrListBindAttrLocation(&attrlist, 0, "coord");
		DL_AttrListBindAttrLocation(&attrlist, 1, "color");
		a_coord = DL_AttrListGetAttrLocation(&attrlist, "coord");
		a_color = DL_AttrListGetAttrLocation(&attrlist, "color");
		DL_InitAttr(
			DL_AttrListGetAttr(&attrlist, a_coord),
			DL_TYPE_INT, sizeof(uint32_t) * 2, sizeof(uint32_t)
		);
		DL_InitAttr(
			DL_AttrListGetAttr(&attrlist, a_color),
			DL_TYPE_BYTE, sizeof(uint8_t) * 4, sizeof(uint8_t)
		);
		DL_AttrSetValue(
			DL_AttrListGetAttr(&attrlist, a_coord),
			&coord_v
		);
		DL_AttrSetValue(
			DL_AttrListGetAttr(&attrlist, a_color),
			&color_v
		);

		uint32_t coord_v_get[2];
		uint8_t color_v_get[4];
		DL_AttrGetValue(
			DL_AttrListGetAttr(&attrlist, a_coord),
			&coord_v_get
		);
		DL_AttrGetValue(
			DL_AttrListGetAttr(&attrlist, a_color),
			&color_v_get
		);

		printf("AttrList Capacity: %d\n", attrlist.data_capacity);
		printf("AttrList Attribute 0 (%s): %d, %d\n",
			DL_AttrListGetAttrID(&attrlist, 0),
			coord_v_get[0], coord_v_get[1]);
		printf("AttrList Attribute 1 (%s): %d, %d, %d, %d\n",
			DL_AttrListGetAttrID(&attrlist, 1),
			color_v_get[0], color_v_get[1], color_v_get[2], color_v_get[3]);
	}

	DL_DeleteAttr(&attr);
	DL_DeleteAttrList(&attrlist);
	return 0;
}