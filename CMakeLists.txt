cmake_minimum_required(VERSION 3.14)
project(mivni)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES DataCenter.cpp DataStructure.cpp Server.cpp
        main1.cpp OSKey.cpp OSKey.h)
set(HEADER_FILES AVLTree.h AVLNode.h DataCenter.h DataStructureExceptions.h
        DataStructure.h Server.h library1.h library1.cpp OSKey.cpp OSKey.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})