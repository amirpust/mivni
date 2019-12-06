#include "DataStructure.h"

DataStructure::DataStructure() {
    idTree = new AVLTree<DataCenter,int,CompareID>(true);
    linuxTree = new AVLTree<DataCenter,int,CompareLinux>();
    windowsTree = new AVLTree<DataCenter,int,CompareWindows>();
}

DataStructure::~DataStructure() {
    delete linuxTree;
    delete windowsTree;
    delete idTree;
}
