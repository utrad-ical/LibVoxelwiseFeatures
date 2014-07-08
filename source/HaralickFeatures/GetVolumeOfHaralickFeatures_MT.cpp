

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


VOL_RAWVOLUMEDATA* GetVolumeOfHaralickFeatures_MT(
	VOL_RAWVOLUMEDATA* volume, int vChannel, VOL_RAWVOLUMEDATA* mask, int mChannel, 
	VOL_VALUERANGE* range, int numGradation, VOL_KERNEL* roi, VOL_KERNEL* references, int numThreads)
{
	VOL_INTSIZE3D* size = VOL_GetIntSize3DFromIntSize4D(volume->matrixSize);

	VOL_RAWVOLUMEDATA* output = VOL_NewSingleChannelRawVolumeData(size, VOL_VALUEUNIT_FLOAT32, VOL_VALUETYPE_SINGLE);
	for(int i=1; i<NUM_HARALICK_FEATURES; i++) {
		VOL_AddNewChannelInRawVolumeData(output, VOL_VALUEUNIT_FLOAT32, VOL_VALUETYPE_SINGLE);
	}

	VOLUMEHARALICKCALCULATION* volumeH;
	volumeH = NewVolumeHaralickCalculation(volume, vChannel, range, numGradation, roi, references);

//	CALCULATINGVOXELS* area = NewCalculatingVoxels(mask, mChannel);
//	ConvertPositions1DTo3DCalculatingVoxels(area);

	DIVIDEDCALCULATINGVOXELS* divs = NewDividedCalculatingVoxelsFromMask(mask, mChannel, numThreads);
//	for(int t=0; t<numThreads; t++) {
//		ConvertPositions1DTo3DCalculatingVoxels(divs->set[t]);
//	}

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