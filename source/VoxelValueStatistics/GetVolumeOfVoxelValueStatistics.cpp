

#pragma warning(disable: 4996)


#include "VOL.h"
#include "VoxelValueStatistics.h"
#include "VoxelValueStatistics.private.h"
#include "../Utilities/ConvertMaskToCalculatingVoxels.h"



VOL_RAWVOLUMEDATA* GetVolumeOfVoxelValueStatistics(
	VOL_RAWVOLUMEDATA* volume, int vChannel, VOL_RAWVOLUMEDATA* mask, int mChannel, VOL_KERNEL* roi)
{
	VOL_INTSIZE3D* size = VOL_GetIntSize3DFromIntSize4D(volume->matrixSize);
//	printf("a,");

	VOL_RAWVOLUMEDATA* output = VOL_NewSingleChannelRawVolumeData(size, VOL_VALUEUNIT_FLOAT32, VOL_VALUETYPE_SINGLE);
	for(int i=1; i<NUM_VOXEL_VALUE_STATISTICS; i++) {
		VOL_AddNewChannelInRawVolumeData(output, VOL_VALUEUNIT_FLOAT32, VOL_VALUETYPE_SINGLE);
	}
//	printf("b,");

//	CALCULATINGVOXELS* subset = NewCalculatingVoxels(mask, mChannel);
	CALCULATINGVOXELS* subset = ConvertMaskToCalculatingVoxels(mask, mChannel);
//	ConvertPositions1DTo3DCalculatingVoxels(subset);
//	printf("c,");

	int margin = SetIntRadInVolKernel(roi);
	VOL_AttachOffsetXYZ(volume, margin, VOL_RESIZE_BACKGROUNDTYPE_BORDERCOPY_UNIFORM);
//	printf("d,");

	SetCalculatedStatisticsAsVoxelValue(volume, vChannel, output, subset, roi);
//	printf("e,");

	VOL_DeleteIntSize3D(size);
	DeleteCalculatingVoxels(subset);
	printf("f,");

	VOL_RemoveOffsetXYZ(volume, margin);
	printf("g\n");

	return output;
}


	
	




