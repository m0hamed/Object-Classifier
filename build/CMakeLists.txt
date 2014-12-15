cmake_minimum_required (VERSION 2.8)  
project (Object-Classifier)

find_package (OpenCV REQUIRED)
include_directories	("../include")

file (MAKE_DIRECTORY ../bin)
file (GLOB_RECURSE SOURCES "../src/*.cpp")

SET(CMAKE_CXX_FLAGS "-std=c++0x")

add_executable (classifier ${SOURCES})
set_target_properties (classifier PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../bin/)
target_link_libraries (classifier ${OpenCV_LIBS})
