cmake_minimum_required(VERSION 3.0)

set(CMAKE_VERBOSE_MAKEFILES on) # Advanced commenting
project(repeating_count)
set(SOURCE_FILES repeating_count.cpp)
if (WIN32)
	set(BUILD_SHARED_LIBS ON)
endif (WIN32)

# Find PythonLibs
find_package(PythonLibs 3.4 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

# Make module
if (UNIX)
	python_add_module(repeating_count repeating_count.cpp)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
	add_library(repeating_count ${SOURCE_FILES})
endif (UNIX)
target_link_libraries(repeating_count ${PYTHON_LIBRARIES})
