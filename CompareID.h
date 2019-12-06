#ifndef _COMPAREID_H
#define _COMPAREID_H

#include <memory>
#include "DataCenter.h"

class CompareID {
public:
    int operator()(DataCenter &dataCenter, int key) {
        return dataCenter.getDataCenterId() - key;
    }

    int operator()(DataCenter &dataCenter1, DataCenter &dataCenter2) {
        return dataCenter1.getDataCenterId() - dataCenter2.getDataCenterId();
    }
};


#endif //_COMPAREID_H
