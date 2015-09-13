cmake_minimum_required(VERSION 3.2)
#set(CMAKE_VERBOSE_MAKEFILES on)
project(Proj)
set(SOURCE_FILES repeating_count.cpp)

set(CMAKE_VERBOSE_MAKEFILE on)
find_package(PythonLibs 3.4 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
python_add_module(repeating_count repeating_count.cpp)
# target_link_libraries(repeating_count ${PYTHON_LIBRARIES}) #only for Win

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_executable(Proj ${SOURCE_FILES})
target_link_libraries(Proj ${PYTHON_LIBRARIES})