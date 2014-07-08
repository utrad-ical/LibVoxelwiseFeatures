

//#include "DividedCalculatingVoxels.h"
#include "CalculatingVoxels.h"
#include "CheckRasterPositionedVoxelValuePresense.h"


CALCULATINGVOXELS* ConvertMaskToCalculatingVoxels(VOL_RAWVOLUMEDATA* mask, int channel)
{
	int count=0;

	for(int i=0; i<mask->matrixSize->depth*mask->matrixSize->height*mask->matrixSize->width; i++) {
		if(CheckRasterPositionedVoxelValuePresense(mask, channel, i))	count++;
	}

	CALCULATINGVOXELS* data = new CALCULATINGVOXELS;

	data->num = count;
	data->rp = new int [count];
	data->xc = new int [count];
	data->yc = new int [count];
	data->zc = new int [count];
//	data->volsize = VOL_GetIntSize3DFromIntSize4D(mask->matrixSize);

	int xye = mask->matrixSize->height*mask->matrixSize->width;
		// data->volsize->width*data->volsize->height;
	count=0;

	for(int i=0; i<mask->matrixSize->depth*mask->matrixSize->height*mask->matrixSize->width; i++) {
	if(CheckRasterPositionedVoxelValuePresense(mask, channel, i)) {
		data->rp[count] = i;
		data->zc[count] = data->rp[count]/xye;
		data->yc[count] = (data->rp[count]-data->zc[count]*xye)/mask->matrixSize->width;
		data->xc[count] = data->rp[count]%mask->matrixSize->width;
		count++;
	}}

	return data;
}

