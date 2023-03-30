cmake_minimum_required(VERSION 3.5)

project(siaod-4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
  siaod-4 main.cpp
  utils.h utils.cpp
  pdd.h pdd.cpp
)

install(TARGETS siaod-4
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
