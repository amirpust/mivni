#ifndef _NODE_H
#define _NODE_H

#include <cstdio>
#include "Server.h"
#include "DataCenter.h"

template <class Data>
class AVLNode {
private:
    Data *currentData;
    AVLNode<Data> *father;
    AVLNode<Data> *rightSon;
    AVLNode<Data> *leftSon;
    int nodeHeight;
    int bf;

public:

    explicit AVLNode(Data *currentData, AVLNode<Data> *father = nullptr, AVLNode<Data> *rightSon  = nullptr
            , AVLNode<Data> *leftSon = nullptr, int nodeHeight = -1, int bf = 0);

    Data *getCurrentData() const;

    bool updateHeightsAndBF();

    virtual ~AVLNode() = default;

    AVLNode *getFather() const;

    AVLNode *getRightSon() const;

    AVLNode *getLeftSon() const;

    int getNodeHeight() const;

    int getBf() const;

    void setCurrentData(Data *currentData);

    void setFather(AVLNode *father);

    void setRightSon(AVLNode *rightSon);

    void setLeftSon(AVLNode *leftSon);

    void setNodeHeight(int nodeHeight);

    void setBf(int bf);

private:
    int getSonHeight(AVLNode* son);
};

#endif //_NODE_H
