cmake_minimum_required(VERSION 3.5)

project(hanoi-111 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(hanoi-111 main.cpp)

install(TARGETS hanoi-111
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
