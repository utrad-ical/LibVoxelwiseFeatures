
#include "VOL.h"

#include "Hu3DMomentInvariants.h"
#include "../Utilities/Check3DPositionedVoxelValuePresense.h"
#include "../Utilities/SetIntRadInVolKernel.h"


VOL_RAWVOLUMEDATA* GetVolumeOfHu3DMomentInvariants(
	VOL_RAWVOLUMEDATA* volume, int channel, VOL_RAWVOLUMEDATA* mask, int mch, VOL_KERNEL* kernel)
{
	VOL_INTSIZE3D* orgsz = VOL_GetIntSize3DFromIntSize4D(volume->matrixSize);

	VOL_RAWVOLUMEDATA* outvolume = VOL_NewSingleChannelRawVolumeData(orgsz, VOL_VALUEUNIT_FLOAT32, VOL_VALUETYPE_SINGLE);
	for(int i=1; i<NUM_HU_3D_MOMENT_INVARIANTS; i++) {
		VOL_AddNewChannelInRawVolumeData(outvolume, VOL_VALUEUNIT_FLOAT32, VOL_VALUETYPE_SINGLE);
	}

	int margin = SetIntRadInVolKernel(kernel);
	kernel->intRad = margin;
	VOL_AttachOffsetXYZ(volume, margin, VOL_RESIZE_BACKGROUNDTYPE_BORDERCOPY_UNIFORM);

	float**** outvol = (float****)outvolume->array4D;

	VOL_INTVECTOR3D p_org, p_add;

	for(p_org.z=0; p_org.z<orgsz->depth; p_org.z++) {

		p_add.z = p_org.z+margin;

		for(p_org.y=0; p_org.y<orgsz->height; p_org.y++) {

			p_add.y = p_org.y+margin;

			for(p_org.x=0; p_org.x<orgsz->width; p_org.x++) {
			if(Check3DPositionedVoxelValuePresense(mask, mch, &p_org)) {

				p_add.x = p_org.x+margin;

				HU3DMOMENTINVARIANTS invs = CalculateHu3DMomentInvariants(volume, channel, &p_add, kernel);

				outvol[0][p_org.z][p_org.y][p_org.x] = invs.J1;
				outvol[1][p_org.z][p_org.y][p_org.x] = invs.J2;
				outvol[2][p_org.z][p_org.y][p_org.x] = invs.delta;
				outvol[3][p_org.z][p_org.y][p_org.x] = invs.I1;
				outvol[4][p_org.z][p_org.y][p_org.x] = invs.I2;
			}}
		}
	}

	VOL_RemoveOffsetXYZ(volume, margin);

	VOL_DeleteIntSize3D(orgsz);

	return outvolume;
}



