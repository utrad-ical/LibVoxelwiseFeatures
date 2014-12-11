

#include "VoxelValueStatistics.h"
#include "../Utilities/CalculatingVoxels.h"


void SetCalculatedStatisticsAsVoxelValue(
	VOL_RAWVOLUMEDATA* input, int ch, VOL_RAWVOLUMEDATA* output, CALCULATINGVOXELS* subset, VOL_KERNEL* kernel)
{
//	float**** features = (float****)output->array4D;
	float*** mean_vol = (float***)output->array4D[0];
	float*** var_vol = (float***)output->array4D[1];
	float*** skew_vol = (float***)output->array4D[2];
	float*** kurt_vol = (float***)output->array4D[3];

	VOL_INTVECTOR3D coord;
	
	for(int i=0; i<subset->num; i++) {
		
		coord.x = subset->xc[i]+kernel->intRad;
		coord.y = subset->yc[i]+kernel->intRad;
		coord.z = subset->zc[i]+kernel->intRad;
	//	printf("set[%d]=(%d,%d,%d)->coord(%d,%d,%d); ", 
	//		i,subset->xc[i],subset->yc[i],subset->zc[i],coord.x,coord.y,coord.z);

		VOXELVALUESTATISTICS temp = CalculateVoxelValueStatistics(input, ch, &coord, kernel);
	//	printf("%f,%f,%f,%f ", temp.mean,temp.var,temp.skew,temp.kurt);

		mean_vol[subset->zc[i]][subset->yc[i]][subset->xc[i]] = temp.mean;
		var_vol[subset->zc[i]][subset->yc[i]][subset->xc[i]] = temp.var;
		skew_vol[subset->zc[i]][subset->yc[i]][subset->xc[i]] = temp.skew;
		kurt_vol[subset->zc[i]][subset->yc[i]][subset->xc[i]] = temp.kurt;
	//	printf("ok\n");
	}

	return;
}

