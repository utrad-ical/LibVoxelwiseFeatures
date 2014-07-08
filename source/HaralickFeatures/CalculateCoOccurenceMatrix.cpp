
#include "VOL.h"


float* CalculateCoOccurrenceMatrix(
	VOL_RAWVOLUMEDATA* volume, int channel, int gradation, VOL_INTVECTOR3D* coord, 
	VOL_KERNEL* roi, VOL_KERNEL* dispracements)
{
	VOL_LOCATIONARRAY* R = roi->locationArray;
	VOL_LOCATIONARRAY* D = dispracements->locationArray;

	unsigned char*** vol = (unsigned char***)volume->array4D[channel];

	int nmat = gradation*gradation;
	int ndata = R->nElements*D->nElements;
	float w = 1.0f/(float)ndata;

	float* coMatrix1D = new float [nmat];
	memset(coMatrix1D, 0x00, sizeof(float)*nmat);

	for(int ir=0; ir<R->nElements; ir++) {

		int x = coord->x+R->x[ir];
		int y = coord->y+R->y[ir];
		int z = coord->z+R->z[ir];
		int p = (int)vol[z][y][x];
		int pj = p*gradation;

		for(int id=0; id<D->nElements; id++) {

			int r = (int)vol[z+D->z[id]][y+D->y[id]][x+D->x[id]];
			coMatrix1D[pj+r] += w;
		}
	}

	/*
	int num = (int)gradation*((int)gradation+1)/2;
	float* coMatrix1D = new float [num];
	memset(coMatrix1D, 0x00, sizeof(float)*num);

	int p = (int)vol[coord->z][coord->y][coord->x];
	if(p>=gradation)	p = gradation-1;
	int pj = (int)p*((int)p+1)/2;

	for(int t=0; t<references->nElements; t++)
	{
		int i = coord->x+references->x[t];
		int j = coord->y+references->y[t];
		int k = coord->z+references->z[t];

		int r = (int)vol[k][j][i];
	//	if(r>=gradation)	r = gradation-1;
		
		coMatrix1D[pj+r] += 1.0f/(float)references->nElements;
	}
	*/

	return coMatrix1D;
	
}

