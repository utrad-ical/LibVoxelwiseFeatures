
#pragma warning(disable: 4996)


#include "pthread.h"
#include "Sift3D.h"
#include "Sift3D.private.h"
#include "..\Utilities\DividedCalculatingVoxels.h"


VOL_RAWVOLUMEDATA* VolumeOfSift3D_MT(
	VOL_RAWVOLUMEDATA* volume, int ch_v, VOL_RAWVOLUMEDATA* mask, int ch_m, 
	int roi_size, int num_roi_division, int num_angle, int num_threads)
{
	if(num_threads==1) {
		return VolumeOfSift3D(volume, ch_v, mask, ch_m, roi_size, num_roi_division, num_angle);
	}

	int nfeats = num_roi_division*num_roi_division*num_roi_division*num_angle;
	fprintf(stderr, "nfeats=%d,", nfeats);

	VOL_INTSIZE3D size3d;
	size3d.width=WID(volume);	size3d.height=HEI(volume);	size3d.depth=DEP(volume);

	fprintf(stderr, "setvol,");
	VOL_RAWVOLUMEDATA* output = VOL_NewSingleChannelRawVolumeData(&size3d, VOL_VALUEUNIT_FLOAT32, VOL_VALUETYPE_SINGLE);
	for(int i=1; i<nfeats; i++) {
		VOL_AddNewChannelInRawVolumeData(output, VOL_VALUEUNIT_FLOAT32, VOL_VALUETYPE_SINGLE);
	}

	fprintf(stderr, "get_pt,");
	CALCULATINGVOXELS* points;
	if(mask!=NULL) {
		points = ConvertMaskToCalculatingVoxels(mask, ch_m);
	} else {
		points = NewCalculatingVoxels(DATSIZE(volume));
		int count=0;
		for(int k=0; k<DEP(volume); k++) for(int j=0; j<HEI(volume); j++) for(int i=0; i<WID(volume); i++) {
			points->rp[count] = count;
			points->xc[count] = i;
			points->yc[count] = j;
			points->zc[count] = k;
			count++;
		}
	}
//	fprintf(stderr, "get_pt,");
//	CALCULATINGVOXELS* points = ConvertMaskToCalculatingVoxels(mask, ch_m);

	fprintf(stderr, "%d,calc_mt\n", points->num);
	SIFT_3D_FEATURES* feats = CalculateSift3D_MultiPositions_MT(volume, ch_v, points, roi_size, num_roi_division, num_angle, num_threads);

	for(int i=0; i<feats->n_sample; i++) {
		int x=points->xc[i], y=points->yc[i], z=points->zc[i];
		for(int ch=0; ch<feats->n_feats; ch++) {
			float*** feat_vol = (float***)output->array4D[ch];
			feat_vol[z][y][x] = feats->feat_array[i][ch];
		}
	}

	fprintf(stderr, "del,");
	DeleteCalculatingVoxels(points);
	DeleteSift3dFeatures(feats);

	fprintf(stderr, "ok\n");
	return output;
}


