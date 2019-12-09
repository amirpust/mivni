#ifndef _SERVER_H
#define _SERVER_H

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
            os(LINUX), id(id), next(next), previous(previous), taken(false){}

    ~Server() = default;

    void setOs(int os);

    int getOs();

    bool isTaken();

    void setTaken(bool _taken);

    int getId() const;

    Server *getNext() const;

    Server *getPrevious() const;

    void setPrevious(Server *previous);

    void setNext(Server *next);

    /**
     * Remove the Server from the list
     * Sets the next/previous to nullptr
     */
    void removeServerFromList();
    /**
     * Add the server to the list between the newnext to the newPrev
     * @param newNext
     * @param newPrev
     */
    void addServerToList(Server* newNext, Server* newPrev);


private:

};


#endif //_SERVER_H
