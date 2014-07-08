
#ifndef HAAR_FEATURES_PRIVATE__H


#include "VOL.h"

#include "../Utilities/BoundingBoxOfVolKernel.h"
#include "../Utilities/CalculatingVoxels.h"
#include "../Utilities/Check3DPositionedVoxelValuePresense.h"
#include "../Utilities/DividedCalculatingVoxels.h"
#include "../Utilities/SetIntRadInVolKernel.h"
#include "../Utilities/SumIntensityOfVoxelsInIntBox.h"


double CalculateSingleHaarFeatureInIntBox(VOL_RAWVOLUMEDATA* volume, int channel, VOL_INTBOX3D* box, int index);

void CalculateSingleHaarFeature_forVoxelSubset(
	VOL_RAWVOLUMEDATA* input, int ch, CALCULATINGVOXELS* subset, VOL_KERNEL* kernel, int index, float*** output);


//#include "../Utilities/IntegralVolume.h"
//float CalculateSigngleHaarFeatureByIntegralVolume(INTEGRALVOLUME* integral, VOL_INTBOX3D* box, int maskType);


#define HAAR_FEATURES_PRIVATE__H
#endif