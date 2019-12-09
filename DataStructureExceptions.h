#ifndef _DataStructureExceptionS_H
#define _DataStructureExceptionS_H

#include <exception>
#include "library1.h"

using std::exception;

class DataStructureException: public exception{
public:
    explicit DataStructureException() = default;
    virtual StatusType getException() = 0;
};

class OutOfMemory : public DataStructureException{
public:
    StatusType getException() override {
        return ALLOCATION_ERROR;
    }
};

class AlreadyExists: public DataStructureException{
public:
    StatusType getException() override {
        return FAILURE;
    }
};

class InvalidInput: public DataStructureException{
public:
    StatusType getException() override {
        return INVALID_INPUT;
    }
};

class NullArg: public DataStructureException{
public:
    StatusType getException() override {
        return FAILURE;
    }
};

class DoesntExists: public DataStructureException{
public:
    StatusType getException() override {
        return FAILURE;
    }
};

class NoFreeServers: public DataStructureException{
public:
    StatusType getException() override {
        return FAILURE;
    }
};

class AlreadyFree: public DataStructureException{
public:
    StatusType getException() override {
        return FAILURE;
    }
};

#endif //_DataStructureExceptionS_H
