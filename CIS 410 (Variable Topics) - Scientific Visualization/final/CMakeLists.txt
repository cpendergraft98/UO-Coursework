cmake_minimum_required(VERSION 3.10)

PROJECT(astro)
SET(VTK_DIR /home/cole/Desktop/cis410/VTK-build)

find_package(VTK REQUIRED)

add_executable(astro astro)

SET(CMAKE_CXX_LINK_FLAGS "-lGL")
if(VTK_LIBRARIES)
  target_link_libraries(astro ${VTK_LIBRARIES})
else()
  target_link_libraries(astro vtkHybrid)
endif()

vtk_module_autoinit(
  TARGETS astro
  MODULES ${VTK_LIBRARIES})

