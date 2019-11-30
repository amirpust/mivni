cmake_minimum_required(VERSION 3.14)
project(mivni)

set(CMAKE_CXX_STANDARD 11)

add_executable(mivni main.cpp AvlNode.cpp AvlNode.h
        DataCenter.cpp DataCenter.h Server.h Server.cpp AVLTree.cpp AVLTree.h DataStructure.cpp DataStructure.h AVLTreeById.cpp AVLTreeById.h AVLTreeByWindows.cpp AVLTreeByWindows.h AVLTreeByLinux.cpp AVLTreeByLinux.h)