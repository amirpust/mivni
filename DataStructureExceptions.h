#ifndef _DataStructureExceptionS_H
#define _DataStructureExceptionS_H

#include <exception>
#include "library1.h"

using std::exception;

class DataStructureException: public exception{
public:
    StatusType statusType;
};

class OutOfMemory : public DataStructureException{
public:
    StatusType statusType = ALLOCATION_ERROR;
};

class AlreadyExists: public DataStructureException{
public:
    StatusType statusType = FAILURE;
};

class InvalidInput: public DataStructureException{
public:
    StatusType statusType = INVALID_INPUT;
};

class NullArg: public DataStructureException{
public:
    StatusType statusType = FAILURE;
};

class DoesntExists: public DataStructureException{
public:
    StatusType statusType = FAILURE;
};

class NoFreeServers: public DataStructureException{
public:
    StatusType statusType = FAILURE;
};

class AlreadyFree: public DataStructureException{
public:
    StatusType statusType = FAILURE;
};


#endif //_DataStructureExceptionS_H
