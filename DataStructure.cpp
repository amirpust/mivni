//
// Created by Amir on 30/11/2019.
//

#include "DataStructure.h"

DataStructure::DataStructure() {
    idTree = new AVLTreeById();
    windowsTree = new AVLTreeByWindows;
    linuxTree = new AVLTreeByLinux;
}
