

#include "CalculatingVoxels.h"


int CalculatingVoxels_AttachOffsetXYZ(CALCULATINGVOXELS* data, int* orgsize3d, int offset)
{
	int xe = orgsize3d[0]+offset, xye = (orgsize3d[0]+offset)*(orgsize3d[1]+offset);

	for(int i=0; i<data->num; i++) {
		data->zc[i] += offset;
		data->yc[i] += offset;
		data->xc[i] += offset;
		data->rp[i] = data->xc[i] + data->yc[i]*xe + data->zc[i]*xye;
	}

	return 0;
}