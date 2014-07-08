
#ifndef CALCULATING_VOXELS__H


#include "VOL.h"


typedef struct CALCULATING_VOXELS
{
	int num;
	int* rp;	// raster_positions

//	VOL_INTSIZE3D* volsize;
	int* xc;	// x_coordinates
	int* yc;	// y_coordinates
	int* zc;	// z_coordinates
}
CALCULATINGVOXELS;


//CALCULATINGVOXELS* NewCalculatingVoxels(VOL_RAWVOLUMEDATA* mask, int channel);
CALCULATINGVOXELS* NewCalculatingVoxels(int num);
void DeleteCalculatingVoxels(CALCULATINGVOXELS* data);
CALCULATINGVOXELS* DuplicateCalculatingVoxels(CALCULATINGVOXELS* data);

/*
int ConvertPositions1DTo3DCalculatingVoxels(CALCULATINGVOXELS* data);
int ConvertPositions3DTo1DCalculatingVoxels(CALCULATINGVOXELS* data);
*/

#define CALCULATING_VOXELS__H
#endif



