# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cole/Desktop/cis410/proj8

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cole/Desktop/cis410/proj8

# Include any dependencies generated for this target.
include CMakeFiles/proj8G.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/proj8G.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/proj8G.dir/flags.make

CMakeFiles/proj8G.dir/proj8G.cxx.o: CMakeFiles/proj8G.dir/flags.make
CMakeFiles/proj8G.dir/proj8G.cxx.o: proj8G.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cole/Desktop/cis410/proj8/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/proj8G.dir/proj8G.cxx.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/proj8G.dir/proj8G.cxx.o -c /home/cole/Desktop/cis410/proj8/proj8G.cxx

CMakeFiles/proj8G.dir/proj8G.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/proj8G.dir/proj8G.cxx.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cole/Desktop/cis410/proj8/proj8G.cxx > CMakeFiles/proj8G.dir/proj8G.cxx.i

CMakeFiles/proj8G.dir/proj8G.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/proj8G.dir/proj8G.cxx.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cole/Desktop/cis410/proj8/proj8G.cxx -o CMakeFiles/proj8G.dir/proj8G.cxx.s

# Object files for target proj8G
proj8G_OBJECTS = \
"CMakeFiles/proj8G.dir/proj8G.cxx.o"

# External object files for target proj8G
proj8G_EXTERNAL_OBJECTS =

proj8G: CMakeFiles/proj8G.dir/proj8G.cxx.o
proj8G: CMakeFiles/proj8G.dir/build.make
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkWrappingTools-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkViewsInfovis-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkViewsContext2D-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkTestingRendering-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkRenderingVolumeOpenGL2-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkRenderingLabel-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkRenderingLOD-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkRenderingImage-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkRenderingContextOpenGL2-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkIOVeraOut-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkIOTecplotTable-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkIOSegY-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkIOParallelXML-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkIOPLY-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkIOOggTheora-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtktheora-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkogg-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkIONetCDF-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkIOMotionFX-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkIOParallel-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkIOMINC-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkIOLSDyna-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkIOInfovis-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtklibxml2-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkIOImport-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkIOIOSS-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkioss-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkIOHDF-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkIOVideo-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkIOMovie-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkIOExportPDF-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkIOExportGL2PS-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkRenderingGL2PSOpenGL2-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkgl2ps-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkIOExport-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkRenderingVtkJS-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkIOGeometry-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkRenderingSceneGraph-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkIOExodus-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkIOEnSight-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkIOCityGML-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkIOChemistry-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkIOCONVERGECFD-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkIOCGNSReader-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkIOAsynchronous-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkIOAMR-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkInteractionImage-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkImagingStencil-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkImagingStatistics-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkImagingMorphological-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkImagingMath-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkImagingFourier-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkIOSQL-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtksqlite-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkGeovisCore-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtklibproj-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkInfovisLayout-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkViewsCore-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkInteractionWidgets-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkRenderingVolume-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkRenderingAnnotation-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkImagingHybrid-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkImagingColor-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkInteractionStyle-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkFiltersTopology-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkFiltersSelection-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkFiltersSMP-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkFiltersProgrammable-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkFiltersPoints-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkFiltersVerdict-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkverdict-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkFiltersParallelImaging-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkFiltersImaging-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkImagingGeneral-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkFiltersHyperTree-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkFiltersGeneric-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkFiltersFlowPaths-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkFiltersAMR-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkFiltersParallel-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkFiltersTexture-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkFiltersModeling-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkFiltersHybrid-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkDomainsChemistryOpenGL2-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkRenderingOpenGL2-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkRenderingUI-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkDomainsChemistry-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkChartsCore-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkInfovisCore-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkFiltersExtraction-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkParallelDIY-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkIOXML-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkIOXMLParser-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkexpat-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkParallelCore-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkIOLegacy-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkIOCore-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkdoubleconversion-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtklz4-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtklzma-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkFiltersStatistics-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkImagingSources-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkIOImage-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkDICOMParser-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkmetaio-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtktiff-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkRenderingContext2D-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkRenderingFreeType-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkfreetype-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkRenderingCore-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkFiltersSources-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkImagingCore-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkFiltersGeometry-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkFiltersGeneral-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkfmt-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkCommonComputationalGeometry-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkFiltersCore-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkCommonExecutionModel-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtklibharu-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkjsoncpp-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkexodusII-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtknetcdf-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkcgns-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkhdf5_hl-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkhdf5-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkpng-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkjpeg-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkglew-9.1.so.9.1.0
proj8G: /usr/lib/x86_64-linux-gnu/libGLX.so
proj8G: /usr/lib/x86_64-linux-gnu/libOpenGL.so
proj8G: /usr/lib/x86_64-linux-gnu/libX11.so
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkzlib-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkCommonColor-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkCommonDataModel-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkpugixml-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkCommonSystem-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkCommonMisc-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkCommonTransforms-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkCommonMath-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkkissfft-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkCommonCore-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtkloguru-9.1.so.9.1.0
proj8G: /home/cole/Desktop/cis410/VTK-build/lib/libvtksys-9.1.so.9.1.0
proj8G: CMakeFiles/proj8G.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cole/Desktop/cis410/proj8/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable proj8G"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/proj8G.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/proj8G.dir/build: proj8G

.PHONY : CMakeFiles/proj8G.dir/build

CMakeFiles/proj8G.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/proj8G.dir/cmake_clean.cmake
.PHONY : CMakeFiles/proj8G.dir/clean

CMakeFiles/proj8G.dir/depend:
	cd /home/cole/Desktop/cis410/proj8 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cole/Desktop/cis410/proj8 /home/cole/Desktop/cis410/proj8 /home/cole/Desktop/cis410/proj8 /home/cole/Desktop/cis410/proj8 /home/cole/Desktop/cis410/proj8/CMakeFiles/proj8G.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/proj8G.dir/depend

