//
// Created by Amir on 29/11/2019.
//

#include "AVLNode.h"

AVLNode::AVLNode(DataCenter *currentFarm, AVLNode *fatherNode
        , AVLNode *rightSon, AVLNode *leftSon)
        : father(father), rightSon(rightSon),
          leftSon(leftSon),
          currentFarm(currentFarm) {}

AVLNode *AVLNode::getFather() const {
    return father;
}

void AVLNode::setFather(AVLNode *father) {
    AVLNode::father = father;
}

AVLNode *AVLNode::getRightSon() const {
    return rightSon;
}

void AVLNode::setRightSon(AVLNode *rightSon) {
    AVLNode::rightSon = rightSon;
}

AVLNode *AVLNode::getLeftSon() const {
    return leftSon;
}

void AVLNode::setLeftSon(AVLNode *leftSon) {
    AVLNode::leftSon = leftSon;
}

int AVLNode::getNodeHight() const {
    return nodeHight;
}

void AVLNode::setNodeHight(int nodeHight) {
    AVLNode::nodeHight = nodeHight;
}
