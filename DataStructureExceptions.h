#ifndef _DataStructureExceptionS_H
#define _DataStructureExceptionS_H

#include <exception>
#include "library1.h"

using std::exception;

class DataStructureException: public exception{
public:
    StatusType statusType;
    explicit DataStructureException(StatusType s):statusType(s){};
};

class OutOfMemory : public DataStructureException{
public:
    OutOfMemory():
            DataStructureException(ALLOCATION_ERROR){};
};

class AlreadyExists: public DataStructureException{
public:
    AlreadyExists():
            DataStructureException(FAILURE){};
};

class InvalidInput: public DataStructureException{
public:
    InvalidInput():
            DataStructureException(INVALID_INPUT){};
};

class NullArg: public DataStructureException{
public:
    NullArg():
            DataStructureException(FAILURE){};
};

class DoesntExists: public DataStructureException{
public:
    DoesntExists():
            DataStructureException(FAILURE){};
};

class NoFreeServers: public DataStructureException{
public:
    NoFreeServers():
            DataStructureException(FAILURE){};
};

class AlreadyFree: public DataStructureException{
public:
    AlreadyFree():
            DataStructureException(FAILURE){};
};


#endif //_DataStructureExceptionS_H
