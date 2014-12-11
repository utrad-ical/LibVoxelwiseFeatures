

#include "pthread.h"
#include "Hu3DMomentInvariants.h"
#include "../Utilities/DividedCalculatingVoxels.h"


// in Hu3DMomentInvariantsVolume.h
//void regional_Hu3DMomentInvariantsVolume(VOL_RAWVOLUMEDATA* input, int ich, VOL_KERNEL* kernel, VOL_INTBOX3D* box, 
//										 VOL_RAWVOLUMEDATA* output);

void regional_GetVolumeOfHu3DMomentInvariants(
	VOL_RAWVOLUMEDATA* input, int ich, VOL_KERNEL* kernel, CALCULATINGVOXELS* targets, VOL_RAWVOLUMEDATA* output)
{
//	float**** outvol = (float****)output->array4D;
	float*** vol_j1 = (float***)output->array4D[0];
	float*** vol_j2 = (float***)output->array4D[1];
	float*** vol_delta = (float***)output->array4D[2];
	float*** vol_i1 = (float***)output->array4D[3];
	float*** vol_i2 = (float***)output->array4D[4];

	VOL_INTVECTOR3D p;

	for(int i=0; i<targets->num; i++) {
		p.x = targets->xc[i];
		p.y = targets->yc[i];
		p.z = targets->zc[i];

		HU3DMOMENTINVARIANTS invs = CalculateHu3DMomentInvariants(input, ich, &p, kernel);

		vol_j1[p.z][p.y][p.x] = invs.J1;
		vol_j2[p.z][p.y][p.x] = invs.J2;
		vol_delta[p.z][p.y][p.x] = invs.delta;
		vol_i1[p.z][p.y][p.x] = invs.I1;
		vol_i2[p.z][p.y][p.x] = invs.I2;
	}

	return;
}


typedef struct _THREADING_VOLUME_HU_3D_MOMENT_INVARIANTS_
{
	VOL_RAWVOLUMEDATA* input;
	int ich;
	VOL_KERNEL* kernel;
//	VOL_INTBOX3D* box;
	CALCULATINGVOXELS* targets;
	VOL_RAWVOLUMEDATA* output;
}
THREADING_VOLUMEHU3DMOMENTINVARIANTS;


void* threaded_GetVolumeOfHu3DMomentInvariants(void* args)
{
	THREADING_VOLUMEHU3DMOMENTINVARIANTS* data = (THREADING_VOLUMEHU3DMOMENTINVARIANTS*)args;

	regional_GetVolumeOfHu3DMomentInvariants(data->input, data->ich, data->kernel, data->targets, data->output);

	return NULL;
}


VOL_RAWVOLUMEDATA* GetVolumeOfHu3DMomentInvariants_MT(
	VOL_RAWVOLUMEDATA* volume, int channel, VOL_RAWVOLUMEDATA* mask, int mch, VOL_KERNEL* roi, int nthreads)
{
	VOL_INTSIZE3D* sizeorg = VOL_GetIntSize3DFromIntSize4D(volume->matrixSize);

	int margin = 0;
	for(int i=0; i<roi->locationArray->nElements; i++) {
		if(margin<abs(roi->locationArray->x[i]))	margin = abs(roi->locationArray->x[i]);
		if(margin<abs(roi->locationArray->y[i]))	margin = abs(roi->locationArray->y[i]);
		if(margin<abs(roi->locationArray->z[i]))	margin = abs(roi->locationArray->z[i]);
	}

	VOL_AttachOffsetXYZ(volume, margin, VOL_RESIZE_BACKGROUNDTYPE_BORDERCOPY_UNIFORM);

	VOL_INTSIZE3D* attachedsz = VOL_GetIntSize3DFromIntSize4D(volume->matrixSize);

	VOL_RAWVOLUMEDATA* outvolume = VOL_NewSingleChannelRawVolumeData(attachedsz, VOL_VALUEUNIT_FLOAT32, VOL_VALUETYPE_SINGLE);
	for(int i=1; i<5; i++) {
		VOL_AddNewChannelInRawVolumeData(outvolume, VOL_VALUEUNIT_FLOAT32, VOL_VALUETYPE_SINGLE);
	}

//	VOL_INTVECTOR3D org;	org.x = org.y = org.z = margin;
//	VOL_INTBOX3D* box = VOL_NewIntBox3D(&org, sizeorg);
//	regional_HuMomentVolume(volume, channel, kernel, box, outvolume);

//	int* ztops = new int [nthreads+1];
//	for(int i=0; i<=nthreads; i++) {
//		ztops[i] = margin+(int)((double)i*(double)sizeorg->depth/(double)nthreads+0.5);
//	}

	DIVIDEDCALCULATINGVOXELS* divisions = NewDividedCalculatingVoxelsFromMask(mask, mch, nthreads);

	THREADING_VOLUMEHU3DMOMENTINVARIANTS** targs = new THREADING_VOLUMEHU3DMOMENTINVARIANTS* [nthreads];
	for(int i=0; i<nthreads; i++) {
		targs[i] = new THREADING_VOLUMEHU3DMOMENTINVARIANTS;

		targs[i]->ich = channel;
		targs[i]->input = volume;
		targs[i]->kernel = roi; 
		targs[i]->output = outvolume;

//		ConvertPositions1DTo3DCalculatingVoxels(divisions->set[i]);
		for(int j=0; j<divisions->set[i]->num; j++) {
			divisions->set[i]->xc[j] += margin;
			divisions->set[i]->yc[j] += margin;
			divisions->set[i]->zc[j] += margin;
		}
		
		targs[i]->targets = divisions->set[i];

	//	targs[i]->box = VOL_NewIntBox3D(&org, sizeorg);
	//	targs[i]->box->origin->z = ztops[i];
	//	targs[i]->box->size->depth = ztops[i+1]-ztops[i];
	}

	pthread_t* threads = new pthread_t [nthreads];

	for(int t=0; t<nthreads; t++) {
		pthread_create(&threads[t], NULL, threaded_GetVolumeOfHu3DMomentInvariants, (void*)targs[t]);
	}

	for(int t=0; t<nthreads; t++) {
		pthread_join(threads[t], NULL);
	}

	for(int t=0; t<nthreads; t++) {
		delete targs[t];
	}
	delete [] targs;
	delete [] threads;


	VOL_RemoveOffsetXYZ(volume, margin);
	VOL_RemoveOffsetXYZ(outvolume, margin);

//	VOL_DeleteIntBox3D(box);
	VOL_DeleteIntSize3D(sizeorg);
	VOL_DeleteIntSize3D(attachedsz);

	DeleteDividedCalculatingVoxels(divisions);
	
//	delete [] ztops;

	return outvolume;
}