

#include "Hu3DMomentInvariants.h"
#include "Hu3DMomentInvariants.private.h"


HU3DMOMENTINVARIANTS CalculateHu3DMomentInvariants(VOL_RAWVOLUMEDATA* volume, int channel, VOL_INTVECTOR3D* coord, VOL_KERNEL* roi)
{
	HU3DMOMENTS hu3d = CalculateHu3DMoments(volume, channel, coord, roi);

	float* invariants = CalculateInvariantsFromHu3DMoments(&hu3d);

	HU3DMOMENTINVARIANTS out;
	out.J1 = invariants[0];
	out.J2 = invariants[1];
	out.delta = invariants[2];
	out.I1 = invariants[3];
	out.I2 = invariants[4];

	delete [] invariants;

	return out;
}



