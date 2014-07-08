

//#include "Hu3DMomentInvariants.h"
#include "Hu3DMomentInvariants.private.h"
#include <float.h>


template <typename VTYPE>
HU3DMOMENTS primitive_CalculateHu3DMoments(VTYPE*** vol, VOL_INTVECTOR3D* coord, VOL_KERNEL* kernel)
{
	HU3DMOMENTS hu;
	hu.m000 = hu.m002 = hu.m011 = hu.m020 = hu.m101 = hu.m110 = hu.m200 = 0.0;

	int orderMoment = 2;
	VOL_LOCATIONARRAY* ary = kernel->locationArray;

	double min_value=DBL_MAX;
	for(int c=0; c<ary->nElements; c++)
	{
		double value = (double)vol[coord->z+ary->z[c]][coord->y+ary->y[c]][coord->x+ary->x[c]];
		if(min_value>value)		min_value = value;
	}
//	min_value = min_value-(double)1.0/ary->nElements;
	min_value = min_value-1.0e-6;
	
	
	// intensity_weighted_gravity
	double gx=0.0, gy=0.0, gz=0.0;//, m000=0.0;

	for(int c=0; c<ary->nElements; c++)
	{
		double value = (double)vol[coord->z+ary->z[c]][coord->y+ary->y[c]][coord->x+ary->x[c]]-min_value;
		gx += value*(double)ary->x[c];
		gy += value*(double)ary->y[c];
		gz += value*(double)ary->z[c];
		hu.m000 += value;
	}
	gx /= hu.m000;
	gy /= hu.m000;
	gz /= hu.m000;

	// moments
	for(int c=0; c<ary->nElements; c++)
	{
		double value = (double)vol[coord->z+ary->z[c]][coord->y+ary->y[c]][coord->x+ary->x[c]]-min_value;
		double zk = (double)ary->z[c]-gz;
		double yj = (double)ary->y[c]-gy;
		double xi = (double)ary->x[c]-gx;

		hu.m200 += value*xi*xi;
		hu.m020 += value*yj*yj;
		hu.m002 += value*zk*zk;
		hu.m110 += value*xi*yj;
		hu.m101 += value*xi*zk;
		hu.m011 += value*yj*zk;
	}

	return hu;
}


HU3DMOMENTS CalculateHu3DMoments(VOL_RAWVOLUMEDATA* volume, int channel, VOL_INTVECTOR3D* coord, VOL_KERNEL* kernel)
{
	HU3DMOMENTS out;

	switch(volume->voxelUnit[channel]) {
	case VOL_VALUEUNIT_UINT8:
		out = primitive_CalculateHu3DMoments((unsigned char***)volume->array4D[channel], coord, kernel);
		break;
	case VOL_VALUEUNIT_SINT8:
		out = primitive_CalculateHu3DMoments((char***)volume->array4D[channel], coord, kernel);
		break;
	case VOL_VALUEUNIT_UINT16:
		out = primitive_CalculateHu3DMoments((unsigned short***)volume->array4D[channel], coord, kernel);
		break;
	case VOL_VALUEUNIT_SINT16:
		out = primitive_CalculateHu3DMoments((short***)volume->array4D[channel], coord, kernel);
		break;
	case VOL_VALUEUNIT_UINT32:
		out = primitive_CalculateHu3DMoments((unsigned int***)volume->array4D[channel], coord, kernel);
		break;
	case VOL_VALUEUNIT_SINT32:
		out = primitive_CalculateHu3DMoments((int***)volume->array4D[channel], coord, kernel);
		break;
	case VOL_VALUEUNIT_FLOAT32:
		out = primitive_CalculateHu3DMoments((float***)volume->array4D[channel], coord, kernel);
		break;
	case VOL_VALUEUNIT_FLOAT64:
		out = primitive_CalculateHu3DMoments((double***)volume->array4D[channel], coord, kernel);
		break;
	}

	return out;
}


