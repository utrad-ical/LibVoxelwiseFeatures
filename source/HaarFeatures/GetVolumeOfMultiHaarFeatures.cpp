

#include "HaarFeatures.h"
#include "HaarFeatures.private.h"

#include "../Utilities/SetIntRadInVolKernel.h"
#include "../Utilities/CalculatingVoxels.h"
#include "../Utilities/ConvertMaskToCalculatingVoxels.h"


VOL_RAWVOLUMEDATA* GetVolumeOfMultiHaarFeatures(
	VOL_RAWVOLUMEDATA* volume, int vChannel, VOL_RAWVOLUMEDATA* mask, int mChannel, VOL_KERNEL* roi)
{
	VOL_INTSIZE3D* size3d = VOL_GetIntSize3DFromIntSize4D(volume->matrixSize);

	VOL_RAWVOLUMEDATA* output = VOL_NewSingleChannelRawVolumeData(size3d, VOL_VALUEUNIT_FLOAT32, VOL_VALUETYPE_SINGLE);
	for(int idx=1; idx<NUM_HAAR_FEATURES; idx++) {
		VOL_DuplicateChannelOfRawVolumeData(output, 0);
	}

	CALCULATINGVOXELS* subset = ConvertMaskToCalculatingVoxels(mask, mChannel);

	int margin = SetIntRadInVolKernel(roi);
	VOL_AttachOffsetXYZ(volume, margin, VOL_RESIZE_BACKGROUNDTYPE_BORDERCOPY_UNIFORM);

	for(int idx=0; idx<NUM_HAAR_FEATURES; idx++) {
		float*** featvol = (float***)output->array4D[idx];
		CalculateSingleHaarFeature_forVoxelSubset(volume, vChannel, subset, roi, idx, featvol);
	}

	VOL_DeleteIntSize3D(size3d);
	DeleteCalculatingVoxels(subset);

	VOL_RemoveOffsetXYZ(volume, margin);

	return output;
}

