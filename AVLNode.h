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
    AVLNode *father;
    AVLNode *rightSon;
    AVLNode *leftSon;
    DataCenter *currentFarm;

public:
    explicit AVLNode(DataCenter *currentFarmNode, AVLNode *fatherNode = nullptr
            , AVLNode *rightSonNode = nullptr, AVLNode *leftSonNode = nullptr);

    AVLNode *getFather() const;

    void setFather(AVLNode *father);

    AVLNode *getRightSon() const;

    void setRightSon(AVLNode *rightSon);

    AVLNode *getLeftSon() const;

    void setLeftSon(AVLNode *leftSon);

};

#endif //_NODE_H
