
#pragma warning(disable: 4996)

#include <cmath>
#include <vector>
#include "VOL.h"

#include "Sift3D.h"





typedef struct _bouding_box_ {
	int top[3], tail[3];
} BOUNDING_BOX;

BOUNDING_BOX BoundingBoxOfSamplePositions(int num_sample, int** sample_positions)
{
	BOUNDING_BOX box;
	for(int c=0; c<3; c++)	box.top[c] = box.tail[c] = sample_positions[0][c];
	for(int i=0; i<num_sample; i++) for(int c=0; c<3; c++) {
		if(box.top[c]>sample_positions[i][c])	box.top[c] = sample_positions[i][c];
		if(box.tail[c]<sample_positions[i][c])	box.tail[c] = sample_positions[i][c];
	}
	return box;
}

#define DEP(v)	v->matrixSize->depth
#define HEI(v)	v->matrixSize->height
#define WID(v)	v->matrixSize->width



float** GetEquallySpacedPointsOnUnitSphere(int num)
{
	float** vectors = new float* [num];
	vectors[0] = new float [num*3];
	for(int i=0; i<num; i++)	vectors[i] = vectors[0]+i*3;

	switch(num) {
	case 4:
		vectors[ 0][0] = 1.0f;			vectors[ 0][1] = 1.0f;			vectors[ 0][2] = 1.0f;
		vectors[ 1][0] = 1.0f;			vectors[ 1][1] = -1.0f;			vectors[ 1][2] = -1.0f;
		vectors[ 2][0] = -1.0f;			vectors[ 2][1] = 1.0f;			vectors[ 2][2] = -1.0f;
		vectors[ 3][0] = -1.0f;			vectors[ 3][1] = -1.0f;			vectors[ 3][2] = 1.0f;
		break;
	case 6:
		vectors[ 0][0] = 1.0f;			vectors[ 0][1] = 0.0f;			vectors[ 0][2] = 0.0f;
		vectors[ 1][0] = -1.0f;			vectors[ 1][1] = 0.0f;			vectors[ 1][2] = 0.0f;
		vectors[ 2][0] = 0.0f;			vectors[ 2][1] = 1.0f;			vectors[ 2][2] = 0.0f;
		vectors[ 3][0] = 0.0f;			vectors[ 3][1] = -1.0f;			vectors[ 3][2] = 0.0f;
		vectors[ 4][0] = 0.0f;			vectors[ 4][1] = 0.0f;			vectors[ 4][2] = 1.0f;
		vectors[ 5][0] = 0.0f;			vectors[ 5][1] = 0.0f;			vectors[ 5][2] = -1.0f;
		break;
	case 8:
		vectors[ 0][0] = -1.0f;			vectors[ 0][1] = -1.0f;			vectors[ 0][2] = -1.0f;
		vectors[ 1][0] = -1.0f;			vectors[ 1][1] = -1.0f;			vectors[ 1][2] = 1.0f;
		vectors[ 2][0] = -1.0f;			vectors[ 2][1] = 1.0f;			vectors[ 2][2] = -1.0f;
		vectors[ 3][0] = -1.0f;			vectors[ 3][1] = 1.0f;			vectors[ 3][2] = 1.0f;
		vectors[ 4][0] = 1.0f;			vectors[ 4][1] = -1.0f;			vectors[ 4][2] = -1.0f;
		vectors[ 5][0] = 1.0f;			vectors[ 5][1] = -1.0f;			vectors[ 5][2] = 1.0f;
		vectors[ 6][0] = 1.0f;			vectors[ 6][1] = 1.0f;			vectors[ 6][2] = -1.0f;
		vectors[ 7][0] = 1.0f;			vectors[ 7][1] = 1.0f;			vectors[ 7][2] = 1.0f;
		break;
	case 10:
		vectors[ 0][0] = 1.0f;			vectors[ 0][1] = 0.0f;			vectors[ 0][2] = 0.0f;
		vectors[ 1][0] = 0.678f;		vectors[ 1][1] = 0.735f;		vectors[ 1][2] = 0.0f;
		vectors[ 2][0] = -0.556f;		vectors[ 2][1] = 0.504f;		vectors[ 2][2] = 0.661f;
		vectors[ 3][0] = 0.672f;		vectors[ 3][1] = -0.733f;		vectors[ 3][2] = 0.106f;
		vectors[ 4][0] = 0.012f;		vectors[ 4][1] = -0.801f;		vectors[ 4][2] = 0.598f;
		vectors[ 5][0] = -0.680f;		vectors[ 5][1] = -0.310f;		vectors[ 5][2] = 0.664f;
		vectors[ 6][0] = -0.045f;		vectors[ 6][1] = -0.011f;		vectors[ 6][2] = 0.999f;
		vectors[ 7][0] = 0.024f;		vectors[ 7][1] = 0.966f;		vectors[ 7][2] = 0.257f;
		vectors[ 8][0] = 0.458f;		vectors[ 8][1] = 0.521f;		vectors[ 8][2] = 0.721f;
		vectors[ 9][0] = 0.658f;		vectors[ 9][1] = -0.250f;		vectors[ 9][2] = 0.710f;
		break;
	case 12:
		vectors[ 0][0] = 0.0f;			vectors[ 0][1] = 0.0f;			vectors[ 0][2] = 1.90211f;
		vectors[ 1][0] = 1.7013f;		vectors[ 1][1] = 0.0f;			vectors[ 1][2] = 0.850651f;
		vectors[ 2][0] = 0.525731f;		vectors[ 2][1] = 1.61803f;		vectors[ 2][2] = 0.850651f;
		vectors[ 3][0] = -1.37638f;		vectors[ 3][1] = 1.0f;			vectors[ 3][2] = 0.850651f;
		vectors[ 4][0] = -1.37638f;		vectors[ 4][1] = -1.0f;			vectors[ 4][2] = 0.850651f;
		vectors[ 5][0] = 0.525731f;		vectors[ 5][1] = -1.61803f;		vectors[ 5][2] = 0.850651f;
		vectors[ 6][0] = 1.37638f;		vectors[ 6][1] = -1.0f;			vectors[ 6][2] = -0.850651f;
		vectors[ 7][0] = 1.37638f;		vectors[ 7][1] = 1.0f;			vectors[ 7][2] = -0.850651f;
		vectors[ 8][0] = -0.525731f;	vectors[ 8][1] = 1.61803f;		vectors[ 8][2] = -0.850651f;
		vectors[ 9][0] = -1.7013f;		vectors[ 9][1] = 0.0f;			vectors[ 9][2] = -0.850651f;
		vectors[10][0] = -0.525731f;	vectors[10][1] = -1.61803f;		vectors[10][2] = -0.850651f;
		vectors[11][0] = 0.0f;			vectors[11][1] = 0.0f;			vectors[11][2] = -1.90211f;
		break;
	case 20:
		vectors[ 0][0] = 1.7013f;		vectors[ 0][1] = 0.0f;			vectors[ 0][2] = 2.22703f;
		vectors[ 1][0] = 0.525731f;		vectors[ 1][1] = 1.61803f;		vectors[ 1][2] = 2.22703f;
		vectors[ 2][0] = -1.37638f;		vectors[ 2][1] = 1.0f;			vectors[ 2][2] = 2.22703f;
		vectors[ 3][0] = -1.37638f;		vectors[ 3][1] = -1.0f;			vectors[ 3][2] = 2.22703f;
		vectors[ 4][0] = 0.525731f;		vectors[ 4][1] = -1.61803f;		vectors[ 4][2] = 2.22703f;
		vectors[ 5][0] = 2.75276f;		vectors[ 5][1] = 0.0f;			vectors[ 5][2] = 0.525731f;
		vectors[ 6][0] = 0.850651f;		vectors[ 6][1] = 2.61803f;		vectors[ 6][2] = 0.525731f;
		vectors[ 7][0] = -2.22703f;		vectors[ 7][1] = 1.61803f;		vectors[ 7][2] = 0.525731f;
		vectors[ 8][0] = -2.22703f;		vectors[ 8][1] = -1.61803f;		vectors[ 8][2] = 0.525731f;
		vectors[ 9][0] = 0.850651f;		vectors[ 9][1] = -2.61803f;		vectors[ 9][2] = 0.525731f;
		vectors[10][0] = 2.22703f;		vectors[10][1] = -1.61803f;		vectors[10][2] = -0.525731f;
		vectors[11][0] = 2.22703f;		vectors[11][1] = 1.61803f;		vectors[11][2] = -0.525731f;
		vectors[12][0] = -0.850651f;	vectors[12][1] = 2.61803f;		vectors[12][2] = -0.525731f;
		vectors[13][0] = -2.75276f;		vectors[13][1] = 0.0f;			vectors[13][2] = -0.525731f;
		vectors[14][0] = -0.850651f;	vectors[14][1] = -2.61803f;		vectors[14][2] = -0.525731f;
		vectors[15][0] = 1.37638f;		vectors[15][1] = -1.0f;			vectors[15][2] = -2.22703f;
		vectors[16][0] = 1.37638f;		vectors[16][1] = 1.0f;			vectors[16][2] = -2.22703f;
		vectors[17][0] = -0.525731f;	vectors[17][1] = 1.61803f;		vectors[17][2] = -2.22703f;
		vectors[18][0] = -1.7013f;		vectors[18][1] = 0.0f;			vectors[18][2] = -2.22703f;
		vectors[19][0] = -0.525731f;	vectors[19][1] = -1.61803f;		vectors[19][2] = -2.22703f;		break;
	}

	for(int i=0; i<num; i++) {
		double norm = 0.0;
		for(int j=0; j<3; j++)	norm += (double)vectors[i][j]*(double)vectors[i][j];
		norm = sqrt(norm);
		for(int j=0; j<3; j++)	vectors[i][j] = (float)((double)vectors[i][j]/norm);
	}

	return vectors;
}


SIFT3D_FEATURES* CalculateSift3D_MultiPositions(
	VOL_RAWVOLUMEDATA* volume, int ch_v, int num_sample, int** sample_positions, 
	int roi_size, int num_roi_division, int num_angle)
{
	VOL_INTSIZE3D* size = VOL_GetIntSize3DFromIntSize4D(volume->matrixSize);
	int num_feats = num_roi_division*num_roi_division*num_roi_division*num_angle;

	SIFT3D_FEATURES* fout = NewSift3dFeatures(num_sample, num_feats);

	char bool_add_margin = 0;

	BOUNDING_BOX box = BoundingBoxOfSamplePositions(num_sample, sample_positions);
	int volsz3d[3];
	volsz3d[0] = WID(volume);	volsz3d[1] = HEI(volume);	volsz3d[2] = DEP(volume);

	int margin = 0;
	for(int c=0; c<3; c++) {
		box.top[c] -= roi_size/2;
		if(margin<-box.top[c])					margin = -box.top[c];
		box.tail[c] += roi_size/2;
		if(margin<box.tail[c]-volsz3d[c]+1)		margin = box.tail[c]-volsz3d[c]+1;
	}

	VOL_RAWVOLUMEDATA* input_vol = VOL_ExtractSingleChannelRawVolumeData(volume, ch_v);
	
	if(margin>0) {
		VOL_AttachOffsetXYZ(input_vol, margin, VOL_RESIZE_BACKGROUNDTYPE_BORDERCOPY_UNIFORM);
		for(int i=0; i<num_sample; i++) for(int c=0; c<3; c++) {
			sample_positions[i][c] += margin;
		}
	}

	float** ary_angles = GetEquallySpacedPointsOnUnitSphere(num_angle);

	for(int i=0; i<num_sample; i++) {
		float* f_tmp = CalculateSift3D_SinglePosition(input_vol, 0, sample_positions[i],
													  roi_size, num_roi_division, num_angle, ary_angles);
		memcpy(fout+i*num_feats, f_tmp, sizeof(float)*num_feats);
		delete [] f_tmp;
	}


	VOL_DeleteRawVolumeData(input_vol);

	if(margin>0) {
		for(int i=0; i<num_sample; i++) for(int c=0; c<3; c++) {
			sample_positions[i][c] -= margin;
		}
	}

	delete [] ary_angles[0];
	delete [] ary_angles;

	return fout;
}

