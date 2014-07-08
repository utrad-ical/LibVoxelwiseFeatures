
#ifndef DIVIDED_CALCULATING_VOXELS__H



#include "VOL.h"
#include "CalculatingVoxels.h"


typedef struct DIVIDED_CALCULATING_VOXELS
{
	int ndiv;
//	VOL_INTSIZE3D* volsize;
	CALCULATINGVOXELS** set;
}
DIVIDEDCALCULATINGVOXELS;


// DIVIDEDCALCULATINGVOXELS* NewDividedCalculatingVoxels(VOL_RAWVOLUMEDATA* mask, int channel, int ndiv);

DIVIDEDCALCULATINGVOXELS* NewDividedCalculatingVoxels(CALCULATINGVOXELS* voxels, int ndiv);
DIVIDEDCALCULATINGVOXELS* NewDividedCalculatingVoxelsFromMask(VOL_RAWVOLUMEDATA* mask, int channel, int ndiv);

void DeleteDividedCalculatingVoxels(DIVIDEDCALCULATINGVOXELS* data);



#define DIVIDED_CALCULATING_VOXELS__H
#endif