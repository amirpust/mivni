cmake_minimum_required(VERSION 3.14)
project(mivni)

set(CMAKE_CXX_STANDARD 11)

add_executable(mivni main.cpp AVLNode.cpp AVLNode.h
        DataCenter.cpp DataCenter.h Server.h Server.cpp)