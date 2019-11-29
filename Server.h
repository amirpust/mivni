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

    /**
     * The Function switch between OS's and already remove/add it from/to the new list.
     * Need the new list ptr's - can be nullptr (that's why it need both)
     * @param newNext: the new next ptr for the new list
     * @param newPrev: the new previous ptr for the new list
     */
    void switchOs (Server* newNext, Server* newPrev){
        if(taken)
            return; //TODO: throw
        removeServerFromList();
        os = 1 - os;
        addServerToList(newNext,newPrev);
        taken = true;
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


private:
    void removeServerFromList(){
        if (previous != nullptr)
            previous->next = next;
        if (next != nullptr)
            next->previous = previous;
    }
    void addServerToList(Server* newNext, Server* newPrev){
        next = newNext;
        previous = newPrev;
        if(newNext != nullptr)
            newNext->previous=this;
        if(newPrev != nullptr)
            newPrev->next=this;
    }
};


#endif //MIVNI_SERVER_H
