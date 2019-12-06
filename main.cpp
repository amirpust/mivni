#include <iostream>
#include "DataCenter.h"
#include <cassert>
#include "AVLTree.h"
#include "CompareInt.h"


int main() {
    AVLTree<int ,int, CompareInt> intTree(true);

    for(int i = 0; i < 3; ++i){
        int* ptr = (int*)malloc(sizeof(*ptr));
        *ptr = 2*i;
        intTree.insert(ptr);
    }
    intTree.printInOrder();


    return 0;
}