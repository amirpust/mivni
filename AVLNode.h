#ifndef _NODE_H
#define _NODE_H

#include <cstdio>
#include <cmath>
#include "Server.h"
#include "DataCenter.h"

template<class Data>
class AVLNode {
private:
    Data *currentData;
    AVLNode<Data> *father;
    AVLNode<Data> *rightSon;
    AVLNode<Data> *leftSon;
    int nodeHeight;
    int bf;

public:

    explicit AVLNode(Data *currentData, AVLNode<Data> *father = nullptr, AVLNode<Data> *rightSon = nullptr,
                     AVLNode<Data> *leftSon = nullptr, int nodeHeight = 0, int bf = 0) :
            currentData(currentData), father(father), rightSon(rightSon), leftSon(leftSon), nodeHeight(nodeHeight),
            bf(bf) {};

    Data *getCurrentData() const {
        return currentData;
    };

    /**
 * update the heights and the BF.
 * @return
 * true: if the height is changed
 * false: otherwise
 */
    bool updateHeightsAndBF() {
        int rightSonHeight = getSonHeight(rightSon);
        int leftSonHeight = getSonHeight(leftSon);
        bf = leftSonHeight - rightSonHeight;
        if (nodeHeight != ((int) fmax(rightSonHeight, leftSonHeight) + 1)) {
            nodeHeight = (int) fmax(rightSonHeight, leftSonHeight) + 1;
            return true;
        }
        return false;
    };

    virtual ~AVLNode() = default;

    AVLNode<Data> *getFather() const {
        return father;
    };

    AVLNode<Data> *getRightSon() const {
        return rightSon;
    };

    AVLNode<Data> *getLeftSon() const {
        return leftSon;
    };

    int getNodeHeight() const {
        return nodeHeight;
    };

    int getBf() const {
        return bf;
    };

    void setFather(AVLNode<Data> *_father) {
        this->father = _father;
    };

    void setRightSon(AVLNode<Data> *_rightSon) {
        assert(_rightSon != this);
        this->rightSon = _rightSon;
        if (rightSon != nullptr)
            rightSon->setFather(this);
    };

    void setLeftSon(AVLNode<Data> *_leftSon) {
        leftSon = _leftSon;
        if (leftSon != nullptr)
            leftSon->setFather(this);
    };

private:
    int getSonHeight(AVLNode<Data> *son) {
        if (son == nullptr)
            return -1;
        return son->getNodeHeight();
    };
};

#endif //_NODE_H
