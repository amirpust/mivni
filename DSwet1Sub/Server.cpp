//
// Created by jonat on 29/11/2019.
//

#include "Server.h"

void Server::setOs(int os) {
    Server::os = os;
}

int Server::getOs() {
    return os;
}

bool Server::isTaken() {
    return taken;
}

void Server::setTaken(bool _taken) {
    this->taken = _taken;
}

int Server::getId() const {
    return id;
}

Server *Server::getNext() const {
    return next;
}

Server *Server::getPrevious() const {
    return previous;
}

void Server::setPrevious(Server *previous) {
    Server::previous = previous;
}

void Server::setNext(Server *next) {
    Server::next = next;
}

void Server::removeServerFromList() {
    if (previous != nullptr)
        previous->setNext(next);
    if (next != nullptr)
        next->setPrevious(previous);
    next = nullptr;
    previous = nullptr;
}

void Server::addServerToList(Server *newNext, Server *newPrev) {
    next = newNext;
    previous = newPrev;
    if(newNext != nullptr)
        newNext->setPrevious(this);
    if(newPrev != nullptr)
        newPrev->setNext(this);
}
