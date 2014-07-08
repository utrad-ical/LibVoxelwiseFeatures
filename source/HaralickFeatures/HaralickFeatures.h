
#ifndef HARALICK_FEATURES__H


#include "VOL.h"


typedef struct VOLUME_HARALICK_CALCULATION
{
	int margin;			// xyz-margin of volume
	int numGradation;
	void* vol;			// including unsigned-char single-channel volume
}
VOLUMEHARALICKCALCULATION;


VOLUMEHARALICKCALCULATION* NewVolumeHaralickCalculation(
	VOL_RAWVOLUMEDATA* volume, int channel, VOL_VALUERANGE* range, int numGradation, VOL_KERNEL* roi, VOL_KERNEL* references);

void DeleteVolumeHaralickCalculation(VOLUMEHARALICKCALCULATION* volumeH);


#define NUM_HARALICK_FEATURES	11
// [0] asm: angular second moment
// [1] idm: inverse difference moment
// [2] cnt: contrast
// [3] var: variance
// [4] ent: entropy
// [5] crr: correlation
// [6] sumavg: sum average
// [7] sumvar: sum variance
// [8] sument: sum entropy
// [9] difvar: difference variance
// [10] difent: difference entropy


float* CalculateHaralickFeatures(
	VOLUMEHARALICKCALCULATION* volumeH, VOL_INTVECTOR3D* coord, VOL_KERNEL* roi, VOL_KERNEL* references);


VOL_RAWVOLUMEDATA* GetVolumeOfHaralickFeatures(
	VOL_RAWVOLUMEDATA* volume, int channel, VOL_RAWVOLUMEDATA* mask, int cmask, 
	VOL_VALUERANGE* range, int numGradation, VOL_KERNEL* roi, VOL_KERNEL* references);


VOL_RAWVOLUMEDATA* GetVolumeOfHaralickFeatures_MT(
	VOL_RAWVOLUMEDATA* volume, int channel, VOL_RAWVOLUMEDATA* mask, int cmask, 
	VOL_VALUERANGE* range, int numGradation, VOL_KERNEL* roi, VOL_KERNEL* references, int numThreads);


#define HARALICK_FEATURES__H
#endif