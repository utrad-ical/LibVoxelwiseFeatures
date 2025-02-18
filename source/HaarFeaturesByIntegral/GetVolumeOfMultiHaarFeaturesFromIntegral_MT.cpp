

#include "HaarFeaturesByIntegral.h"
#include "HaarFeaturesByIntegral.private.h"

#include "pthread.h"


void CalculateMultiHaarFeatureByIntegral_forVoxelSubset(
	INTEGRALVOLUME* integral, CALCULATINGVOXELS* subset, VOL_KERNEL* kernel, float**** output);


void* threaded_GetVolumeOfMultiHaarFeaturesFromIntegral(void* args)
{
	THREADING_VOLUMEHAARFEATURES* a = (THREADING_VOLUMEHAARFEATURES*)args;

//	float**** features = (float****)a->output->array4D;
	float**** features = new float*** [a->output->matrixSize->channel];
	for(int c=0; c<a->output->matrixSize->channel; c++)	features[c] = (float***)a->output->array4D[c];

	CalculateMultiHaarFeatureByIntegral_forVoxelSubset(a->integral, a->subset, a->roi, features);

	delete [] features;

	return NULL;
}


VOL_RAWVOLUMEDATA* GetVolumeOfMultiHaarFeaturesFromIntegral_MT(
	void* intvolume, VOL_RAWVOLUMEDATA* mask, int mch, VOL_KERNEL* roi, int numThreads)
{
	INTEGRALVOLUME* integral = (INTEGRALVOLUME*)intvolume;


	VOL_INTSIZE4D* sz_i = integral->volume->matrixSize;
	VOL_INTSIZE4D* sz_m = mask->matrixSize;

	int bError=3;
	if(sz_i->depth==sz_m->depth+roi->intRad*2)		bError--;
	if(sz_i->height==sz_m->height+roi->intRad*2)	bError--;
	if(sz_i->width==sz_m->width+roi->intRad*2)		bError--;

	if(bError>0) {
		fprintf(stderr, "volume size error!");
		return NULL;
	}

	VOL_INTSIZE3D* size3d = VOL_GetIntSize3DFromIntSize4D(mask->matrixSize);

//	INTEGRALVOLUME* integral = NewInitializedIntegralVolume(input, ich);
	
//	int offsetXYZ = SetIntRadInVolKernel(roi);
//	VOL_AttachOffsetXYZ(integral->volume, offsetXYZ, VOL_RESIZE_BACKGROUNDTYPE_BORDERCOPY_UNIFORM);
//	SetIntegralVolume(integral);

	VOL_RAWVOLUMEDATA* output = VOL_NewSingleChannelRawVolumeData(size3d, VOL_VALUEUNIT_FLOAT32, VOL_VALUETYPE_SINGLE);
	for(int idx=1; idx<NUM_HAAR_FEATURES; idx++) {
		VOL_DuplicateChannelOfRawVolumeData(output, 0);
	}

	DIVIDEDCALCULATINGVOXELS* divs = NewDividedCalculatingVoxelsFromMask(mask, mch, numThreads);
//	for(int t=0; t<numThreads; t++) {
//		ConvertPositions1DTo3DCalculatingVoxels(divs->set[t]);
//	}

	THREADING_VOLUMEHAARFEATURES** t_args = new THREADING_VOLUMEHAARFEATURES* [numThreads];
	for(int t=0; t<numThreads; t++) {
		t_args[t] = new THREADING_VOLUMEHAARFEATURES;
		t_args[t]->integral = integral;
		t_args[t]->subset = divs->set[t];
		t_args[t]->roi = roi;
	//	t_args[t]->index = index;
		t_args[t]->output = output;
	}

	pthread_t* threads = new pthread_t [numThreads];

	for(int t=0; t<numThreads; t++) {
		pthread_create(&threads[t], NULL, threaded_GetVolumeOfMultiHaarFeaturesFromIntegral, (void*)t_args[t]);
	}

	for(int t=0; t<numThreads; t++) {
		pthread_join(threads[t], NULL);
	}

	for(int t=0; t<numThreads; t++) {
		delete t_args[t];
	}
	delete [] t_args;
	delete [] threads;

//	CALCULATINGVOXELS* subset = NewCalculatingVoxels(mask, mch);
//	float*** feature = (float***)output->array4D[0];
//	CalculateSingleHaarFeatureByIntegral_forVoxelSubset(integral, subset, roi, index, feature);

	VOL_DeleteIntSize3D(size3d);
//	DeleteIntegralVolume(integral);
	DeleteDividedCalculatingVoxels(divs);
	
//	DeleteCalculatingVoxels(subset);
//	VOL_RemoveOffsetXYZ(input, offsetXYZ);

	return output;
}


