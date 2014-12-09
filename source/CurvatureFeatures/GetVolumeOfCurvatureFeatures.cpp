

#include "CurvatureFeatures.h"

//#include "../Utilities/CalculatingVoxels.h"
//#include "../Utilities/DividedCalculatingVoxels.h"
#include "../Utilities/ConvertMaskToCalculatingVoxels.h"
#include "../Utilities/SetIntRadInVolKernel.h"


void CalculateCurvatureFeatures_SubsetOfVoxels(
	VOL_RAWVOLUMEDATA* input, int ch, VOL_RAWVOLUMEDATA* output, CALCULATINGVOXELS* subset, int margin);


VOL_RAWVOLUMEDATA* GetVolumeOfCurvatureFeatures(
	VOL_RAWVOLUMEDATA* volume, int vChannel, VOL_RAWVOLUMEDATA* mask, int mChannel)
{
	VOL_INTSIZE3D* size = VOL_GetIntSize3DFromIntSize4D(volume->matrixSize);

	VOL_RAWVOLUMEDATA* output = VOL_NewSingleChannelRawVolumeData(size, VOL_VALUEUNIT_FLOAT32, VOL_VALUETYPE_SINGLE);
	for(int i=1; i<NUM_CURVATURE_FEATURES; i++) {
		VOL_AddNewChannelInRawVolumeData(output, VOL_VALUEUNIT_FLOAT32, VOL_VALUETYPE_SINGLE);
	}

	CALCULATINGVOXELS* subset = ConvertMaskToCalculatingVoxels(mask, mChannel);

	VOL_RAWVOLUMEDATA* voltmp = VOL_ExtractSingleChannelRawVolumeData(volume, vChannel);

	int margin = 1;
	VOL_AttachOffsetXYZ(voltmp, margin, VOL_RESIZE_BACKGROUNDTYPE_BORDERCOPY_UNIFORM);

	VOL_ConvertVoxelUnit(voltmp, 0, VOL_VALUEUNIT_FLOAT32, NULL, NULL, VOL_CONVERTUNIT_TYPE_DIRECT);

	// CalculateCurvatureFeatures_SubsetOfVoxels(volume, vChannel, output, subset);
	CalculateCurvatureFeatures_SubsetOfVoxels(voltmp, 0, output, subset, margin);

	VOL_DeleteIntSize3D(size);
	DeleteCalculatingVoxels(subset);
	VOL_DeleteRawVolumeData(voltmp);

	return output;
}

