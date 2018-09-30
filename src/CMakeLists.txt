cmake_minimum_required(VERSION 3.5)
project(nomadecs CXX)

set(CMAKE_CXX_STANDARD 14)

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
