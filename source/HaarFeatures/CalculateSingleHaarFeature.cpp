
#include "HaarFeatures.h"
#include "HaarFeatures.private.h"
#include "../Utilities/BoundingBoxOfVolKernel.h"


float CalculateSingleHaarFeature(
	VOL_RAWVOLUMEDATA* volume, int channel, VOL_INTVECTOR3D* coord, VOL_KERNEL* roi, int index)
{
	VOL_INTBOX3D* box = BoundingBoxOfVolKernel(coord, roi);
//	printf("calcbox{(%d,%d,%d),[%d,%d,%d]}, ", 
//		box->origin->x,box->origin->y,box->origin->z,box->size->width,box->size->height,box->size->depth);

	if(box->origin->x<0 || box->origin->x+box->size->width>volume->matrixSize->width ||
		box->origin->y<0 || box->origin->y+box->size->height>volume->matrixSize->height ||
		box->origin->z<0 || box->origin->z+box->size->depth>volume->matrixSize->depth )
	{
		printf("\nERROR; p(%d,%d,%d)=box{org(%d,%d,%d),sz(%d,%d,%d)} <-> volsize(%d,%d,%d) ", 
			coord->x,coord->y,coord->z,
			box->origin->x,box->origin->y,box->origin->z,
			box->size->width,box->size->height,box->size->depth,
			volume->matrixSize->width,volume->matrixSize->height,volume->matrixSize->depth);
		getchar();
	}

	double feat = CalculateSingleHaarFeatureInIntBox(volume, channel, box, index);

	VOL_DeleteIntBox3D(box);

	return (float)feat;
}

