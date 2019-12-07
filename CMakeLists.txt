cmake_minimum_required(VERSION 3.14)
project(mivni)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES DataCenter.cpp DataStructure.cpp Server.cpp
        CompareID.cpp CompareLinux.cpp CompareWindows.cpp)
set(HEADER_FILES AVLTree.h AVLNode.h DataCenter.h DataStructureExceptions.h
        DataStructure.h Server.h library1.h CompareID.h CompareLinux.h CompareWindows.h library1.cpp main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})