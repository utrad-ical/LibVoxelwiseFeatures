
#include "VOL.h"
#include "HaarFeaturesByIntegral.h"
#include "HaarFeaturesByIntegral.private.h"



float CalculateSigngleHaarFeatureInIntBoxByIntegral(INTEGRALVOLUME* integral, VOL_INTBOX3D* box, int index)
{
	VOL_INTVECTOR3D org;	org.x = org.y = org.z = 0;
	VOL_INTSIZE3D* sz = VOL_GetIntSize3DFromIntSize4D(integral->volume->matrixSize);

	VOL_INTBOX3D* boxOrg;
	if(box==NULL)	boxOrg = VOL_NewIntBox3D(&org, sz);
	else			boxOrg = box;

	VOL_DeleteIntSize3D(sz);

	VOL_INTBOX3D* boxProc = VOL_NewIntBox3D(boxOrg->origin, boxOrg->size);


	double feat=0.0;

	switch(index)
	{
	case 0: // x•ûŒü2•ªŠ„
		boxProc->size->width = (int)((float)boxOrg->size->width/2.0f+0.5f);
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->x += boxOrg->size->width/2;
		feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		break;
	case 1: // y•ûŒü2•ªŠ„
		boxProc->size->height = (int)((float)boxOrg->size->height/2.0f+0.5f);
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->y += boxOrg->size->height/2;
		feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		break;
	case 2: // z•ûŒü2•ªŠ„
		boxProc->size->depth = (int)((float)boxOrg->size->depth/2.0f+0.5f);
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->z += boxOrg->size->depth/2;
		feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		break;

	case 3: // x•ûŒü3•ªŠ„
		boxProc->size->width = (int)((float)boxOrg->size->width/3.0f+0.5f);
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->x = boxOrg->origin->x + boxOrg->size->width/3;
		feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->x = boxOrg->origin->x + boxOrg->size->width*2/3;
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		break;
	case 4: // y•ûŒü3•ªŠ„
		boxProc->size->height = (int)((float)boxOrg->size->height/3.0f+0.5f);
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->y = boxOrg->origin->y + boxOrg->size->height/3;
		feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->y = boxOrg->origin->y + boxOrg->size->height*2/3;
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		break;
	case 5: // z•ûŒü3•ªŠ„
		boxProc->size->depth = (int)((float)boxOrg->size->depth/3.0f+0.5f);
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->z = boxOrg->origin->z + boxOrg->size->depth/3;
		feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->z = boxOrg->origin->z + boxOrg->size->depth*2/3;
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		break;

	case 6: // xy–Ê2x2•ªŠ„
		boxProc->size->width = (int)((float)boxOrg->size->width/2.0f+0.5f);
		boxProc->size->height = (int)((float)boxOrg->size->height/2.0f+0.5f);
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->x = boxOrg->origin->x + boxOrg->size->width/2;
		feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->y = boxOrg->origin->y + boxOrg->size->height/2;
		boxProc->origin->x = boxOrg->origin->x;
		feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->x = boxOrg->origin->x + boxOrg->size->width/2;
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		break;
	case 7: // yz–Ê2x2•ªŠ„
		boxProc->size->height = (int)((float)boxOrg->size->height/2.0f+0.5f);
		boxProc->size->depth = (int)((float)boxOrg->size->depth/2.0f+0.5f);
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->y = boxOrg->origin->y + boxOrg->size->height/2;
		feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->y = boxOrg->origin->y;
		boxProc->origin->z = boxOrg->origin->z + boxOrg->size->depth/2;
		feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->y = boxOrg->origin->y + boxOrg->size->height/2;
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		break;
	case 8: // xz–Ê2x2•ªŠ„
		boxProc->size->width = (int)((float)boxOrg->size->width/2.0f+0.5f);
		boxProc->size->depth = (int)((float)boxOrg->size->depth/2.0f+0.5f);
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->z = boxOrg->origin->z + boxOrg->size->depth/2;
		feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->z = boxOrg->origin->z;
		boxProc->origin->x = boxOrg->origin->x + boxOrg->size->width/2;
		feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->z = boxOrg->origin->z + boxOrg->size->depth/2;
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		break;

	case 9: // xy•ûŒü2•ªŠ„
		boxProc->size->width = (int)((float)boxOrg->size->width/2.0f+0.5f);
		boxProc->size->height = (int)((float)boxOrg->size->height/2.0f+0.5f);
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->x = boxOrg->origin->x + boxOrg->size->width/2;
		boxProc->origin->y = boxOrg->origin->y + boxOrg->size->height/2;
		feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		break;
	case 10: // yz•ûŒü2•ªŠ„
		boxProc->size->height = (int)((float)boxOrg->size->height/2.0f+0.5f);
		boxProc->size->depth = (int)((float)boxOrg->size->depth/2.0f+0.5f);
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->y = boxOrg->origin->y + boxOrg->size->height/2;
		boxProc->origin->z = boxOrg->origin->z + boxOrg->size->depth/2;
		feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		break;
	case 11: // zx•ûŒü2•ªŠ„
		boxProc->size->depth = (int)((float)boxOrg->size->depth/2.0f+0.5f);
		boxProc->size->width = (int)((float)boxOrg->size->width/2.0f+0.5f);
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->z = boxOrg->origin->z + boxOrg->size->depth/2;
		boxProc->origin->x = boxOrg->origin->x + boxOrg->size->width/2;
		feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		break;

	case 12: // x(-y)•ûŒü2•ªŠ„
		boxProc->size->width = (int)((float)boxOrg->size->width/2.0f+0.5f);
		boxProc->size->height = (int)((float)boxOrg->size->height/2.0f+0.5f);
		boxProc->origin->x = boxOrg->origin->x + boxOrg->size->width/2;
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->x = boxOrg->origin->x;
		boxProc->origin->y = boxOrg->origin->y + boxOrg->size->height/2;
		feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		break;
	case 13: // y(-z)•ûŒü2•ªŠ„
		boxProc->size->height = (int)((float)boxOrg->size->height/2.0f+0.5f);
		boxProc->size->depth = (int)((float)boxOrg->size->depth/2.0f+0.5f);
		boxProc->origin->y = boxOrg->origin->y + boxOrg->size->height/2;
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->y = boxOrg->origin->y;
		boxProc->origin->z = boxOrg->origin->z + boxOrg->size->depth/2;
		feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		break;
	case 14: // z(-x)•ûŒü2•ªŠ„
		boxProc->size->depth = (int)((float)boxOrg->size->depth/2.0f+0.5f);
		boxProc->size->width = (int)((float)boxOrg->size->width/2.0f+0.5f);
		boxProc->origin->z = boxOrg->origin->z + boxOrg->size->depth/2;
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->z = boxOrg->origin->z;
		boxProc->origin->x = boxOrg->origin->x + boxOrg->size->width/2;
		feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		break;

	case 15: // xyz•ûŒü2•ªŠ„
		boxProc->size->width = (int)((float)boxOrg->size->width/2.0f+0.5f);
		boxProc->size->height = (int)((float)boxOrg->size->height/2.0f+0.5f);
		boxProc->size->depth = (int)((float)boxOrg->size->depth/2.0f+0.5f);
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->x = boxOrg->origin->x + boxOrg->size->width/2;
		boxProc->origin->y = boxOrg->origin->y + boxOrg->size->height/2;
		boxProc->origin->z = boxOrg->origin->z + boxOrg->size->depth/2;
		feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		break;

	case 16: // (-x)yz•ûŒü2•ªŠ„
		boxProc->size->width = (int)((float)boxOrg->size->width/2.0f+0.5f);
		boxProc->size->height = (int)((float)boxOrg->size->height/2.0f+0.5f);
		boxProc->size->depth = (int)((float)boxOrg->size->depth/2.0f+0.5f);
		boxProc->origin->x = boxOrg->origin->x + boxOrg->size->width/2;
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->x = boxOrg->origin->x;
		boxProc->origin->y = boxOrg->origin->y + boxOrg->size->height/2;
		boxProc->origin->z = boxOrg->origin->z + boxOrg->size->depth/2;
		feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		break;
	case 17: // x(-y)z•ûŒü2•ªŠ„
		boxProc->size->width = (int)((float)boxOrg->size->width/2.0f+0.5f);
		boxProc->size->height = (int)((float)boxOrg->size->height/2.0f+0.5f);
		boxProc->size->depth = (int)((float)boxOrg->size->depth/2.0f+0.5f);
		boxProc->origin->y = boxOrg->origin->y + boxOrg->size->height/2;
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->x = boxOrg->origin->x + boxOrg->size->width/2;
		boxProc->origin->y = boxOrg->origin->y;
		boxProc->origin->z = boxOrg->origin->z + boxOrg->size->depth/2;
		feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		break;
	case 18: // xy(-z)•ûŒü2•ªŠ„
		boxProc->size->width = (int)((float)boxOrg->size->width/2.0f+0.5f);
		boxProc->size->height = (int)((float)boxOrg->size->height/2.0f+0.5f);
		boxProc->size->depth = (int)((float)boxOrg->size->depth/2.0f+0.5f);
		boxProc->origin->z = boxOrg->origin->z + boxOrg->size->depth/2;
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->x = boxOrg->origin->x + boxOrg->size->width/2;
		boxProc->origin->y = boxOrg->origin->y + boxOrg->size->height/2;
		boxProc->origin->z = boxOrg->origin->z;
		feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		break;

	case 19: // (-x)(-y)z•ûŒü2•ªŠ„
		boxProc->size->width = (int)((float)boxOrg->size->width/2.0f+0.5f);
		boxProc->size->height = (int)((float)boxOrg->size->height/2.0f+0.5f);
		boxProc->size->depth = (int)((float)boxOrg->size->depth/2.0f+0.5f);
		boxProc->origin->x = boxOrg->origin->x + boxOrg->size->width/2;
		boxProc->origin->y = boxOrg->origin->y + boxOrg->size->height/2;
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->x = boxOrg->origin->x;
		boxProc->origin->y = boxOrg->origin->y;
		boxProc->origin->z = boxOrg->origin->z + boxOrg->size->depth/2;
		feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		break;
	case 20: // x(-y)(-z)•ûŒü2•ªŠ„
		boxProc->size->width = (int)((float)boxOrg->size->width/2.0f+0.5f);
		boxProc->size->height = (int)((float)boxOrg->size->height/2.0f+0.5f);
		boxProc->size->depth = (int)((float)boxOrg->size->depth/2.0f+0.5f);
		boxProc->origin->y = boxOrg->origin->y + boxOrg->size->height/2;
		boxProc->origin->z = boxOrg->origin->z + boxOrg->size->depth/2;
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->x = boxOrg->origin->x + boxOrg->size->width/2;
		boxProc->origin->y = boxOrg->origin->y;
		boxProc->origin->z = boxOrg->origin->z;
		feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		break;
	case 21: // (-x)y(-z)•ûŒü2•ªŠ„
		boxProc->size->width = (int)((float)boxOrg->size->width/2.0f+0.5f);
		boxProc->size->height = (int)((float)boxOrg->size->height/2.0f+0.5f);
		boxProc->size->depth = (int)((float)boxOrg->size->depth/2.0f+0.5f);
		boxProc->origin->x = boxOrg->origin->x + boxOrg->size->width/2;
		boxProc->origin->z = boxOrg->origin->z + boxOrg->size->depth/2;
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->x = boxOrg->origin->x;
		boxProc->origin->y = boxOrg->origin->y + boxOrg->size->height/2;
		boxProc->origin->z = boxOrg->origin->z;
		feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		break;
	}
	
	if(box==NULL)	VOL_DeleteIntBox3D(boxOrg);
	VOL_DeleteIntBox3D(boxProc);

	return (float)feat;
}

/*
float* CalculateHaarFeaturesByIntegralVolume(VOL_RAWVOLUMEDATA* volume, int chIntegral, VOL_INTBOX3D* box)
{
	float* output = new float [NUM_TYPICAL_HAAR_FEATURES];

	for(int i=0; i<NUM_TYPICAL_HAAR_FEATURES; i++) {
		output[i] = CalculateSigngleHaarFeaturesByIntegralVolume(volume, chIntegral, box, i);
	}

	return output;
}
*/



