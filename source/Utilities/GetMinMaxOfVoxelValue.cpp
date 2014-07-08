

#include "VOL.h"


template <typename VTYPE>
VOL_VALUERANGE primitive_GetMinMax(VTYPE* data, int num)
{
	VOL_VALUERANGE range;
	range.max = range.min =(float)data[0];

	for(int i=1; i<num; i++) {
		if(range.min>(float)data[i])	range.min = (float)data[i];
		if(range.max<(float)data[i])	range.max = (float)data[i];
	}

	return range;
}


VOL_VALUERANGE GetMinMaxOfVoxelValue(VOL_RAWVOLUMEDATA* volume, int channel)
{
	VOL_VALUERANGE range;

	int num = volume->matrixSize->depth*volume->matrixSize->height*volume->matrixSize->width;

	switch(volume->voxelUnit[channel]) {
	case VOL_VALUEUNIT_UINT8:
		range = primitive_GetMinMax((unsigned char*)volume->data[channel], num);
		break;
	case VOL_VALUEUNIT_SINT8:
		range = primitive_GetMinMax((char*)volume->data[channel], num);
		break;
	case VOL_VALUEUNIT_UINT16:
		range = primitive_GetMinMax((unsigned short*)volume->data[channel], num);
		break;
	case VOL_VALUEUNIT_SINT16:
		range = primitive_GetMinMax((short*)volume->data[channel], num);
		break;
	case VOL_VALUEUNIT_UINT32:
		range = primitive_GetMinMax((unsigned int*)volume->data[channel], num);
		break;
	case VOL_VALUEUNIT_SINT32:
		range = primitive_GetMinMax((int*)volume->data[channel], num);
		break;
	case VOL_VALUEUNIT_FLOAT32:
		range = primitive_GetMinMax((float*)volume->data[channel], num);
		break;
	case VOL_VALUEUNIT_FLOAT64:
		range = primitive_GetMinMax((double*)volume->data[channel], num);
		break;
	}

	return range;
}
