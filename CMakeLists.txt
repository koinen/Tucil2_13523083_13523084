cmake_minimum_required(VERSION 3.10.0)
project(Tucil2_13523083_13523084 VERSION 0.1.0 LANGUAGES C CXX)

find_package(fmt CONFIG REQUIRED)
find_package(CImg CONFIG REQUIRED)
message(STATUS "CImg include directory: ${CIMG_INCLUDE_DIRS}")
message(STATUS "fmt include directory: ${fmt_INCLUDE_DIRS}")
add_executable(app src/test.cpp)

target_link_libraries(app PRIVATE fmt::fmt CImg::CImg)