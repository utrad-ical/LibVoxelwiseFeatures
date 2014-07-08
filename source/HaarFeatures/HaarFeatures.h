
#ifndef HAAR_FEATURES__H


#include "VOL.h"



#define NUM_HAAR_FEATURES	19

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////
////	float* haar_features = {
////			[ 0]=x����2����,			[ 1]=y����2����,			[ 2]=z����2����,
////			[ 3]=x����3����,			[ 4]=y����3����,			[ 5]=z����3����,
////			[ 6]=xy��2x2����,			[ 7]=yz��2x2����,			[ 8]=zx��2x2����,
////			[ 9]=xy����2����,			[10]=yz����2����,			[11]=zx����2����,
////			[12]=x(-y)����2����,		[13]=y(-z)����2����,		[14]=z(-x)����2����,
////			[15]=xyz��������,			[16]=(-x)yz��������,		[17]=x(-y)z��������,		[18]=xy(-z)��������		}
////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



float CalculateSingleHaarFeature(
	VOL_RAWVOLUMEDATA* volume, int channel, VOL_INTVECTOR3D* coord, VOL_KERNEL* roi, int index);

float* CalculateMultiHaarFeatures(
	VOL_RAWVOLUMEDATA* volume, int channel, VOL_INTVECTOR3D* coord, VOL_KERNEL* roi);


VOL_RAWVOLUMEDATA* GetVolumeOfSingleHaarFeature(
	VOL_RAWVOLUMEDATA* volume, int vChannel, VOL_RAWVOLUMEDATA* mask, int mChannel, VOL_KERNEL* roi, int index);

VOL_RAWVOLUMEDATA* GetVolumeOfMultiHaarFeatures(
	VOL_RAWVOLUMEDATA* volume, int vChannel, VOL_RAWVOLUMEDATA* mask, int mChannel, VOL_KERNEL* roi);


VOL_RAWVOLUMEDATA* GetVolumeOfSingleHaarFeature_MT(
	VOL_RAWVOLUMEDATA* volume, int vChannel, VOL_RAWVOLUMEDATA* mask, int mChannel, VOL_KERNEL* roi, int index, int numThreads);

VOL_RAWVOLUMEDATA* GetVolumeOfMultiHaarFeatures_MT(
	VOL_RAWVOLUMEDATA* volume, int vChannel, VOL_RAWVOLUMEDATA* mask, int mChannel, VOL_KERNEL* roi, int numThreads);



#define HAAR_FEATURES__H
#endif