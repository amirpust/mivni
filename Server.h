#ifndef MIVNI_SERVER_H
#define MIVNI_SERVER_H

#include <cstdio>

#define LINUX 0
#define WINDOWS 1

class Server{
    int os;
    int id;
    Server *next;
    Server *previous;
    bool taken;

public:
    explicit Server(int id, Server *next = nullptr, Server *previous = nullptr):
    id(id), next(next), previous(previous), os(LINUX), taken(false){}

    ~Server() = default;

    void setOs(int os) {
        Server::os = os;
    }

    int getOs(){
        return os;
    }
    bool isTaken(){
        return taken;
    }
    void setTaken(bool _taken){
        this->taken = _taken;
    }

    int getId() const {
        return id;
    }

    Server *getNext() const {
        return next;
    }

    Server *getPrevious() const {
        return previous;
    }
    void setPrevious(Server *previous) {
        Server::previous = previous;
    }
    void setNext(Server *next) {
        Server::next = next;
    }

    /**
     * Remove the Server from the list
     * Sets the next/previous to nullptr
     */
    void removeServerFromList(){
        if (previous != nullptr)
            previous->setNext(next);
        if (next != nullptr)
            next->setPrevious(previous);
        next = nullptr;
        previous = nullptr;
    }
    /**
     * Add the server to the list between the newnext to the newPrev
     * @param newNext
     * @param newPrev
     */
    void addServerToList(Server* newNext, Server* newPrev){
        next = newNext;
        previous = newPrev;
        if(newNext != nullptr)
            newNext->setPrevious(this);
        if(newPrev != nullptr)
            newPrev->setNext(this);
    }


private:

};


#endif //MIVNI_SERVER_H
