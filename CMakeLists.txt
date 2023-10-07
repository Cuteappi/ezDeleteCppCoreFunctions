cmake_minimum_required(VERSION 3.26)
project(FileHandling.def VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

add_library(FileHandling SHARED FileHandling.cpp FileHandling.def
)

set_target_properties(FileHandling PROPERTIES
        PUBLIC_HEADER FileHandling.h
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
        OUTPUT_NAME "FileHandling"
)

set(CMAKE_SHARED_LIBRARY_SUFFIX ".dll")
