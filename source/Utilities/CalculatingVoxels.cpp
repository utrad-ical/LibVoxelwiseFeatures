

#include "CalculatingVoxels.h"
#include "CheckRasterPositionedVoxelValuePresense.h"



//CALCULATINGVOXELS* NewCalculatingVoxels(VOL_RAWVOLUMEDATA* mask, int channel)
CALCULATINGVOXELS* NewCalculatingVoxels(int num)
{
	int count = num; //=0;

	CALCULATINGVOXELS* data = new CALCULATINGVOXELS;
	data->num = count;
	data->rp = new int [count];
	data->xc = new int [count];
	data->yc = new int [count];
	data->zc = new int [count];

	return data;
}


CALCULATINGVOXELS* DuplicateCalculatingVoxels(CALCULATINGVOXELS* data)
{
	CALCULATINGVOXELS* out = NewCalculatingVoxels(data->num);
	memcpy(out->rp, data->rp, sizeof(int)*data->num);
	memcpy(out->xc, data->xc, sizeof(int)*data->num);
	memcpy(out->yc, data->yc, sizeof(int)*data->num);
	memcpy(out->zc, data->zc, sizeof(int)*data->num);
	return out;
}


void DeleteCalculatingVoxels(CALCULATINGVOXELS* data)
{
	if(data->rp!=NULL)	delete [] data->rp;
	if(data->xc!=NULL)	delete [] data->xc;
	if(data->yc!=NULL)	delete [] data->yc;
	if(data->zc!=NULL)	delete [] data->zc;
//	VOL_DeleteIntSize3D(data->volsize);
	delete data;
}

/*
int ConvertPositions1DTo3DCalculatingVoxels(CALCULATINGVOXELS* data)
{
	if(data->rp==NULL)	return 1;

	int xye = data->volsize->width*data->volsize->height;

	data->xc = new int [data->num];
	data->yc = new int [data->num];
	data->zc = new int [data->num];

	for(int i=0; i<data->num; i++) {
		data->zc[i] = data->rp[i]/xye;
		data->yc[i] = (data->rp[i]-data->zc[i]*xye)/data->volsize->width;
		data->xc[i] = data->rp[i]%data->volsize->width;
	}

	delete [] data->rp;

	return 0;
}

/*
int ConvertPositions3DTo1DCalculatingVoxels(CALCULATINGVOXELS* data)
{
	if(data->xc==NULL)	return 1;

	int xye = data->volsize->width*data->volsize->height;

	data->rp = new int [data->num];

	for(int i=0; i<data->num; i++) {
		data->rp[i] = data->xc[i]+data->yc[i]*data->volsize->width+data->zc[i]*xye;
	}

	delete [] data->xc;
	delete [] data->yc;
	delete [] data->zc;

	return 0;
}
*/




