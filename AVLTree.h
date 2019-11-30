#ifndef _AVLTREE_H
#define _AVLTREE_H

#include "AVLNode.h"

//TODO: Jonathan (3) removeNode


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

    void insert(DataCenter* dc){//TODO: Jonathan (2)

    }

    /**
     * Find the legitimate father of the dc.
     * Used mainly to find a place to a new node.
     * @param dc the
     * @param isRight a bool ptr that hold "returns" values
     * true if the son's place is from the right of the father
     * false if the son's place is from the left of the father
     * @return
     */
    AVLNode* findfather(DataCenter* dc, bool* isRight){
        AVLNode* temp = root->getLeftSon();
        while(temp != nullptr){
            if(compare(temp->getCurrentDataCenter(),dc) == 0)
                return nullptr;//Happened only if the dc already exists TODO: Jonathan (1) keep think
            if(compare(dc, temp->getCurrentDataCenter()) > 0){
                if(temp->getRightSon() == nullptr){
                    *isRight = true;
                    return temp;
                }
                temp = temp->getRightSon();
            }
            else{
                if(temp->getLeftSon() == nullptr){
                    *isRight = false;
                    return temp;
                }
                temp = temp->getLeftSon();
            }
        }
    }
    /** Read:
 * Inside every DC there is a ptr to the node, this function will be used
 * only in case we need to find the real DC by a dummy that carries the same id.    *
 * @param dc - dummy DC that helps us find the real DC through the right
 * compare function
 * @return AVLNode* of the Node that has the DC or nullptr in case the DC do not exists.
 */
    DataCenter* findDataCenter(DataCenter* dc){
        return findNode(dc)->getCurrentDataCenter();
    }

    /** Read:
     * Inside every DC there is a ptr to the node, this function will be used
     * only in case we need to find the node that contains the real DC by a dummy that carries the same id.    *
     * @param dc - dummy DC that helps us find the real DC through the right
     * compare function
     * @return AVLNode* of the Node that has the DC or nullptr in case the DC do not exists.
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