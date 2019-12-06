#ifndef _COMPARELINUX_H
#define _COMPARELINUX_H

#include "DataCenter.h"

class CompareLinux {
public:
    /**
     * I don't take into account the fact that the os is the same
     * @param dataCenter1
     * @param dataCenter2
     * @return
     * Positive int if there are more Linux servers in dataCenter1.
     * If equal .
     * Negative int otherwise.
     */
    int operator()(DataCenter &dataCenter1, DataCenter &dataCenter2) const {
        int result = dataCenter1.getLinuxServerNumber() - dataCenter2.getLinuxServerNumber();

        if (result)
            return result;
        return dataCenter2.getDataCenterId() - dataCenter2.getDataCenterId();
    }


    /**
     * @param dataCenter
     * @param key - data center's ID.
     * @return
     * Positive int if there are more dataCenter's key is bigger.
     * 0 - if they are equal.
     * Negative int otherwise.
     */
    int operator()(DataCenter &dataCenter, int key) {
        return dataCenter.getDataCenterId() - key;
    }
};


#endif //_COMPARELINUX_H
