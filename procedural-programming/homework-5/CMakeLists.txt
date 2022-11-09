cmake_minimum_required(VERSION 3.22.1)
project(homework_5)

set(CMAKE_CXX_STANDARD 20)

add_executable(
  homework_5 
  main.cpp 
  euclid.h euclid.cpp 
  eratosfen.h eratosfen.cpp 
  texts.h texts.cpp
  sequence.h sequence.cpp
)

