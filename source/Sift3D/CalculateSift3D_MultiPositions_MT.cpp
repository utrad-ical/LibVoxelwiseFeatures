
#pragma warning(disable: 4996)

#include <cmath>
#include <vector>
#include "pthread.h"
#include "VOL.h"

#include "Sift3D.h"
#include "Sift3D.private.h"

#define DEBUG_PRINT 1

typedef struct _THREADING_CALCULATE_SIFT_3D_FEATS_ 
{
	VOL_RAWVOLUMEDATA* volume;
	CALCULATINGVOXELS* samples; 
	int ch_v, roi_size, num_roi_division, num_angle;
	int index_top, index_end;
	float** ary_angles;
	SIFT_3D_FEATURES* out;
}
THREADING_CALCULATE_SIFT_3D_FEATS;


void* threaded_CalculateSift3D_MultiPosition(void* args)
{
	THREADING_CALCULATE_SIFT_3D_FEATS* a = (THREADING_CALCULATE_SIFT_3D_FEATS*)args;

	int p_tmp[3];
	int num_feats = (int)pow((double)a->num_roi_division,3)*a->num_angle;

	for(int i=a->index_top; i<=a->index_end; i++) {
		p_tmp[0] = a->samples->xc[i];
		p_tmp[1] = a->samples->yc[i];
		p_tmp[2] = a->samples->zc[i];
	//	fprintf(stderr, "[%d](%d,%d,%d),", i,p_tmp[0],p_tmp[1],p_tmp[2]);
		float* f_tmp = CalculateSift3D_SinglePosition(a->volume, a->ch_v, p_tmp, a->roi_size, a->num_roi_division, a->num_angle, a->ary_angles);
		memcpy(a->out->feat_array[i], f_tmp, sizeof(float)*num_feats);
		delete [] f_tmp;
	}

	return NULL;
}


SIFT_3D_FEATURES* CalculateSift3D_MultiPositions_MT(
	VOL_RAWVOLUMEDATA* volume, int ch_v, CALCULATINGVOXELS* samples, 
	int roi_size, int num_roi_division, int num_angle, int num_threads)
{
	VOL_INTSIZE3D* size = VOL_GetIntSize3DFromIntSize4D(volume->matrixSize);
	int num_feats = num_roi_division*num_roi_division*num_roi_division*num_angle;

	fprintf(stderr, "a,");
	SIFT_3D_FEATURES* fout = NewSift3dFeatures(samples->num, num_feats);

	fprintf(stderr, "b,");
	BOUNDING_BOX box = BoundingBoxOfSamplePositions(samples);
	int volsz3d[3];
	volsz3d[0] = WID(volume);	volsz3d[1] = HEI(volume);	volsz3d[2] = DEP(volume);

	fprintf(stderr, "c,");
	int margin = 0;
	for(int c=0; c<3; c++) {
		box.top[c] -= roi_size/2;
		if(margin<-box.top[c])					margin = -box.top[c];
		box.tail[c] += roi_size/2;
		if(margin<box.tail[c]-volsz3d[c]+1)		margin = box.tail[c]-volsz3d[c]+1;
	}
	margin++;

	fprintf(stderr, "d,");
	VOL_RAWVOLUMEDATA* input_vol = VOL_ExtractSingleChannelRawVolumeData(volume, ch_v);
	
	if(margin>0) {
		fprintf(stderr, "margin_%d,", margin);
		VOL_AttachOffsetXYZ(input_vol, margin, VOL_RESIZE_BACKGROUNDTYPE_BORDERCOPY_UNIFORM);
		for(int i=0; i<samples->num; i++) {
			samples->xc[i] += margin;
			samples->yc[i] += margin;
			samples->zc[i] += margin;
		}
	}

	fprintf(stderr, "e,");
	float** ary_angles = GetEquallySpacedPointsOnUnitSphere(num_angle);
	// int p_tmp[3];
	double unit_size = (double)samples->num/(double)num_threads;
	
	THREADING_CALCULATE_SIFT_3D_FEATS** th_args = new THREADING_CALCULATE_SIFT_3D_FEATS* [num_threads];

	for(int t=0; t<num_threads; t++) {
		th_args[t] = new THREADING_CALCULATE_SIFT_3D_FEATS;
		th_args[t]->ch_v = 0; // ch_v;
		th_args[t]->num_angle = num_angle;
		th_args[t]->num_roi_division = num_roi_division;
		th_args[t]->roi_size = roi_size;
		th_args[t]->samples = samples;
		th_args[t]->volume = input_vol; // volume;
		th_args[t]->index_top = (int)(unit_size*(double)t+0.5);
		th_args[t]->index_end = (int)(unit_size*(double)(t+1)+0.5)-1;
		th_args[t]->ary_angles = ary_angles;
		th_args[t]->out = fout;
		fprintf(stderr, "[%d](%d~%d),", t,th_args[t]->index_top,th_args[t]->index_end);
	}

	fprintf(stderr, "pthread,");
	pthread_t* pthread = new pthread_t [num_threads];

	for(int t=0; t<num_threads; t++) {
		pthread_create(&pthread[t], NULL, threaded_CalculateSift3D_MultiPosition, (void*)th_args[t]);
	}

	for(int t=0; t<num_threads; t++) {
		pthread_join(pthread[t], NULL);
	}

	fprintf(stderr, "end,");
	for(int t=0; t<num_threads; t++)	delete th_args[t];
	delete [] th_args;
	delete [] pthread;

	/*
	for(int i=0; i<samples->num; i++) {
		p_tmp[0] = samples->xc[i];
		p_tmp[1] = samples->yc[i];
		p_tmp[2] = samples->zc[i];
		float* f_tmp = CalculateSift3D_SinglePosition(input_vol, 0, p_tmp, roi_size, num_roi_division, num_angle, ary_angles);
		memcpy(fout->feat_array[i], f_tmp, sizeof(float)*num_feats);
		delete [] f_tmp;
	}
	*/
	
	fprintf(stderr, "del,");
	VOL_DeleteRawVolumeData(input_vol);

	if(margin>0) for(int i=0; i<samples->num; i++) {
		samples->xc[i] -= margin;
		samples->yc[i] -= margin;
		samples->zc[i] -= margin;
	}

	delete [] ary_angles[0];
	delete [] ary_angles;
	fprintf(stderr, "ok\n");

	return fout;
}

