
#pragma warning(disable: 4996)

#include <cmath>
#include "VOL.h"

// #define DEBUG_PRINT
#define	PI	3.141593f

float Inner(float* v1, float* v2, int n)
{
	float out = 0.0f;
	for(int i=0; i<n; i++)	out += v1[i]*v2[i];
	return out;
}

template <typename VTYPE>
float* CalculateSift3D_Primitive(
	VTYPE*** vol, int num_sampling, int** sampling, int num_angle, float** angles)
{
	float* out = new float [num_angle+1];
	memset(out, 0x00, sizeof(float)*(num_angle+1));

	float g[3], add_weight=1.0f/(float)num_sampling;

	for(int t=0; t<num_sampling; t++) {
		int i=sampling[t][0], j=sampling[t][1], k=sampling[t][2];
		g[0] = (float)(vol[k][j][i+1]-vol[k][j][i-1]);
		g[1] = (float)(vol[k][j+1][i]-vol[k][j-1][i]);
		g[2] = (float)(vol[k+1][j][i]-vol[k-1][j][i]);
#ifdef DEBUG_PRINT
		fprintf(stderr, "p[%d,%d,%d]=g(%.2f,%.2f,%.2f); ",i,j,k,g[0],g[1],g[2]);
#endif
		if(g[0]==0.0f && g[1]==0.0f && g[2]==0.0f) {
			out[num_angle] += add_weight;
#ifdef DEBUG_PRINT
			fprintf(stderr, "no_grad");
#endif
		} else {
			int i_max = 0;
			float max_value = Inner(g, angles[0], 3);
#ifdef DEBUG_PRINT
			fprintf(stderr, "[0](%.3f,%.3f,%.3f)->%.3f,", angles[0][0],angles[0][1],angles[0][2],max_value);
#endif
			for(int i=1; i<num_angle; i++) {
				float tmp = Inner(g, angles[i], 3);
#ifdef DEBUG_PRINT
				fprintf(stderr, "[%d](%.3f,%.3f,%.3f)->%.3f,", i,angles[i][0],angles[i][1],angles[i][2],tmp);
#endif
				if(max_value<tmp) {
					i_max = i;		max_value = tmp;
				}
#ifdef DEBUG_PRINT
				fprintf(stderr, "max_%d(%.3f),", i_max,max_value);
#endif
			}
#ifdef DEBUG_PRINT
			fprintf(stderr, " out=%d(%.3f),add%.3f", i_max,max_value,add_weight);
#endif
			out[i_max] += add_weight;
		}
#ifdef DEBUG_PRINT
		fprintf(stderr, "\n");
		getchar();
#endif
	}

//	for(int i=0; i<=num_angle; i++) {
//		fprintf(stderr, "[%d]=%.3f, ", i,out[i]);
//	}
//	fprintf(stderr, "\n");
//	getchar();

	return out;
}

float* CalculateSift3D_SinglePosition(
	VOL_RAWVOLUMEDATA* volume, int ch, int* p,
	int roi_size, int num_roi_division, int num_angle, float** base_angles)
{
	float** angles = base_angles;

#ifdef DEBUG_PRINT
	fprintf(stderr, "1,");
#endif
	int org[3];
	org[0] = p[0]-roi_size/2;	org[1] = p[1]-roi_size/2;	org[2] = p[2]-roi_size/2;

#ifdef DEBUG_PRINT
	fprintf(stderr, "2,");
#endif
	float sz_sub = (float)roi_size/(float)num_roi_division;

#ifdef DEBUG_PRINT
	fprintf(stderr, "3,");
#endif
	int n_tmp_roi = ((int)sz_sub+1)*((int)sz_sub+1)*((int)sz_sub+1);
	int** tmp_roi = new int* [n_tmp_roi];
	tmp_roi[0] = new int [n_tmp_roi*3];
	for(int i=0; i<n_tmp_roi; i++)	tmp_roi[i] = tmp_roi[0]+3*i; 

#ifdef DEBUG_PRINT
	fprintf(stderr, "4,");
#endif
	float* out = new float [num_angle*num_roi_division*num_roi_division*num_roi_division];

#ifdef DEBUG_PRINT
	fprintf(stderr, "5,");
#endif
	int i_top = 0;
	for(int z=0; z<num_roi_division; z++) {	
		int sz=(int)((float)z*sz_sub+0.5f);
		int ez=(int)((float)(z+1)*sz_sub+0.5f);
		for(int y=0; y<num_roi_division; y++) {	
			int sy=(int)((float)y*sz_sub+0.5f);
			int ey=(int)((float)(y+1)*sz_sub+0.5f);
			for(int x=0; x<num_roi_division; x++) {	
				int sx=(int)((float)x*sz_sub+0.5f);
				int ex=(int)((float)(x+1)*sz_sub+0.5f);

#ifdef DEBUG_PRINT
				fprintf(stderr, "(%d,%d,%d),", z,y,x);
#endif
				int cnt=0;
				for(int k=sz; k<ez; k++) for(int j=sy; j<ey; j++) for(int i=sx; i<ex; i++) {
					tmp_roi[cnt][0] = org[0]+i;
					tmp_roi[cnt][1] = org[1]+j;
					tmp_roi[cnt][2] = org[2]+k;
					cnt++;
				}

#ifdef DEBUG_PRINT
				fprintf(stderr, "cnt%d,", cnt);
#endif
				float* tmp_out;
				switch(volume->voxelUnit[ch]) {
				case 0:
					tmp_out = CalculateSift3D_Primitive((unsigned char***)volume->array4D[ch], cnt, tmp_roi, num_angle, angles);
					break;
				case 1:
					tmp_out = CalculateSift3D_Primitive((char***)volume->array4D[ch], cnt, tmp_roi, num_angle, angles);
					break;
				case 2:
					tmp_out = CalculateSift3D_Primitive((unsigned short***)volume->array4D[ch], cnt, tmp_roi, num_angle, angles);
					break;
				case 3:
					tmp_out = CalculateSift3D_Primitive((short***)volume->array4D[ch], cnt, tmp_roi, num_angle, angles);
					break;
				case 4:
					tmp_out = CalculateSift3D_Primitive((unsigned int***)volume->array4D[ch], cnt, tmp_roi, num_angle, angles);
					break;
				case 5:
					tmp_out = CalculateSift3D_Primitive((int***)volume->array4D[ch], cnt, tmp_roi, num_angle, angles);
					break;
				case 6:
					tmp_out = CalculateSift3D_Primitive((float***)volume->array4D[ch], cnt, tmp_roi, num_angle, angles);
					break;
				case 7:
					tmp_out = CalculateSift3D_Primitive((double***)volume->array4D[ch], cnt, tmp_roi, num_angle, angles);
					break;
				}
#ifdef DEBUG_PRINT
				fprintf(stderr, ".");
#endif
				memcpy(out+i_top, tmp_out, sizeof(float)*num_angle);
				i_top += num_angle;
#ifdef DEBUG_PRINT
				fprintf(stderr, "%d, ", i_top);
#endif
	}}}

	delete [] tmp_roi[0];
	delete [] tmp_roi;
#ifdef DEBUG_PRINT
	fprintf(stderr, "ok\n");
#endif
	return out;
}



#ifdef MULTI_ORIENTATION

int**** set_4d(int size)
{
	int**** out = new int*** [size];
	for(int z=0; z<size; z++) {
		out[z] = new int** [size];
		for(int y=0; y<size; y++) {
			out[z][y] = new int* [size];
			for(int x=0; x<size; x++) {
				out[z][y][x] = new int [3];
			}
		}
	}
	return out;
}

void delete_4d(int**** in, int size)
{
	for(int z=0; z<size; z++) {
		for(int y=0; y<size; y++) {
			for(int x=0; x<size; x++)	delete [] in[z][y][x];
			delete [] in[z][y];
		}
		delete [] in[z];
	}
	return;
}

typedef struct _Rotation_Data_{
	float** matrix;
	float ax, ay, az, cos, sin; 
} RotationData;

RotationData* SetRotationDataFromAxisX(float* vect)
{
	RotationData* out = new RotationData;

	out->matrix = new float* [4];
	out->matrix[0] = new float [4*4];
	for(int i=0; i<4; i++)	out->matrix[i] = out->matrix[0]+4*i;
	memset(out->matrix[0], 0x00, sizeof(float)*4*4);

	out->ax = 0.0f;
	out->ay = -vect[2];
	out->az = vect[1];
	out->cos = vect[0];
	out->sin = sqrt(1.0f-out->cos*out->cos);

	out->matrix[0][0] = out->cos;
	out->matrix[0][1] = -out->az*out->sin;
	out->matrix[0][2] = out->ay*out->sin;
	out->matrix[1][0] = out->az*out->sin;
	out->matrix[1][1] = out->ay*out->ay*(1.0f-out->cos)+out->cos;
	out->matrix[1][2] = out->ay*out->az*(1.0f-out->cos);
	out->matrix[2][0] = -out->ay*out->sin;
	out->matrix[2][1] = out->ay*out->az*(1.0f-out->cos);
	out->matrix[2][2] = out->az*out->az*(1.0f-out->cos)+out->cos;
	out->matrix[3][3] = 1.0f;

	return out;
}

void DeleteRotationData(RotationData* in)
{
	delete [] in->matrix[0];
	delete [] in->matrix;
	delete in;
}

float* MultiplyForRotation(int ncolumn, int nrow, float** mat, float* vect)
{
	float* out = new float [nrow];
	memset(out, 0x00, sizeof(float)*nrow);
	for(unsigned int jj=0; jj<ncolumn; jj++) {
		for(unsigned int ii=0; ii<nrow; ii++)	out[jj] += mat[jj][ii]*vect[ii];
	}
	return out;
}

float* CalculateSift3D_SinglePosition(
	VOL_RAWVOLUMEDATA* volume, int ch, int* p, float* orientation,
	int roi_size, int num_roi_div, int num_angle, float** base_angles)
{
	RotationData* d_rot = NULL;
	if(orientation!=NULL)	SetRotationDataFromAxisX(orientation);

	// äeï˚å¸ê¨ï™ÇorientationÇ≈ï‚ê≥
	float** angles;
	if(d_rot==NULL) {
		angles = base_angles;
	} else {
		angles = new float* [num_angle];
		for(int i=0; i<num_angle; i++) {
			angles[i] = MultiplyForRotation(4, 4, d_rot->matrix, base_angles[i]);
		}
	}

	// óßï˚ëÃèÛÇÃåvéZóÃàÊ
	int**** roi_set = set_4d(roi_size);
	float org_xyz[3], ori_xyz[3];
	
	if(orientation==NULL) {
		ori_xyz[0] = ori_xyz[1] = ori_xyz[2] = 1.0f;
	} else {
		for(int d=0; d<3; d++) {
			ori_xyz[d] = 0.0f;
			for(int t=0; t<3; t++)	ori_xyz[d] += orientation[t][d];
		}
	}

	for(int d=0; d<3; d++) {
		org_xyz[d] = (float)p[d]-(float)(roi_size/2)*ori_xyz[d];
	}

	for(int k=0; k<roi_size; k++) for(int j=0; j<roi_size; j++) for(int i=0; i<roi_size; i++) {
		for(int d=0; d<3; d++)	roi_set[k][j][i][d] = (int)(org_xyz[d]+ori_xyz[d]*(float)i+0.5f);
	}
	

	float sz_sub = (float)roi_size/(float)num_roi_div;
	int** tmp_roi = new int* [((int)sz_sub+1)*((int)sz_sub+1)*((int)sz_sub+1)];

	float* out = new float [num_angle*num_roi_div*num_roi_div*num_roi_div];
	int i_top = 0;
	for(int z=0; z<num_roi_div; z++) {
	for(int y=0; y<num_roi_div; y++) {
	for(int x=0; x<num_roi_div; x++) {
		int cnt = 0;
		for(int k=(int)((float)z*sz_sub+0.5f); k<(int)((float)(z+1)*sz_sub+0.5f); k++) {
		for(int j=(int)((float)y*sz_sub+0.5f); j<(int)((float)(y+1)*sz_sub+0.5f); j++) {
		for(int i=(int)((float)x*sz_sub+0.5f); i<(int)((float)(x+1)*sz_sub+0.5f); i++) {
			tmp_roi[cnt++] = roi_set[k][j][i];
		}}}
		float* tmp_out;
		switch(volume->voxelUnit[ch]) {
		case 0:
			tmp_out = CalculateSift3D_Primitive((unsigned char***)volume->array4D[ch], cnt, tmp_roi, num_angle, angles);
			break;
		case 1:
			tmp_out = CalculateSift3D_Primitive((char***)volume->array4D[ch], cnt, tmp_roi, num_angle, angles);
			break;
		case 2:
			tmp_out = CalculateSift3D_Primitive((unsigned short***)volume->array4D[ch], cnt, tmp_roi, num_angle, angles);
			break;
		case 3:
			tmp_out = CalculateSift3D_Primitive((short***)volume->array4D[ch], cnt, tmp_roi, num_angle, angles);
			break;
		case 4:
			tmp_out = CalculateSift3D_Primitive((unsigned int***)volume->array4D[ch], cnt, tmp_roi, num_angle, angles);
			break;
		case 5:
			tmp_out = CalculateSift3D_Primitive((int***)volume->array4D[ch], cnt, tmp_roi, num_angle, angles);
			break;
		case 6:
			tmp_out = CalculateSift3D_Primitive((float***)volume->array4D[ch], cnt, tmp_roi, num_angle, angles);
			break;
		case 7:
			tmp_out = CalculateSift3D_Primitive((double***)volume->array4D[ch], cnt, tmp_roi, num_angle, angles);
			break;
		}
		memcpy(out+i_top, tmp_out, sizeof(float)*num_angle);
		i_top += num_angle;
	}}}

	delete [] tmp_roi;
	delete_4d(roi_set, roi_size);
	if(orientation!=NULL) {
		delete [] angles[0];
		delete [] angles;
	}
	
	return out;
}

#endif


