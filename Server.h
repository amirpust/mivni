#ifndef MIVNI_SERVER_H
#define MIVNI_SERVER_H

#include <stdio.h>

#define LINUX 0
#define WINDOWS 1

class Server{
    int os;
    int id;
    Server* next;
    Server* previous;
    bool taken;

public:
    explicit Server(int id, Server* next = NULL, Server* previous = NULL): id(id), next(next), previous(previous){
        os = LINUX;
        taken = false;
    }
};


#endif //MIVNI_SERVER_H
