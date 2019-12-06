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

    AVLNode(data *currentData, AVLNode *father, AVLNode *rightSon
            , AVLNode *leftSon, int nodeHeight, int bf);

    data *getCurrentData() const;

    bool updateHeightsAndBF();

    virtual ~AVLNode() = default;

    AVLNode *getFather() const;

    AVLNode *getRightSon() const;

    AVLNode *getLeftSon() const;

    int getNodeHeight() const;

    int getBf() const;

    void setCurrentData(data *currentData);

    void setFather(AVLNode *father);

    void setRightSon(AVLNode *rightSon);

    void setLeftSon(AVLNode *leftSon);

    void setNodeHeight(int nodeHeight);

    void setBf(int bf);

private:
    int getSonHeight(AVLNode* son);
};

#endif //_NODE_H
