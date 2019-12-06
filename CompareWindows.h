#ifndef _COMPAREWINDOWS_H
#define _COMPAREWINDOWS_H


#include "DataCenter.h"

class CompareWindows {
public:
    int operator()(DataCenter *dataCenter1, DataCenter *dataCenter2) {
        int result = dataCenter1->getwindowsServerNumber() - dataCenter2->getwindowsServerNumber();
        if (result)
            return result;
        return dataCenter1->getDataCenterId() - dataCenter2->getDataCenterId();
    }

    int operator()(DataCenter* dataCenter,int key){

    }
};


#endif //_COMPAREWINDOWS_H
