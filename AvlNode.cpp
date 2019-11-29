//
// Created by Amir on 29/11/2019.
//

#include "AvlNode.h"

AvlNode::AvlNode(DataCenter *currentFarm, AvlNode *fatherNode
        , AvlNode *rightSon, AvlNode *leftSon)
        : father(father), rightSon(rightSon),
          leftSon(leftSon),
          currentFarm(currentFarm) {}

AvlNode *AvlNode::getFather() const {
    return father;
}

void AvlNode::setFather(AvlNode *father) {
    AvlNode::father = father;
}

AvlNode *AvlNode::getRightSon() const {
    return rightSon;
}

void AvlNode::setRightSon(AvlNode *rightSon) {
    AvlNode::rightSon = rightSon;
}

AvlNode *AvlNode::getLeftSon() const {
    return leftSon;
}

void AvlNode::setLeftSon(AvlNode *leftSon) {
    AvlNode::leftSon = leftSon;
}
