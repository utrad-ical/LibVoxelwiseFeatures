

#include "pthread.h"
#include "CurvatureFeatures.h"

#include "../Utilities/CalculatingVoxels.h"
#include "../Utilities/DividedCalculatingVoxels.h"
#include "../Utilities/SetIntRadInVolKernel.h"


void CalculateCurvatureFeatures_SubsetOfVoxels(
	VOL_RAWVOLUMEDATA* input, int ch, VOL_RAWVOLUMEDATA* output, CALCULATINGVOXELS* subset);


typedef struct THREADING_CURVATURES_VOLUME
{
	VOL_RAWVOLUMEDATA* input;
	int ch;
	VOL_RAWVOLUMEDATA* output;
	CALCULATINGVOXELS* subset;
}
THREADING_CURVATUREVOLUME;


void* threaded_GetVolumeOfCurvatureFeatures(void* args)
{
	THREADING_CURVATUREVOLUME* a = (THREADING_CURVATUREVOLUME*)args;

	CalculateCurvatureFeatures_SubsetOfVoxels(a->input, a->ch, a->output, a->subset);

	return NULL;
}


VOL_RAWVOLUMEDATA* GetVolumeOfCurvatureFeatures_MT(
	VOL_RAWVOLUMEDATA* volume, int vChannel, VOL_RAWVOLUMEDATA* mask, int mChannel, int numThreads)
{
	VOL_INTSIZE3D* size = VOL_GetIntSize3DFromIntSize4D(volume->matrixSize);
	printf("a,");

	VOL_RAWVOLUMEDATA* output = VOL_NewSingleChannelRawVolumeData(size, VOL_VALUEUNIT_FLOAT32, VOL_VALUETYPE_SINGLE);
	for(int i=1; i<NUM_CURVATURE_FEATURES; i++) {
		VOL_AddNewChannelInRawVolumeData(output, VOL_VALUEUNIT_FLOAT32, VOL_VALUETYPE_SINGLE);
	}
	printf("b,");

//	CALCULATINGVOXELS* subset = NewCalculatingVoxels(mask, mChannel);
	DIVIDEDCALCULATINGVOXELS* divs = NewDividedCalculatingVoxelsFromMask(mask, mChannel, numThreads);
	printf("c,");

//	CalculateCurvatureFeatures_SubsetOfVoxels(volume, vChannel, output, subset);
//	printf("e,");

	THREADING_CURVATUREVOLUME** t_args = new THREADING_CURVATUREVOLUME* [numThreads];
	for(int t=0; t<numThreads; t++) {
		t_args[t] = new THREADING_CURVATUREVOLUME;
		t_args[t]->ch = vChannel;
		t_args[t]->input = volume;
		t_args[t]->output = output;
		t_args[t]->subset = divs->set[t];
	}
	printf("d,");
	
	pthread_t* threads = new pthread_t [numThreads];

	for(int t=0; t<numThreads; t++) {
		pthread_create(&threads[t], NULL, threaded_GetVolumeOfCurvatureFeatures, (void*)t_args[t]);
	}

	for(int t=0; t<numThreads; t++) {
		pthread_join(threads[t], NULL);
	}

	for(int t=0; t<numThreads; t++) {
		delete t_args[t];
	}
	delete [] t_args;
	delete [] threads;
	printf("e,");

	VOL_DeleteIntSize3D(size);
//	DeleteCalculatingVoxels(subset);
	DeleteDividedCalculatingVoxels(divs);
	printf("f\n");

	return output;
}

