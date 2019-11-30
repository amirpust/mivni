#ifndef _AVLTREEBYLINUX_H
#define _AVLTREEBYLINUX_H

#include "AVLTree.h"

class AVLTreeByLinux: public AVLTree {
protected:
    int compare(DataCenter *dc1, DataCenter *dc2) override;
};


#endif //_AVLTREEBYLINUX_H
