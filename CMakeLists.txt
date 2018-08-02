cmake_minimum_required(VERSION 3.1)

project(nomad)

add_library(nomad STATIC src/demo.cpp)

install(TARGETS nomad DESTINATION "lib")
install(FILES src/demo.h DESTINATION "../include")