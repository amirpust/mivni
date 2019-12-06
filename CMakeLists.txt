cmake_minimum_required(VERSION 3.14)
project(mivni)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.cpp)
set(HEADER_FILES AVLTree.h AVLNode.h CompareInt.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})