cmake_minimum_required(VERSION 3.18)

project(udi-cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(udi-cpp main.cpp
  utils.h utils.cpp
  arguments.h arguments.cpp
  desktops.h desktops.cpp
)

install(TARGETS udi-cpp
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})