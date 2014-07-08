
#include "VOL.h"
#include "HaarFeaturesByIntegral.h"
#include "HaarFeaturesByIntegral.private.h"

#include "../Utilities/SumIntensityOfVoxelsInIntBoxByIntegral.h"


float* CalculateMultiHaarFeatureByIntegral(INTEGRALVOLUME* integral, VOL_INTVECTOR3D* coord, VOL_KERNEL* roi)
{
	float* feats = new float [NUM_HAAR_FEATURES];

	VOL_INTBOX3D* box = BoundingBoxOfVolKernel(coord, roi);

	/*
	int index=0;
	{
		VOL_INTVECTOR3D org;	org.x = org.y = org.z = 0;
		VOL_INTSIZE3D* sz = VOL_GetIntSize3DFromIntSize4D(integral->volume->matrixSize);

		VOL_INTBOX3D* boxOrg;
		if(box==NULL)	boxOrg = VOL_NewIntBox3D(&org, sz);
		else			boxOrg = box;

		VOL_DeleteIntSize3D(sz);

	//	VOL_INTBOX3D* boxProc = VOL_NewIntBox3D(boxOrg->origin, boxOrg->size);
		VOL_INTBOX3D* boxProc;

		double feat=0.0;
	//	double f1, f2, f3;

		// index=0: x•ûŒü2•ªŠ„
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
		boxProc->size->width = (int)((float)boxOrg->size->width/2.0f+0.5f);
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->x += boxOrg->size->width/2;
		feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		feats[index++] = (float)feat;
		VOL_DeleteIntBox3D(boxProc);

		// index=1: y•ûŒü2•ªŠ„
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
		boxProc->size->height = (int)((float)boxOrg->size->height/2.0f+0.5f);
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->y += boxOrg->size->height/2;
		feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		feats[index++] = (float)feat;
		VOL_DeleteIntBox3D(boxProc);

		// index=2: z•ûŒü2•ªŠ„
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
		boxProc->size->depth = (int)((float)boxOrg->size->depth/2.0f+0.5f);
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->z += boxOrg->size->depth/2;
		feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		feats[index++] = (float)feat;
		VOL_DeleteIntBox3D(boxProc);

		// index=3: x•ûŒü3•ªŠ„
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
		boxProc->size->width = (int)((float)boxOrg->size->width/3.0f+0.5f);
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->x = boxOrg->origin->x + boxOrg->size->width/3;
		feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->x = boxOrg->origin->x + boxOrg->size->width*2/3;
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		feats[index++] = (float)feat;
		VOL_DeleteIntBox3D(boxProc);

		// index=4: y•ûŒü3•ªŠ„
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
		boxProc->size->height = (int)((float)boxOrg->size->height/3.0f+0.5f);
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->y = boxOrg->origin->y + boxOrg->size->height/3;
		feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->y = boxOrg->origin->y + boxOrg->size->height*2/3;
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		feats[index++] = (float)feat;
		VOL_DeleteIntBox3D(boxProc);

		// index=5: z•ûŒü3•ªŠ„
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
		boxProc->size->depth = (int)((float)boxOrg->size->depth/3.0f+0.5f);
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->z = boxOrg->origin->z + boxOrg->size->depth/3;
		feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		boxProc->origin->z = boxOrg->origin->z + boxOrg->size->depth*2/3;
		feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		feats[index++] = (float)feat;
		VOL_DeleteIntBox3D(boxProc);

		// index=6: xy–Ê2x2•ªŠ„
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
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
		feats[index++] = (float)feat;
		VOL_DeleteIntBox3D(boxProc);

		// index=7: yz–Ê2x2•ªŠ„
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
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
		feats[index++] = (float)feat;
		VOL_DeleteIntBox3D(boxProc);

		// index=8: xz–Ê2x2•ªŠ„
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
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
		feats[index++] = (float)feat;
		VOL_DeleteIntBox3D(boxProc);

		// index=9: xy•ûŒü2•ªŠ„
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
			boxProc->size->width = (int)((float)boxOrg->size->width/2.0f+0.5f);
			boxProc->size->height = (int)((float)boxOrg->size->height/2.0f+0.5f);
			feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
			boxProc->origin->x = boxOrg->origin->x + boxOrg->size->width/2;
			boxProc->origin->y = boxOrg->origin->y + boxOrg->size->height/2;
			feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		feats[index++] = (float)feat;
		VOL_DeleteIntBox3D(boxProc);

		// index=10: yz•ûŒü2•ªŠ„
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
			boxProc->size->height = (int)((float)boxOrg->size->height/2.0f+0.5f);
			boxProc->size->depth = (int)((float)boxOrg->size->depth/2.0f+0.5f);
			feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
			boxProc->origin->y = boxOrg->origin->y + boxOrg->size->height/2;
			boxProc->origin->z = boxOrg->origin->z + boxOrg->size->depth/2;
			feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
		feats[index++] = (float)feat;
		VOL_DeleteIntBox3D(boxProc);

		// index=11: zx•ûŒü2•ªŠ„
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
		feats[index++] = (float)feat;
		VOL_DeleteIntBox3D(boxProc);

		// index=12: 
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
		feats[index++] = (float)feat;
		VOL_DeleteIntBox3D(boxProc);

		// index=13: 
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
		feats[index++] = (float)feat;
		VOL_DeleteIntBox3D(boxProc);

		// index=14: 
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
		feats[index++] = (float)feat;
		VOL_DeleteIntBox3D(boxProc);

		// index=15: 
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
		feats[index++] = (float)feat;
		VOL_DeleteIntBox3D(boxProc);

		// index=16: 
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
		feats[index++] = (float)feat;
		VOL_DeleteIntBox3D(boxProc);

		// index=17: 
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
		feats[index++] = (float)feat;
		VOL_DeleteIntBox3D(boxProc);

		// index=18: 
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
		feats[index++] = (float)feat;
		VOL_DeleteIntBox3D(boxProc);

		// index=19: 
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
		feats[index++] = (float)feat;
		VOL_DeleteIntBox3D(boxProc);

		// index=20: 
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
		feats[index++] = (float)feat;
		VOL_DeleteIntBox3D(boxProc);

		// index=21: 
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
		feats[index++] = (float)feat;
		VOL_DeleteIntBox3D(boxProc);

		// index=x: 
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
		feats[index++] = (float)feat;
		VOL_DeleteIntBox3D(boxProc);

		// index=x: 
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
		feats[index++] = (float)feat;
		VOL_DeleteIntBox3D(boxProc);



		{
		// case 0: // x•ûŒü2•ªŠ„
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
			boxProc->size->width = (int)((float)boxOrg->size->width/2.0f+0.5f);
			feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
			boxProc->origin->x += boxOrg->size->width/2;
			feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
			break;
		// case 1: // y•ûŒü2•ªŠ„
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
			boxProc->size->height = (int)((float)boxOrg->size->height/2.0f+0.5f);
			feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
			boxProc->origin->y += boxOrg->size->height/2;
			feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
			break;
		// case 2: // z•ûŒü2•ªŠ„
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
			boxProc->size->depth = (int)((float)boxOrg->size->depth/2.0f+0.5f);
			feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
			boxProc->origin->z += boxOrg->size->depth/2;
			feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
			break;

		// case 3: // x•ûŒü3•ªŠ„
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
			boxProc->size->width = (int)((float)boxOrg->size->width/3.0f+0.5f);
			feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
			boxProc->origin->x = boxOrg->origin->x + boxOrg->size->width/3;
			feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
			boxProc->origin->x = boxOrg->origin->x + boxOrg->size->width*2/3;
			feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
			break;
		// case 4: // y•ûŒü3•ªŠ„
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
			boxProc->size->height = (int)((float)boxOrg->size->height/3.0f+0.5f);
			feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
			boxProc->origin->y = boxOrg->origin->y + boxOrg->size->height/3;
			feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
			boxProc->origin->y = boxOrg->origin->y + boxOrg->size->height*2/3;
			feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
			break;
		// case 5: // z•ûŒü3•ªŠ„
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
			boxProc->size->depth = (int)((float)boxOrg->size->depth/3.0f+0.5f);
			feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
			boxProc->origin->z = boxOrg->origin->z + boxOrg->size->depth/3;
			feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
			boxProc->origin->z = boxOrg->origin->z + boxOrg->size->depth*2/3;
			feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
			break;

		// case 6: // xy–Ê2x2•ªŠ„
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
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
		// case 7: // yz–Ê2x2•ªŠ„
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
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
		//case 8: // xz–Ê2x2•ªŠ„
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
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

		// case 9: // xy•ûŒü2•ªŠ„
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
			boxProc->size->width = (int)((float)boxOrg->size->width/2.0f+0.5f);
			boxProc->size->height = (int)((float)boxOrg->size->height/2.0f+0.5f);
			feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
			boxProc->origin->x = boxOrg->origin->x + boxOrg->size->width/2;
			boxProc->origin->y = boxOrg->origin->y + boxOrg->size->height/2;
			feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
			break;
		//case 10: // yz•ûŒü2•ªŠ„
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
			boxProc->size->height = (int)((float)boxOrg->size->height/2.0f+0.5f);
			boxProc->size->depth = (int)((float)boxOrg->size->depth/2.0f+0.5f);
			feat -= SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
			boxProc->origin->y = boxOrg->origin->y + boxOrg->size->height/2;
			boxProc->origin->z = boxOrg->origin->z + boxOrg->size->depth/2;
			feat += SumIntensityOfVoxelsInIntBoxByIntegral(integral, boxProc);
			break;
		//case 11: // zx•ûŒü2•ªŠ„
		feat=0.0;
		boxProc = VOL_DuplicateIntBox3D(boxOrg);
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
	}
	*/


	for(int i=0; i<NUM_HAAR_FEATURES; i++) {
		feats[i] = (float)CalculateSigngleHaarFeatureInIntBoxByIntegral(integral, box, i);
	}

	VOL_DeleteIntBox3D(box);

	return feats;
}

