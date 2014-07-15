

#include "CurvatureFeatures.h"

//#include "../Utilities/CalculatingVoxels.h"
//#include "../Utilities/DividedCalculatingVoxels.h"
#include "../Utilities/ConvertMaskToCalculatingVoxels.h"
#include "../Utilities/SetIntRadInVolKernel.h"


void CalculateCurvatureFeatures_SubsetOfVoxels(
	VOL_RAWVOLUMEDATA* input, int ch, VOL_RAWVOLUMEDATA* output, CALCULATINGVOXELS* subset);


VOL_RAWVOLUMEDATA* GetVolumeOfCurvatureFeatures(
	VOL_RAWVOLUMEDATA* volume, int vChannel, VOL_RAWVOLUMEDATA* mask, int mChannel)
{
	VOL_INTSIZE3D* size = VOL_GetIntSize3DFromIntSize4D(volume->matrixSize);
	printf("a,");

	VOL_RAWVOLUMEDATA* output = VOL_NewSingleChannelRawVolumeData(size, VOL_VALUEUNIT_FLOAT32, VOL_VALUETYPE_SINGLE);
	for(int i=1; i<NUM_CURVATURE_FEATURES; i++) {
		VOL_AddNewChannelInRawVolumeData(output, VOL_VALUEUNIT_FLOAT32, VOL_VALUETYPE_SINGLE);
	}
	printf("b,");

	CALCULATINGVOXELS* subset = ConvertMaskToCalculatingVoxels(mask, mChannel);
	printf("c,");

	CalculateCurvatureFeatures_SubsetOfVoxels(volume, vChannel, output, subset);
	printf("e,");

	VOL_DeleteIntSize3D(size);
	DeleteCalculatingVoxels(subset);
	printf("f\n");

	return output;
}

