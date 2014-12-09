

#include "pthread.h"
#include "CurvatureFeatures.h"

#include "../Utilities/CalculatingVoxels.h"
#include "../Utilities/DividedCalculatingVoxels.h"
//#include "../Utilities/SetIntRadInVolKernel.h"


#define OFFSET_XYZ	2


//int SetIntRadInVolKernel(VOL_KERNEL* kernel);
float* CalculateCurvatureFeatures(VOL_RAWVOLUMEDATA* input, int ch, VOL_INTVECTOR3D* coord);


void MemorySetOfCurvatureFeatures(
	VOL_RAWVOLUMEDATA* input, int ch, CALCULATINGVOXELS* subset, float** features)
{
	VOL_INTVECTOR3D coord;
	
	for(int i=0; i<subset->num; i++) {
		
		coord.x = subset->xc[i]+OFFSET_XYZ;
		coord.y = subset->yc[i]+OFFSET_XYZ;
		coord.z = subset->zc[i]+OFFSET_XYZ;

		float* temp = CalculateCurvatureFeatures(input, ch, &coord);

		for(int x=0; x<NUM_CURVATURE_FEATURES; x++)		features[i][x] = temp[x];

		delete [] temp;
	}
	return;
}


typedef struct THREADING_CURVATURE_FEATURES
{
	VOL_RAWVOLUMEDATA* input;
	int ch;
//	VOL_RAWVOLUMEDATA* output;
	CALCULATINGVOXELS* subset;
	float** features;
}
THREADING_CURVATUREFEATURES;

void* threaded_CalculateCurvatureFeatures(void* args)
{
	THREADING_CURVATUREFEATURES* a = (THREADING_CURVATUREFEATURES*)args;

	MemorySetOfCurvatureFeatures(a->input, a->ch, a->subset, a->features);

	return NULL;
}


float** CalculateCurvatureFeaturesAtMultiPositions_MT(
	VOL_RAWVOLUMEDATA* volume, int channel, CALCULATINGVOXELS* subset, int nthreads)
{

	float** output = new float* [subset->num];
	output[0] = new float [subset->num*NUM_CURVATURE_FEATURES];
	for(int i=0; i<subset->num; i++) {
		output[i] = output[0]+i*NUM_CURVATURE_FEATURES;
	}

	VOL_RAWVOLUMEDATA* vtemp = VOL_ExtractSingleChannelRawVolumeData(volume, channel);
	VOL_AttachOffsetXYZ(vtemp, OFFSET_XYZ, VOL_RESIZE_BACKGROUNDTYPE_BORDERCOPY_UNIFORM);

	VOL_ConvertVoxelUnit(vtemp, 0, VOL_VALUEUNIT_FLOAT32, NULL, NULL, VOL_CONVERTUNIT_TYPE_DIRECT);

	DIVIDEDCALCULATINGVOXELS* divs = NewDividedCalculatingVoxels(subset, nthreads);

	THREADING_CURVATUREFEATURES** t_args = new THREADING_CURVATUREFEATURES* [nthreads];
	int idxTop = 0;
	for(int t=0; t<nthreads; t++) {
		t_args[t] = new THREADING_CURVATUREFEATURES;
		t_args[t]->input = vtemp;	// volume;
		t_args[t]->ch = 0;			// channel;
		t_args[t]->features = output+idxTop;
		t_args[t]->subset = divs->set[t];
		idxTop += divs->set[t]->num;
	}
	
	pthread_t* threads = new pthread_t [nthreads];

	for(int t=0; t<nthreads; t++) {
		pthread_create(&threads[t], NULL, threaded_CalculateCurvatureFeatures, (void*)t_args[t]);
	}

	for(int t=0; t<nthreads; t++) {
		pthread_join(threads[t], NULL);
	}


	for(int t=0; t<nthreads; t++) {
		delete t_args[t];
	}
	delete [] t_args;
	delete [] threads;

	VOL_DeleteRawVolumeData(vtemp);
	DeleteDividedCalculatingVoxels(divs);


	return output;
}

