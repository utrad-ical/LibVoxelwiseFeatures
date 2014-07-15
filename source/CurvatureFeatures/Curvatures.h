
#ifndef CALC_CURVATURES__H
#define CALC_CURVATURES__H


#include "VOL.h"


// int CalculateCyrvaturesGaussianAndMeanFromSinglePosition(float*** vol, VOL_INTVECTOR3D* coord, float* out);
// int ConvertCurvatureGaussianMeanToShapeindexCurvedness(float gaussian, float mean, float* out);

int CalculateCurvaturesHesseLambda(float*** vol, VOL_INTVECTOR3D* coord, float* out);
int ConvertCurvaturesToSICurvPC(float gaussian, float mean, float* out);


#endif 

