

#include "pthread.h"
#include "VOL.h"
#include "HaralickFeatures.h"
#include "HaralickFeatures.private.h"



typedef struct THREADING_HARALICK_VOLUME
{
	VOL_RAWVOLUMEDATA* output;
	VOLUMEHARALICKCALCULATION* volumeH;
	CALCULATINGVOXELS* subset;
	VOL_KERNEL* roi;
	VOL_KERNEL* references;
}
THREADING_HARALICKVOLUME;


void* threaded_GetVolumeOfHaralickFeatures(void* args)
{
	THREADING_HARALICKVOLUME* a = (THREADING_HARALICKVOLUME*)args;

	CalculateHaralickFeatures_SubsetOfVoxels(a->output, a->volumeH, a->subset, a->roi, a->references);

	return NULL;
}

/*
template <class C>
void t_SetValueForVolMargins(C*** vol, int xe, int ye, int ze, int margin, C value)
{
	for(int k=0; k<ze; k++) { for(int j=0; j<ye; j++) { for(int i=0; i<xe; i++) {
	if(k<margin || k>=ze-margin || j<margin || j>=ye-margin || i<margin || i>=xe-margin ) { 
		vol[k][j][i] = value;
	}}}}
	return;
}

void SetValueForVolumeMarginVoxels(VOL_RAWVOLUMEDATA* vol, int ch, int margin, int value)
{
	int xe=vol->matrixSize->width, ye=vol->matrixSize->height, ze=vol->matrixSize->depth;
	if(vol->voxelUnit[ch]==0) {
		t_SetValueForVolMargins((unsigned char***)vol->array4D[ch], xe, ye, ze, margin, (unsigned char)value);
	} else if(vol->voxelUnit[ch]==1) {
		t_SetValueForVolMargins((char***)vol->array4D[ch], xe, ye, ze, margin, (char)value);
	} else if(vol->voxelUnit[ch]==2) {
		t_SetValueForVolMargins((unsigned short***)vol->array4D[ch], xe, ye, ze, margin, (unsigned short)value);
	} else if(vol->voxelUnit[ch]==3) {
		t_SetValueForVolMargins((short***)vol->array4D[ch], xe, ye, ze, margin, (short)value);
	}
	return;
}
*/


VOL_RAWVOLUMEDATA* GetVolumeOfHaralickFeatures_MT(
	VOL_RAWVOLUMEDATA* volume, int vChannel, VOL_RAWVOLUMEDATA* mask, int mChannel, 
	VOL_VALUERANGE* range, int numGradation, VOL_KERNEL* roi, VOL_KERNEL* references, int numThreads)
{
	int margin = SetIntRadInVolKernel(roi);
	margin += SetIntRadInVolKernel(references);

//	VOL_RAWVOLUMEDATA* vtmp = VOL_ExtractSingleChannelRawVolumeData(volume, vChannel);
//	VOL_AddNewChannelOfRawVolumeData(vtmp, mask, mChannel);
//	VOL_AttachOffsetXYZ(vtmp, margin, VOL_RESIZE_BACKGROUNDTYPE_BORDERCOPY_UNIFORM);
//	SetValueForVolumeMarginVoxels(vtmp, 1, margin, 0);

	VOL_INTSIZE3D* size = VOL_GetIntSize3DFromIntSize4D(volume->matrixSize);

	VOL_RAWVOLUMEDATA* output = VOL_NewSingleChannelRawVolumeData(size, VOL_VALUEUNIT_FLOAT32, VOL_VALUETYPE_SINGLE);
	for(int i=1; i<NUM_HARALICK_FEATURES; i++) {
		VOL_AddNewChannelInRawVolumeData(output, VOL_VALUEUNIT_FLOAT32, VOL_VALUETYPE_SINGLE);
	}

	VOLUMEHARALICKCALCULATION* volumeH;
	volumeH = NewVolumeHaralickCalculation(volume, vChannel, range, numGradation, roi, references);
	VOL_INTSIZE4D* tsz = ((VOL_RAWVOLUMEDATA*)volumeH->vol)->matrixSize;
	printf("margin_h=%d,sz(%d,%d,%d),",volumeH->margin,tsz->width,tsz->height,tsz->depth);

	DIVIDEDCALCULATINGVOXELS* divs = NewDividedCalculatingVoxelsFromMask(mask, mChannel, numThreads);

	THREADING_HARALICKVOLUME** t_args = new THREADING_HARALICKVOLUME* [numThreads];
	for(int t=0; t<numThreads; t++) {
		t_args[t] = new THREADING_HARALICKVOLUME;
		t_args[t]->output = output;
		t_args[t]->references = references;
		t_args[t]->roi = roi;
		t_args[t]->subset = divs->set[t];
		t_args[t]->volumeH = volumeH;
	}

	pthread_t* threads = new pthread_t [numThreads];

	for(int t=0; t<numThreads; t++) {
		pthread_create(&threads[t], NULL, threaded_GetVolumeOfHaralickFeatures, (void*)t_args[t]);
	}

	for(int t=0; t<numThreads; t++) {
		pthread_join(threads[t], NULL);
	}

	for(int t=0; t<numThreads; t++) {
		delete t_args[t];
	}
	delete [] t_args;
	delete [] threads;
	
	VOL_DeleteIntSize3D(size);
	DeleteVolumeHaralickCalculation(volumeH);
	DeleteDividedCalculatingVoxels(divs);

	return output;
}