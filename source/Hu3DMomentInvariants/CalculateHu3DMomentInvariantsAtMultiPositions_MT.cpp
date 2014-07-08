

#include "pthread.h"
#include "Hu3DMomentInvariants.h"
#include "../Utilities/DividedCalculatingVoxels.h"


int SetIntRadInVolKernel(VOL_KERNEL* kernel);


void MemorySetOfHu3DMomentInvariantsAtMultiPositions(
	VOL_RAWVOLUMEDATA* input, int ich, VOL_KERNEL* kernel, CALCULATINGVOXELS* targets, float** output)
//	, VOL_RAWVOLUMEDATA* output)
{
//	float**** outvol = (float****)output->array4D;

	VOL_INTVECTOR3D p;

	for(int i=0; i<targets->num; i++) {

		p.x = targets->xc[i];
		p.y = targets->yc[i];
		p.z = targets->zc[i];

		HU3DMOMENTINVARIANTS invs = CalculateHu3DMomentInvariants(input, ich, &p, kernel);

		output[i][0] = invs.J1;
		output[i][1] = invs.J2;
		output[i][2] = invs.delta;
		output[i][3] = invs.I1;
		output[i][4] = invs.I2;

	//	outvol[0][p.z][p.y][p.x] = invs.J1;
	//	outvol[1][p.z][p.y][p.x] = invs.J2;
	//	outvol[2][p.z][p.y][p.x] = invs.delta;
	//	outvol[3][p.z][p.y][p.x] = invs.I1;
	//	outvol[4][p.z][p.y][p.x] = invs.I2;
	}

	return;
}


typedef struct _THREADING_HU_3D_MOMENT_INVARIANTS_
{
	VOL_RAWVOLUMEDATA* input;
	int ich;
	VOL_KERNEL* kernel;
//	VOL_INTBOX3D* box;
	CALCULATINGVOXELS* targets;
//	VOL_RAWVOLUMEDATA* output;
	float** features;
}
THREADING_HU3DMOMENTINVARIANTS;


void* threaded_CalculateHu3DMomentInvariants(void* args)
{
	THREADING_HU3DMOMENTINVARIANTS* data = (THREADING_HU3DMOMENTINVARIANTS*)args;

	MemorySetOfHu3DMomentInvariantsAtMultiPositions(data->input, data->ich, data->kernel, data->targets, data->features);

	return NULL;
}


float** CalculateHu3DMomentInvariantsAtMultiPositions_MT(
	VOL_RAWVOLUMEDATA* volume, int channel, CALCULATINGVOXELS* subset, VOL_KERNEL* roi, int numThreads)
{

	float** output = new float* [subset->num];
	output[0] = new float [subset->num*NUM_HU_3D_MOMENT_INVARIANTS];
	for(int i=0; i<subset->num; i++) {
		output[i] = output[0]+i*NUM_HU_3D_MOMENT_INVARIANTS;
	}


	int nthreads = numThreads;
	if(nthreads>subset->num)	nthreads = subset->num;

	VOL_RAWVOLUMEDATA* voltemp = VOL_ExtractSingleChannelRawVolumeData(volume, channel);

	int offsetXYZ = SetIntRadInVolKernel(roi);
	VOL_AttachOffsetXYZ(voltemp, offsetXYZ, VOL_RESIZE_BACKGROUNDTYPE_BORDERCOPY_UNIFORM);

	CALCULATINGVOXELS* tempVoxels = DuplicateCalculatingVoxels(subset);
	for(int i=0; i<subset->num; i++) {
		tempVoxels->xc[i] = tempVoxels->xc[i]+offsetXYZ;
		tempVoxels->yc[i] = tempVoxels->yc[i]+offsetXYZ;
		tempVoxels->zc[i] = tempVoxels->zc[i]+offsetXYZ;
	}


	DIVIDEDCALCULATINGVOXELS* divisions = NewDividedCalculatingVoxels(tempVoxels, nthreads);

	THREADING_HU3DMOMENTINVARIANTS** targs = new THREADING_HU3DMOMENTINVARIANTS* [nthreads];
	int idxTop = 0;
	for(int i=0; i<nthreads; i++) {
		targs[i] = new THREADING_HU3DMOMENTINVARIANTS;
		targs[i]->ich = 0;
		targs[i]->input = voltemp;
		targs[i]->kernel = roi; 
		targs[i]->targets = divisions->set[i];
		targs[i]->features = output+idxTop;
		idxTop += divisions->set[i]->num;
	}

	pthread_t* threads = new pthread_t [nthreads];

	for(int t=0; t<nthreads; t++) {
		pthread_create(&threads[t], NULL, threaded_CalculateHu3DMomentInvariants, (void*)targs[t]);
	}

	for(int t=0; t<nthreads; t++) {
		pthread_join(threads[t], NULL);
	}


	for(int t=0; t<nthreads; t++) {
		delete targs[t];
	}
	delete [] targs;
	delete [] threads;

	VOL_DeleteRawVolumeData(voltemp);
	DeleteCalculatingVoxels(tempVoxels);
	DeleteDividedCalculatingVoxels(divisions);


	return output;
}