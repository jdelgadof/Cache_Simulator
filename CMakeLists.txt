cmake_minimum_required(VERSION 3.26)
project(CacheSimulator)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CacheSimulator
        Cache.cpp
        Cache.h
        CacheBlock.cpp
        CacheBlock.h
        CacheSet.cpp
        CacheSet.h
        CacheSimulator.cpp
        Memory.cpp
        Memory.h
        stdafx.cpp
        stdafx.h
        targetver.h)
