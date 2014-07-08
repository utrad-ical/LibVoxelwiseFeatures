

#include "ConvertMaskToCalculatingVoxels.h"
#include "DividedCalculatingVoxels.h"
#include "CheckRasterPositionedVoxelValuePresense.h"


DIVIDEDCALCULATINGVOXELS* NewDividedCalculatingVoxels(CALCULATINGVOXELS* voxels, int ndiv)
{
	DIVIDEDCALCULATINGVOXELS* data = new DIVIDEDCALCULATINGVOXELS;

	data->ndiv = ndiv;
	data->set = new CALCULATINGVOXELS* [ndiv];
	float n_single_div = (float)voxels->num/(float)ndiv;

	int sum=0;
	for(int i=0; i<data->ndiv; i++) {
		data->set[i] = new CALCULATINGVOXELS;
		data->set[i]->num = (int)(n_single_div*(float)(i+1)+0.5f)-(int)(n_single_div*(float)i+0.5f);
		data->set[i]->rp = new int [data->set[i]->num];
		data->set[i]->xc = new int [data->set[i]->num];
		data->set[i]->yc = new int [data->set[i]->num];
		data->set[i]->zc = new int [data->set[i]->num];
		sum += data->set[i]->num;
	}

	int cnt_div=0, cnt_area=0;
	for(int i=0; i<voxels->num; i++) {
		data->set[cnt_div]->rp[cnt_area] = voxels->rp[i];
		data->set[cnt_div]->zc[cnt_area] = voxels->zc[i];
		data->set[cnt_div]->yc[cnt_area] = voxels->yc[i];
		data->set[cnt_div]->xc[cnt_area] = voxels->xc[i];
		cnt_area++;
		if(cnt_area==data->set[cnt_div]->num) {
			cnt_div++;	cnt_area=0;
		}
	}

	return data;
}


DIVIDEDCALCULATINGVOXELS* NewDividedCalculatingVoxelsFromMask(VOL_RAWVOLUMEDATA* mask, int channel, int ndiv)
{
	CALCULATINGVOXELS* voxels = ConvertMaskToCalculatingVoxels(mask, channel);

	DIVIDEDCALCULATINGVOXELS* data = NewDividedCalculatingVoxels(voxels, ndiv);

	DeleteCalculatingVoxels(voxels);

	return data;

//	int numdata = mask->matrixSize->depth*mask->matrixSize->height*mask->matrixSize->width;
//	int numarea = 0;

//	for(int i=0; i<numdata; i++) {
//		if(CheckRasterPositionedVoxelValuePresense(mask, channel, i))	numarea++;
//	}
//	float n_single_div = (float)voxels->num/(float)ndiv;

//	DIVIDEDCALCULATINGVOXELS* data = new DIVIDEDCALCULATINGVOXELS;
//	data->ndiv = ndiv;
//	data->set = new CALCULATINGVOXELS* [ndiv];
//	data->volsize = VOL_GetIntSize3DFromIntSize4D(mask->matrixSize);

//	int sum=0;
//	for(int i=0; i<data->ndiv; i++) {
//		data->set[i] = new CALCULATINGVOXELS;
//		data->set[i]->num = (int)(n_single_div*(float)(i+1)+0.5f)-(int)(n_single_div*(float)i+0.5f);
//	//	data->set[i]->volsize = data->volsize;
//		data->set[i]->rp = new int [data->set[i]->num];
//		data->set[i]->xc = new int [data->set[i]->num];
//		data->set[i]->yc = new int [data->set[i]->num];
//		data->set[i]->zc = new int [data->set[i]->num];
//		sum += data->set[i]->num;
//	}
	
//	int cnt_div=0, cnt_area=0;
//	int xye = mask->matrixSize->height*mask->matrixSize->width;

//	for(int i=0; i<numdata; i++) {
//
//		if(cnt_div>=data->ndiv)		break;
//
//		if(CheckRasterPositionedVoxelValuePresense(mask, channel, i)) {
//
//			data->set[cnt_div]->rp[cnt_area] = i;
//			data->set[cnt_div]->zc[cnt_area] = i/xye;
//			data->set[cnt_div]->yc[cnt_area] = (i-data->set[cnt_div]->zc[cnt_area]*xye)/data->volsize->width;
//			data->set[cnt_div]->xc[cnt_area] = i%data->volsize->width;
//			cnt_area++;
//
//			if(cnt_area==data->set[cnt_div]->num) {
//				cnt_div++;
//				cnt_area=0;
//			}
//		}
//	}
//
//	return data;
}


void DeleteDividedCalculatingVoxels(DIVIDEDCALCULATINGVOXELS* data)
{
	for(int i=0; i<data->ndiv; i++) {
		if(data->set[i]->rp!=NULL)	delete [] data->set[i]->rp;
		if(data->set[i]->xc!=NULL)	delete [] data->set[i]->xc;
		if(data->set[i]->yc!=NULL)	delete [] data->set[i]->yc;
		if(data->set[i]->zc!=NULL)	delete [] data->set[i]->zc;
		delete data->set[i];
	}
//	VOL_DeleteIntSize3D(data->volsize);
	delete [] data->set;
	delete data;
}