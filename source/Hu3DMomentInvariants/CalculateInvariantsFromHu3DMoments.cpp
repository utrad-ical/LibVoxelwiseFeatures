

//#include <cstdio>
#include "Hu3DMomentInvariants.h"
#include "Hu3DMomentInvariants.private.h"


template <typename VTYPE>
VTYPE CalcDeterminant(VTYPE** m, int width, int height)
{
	if(width==1) {
		return m[0][0];
	} else if(width==2) {
		return m[0][0]*m[1][1]-m[0][1]*m[1][0];
	}

	int col, row;
	VTYPE accum_plus, accum_minus, determinant=0.0;

	for(int start=0; start<height; start++)
	{
		accum_plus=1.0, accum_minus=1.0;
		for(int step=0; step<width; step++)
		{
			row = start+step;
			if(row>=height)	row -= height;
			col = step;
			accum_plus *= m[row][col];

			col = height-step-1;
			accum_minus *= m[row][col];
		}
		determinant += accum_plus-accum_minus;	
	}

	return determinant;
}


//HU3DMOMENTINVARIANTS CalculateInvariantsFromHu3DMoments(HU3DMOMENTS* hu)
float* CalculateInvariantsFromHu3DMoments(HU3DMOMENTS* hu)
{
	double** hu_matrix = new double* [3];
	hu_matrix[0] = new double [3*3];
	for(int i=1; i<3; i++)	hu_matrix[i] = hu_matrix[0]+i*3;

	hu_matrix[0][0] = hu->m200;
	hu_matrix[1][1] = hu->m020;
	hu_matrix[2][2] = hu->m002;
	hu_matrix[1][0] = hu_matrix[0][1] = hu->m110;
	hu_matrix[2][0] = hu_matrix[0][2] = hu->m101;
	hu_matrix[2][1] = hu_matrix[1][2] = hu->m011;

	double determinant = CalcDeterminant(hu_matrix, 3, 3);

	delete [] hu_matrix[0];
	delete [] hu_matrix;


	float* out = new float [NUM_INVARIANTS_FROM_HU_3D_MOMENT];
	out[0] = (float)(hu->m002+hu->m020+hu->m200);
	out[1] = (float)(hu->m002*hu->m020-hu->m011*hu->m011 + hu->m020*hu->m200-hu->m110*hu->m110 + hu->m002*hu->m200-hu->m101*hu->m101);
	out[2] = (float)determinant;
	out[3] = out[0]*out[0]/out[1];
	out[4] = out[2]/(out[0]*out[0]*out[0]);

//	HU3DMOMENTINVARIANTS out;
//	out.J1 = (float)(hu->m002+hu->m020+hu->m200);
//	out.J2 = (float)(hu->m002*hu->m020-hu->m011*hu->m011 + hu->m020*hu->m200-hu->m110*hu->m110 + hu->m002*hu->m200-hu->m101*hu->m101);
//	out.delta = (float)determinant;
//	out.I1 = out.J1*out.J1/out.J2;
//	out.I2 = out.delta/(out.J1*out.J1*out.J1);

	return out;
}


/*
PR_MATHMATRIX* mmatrix = PR_NewMathMatrix(3, 3);
mmatrix->dataMatrix[0][0] = m200;
mmatrix->dataMatrix[1][1] = m020;
mmatrix->dataMatrix[2][2] = m002;
mmatrix->dataMatrix[1][0] = mmatrix->dataMatrix[0][1] = m110;
mmatrix->dataMatrix[2][0] = mmatrix->dataMatrix[0][2] = m101;
mmatrix->dataMatrix[2][1] = mmatrix->dataMatrix[1][2] = m011;

double det = PR_CalcDeterminantDouble(mmatrix);
PR_DeleteMathMatrix(mmatrix);

float* output = new float [5];
output[0] = (float)(m002+m020+m200);
output[1] = (float)(m002*m020-m011*m011 + m020*m200-m110*m110 + m002*m200-m101*m101);
output[2] = (float)det;
output[3] = output[0]*output[0]/output[1];
output[4] = output[2]/(output[0]*output[0]*output[0]);
*/

