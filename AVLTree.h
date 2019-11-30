#ifndef _AVLTREE_H
#define _AVLTREE_H

#include <cassert>
#include "AVLNode.h"

//TODO: write what the enum is for
/**
 *
 */
typedef enum{
    leftSon = -1,
    tempSon = 0,
    rightSon = 1
}Sons;

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

    void insert(DataCenter* dc){
        Sons son;
        AVLNode* father = findFather(dc, &son);

        assert( father != nullptr);
        AVLNode* newNode = new AVLNode(dc,father);


        if(son == leftSon){
            assert(father->getLeftSon() == nullptr);
            father->setLeftSon(newNode);
        }
        if(son == rightSon){
            assert(father->getRightSon() == nullptr);
            father->setRightSon(newNode);
        }

        updateTree(father);
    }

    /**
     * Find the legitimate father of the dc.
     * Used mainly to find a place to a new node.
     * @param dc the
     * @param son is an int ptr that holds where the son needs to be.
     * @return
     * The AVLNode to the father
     */
    AVLNode* findFather(DataCenter* dc, Sons* son){
        AVLNode* temp = root->getLeftSon();
        if(temp == nullptr){
            *son = leftSon;
            return root;
        }


        while(temp != nullptr){
            if(compare(temp->getCurrentDataCenter(),dc) == 0){
                *son = tempSon;
                return nullptr; //Happened only if the dc already exists
            }
            if(compare(dc, temp->getCurrentDataCenter()) > 0){
                if(temp->getRightSon() == nullptr){
                    *son = rightSon;
                    return temp;
                }
                temp = temp->getRightSon();
            }
            else{
                if(temp->getLeftSon() == nullptr){
                    *son = leftSon;
                    return temp;
                }
                temp = temp->getLeftSon();
            }
        }
        return nullptr; //Shouldn't reach here
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

    //TODO: Jonathan (3) removeNode
    void remove(DataCenter* dc){
        assert(dc == nullptr);
        AVLNode* node = findNode(dc);

    }

    AVLNode* findClosestFromRight();

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
    void updateTree(AVLNode* updateFrom){
        while(updateFrom != root && updateFrom->updateHeightsAndBF()){
            int bf = updateFrom->getBf();
            if(bf < -1 || bf > 1){
                if(bf > 0)
                    if(updateFrom->getLeftSon()->getBf() == -1)
                        rollLR(updateFrom);
                    else
                        rollLL(updateFrom);
                else
                    if(updateFrom->getRightSon()->getBf() == 1)
                        rollRL(updateFrom);
                    else
                        rollRR(updateFrom);

            }
            updateFrom = updateFrom->getFather();
        }
    }

    void rollRR(AVLNode* nodeToRoll);
    void rollLL(AVLNode* nodeToRoll){
        assert(nodeToRoll != nullptr);

        AVLNode* temp = nodeToRoll->getLeftSon();
        nodeToRoll->setLeftSon(temp->getRightSon());
        temp->setRightSon(nodeToRoll);
    }

    void rollRL(AVLNode* nodeToRoll);
    void rollLR(AVLNode* nodeToRoll);
};


#endif //_AVLTREE_H