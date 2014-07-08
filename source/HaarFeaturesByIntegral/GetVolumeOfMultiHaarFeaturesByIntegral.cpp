

#include "HaarFeaturesByIntegral.h"
#include "HaarFeaturesByIntegral.private.h"



VOL_RAWVOLUMEDATA* GetVolumeOfMultiHaarFeaturesByIntegral(VOL_RAWVOLUMEDATA* input, int ich, VOL_RAWVOLUMEDATA* mask, int mch, VOL_KERNEL* roi)
{
	VOL_INTSIZE3D* size3d = VOL_GetIntSize3DFromIntSize4D(input->matrixSize);

	INTEGRALVOLUME* integral = NewInitializedIntegralVolume(input, ich);
	
	int offsetXYZ = SetIntRadInVolKernel(roi);
	VOL_AttachOffsetXYZ(integral->volume, offsetXYZ, VOL_RESIZE_BACKGROUNDTYPE_BORDERCOPY_UNIFORM);
	SetIntegralVolume(integral);

	VOL_RAWVOLUMEDATA* output = VOL_NewSingleChannelRawVolumeData(size3d, VOL_VALUEUNIT_FLOAT32, VOL_VALUETYPE_SINGLE);
	for(int idx=1; idx<NUM_HAAR_FEATURES; idx++) {
		VOL_DuplicateChannelOfRawVolumeData(output, 0);
	}

//	CALCULATINGVOXELS* subset = NewCalculatingVoxels(mask, mch);
	CALCULATINGVOXELS* subset = ConvertMaskToCalculatingVoxels(mask, mch);

	for(int idx=0; idx<NUM_HAAR_FEATURES; idx++) {
		float*** features = (float***)output->array4D[idx];
		CalculateSingleHaarFeatureByIntegral_forVoxelSubset(integral, subset, roi, idx, features);
	}

	VOL_DeleteIntSize3D(size3d);
	DeleteIntegralVolume(integral);
	DeleteCalculatingVoxels(subset);

//	VOL_RemoveOffsetXYZ(input, offsetXYZ);

	return output;
}

