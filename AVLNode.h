//
// Created by Amir on 29/11/2019.
//

#ifndef _NODE_H
#define _NODE_H

#include <cstdio>
#include "Server.h"
#include "DataCenter.h"

template<class Data>
class AVLNode {
private:
    AVLNode *father;
    AVLNode *rightSon;
    AVLNode *leftSon;
    Data *currentData;
    int nodeHeight;

public:
    explicit AVLNode(Data *currentData, AVLNode *father = NULL,
            AVLNode *rightSon = NULL, AVLNode *leftSon = NULL,
            int nodeHeight = 0)
            : father(father), rightSon(rightSon), leftSon(leftSon),
            currentData(currentData), nodeHeight(nodeHeight) {}

    AVLNode<Data> *getFather() const ;

    void setFather(AVLNode *father);

    AVLNode *getRightSon() const;

    void setRightSon(AVLNode *rightSon);

    AVLNode *getLeftSon() const;

    void setLeftSon(AVLNode *leftSon) {
        AVLNode::leftSon = leftSon;
    }

    Data *getCurrentData() const {
        return currentData;
    }

    void setCurrentData(Data *currentData) {
        AVLNode::currentData = currentData;
    }

};

#endif //_NODE_H
