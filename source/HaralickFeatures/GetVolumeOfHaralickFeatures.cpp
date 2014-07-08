

#include "VOL.h"
#include "HaralickFeatures.h"
#include "HaralickFeatures.private.h"
#include "../Utilities/ConvertMaskToCalculatingVoxels.h"


void CalculateHaralickFeatures_SubsetOfVoxels(
	VOL_RAWVOLUMEDATA* output, VOLUMEHARALICKCALCULATION* volumeH, CALCULATINGVOXELS* subset, VOL_KERNEL* roi, VOL_KERNEL* references)
{
	float**** featvol = (float****)output->array4D;

	VOL_INTVECTOR3D coord;
	for(int i=0; i<subset->num; i++) {

		coord.x = subset->xc[i];	coord.y = subset->yc[i];	coord.z = subset->zc[i];

		float* temp = CalculateHaralickFeatures(volumeH, &coord, roi, references);

		for(int j=0; j<NUM_HARALICK_FEATURES; j++)		featvol[j][coord.z][coord.y][coord.x] = temp[j];

		delete [] temp;
	}

	return;
}


VOL_RAWVOLUMEDATA* GetVolumeOfHaralickFeatures(
	VOL_RAWVOLUMEDATA* volume, int vChannel, VOL_RAWVOLUMEDATA* mask, int mChannel, 
	VOL_VALUERANGE* range, int numGradation, VOL_KERNEL* roi, VOL_KERNEL* references)
{
	VOL_INTSIZE3D* size = VOL_GetIntSize3DFromIntSize4D(volume->matrixSize);

	VOL_RAWVOLUMEDATA* output = VOL_NewSingleChannelRawVolumeData(size, VOL_VALUEUNIT_FLOAT32, VOL_VALUETYPE_SINGLE);
	
	for(int i=1; i<NUM_HARALICK_FEATURES; i++) {
		VOL_AddNewChannelInRawVolumeData(output, VOL_VALUEUNIT_FLOAT32, VOL_VALUETYPE_SINGLE);
	}

	VOLUMEHARALICKCALCULATION* volumeH;
	volumeH = NewVolumeHaralickCalculation(volume, vChannel, range, numGradation, roi, references);

//	CALCULATINGVOXELS* subset = NewCalculatingVoxels(mask, mChannel);
	CALCULATINGVOXELS* subset = ConvertMaskToCalculatingVoxels(mask, mChannel);
//	ConvertPositions1DTo3DCalculatingVoxels(subset);

	CalculateHaralickFeatures_SubsetOfVoxels(output, volumeH, subset, roi, references);

	VOL_DeleteIntSize3D(size);
	DeleteVolumeHaralickCalculation(volumeH);
	DeleteCalculatingVoxels(subset);

	return output;
}



/*
// 同時生起行列由来のテクスチャ特徴量計測
float* CalculateHaralickFeatures(
	VOLUMEHARALICKCALCULATION* volumeH, VOL_INTVECTOR3D* coord, VOL_KERNEL* roi, VOL_KERNEL* references)
{
	VOL_INTVECTOR3D ctemp;
	ctemp.x += volumeH->margin;
	ctemp.y += volumeH->margin;
	ctemp.z += volumeH->margin;

	float* coMatrix1D = CalculateCoOccurrenceMatrix(
		volumeH->volume, 0, volumeH->numGradation, &ctemp, roi, references);

	float* features = CalculateHaralickFeaturesFromCoOccurenceMatrix(coMatrix1D, volumeH->numGradation);

	delete [] coMatrix1D;

	return features;
}
*/