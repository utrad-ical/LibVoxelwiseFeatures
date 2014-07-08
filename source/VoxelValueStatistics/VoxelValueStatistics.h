
#ifndef VOXEL_VALUE_STATISTICS__H


#include "VOL.h"
//#include <cstdio>
#include "../Utilities/CalculatingVoxels.h"


#define NUM_VOXEL_VALUE_STATISTICS	4


typedef struct _VOXEL_VALUE_STATISTICS_
{
	float mean, var, skew, kurt;
}
VOXELVALUESTATISTICS;

VOXELVALUESTATISTICS CalculateVoxelValueStatistics(
	VOL_RAWVOLUMEDATA* volume, int channel, VOL_INTVECTOR3D* coord, VOL_KERNEL* roi);


VOL_RAWVOLUMEDATA* GetVolumeOfVoxelValueStatistics(
	VOL_RAWVOLUMEDATA* volume, int vChannel, VOL_RAWVOLUMEDATA* mask, int mChannel, VOL_KERNEL* roi);

VOL_RAWVOLUMEDATA* GetVolumeOfVoxelValueStatistics_MT(
	VOL_RAWVOLUMEDATA* volume, int vChannel, VOL_RAWVOLUMEDATA* mask, int mChannel, VOL_KERNEL* roi, int numThreads);


float** CalculateVoxelValueStatisticsAtMultiPositions_MT(
	VOL_RAWVOLUMEDATA* input, int ch, CALCULATINGVOXELS* subset, VOL_KERNEL* roi, int numThreads);


#define VOXEL_VALUE_STATISTICS__H
#endif