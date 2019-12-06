#ifndef _COMPAREINT_H
#define _COMPAREINT_H

//TODO: fix compares
class CompareInt{
public:
    int operator()(int* value1, int value2) {
        return *value1-value2;
    }
    int operator()(int* value1, int* value2) {
        return *value1-*value2;
    }
};

#endif
