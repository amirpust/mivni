//
// Created by jonathan on 29/11/2019.
//

#ifndef _DATACENTER_H
#define _DATACENTER_H
#include "Server.h"

class DataCenter {
    int dataCenterID;
    int numberOfServers;
    int linuxServerNumber;
    int WindowsServerNumber;
    Server** pointerArray;
    Server* linuxListHead;
    Server* linuxListEnd;
    Server* windowsListHead;
    Server* windowsListEnd;



public:
    DataCenter(int dataCenterId, int numberOfServers);


private:
    void initializeListAndPointerArray(){
        Server* FirstServer = new Server(0);
        pointerArray[]
    }
};


#endif //_DATACENTER_H
