
#include "VOL.h"


int SetIntRadInVolKernel(VOL_KERNEL* kernel)
{
	VOL_LOCATIONARRAY* L = kernel->locationArray;
	
	int rad = 1;
	for(int i=0; i<L->nElements; i++) {
		if(rad<abs(L->x[i]))		rad = abs(L->x[i]);
		if(rad<abs(L->y[i]))		rad = abs(L->y[i]);
		if(rad<abs(L->z[i]))		rad = abs(L->z[i]);
	}
//	if(rad<0)	rad = 0;

	kernel->intRad = rad;

	return rad;
}

