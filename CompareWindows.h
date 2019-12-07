#ifndef _COMPAREWINDOWS_H
#define _COMPAREWINDOWS_H

#include "DataCenter.h"


class CompareWindows {
public:
    int operator()(DataCenter &dataCenter1, DataCenter &dataCenter2) {
        int result = dataCenter2.getwindowsServerNumber() - dataCenter1.getwindowsServerNumber();

        if (result != 0)
            return result;
        return dataCenter1.getDataCenterId()- dataCenter2.getDataCenterId();
    }

    int operator()(DataCenter &dataCenter,int key){
        return dataCenter.getDataCenterId()- key;
    }
};


#endif //_COMPAREWINDOWS_H
