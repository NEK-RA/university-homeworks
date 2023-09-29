cmake_minimum_required(VERSION 3.18)

project(siaod LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    siaod main.cpp
    task1.h task1.cpp
    task2.h task2.cpp
    t2.txt
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/t2.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

install(TARGETS siaod
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
