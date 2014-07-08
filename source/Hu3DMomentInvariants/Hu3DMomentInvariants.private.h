
#ifndef HU_3D_MOMENT_INVARIANTS_PRIVATE__H


#include "VOL.h"
#include <cstdio>


#define NUM_INVARIANTS_FROM_HU_3D_MOMENT 5


typedef struct _HU_3D_MOMENTS_
{
	double m000, m200, m020, m002, m110, m101, m011;
}
HU3DMOMENTS;



HU3DMOMENTS CalculateHu3DMoments(VOL_RAWVOLUMEDATA* volume, int channel, VOL_INTVECTOR3D* coord, VOL_KERNEL* kernel);

float* CalculateInvariantsFromHu3DMoments(HU3DMOMENTS* hu);	//	out = { J1, J2, delta, I1, I2 }


/*
VOL_RAWVOLUMEDATA* Hu3DMomentInvariantsVolume(VOL_RAWVOLUMEDATA* volume, int channel, VOL_KERNEL* kernel);
VOL_RAWVOLUMEDATA* Hu3DMomentInvariantsVolume_MT(VOL_RAWVOLUMEDATA* volume, int channel, VOL_KERNEL* kernel, int nthreads);
*/


#define HU_3D_MOMENT_INVARIANTS_PRIVATE__H
#endif