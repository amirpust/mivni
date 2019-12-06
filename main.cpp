#include <iostream>
#include "DataCenter.h"
#include <cassert>
#include "AVLTree.h"
#include "CompareInt.h"
void test1();

int main() {

    test1();


    return 0;
}

void test1(){
    AVLTree<int ,int, CompareInt> intTree(true);

    for(int i = 0; i < 20; ++i){
        int* ptr = (int*)malloc(sizeof(*ptr));
        *ptr = (100 - 11*i)%300;
        intTree.insert(ptr);
    }
    intTree.printInOrder();
}