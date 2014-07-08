
#include "IntegralVolume.h"

#include "AddOffsetToVoxelValue.h"
#include "GetMinMaxOfVoxelValue.h"


template <typename VTYPE>
void primitive_RectangleVolume(VTYPE*** vol, int xe, int ye, int ze)
{
	VTYPE yb1,xb1,xyb1;

	for(int k=0; k<ze; k++)
	{
		for(int j=0; j<ye; j++)
		for(int i=0; i<xe; i++)
		{
			if(j)	yb1=vol[k][j-1][i];
			else	yb1=0;
			if(i)	xb1=vol[k][j][i-1];
			else	xb1=0;
			if(j && i)	xyb1=vol[k][j-1][i-1];
			else		xyb1=0;
			vol[k][j][i] += yb1+xb1-xyb1;
		}

		if(k)
		for(int j=0; j<ye; j++)
		for(int i=0; i<xe; i++)
		{
			vol[k][j][i] += vol[k-1][j][i];
		}
	}
}


INTEGRALVOLUME* NewInitializedIntegralVolume(VOL_RAWVOLUMEDATA* source, int channel)
{
	VOL_VALUERANGE range = GetMinMaxOfVoxelValue(source, channel);

	INTEGRALVOLUME* data = new INTEGRALVOLUME;

	data->intensity_offset = -1.0*(double)range.min;
	data->volume = VOL_ExtractSingleChannelRawVolumeData(source, channel);
	
	AddOffsetToVoxelValue(data->volume, 0, (float)data->intensity_offset);

	if(data->volume->voxelUnit[0]==VOL_VALUEUNIT_FLOAT32) {
		VOL_ConvertVoxelUnit(data->volume, 0, VOL_VALUEUNIT_FLOAT64, NULL, NULL, VOL_CONVERTUNIT_TYPE_DIRECT);
	} else if (data->volume->voxelUnit[0]!=VOL_VALUEUNIT_FLOAT64) {
		VOL_ConvertVoxelUnit(data->volume, 0, VOL_VALUEUNIT_UINT32, NULL, NULL, VOL_CONVERTUNIT_TYPE_DIRECT);
	}

	return data;
}


void DeleteIntegralVolume(INTEGRALVOLUME* data)
{
	VOL_DeleteRawVolumeData(data->volume);
	delete data;
}


void SetIntegralVolume(INTEGRALVOLUME* initialized)
{
	VOL_RAWVOLUMEDATA* vol = initialized->volume;
		 
	switch(vol->voxelUnit[0])
	{
	case VOL_VALUEUNIT_UINT32:
		primitive_RectangleVolume((unsigned int***)vol->array4D[0], vol->matrixSize->width, vol->matrixSize->height, vol->matrixSize->depth);
		break;
	case VOL_VALUEUNIT_FLOAT64:
		primitive_RectangleVolume((double***)vol->array4D[0], vol->matrixSize->width, vol->matrixSize->height, vol->matrixSize->depth);
		break;
	}
}


/*
INTEGRALVOLUME* GetIntegralVolume(VOL_RAWVOLUMEDATA* volume, int channel)
{
	VOL_VALUERANGE range = GetMinMaxOfVoxelValue(volume, channel);
	INTEGRALVOLUME* output = NewInitializedIntegralVolume(volume, channel, -1.0f*range.min);

	switch(volume->voxelUnit[channel])
	{
	case VOL_VALUEUNIT_UINT32:
		primitive_RectangleVolume((unsigned int***)output->volume->array4D[channel], volume->matrixSize->width, volume->matrixSize->height, volume->matrixSize->depth);
		break;
	case VOL_VALUEUNIT_FLOAT64:
		primitive_RectangleVolume((double***)output->volume->array4D[channel], volume->matrixSize->width, volume->matrixSize->height, volume->matrixSize->depth);
		break;
	}

	return output;
}
*/


