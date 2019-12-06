cmake_minimum_required(VERSION 3.14)
project(mivni)

set(CMAKE_CXX_STANDARD 11)

add_executable(tests main.cpp AVLTree.h AVLTree.cpp AVLNode.h AVLNode.cpp)