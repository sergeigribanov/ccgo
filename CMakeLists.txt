cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(CCGO VERSION 1.0)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
find_package(Eigen3 REQUIRED NO_MODULE)
file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
set(LIB_SOURCES ${SOURCES})
list(REMOVE_ITEM LIB_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
file(GLOB HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)
add_library(ccgo SHARED ${LIB_SOURCES})
set_property(TARGET ccgo PROPERTY CXX_STANDARD 11)
target_include_directories(ccgo
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_link_libraries(ccgo
  PRIVATE
  Eigen3::Eigen)
set(PUBLIC_HEADERS ${HEADERS})
set_target_properties(ccgo
PROPERTIES
PUBLIC_HEADER "${PUBLIC_HEADERS}")
install(TARGETS ccgo
  EXPORT CCGOTargets
  LIBRARY DESTINATION lib
  PUBLIC_HEADER DESTINATION include/ccgo)
install(EXPORT CCGOTargets
  FILE CCGOTargets.cmake
  DESTINATION lib/cmake)
include(CMakePackageConfigHelpers)
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/CCGOConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/CCGOConfig.cmake"
  INSTALL_DESTINATION "lib/cmake/example"
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/CCGOConfigVersion.cmake"
  VERSION "${CCGO_VERSION_MAJOR}.${CCGO_VERSION_MINOR}"
  COMPATIBILITY AnyNewerVersion)
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/CCGOConfig.cmake
  DESTINATION lib/cmake)
export(EXPORT CCGOTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/CCGOTargets.cmake")
export(PACKAGE CCGO)
