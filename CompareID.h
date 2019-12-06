#ifndef _COMPAREID_H
#define _COMPAREID_H


#include "DataCenter.h"

class CompareID {
public:
    int operator()(DataCenter *dataCenter, int key) {
        return dataCenter->getDataCenterId() - key;
    }
};


#endif //_COMPAREID_H
