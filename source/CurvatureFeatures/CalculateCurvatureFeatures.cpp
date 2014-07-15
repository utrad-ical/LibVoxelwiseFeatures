


#include "CurvatureFeatures.h"
#include "Curvatures.h"
#include "../Utilities/CalculatingVoxels.h"


float* CalculateCurvatureFeatures(VOL_RAWVOLUMEDATA* input, int ch, VOL_INTVECTOR3D* coord)
{
	float* output = new float [NUM_CURVATURE_FEATURES];
	float* aryFeat1 = new float [NUM_CURVATURE_FEATURES];
	float* aryFeat2 = new float [NUM_CURVATURE_FEATURES];

	float*** vol = (float***)input->array4D[ch];

	// CalculateCyrvaturesGaussianAndMeanFromSinglePosition(vol, coord, output);
	// ConvertCurvatureGaussianMeanToShapeindexCurvedness(output[0], output[1], output+2);

	CalculateCurvaturesHesseLambda(vol, coord, aryFeat1);
	ConvertCurvaturesToSICurvPC(aryFeat1[0], aryFeat1[1], aryFeat2);

	output[0] = aryFeat1[0];
	output[1] = aryFeat1[1];
	output[4] = aryFeat1[2];
	output[5] = aryFeat1[3];
	output[6] = aryFeat1[4];

	output[2] = aryFeat2[0];
	output[3] = aryFeat2[1];
	output[7] = aryFeat2[2];
	output[8] = aryFeat2[3];

	delete [] aryFeat1;
	delete [] aryFeat2;

	return output;
}


void CalculateCurvatureFeatures_SubsetOfVoxels(
	VOL_RAWVOLUMEDATA* input, int ch, VOL_RAWVOLUMEDATA* output, CALCULATINGVOXELS* subset)
{
	float*** vol = (float***)input->array4D[ch];
	float**** features = (float****)output->array4D;

	VOL_INTVECTOR3D coord;
	float* aryFeat1 = new float [NUM_CURVATURE_FEATURES];
	float* aryFeat2 = new float [NUM_CURVATURE_FEATURES];
	
	for(int i=0; i<subset->num; i++) {
		
		coord.x = subset->xc[i];
		coord.y = subset->yc[i];
		coord.z = subset->zc[i];

	//	CalculateCyrvaturesGaussianAndMeanFromSinglePosition(vol, &coord, aryFeat);
	//	ConvertCurvatureGaussianMeanToShapeindexCurvedness(aryFeat[0], aryFeat[1], aryFeat+2);
	//	printf("%f,%f,%f,%f ", aryFeat[0],aryFeat[1],aryFeat[2],aryFeat[3]);
	//	features[0][subset->zc[i]][subset->yc[i]][subset->xc[i]] = aryFeat[0];
	//	features[1][subset->zc[i]][subset->yc[i]][subset->xc[i]] = aryFeat[1];
	//	features[2][subset->zc[i]][subset->yc[i]][subset->xc[i]] = aryFeat[2];
	//	features[3][subset->zc[i]][subset->yc[i]][subset->xc[i]] = aryFeat[3];

		CalculateCurvaturesHesseLambda(vol, &coord, aryFeat1);
		ConvertCurvaturesToSICurvPC(aryFeat1[0], aryFeat1[1], aryFeat2);

		features[0][subset->zc[i]][subset->yc[i]][subset->xc[i]] = aryFeat1[0];
		features[1][subset->zc[i]][subset->yc[i]][subset->xc[i]] = aryFeat1[1];
		features[2][subset->zc[i]][subset->yc[i]][subset->xc[i]] = aryFeat2[0];
		features[3][subset->zc[i]][subset->yc[i]][subset->xc[i]] = aryFeat2[1];
		features[4][subset->zc[i]][subset->yc[i]][subset->xc[i]] = aryFeat1[2];
		features[5][subset->zc[i]][subset->yc[i]][subset->xc[i]] = aryFeat1[3];
		features[6][subset->zc[i]][subset->yc[i]][subset->xc[i]] = aryFeat1[4];
		features[7][subset->zc[i]][subset->yc[i]][subset->xc[i]] = aryFeat2[2];
		features[8][subset->zc[i]][subset->yc[i]][subset->xc[i]] = aryFeat2[3];
	//	printf("ok\n");
	}

	delete [] aryFeat1;
	delete [] aryFeat2;

	return;
}


