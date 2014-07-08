

#include "VOL.h"


int CheckRasterPositionedVoxelValuePresense(VOL_RAWVOLUMEDATA* volume, int channel, int position)
{
	int output = 0;
	unsigned char* data_0 = (unsigned char*)volume->data[channel];
	char* data_1 = (char*)volume->data[channel];
	unsigned short* data_2 = (unsigned short*)volume->data[channel];
	short* data_3 = (short*)volume->data[channel];
	unsigned int* data_4 = (unsigned int*)volume->data[channel];
	int* data_5 = (int*)volume->data[channel];
	float* data_6 = (float*)volume->data[channel];
	double* data_7 = (double*)volume->data[channel];

	switch(volume->voxelUnit[channel]) {
	case VOL_VALUEUNIT_UINT8:
		if(data_0[position]!=0)	output=1;
		break;
	case VOL_VALUEUNIT_SINT8:
		if(data_1[position]!=0)	output=1;
		break;
	case VOL_VALUEUNIT_UINT16:
		if(data_2[position]!=0)	output=1;
		break;
	case VOL_VALUEUNIT_SINT16:
		if(data_3[position]!=0)	output=1;
		break;
	case VOL_VALUEUNIT_UINT32:
		if(data_4[position]!=0)	output=1;
		break;
	case VOL_VALUEUNIT_SINT32:
		if(data_5[position]!=0)	output=1;
		break;
	case VOL_VALUEUNIT_FLOAT32:
		if(data_6[position]!=0.0f)	output=1;
		break;
	case VOL_VALUEUNIT_FLOAT64:
		if(data_7[position]!=0.0)	output=1;
		break;
	}

	return output;
}

