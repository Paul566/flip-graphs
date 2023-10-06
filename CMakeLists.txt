cmake_minimum_required(VERSION 3.26)
project(flip_graphs)

set(CMAKE_CXX_STANDARD 17)

add_executable(flip_graphs main.cpp
        Point.h
        Point.cpp
        Triangulation.h
        Triangle.h
        Triangle.cpp
        Triangulation.cpp)
