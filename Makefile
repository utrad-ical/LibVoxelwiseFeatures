# Makefile

LIB = libVoxelwiseFeatures-1.0.a

SRC_CURVATURE     = source/CurvatureFeatures/
SRC_HAAR_INTEGRAL = source/HaarFeaturesByIntegral/
SRC_HAAR          = source/HaarFeatures/
SRC_HARALICK      = source/HaralickFeatures/
SRC_HU3D          = source/Hu3DMomentInvariants/
SRC_SIFT3D        = source/Sift3D/
SRC_UTILITIES     = source/Utilities/
SRC_VOXEL_STAT    = source/VoxelValueStatistics/

DST_HEADDER = /usr/include/libVoxelwiseFeatures-1.0/

#----------------------------------------------------------------------------
#       Macros
#----------------------------------------------------------------------------
AR            = ar
CXX           = g++
CXXFLAGS      = -c -O2 -I"/usr/include/libVOL-1.2" -lpthread
OBJEXT        = .o
RM            = rm -rf
OBJS          = $(SRC_CURVATURE)CalculateCurvatureFeatures.o $(SRC_CURVATURE)CalculateCurvatureFeaturesAtMultiPositions_MT.o $(SRC_CURVATURE)Curvatures.o $(SRC_CURVATURE)GetVolumeOfCurvatureFeatures.o $(SRC_CURVATURE)GetVolumeOfCurvatureFeatures_MT.o $(SRC_HAAR_INTEGRAL)CalculateMultiHaarFeatureByIntegral.o $(SRC_HAAR_INTEGRAL)CalculateMultiHaarFeatureByIntegral_forVoxelSubset.o $(SRC_HAAR_INTEGRAL)CalculateMultiHaarFeaturesAtMultiPositionsByIntegral_MT.o $(SRC_HAAR_INTEGRAL)CalculateMultiHaarFeaturesAtVoxelsByIntegral.o $(SRC_HAAR_INTEGRAL)CalculateSigngleHaarFeatureByIntegral.o $(SRC_HAAR_INTEGRAL)CalculateSigngleHaarFeatureInIntBoxByIntegral.o $(SRC_HAAR_INTEGRAL)GetVolumeOfMultiHaarFeaturesByIntegral.o $(SRC_HAAR_INTEGRAL)GetVolumeOfMultiHaarFeaturesByIntegral_MT.o $(SRC_HAAR_INTEGRAL)GetVolumeOfMultiHaarFeaturesFromIntegral_MT.o $(SRC_HAAR_INTEGRAL)GetVolumeOfSingleHaarFeatureByIntegral.o $(SRC_HAAR_INTEGRAL)GetVolumeOfSingleHaarFeatureByIntegral_MT.o $(SRC_HAAR)CalculateMultiHaarFeatures.o $(SRC_HAAR)CalculateSingleHaarFeatureInIntBox.o $(SRC_HAAR)CalculateSingleHaarFeature.o $(SRC_HAAR)GetVolumeOfMultiHaarFeatures.o $(SRC_HAAR)GetVolumeOfMultiHaarFeatures_MT.o $(SRC_HAAR)GetVolumeOfSingleHaarFeature.o $(SRC_HAAR)GetVolumeOfSingleHaarFeature_MT.o $(SRC_HARALICK)CalculateCoOccurenceMatrix.o $(SRC_HARALICK)CalculateHaralickFeatures.o $(SRC_HARALICK)CalculateHaralickFeaturesFromCoOccurenceMatrix.o $(SRC_HARALICK)GetVolumeOfHaralickFeatures.o $(SRC_HARALICK)GetVolumeOfHaralickFeatures_MT.o $(SRC_HARALICK)NewDeleteVolumeHaralickCalculation.o $(SRC_HU3D)CalculateHu3DMomentInvariants.o $(SRC_HU3D)CalculateHu3DMomentInvariantsAtMultiPositions_MT.o $(SRC_HU3D)CalculateInvariantsFromHu3DMoments.o $(SRC_HU3D)CalculateHu3DMoments.o $(SRC_HU3D)GetVolumeOfHu3DMomentInvariants.o $(SRC_HU3D)GetVolumeOfHu3DMomentInvariants_MT.o $(SRC_SIFT3D)CalculateSift3D_MultiPositions.o $(SRC_SIFT3D)CalculateSift3D_MultiPositions_MT.o $(SRC_SIFT3D)CalculateSift3D_SinglePosition.o $(SRC_SIFT3D)DeleteSift3dFeatures.o $(SRC_SIFT3D)NewSift3dFeatures.o $(SRC_SIFT3D)VolumeOfSift3D.o $(SRC_SIFT3D)VolumeOfSift3D_MT.o $(SRC_UTILITIES)AddOffsetToVoxelValue.o $(SRC_UTILITIES)CalculatingVoxels_AttachOffsetXYZ.o $(SRC_UTILITIES)BoundingBoxOfVolKernel.o $(SRC_UTILITIES)ConvertMaskToCalculatingVoxels.o $(SRC_UTILITIES)EigenCalc.o $(SRC_UTILITIES)SetIntRadInVolKernel.o $(SRC_UTILITIES)SumIntensityOfGivenVoxels.o $(SRC_UTILITIES)CalculatingVoxels.o $(SRC_UTILITIES)CheckRasterPositionedVoxelValuePresense.o $(SRC_UTILITIES)Check3DPositionedVoxelValuePresense.o $(SRC_UTILITIES)ConvertIntBoxToLasterPosition.o $(SRC_UTILITIES)DividedCalculatingVoxels.o $(SRC_UTILITIES)GetMinMaxOfVoxelValue.o $(SRC_UTILITIES)IntegralVolume.o $(SRC_UTILITIES)SumIntensityOfVoxelsInIntBox.o $(SRC_UTILITIES)SumIntensityOfVoxelsInIntBoxByIntegral.o $(SRC_VOXEL_STAT)CalculateVoxelValueStatistics.o $(SRC_VOXEL_STAT)CalculateVoxelValueStatisticsAtMultiPositions_MT.o $(SRC_VOXEL_STAT)MemorySetOfVoxelValueStatisticsAtMultiPositions.o $(SRC_VOXEL_STAT)GetVolumeOfVoxelValueStatistics.o $(SRC_VOXEL_STAT)GetVolumeOfVoxelValueStatistics_MT.o $(SRC_VOXEL_STAT)SetCalculatedStatisticsAsVoxelValue.o


#----------------------------------------------------------------------------
#       Implicit rules
#----------------------------------------------------------------------------
.SUFFIXES: .cxx .cpp .c

.cxx.o:
	$(CXX) $(CXXFLAGS) -o $@ $^

.cpp.o:
	$(CXX) $(CXXFLAGS) -o $@ $^

.c.o:
	$(CXX) $(CXXFLAGS) -o $@ $^


#----------------------------------------------------------------------------
#       Local targets
#----------------------------------------------------------------------------

all: $(LIB)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $(LIB) $(OBJS)

$(SRC_CURVATURE)CalculateCurvatureFeatures.o: $(SRC_CURVATURE)CalculateCurvatureFeatures.cpp
$(SRC_CURVATURE)CalculateCurvatureFeaturesAtMultiPositions_MT.o:                $(SRC_CURVATURE)CalculateCurvatureFeaturesAtMultiPositions_MT.cpp
$(SRC_CURVATURE)Curvatures.o:                                                   $(SRC_CURVATURE)Curvatures.cpp
$(SRC_CURVATURE)GetVolumeOfCurvatureFeatures.o:                                 $(SRC_CURVATURE)GetVolumeOfCurvatureFeatures.cpp
$(SRC_CURVATURE)GetVolumeOfCurvatureFeatures_MT.o:                              $(SRC_CURVATURE)GetVolumeOfCurvatureFeatures_MT.cpp
$(SRC_HAAR_INTEGRAL)CalculateMultiHaarFeatureByIntegral.o:                      $(SRC_HAAR_INTEGRAL)CalculateMultiHaarFeatureByIntegral.cpp
$(SRC_HAAR_INTEGRAL)CalculateMultiHaarFeatureByIntegral_forVoxelSubset.o:       $(SRC_HAAR_INTEGRAL)CalculateMultiHaarFeatureByIntegral_forVoxelSubset.cpp
$(SRC_HAAR_INTEGRAL)CalculateMultiHaarFeaturesAtMultiPositionsByIntegral_MT.o:  $(SRC_HAAR_INTEGRAL)CalculateMultiHaarFeaturesAtMultiPositionsByIntegral_MT.cpp
$(SRC_HAAR_INTEGRAL)CalculateMultiHaarFeaturesAtVoxelsByIntegral.o:             $(SRC_HAAR_INTEGRAL)CalculateMultiHaarFeaturesAtVoxelsByIntegral.cpp
$(SRC_HAAR_INTEGRAL)CalculateSigngleHaarFeatureByIntegral.o:                    $(SRC_HAAR_INTEGRAL)CalculateSigngleHaarFeatureByIntegral.cpp
$(SRC_HAAR_INTEGRAL)CalculateSigngleHaarFeatureInIntBoxByIntegral.o:            $(SRC_HAAR_INTEGRAL)CalculateSigngleHaarFeatureInIntBoxByIntegral.cpp
$(SRC_HAAR_INTEGRAL)GetVolumeOfMultiHaarFeaturesByIntegral.o:                   $(SRC_HAAR_INTEGRAL)GetVolumeOfMultiHaarFeaturesByIntegral.cpp
$(SRC_HAAR_INTEGRAL)GetVolumeOfMultiHaarFeaturesByIntegral_MT.o:                $(SRC_HAAR_INTEGRAL)GetVolumeOfMultiHaarFeaturesByIntegral_MT.cpp
$(SRC_HAAR_INTEGRAL)GetVolumeOfMultiHaarFeaturesFromIntegral_MT.o:              $(SRC_HAAR_INTEGRAL)GetVolumeOfMultiHaarFeaturesFromIntegral_MT.cpp
$(SRC_HAAR_INTEGRAL)GetVolumeOfSingleHaarFeatureByIntegral.o:                   $(SRC_HAAR_INTEGRAL)GetVolumeOfSingleHaarFeatureByIntegral.cpp
$(SRC_HAAR_INTEGRAL)GetVolumeOfSingleHaarFeatureByIntegral_MT.o:                $(SRC_HAAR_INTEGRAL)GetVolumeOfSingleHaarFeatureByIntegral_MT.cpp
$(SRC_HAAR)CalculateMultiHaarFeatures.o:                                        $(SRC_HAAR)CalculateMultiHaarFeatures.cpp
$(SRC_HAAR)CalculateSingleHaarFeatureInIntBox.o:                                $(SRC_HAAR)CalculateSingleHaarFeatureInIntBox.cpp
$(SRC_HAAR)CalculateSingleHaarFeature.o:                                        $(SRC_HAAR)CalculateSingleHaarFeature.cpp
$(SRC_HAAR)GetVolumeOfMultiHaarFeatures.o:                                      $(SRC_HAAR)GetVolumeOfMultiHaarFeatures.cpp
$(SRC_HAAR)GetVolumeOfMultiHaarFeatures_MT.o:                                   $(SRC_HAAR)GetVolumeOfMultiHaarFeatures_MT.cpp
$(SRC_HAAR)GetVolumeOfSingleHaarFeature.o:                                      $(SRC_HAAR)GetVolumeOfSingleHaarFeature.cpp
$(SRC_HAAR)GetVolumeOfSingleHaarFeature_MT.o:                                   $(SRC_HAAR)GetVolumeOfSingleHaarFeature_MT.cpp
$(SRC_HARALICK)CalculateCoOccurenceMatrix.o:                                    $(SRC_HARALICK)CalculateCoOccurenceMatrix.cpp
$(SRC_HARALICK)CalculateHaralickFeatures.o:                                     $(SRC_HARALICK)CalculateHaralickFeatures.cpp
$(SRC_HARALICK)CalculateHaralickFeaturesFromCoOccurenceMatrix.o:                $(SRC_HARALICK)CalculateHaralickFeaturesFromCoOccurenceMatrix.cpp
$(SRC_HARALICK)GetVolumeOfHaralickFeatures.o:                                   $(SRC_HARALICK)GetVolumeOfHaralickFeatures.cpp
$(SRC_HARALICK)GetVolumeOfHaralickFeatures_MT.o:                                $(SRC_HARALICK)GetVolumeOfHaralickFeatures_MT.cpp
$(SRC_HARALICK)NewDeleteVolumeHaralickCalculation.o:                            $(SRC_HARALICK)NewDeleteVolumeHaralickCalculation.cpp
$(SRC_HU3D)CalculateHu3DMomentInvariants.o:                                     $(SRC_HU3D)CalculateHu3DMomentInvariants.cpp
$(SRC_HU3D)CalculateHu3DMomentInvariantsAtMultiPositions_MT.o:                  $(SRC_HU3D)CalculateHu3DMomentInvariantsAtMultiPositions_MT.cpp
$(SRC_HU3D)CalculateInvariantsFromHu3DMoments.o:                                $(SRC_HU3D)CalculateInvariantsFromHu3DMoments.cpp
$(SRC_HU3D)CalculateHu3DMoments.o:                                              $(SRC_HU3D)CalculateHu3DMoments.cpp
$(SRC_HU3D)GetVolumeOfHu3DMomentInvariants.o:                                   $(SRC_HU3D)GetVolumeOfHu3DMomentInvariants.cpp
$(SRC_HU3D)GetVolumeOfHu3DMomentInvariants_MT.o:                                $(SRC_HU3D)GetVolumeOfHu3DMomentInvariants_MT.cpp
$(SRC_SIFT3D)CalculateSift3D_MultiPositions.o:                                  $(SRC_SIFT3D)CalculateSift3D_MultiPositions.cpp
$(SRC_SIFT3D)CalculateSift3D_MultiPositions_MT.o:                               $(SRC_SIFT3D)CalculateSift3D_MultiPositions_MT.cpp
$(SRC_SIFT3D)CalculateSift3D_SinglePosition.o:                                  $(SRC_SIFT3D)CalculateSift3D_SinglePosition.cpp
$(SRC_SIFT3D)DeleteSift3dFeatures.o:                                            $(SRC_SIFT3D)DeleteSift3dFeatures.cpp
$(SRC_SIFT3D)NewSift3dFeatures.o:                                               $(SRC_SIFT3D)NewSift3dFeatures.cpp
$(SRC_SIFT3D)VolumeOfSift3D.o:                                                  $(SRC_SIFT3D)VolumeOfSift3D.cpp
$(SRC_SIFT3D)VolumeOfSift3D_MT.o:                                               $(SRC_SIFT3D)VolumeOfSift3D_MT.cpp
$(SRC_UTILITIES)AddOffsetToVoxelValue.o:                                        $(SRC_UTILITIES)AddOffsetToVoxelValue.cpp
$(SRC_UTILITIES)CalculatingVoxels_AttachOffsetXYZ.o:                            $(SRC_UTILITIES)CalculatingVoxels_AttachOffsetXYZ.cpp
$(SRC_UTILITIES)BoundingBoxOfVolKernel.o:                                       $(SRC_UTILITIES)BoundingBoxOfVolKernel.cpp
$(SRC_UTILITIES)ConvertMaskToCalculatingVoxels.o:                               $(SRC_UTILITIES)ConvertMaskToCalculatingVoxels.cpp
$(SRC_UTILITIES)EigenCalc.o:                                                    $(SRC_UTILITIES)EigenCalc.cpp
$(SRC_UTILITIES)SetIntRadInVolKernel.o:                                         $(SRC_UTILITIES)SetIntRadInVolKernel.cpp
$(SRC_UTILITIES)SumIntensityOfGivenVoxels.o:                                    $(SRC_UTILITIES)SumIntensityOfGivenVoxels.cpp
$(SRC_UTILITIES)CalculatingVoxels.o:                                            $(SRC_UTILITIES)CalculatingVoxels.cpp
$(SRC_UTILITIES)CheckRasterPositionedVoxelValuePresense.o:                      $(SRC_UTILITIES)CheckRasterPositionedVoxelValuePresense.cpp
$(SRC_UTILITIES)Check3DPositionedVoxelValuePresense.o:                          $(SRC_UTILITIES)Check3DPositionedVoxelValuePresense.cpp
$(SRC_UTILITIES)ConvertIntBoxToLasterPosition.o:                                $(SRC_UTILITIES)ConvertIntBoxToLasterPosition.cpp
$(SRC_UTILITIES)DividedCalculatingVoxels.o:                                     $(SRC_UTILITIES)DividedCalculatingVoxels.cpp
$(SRC_UTILITIES)GetMinMaxOfVoxelValue.o:                                        $(SRC_UTILITIES)GetMinMaxOfVoxelValue.cpp
$(SRC_UTILITIES)IntegralVolume.o:                                               $(SRC_UTILITIES)IntegralVolume.cpp
$(SRC_UTILITIES)SumIntensityOfVoxelsInIntBox.o:                                 $(SRC_UTILITIES)SumIntensityOfVoxelsInIntBox.cpp
$(SRC_UTILITIES)SumIntensityOfVoxelsInIntBoxByIntegral.o:                       $(SRC_UTILITIES)SumIntensityOfVoxelsInIntBoxByIntegral.cpp
$(SRC_VOXEL_STAT)CalculateVoxelValueStatistics.o:                               $(SRC_VOXEL_STAT)CalculateVoxelValueStatistics.cpp
$(SRC_VOXEL_STAT)CalculateVoxelValueStatisticsAtMultiPositions_MT.o:            $(SRC_VOXEL_STAT)CalculateVoxelValueStatisticsAtMultiPositions_MT.cpp
$(SRC_VOXEL_STAT)MemorySetOfVoxelValueStatisticsAtMultiPositions.o:             $(SRC_VOXEL_STAT)MemorySetOfVoxelValueStatisticsAtMultiPositions.cpp
$(SRC_VOXEL_STAT)GetVolumeOfVoxelValueStatistics.o:                             $(SRC_VOXEL_STAT)GetVolumeOfVoxelValueStatistics.cpp
$(SRC_VOXEL_STAT)GetVolumeOfVoxelValueStatistics_MT.o:                          $(SRC_VOXEL_STAT)GetVolumeOfVoxelValueStatistics_MT.cpp
$(SRC_VOXEL_STAT)SetCalculatedStatisticsAsVoxelValue.o:                         $(SRC_VOXEL_STAT)SetCalculatedStatisticsAsVoxelValue.cpp


.PHONY: clean realclean install

clean:
	-$(RM) $(OBJS)

realclean: clean
	-$(RM) $(SHLIB) $(LIB)

install:
	install -m 644 -o root -g root -p $(LIB) /usr/lib
	install -d $(DST_HEADDER)
	install -d $(DST_HEADDER)CurvatureFeatures/
	install -d $(DST_HEADDER)HaarFeatures/
	install -d $(DST_HEADDER)HaarFeaturesByIntegral/
	install -d $(DST_HEADDER)HaralickFeatures/
	install -d $(DST_HEADDER)Hu3DMomentInvariants/
	install -d $(DST_HEADDER)Sift3D/
	install -d $(DST_HEADDER)Utilities/
	install -d $(DST_HEADDER)VoxelValueStatistics/
	install -m 644 -o root -g root -p source/LibVoxelwiseFeatures.h $(DST_HEADDER)
	install -m 644 -o root -g root -p source/CurvatureFeatures/CurvatureFeatures.h $(DST_HEADDER)CurvatureFeatures/
	install -m 644 -o root -g root -p source/CurvatureFeatures/Curvatures.h $(DST_HEADDER)CurvatureFeatures/
	install -m 644 -o root -g root -p source/HaarFeatures/HaarFeatures.h $(DST_HEADDER)HaarFeatures/
	install -m 644 -o root -g root -p source/HaarFeaturesByIntegral/HaarFeaturesByIntegral.h $(DST_HEADDER)HaarFeaturesByIntegral/
	install -m 644 -o root -g root -p source/HaralickFeatures/HaralickFeatures.h $(DST_HEADDER)HaralickFeatures/
	install -m 644 -o root -g root -p source/Hu3DMomentInvariants/Hu3DMomentInvariants.h $(DST_HEADDER)Hu3DMomentInvariants/
	install -m 644 -o root -g root -p source/Sift3D/Sift3D.h $(DST_HEADDER)Sift3D/
	install -m 644 -o root -g root -p source/Utilities/AddOffsetToVoxelValue.h $(DST_HEADDER)Utilities/
	install -m 644 -o root -g root -p source/Utilities/BoundingBoxOfVolKernel.h $(DST_HEADDER)Utilities/
	install -m 644 -o root -g root -p source/Utilities/CalculatingVoxels.h $(DST_HEADDER)Utilities/
	install -m 644 -o root -g root -p source/Utilities/Check3DPositionedVoxelValuePresense.h $(DST_HEADDER)Utilities/
	install -m 644 -o root -g root -p source/Utilities/CheckRasterPositionedVoxelValuePresense.h $(DST_HEADDER)Utilities/
	install -m 644 -o root -g root -p source/Utilities/ConvertIntBoxToLasterPosition.h $(DST_HEADDER)Utilities/
	install -m 644 -o root -g root -p source/Utilities/ConvertMaskToCalculatingVoxels.h $(DST_HEADDER)Utilities/
	install -m 644 -o root -g root -p source/Utilities/DividedCalculatingVoxels.h $(DST_HEADDER)Utilities/
	install -m 644 -o root -g root -p source/Utilities/GetMinMaxOfVoxelValue.h $(DST_HEADDER)Utilities/
	install -m 644 -o root -g root -p source/Utilities/IntegralVolume.h $(DST_HEADDER)Utilities/
	install -m 644 -o root -g root -p source/Utilities/SetIntRadInVolKernel.h $(DST_HEADDER)Utilities/
	install -m 644 -o root -g root -p source/Utilities/SumIntensityOfGivenVoxels.h $(DST_HEADDER)Utilities/
	install -m 644 -o root -g root -p source/Utilities/SumIntensityOfVoxelsInIntBox.h $(DST_HEADDER)Utilities/
	install -m 644 -o root -g root -p source/Utilities/SumIntensityOfVoxelsInIntBoxByIntegral.h $(DST_HEADDER)Utilities/
	install -m 644 -o root -g root -p source/VoxelValueStatistics/VoxelValueStatistics.h $(DST_HEADDER)VoxelValueStatistics/
