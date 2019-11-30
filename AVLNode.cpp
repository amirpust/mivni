#include "AVLNode.h"
#include <cmath>

AVLNode::AVLNode(DataCenter *currentDataCenter, AVLNode *father
        , AVLNode *rightSon, AVLNode *leftSon, int nodeHeight)
        : currentDataCenter(currentDataCenter), father(father), rightSon(rightSon)
        , leftSon(leftSon),
          nodeHeight(nodeHeight) {

}

/**
 * update the heights and the BF.
 * @return
 * true: if the height is changed
 * false: otherwise
 */
bool AVLNode::updateHeightsAndBF(){
    int rightSonHeight = getSonHeight(rightSon);
    int leftSonHeight = getSonHeight(leftSon);
    bf = leftSonHeight - rightSonHeight;
    if(nodeHeight != (int)fmax(rightSonHeight, leftSonHeight) + 1){
        nodeHeight =  (int)fmax(rightSonHeight, leftSonHeight) + 1;
        return true;
    }
    return false;
}

int AVLNode::getSonHeight(AVLNode *son) {
    if(son == nullptr)
        return -1;
    return son->getNodeHeight();
}

DataCenter* AVLNode::getCurrentDataCenter() const {
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
    if(rightSon != nullptr)
        rightSon->setFather(this);
}

AVLNode *AVLNode::getLeftSon() const {
    return leftSon;
}

void AVLNode::setLeftSon(AVLNode *leftSon) {
    AVLNode::leftSon = leftSon;
    if(leftSon != nullptr)
        leftSon->setFather(this);
}

int AVLNode::getNodeHeight() const {
    return nodeHeight;
}

void AVLNode::setNodeHeight(int nodeHeight) {
    AVLNode::nodeHeight = nodeHeight;
}

int AVLNode::getBf() const {
    return bf;
}
