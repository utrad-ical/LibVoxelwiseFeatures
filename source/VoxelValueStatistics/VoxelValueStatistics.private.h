
#ifndef VOXEL_VALUE_STATISTICS_PRIVATE__H

#include "VOL.h"

#include "../Utilities/CalculatingVoxels.h"
#include "../Utilities/DividedCalculatingVoxels.h"
#include "../Utilities/SetIntRadInVolKernel.h"


//VOXELVALUESTATISTICS CalculateVoxelValueStatistics(VOL_RAWVOLUMEDATA* volume, int channel, VOL_INTVECTOR3D* coord, VOL_KERNEL* kernel);

void SetCalculatedStatisticsAsVoxelValue(
	VOL_RAWVOLUMEDATA* input, int ch, VOL_RAWVOLUMEDATA* output, CALCULATINGVOXELS* subset, VOL_KERNEL* kernel);


#define VOXEL_VALUE_STATISTICS_PRIVATE__H
#endif