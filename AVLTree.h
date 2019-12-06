#ifndef _AVLTREE_H
#define _AVLTREE_H

#include <cassert>
#include <iostream>
#include "AVLNode.h"

//TODO: For debugging
using namespace std;

//TODO: Jonathan for all the class - check for error returns && add consts where its possible

typedef enum{
    leftSon = -1,
    tempSon = 0,
    rightSon = 1
}Sons;

/** AVL Tree
 * To use this class, please send ad a template 2 classes.
 * @tparam Compare - A function object that can Compare between 2 Data or
 * between Data to key
 *  positive number in case data1 > data2
 * negative number in case data1 < data2
 * 0 in case data1 == data2
 */
 template <class Data, class Key, class Compare>
class AVLTree {
    AVLNode<Data>* root;  //Dummy Root - the left son is the real first node
    Compare compare;
    bool isManagedMemory;
public:
    explicit AVLTree(bool _isManagedMemory = false) : isManagedMemory(_isManagedMemory){
        root = new AVLNode<Data>(nullptr);
        //compare();
    };
    ~AVLTree(){
        removeAll(root->getLeftSon());
        delete root;
    };

    void insert(Data* data){
        Sons son;
        AVLNode<Data>* father = findFather(data, &son);

        assert( father != nullptr);
        auto newNode = new AVLNode<Data>(data,father);


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
     * @param Key
     * @return Pointer to the data connected to this key
     */
    Data* findData(Key key){
        return findNode(key)->getCurrentData();
    }

    /**
     * remove just remove the node from the tree - *without deleting the Data*
     * @param Key
     */
    void remove(Key key){
        AVLNode<Data>* node = findNode(key);
        assert(node != nullptr); //TODO: Exception Key do not exist
        removeNode(node);
    }

    //TODO: for debugging - delete before sub
    void printInOrder(){
        printInOrderAux(root->getLeftSon());
    }

private:
    /**
     * remove the tree which r is its root bt post order
     * @param r
     */
    void removeAll(AVLNode<Data>* r){
        if(r == nullptr)
            return;
        removeAll(r->getLeftSon());
        removeAll(r->getRightSon());
        removeNode(r);
    }

    void removeNode(AVLNode<Data>* node){
        bool nodeIsRightSon = node->getFather()->getRightSon()==node;
        if(node->getRightSon() == nullptr){
            if(nodeIsRightSon)
                node->getFather()->setRightSon(node->getLeftSon());
            else
                node->getFather()->setLeftSon(node->getLeftSon());

            if(isManagedMemory)
                delete node->getCurrentData();
            delete node;
            return;
        }
        AVLNode<Data>* updateFrom = nullptr;
        AVLNode<Data>* replaceBy = findReplacement(node, updateFrom);
        assert(updateFrom != nullptr);

        //Sets the replacement sons
        replaceBy->setRightSon(node->getRightSon());
        replaceBy->setLeftSon(node->getLeftSon());

        //set the father ti point on the replacement
        if(nodeIsRightSon)
            node->getFather()->setRightSon(replaceBy);
        else
            node->getFather()->setLeftSon(replaceBy);

        if(isManagedMemory)
            delete node->getCurrentData();

        updateTree(updateFrom);
    }

    void printInOrderAux(AVLNode<Data>* node){
        if(node == nullptr)
            return;
        cout << *(node->getCurrentData()) << endl;
        printInOrderAux(node->getLeftSon());
        printInOrderAux(node->getRightSon());

    }

    /** Read:
 * Inside every data there is a ptr to the node, this function will be used
 * only in case we need to find the node that contains the real data by a dummy that carries the same id.    *
 * @param data - dummy data that helps us find the real data through the right
 * Compare function
 * @return AVLNode* of the Node that has the data or nullptr in case the data do not exists.
 */
    AVLNode<Data>* findNode(Key key){
        AVLNode<Data>* temp = root->getLeftSon();
        while(temp != nullptr){
            if(compare(temp->getCurrentData(),key) == 0)
                return temp;
            if(compare(key, temp->getCurrentData()) > 0)
                temp = temp->getRightSon();
            else
                temp = temp->getLeftSon();
        }
        return nullptr;
    }

    /**
 * Find the legitimate father of the data.
 * Used mainly to find a place to a new node.
 * @param data the
 * @param son is an int ptr that holds where the son needs to be.
 * @return
 * The AVLNode to the father
 */
    AVLNode<Data>* findFather(Data* data, Sons* son){
        AVLNode<Data>* temp = root->getLeftSon();
        if(temp == nullptr){
            *son = leftSon;
            return root;
        }

        while(temp != nullptr){
            if(compare(temp->getCurrentData(),data) == 0){
                *son = tempSon;
                return nullptr; //TODO: Exception - already exists
            }
            if(compare(data, temp->getCurrentData()) > 0){
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
    static AVLNode<Data>* findReplacement(const AVLNode<Data>* node, AVLNode<Data>*& updateFrom){
        AVLNode<Data>* iterator = node->getRightSon();
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
    void updateTree(AVLNode<Data>* updateFrom){
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

    //Rolls
    static void rollRR(AVLNode<Data>* nodeToRoll){
        assert(nodeToRoll != nullptr);
        bool isRightSon = nodeToRoll->getFather()->getRightSon() == nodeToRoll;

        AVLNode<Data>* temp = nodeToRoll->getRightSon();
        if(isRightSon)
            nodeToRoll->getFather()->setRightSon(temp);
        else
            nodeToRoll->getFather()->getLeftSon(temp);

        nodeToRoll->setRightSon(temp->getLeftSon());
        temp->setLeftSon(nodeToRoll);


    }
    static void rollLL(AVLNode<Data>* nodeToRoll){
        assert(nodeToRoll != nullptr);

        AVLNode<Data>* temp = nodeToRoll->getLeftSon();
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
    static void rollRL(AVLNode<Data>* nodeToRoll){
        assert(nodeToRoll != nullptr);
        AVLNode<Data>* tempA = nodeToRoll->getRightSon();
        AVLNode<Data>* tempB = tempA->getLeftSon();

        nodeToRoll->setRightSon(tempB->getLeftSon());
        tempA->setLeftSon(tempB->getRightSon());

        tempB->setRightSon(tempA);
        tempB->setLeftSon(nodeToRoll);
    }
    static void rollLR(AVLNode<Data>* nodeToRoll){
        assert(nodeToRoll != nullptr);

        AVLNode<Data>* tempA = nodeToRoll->getLeftSon();
        AVLNode<Data>* tempB = tempA->getRightSon();

        tempA->setRightSon(tempB->getLeftSon());
        tempB->setLeftSon(tempA);

        nodeToRoll->setLeftSon(tempB->getRightSon());
        tempB->setRightSon(nodeToRoll);
    }
};


#endif //_AVLTREE_H