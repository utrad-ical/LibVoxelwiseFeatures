

#ifndef HARALICK_FEATURES_PRIVATE__H

#include "VOL.h"
#include "../Utilities/CalculatingVoxels.h"
#include "../Utilities/DividedCalculatingVoxels.h"
#include "../Utilities/SetIntRadInVolKernel.h"


float* CalculateCoOccurrenceMatrix(
	VOL_RAWVOLUMEDATA* volume, int channel, int gradation, VOL_INTVECTOR3D* coord, 
	VOL_KERNEL* roi, VOL_KERNEL* dispracements);

float* CalculateHaralickFeaturesFromCoOccurenceMatrix(
	float* coMatrix1D, int gradation);

void CalculateHaralickFeatures_SubsetOfVoxels(
	VOL_RAWVOLUMEDATA* output, VOLUMEHARALICKCALCULATION* volumeH, CALCULATINGVOXELS* area, VOL_KERNEL* roi, VOL_KERNEL* references);


#define HARALICK_FEATURES_PRIVATE__H
#endif