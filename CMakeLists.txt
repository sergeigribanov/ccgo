cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(CCGO)
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
  ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(ccgo
  Eigen3::Eigen)
set(PUBLIC_HEADERS ${HEADERS})
set_target_properties(ccgo
PROPERTIES
PUBLIC_HEADER "${PUBLIC_HEADERS}")
install(TARGETS ccgo
  LIBRARY DESTINATION lib
  PUBLIC_HEADER DESTINATION include/ccgo)
