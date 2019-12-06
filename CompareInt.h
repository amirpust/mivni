#ifndef _COMPAREINT_H
#define _COMPAREINT_H

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
