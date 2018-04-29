cmake_minimum_required(VERSION 3.9)
project(MinimalVertexCover)


set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_COMPILER /usr/local/bin/g++-7)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -O2 -fopenmp")



add_executable(MinimalVertexCover
        src/main.cpp
        src/Individual.h
        src/Graph.h
        src/Population.h
        )
