
#ifndef HAAR_FEATURES_BY_INTEGRAL__H


#include "../HaarFeatures/HaarFeatures.h"
#include "../Utilities/CalculatingVoxels.h"


VOL_RAWVOLUMEDATA* GetVolumeOfSingleHaarFeatureByIntegral(
	VOL_RAWVOLUMEDATA* input, int ich, VOL_RAWVOLUMEDATA* mask, int mch, VOL_KERNEL* roi, int index);

VOL_RAWVOLUMEDATA* GetVolumeOfMultiHaarFeaturesByIntegral(
	VOL_RAWVOLUMEDATA* input, int ich, VOL_RAWVOLUMEDATA* mask, int mch, VOL_KERNEL* roi);


VOL_RAWVOLUMEDATA* GetVolumeOfSingleHaarFeatureByIntegral_MT(
	VOL_RAWVOLUMEDATA* input, int ich, VOL_RAWVOLUMEDATA* mask, int mch, VOL_KERNEL* roi, int index, int numThreads);

VOL_RAWVOLUMEDATA* GetVolumeOfMultiHaarFeaturesByIntegral_MT(
	VOL_RAWVOLUMEDATA* input, int ich, VOL_RAWVOLUMEDATA* mask, int mch, VOL_KERNEL* roi, int numThreads);


VOL_RAWVOLUMEDATA* GetVolumeOfMultiHaarFeaturesFromIntegral_MT(
	void* integral, VOL_RAWVOLUMEDATA* mask, int mch, VOL_KERNEL* roi, int numThreads);

float** CalculateMultiHaarFeaturesAtMultiPositionsByIntegral_MT(
	void* intvolume, CALCULATINGVOXELS* voxels, VOL_KERNEL* roi, int numThreads);


#define HAAR_FEATURES_BY_INTEGRAL__H
#endif