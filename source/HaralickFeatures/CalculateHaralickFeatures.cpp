

#include "VOL.h"
#include "HaralickFeatures.h"
#include "HaralickFeatures.private.h"



// 同時生起行列由来のテクスチャ特徴量計測
float* CalculateHaralickFeatures(
	VOLUMEHARALICKCALCULATION* volumeH, VOL_INTVECTOR3D* coord, VOL_KERNEL* roi, VOL_KERNEL* references)
{
	VOL_RAWVOLUMEDATA* volume = (VOL_RAWVOLUMEDATA*)volumeH->vol;
//	printf("a,");
 
	VOL_INTVECTOR3D ctemp;
	ctemp.x = coord->x + volumeH->margin;
	ctemp.y = coord->y + volumeH->margin;
	ctemp.z = coord->z + volumeH->margin;
//	printf("b_margin%d,", volumeH->margin);

	float* coMatrix1D = CalculateCoOccurrenceMatrix(volume, 0, volumeH->numGradation, &ctemp, roi, references);
//	printf("c,");

	float* features = CalculateHaralickFeaturesFromCoOccurenceMatrix(coMatrix1D, volumeH->numGradation);
//	printf("d,");

	delete [] coMatrix1D;
//	printf("ok\n");

	return features;
}