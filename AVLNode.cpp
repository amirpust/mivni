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
