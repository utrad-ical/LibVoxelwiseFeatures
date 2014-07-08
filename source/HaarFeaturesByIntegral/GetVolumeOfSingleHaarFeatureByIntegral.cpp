

#include "HaarFeaturesByIntegral.h"
#include "HaarFeaturesByIntegral.private.h"



void CalculateSingleHaarFeatureByIntegral_forVoxelSubset(
	INTEGRALVOLUME* integral, CALCULATINGVOXELS* subset, VOL_KERNEL* kernel, int index, float*** output)
{
//	float*** feature = (float***)output->array4D[0];

	VOL_INTVECTOR3D coord;
	
	for(int i=0; i<subset->num; i++) {
		
		coord.x = subset->xc[i]+kernel->intRad;
		coord.y = subset->yc[i]+kernel->intRad;
		coord.z = subset->zc[i]+kernel->intRad;

		float temp = CalculateSigngleHaarFeatureByIntegral(integral, &coord, kernel, index);

		output[subset->zc[i]][subset->yc[i]][subset->xc[i]] = temp;
	}
}


VOL_RAWVOLUMEDATA* GetVolumeOfSingleHaarFeatureByIntegral(VOL_RAWVOLUMEDATA* input, int ich, VOL_RAWVOLUMEDATA* mask, int mch, VOL_KERNEL* roi, int index)
{
	VOL_INTSIZE3D* size3d = VOL_GetIntSize3DFromIntSize4D(input->matrixSize);

	INTEGRALVOLUME* integral = NewInitializedIntegralVolume(input, ich);
	
	int offsetXYZ = SetIntRadInVolKernel(roi);
	VOL_AttachOffsetXYZ(integral->volume, offsetXYZ, VOL_RESIZE_BACKGROUNDTYPE_BORDERCOPY_UNIFORM);
	SetIntegralVolume(integral);

	VOL_RAWVOLUMEDATA* output = VOL_NewSingleChannelRawVolumeData(size3d, VOL_VALUEUNIT_FLOAT32, VOL_VALUETYPE_SINGLE);

//	CALCULATINGVOXELS* subset = NewCalculatingVoxels(mask, mch);
	CALCULATINGVOXELS* subset = ConvertMaskToCalculatingVoxels(mask, mch);

	float*** feature = (float***)output->array4D[0];
	CalculateSingleHaarFeatureByIntegral_forVoxelSubset(integral, subset, roi, index, feature);

	VOL_DeleteIntSize3D(size3d);
	DeleteIntegralVolume(integral);
	DeleteCalculatingVoxels(subset);

//	VOL_RemoveOffsetXYZ(input, offsetXYZ);

	return output;
}


