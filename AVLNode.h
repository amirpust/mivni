//
// Created by Amir on 29/11/2019.
//

#ifndef _NODE_H
#define _NODE_H

#include <cstdio>
#include "Server.h"
#include "DataCenter.h"

class AVLNode {
private:
    DataCenter *currentDataCenter;
    AVLNode *father;
    AVLNode *rightSon;
    AVLNode *leftSon;
    int nodeHeight;

public:
    AVLNode(DataCenter *currentDataCenter, AVLNode *father = NULL
            , AVLNode *rightSon = NULL, AVLNode *leftSon = NULL, int nodeHeight = NULL);

    int getNodeHeight() const;

    void setNodeHeight(int nodeHeight);

    DataCenter *getCurrentDataCenter() const;

    void setCurrentDataCenter(DataCenter *currentDataCenter);

    AVLNode *getFather() const;

    void setFather(AVLNode *father);

    AVLNode *getRightSon() const;

    void setRightSon(AVLNode *rightSon);

    AVLNode *getLeftSon() const;

    void setLeftSon(AVLNode *leftSon);
};

#endif //_NODE_H
