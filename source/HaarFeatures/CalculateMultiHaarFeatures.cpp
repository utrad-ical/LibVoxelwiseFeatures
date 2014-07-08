

#include "HaarFeatures.h"
#include "HaarFeatures.private.h"


float* CalculateMultiHaarFeatures(
	VOL_RAWVOLUMEDATA* volume, int channel, VOL_INTVECTOR3D* coord, VOL_KERNEL* roi)
{
	VOL_INTBOX3D* box = BoundingBoxOfVolKernel(coord, roi);

	float* feats = new float [NUM_HAAR_FEATURES];
	for(int i=0; i<NUM_HAAR_FEATURES; i++) {
		feats[i] = (float)CalculateSingleHaarFeatureInIntBox(volume, channel, box, i);
	}

	VOL_DeleteIntBox3D(box);

	return feats;
}





