#ifndef _NODE_H
#define _NODE_H

#include <cstdio>
#include <cmath>
#include "Server.h"
#include "DataCenter.h"

/** AVLNode
 * A helper class to manage the AVL tree
 * @tparam Data
 * @tparam Key
 */
template<class Data, class Key>
class AVLNode {
private:
    Data currentData;
    const Key key;

    AVLNode<Data, Key> *father;
    AVLNode<Data, Key> *rightSon;
    AVLNode<Data, Key> *leftSon;

    int nodeHeight;
    int bf;

public:

    AVLNode(Data &currentData, const Key &key, AVLNode<Data, Key> *father = nullptr,
            AVLNode<Data, Key> *rightSon = nullptr,
            AVLNode<Data, Key> *leftSon = nullptr, int nodeHeight = 0, int bf = 0)
            : currentData(currentData), key(key), father(father),
              rightSon(rightSon), leftSon(leftSon),
              nodeHeight(nodeHeight), bf(bf) {};


    //only to create the root
    explicit  AVLNode(AVLNode<Data, Key> *leftSon, int nodeHeight = 0, int bf = 0)
            :key(Key()),father(nullptr),rightSon(nullptr), leftSon(leftSon), nodeHeight(nodeHeight), bf(bf) {};

    virtual ~AVLNode() = default;

    /** isRightSon
     * @return true if the node is the right son of it's father
     *         false otherwise
     * @throws NullArg in case father is nullptr
     */
    bool isRightSon() const {
        if(this->getFather() == nullptr){
            throw NullArg();
        }
        return this->getFather()->getRightSon() == this;
    }

    /**
    * update the heights and the BF.
    * @return
    * true: if the height is changed
    * false: otherwise
    */
    bool updateHeightsAndBF() {
        int rightSonHeight = getSonHeight(rightSon);
        int leftSonHeight = getSonHeight(leftSon);
        bf = leftSonHeight - rightSonHeight;
        if (nodeHeight != ((int) fmax(rightSonHeight, leftSonHeight) + 1)) {
            nodeHeight = (int) fmax(rightSonHeight, leftSonHeight) + 1;
            return true;
        }
        return false;
    };

    void setRightSon(AVLNode<Data, Key> *_rightSon) {
        assert(_rightSon != this);
        this->rightSon = _rightSon;
        if (rightSon != nullptr)
            rightSon->setFather(this);
    };

    void setFather(AVLNode<Data, Key> *_father) {
        AVLNode::father = _father;
    }

    void setNodeHeight(int _nodeHeight) {
        AVLNode::nodeHeight = _nodeHeight;
    }

    void setBf(int _bf) {
        AVLNode::bf = _bf;
    }

    void setLeftSon(AVLNode<Data, Key> *_leftSon) {
        leftSon = _leftSon;
        if (leftSon != nullptr)
            leftSon->setFather(this);
    };

    Data *getCurrentData() {
        return &currentData;
    }

    const Key &getKey() const {
        return key;
    }

    AVLNode<Data, Key> *getFather() const {
        return father;
    }

    AVLNode<Data, Key> *getRightSon() const {
        return rightSon;
    }

    AVLNode<Data, Key> *getLeftSon() const {
        return leftSon;
    }

    int getNodeHeight() const {
        return nodeHeight;
    }

    int getBf() const {
        return bf;
    }

private:
    int getSonHeight(AVLNode<Data, Key> *son) {
        if (son == nullptr)
            return -1;
        return son->getNodeHeight();
    };
};

#endif //_NODE_H
