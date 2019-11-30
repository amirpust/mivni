#ifndef _AVLTREEBYWINDOWS_H
#define _AVLTREEBYWINDOWS_H

#include "AVLTree.h"
class AVLTreeByWindows: public AVLTree {
protected:
    int compare(DataCenter *dc1, DataCenter *dc2) override;
};


#endif //_AVLTREEBYWINDOWS_H
