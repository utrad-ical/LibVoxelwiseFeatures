
#ifndef HAAR_FEATURES_BY_INTEGRAL_PRIVATE__H


#include "VOL.h"

#include "../Utilities/BoundingBoxOfVolKernel.h"
#include "../Utilities/CalculatingVoxels.h"
#include "../Utilities/ConvertMaskToCalculatingVoxels.h"
#include "../Utilities/Check3DPositionedVoxelValuePresense.h"
#include "../Utilities/DividedCalculatingVoxels.h"
#include "../Utilities/IntegralVolume.h"
#include "../Utilities/SetIntRadInVolKernel.h"
//#include "../Utilities/SumIntensityOfVoxelsInIntBox.h"
#include "../Utilities/SumIntensityOfVoxelsInIntBoxByIntegral.h"


float CalculateSigngleHaarFeatureInIntBoxByIntegral(INTEGRALVOLUME* integral, VOL_INTBOX3D* box, int index);
float CalculateSigngleHaarFeatureByIntegral(INTEGRALVOLUME* integral, VOL_INTVECTOR3D* coord, VOL_KERNEL* roi, int index);

void CalculateSingleHaarFeatureByIntegral_forVoxelSubset(INTEGRALVOLUME* integral, CALCULATINGVOXELS* subset, VOL_KERNEL* kernel, int index, float*** output);


typedef struct THREADING_VOLUME_HAAR_FEATURES
{
	INTEGRALVOLUME* integral;
	CALCULATINGVOXELS* subset;
	VOL_KERNEL* roi;
	int index;
	VOL_RAWVOLUMEDATA* output;
}
THREADING_VOLUMEHAARFEATURES;


#define HAAR_FEATURES_BY_INTEGRAL_PRIVATE__H
#endif