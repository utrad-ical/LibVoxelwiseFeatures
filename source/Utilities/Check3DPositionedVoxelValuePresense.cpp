

#include "VOL.h"


int Check3DPositionedVoxelValuePresense(VOL_RAWVOLUMEDATA* volume, int channel, VOL_INTVECTOR3D* position)
{
	int output = 0;
	unsigned char*** vol_0 = (unsigned char***)volume->array4D[channel];
	char*** vol_1 = (char***)volume->array4D[channel];
	unsigned short*** vol_2 = (unsigned short***)volume->array4D[channel];
	short*** vol_3 = (short***)volume->array4D[channel];
	unsigned int*** vol_4 = (unsigned int***)volume->array4D[channel];
	int*** vol_5 = (int***)volume->array4D[channel];
	float*** vol_6 = (float***)volume->array4D[channel];
	double*** vol_7 = (double***)volume->array4D[channel];

	switch(volume->voxelUnit[channel]) {
	case VOL_VALUEUNIT_UINT8:
		if(vol_0[position->z][position->y][position->x]!=0)	output=1;
		break;
	case VOL_VALUEUNIT_SINT8:
		if(vol_1[position->z][position->y][position->x]!=0)	output=1;
		break;
	case VOL_VALUEUNIT_UINT16:
		if(vol_2[position->z][position->y][position->x]!=0)	output=1;
		break;
	case VOL_VALUEUNIT_SINT16:
		if(vol_3[position->z][position->y][position->x]!=0)	output=1;
		break;
	case VOL_VALUEUNIT_UINT32:
		if(vol_4[position->z][position->y][position->x]!=0)	output=1;
		break;
	case VOL_VALUEUNIT_SINT32:
		if(vol_5[position->z][position->y][position->x]!=0)	output=1;
		break;
	case VOL_VALUEUNIT_FLOAT32:
		if(vol_6[position->z][position->y][position->x]!=0.0f)	output=1;
		break;
	case VOL_VALUEUNIT_FLOAT64:
		if(vol_7[position->z][position->y][position->x]!=0.0)	output=1;
		break;
	}

	return output;
}





