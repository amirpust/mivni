#ifndef _AVLTREE_H
#define _AVLTREE_H

#include "AVLNode.h"

class AVLTree {
    //Dummy Root - the left son is the real first node
    AVLNode Root;

public:
    AVLTree(){
        Root = new AVLNode(nullptr);
    };
    ~AVLTree() = default;


private:
    virtual AVLNode* compare(AVLNode nodeToCompare) = 0;

    /**
     * Update the Tree by Data < Operators.
     *
     * @param updateFrom
     */
    void updateTree(AVLNode updateFrom);
    void rollRR(AVLNode nodeToRoll);
    void rollLL(AVLNode nodeToRoll);
    void rollRL(AVLNode nodeToRoll);
    void rollLR(AVLNode nodeToRoll);
};


#endif //_AVLTREE_H