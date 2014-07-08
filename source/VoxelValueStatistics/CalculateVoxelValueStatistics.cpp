

#pragma warning(disable: 4996)

#include "VOL.h"
#include "VoxelValueStatistics.h"


template <typename VTYPE>
VOXELVALUESTATISTICS templete_CalcStatistics(VTYPE*** vol, VOL_INTVECTOR3D* coord, VOL_KERNEL* kernel)
{
	VOXELVALUESTATISTICS out;

	double avg = 0.0;
	VOL_LOCATIONARRAY* voi = kernel->locationArray;

	for(int i=0; i<voi->nElements; i++) { 
		avg += (double)vol[coord->z+voi->z[i]][coord->y+voi->y[i]][coord->x+voi->x[i]];
	}
	avg /= (double)voi->nElements;
	out.mean = (float)avg;

	double m2=0.0, m3=0.0, m4=0.0;
	for(int i=0; i<voi->nElements; i++) { 
		double sub = (double)vol[coord->z+voi->z[i]][coord->y+voi->y[i]][coord->x+voi->x[i]]-avg;
		m2 += sub*sub/(double)(voi->nElements-1);
		m3 += sub*sub*sub/(double)(voi->nElements-1);
		m4 += sub*sub*sub*sub/(double)(voi->nElements-1);
	}

	double stdev = sqrt(m2);
	out.var = (float)m2;
	if(m2!=0.0) {
		out.skew = (float)(m3/(stdev*m2));	// out.skew = (float)m3;
		out.kurt = (float)(m4/(m2*m2));		// out.kurt = (float)m4;
	} else {
		out.skew = out.kurt = 0.0f;
	}

	return out;
}


VOXELVALUESTATISTICS CalculateVoxelValueStatistics(VOL_RAWVOLUMEDATA* volume, int channel, VOL_INTVECTOR3D* coord, VOL_KERNEL* roi)
{
	VOXELVALUESTATISTICS out;

	switch(volume->voxelUnit[channel]) {
	case VOL_VALUEUNIT_UINT8:
		out = templete_CalcStatistics((unsigned char***)volume->array4D[channel], coord, roi);
		break;
	case VOL_VALUEUNIT_SINT8:
		out = templete_CalcStatistics((char***)volume->array4D[channel], coord, roi);
		break;
	case VOL_VALUEUNIT_UINT16:
		out = templete_CalcStatistics((unsigned short***)volume->array4D[channel], coord, roi);
		break;
	case VOL_VALUEUNIT_SINT16:
		out = templete_CalcStatistics((short***)volume->array4D[channel], coord, roi);
		break;
	case VOL_VALUEUNIT_UINT32:
		out = templete_CalcStatistics((unsigned int***)volume->array4D[channel], coord, roi);
		break;
	case VOL_VALUEUNIT_SINT32:
		out = templete_CalcStatistics((int***)volume->array4D[channel], coord, roi);
		break;
	case VOL_VALUEUNIT_FLOAT32:
		out = templete_CalcStatistics((float***)volume->array4D[channel], coord, roi);
		break;
	case VOL_VALUEUNIT_FLOAT64:
		out = templete_CalcStatistics((double***)volume->array4D[channel], coord, roi);
		break;
	}

	return out;
}




