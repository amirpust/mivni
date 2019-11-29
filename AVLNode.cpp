//
// Created by Amir on 29/11/2019.
//

#include "AVLNode.h"
template <class Data>
AVLNode<Data>* AVLNode<Data>::getFather() const {
    return father;
}
template <class Data>
void AVLNode<Data>::setFather(AVLNode *father) {
    AVLNode::father = father;
}

template <class Data>
AVLNode<Data>* AVLNode<Data>::getRightSon() const {
    return rightSon;
}

template <class Data>
void AVLNode<Data>::setRightSon(AVLNode *rightSon) {
    AVLNode::rightSon = rightSon;
}

template <class  Data>
AVLNode<Data>* AVLNode<Data>::getLeftSon() const {
    return leftSon;
}

template <class  Data>
void AVLNode<Data>::setLeftSon(AVLNode *leftSon) {
    AVLNode::leftSon = leftSon;
}

template <class Data>
Data* AVLNode<Data>::getCurrentData() const {
    return currentData;
}

template<class Data>
int AVLNode<Data>::getNodeHeight() const {
    return nodeHeight;
}
