cmake_minimum_required(VERSION 3.10.0)
project(Tucil2_13523083_13523084 VERSION 0.1.0 LANGUAGES C CXX)

find_package(Stb REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(GIF REQUIRED)
include_directories(include)

add_executable(app src/main.cpp
    src/ErrorMeasure.cpp
    src/Image.cpp
    src/QuadTree.cpp
    src/GIF.cpp
)

target_include_directories(app PRIVATE ${Stb_INCLUDE_DIR})
target_include_directories(app PRIVATE ${EIGEN3_INCLUDE_DIRS})
target_include_directories(app PRIVATE ${GIF_INCLUDE_DIRS})
target_link_libraries(app PRIVATE GIF::GIF)