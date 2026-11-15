cmake_minimum_required(VERSION 3.14)
project(nomadecs VERSION 0.0.5 LANGUAGES CXX)

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
  set(NOMADECS_IS_TOP_LEVEL ON)
else()
  set(NOMADECS_IS_TOP_LEVEL OFF)
endif()

option(NOMADECS_BUILD_EXAMPLE "Build the example program" ${NOMADECS_IS_TOP_LEVEL})
option(NOMADECS_INSTALL "Generate the install target" ${NOMADECS_IS_TOP_LEVEL})

include(GNUInstallDirs)

add_library(nomadecs
  src/component.cpp
  src/componentMask.cpp
  src/entityManager.cpp
  src/system.cpp
  src/world.cpp)
add_library(nomadecs::nomadecs ALIAS nomadecs)
target_compile_features(nomadecs PUBLIC cxx_std_14)
set_target_properties(nomadecs PROPERTIES CXX_EXTENSIONS OFF)
target_include_directories(nomadecs PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

if(NOMADECS_IS_TOP_LEVEL)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
  include(cmake/clang-cxx-dev-tools.cmake)
endif()

if(NOMADECS_BUILD_EXAMPLE)
  add_subdirectory(example)
endif()

if(NOMADECS_INSTALL)
  include(CMakePackageConfigHelpers)

  install(TARGETS nomadecs EXPORT nomadecsTargets)
  install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
  install(EXPORT nomadecsTargets
    FILE nomadecsConfig.cmake
    NAMESPACE nomadecs::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/nomadecs)

  write_basic_package_version_file(
    ${PROJECT_BINARY_DIR}/nomadecsConfigVersion.cmake
    COMPATIBILITY SameMinorVersion)
  install(FILES ${PROJECT_BINARY_DIR}/nomadecsConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/nomadecs)
endif()
