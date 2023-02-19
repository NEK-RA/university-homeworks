cmake_minimum_required(VERSION 3.5)

project(siaod-1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    siaod-1 main.cpp
    utils.h utils.cpp
    array_static.h array_static.cpp
    array_dynamic.h array_dynamic.cpp
    array_vector.h array_vector.cpp
)

install(TARGETS siaod-1
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
