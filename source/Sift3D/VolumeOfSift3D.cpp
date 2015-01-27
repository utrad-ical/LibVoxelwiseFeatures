
#pragma warning(disable: 4996)


#include "Sift3D.h"
#include "Sift3D.private.h"


VOL_RAWVOLUMEDATA* VolumeOfSift3D(
	VOL_RAWVOLUMEDATA* volume, int vch, VOL_RAWVOLUMEDATA* mask, int mch, 
	int roi_size, int num_roi_division, int num_angle)
{
	fprintf(stderr, "get_points,");
	CALCULATINGVOXELS* points;
	if(mask!=NULL) {
		points = ConvertMaskToCalculatingVoxels(mask, mch);
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

	fprintf(stderr, "%d,calc_sift,", points->num);
	SIFT_3D_FEATURES* sift_feats = CalculateSift3D_MultiPositions(volume, vch, points, roi_size, num_roi_division, num_angle);

	fprintf(stderr, "out_vol_size,");
	VOL_INTSIZE3D* size3d = VOL_GetIntSize3DFromIntSize4D(volume->matrixSize);

	fprintf(stderr, "out_vol_set,");
	VOL_RAWVOLUMEDATA* output = VOL_NewSingleChannelRawVolumeData(size3d, VOL_VALUEUNIT_FLOAT32, VOL_VALUETYPE_SINGLE);
	for(int i=1; i<sift_feats->n_feats; i++) {
		VOL_AddNewChannelInRawVolumeData(output, VOL_VALUEUNIT_FLOAT32, VOL_VALUETYPE_SINGLE);
	}

	fprintf(stderr, "4d_array,");
	float**** o_vol = new float*** [sift_feats->n_feats];
	for(int i=0; i<sift_feats->n_feats; i++) {
		o_vol[i] = (float***)output->array4D[i];
	}

	fprintf(stderr, "copy,");
	for(int j=0; j<points->num; j++) {
		int x=points->xc[j], y=points->yc[j], z=points->zc[j];
		for(int i=0; i<sift_feats->n_feats; i++) {
			o_vol[i][z][y][x] = sift_feats->feat_array[j][i];
		}
	}

	fprintf(stderr, "delete,");
	DeleteCalculatingVoxels(points);
	DeleteSift3dFeatures(sift_feats);
	VOL_DeleteIntSize3D(size3d);
	delete [] o_vol;

	return output;
}


