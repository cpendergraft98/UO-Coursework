cmake_minimum_required(VERSION 3.10)

PROJECT(proj4)
SET(VTK_DIR /home/cole/Desktop/cis410/VTK-build)

find_package(VTK REQUIRED)

add_executable(proj5 proj5)

SET(CMAKE_CXX_LINK_FLAGS "-lGL")
if(VTK_LIBRARIES)
  target_link_libraries(proj5 ${VTK_LIBRARIES})
else()
  target_link_libraries(proj5 vtkHybrid)
endif()

vtk_module_autoinit(
  TARGETS proj5
  MODULES ${VTK_LIBRARIES})

