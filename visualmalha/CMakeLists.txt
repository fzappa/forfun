#https://cmake.org/cmake/help/v2.8.12/cmake.html#section_Variables
#https://mirkokiefer.com/cmake-by-example-f95eb47d45b1

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(VisualMesh CXX)
SET(CMAKE_BUILD_TYPE Release)

# Put everything in same folder
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/VisualMesh-bin)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/VisualMesh-bin)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/VisualMesh-bin)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/VisualMesh-bin)

#Folders that have files to build
ADD_SUBDIRECTORY(lib)
ADD_SUBDIRECTORY(main)

