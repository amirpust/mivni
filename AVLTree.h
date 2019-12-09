#ifndef _AVLTREE_H
#define _AVLTREE_H

#include <cassert>
#include <iostream>
#include "AVLNode.h"
#include "DataStructureExceptions.h"

//TODO: For debugging
using namespace std;

typedef enum{
    leftSon,
    rightSon
}Sons;

/** AVL Tree
 * To use this class, please send as a template 2 classes.
 * @tparam: Data - the data the tree will keep.
 * Requirments:
 * operator =
 * copyCtor (...)
 * empty Ctor () - for a dummy root
 * @tparam Key - the tree will arrange itself according to it.
 * Requirments:
 * operator ==
 * operator >
 * copyCtor (...)
 * empty Ctor () - for a dummy root
 */
 template <class Data, class Key>
class AVLTree {
    AVLNode<Data, Key>* root;  //Dummy Root- the left son is the real first node
public:
    /** c'tor
     * @throws OutOfMemory in case of bad allocation
     * @time_complexity O(1)
     * @memory_complexity O(1)
     */
    explicit AVLTree(){
        try {
            root = new AVLNode<Data, Key>(nullptr);
        }catch (exception e){
            throw OutOfMemory();
        }
    };

    /** D'tor
     * Clean the tree, and destroy the instance.
     * @time_complexity number of keys in the tree
     * @memory_complexity log(number of keys in the tree)
     */
    ~AVLTree(){
        treeClear();
        delete root;
    };

    /** insert
     * This function receive a data and a key and save a replica of them
     * Please note that to avoid memory leak, the function that calls to this
     * one shouldn't save the data nor the key.
     * @param data
     * @param key
     * @throws OutOfMemory: in case of bad allocation
     * @throws AlreadyExists: in case the key already exists
     * @time_complexity log(number of keys in the tree)
     * @memory_complexity log(number of keys in the tree)
     */
    void insert(Data data, const Key key){
        Sons son;
        AVLNode<Data, Key>* father = findFather(key, &son);

        assert( father != nullptr);
        AVLNode<Data, Key>* newNode;
        try{
            newNode = new AVLNode<Data, Key>(data,key);
        }catch(exception& e) {
            throw OutOfMemory();
        }

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

    /** findData
     * Returns the data which is connected to the provided key
     * @param key
     * @return Pointer to the data connected to this key
     * @throws DoesntExists
     * @time_complexity log(number of keys in the tree)
     * @memory_complexity log(number of keys in the tree)
     */
    Data* findData(const Key& key){
        return findNode(key)->getCurrentData();
    }

    /** remove
     * Remove the node from the tree, and update the tree accordingly
     * @param Key
     * @throws DoesntExists
     * @time_complexity log(number of keys in the tree)
     * @memory_complexity log(number of keys in the tree)
     */
    void remove(const Key& key){
        AVLNode<Data, Key>* node = findNode(key);
        removeNode(node);
    }

    /** printInOrder
     * Print the data in order. The data should have << operator.
     * Useful function for debugging
     * @time_complexity number of keys in the tree
     * @memory_complexity log(number of keys in the tree)
     */
    void printInOrder(){
        printInOrderAux(root->getLeftSon());
    }

    /** getDataInOrder
     * Receive a Data**, that already point on allocated memory, and it's size.
     * After the call to this function the first numOfData data in the tree will
     * have a replica in the data param.
     * Please note that to avoid sigmentaion failure numOfData should be
     * equal or smaller than number of keys in the tree.
     * @param keys
     * @param numOfKeys
     * @throws DoesntExists - in case of empty tree
     * @time_complexity numOfData(param) + log(number of keys in the tree)
     * @memory_complexity log(number of keys in the tree)
     */
    void getDataInOrder(Data** data, const int numOfData){
        int index = 0;
        if(root->getLeftSon() == nullptr)
            throw DoesntExists();
        getDataInOrderAux(data, numOfData, &index, root->getLeftSon());
    }

    /** treeClear
     * Delete all the data&keys in the tree.
     * @time_complexity number of keys in the tree
     * @memory_complexity log(number of keys in the tree)
     */
    void treeClear(){
        removeAll(root->getLeftSon());
    }

// =============== private functions ===============
private:

    /** getDataInOrderAux
     * A Recursion function which helps the getDataInOrder
     * @param data
     * @param numOfData
     * @param index
     * @param node
     */
    void getDataInOrderAux(Data** data, const int numOfData, int* index,
            AVLNode<Data, Key>* node){
        if( *index >= numOfData || node == nullptr)
            return;
        getDataInOrderAux(data,numOfData,index,node->getLeftSon());
        (*data)[(*index)] = *(node->getCurrentData());
        *index = *index + 1;
        getDataInOrderAux(data,numOfData,index,node->getRightSon());
    }

    /** removeAll
     * Remove the tree which node is its root by post order.
     * @param node
     */
    void removeAll(AVLNode<Data, Key>* node){
        if(node == nullptr)
            return;
        removeAll(node->getLeftSon());
        removeAll(node->getRightSon());
        delete node;
    }

    /** removeNode
     * Remove the node from the tree and update it (rolls, etc)
     * @param node
     */
    void removeNode(AVLNode<Data, Key>* node){
        AVLNode<Data, Key>* replacement = nullptr;
        AVLNode<Data, Key>* repFather = nullptr;

        findReplacement(node, &replacement,&repFather);


        if(node->isRightSon())
            node->getFather()->setRightSon(replacement);
        else
            node->getFather()->setLeftSon(replacement);

        if(node->getRightSon() == nullptr){
            //No special treatment
        }else if(node->getRightSon() == replacement){
            replacement->setLeftSon(node->getLeftSon());
        }else{
            repFather->setLeftSon(replacement->getRightSon());
            replacement->setLeftSon(node->getLeftSon());
            replacement->setRightSon(node->getRightSon());
        }

        delete node;
        updateTree(repFather);
    }

    /**printInOrderAux
     * A Recursion function which helps the printInOrder
     * @param node
     */
    void printInOrderAux(AVLNode<Data, Key>* node){
        if(node == nullptr)
            return;
        printInOrderAux(node->getLeftSon());
        cout << *(node->getCurrentData()) << endl;
        printInOrderAux(node->getRightSon());

    }

    /** findNode
    * Find the node which contains the key.
    * @param key
    * @return AVLNode*
    * @throws DoesntExists
    */
    AVLNode<Data, Key>* findNode(const Key& key){
        AVLNode<Data, Key>* temp = root->getLeftSon();
        while(temp != nullptr){
            if(key == temp->getKey())
                return temp;
            if(key > temp->getKey())
                temp = temp->getRightSon();
            else
                temp = temp->getLeftSon();
        }
        throw DoesntExists();
    }

    /**
    * Find the legitimate father of the data.
    * Used mainly to find a place to a new node.
    * @param key
    * @param son is a ptr that holds where the son needs to be.
    * @return The AVLNode to the father
    * @throws AlreadyExists
    */
    AVLNode<Data, Key>* findFather(const Key& key, Sons* son){
        AVLNode<Data, Key>* toCheck = root->getLeftSon();
        if(toCheck == nullptr){
            *son = leftSon;
            return root;
        }
        while(toCheck!= nullptr){
            if( key == toCheck->getKey()){
                throw AlreadyExists();
            }else if(key > toCheck->getKey()){
                if(toCheck->getRightSon() == nullptr){
                    *son = rightSon;
                    return toCheck;
                }
                toCheck = toCheck->getRightSon();
            }else{
                if(toCheck->getLeftSon() == nullptr){
                    *son = leftSon;
                    return toCheck;
                }
                toCheck = toCheck->getLeftSon();
            }
        }
        return nullptr;
    }

    /**findReplacement
     * find a replacement for the node.
     * === Does not change any other value ===
     * @param nodeToReplace
     * @param replacement a ptr that will point to the replacement after this
     * call
     * @param repFather a ptr that will point to the the tree will need to start
     * update from after this call.
     * except 1 edge case - it will be the replacement father
     */
    void findReplacement(const AVLNode<Data, Key>* nodeToReplace,AVLNode<Data, Key>** replacement ,AVLNode<Data, Key>** repFather){
        assert(nodeToReplace != nullptr);
        if(nodeToReplace->getRightSon() == nullptr){
            *replacement = nodeToReplace->getLeftSon();
            *repFather = nodeToReplace->getFather();
        }else if(nodeToReplace->getRightSon()->getLeftSon() == nullptr){
            *replacement = nodeToReplace->getRightSon();
            *repFather = *replacement;
        }else{
            AVLNode<Data, Key>* iter = nodeToReplace->getRightSon();
            while(iter->getLeftSon() != nullptr)
                iter = iter->getLeftSon();
            *replacement = iter;
            *repFather = iter->getFather();
        }
    }

    /** updateTree
     * Update the tree from the param up in this order:
     *      check if the node is the root
     *      update high and BF of the node
     *      check if the hight changes
     *      check if the BF out of bounds
     *      roll the hell out of it
     * @param updateFrom
     */
    void updateTree(AVLNode<Data, Key>* updateFrom){
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

    /** Rolls
     * and not the tasty ones...
     * @param nodeToRoll
     */
    static void rollRR(AVLNode<Data, Key>* nodeToRoll){
        bool isRightSon = nodeToRoll->getFather()->getRightSon() == nodeToRoll;

        AVLNode<Data, Key>* temp = nodeToRoll->getRightSon();
        if(isRightSon)
            nodeToRoll->getFather()->setRightSon(temp);
        else
            nodeToRoll->getFather()->setLeftSon(temp);

        nodeToRoll->setRightSon(temp->getLeftSon());
        temp->setLeftSon(nodeToRoll);

        nodeToRoll->updateHeightsAndBF();
        temp->updateHeightsAndBF();
    }

    static void rollLL(AVLNode<Data, Key>* nodeToRoll){
        assert(nodeToRoll != nullptr);
        bool isRightSon = nodeToRoll->getFather()->getRightSon() == nodeToRoll;

        AVLNode<Data, Key>* temp = nodeToRoll->getLeftSon();
        if(isRightSon)
            nodeToRoll->getFather()->setRightSon(temp);
        else
            nodeToRoll->getFather()->setLeftSon(temp);

        nodeToRoll->setLeftSon(temp->getRightSon());
        temp->setRightSon(nodeToRoll);

        nodeToRoll->updateHeightsAndBF();
        temp->updateHeightsAndBF();
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
    static void rollRL(AVLNode<Data, Key>* nodeToRoll){
        assert(nodeToRoll != nullptr);
        bool isRightSon = nodeToRoll->getFather()->getRightSon() == nodeToRoll;

        AVLNode<Data, Key>* tempA = nodeToRoll->getRightSon();
        AVLNode<Data, Key>* tempB = tempA->getLeftSon();

        if(isRightSon)
            nodeToRoll->getFather()->setRightSon(tempB);
        else
            nodeToRoll->getFather()->setLeftSon(tempB);

        nodeToRoll->setRightSon(tempB->getLeftSon());
        tempA->setLeftSon(tempB->getRightSon());

        tempB->setRightSon(tempA);
        tempB->setLeftSon(nodeToRoll);

        nodeToRoll->updateHeightsAndBF();
        tempA->updateHeightsAndBF();
        tempB->updateHeightsAndBF();
    }

    static void rollLR(AVLNode<Data, Key>* nodeToRoll){
        assert(nodeToRoll != nullptr);
        bool isRightSon = nodeToRoll->getFather()->getRightSon() == nodeToRoll;

        AVLNode<Data, Key>* tempA = nodeToRoll->getLeftSon();
        AVLNode<Data, Key>* tempB = tempA->getRightSon();

        if(isRightSon)
            nodeToRoll->getFather()->setRightSon(tempB);
        else
            nodeToRoll->getFather()->setLeftSon(tempB);

        tempA->setRightSon(tempB->getLeftSon());
        tempB->setLeftSon(tempA);

        nodeToRoll->setLeftSon(tempB->getRightSon());
        tempB->setRightSon(nodeToRoll);

        nodeToRoll->updateHeightsAndBF();
        tempA->updateHeightsAndBF();
        tempB->updateHeightsAndBF();
    }
};


#endif //_AVLTREE_H