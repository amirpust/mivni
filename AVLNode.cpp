//
// Created by Amir on 29/11/2019.
//

#include "AVLNode.h"

AVLNode::AVLNode(DataCenter *currentDataCenter, AVLNode *father
        , AVLNode *rightSon, AVLNode *leftSon, int nodeHeight)
        : currentDataCenter(currentDataCenter), father(father), rightSon(rightSon)
        , leftSon(leftSon),
          nodeHeight(nodeHeight) {

}

DataCenter *AVLNode::getCurrentDataCenter() const {
    return currentDataCenter;
}

void AVLNode::setCurrentDataCenter(DataCenter *currentDataCenter) {
    AVLNode::currentDataCenter = currentDataCenter;
}

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

int AVLNode::getNodeHeight() const {
    return nodeHeight;
}

void AVLNode::setNodeHeight(int nodeHeight) {
    AVLNode::nodeHeight = nodeHeight;
}
