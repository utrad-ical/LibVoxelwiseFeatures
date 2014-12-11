
#ifndef _SIFT_3D_H_


#include "VOL.h"


#define NUM_SIFT_FEAT_ANGLES__FOUR		4
#define NUM_SIFT_FEAT_ANGLES__SIX		6
#define NUM_SIFT_FEAT_ANGLES__EIGHT		8
#define NUM_SIFT_FEAT_ANGLES__TEN		10
#define NUM_SIFT_FEAT_ANGLES__TWELVE	12
#define NUM_SIFT_AFEAT_NGLES__TWENTY	20


float* CalculateSift3D_SinglePosition(
	VOL_RAWVOLUMEDATA* volume, int ch, int* p,
	int roi_size, int num_roi_division, int num_angle, float** base_angles);


typedef struct _Sift3d_features_ {
	int n_feats, n_sample;
	float** feat_array;
} SIFT3D_FEATURES;

SIFT3D_FEATURES* NewSift3dFeatures(int n_sample, int n_feats);

void DeleteSift3dFeatures(SIFT3D_FEATURES* data);

SIFT3D_FEATURES* CalculateSift3D_MultiPositions(
	VOL_RAWVOLUMEDATA* volume, int ch_v, int num_sample, int** sample_positions, 
	int roi_size, int num_roi_division, int num_angle);





#define _SIFT_3D_H_
#endif _SIFT_3D_H_