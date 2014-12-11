

#include "VoxelValueStatistics.h"
#include "../Utilities/CalculatingVoxels.h"


void MemorySetOfVoxelValueStatisticsAtMultiPositions(
	VOL_RAWVOLUMEDATA* input, int ch, CALCULATINGVOXELS* subset, VOL_KERNEL* kernel, float** output)
{
	VOL_INTVECTOR3D coord;
	
	for(int i=0; i<subset->num; i++) {
		
		coord.x = subset->xc[i]; //+kernel->intRad;
		coord.y = subset->yc[i]; //+kernel->intRad;
		coord.z = subset->zc[i]; //+kernel->intRad;
	//	printf("set[%d]=(%d,%d,%d)->coord(%d,%d,%d); ", 
	//		i,subset->xc[i],subset->yc[i],subset->zc[i],coord.x,coord.y,coord.z);

		VOXELVALUESTATISTICS temp = CalculateVoxelValueStatistics(input, ch, &coord, kernel);
	//	printf("%f,%f,%f,%f ", temp.mean,temp.var,temp.skew,temp.kurt);

		output[i][0] = temp.mean;
		output[i][1] = temp.var;
		output[i][2] = temp.skew;
		output[i][3] = temp.kurt;

	//	features[0][subset->zc[i]][subset->yc[i]][subset->xc[i]] = temp.mean;
	//	features[1][subset->zc[i]][subset->yc[i]][subset->xc[i]] = temp.var;
	//	features[2][subset->zc[i]][subset->yc[i]][subset->xc[i]] = temp.skew;
	//	features[3][subset->zc[i]][subset->yc[i]][subset->xc[i]] = temp.kurt;
	//	printf("ok\n");
	}

	return;
}

