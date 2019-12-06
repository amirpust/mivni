#include <iostream>
#include "DataCenter.h"
#include <cassert>
#include "AVLTree.h"

class CompareInt{
public:
    int operator()(int* value1, int value2) {
        return *value1-value2;
    }
    int operator()(int* value1, int* value2) {
        return *value1-*value2;
    }
};

int main() {
    AVLTree<int ,int, CompareInt> intTree(true);

    for(int i = 0; i < 20; ++i){
        int* ptr = (int*)malloc(sizeof(*ptr));
        *ptr = 2*i;
        intTree.insert(ptr);
    }


    return 0;
}