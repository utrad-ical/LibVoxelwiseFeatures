

#include "HaarFeatures.h"
#include "HaarFeatures.private.h"


double CalculateSingleHaarFeatureInIntBox(VOL_RAWVOLUMEDATA* volume, int channel, VOL_INTBOX3D* box, int index)
{
	VOL_INTVECTOR3D org;
	org.x = box->origin->x;		org.y = box->origin->y;		org.z = box->origin->z;

	VOL_INTSIZE3D sz;
	sz.width = box->size->width;	sz.height = box->size->height;	sz.depth = box->size->depth;

	VOL_INTBOX3D* tempBox = VOL_NewIntBox3D(&org, &sz); 

	double feat = 0.0;

	switch(index)
	{
	case 0: // x方向2分割
		tempBox->size->width = (int)((float)sz.width/2.0f+0.5f);
	//	tempBox->size->width = sz.width/2;
		feat -= SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		tempBox->origin->x += sz.width/2;
	//	tempBox->origin->x += (int)((float)sz.width/2.0f+0.5f);
		feat += SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		break;
	case 1: // y方向2分割
		tempBox->size->height = (int)((float)sz.height/2.0f+0.5f);
		feat -= SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		tempBox->origin->y += sz.height/2;
		feat += SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		break;
	case 2: // z方向2分割
		tempBox->size->depth = (int)((float)sz.depth/2.0f+0.5f);
		feat -= SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		tempBox->origin->z += sz.depth/2;
		feat += SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		break;

	case 3: // x方向3分割
		tempBox->size->width = (int)((float)sz.width/3.0f+0.5f);
		feat -= SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		tempBox->origin->x = org.x + sz.width/3;
		feat += SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		tempBox->origin->x = org.x + sz.width*2/3;
		feat -= SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		break;
	case 4: // y方向3分割
		tempBox->size->height = (int)((float)sz.height/3.0f+0.5f);
		feat -= SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		tempBox->origin->y = org.y + sz.height/3;
		feat += SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		tempBox->origin->y = org.y + sz.height*2/3;
		feat -= SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		break;
	case 5: // z方向3分割
		tempBox->size->depth = (int)((float)sz.depth/3.0f+0.5f);
		feat -= SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		tempBox->origin->z = org.z + sz.depth/3;
		feat += SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		tempBox->origin->z = org.z + sz.depth*2/3;
		feat -= SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		break;

	case 6: // xy面2x2分割
		tempBox->size->width = (int)((float)sz.width/2.0f+0.5f);
		tempBox->size->height = (int)((float)sz.height/2.0f+0.5f);
		feat -= SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		tempBox->origin->x = org.x + sz.width/2;
		feat += SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		tempBox->origin->y = org.y + sz.height/2;
		tempBox->origin->x = org.x;
		feat += SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		tempBox->origin->x = org.x + sz.width/2;
		feat -= SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		break;
	case 7: // yz面2x2分割
		tempBox->size->height = (int)((float)sz.height/2.0f+0.5f);
		tempBox->size->depth = (int)((float)sz.depth/2.0f+0.5f);
		feat -= SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		tempBox->origin->y = org.y + sz.height/2;
		feat += SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		tempBox->origin->y = org.y;
		tempBox->origin->z = org.z + sz.depth/2;
		feat += SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		tempBox->origin->y = org.y + sz.height/2;
		feat -= SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		break;
	case 8: // xz面2x2分割
		tempBox->size->width = (int)((float)sz.width/2.0f+0.5f);
		tempBox->size->depth = (int)((float)sz.depth/2.0f+0.5f);
		feat -= SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		tempBox->origin->z = org.z + sz.depth/2;
		feat += SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		tempBox->origin->z = org.z;
		tempBox->origin->x = org.x + sz.width/2;
		feat += SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		tempBox->origin->z = org.z + sz.depth/2;
		feat -= SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		break;

	case 9: // xy方向2分割
		tempBox->size->width = (int)((float)sz.width/2.0f+0.5f);
		tempBox->size->height = (int)((float)sz.height/2.0f+0.5f);
		feat -= SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		tempBox->origin->x = org.x + sz.width/2;
		tempBox->origin->y = org.y + sz.height/2;
		feat += SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		break;
	case 10: // yz方向2分割
		tempBox->size->height = (int)((float)sz.height/2.0f+0.5f);
		tempBox->size->depth = (int)((float)sz.depth/2.0f+0.5f);
		feat -= SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		tempBox->origin->y = org.y + sz.height/2;
		tempBox->origin->z = org.z + sz.depth/2;
		feat += SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		break;
	case 11: // zx方向2分割
		tempBox->size->depth = (int)((float)sz.depth/2.0f+0.5f);
		tempBox->size->width = (int)((float)sz.width/2.0f+0.5f);
		feat -= SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		tempBox->origin->z = org.z + sz.depth/2;
		tempBox->origin->x = org.x + sz.width/2;
		feat += SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		break;

	case 12: // x(-y)方向2分割
		tempBox->size->width = (int)((float)sz.width/2.0f+0.5f);
		tempBox->size->height = (int)((float)sz.height/2.0f+0.5f);
		tempBox->origin->x = org.x + sz.width/2;
		feat -= SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		tempBox->origin->x = org.x;
		tempBox->origin->y = org.y + sz.height/2;
		feat += SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		break;
	case 13: // y(-z)方向2分割
		tempBox->size->height = (int)((float)sz.height/2.0f+0.5f);
		tempBox->size->depth = (int)((float)sz.depth/2.0f+0.5f);
		tempBox->origin->y = org.y + sz.height/2;
		feat -= SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		tempBox->origin->y = org.y;
		tempBox->origin->z = org.z + sz.depth/2;
		feat += SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		break;
	case 14: // z(-x)方向2分割
		tempBox->size->depth = (int)((float)sz.depth/2.0f+0.5f);
		tempBox->size->width = (int)((float)sz.width/2.0f+0.5f);
		tempBox->origin->z = org.z + sz.depth/2;
		feat -= SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		tempBox->origin->z = org.z;
		tempBox->origin->x = org.x + sz.width/2;
		feat += SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		break;

	case 15: // xyz方向2分割
		tempBox->size->width = (int)((float)sz.width/2.0f+0.5f);
		tempBox->size->height = (int)((float)sz.height/2.0f+0.5f);
		tempBox->size->depth = (int)((float)sz.depth/2.0f+0.5f);
		feat -= SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		tempBox->origin->x = org.x + sz.width/2;
		tempBox->origin->y = org.y + sz.height/2;
		tempBox->origin->z = org.z + sz.depth/2;
		feat += SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		break;

	case 16: // (-x)yz方向2分割
		tempBox->size->width = (int)((float)sz.width/2.0f+0.5f);
		tempBox->size->height = (int)((float)sz.height/2.0f+0.5f);
		tempBox->size->depth = (int)((float)sz.depth/2.0f+0.5f);
		tempBox->origin->x = org.x + sz.width/2;
		feat -= SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		tempBox->origin->x = org.x;
		tempBox->origin->y = org.y + sz.height/2;
		tempBox->origin->z = org.z + sz.depth/2;
		feat += SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		break;
	case 17: // x(-y)z方向2分割
		tempBox->size->width = (int)((float)sz.width/2.0f+0.5f);
		tempBox->size->height = (int)((float)sz.height/2.0f+0.5f);
		tempBox->size->depth = (int)((float)sz.depth/2.0f+0.5f);
		tempBox->origin->y = org.y + sz.height/2;
		feat -= SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		tempBox->origin->x = org.x + sz.width/2;
		tempBox->origin->y = org.y;
		tempBox->origin->z = org.z + sz.depth/2;
		feat += SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		break;
	case 18: // xy(-z)方向2分割
		tempBox->size->width = (int)((float)sz.width/2.0f+0.5f);
		tempBox->size->height = (int)((float)sz.height/2.0f+0.5f);
		tempBox->size->depth = (int)((float)sz.depth/2.0f+0.5f);
		tempBox->origin->z = org.z + sz.depth/2;
		feat -= SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		tempBox->origin->x = org.x + sz.width/2;
		tempBox->origin->y = org.y + sz.height/2;
		tempBox->origin->z = org.z;
		feat += SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		break;

	/*
	case 19: // (-x)(-y)z方向2分割
		tempBox->size->width = (int)((float)sz.width/2.0f+0.5f);
		tempBox->size->height = (int)((float)sz.height/2.0f+0.5f);
		tempBox->size->depth = (int)((float)sz.depth/2.0f+0.5f);
		tempBox->origin->x = org.x + sz.width/2;
		tempBox->origin->y = org.y + sz.height/2;
		feat -= SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		tempBox->origin->x = org.x;
		tempBox->origin->y = org.y;
		tempBox->origin->z = org.z + sz.depth/2;
		feat += SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		break;
	case 20: // x(-y)(-z)方向2分割
		tempBox->size->width = (int)((float)sz.width/2.0f+0.5f);
		tempBox->size->height = (int)((float)sz.height/2.0f+0.5f);
		tempBox->size->depth = (int)((float)sz.depth/2.0f+0.5f);
		tempBox->origin->y = org.y + sz.height/2;
		tempBox->origin->z = org.z + sz.depth/2;
		feat -= SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		tempBox->origin->x = org.x + sz.width/2;
		tempBox->origin->y = org.y;
		tempBox->origin->z = org.z;
		feat += SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		break;
	case 21: // (-x)y(-z)方向2分割
		tempBox->size->width = (int)((float)sz.width/2.0f+0.5f);
		tempBox->size->height = (int)((float)sz.height/2.0f+0.5f);
		tempBox->size->depth = (int)((float)sz.depth/2.0f+0.5f);
		tempBox->origin->x = org.x + sz.width/2;
		tempBox->origin->z = org.z + sz.depth/2;
		feat -= SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		tempBox->origin->x = org.x;
		tempBox->origin->y = org.y + sz.height/2;
		tempBox->origin->z = org.z;
		feat += SumIntensityOfVoxelsInIntBox(volume, channel, tempBox);
		break;
	*/
	}
	
	VOL_DeleteIntBox3D(tempBox);

	return feat;
}

