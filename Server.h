#ifndef MIVNI_SERVER_H
#define MIVNI_SERVER_H

#include <stdio.h>

Class Server{
    int os;
    int id;
    Server* next;
    Server* previous;
    bool taken;

public:
    Server(int id, Server* next = NULL, Server* previous = NULL){

    }
};


#endif //MIVNI_SERVER_H
