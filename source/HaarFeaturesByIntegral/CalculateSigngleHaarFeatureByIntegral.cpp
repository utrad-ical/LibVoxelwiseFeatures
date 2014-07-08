
#include "VOL.h"
#include "HaarFeaturesByIntegral.h"
#include "HaarFeaturesByIntegral.private.h"

#include "../Utilities/SumIntensityOfVoxelsInIntBoxByIntegral.h"


float CalculateSigngleHaarFeatureByIntegral(INTEGRALVOLUME* integral, VOL_INTVECTOR3D* coord, VOL_KERNEL* roi, int index)
{
	VOL_INTBOX3D* box = BoundingBoxOfVolKernel(coord, roi);

	double feat = CalculateSigngleHaarFeatureInIntBoxByIntegral(integral, box, index);

	VOL_DeleteIntBox3D(box);

	return (float)feat;
}


