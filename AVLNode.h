#ifndef _NODE_H
#define _NODE_H

#include <cstdio>
#include "Server.h"
#include "DataCenter.h"
template <class data>
class AVLNode {
private:
    data *currentData;
    AVLNode *father;
    AVLNode *rightSon;
    AVLNode *leftSon;
    int nodeHeight;
    int bf;

public:
    AVLNode(DataCenter *currentDataCenter, AVLNode *father = nullptr
            , AVLNode *rightSon = nullptr, AVLNode *leftSon = nullptr
                    , int nodeHeight = 0);

    int getNodeHeight() const;

    void setNodeHeight(int nodeHeight);

    DataCenter *getCurrentDataCenter() const;

    void setCurrentDataCenter(DataCenter *currentDataCenter);

    AVLNode *getFather() const;

    void setFather(AVLNode *father);

    AVLNode *getRightSon() const;

    void setRightSon(AVLNode *rightSon);

    AVLNode *getLeftSon() const;

    int getBf() const;

    void setLeftSon(AVLNode* leftSon);

    bool updateHeightsAndBF();

    virtual ~AVLNode() = default;

private:
    int getSonHeight(AVLNode* son);
};

#endif //_static static static NODE_H
