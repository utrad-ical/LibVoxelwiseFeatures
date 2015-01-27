
#ifndef _SIFT_3D_H_


#include "VOL.h"
#include "../Utilities/ConvertMaskToCalculatingVoxels.h"


#define NUM_SIFT_ANGLES__FOUR		4
#define NUM_SIFT_ANGLES__SIX		6
#define NUM_SIFT_ANGLES__EIGHT		8
#define NUM_SIFT_ANGLES__TEN		10
#define NUM_SIFT_ANGLES__TWELVE		12
#define NUM_SIFT_ANGLES__TWENTY		20


float* CalculateSift3D_SinglePosition(
	VOL_RAWVOLUMEDATA* volume, int ch, int* p,
	int roi_size, int num_roi_division, int num_angle, float** base_angles);


typedef struct _Sift_3d_features_ {
	int n_feats, n_sample;
	float** feat_array;
} SIFT_3D_FEATURES;

SIFT_3D_FEATURES* NewSift3dFeatures(int n_sample, int n_feats);

void DeleteSift3dFeatures(SIFT_3D_FEATURES* data);

SIFT_3D_FEATURES* CalculateSift3D_MultiPositions(
	VOL_RAWVOLUMEDATA* volume, int ch_v, CALCULATINGVOXELS* samples,
	int roi_size, int num_roi_division, int num_angle);

SIFT_3D_FEATURES* CalculateSift3D_MultiPositions_MT(
	VOL_RAWVOLUMEDATA* volume, int ch_v, CALCULATINGVOXELS* samples, 
	int roi_size, int num_roi_division, int num_angle, int num_threads);


VOL_RAWVOLUMEDATA* VolumeOfSift3D(
	VOL_RAWVOLUMEDATA* volume, int vch, VOL_RAWVOLUMEDATA* mask, int mch, 
	int roi_size, int num_roi_division, int num_angle);


VOL_RAWVOLUMEDATA* VolumeOfSift3D_MT(
	VOL_RAWVOLUMEDATA* volume, int ch_v, VOL_RAWVOLUMEDATA* mask, int ch_m, 
	int roi_size, int num_roi_division, int num_angle, int num_threads);



#define _SIFT_3D_H_
#endif _SIFT_3D_H_