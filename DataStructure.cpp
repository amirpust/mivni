#include "DataStructure.h"

DataStructure::DataStructure() {
    numberOfDataCenters = 0;
    try {
        idTree = new AVLTree<DataCenter,int,CompareID>(true);
    }catch (exception& e){
        throw OutOfMemory();
    }
    try {
        linuxTree = new AVLTree<DataCenter,int,CompareLinux>();
    }catch (exception& e){
        delete idTree;
        throw OutOfMemory();
    }

    try {
        windowsTree = new AVLTree<DataCenter,int,CompareWindows>();
    }catch (exception& e){
        delete idTree;
        delete linuxTree;
        throw OutOfMemory();
    }

}

DataStructure::~DataStructure() {
    delete linuxTree;
    delete windowsTree;
    delete idTree;
}
