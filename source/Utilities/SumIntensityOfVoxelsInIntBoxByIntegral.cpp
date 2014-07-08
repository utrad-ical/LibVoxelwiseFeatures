

#include "VOL.h"
#include "IntegralVolume.h"



template <typename VTYPE>
double primitive_SumIntensityOfVoxelsInIntBoxByIntegral(VTYPE*** vol, VOL_INTBOX3D* box)
{
	double a=0.0, b=0.0, c=0.0, d=0.0, e=0.0, f=0.0, g=0.0, h=0.0;

	int xTop = box->origin->x+box->size->width-1, xOut = box->origin->x-1;
	int yTop = box->origin->y+box->size->height-1, yOut = box->origin->y-1;
	int zTop = box->origin->z+box->size->depth-1, zOut = box->origin->z-1;

	a=(double)vol[zTop][yTop][xTop];
	if(zOut>=0)		b=(double)vol[zOut][yTop][xTop];
	if(xOut>=0)
	{
		c=(double)vol[zTop][yTop][xOut];
		if(zOut>=0)		d=(double)vol[zOut][yTop][xOut];
	}
	if(yOut>=0)
	{
		e=(double)vol[zTop][yOut][xTop];
		if(zOut>=0)		f=(double)vol[zOut][yOut][xTop];
	}
	if(xOut>=0 && yOut>=0)
	{
		g=(double)vol[zTop][yOut][xOut];
		if(zOut>=0)		h=(double)vol[zOut][yOut][xOut];
	}

	return a-b-c+d-e+f+g-h;
}


double SumIntensityOfVoxelsInIntBoxByIntegral(INTEGRALVOLUME* integral, VOL_INTBOX3D* box)
{
	double sum;

	switch(integral->volume->voxelUnit[0])
	{

	case VOL_VALUEUNIT_UINT32:
		sum = primitive_SumIntensityOfVoxelsInIntBoxByIntegral((unsigned int***)integral->volume->array4D[0], box);
		break;

	case VOL_VALUEUNIT_SINT32:
		sum = primitive_SumIntensityOfVoxelsInIntBoxByIntegral((int***)integral->volume->array4D[0], box);
		break;

	case VOL_VALUEUNIT_FLOAT64:
		sum = primitive_SumIntensityOfVoxelsInIntBoxByIntegral((double***)integral->volume->array4D[0], box);
		break;
	}

	return sum;
}
