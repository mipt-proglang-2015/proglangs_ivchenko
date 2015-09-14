cmake_minimum_required(VERSION 3.2)
project(repeating_count)
set(SOURCE_FILES repeating_count.cpp)
if (WIN32)
	set(BUILD_SHARED_LIBS ON)
endif (WIN32)

set(CMAKE_VERBOSE_MAKEFILES on)
# Find PythonLibs
find_package(PythonLibs 3.4 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

if (UNIX)
	python_add_module(repeating_count repeating_count.cpp)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif (UNIX)

# This will create the repeating_count.dll
add_library(repeating_count ${SOURCE_FILES})
target_link_libraries(repeating_count ${PYTHON_LIBRARIES})
