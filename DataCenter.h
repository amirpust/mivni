//
// Created by jonathan on 29/11/2019.
//

#ifndef _DATACENTER_H
#define _DATACENTER_H
#include "Server.h"

class DataCenter {
private:
    int dataCenterID;
    int numberOfServers;
    int linuxServerNumber;
    int WindowsServerNumber;
    Server** pointerArray;
    Server* linuxListHead;
    Server* linuxListend;
    Server* windowsListHead;
    Server* windowsListend;
public:
    DataCenter(int dataCenterId, int numberOfServers);

};


#endif //_DATACENTER_H
