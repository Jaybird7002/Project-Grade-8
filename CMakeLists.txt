cmake_minimum_required(VERSION 3.20)
project(Project_Grade_8)

set(CMAKE_CXX_STANDARD 14)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)
link_libraries(freeimageplus)

add_executable(Project_Grade_8 main.cpp shapes.h color.h image.cpp scene.h ray.h)
