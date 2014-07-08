

#pragma warning(disable: 4996)

#include "pthread.h"
#include "VOL.h"
#include "VoxelValueStatistics.h"
#include "VoxelValueStatistics.private.h"


//void CalculateStatistics_SubsetOfVoxels(
//	VOL_RAWVOLUMEDATA* input, int ch, VOL_RAWVOLUMEDATA* output, CALCULATINGVOXELS* subset, VOL_KERNEL* kernel)

typedef struct THREADING_STATISTICS_VOLUME
{
	VOL_RAWVOLUMEDATA* input;
	int ch;
	VOL_RAWVOLUMEDATA* output;
	CALCULATINGVOXELS* subset;
	VOL_KERNEL* kernel;
}
THREADING_STATISTICSVOLUME;


void* threaded_GetVolumeOfVoxelValueStatistics(void* args)
{
	THREADING_STATISTICSVOLUME* a = (THREADING_STATISTICSVOLUME*)args;

	SetCalculatedStatisticsAsVoxelValue(a->input, a->ch, a->output, a->subset, a->kernel);

	return NULL;
}


VOL_RAWVOLUMEDATA* GetVolumeOfVoxelValueStatistics_MT(
	VOL_RAWVOLUMEDATA* volume, int vChannel, VOL_RAWVOLUMEDATA* mask, int mChannel, VOL_KERNEL* roi, int numThreads)
{
	VOL_INTSIZE3D* size = VOL_GetIntSize3DFromIntSize4D(volume->matrixSize);

	VOL_RAWVOLUMEDATA* output = VOL_NewSingleChannelRawVolumeData(size, VOL_VALUEUNIT_FLOAT32, VOL_VALUETYPE_SINGLE);
	for(int i=1; i<NUM_VOXEL_VALUE_STATISTICS; i++) {
		VOL_AddNewChannelInRawVolumeData(output, VOL_VALUEUNIT_FLOAT32, VOL_VALUETYPE_SINGLE);
	}
//	printf("a,");
	
	DIVIDEDCALCULATINGVOXELS* divs = NewDividedCalculatingVoxelsFromMask(mask, mChannel, numThreads);
//	printf("b,");

	int margin = SetIntRadInVolKernel(roi);
	VOL_AttachOffsetXYZ(volume, margin, VOL_RESIZE_BACKGROUNDTYPE_BORDERCOPY_UNIFORM);
//	printf("c,");

	THREADING_STATISTICSVOLUME** t_args = new THREADING_STATISTICSVOLUME* [numThreads];
	for(int t=0; t<numThreads; t++) {
		t_args[t] = new THREADING_STATISTICSVOLUME;
		t_args[t]->ch = vChannel;
		t_args[t]->input = volume;
		t_args[t]->kernel = roi;
		t_args[t]->output = output;
		t_args[t]->subset = divs->set[t];
	}
//	printf("d,");
	
	pthread_t* threads = new pthread_t [numThreads];

	for(int t=0; t<numThreads; t++) {
		pthread_create(&threads[t], NULL, threaded_GetVolumeOfVoxelValueStatistics, (void*)t_args[t]);
	}

	for(int t=0; t<numThreads; t++) {
		pthread_join(threads[t], NULL);
	}

	for(int t=0; t<numThreads; t++) {
		delete t_args[t];
	}
	delete [] t_args;
	delete [] threads;
//	printf("e,");

	VOL_RemoveOffsetXYZ(volume, margin);
//	printf("f,");

	VOL_DeleteIntSize3D(size);
	DeleteDividedCalculatingVoxels(divs);
//	DeleteCalculatingVoxels(subset);
//	printf("g\n");

	return output;
}

	
	




