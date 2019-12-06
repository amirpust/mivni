#include "AVLNode.h"
#include <cmath>

/**
 * update the heights and the BF.
 * @return
 * true: if the height is changed
 * false: otherwise
 */
 template <class Data>
bool AVLNode<Data>::updateHeightsAndBF(){
    int rightSonHeight = getSonHeight(rightSon);
    int leftSonHeight = getSonHeight(leftSon);
    bf = leftSonHeight - rightSonHeight;
    if(nodeHeight != (int)fmax(rightSonHeight, leftSonHeight) + 1){
        nodeHeight =  (int)fmax(rightSonHeight, leftSonHeight) + 1;
        return true;
    }
    return false;
}


template<class Data>
AVLNode<Data>::AVLNode(Data *currentData, AVLNode *father, AVLNode *rightSon, AVLNode *leftSon, int nodeHeight, int bf)
        :currentData(currentData), father(father), rightSon(rightSon), leftSon(leftSon), nodeHeight(nodeHeight),
         bf(bf) {}

template<class Data>
Data *AVLNode<Data>::getCurrentData() const {
    return currentData;
}

template<class Data>
AVLNode<Data> *AVLNode<Data>::getFather() const {
    return father;
}

template<class Data>
AVLNode<Data> *AVLNode<Data>::getRightSon() const {
    return rightSon;
}

template<class Data>
AVLNode<Data> *AVLNode<Data>::getLeftSon() const {
    return leftSon;
}

template<class Data>
int AVLNode<Data>::getNodeHeight() const {
    return nodeHeight;
}

template<class Data>
int AVLNode<Data>::getBf() const {
    return bf;
}

template<class Data>
void AVLNode<Data>::setCurrentData(Data *currentData) {
    AVLNode::currentData = currentData;
}

template<class Data>
void AVLNode<Data>::setFather(AVLNode *father) {
    AVLNode::father = father;
}

template<class Data>
void AVLNode<Data>::setRightSon(AVLNode *rightSon) {
    AVLNode::rightSon = rightSon;
    if(rightSon != nullptr)
        rightSon->setFather(this);
}

template<class Data>
void AVLNode<Data>::setLeftSon(AVLNode *leftSon) {
    AVLNode::leftSon = leftSon;
    if(leftSon != nullptr)
        leftSon->setFather(this);
}

template<class Data>
void AVLNode<Data>::setNodeHeight(int nodeHeight) {
    AVLNode::nodeHeight = nodeHeight;
}

template<class Data>
void AVLNode<Data>::setBf(int bf) {
    AVLNode::bf = bf;
}

template<class Data>
int AVLNode<Data>::getSonHeight(AVLNode *son) {
    if (son == nullptr)
        return -1;
    return  son->getNodeHeight();
}
