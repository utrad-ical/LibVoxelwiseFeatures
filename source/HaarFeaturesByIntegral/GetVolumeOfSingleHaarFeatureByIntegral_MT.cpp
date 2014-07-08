
#include "pthread.h"

#include "HaarFeaturesByIntegral.h"
#include "HaarFeaturesByIntegral.private.h"


void* threaded_GetVolumeOfSingleHaarFeatureByIntegral(void* args)
{
	THREADING_VOLUMEHAARFEATURES* a = (THREADING_VOLUMEHAARFEATURES*)args;

	float*** feature = (float***)a->output->array4D[0];

	CalculateSingleHaarFeatureByIntegral_forVoxelSubset(a->integral, a->subset, a->roi, a->index, feature);

	return NULL;
}


VOL_RAWVOLUMEDATA* GetVolumeOfSingleHaarFeatureByIntegral_MT(VOL_RAWVOLUMEDATA* input, int ich, VOL_RAWVOLUMEDATA* mask, int mch, VOL_KERNEL* roi, int index, int numThreads)
{
	VOL_INTSIZE3D* size3d = VOL_GetIntSize3DFromIntSize4D(input->matrixSize);

	INTEGRALVOLUME* integral = NewInitializedIntegralVolume(input, ich);
	
	int offsetXYZ = SetIntRadInVolKernel(roi);
	VOL_AttachOffsetXYZ(integral->volume, offsetXYZ, VOL_RESIZE_BACKGROUNDTYPE_BORDERCOPY_UNIFORM);
	SetIntegralVolume(integral);

	VOL_RAWVOLUMEDATA* output = VOL_NewSingleChannelRawVolumeData(size3d, VOL_VALUEUNIT_FLOAT32, VOL_VALUETYPE_SINGLE);

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
		t_args[t]->index = index;
		t_args[t]->output = output;
	}

	pthread_t* threads = new pthread_t [numThreads];

	for(int t=0; t<numThreads; t++) {
		pthread_create(&threads[t], NULL, threaded_GetVolumeOfSingleHaarFeatureByIntegral, (void*)t_args[t]);
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
	DeleteIntegralVolume(integral);
	DeleteDividedCalculatingVoxels(divs);
	
//	DeleteCalculatingVoxels(subset);
//	VOL_RemoveOffsetXYZ(input, offsetXYZ);

	return output;
}


/*
#include "../Utilities/CalculatingVoxels.h"
#include "../Utilities/DividedCalculatingVoxels.h"
//#include "../Utilities/Check3DPositionedVoxelValuePresense.h"
#include "../Utilities/IntegralVolume.h"
#include "../Utilities/SumIntensityOfVoxelsInIntBoxByIntegral.h"

//float CalculateSigngleHaarFeatureByIntegralVolume(VOL_RAWVOLUMEDATA* volume, int chIntegral, VOL_INTBOX3D* box, int maskType);


void RegionalCalculation_SingleHaarFeatureInCubeByIntegral(
	INTEGRALVOLUME* integral, CALCULATINGVOXELS* obj, int cubeSize, int index, VOL_RAWVOLUMEDATA* output)
{
	int xye = output->matrixSize->height*output->matrixSize->width;
	int xe = output->matrixSize->width;

	float*** feature = (float***)output->array4D[0];

	VOL_INTVECTOR3D p3d;
	VOL_INTSIZE3D roisz;	roisz.width = roisz.height = roisz.depth = cubeSize;
	VOL_INTBOX3D* cbox = VOL_NewIntBox3D(&p3d, &roisz);

	for(int i=0; i<obj->num; i++) {
		cbox->origin->x = obj->xc[i];
		cbox->origin->y = obj->yc[i];
		cbox->origin->z = obj->zc[i];
		feature[cbox->origin->z][cbox->origin->y][cbox->origin->x] = CalculateSigngleHaarFeatureByIntegralVolume(integral, cbox, index);
	}

	VOL_DeleteIntBox3D(cbox);

	return;
}


VOL_RAWVOLUMEDATA* VolumeOfSingleHaarFeatureInCubeByIntegral_MT(
	VOL_RAWVOLUMEDATA* input, int ich, VOL_RAWVOLUMEDATA* mask, int mch, int cubeSize, int index, int numThreads)
{
//	INTEGRALVOLUME* integral = GetIntegralVolume(input, ich);
	INTEGRALVOLUME* integral = NewInitializedIntegralVolume(input, ich);

	VOL_INTSIZE3D* size3d = VOL_GetIntSize3DFromIntSize4D(input->matrixSize);
	VOL_RAWVOLUMEDATA* output = VOL_NewSingleChannelRawVolumeData(size3d, VOL_VALUEUNIT_FLOAT32, VOL_VALUETYPE_SINGLE);
	

	int offsetXYZ = (int)((double)cubeSize/2.0+0.5);
	VOL_AttachOffsetXYZ(integral->volume, offsetXYZ, VOL_RESIZE_BACKGROUNDTYPE_BORDERCOPY_UNIFORM);
	SetIntegralVolume(integral);


	DIVIDEDCALCULATINGVOXELS* divisions = NewDividedCalculatingVoxels(mask, mch, numThreads);


	THREADING_CALCHAARFEATURESCUBE** targs = new THREADING_CALCHAARFEATURESCUBE* [numThreads];

	for(int i=0; i<numThreads; i++) {
		targs[i] = new THREADING_CALCHAARFEATURESCUBE;
		targs[i]->integral = integral;
	//	targs[i]->input = integral->volume;
	//	targs[i]->ich = 0;
		targs[i]->cubeSize = cubeSize;
		targs[i]->index = index;
		targs[i]->output = output;
		
		ConvertPositions1DTo3DCalculatingVoxels(divisions->set[i]);

		targs[i]->obj = divisions->set[i];
	//	for(int j=0; j<targs[i]->obj->num; j++) {
	//		targs[i]->obj->xc[j] += offsetXYZ;
	//		targs[i]->obj->yc[j] += offsetXYZ;
	//		targs[i]->obj->zc[j] += offsetXYZ;
	//	}
	}


	pthread_t* threads = new pthread_t [numThreads];

	for(int t=0; t<numThreads; t++) {
		pthread_create(&threads[t], NULL, threaded_VolumeOfSingleHaarFeatureInCubeByIntegral, (void*)targs[t]);
	}

	for(int t=0; t<numThreads; t++) {
		pthread_join(threads[t], NULL);
	}

	for(int t=0; t<numThreads; t++) {
		delete targs[t];
	}
	delete [] targs;
	delete [] threads;


	DeleteIntegralVolume(integral);
	VOL_DeleteIntSize3D(size3d);
	VOL_RemoveOffsetXYZ(input, offsetXYZ);
	DeleteDividedCalculatingVoxels(divisions);


	return output;
}
*/

