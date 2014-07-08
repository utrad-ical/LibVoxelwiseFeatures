
#ifndef CURVATURE_FEATURES_H


#include "VOL.h"
#include "../Utilities/CalculatingVoxels.h"


#define NUM_CURVATURE_FEATURES	4
// [0]: Gaussian-Curvature
// [1]: Mean-Curvature
// [2]: Shape-Index
// [3]: Curvedness


float* CalculateCurvatureFeatures(VOL_RAWVOLUMEDATA* input, int ch, VOL_INTVECTOR3D* coord);


VOL_RAWVOLUMEDATA* GetVolumeOfCurvatureFeatures(
	VOL_RAWVOLUMEDATA* volume, int vChannel, VOL_RAWVOLUMEDATA* mask, int mChannel);


VOL_RAWVOLUMEDATA* GetVolumeOfCurvatureFeatures_MT(
	VOL_RAWVOLUMEDATA* volume, int vChannel, VOL_RAWVOLUMEDATA* mask, int mChannel, int numThreads);


float** CalculateCurvatureFeaturesAtMultiPositions_MT(
	VOL_RAWVOLUMEDATA* volume, int channel, CALCULATINGVOXELS* subset, int nthreads);



#define CURVATURE_FEATURES_H
#endif

