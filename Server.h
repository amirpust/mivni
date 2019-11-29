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

    void switchOs (Server* newNext, Server* newPrev){
        removeNodeFromList();
        os = 1 - os;

    }

private:
    void removeNodeFromList(){
        if (previous != nullptr)
            previous->next = next;
        if (next != nullptr)
            next->previous = previous;
    }
};


#endif //MIVNI_SERVER_H
