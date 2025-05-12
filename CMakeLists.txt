cmake_minimum_required(VERSION 3.31)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled
        RO.h
        RO.cpp
        DIST.cpp
        DIST.h
        PRF.cpp
        PRF.h
        PRF_project_clone.cpp)
