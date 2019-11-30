#ifndef _AVLTREE_H
#define _AVLTREE_H

#include <cassert>
#include "AVLNode.h"

//TODO: Jonathan for all the class - check for error returns && add consts where its possible

typedef enum{
    leftSon = -1,
    tempSon = 0,
    rightSon = 1
}Sons;

/** TODO: write how to use the class include what to override and the D'tor use
 *
 */
class AVLTree {
    AVLNode* root;  //Dummy Root - the left son is the real first node

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
        auto newNode = new AVLNode(dc,father);


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

    /**
     * remove just remove the node from the tree - *without deleting the data*
     * for remove + delete data use destroy(dc);
     * @param dc
     */
    void remove(DataCenter* dc){
        assert(dc != nullptr);
        AVLNode* node = findNode(dc);
        bool nodeIsRightSon = node->getFather()->getRightSon()==node;
        if(node->getRightSon() == nullptr){
            if(nodeIsRightSon)
                node->getFather()->setRightSon(node->getLeftSon());
            else
                node->getFather()->setLeftSon(node->getLeftSon());
            delete node;    //TODO: check that node D'tor does not delete DC
            return;
        }
        AVLNode* updateFrom = nullptr;
        AVLNode* replaceBy = findReplacement(node, updateFrom);
        assert(updateFrom != nullptr);

        //Sets the replacement sons
        replaceBy->setRightSon(node->getRightSon());
        replaceBy->setLeftSon(node->getLeftSon());

        //set the father ti point on the replacement
        if(nodeIsRightSon)
            node->getFather()->setRightSon(replaceBy);
        else
            node->getFather()->setLeftSon(replaceBy);

        updateTree(updateFrom);
    }

    void destroy(DataCenter* dc){
        remove(dc);
        delete dc;
    }

    //TODO: Jonathan (4) orders
    int** inOrder(){

    }
    int** postOrder(){

    }
    int** preOrder(){

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

    /**findReplacement
     * find a replacement for the node, and reap it from it's place.
     * i.e. sets the replacements right son to its father as a left son
     * === Does not change any other value ===
     * @param node
     * @return
     */
    static AVLNode* findReplacement(const AVLNode* node, AVLNode*& updateFrom){
        AVLNode* iterator = node->getRightSon();
        assert(iterator != nullptr);
        while(iterator->getLeftSon() != nullptr)
            iterator = iterator->getLeftSon();

        updateFrom = iterator->getFather();
        iterator->getFather()->setLeftSon(iterator->getRightSon());

        return iterator;
    }

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


    //TODO: Amir - enjoy
    void rollRR(AVLNode* nodeToRoll);
    static void rollLL(AVLNode* nodeToRoll){
        assert(nodeToRoll != nullptr);

        AVLNode* temp = nodeToRoll->getLeftSon();
        nodeToRoll->setLeftSon(temp->getRightSon());
        temp->setRightSon(nodeToRoll);
    }

    /** picture better than thousand words... so...
     *  Tree before:
     *                  nodeToRoll
     *      nodeToRoll(l)               A
     *                          B           A(r)
     *                     B(l)     B(r)
     *
     *   Tree after:
     *                           B
     *       NodeToRoll                     A
     *                  B(l)          B(r)      A(r)
     *
     * @param nodeToRoll
     */
    static void rollRL(AVLNode* nodeToRoll){
        assert(nodeToRoll != nullptr);
        AVLNode* tempA = nodeToRoll->getRightSon();
        AVLNode* tempB = tempA->getLeftSon();

        nodeToRoll->setRightSon(tempB->getLeftSon());
        tempA->setLeftSon(tempB->getRightSon());

        tempB->setRightSon(tempA);
        tempB->setLeftSon(nodeToRoll);
    }
    //TODO: Amir - enjoy
    void rollLR(AVLNode* nodeToRoll);
};


#endif //_AVLTREE_H