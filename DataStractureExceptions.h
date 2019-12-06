#ifndef _DATASTRACTUREEXCEPTIONS_H
#define _DATASTRACTUREEXCEPTIONS_H

#include <exception>

using std::exception;

class OutOfMemory : public exception{};
class AlreadyExists: public exception{};
class InvalidInput: public exception{};
class NullArg: public exception{};
class DoesntExists: public exception{};


#endif //_DATASTRACTUREEXCEPTIONS_H
