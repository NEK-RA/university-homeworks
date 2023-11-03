cmake_minimum_required(VERSION 3.5)

project(siaod-tree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(siaod-tree main.cpp

  readme.md
  node.h node.cpp
)

include(GNUInstallDirs)
install(TARGETS siaod-tree
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
