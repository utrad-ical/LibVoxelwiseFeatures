

#include "VOL.h"
#include "HaralickFeatures.h"



// 同時生起行列由来のテクスチャ特徴量計測
float* CalculateHaralickFeaturesFromCoOccurenceMatrix(float* coMatrix1D, int gradation)
{
	float** coMatrix2D = new float* [gradation]; 
	for(int j=0; j<gradation; j++) {
		coMatrix2D[j] = coMatrix1D+j*gradation;
	}
	
	int nfeas = NUM_HARALICK_FEATURES;

	float* features = new float [nfeas];
	memset(features, 0x00, sizeof(float)*nfeas);

	float* px = new float [gradation];				
	float* py = new float [gradation];
	float* pxyadd = new float [gradation*2];
	float* pxysub = new float [gradation];

	memset(px, 0x00, sizeof(float)*gradation);
	memset(py, 0x00, sizeof(float)*gradation);
	memset(pxyadd, 0x00, sizeof(float)*(gradation*2));
	memset(pxysub, 0x00, sizeof(float)*gradation);

	for(int j=0; j<gradation; j++)
	for(int i=0; i<gradation; i++)
	{
		float pm = coMatrix2D[j][i];
		px[i] += pm;
		py[j] += pm;
		pxyadd[i+j] += pm;
		pxysub[abs(i-j)] += pm;
	}
	
	float mx=0.0f, my=0.0f;
	for(int i=0; i<gradation; i++)
	{
		mx += (float)i*px[i];
		my += (float)i*py[i];
	}

	for(int j=0; j<gradation; j++)
	for(int i=0; i<gradation; i++)
	if(coMatrix2D[j][i]>0.0f)
	{
		float pm = coMatrix2D[j][i];
		features[0] += pm*pm;											// asm: angular second moment
		features[1] += pm/(1.0f+(float)((i-j)*(i-j)));					// idm: inverse difference moment
	}
//	printf("[0]%f,[1]%f,",features[0],features[1]);

	for(int k=0; k<gradation; k++)
	if(pxysub[k]>0.0f)	features[2] += (float)(k*k)*pxysub[k];				// cnt: contrast
//	printf("[2]%f,",features[2]);

	for(int j=0; j<gradation; j++)
	for(int i=0; i<gradation; i++)
	if(coMatrix2D[j][i]>0.0f)
	{
		float pm = coMatrix2D[j][i];
		features[3] += ((float)i-mx)*((float)i-mx)*pm;		// var: variance
		features[4] -= pm*log(pm);							// ent: entropy
		features[5] += (float)(i*j)*pm;						// crr: correlation
	}
//	printf("[3]%f,[4]%f,[5']%f,",features[3],features[4],features[5]);


	float sx2=0.0f, sy2=0.0f;
	for(int i=0; i<gradation; i++)
	{
		sx2 += (mx-(float)i)*(mx-(float)i)*px[i];
		sy2 += (my-(float)i)*(my-(float)i)*py[i];
	}

	float sx=0.0f, sy=0.0f;
	if(sx2>1.0e-6)	sx = sqrt(sx2);
	if(sy2>1.0e-6)	sy = sqrt(sy2);

	if(sx*sy>0.0f)	features[5] = (features[5]-mx*my)/(sx*sy);		// crr: correlation
	else			features[5] = -5.0f;
//	printf("[5]%f,",features[5]);

	for(int k=0; k<gradation*2-1; k++)
	if(pxyadd[k]>0.0f)	features[6] += (float)k*pxyadd[k];				// sumavg: sum average
//	printf("[6]%f,",features[6]);

	for(int k=0; k<gradation*2-1; k++)
	if(pxyadd[k]>0.0f)
	{
		float sub = (float)k-features[6];
		features[7] += sub*sub*pxyadd[k];				// sumvar: sum variance
	}
//	printf("[7]%f,",features[7]);

	for(int k=0; k<gradation*2-1; k++)
	if(pxyadd[k]>0.0f)	features[8] -= pxyadd[k]*log(pxyadd[k]);		// sument: sum entropy
//	printf("[8]%f,",features[8]);


	float tmpDifVar=0.0f;
	for(int k=0; k<gradation; k++) {
		if(pxysub[k]>0.0f)	tmpDifVar += (float)k*pxysub[k];
	}

	for(int k=0; k<gradation; k++)
	if(pxysub[k]>0.0f)
	{
		float sub = (float)k-tmpDifVar;
		features[9] += sub*sub*pxysub[k];					// difvar: difference variance
	}
//	printf("[9]%f,",features[9]);

	for(int k=0; k<gradation; k++)
	if(pxysub[k]>0.0f)		features[10] -= pxysub[k]*log(pxysub[k]);			// difent: difference entropy
//	printf("[10]%f,",features[10]);


//	delete [] coMatrix2D[0];
	delete [] coMatrix2D;
	delete [] px;
	delete [] py;
	delete [] pxyadd;
	delete [] pxysub;

//	printf("\n");

	return features;
}