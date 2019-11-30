#ifndef _AVLTREEBYID_H
#define _AVLTREEBYID_H

#include "AVLTree.h"
class AVLTreeById: public AVLTree{
protected:
    int compare(DataCenter *dc1, DataCenter *dc2) override;
};


#endif //_AVLTREEBYID_H
