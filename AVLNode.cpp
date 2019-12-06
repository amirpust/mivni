#include "AVLNode.h"
#include <cmath>

/**
 * update the heights and the BF.
 * @return
 * true: if the height is changed
 * false: otherwise
 */
 template <class data>
bool AVLNode<data>::updateHeightsAndBF(){
    int rightSonHeight = getSonHeight(rightSon);
    int leftSonHeight = getSonHeight(leftSon);
    bf = leftSonHeight - rightSonHeight;
    if(nodeHeight != (int)fmax(rightSonHeight, leftSonHeight) + 1){
        nodeHeight =  (int)fmax(rightSonHeight, leftSonHeight) + 1;
        return true;
    }
    return false;
}


template<class data>
AVLNode<data>::AVLNode(data *currentData, AVLNode *father, AVLNode *rightSon, AVLNode *leftSon, int nodeHeight, int bf)
        :currentData(currentData), father(father), rightSon(rightSon), leftSon(leftSon), nodeHeight(nodeHeight),
         bf(bf) {}

template<class data>
data *AVLNode<data>::getCurrentData() const {
    return currentData;
}

template<class data>
AVLNode<data> *AVLNode<data>::getFather() const {
    return father;
}

template<class data>
AVLNode<data> *AVLNode<data>::getRightSon() const {
    return rightSon;
}

template<class data>
AVLNode<data> *AVLNode<data>::getLeftSon() const {
    return leftSon;
}

template<class data>
int AVLNode<data>::getNodeHeight() const {
    return nodeHeight;
}

template<class data>
int AVLNode<data>::getBf() const {
    return bf;
}

template<class data>
void AVLNode<data>::setCurrentData(data *currentData) {
    AVLNode::currentData = currentData;
}

template<class data>
void AVLNode<data>::setFather(AVLNode *father) {
    AVLNode::father = father;
}

template<class data>
void AVLNode<data>::setRightSon(AVLNode *rightSon) {
    AVLNode::rightSon = rightSon;
    if(rightSon != nullptr)
        rightSon->setFather(this);
}

template<class data>
void AVLNode<data>::setLeftSon(AVLNode *leftSon) {
    AVLNode::leftSon = leftSon;
    if(leftSon != nullptr)
        leftSon->setFather(this);
}

template<class data>
void AVLNode<data>::setNodeHeight(int nodeHeight) {
    AVLNode::nodeHeight = nodeHeight;
}

template<class data>
void AVLNode<data>::setBf(int bf) {
    AVLNode::bf = bf;
}

template<class data>
int AVLNode<data>::getSonHeight(AVLNode *son) {
    if (son == nullptr)
        return -1;
    return  son->getNodeHeight();
}
