

#include "HaarFeaturesByIntegral.h"
#include "HaarFeaturesByIntegral.private.h"


float* CalculateMultiHaarFeatureByIntegral(INTEGRALVOLUME* integral, VOL_INTVECTOR3D* coord, VOL_KERNEL* roi);


void CalculateMultiHaarFeaturesAtVoxelsByIntegral(
	INTEGRALVOLUME* integral, CALCULATINGVOXELS* subset, VOL_KERNEL* kernel, float** output)
{
//	float** output = new float* [subset->num];
//	output[0] = new float [subset->num*NUM_HAAR_FEATURES];

	VOL_INTVECTOR3D coord;
	
	for(int i=0; i<subset->num; i++) {
		
		coord.x = subset->xc[i]; //+kernel->intRad;
		coord.y = subset->yc[i]; //+kernel->intRad;
		coord.z = subset->zc[i]; //+kernel->intRad;

		float* temp = CalculateMultiHaarFeatureByIntegral(integral, &coord, kernel);

	//	for(int f=0; f<NUM_HAAR_FEATURES; f++) {
	//		output[f][subset->zc[i]][subset->yc[i]][subset->xc[i]] = temp[f];
	//	}
		memcpy(output[i], temp, sizeof(float)*NUM_HAAR_FEATURES);

		delete temp;
	}
}


