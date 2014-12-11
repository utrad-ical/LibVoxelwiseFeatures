
#pragma warning(disable: 4996)

#include <cmath>
#include "VOL.h"


float* CalculateSift3D_SinglePosition(
	VOL_RAWVOLUMEDATA* volume, int ch, int* p,
	int roi_size, int num_roi_division, int num_angle, float** base_angles);


VOL_RAWVOLUMEDATA* VolumeOfSift3D(
	VOL_RAWVOLUMEDATA* volume, int ch_v, VOL_RAWVOLUMEDATA* mask, int ch_m, 
	int roi_size, int num_roi_division, int num_angle)
{
	VOL_INTSIZE3D* size = VOL_GetIntSize3DFromIntSize4D(volume->matrixSize);
	int num_feats = num_roi_division*num_roi_division*num_roi_division*num_angle;

	VOL_RAWVOLUMEDATA* output = VOL_NewSingleChannelRawVolumeData(size, VOL_VALUEUNIT_FLOAT32, VOL_VALUETYPE_SINGLE);
	for(int i=1; i<num_feats; i++) {
		VOL_AddNewChannelInRawVolumeData(output, VOL_VALUEUNIT_FLOAT32, VOL_VALUETYPE_SINGLE);
	}

	return NULL;
}