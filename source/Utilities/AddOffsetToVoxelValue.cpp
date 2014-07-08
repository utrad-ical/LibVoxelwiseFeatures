

#include "VOL.h"


template <typename VTYPE>
void primitive_AddOffset(VTYPE* data, VTYPE offset, int num)
{
	for(int i=0; i<num; i++) {
		data[i] += offset;
	}
	return;
}


void AddOffsetToVoxelValue(VOL_RAWVOLUMEDATA* volume, int channel, float offset)
{
	int num = volume->matrixSize->depth*volume->matrixSize->height*volume->matrixSize->width;

	switch(volume->voxelUnit[channel]) {
	case VOL_VALUEUNIT_UINT8:
		primitive_AddOffset((unsigned char*)volume->data[channel], (unsigned char)offset, num);
		break;
	case VOL_VALUEUNIT_SINT8:
		primitive_AddOffset((char*)volume->data[channel], (char)offset, num);
		break;
	case VOL_VALUEUNIT_UINT16:
		primitive_AddOffset((unsigned short*)volume->data[channel], (unsigned short)offset, num);
		break;
	case VOL_VALUEUNIT_SINT16:
		primitive_AddOffset((short*)volume->data[channel], (short)offset, num);
		break;
	case VOL_VALUEUNIT_UINT32:
		primitive_AddOffset((unsigned int*)volume->data[channel], (unsigned int)offset, num);
		break;
	case VOL_VALUEUNIT_SINT32:
		primitive_AddOffset((int*)volume->data[channel], (int)offset, num);
		break;
	case VOL_VALUEUNIT_FLOAT32:
		primitive_AddOffset((float*)volume->data[channel], (float)offset, num);
		break;
	case VOL_VALUEUNIT_FLOAT64:
		primitive_AddOffset((double*)volume->data[channel], (double)offset, num);
		break;
	}

	return;
}