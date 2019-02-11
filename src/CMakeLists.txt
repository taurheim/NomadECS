cmake_minimum_required(VERSION 3.6)
project(nomadecs CXX)

# Include custom cmake rules
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
include(../cmake/clang-cxx-dev-tools.cmake OPTIONAL)

add_library(nomadecs
	component.cpp
	entity.h
	componentManager.h
	system.cpp
	world.cpp
	world.h
	componentMask.cpp
	componentMask.h
	entityManager.cpp
	entityManager.h
	entityHandle.h
	componentHandle.h)
