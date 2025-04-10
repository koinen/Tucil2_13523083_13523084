cmake_minimum_required(VERSION 3.10.0)
project(Tucil2_13523083_13523084 VERSION 0.1.0 LANGUAGES C CXX)

find_package(Stb REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(GIF REQUIRED)
include_directories(src/include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
add_executable(app src/main.cpp
    src/include/ErrorMeasure.cpp
    src/include/Image.cpp
    src/include/QuadTree.cpp
    src/include/GIF.cpp
) 

target_include_directories(app PRIVATE ${Stb_INCLUDE_DIR})
target_include_directories(app PRIVATE ${EIGEN3_INCLUDE_DIRS})
target_link_libraries(app PRIVATE GIF::GIF)