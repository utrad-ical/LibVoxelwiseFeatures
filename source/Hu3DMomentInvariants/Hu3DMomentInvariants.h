
#ifndef HU_3D_MOMENT_INVARIANTS__H


#include "VOL.h"
#include <cstdio>
#include "../Utilities/CalculatingVoxels.h"


#define NUM_HU_3D_MOMENT_INVARIANTS		5


typedef struct _HU_3D_MOMENT_INVARIANTS_
{
	float J1, J2;
	float delta;
	float I1, I2;	// max-order=2
}
HU3DMOMENTINVARIANTS;

HU3DMOMENTINVARIANTS CalculateHu3DMomentInvariants(
	VOL_RAWVOLUMEDATA* volume, int channel, VOL_INTVECTOR3D* coord, VOL_KERNEL* roi);


//																	//
//	details of output VOL_RAWVOLUMEDATA;							//
//		output->data[0][*] = J1,		output->data[1][*] = J2,	//
//		output->data[2][*] = delta,									//
//		output->data[3][*] = I1,		output->data[4][*] = I2		//
//																	//

VOL_RAWVOLUMEDATA* GetVolumeOfHu3DMomentInvariants(
	VOL_RAWVOLUMEDATA* volume, int channel,  VOL_RAWVOLUMEDATA* mask, int mch, VOL_KERNEL* roi);

VOL_RAWVOLUMEDATA* GetVolumeOfHu3DMomentInvariants_MT(
	VOL_RAWVOLUMEDATA* volume, int channel,  VOL_RAWVOLUMEDATA* mask, int mch, VOL_KERNEL* roi, int nthreads);


float** CalculateHu3DMomentInvariantsAtMultiPositions_MT(
	VOL_RAWVOLUMEDATA* in_volume, int channel, CALCULATINGVOXELS* subset, VOL_KERNEL* roi, int numThreads);


#define HU_3D_MOMENT_INVARIANTS__H
#endif