
#include "VOL.h"
#include "ConvertIntBoxToLasterPosition.h"
#include "SumIntensityOfGivenVoxels.h"


float SumIntensityOfVoxelsInIntBox(VOL_RAWVOLUMEDATA* volume, int channel, VOL_INTBOX3D* box)
{
	VOL_INTSIZE3D* size = VOL_GetIntSize3DFromIntSize4D(volume->matrixSize);

	VOL_LOCATIONARRAY* posi = ConvertIntBoxToLasterPosition(box, size);

	double sum = SumIntensityOfGivenVoxels(volume->data[channel], volume->voxelUnit[channel], posi);

	VOL_DeleteIntSize3D(size);
	VOL_DeleteLocationArray(posi);

	return (float)sum;
}
