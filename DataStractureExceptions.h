#ifndef _DATASTRACTUREEXCEPTIONS_H
#define _DATASTRACTUREEXCEPTIONS_H

#include <exception>
#include "library1.h"

using std::exception;

class OutOfMemory : public exception{
public:
    StatusType statusType = ALLOCATION_ERROR;
};

class AlreadyExists: public exception{
public:
    StatusType statusType = FAILURE;
};

class InvalidInput: public exception{
public:
    StatusType statusType = INVALID_INPUT;
};

class NullArg: public exception{
public:
    StatusType statusType = FAILURE;
};

class DoesntExists: public exception{
public:
    StatusType statusType = FAILURE;
};

class NoFreeServers: public exception{
public:
    StatusType statusType = FAILURE;
};

class AlreadyFree: public exception{
public:
    StatusType statusType = FAILURE;
};

#endif //_DATASTRACTUREEXCEPTIONS_H
