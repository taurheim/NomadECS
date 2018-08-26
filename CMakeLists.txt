cmake_minimum_required(VERSION 3.5)
project(nomad)

set(CMAKE_CXX_STANDARD 14)

add_library(nomad src/component.cpp src/entity.h src/componentManager.h src/componentManager.cpp)