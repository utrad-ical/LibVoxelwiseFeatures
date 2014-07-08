

#include "pthread.h"

#include "HaarFeatures.h"
#include "HaarFeatures.private.h"

#include "../Utilities/CalculatingVoxels.h"
#include "../Utilities/Check3DPositionedVoxelValuePresense.h"
#include "../Utilities/DividedCalculatingVoxels.h"
#include "../Utilities/SetIntRadInVolKernel.h"


typedef struct THREADING_HAAR_FEATURE_VOLUME
{
	VOL_RAWVOLUMEDATA* input;
	int ch;
	CALCULATINGVOXELS* subset;
	VOL_KERNEL* kernel;
	int index;
	VOL_RAWVOLUMEDATA* output;
}
THREADING_HAARFEATUREVOLUME;

//void CalculateSingleHaarFeatureInRoiBoundingBox_VoxelSubset(
//	VOL_RAWVOLUMEDATA* input, int ch, CALCULATINGVOXELS* subset, VOL_KERNEL* kernel, int index, VOL_RAWVOLUMEDATA* output);

void* threaded_GetVolumeOfMultiHaarFeaturesInRoiBoundingBox(void* args)
{
	THREADING_HAARFEATUREVOLUME* a = (THREADING_HAARFEATUREVOLUME*)args;
	float**** featvol = (float****)a->output->array4D;
	for(int idx=0; idx<NUM_HAAR_FEATURES; idx++) {
		CalculateSingleHaarFeature_forVoxelSubset(a->input, a->ch, a->subset, a->kernel, idx, featvol[idx]);
	}
	return NULL;
}


VOL_RAWVOLUMEDATA* GetVolumeOfMultiHaarFeatures_MT(
	VOL_RAWVOLUMEDATA* volume, int vChannel, VOL_RAWVOLUMEDATA* mask, int mChannel, VOL_KERNEL* roi, int numThreads)
{
	VOL_INTSIZE3D* size3d = VOL_GetIntSize3DFromIntSize4D(volume->matrixSize);

	VOL_RAWVOLUMEDATA* output = VOL_NewSingleChannelRawVolumeData(size3d, VOL_VALUEUNIT_FLOAT32, VOL_VALUETYPE_SINGLE);
	for(int i=1; i<NUM_HAAR_FEATURES; i++) {
		VOL_DuplicateChannelOfRawVolumeData(output, 0);
	}

	int margin = SetIntRadInVolKernel(roi);
	VOL_AttachOffsetXYZ(volume, margin, VOL_RESIZE_BACKGROUNDTYPE_BORDERCOPY_UNIFORM);

	DIVIDEDCALCULATINGVOXELS* divs = NewDividedCalculatingVoxelsFromMask(mask, mChannel, numThreads);
//	for(int t=0; t<numThreads; t++) {
//		ConvertPositions1DTo3DCalculatingVoxels(divs->set[t]);
//	}

	THREADING_HAARFEATUREVOLUME** t_args = new THREADING_HAARFEATUREVOLUME* [numThreads];
	for(int t=0; t<numThreads; t++) {
		t_args[t] = new THREADING_HAARFEATUREVOLUME;
		t_args[t]->input = volume;
		t_args[t]->ch = vChannel;
		t_args[t]->subset = divs->set[t];
		t_args[t]->kernel = roi;
	//	t_args[t]->index = index;
		t_args[t]->output = output;
	}

	pthread_t* threads = new pthread_t [numThreads];

	for(int t=0; t<numThreads; t++) {
		pthread_create(&threads[t], NULL, threaded_GetVolumeOfMultiHaarFeaturesInRoiBoundingBox, (void*)t_args[t]);
	}

	for(int t=0; t<numThreads; t++) {
		pthread_join(threads[t], NULL);
	}

	for(int t=0; t<numThreads; t++) {
		delete t_args[t];
	}
	delete [] t_args;
	delete [] threads;

	VOL_DeleteIntSize3D(size3d);
	DeleteDividedCalculatingVoxels(divs);

	VOL_RemoveOffsetXYZ(volume, margin);

	return output;
}

