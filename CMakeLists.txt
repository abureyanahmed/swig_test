cmake_minimum_required(VERSION 2.8.11)
project( test_swig )

set(CMAKE_BUILD_TYPE "Release")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find CGAL
find_package(CGAL REQUIRED)
include( ${CGAL_USE_FILE} )

FIND_PACKAGE(SWIG REQUIRED)
INCLUDE(${SWIG_USE_FILE})

FIND_PACKAGE(PythonLibs)
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

SET(CMAKE_SWIG_FLAGS "")

SET_SOURCE_FILES_PROPERTIES(arrangement_based_crossing_computation.i PROPERTIES CPLUSPLUS ON)
SET_SOURCE_FILES_PROPERTIES(arrangement_based_crossing_computation.i PROPERTIES SWIG_FLAGS "-includeall")
SWIG_ADD_MODULE(arrangement_based_crossing_computation python arrangement_based_crossing_computation.i arrangement_based_crossing_computation.cpp)
SWIG_LINK_LIBRARIES(arrangement_based_crossing_computation ${PYTHON_LIBRARIES})
