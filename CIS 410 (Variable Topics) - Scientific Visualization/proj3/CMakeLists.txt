cmake_minimum_required(VERSION 3.10)

PROJECT(proj3)
SET(VTK_DIR /home/cole/Desktop/cis410/VTK-build)

find_package(VTK REQUIRED)

add_executable(proj3 proj3)

SET(CMAKE_CXX_LINK_FLAGS "-lGL")
if(VTK_LIBRARIES)
  target_link_libraries(proj3 ${VTK_LIBRARIES})
else()
  target_link_libraries(proj3 vtkHybrid)
endif()

vtk_module_autoinit(
  TARGETS proj3
  MODULES ${VTK_LIBRARIES})

