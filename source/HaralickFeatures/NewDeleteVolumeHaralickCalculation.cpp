

#include "HaralickFeatures.h"
#include "HaralickFeatures.private.h"


template <typename VTYPE>
void templete_ReduceGradation(VTYPE* data, int ndata, VOL_VALUERANGE* range, int ngradation)
{
	for(int i=0; i<ndata; i++) {
		float temp = ((float)data[i]-range->min)/(range->max-range->min)*(float)ngradation;
		if(temp<0.0f)	temp = 0.0f;
		else if(temp>=(float)ngradation)	temp = (float)ngradation-1.0f;
		data[i] = (VTYPE)temp;
	}
}


VOLUMEHARALICKCALCULATION* NewVolumeHaralickCalculation(
	VOL_RAWVOLUMEDATA* volume, int channel, VOL_VALUERANGE* range, int numGradation, VOL_KERNEL* roi, VOL_KERNEL* references)
{
	VOLUMEHARALICKCALCULATION* output = new VOLUMEHARALICKCALCULATION;

	SetIntRadInVolKernel(roi);
	SetIntRadInVolKernel(references);

	output->margin = roi->intRad+references->intRad;
	output->numGradation = numGradation;
	output->vol = VOL_ExtractSingleChannelRawVolumeData(volume, channel);
	VOL_RAWVOLUMEDATA* hVol = (VOL_RAWVOLUMEDATA*)output->vol;

	int ndata = hVol->matrixSize->depth*hVol->matrixSize->height*hVol->matrixSize->width;

	switch(hVol->voxelUnit[channel]) {
	case VOL_VALUEUNIT_UINT8:
		templete_ReduceGradation((unsigned char*)hVol->data[channel], ndata, range, numGradation);
		break;
	case VOL_VALUEUNIT_SINT8:
		templete_ReduceGradation((char*)hVol->data[channel], ndata, range, numGradation);
		break;
	case VOL_VALUEUNIT_UINT16:
		templete_ReduceGradation((unsigned short*)hVol->data[channel], ndata, range, numGradation);
		break;
	case VOL_VALUEUNIT_SINT16:
		templete_ReduceGradation((short*)hVol->data[channel], ndata, range, numGradation);
		break;
	case VOL_VALUEUNIT_UINT32:
		templete_ReduceGradation((unsigned int*)hVol->data[channel], ndata, range, numGradation);
		break;
	case VOL_VALUEUNIT_SINT32:
		templete_ReduceGradation((int*)hVol->data[channel], ndata, range, numGradation);
		break;
	case VOL_VALUEUNIT_FLOAT32:
		templete_ReduceGradation((float*)hVol->data[channel], ndata, range, numGradation);
		break;
	case VOL_VALUEUNIT_FLOAT64:
		templete_ReduceGradation((double*)hVol->data[channel], ndata, range, numGradation);
		break;
	}

	if(hVol->voxelUnit[channel]!=VOL_VALUEUNIT_UINT8) {
		VOL_ConvertVoxelUnit(hVol, 0, VOL_VALUEUNIT_UINT8, NULL, NULL, VOL_CONVERTUNIT_TYPE_DIRECT);
	}

	VOL_AttachOffsetXYZ(hVol, output->margin, VOL_RESIZE_BACKGROUNDTYPE_BORDERCOPY_UNIFORM);

	return output;
}


void DeleteVolumeHaralickCalculation(VOLUMEHARALICKCALCULATION* volumeH)
{
	VOL_DeleteRawVolumeData((VOL_RAWVOLUMEDATA*)volumeH->vol);
	delete volumeH;
}

