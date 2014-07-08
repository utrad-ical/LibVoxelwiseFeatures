
#include "VOL.h"

template <typename VTYPE>
double primitive_SumIntensityOfGivenVoxels(VTYPE* data, VOL_LOCATIONARRAY* posi)
{
	double sum = 0.0;
	for(int i=0; i<posi->nElements; i++)	sum += (double)data[posi->rasterPosition[i]];
	return sum;
}

double SumIntensityOfGivenVoxels(void* data, int unit, VOL_LOCATIONARRAY* posi)
{
	double sum;

	switch(unit)
	{
	case VOL_VALUEUNIT_UINT8:
		sum = primitive_SumIntensityOfGivenVoxels((unsigned char*)data, posi);
		break;
	case VOL_VALUEUNIT_SINT8:
		sum = primitive_SumIntensityOfGivenVoxels((char*)data, posi);
		break;
	case VOL_VALUEUNIT_UINT16:
		sum = primitive_SumIntensityOfGivenVoxels((unsigned short*)data, posi);
		break;
	case VOL_VALUEUNIT_SINT16:
		sum = primitive_SumIntensityOfGivenVoxels((short*)data, posi);
		break;
	case VOL_VALUEUNIT_UINT32:
		sum = primitive_SumIntensityOfGivenVoxels((unsigned int*)data, posi);
		break;
	case VOL_VALUEUNIT_SINT32:
		sum = primitive_SumIntensityOfGivenVoxels((int*)data, posi);
		break;
	case VOL_VALUEUNIT_FLOAT32:
		sum = primitive_SumIntensityOfGivenVoxels((float*)data, posi);
		break;
	case VOL_VALUEUNIT_FLOAT64:
		sum = primitive_SumIntensityOfGivenVoxels((double*)data, posi);
		break;
	}

	return sum;
}

