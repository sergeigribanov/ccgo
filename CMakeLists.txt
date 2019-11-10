cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(CCGO)
set(EIGEN3_INCLUDE_DIR "$ENV{EIGEN3_INCLUDE_DIR}")
if(NOT EIGEN3_INCLUDE_DIR)
  message(FATAL_ERROR "Please point the environment variable EIGEN3_INCLUDE_DIR to the include directory of your Eigen3 installation.")
endif()
file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
set(LIB_SOURCES ${SOURCES})
list(REMOVE_ITEM LIB_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
file(GLOB HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)
add_executable(ccgo-test ${SOURCES})
target_include_directories(ccgo-test
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  PRIVATE
  ${EIGEN3_INCLUDE_DIR})
add_library(ccgo SHARED ${LIB_SOURCES})
target_include_directories(ccgo
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  PRIVATE
  ${EIGEN3_INCLUDE_DIR})
set(PUBLIC_HEADERS ${HEADERS})
set_target_properties(ccgo
PROPERTIES
PUBLIC_HEADER "${PUBLIC_HEADERS}")
install(TARGETS ccgo-test DESTINATION bin)
install(TARGETS ccgo
  LIBRARY DESTINATION lib
  PUBLIC_HEADER DESTINATION include)
