cmake_minimum_required(VERSION 3.20)
project(main)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_C_FLAGS "-W -O3 -std=gnu11")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-W -O3 -std=c++11")
aux_source_directory(. DIR_SRCS)
add_executable(main ${DIR_SRCS})