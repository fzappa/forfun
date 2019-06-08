cmake_minimum_required(VERSION 2.8)
project(LibVisualMesh CXX)
set(CMAKE_BUILD_TYPE Release)

message("******** Check VisualMesh libs dependencies ********")

#Flags
# Vectorial optimization for new Processors -mavx -mxop -mfma4
# Theese flags must be removed if compile in old procs
SET(CMAKE_CXX_FLAGS_RELEASE "-Wall -march=native -pedantic -O2 -pipe -D_FORTIFY_SOURCE=2 -floop-interchange -floop-strip-mine -floop-block -mavx -mxop -mfma4")

#Path for dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/deps/")

#LibIGL
find_package(LIBIGL REQUIRED)
if (NOT LIBIGL_FOUND)
   message(FATAL_ERROR "libigl not found --- You can download it using: \n git clone --recursive https://github.com/libigl/libigl.git ${PROJECT_SOURCE_DIR}/../libigl")
endif()


# #OpenGL
find_package(OpenGL REQUIRED)
IF(OPENGL_FOUND)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lGL")
ELSE()
    MESSAGE(FATAL_ERROR "Compiler ${CMAKE_CXX_COMPILER} has no OpenGL or Glut support.")
ENDIF()

#Glew
find_package(GLEW REQUIRED)
IF(GLEW_FOUND)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lGLEW")
ELSE()
    MESSAGE(FATAL_ERROR "Compiler ${CMAKE_CXX_COMPILER} has no Glew support.")
ENDIF()

#GLFW
find_package(GLFW REQUIRED)
if(GLFW_FOUND)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lglfw")
ELSE()
    MESSAGE(FATAL_ERROR "Compiler ${CMAKE_CXX_COMPILER} has no Glfw support.")
endif(GLFW_FOUND)


#Check C++14 standard support
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
if(COMPILER_SUPPORTS_CXX14)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
else()
    message(FATAL_ERROR "Compiler ${CMAKE_CXX_COMPILER} has no C++14 support.")
endif()

#Boost
find_package(Boost REQUIRED)
if (Boost_NOTFOUND)
	message(FATAL_ERROR "Boost library not found")
endif()

#Eigen
find_package(Eigen3 REQUIRED)
if (Eigen3_NOTFOUND)
	message(FATAL_ERROR "Eigen3 library not found")
endif()

#Find OpenMP
FIND_PACKAGE(OpenMP)
IF (OPENMP_FOUND)
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -floop-parallelize-all -ftree-parallelize-loops=4")
ELSE()
    MESSAGE(FATAL_ERROR "OpenMP support not found")
ENDIF()

file(GLOB SOURCES "*.cpp")
add_library(LibVisualMesh SHARED ${SOURCES})
SET_TARGET_PROPERTIES(LibVisualMesh PROPERTIES PREFIX "")



        