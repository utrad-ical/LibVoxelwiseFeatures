
#ifndef HAAR_FEATURES__H


#include "VOL.h"



#define NUM_HAAR_FEATURES	19

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////
////	float* haar_features = {
////			[ 0]=x•ûŒü2•ªŠ„,			[ 1]=y•ûŒü2•ªŠ„,			[ 2]=z•ûŒü2•ªŠ„,
////			[ 3]=x•ûŒü3•ªŠ„,			[ 4]=y•ûŒü3•ªŠ„,			[ 5]=z•ûŒü3•ªŠ„,
////			[ 6]=xy–Ê2x2•ªŠ„,			[ 7]=yz–Ê2x2•ªŠ„,			[ 8]=zx–Ê2x2•ªŠ„,
////			[ 9]=xy•ûŒü2•ªŠ„,			[10]=yz•ûŒü2•ªŠ„,			[11]=zx•ûŒü2•ªŠ„,
////			[12]=x(-y)•ûŒü2•ªŠ„,		[13]=y(-z)•ûŒü2•ªŠ„,		[14]=z(-x)•ûŒü2•ªŠ„,
////			[15]=xyz•ûŒü•ªŠ„,			[16]=(-x)yz•ûŒü•ªŠ„,		[17]=x(-y)z•ûŒü•ªŠ„,		[18]=xy(-z)•ûŒü•ªŠ„		}
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