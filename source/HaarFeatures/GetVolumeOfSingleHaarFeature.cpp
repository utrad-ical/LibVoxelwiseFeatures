

#include "HaarFeatures.h"
#include "HaarFeatures.private.h"
#include "../Utilities/ConvertMaskToCalculatingVoxels.h"


void CalculateSingleHaarFeature_forVoxelSubset(
	VOL_RAWVOLUMEDATA* input, int ch, CALCULATINGVOXELS* subset, VOL_KERNEL* kernel, int index, float*** output)
{
//	float*** feature = (float***)output->array4D[0];

	VOL_INTVECTOR3D coord;
	
	for(int i=0; i<subset->num; i++) {

	//	if(i%100==0)	printf("i%d,", i);
		
		coord.x = subset->xc[i]+kernel->intRad;
		coord.y = subset->yc[i]+kernel->intRad;
		coord.z = subset->zc[i]+kernel->intRad;
		
	//	printf("set[%d]=(%d,%d,%d)->coord(%d,%d,%d); ", 
	//		i,subset->xc[i],subset->yc[i],subset->zc[i],coord.x,coord.y,coord.z);

		float temp = CalculateSingleHaarFeature(input, ch, &coord, kernel, index);
	//	printf("%f", temp); 

		output[subset->zc[i]][subset->yc[i]][subset->xc[i]] = temp;
	//	printf("\n");
	}
}


VOL_RAWVOLUMEDATA* GetVolumeOfSingleHaarFeature(
	VOL_RAWVOLUMEDATA* volume, int vChannel, VOL_RAWVOLUMEDATA* mask, int mChannel, VOL_KERNEL* roi, int index)
{
	VOL_INTSIZE3D* size3d = VOL_GetIntSize3DFromIntSize4D(volume->matrixSize);

	VOL_RAWVOLUMEDATA* output = VOL_NewSingleChannelRawVolumeData(size3d, VOL_VALUEUNIT_FLOAT32, VOL_VALUETYPE_SINGLE);

	int margin = SetIntRadInVolKernel(roi);
	VOL_AttachOffsetXYZ(volume, margin, VOL_RESIZE_BACKGROUNDTYPE_BORDERCOPY_UNIFORM);

//	CALCULATINGVOXELS* subset = NewCalculatingVoxels(mask, mChannel);
	CALCULATINGVOXELS* subset = ConvertMaskToCalculatingVoxels(mask, mChannel);

	float*** featvol = (float***)output->array4D[0];
	CalculateSingleHaarFeature_forVoxelSubset(volume, vChannel, subset, roi, index, featvol);

	VOL_DeleteIntSize3D(size3d);
	DeleteCalculatingVoxels(subset);

	VOL_RemoveOffsetXYZ(volume, margin);

	return output;
}

