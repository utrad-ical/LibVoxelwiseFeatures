

#include "HaarFeaturesByIntegral.h"
#include "HaarFeaturesByIntegral.private.h"


float* CalculateMultiHaarFeatureByIntegral(INTEGRALVOLUME* integral, VOL_INTVECTOR3D* coord, VOL_KERNEL* roi);


void CalculateMultiHaarFeatureByIntegral_forVoxelSubset(
	INTEGRALVOLUME* integral, CALCULATINGVOXELS* subset, VOL_KERNEL* kernel, float**** output)
{
	VOL_INTVECTOR3D coord;
	
	for(int i=0; i<subset->num; i++) {
		
		coord.x = subset->xc[i]+kernel->intRad;
		coord.y = subset->yc[i]+kernel->intRad;
		coord.z = subset->zc[i]+kernel->intRad;

		float* temp = CalculateMultiHaarFeatureByIntegral(integral, &coord, kernel);

		for(int f=0; f<NUM_HAAR_FEATURES; f++) {
			output[f][subset->zc[i]][subset->yc[i]][subset->xc[i]] = temp[f];
		}

		delete temp;
	}
}




