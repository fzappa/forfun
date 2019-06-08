CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(ND100 CXX)
SET(CMAKE_BUILD_TYPE Release)

MESSAGE("******** Check ND100_GPS main dependencies ********")

#Flags
SET(CMAKE_CXX_FLAGS_RELEASE "-Wall -march=native -mtune=native -pedantic -O2 -pipe -fstack-protector-all -fno-plt --param=ssp-buffer-size=4 -D_FORTIFY_SOURCE=2 -floop-interchange -floop-strip-mine -floop-block")

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

#Find OpenMP
FIND_PACKAGE(OpenMP)
IF (OPENMP_FOUND)
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -floop-parallelize-all -ftree-parallelize-loops=4")
ELSE()
    MESSAGE(FATAL_ERROR "OpenMP support not found")
ENDIF()


INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib)
ADD_EXECUTABLE(ND100.bin main.cpp)

SET_TARGET_PROPERTIES(ND100.bin PROPERTIES LINK_FLAGS "-Wl,-rpath,./")
TARGET_LINK_LIBRARIES(ND100.bin LibND100)

