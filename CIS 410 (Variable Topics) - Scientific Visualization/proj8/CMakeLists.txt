cmake_minimum_required(VERSION 3.10)

PROJECT(proj8G)
SET(VTK_DIR /home/cole/Desktop/cis410/VTK-build)

find_package(VTK REQUIRED)

add_executable(proj8G proj8G)

SET(CMAKE_CXX_LINK_FLAGS "-lGL")
if(VTK_LIBRARIES)
  target_link_libraries(proj8G ${VTK_LIBRARIES})
else()
  target_link_libraries(proj8G vtkHybrid)
endif()

vtk_module_autoinit(
  TARGETS proj8G
  MODULES ${VTK_LIBRARIES})

