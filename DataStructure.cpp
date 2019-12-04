#include "DataStructure.h"

DataStructure::DataStructure() {
    idTree = new AVLTreeById();
    windowsTree = new AVLTreeByWindows;
    linuxTree = new AVLTreeByLinux;
}

DataStructure::~DataStructure() {
    delete idTree;
    delete windowsTree;
    delete linuxTree;
}
