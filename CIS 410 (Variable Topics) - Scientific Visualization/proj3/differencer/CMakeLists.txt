cmake_minimum_required(VERSION 3.10)

PROJECT(differencer)
SET(VTK_DIR /home/cole/Desktop/cis410/VTK-build)

find_package(VTK REQUIRED)

add_executable(differencer differencer)

SET(CMAKE_CXX_LINK_FLAGS "-lGL")
if(VTK_LIBRARIES)
  target_link_libraries(differencer ${VTK_LIBRARIES})
else()
  target_link_libraries(differencer vtkHybrid)
endif()

vtk_module_autoinit(
  TARGETS differencer
  MODULES ${VTK_LIBRARIES})

