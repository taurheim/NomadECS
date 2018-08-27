cmake_minimum_required(VERSION 3.5)
project(nomad)

set(CMAKE_CXX_STANDARD 14)

add_library(nomad src/component.cpp src/entity.h src/componentManager.h src/componentManager.cpp src/system.cpp src/world.cpp src/world.h src/componentMask.cpp src/componentMask.h src/entity.cpp src/entityManager.cpp src/entityManager.h)