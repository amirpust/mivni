cmake_minimum_required(VERSION 3.14)
project(mivni)

set(CMAKE_CXX_STANDARD 11)

add_executable(mivni main.cpp Node.cpp Node.h DataCenter.cpp DataCenter.h Server.h Server.cpp library1.c library1.h)