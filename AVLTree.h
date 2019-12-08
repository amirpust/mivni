#ifndef _AVLTREE_H
#define _AVLTREE_H

#include <cassert>
#include <iostream>
#include "AVLNode.h"
#include "DataStructureExceptions.h"

//TODO: For debugging
using namespace std;

typedef enum{
    leftSon = -1,
    tempSon = 0,
    rightSon = 1
}Sons;

/** AVL Tree
 * To use this class, please send ad a template 2 classes.
 * @tparam: Data - the data the tree will keep.
 * operator* of Data will provide the key.
 * @tparam Compare - A function object that can Compare between 2 Data or
 * between Data to key
 *  positive number in case data1 > data2
 * negative number in case data1 < data2
 * 0 in case data1 == data2
 */
 template <class Data, class Key>
class AVLTree {
    AVLNode<Data, Key>* root;  //Dummy Root - the left son is the real first node
    bool isManagedMemory;
public:
    explicit AVLTree(bool _isManagedMemory = false) : isManagedMemory(_isManagedMemory){
        root = new AVLNode<Data, Key>(nullptr);
    };
    ~AVLTree(){
        removeAll(root->getLeftSon());
        delete root;
    };

    /**
     * @param data
     * @throws OutOfMemory
     * @throws AlreadyExists
     * @throws NullArg
     */
    void insert(Data& data, const Key& key){
        if(data == nullptr || key == nullptr)
            throw NullArg();



        Sons son;
        AVLNode<Data, Key>* father = findFather(key, &son);

        assert( father != nullptr);
        AVLNode<Data, Key>* newNode;
        try{
            newNode = new AVLNode<Data, Key>(data);
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

    /**
     * @param Key
     * @return Pointer to the data connected to this key
     * @throws DoesntExists
     */
    Data* findData(Key key){
        return findNode(key)->getCurrentData();
    }

    /**
     * remove just remove the node from the tree - *without deleting the Data*
     * @param Key
     * @throws DoesntExists
     */
    void remove(Key key){
        AVLNode<Data, Key>* node = findNode(key);
        removeNode(node);
    }

    void remove(Data& data){
        AVLNode<Data, Key>* node = findNode(data);
        removeNode(node);
    }


    //TODO: for debugging - delete before sub
    void printInOrder(){
        printInOrderAux(root->getLeftSon());
    }

    /**
     *
     * @param keys
     * @param numOfKeys
     * @throws DoesntExists - in case of empty tree
     */
    void getKeysInOrder(Key** keys, const int numOfKeys){
        int index = 0;
        if(root->getLeftSon() == nullptr)
            throw DoesntExists();
        getKeysInOrderAux(keys, numOfKeys, &index, root->getLeftSon());
    }

private:
    void getKeysInOrderAux(Key** keys, const int numOfKeys, int* index, AVLNode<Data, Key>* node){
        if( *index >= numOfKeys || node == nullptr)
            return;
        getKeysInOrderAux(keys,numOfKeys,index,node->getLeftSon());
        (*keys)[(*index)] = *(*(node->getCurrentData()));
        *index = *index + 1;
        getKeysInOrderAux(keys,numOfKeys,index,node->getRightSon());
    }
    /**
     * remove the tree which r is its root bt post order
     * @param r
     */
    void removeAll(AVLNode<Data, Key>* r){
        if(r == nullptr)
            return;
        removeAll(r->getLeftSon());
        removeAll(r->getRightSon());
        removeNode(r);
    }

    void removeNode(AVLNode<Data, Key>* node){
        AVLNode<Data, Key>* replacement = nullptr;
        AVLNode<Data, Key>* repFather = nullptr;

        findReplacement(node, &replacement,&repFather);

        bool nodeIsRightSon = node->getFather()->getRightSon()==node;
        if(nodeIsRightSon)
            node->getFather()->setRightSon(replacement);
        else
            node->getFather()->setLeftSon(replacement);

        if(node->getRightSon() == nullptr){

        }else if(node->getRightSon() == replacement){
            replacement->setLeftSon(node->getLeftSon());
        }else{
            repFather->setLeftSon(replacement->getRightSon());
            replacement->setLeftSon(node->getLeftSon());
            replacement->setRightSon(node->getRightSon());
        }

        if(isManagedMemory)
            delete node->getCurrentData();
        delete node;
        updateTree(repFather);
    }

    //TODO: for debugging
    void printInOrderAux(AVLNode<Data, Key>* node){
        if(node == nullptr)
            return;
        printInOrderAux(node->getLeftSon());
        cout << *(node->getCurrentData()) << endl;
        printInOrderAux(node->getRightSon());

    }

    /** Read:
 * Inside every data there is a ptr to the node, this function will be used
 * only in case we need to find the node that contains the real data by a dummy that carries the same id.    *
 * @param data - dummy data that helps us find the real data through the right
 * Compare function
 * @return AVLNode* of the Node that has the data or nullptr in case the data do not exists.
 * @throws DoesntExists
 */
    AVLNode<Data, Key>* findNode(Key key){
        AVLNode<Data, Key>* temp = root->getLeftSon();
        while(temp != nullptr){
            if(compare(*(temp->getCurrentData()), key) == 0)
                return temp;
            if(compare(*(temp->getCurrentData()), key) < 0)
                temp = temp->getRightSon();
            else
                temp = temp->getLeftSon();
        }
        throw DoesntExists();
    }

    AVLNode<Data, Key>* findNode(Data& data){
        AVLNode<Data, Key>* temp = root->getLeftSon();
        while(temp != nullptr){
            if(compare(*(temp->getCurrentData()), data) == 0)
                return temp;
            if(compare(*(temp->getCurrentData()), data) < 0)
                temp = temp->getRightSon();
            else
                temp = temp->getLeftSon();
        }
        throw DoesntExists();
    }

    /**
 * Find the legitimate father of the data.
 * Used mainly to find a place to a new node.
 * @param data the
 * @param son is an int ptr that holds where the son needs to be.
 * @return
 * The AVLNode to the father
 * @throws
 *  AlreadyExists
 */
    AVLNode<Data, Key>* findFather(Key& key, Sons* son){
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
        assert(false); //not suppose to reach here
    }

    /**findReplacement
     * find a replacement for the node, and reap it from it's place.
     * i.e. sets the replacements right son to its father as a left son
     * === Does not change any other value ===
     * @param node
     * @return
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

    /**
     * Update the Tree by Data < Operators.
     *
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

    //Rolls
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