

#include "VoxelValueStatistics.h"
#include "VoxelValueStatistics.private.h"

#include "../Utilities/CalculatingVoxels.h"
#include "../Utilities/DividedCalculatingVoxels.h"

#include "pthread.h"


typedef struct THREADING_STATISTICS_VOXEL_VALUE
{
	VOL_RAWVOLUMEDATA* input;
	int ch;
	float** output;
	CALCULATINGVOXELS* subset;
	VOL_KERNEL* kernel;
}
THREADING_STATISTICSVOXELVALUE;


void MemorySetOfVoxelValueStatisticsAtMultiPositions(
	VOL_RAWVOLUMEDATA* input, int ch, CALCULATINGVOXELS* subset, VOL_KERNEL* kernel, float** output);

void* threaded_CalculateVoxelValueStatisticsAtMultiPositions(void* args)
{
	THREADING_STATISTICSVOXELVALUE* a = (THREADING_STATISTICSVOXELVALUE*)args;

	MemorySetOfVoxelValueStatisticsAtMultiPositions(a->input, a->ch, a->subset, a->kernel, a->output);

	return NULL;
}


float** CalculateVoxelValueStatisticsAtMultiPositions_MT(
	VOL_RAWVOLUMEDATA* input, int ch, CALCULATINGVOXELS* subset, VOL_KERNEL* roi, int numThreads)
{
	int nthreads = numThreads;
	if(nthreads>subset->num)	nthreads = subset->num;

	float** output = new float* [subset->num];
	output[0] = new float [subset->num*NUM_VOXEL_VALUE_STATISTICS];
	for(int i=0; i<subset->num; i++) {
		output[i] = output[0]+i*NUM_VOXEL_VALUE_STATISTICS;
	}

	VOL_RAWVOLUMEDATA* volume = VOL_ExtractSingleChannelRawVolumeData(input, ch);

	int offsetXYZ = SetIntRadInVolKernel(roi);
	VOL_AttachOffsetXYZ(volume, offsetXYZ, VOL_RESIZE_BACKGROUNDTYPE_BORDERCOPY_UNIFORM);

	CALCULATINGVOXELS* tempVoxels = DuplicateCalculatingVoxels(subset);
	for(int i=0; i<subset->num; i++) {
		tempVoxels->xc[i] = tempVoxels->xc[i]+offsetXYZ;
		tempVoxels->yc[i] = tempVoxels->yc[i]+offsetXYZ;
		tempVoxels->zc[i] = tempVoxels->zc[i]+offsetXYZ;
	}

	DIVIDEDCALCULATINGVOXELS* divs = NewDividedCalculatingVoxels(tempVoxels, nthreads);

	THREADING_STATISTICSVOXELVALUE** t_args = new THREADING_STATISTICSVOXELVALUE* [nthreads];
	int idxTop = 0;
	for(int t=0; t<nthreads; t++) {
		t_args[t] = new THREADING_STATISTICSVOXELVALUE;
		t_args[t]->input = volume;
		t_args[t]->ch = 0;
		t_args[t]->kernel = roi;
		t_args[t]->output = output+idxTop;
		t_args[t]->subset = divs->set[t];
		idxTop += divs->set[t]->num;
	}

	pthread_t* threads = new pthread_t [nthreads];

	for(int t=0; t<nthreads; t++) {
		pthread_create(&threads[t], NULL, threaded_CalculateVoxelValueStatisticsAtMultiPositions, (void*)t_args[t]);
	}

	for(int t=0; t<nthreads; t++) {
		pthread_join(threads[t], NULL);
	}

	for(int t=0; t<nthreads; t++) {
		delete t_args[t];
	}
	delete [] t_args;
	delete [] threads;
//	printf("e,");

//	VOL_RemoveOffsetXYZ(volume, offsetXYZ);

	VOL_DeleteRawVolumeData(volume);
	DeleteCalculatingVoxels(tempVoxels);
	DeleteDividedCalculatingVoxels(divs);

	return output;
}


