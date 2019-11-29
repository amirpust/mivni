//
// Created by Amir on 29/11/2019.
//

#ifndef _NODE_H
#define _NODE_H

#include <cstdio>
#include "Server.h"
#include "DataCenter.h"

class AvlNode {
private:
    AvlNode *father;
    AvlNode *rightSon;
    AvlNode *leftSon;
    DataCenter *currentFarm;

public:
    explicit AvlNode(DataCenter *currentFarmNode, AvlNode *fatherNode = nullptr
            , AvlNode *rightSonNode = nullptr, AvlNode *leftSonNode = nullptr);

    AvlNode *getFather() const;

    void setFather(AvlNode *father);

    AvlNode *getRightSon() const;

    void setRightSon(AvlNode *rightSon);

    AvlNode *getLeftSon() const;

    void setLeftSon(AvlNode *leftSon);

};

#endif //_NODE_H
