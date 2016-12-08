

#include "HaarFeaturesByIntegral.h"
#include "HaarFeaturesByIntegral.private.h"
#include "../Utilities/CheckRasterPositionedVoxelValuePresense.h"

#include "pthread.h"


typedef struct THREADING_ARRAY_HAAR_FEATURES
{
	INTEGRALVOLUME* integral;
	CALCULATINGVOXELS* subset;
	VOL_KERNEL* roi;
	int index;
	float** output;
}
THREADING_ARRAYHAARFEATURES;


void CalculateMultiHaarFeaturesAtVoxelsByIntegral(
	INTEGRALVOLUME* integral, CALCULATINGVOXELS* subset, VOL_KERNEL* kernel, float** output);


void* threaded_ArrayOfMultiHaarFeaturesByIntegral(void* args)
{
	THREADING_ARRAYHAARFEATURES* a = (THREADING_ARRAYHAARFEATURES*)args;

//	float**** features = (float****)a->output->array4D;
	CalculateMultiHaarFeaturesAtVoxelsByIntegral(a->integral, a->subset, a->roi, a->output);

	return NULL;
}


float** CalculateMultiHaarFeaturesAtMultiPositionsByIntegral_MT(
	void* intvolume, CALCULATINGVOXELS* voxels, VOL_KERNEL* roi, int numThreads)
{
	INTEGRALVOLUME* integral = (INTEGRALVOLUME*)intvolume;

	VOL_INTSIZE4D* sz_i = integral->volume->matrixSize;

	int numarea = voxels->num;
	int nthreads = numThreads;
	if(nthreads>numarea)	nthreads = numarea;

	float** output = new float* [numarea];
	output[0] = new float [numarea*NUM_HAAR_FEATURES];
	for(int j=0; j<numarea; j++) {
		output[j] = output[0]+j*NUM_HAAR_FEATURES;
	}

	DIVIDEDCALCULATINGVOXELS* divs = NewDividedCalculatingVoxels(voxels, nthreads);
	
	THREADING_ARRAYHAARFEATURES** t_args = new THREADING_ARRAYHAARFEATURES* [nthreads];
	int idxArray = 0;
	for(int t=0; t<nthreads; t++) {
		t_args[t] = new THREADING_ARRAYHAARFEATURES;
		t_args[t]->integral = integral;
		t_args[t]->subset = divs->set[t];
		t_args[t]->roi = roi;
	//	t_args[t]->index = index;
		t_args[t]->output = output+idxArray;
		idxArray += divs->set[t]->num;
	}

	pthread_t* threads = new pthread_t [nthreads];

	for(int t=0; t<nthreads; t++) {
		pthread_create(&threads[t], NULL, threaded_ArrayOfMultiHaarFeaturesByIntegral, (void*)t_args[t]);
	}

	for(int t=0; t<nthreads; t++) {
		pthread_join(threads[t], NULL);
	}

	for(int t=0; t<nthreads; t++) {
		delete t_args[t];
	}
	delete [] t_args;
	delete [] threads;

	DeleteDividedCalculatingVoxels(divs);
	
	return output;
}


