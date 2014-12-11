
#pragma warning(disable: 4996)


#include "Sift3D.h"


void DeleteSift3dFeatures(SIFT3D_FEATURES* data)
{
	delete [] data->feat_array[0];
	delete [] data->feat_array;
	delete data;
}

