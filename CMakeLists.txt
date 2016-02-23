cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(equlizeImagesUsingCLAHE)
find_package( OpenCV REQUIRED )

# use sse3 instruction set
SET(CMAKE_CXX_FLAGS "-msse3")

add_executable(main main.cpp main.hpp)
target_link_libraries(main ${OpenCV_LIBS})

ADD_DEFINITIONS(
    -std=c++11 # Or -std=c++0x
    #-fopenmp
    # Other flags
)
