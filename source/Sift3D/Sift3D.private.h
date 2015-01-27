

#include "VOL.h"
#include "Sift3D.h"


#define DEP(v)	v->matrixSize->depth
#define HEI(v)	v->matrixSize->height
#define WID(v)	v->matrixSize->width
#define DATSIZE(v)	WID(v)*HEI(v)*DEP(v)


typedef struct _bouding_box_ {
	int top[3], tail[3];
} BOUNDING_BOX;


BOUNDING_BOX BoundingBoxOfSamplePositions(CALCULATINGVOXELS* samples);

float** GetEquallySpacedPointsOnUnitSphere(int num);

