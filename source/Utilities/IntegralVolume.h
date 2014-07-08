
#ifndef INTEGRAL_VOLUME__H


#include "VOL.h"


typedef struct INTEGRAL_VOLUME
{
	double intensity_offset;
	VOL_RAWVOLUMEDATA* volume;
}
INTEGRALVOLUME;


INTEGRALVOLUME* NewInitializedIntegralVolume(VOL_RAWVOLUMEDATA* source, int channel);

void DeleteIntegralVolume(INTEGRALVOLUME* data);

void SetIntegralVolume(INTEGRALVOLUME* initialized);

//INTEGRALVOLUME* GetIntegralVolume(VOL_RAWVOLUMEDATA* volume, int channel);



#define INTEGRAL_VOLUME__H
#endif
