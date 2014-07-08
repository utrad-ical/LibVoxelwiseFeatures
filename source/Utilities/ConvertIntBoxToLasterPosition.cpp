
#include "VOL.h"


VOL_LOCATIONARRAY* ConvertIntBoxToLasterPosition(VOL_INTBOX3D* box, VOL_INTSIZE3D* size)
{
	int boxvolume = box->size->width*box->size->height*box->size->depth;
	int xe = size->width;
	int xye = size->width*size->height;

	VOL_LOCATIONARRAY* ary = VOL_NewLocationArray(boxvolume);
	int num = 0;

	for(int k=box->origin->z; k<box->origin->z+box->size->depth; k++) {
	if(k>=0 && k<size->depth) { 
		int zp = k*xye;
		for(int j=box->origin->y; j<box->origin->y+box->size->height; j++) {
		if(j>=0 && j<size->height) { 
			int yp = j*xe;
			for(int i=box->origin->x; i<box->origin->x+box->size->width; i++) {
			if(i>=0 && i<size->width) { 
				ary->rasterPosition[num] = i+yp+zp;
				ary->z[num] = k;
				ary->y[num] = j;
				ary->x[num] = i;
				num++;
			}}
		}}
	}}

	ary->nElements = num;

	return ary;
}
