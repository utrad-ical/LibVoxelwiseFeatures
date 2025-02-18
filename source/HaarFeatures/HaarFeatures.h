
#ifndef HAAR_FEATURES__H


#include "VOL.h"



#define NUM_HAAR_FEATURES	19

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////
////	float* haar_features = {
////			[ 0]=x方向2分割,			[ 1]=y方向2分割,			[ 2]=z方向2分割,
////			[ 3]=x方向3分割,			[ 4]=y方向3分割,			[ 5]=z方向3分割,
////			[ 6]=xy面2x2分割,			[ 7]=yz面2x2分割,			[ 8]=zx面2x2分割,
////			[ 9]=xy方向2分割,			[10]=yz方向2分割,			[11]=zx方向2分割,
////			[12]=x(-y)方向2分割,		[13]=y(-z)方向2分割,		[14]=z(-x)方向2分割,
////			[15]=xyz方向分割,			[16]=(-x)yz方向分割,		[17]=x(-y)z方向分割,		[18]=xy(-z)方向分割		}
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