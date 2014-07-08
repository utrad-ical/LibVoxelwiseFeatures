

#include "VOL.h"


VOL_INTBOX3D* BoundingBoxOfVolKernel(VOL_INTVECTOR3D* coord, VOL_KERNEL* kernel)
{
	VOL_LOCATIONARRAY* L = kernel->locationArray;

	/*
	for(int i=0; i<L->nElements; i++) {
		if(L->xMin>L->x[i])		L->xMin = L->x[i];
		if(L->yMin>L->y[i])		L->yMin = L->y[i];
		if(L->zMin>L->z[i])		L->zMin = L->z[i];
		if(L->xMax<L->x[i])		L->xMax = L->x[i];
		if(L->yMax<L->y[i])		L->yMax = L->y[i];
		if(L->zMax<L->z[i])		L->zMax = L->z[i];
	}
	*/

	VOL_INTVECTOR3D org;
	org.x = coord->x+L->xMin;
	org.y = coord->y+L->yMin;
	org.z = coord->z+L->zMin;

	VOL_INTSIZE3D sz;
	sz.width = L->xMax-L->xMin+1;
	sz.height = L->yMax-L->yMin+1;
	sz.depth = L->zMax-L->zMin+1;

	VOL_INTBOX3D* box = VOL_NewIntBox3D(&org, &sz);

	return box;
}

