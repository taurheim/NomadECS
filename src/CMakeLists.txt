cmake_minimum_required(VERSION 3.6)
project(nomadecs CXX)

# Include custom cmake rules
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(../cmake/clang-cxx-dev-tools.cmake)

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
