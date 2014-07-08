

#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "VOL.h"
#include "pthread.h"

#include "Curvatures.static.h"


typedef struct _ARGS_CALC_HU_MOMENTS_3D_MT_
{
	int numchannel;
	float*** vol;
	float**** out;
	VOL_KERNEL* kernel;
	VOL_INTBOX3D* box;
}
ARGS_CALCHUMOMENTS3D_MT;


int CalculateCyrvaturesGaussianAndMeanFromSinglePosition(float*** vol, VOL_INTVECTOR3D* coord, float* out)
{
	int k=coord->z, j=coord->y, i=coord->x;

	float fx = (vol[k][j][i+1]-vol[k][j][i+1])/2.0f;
	float fy = (vol[k][j+1][i]-vol[k][j-1][i])/2.0f;
	float fz = (vol[k+1][j][i]-vol[k-1][j][i])/2.0f;

	float h, M, K, H;

	if( (h=(fx*fx+fy*fy+fz*fz)) > 0.0f )
	{
		float	fxx = (vol[k][j][i+1]+vol[k][j][i+1]-2.0f*vol[k][j][i])/4.0f;
		float	fyy = (vol[k][j+1][i]+vol[k][j-1][i]-2.0f*vol[k][j][i])/4.0f;
		float	fzz = (vol[k+1][j][i]+vol[k-1][j][i]-2.0f*vol[k][j][i])/4.0f;
		float	fxy = (vol[k][j+1][i+1]+vol[k][j-1][i-1]-vol[k][j-1][i+1]-vol[k][j+1][i-1])/4.0f;
		float	fyz = (vol[k+1][j+1][i]+vol[k-1][j-1][i]-vol[k+1][j-1][i]-vol[k-1][j+1][i])/4.0f;
		float	fzx = (vol[k+1][j][i+1]+vol[k-1][j][i-1]-vol[k-1][j][i+1]-vol[k+1][j][i-1])/4.0f;

		M = (float)sqrt(h);

		K = (	fx*fx*(fyy*fzz-fyz*fyz) + 2.0f*fy*fz*(fxy*fzx-fxx*fyz) +
				fy*fy*(fzz*fxx-fzx*fzx) + 2.0f*fz*fx*(fyz*fxy-fyy*fzx) +
				fz*fz*(fxx*fyy-fxy*fxy) + 2.0f*fx*fy*(fzx*fyz-fzz*fxy) )/(h*h);

		H = (	fx*fx*(fyy+fzz) - 2.0f*fy*fz*fyz +
				fy*fy*(fzz+fxx) - 2.0f*fz*fx*fzx +
				fz*fz*(fxx+fyy) - 2.0f*fx*fy*fxy )/(2.0f*h*M);
	}
	else
	{
		K = H = 0.0f;
	}

	out[0] = K;
	out[1] = H;

	return 0;
}

int ConvertCurvatureGaussianMeanToShapeindexCurvedness(float gaussian, float mean, float* out)
{
	float K = gaussian;
	float H = mean;
	float k1, k2, S, R, tmp;
	float PI = 3.141529f;

	if( (tmp=H*H-K) <= 0.0f )
	{
		if( H < 0.0f )	S = 1.0f;
		else			S = 0.0f;

		k1 = k2 = H;
	}
	else
	{
		tmp = (float)sqrt(tmp);
		k1 = H + tmp;
		k2 = H - tmp;
		S = 0.5f - (float)atan((double)((k1+k2)/(k1-k2)))/PI;
	}

	R = 4.0f*H*H - 2.0f*K;

	if( R > 0.0f )	R = (float)(sqrt(R)/2.0);
	else			R = 0.0f;

	out[0] = S;
	out[1] = R;

	return 0;
}



