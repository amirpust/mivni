#ifndef _AVLTREE_H
#define _AVLTREE_H

#include "AVLNode.h"

class AVLTree {
    //Dummy Root - the left son is the real first node
    AVLNode* root;

public:
    explicit AVLTree(){
        root = new AVLNode(nullptr);
    };
    ~AVLTree(){
        delete root;
    };

    void insert(DataCenter dc){

    }
    DataCenter* findDataCenter(DataCenter* dc){

    }

    /** Read:
     * Inside every DC there is a ptr to the node, this function will be used only in dace we need to find
     *
     *
     * @param dc
     * @return
     */
    AVLNode* findNode(DataCenter* dc){
        AVLNode* temp = root->getLeftSon();
        while(temp != nullptr){
            if(compare(temp->getCurrentDataCenter(),dc) == 0)
                return temp;
            if(compare(dc, temp->getCurrentDataCenter()) > 0)
                temp = temp->getRightSon();
            else
                temp = temp->getLeftSon();
        }
        return nullptr;
    }


protected:
    /**
     * Virtual function (to be override) which compare between 2 Dc's
     * @param dc1
     * @param dc2
     * @return:
     * positive number in case dc1 > dc2
     * negative number in case dc1 < dc2
     * 0 in case dc1 == dc2
     */
    virtual int compare(DataCenter* dc1, DataCenter* dc2) = 0;

private:

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