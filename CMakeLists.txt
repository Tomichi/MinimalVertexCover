cmake_minimum_required(VERSION 3.9)
project(MinimalVertexCover)

set(CMAKE_CXX_STANDARD 11)

add_executable(MinimalVertexCover
        src/main.cpp
        src/Individual.h
        src/Graph.h)
