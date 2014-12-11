
#pragma warning(disable: 4996)


#include "cstring"
#include "Sift3D.h"


SIFT_3D_FEATURES* NewSift3dFeatures(int n_sample, int n_feats)
{
	SIFT_3D_FEATURES* data = new SIFT_3D_FEATURES;
	data->feat_array = new float* [n_sample];
	data->feat_array[0] = new float [n_sample*n_feats];
	memset(data->feat_array[0], 0x00, sizeof(float)*n_sample*n_feats);
	for(int i=0; i<n_sample; i++)	data->feat_array[i] = data->feat_array[0]+i*n_feats;
	data->n_feats = n_feats;
	data->n_sample = n_sample;
	return data;
}

