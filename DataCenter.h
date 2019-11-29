//
// Created by jonathan on 29/11/2019.
//

#ifndef _DATACENTER_H
#define _DATACENTER_H
#include "Server.h"
//TODO implement '<'

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

    int getDataCenterId() const;

    int getLinuxServerNumber() const;

    int getWindowsServerNumber() const;

    int getNumberOfServers() const;

private:
    void initializeListAndPointerArray(){
        auto firstServer = new Server(0); //TODO: OOM throw
        firstServer->setPrevious(linuxListHead);
        firstServer->setNext(linuxListEnd);
        pointerArray[0]=firstServer;
        for (int i = 1; i < numberOfServers; ++i) {
            auto temp = new  Server(i);
            pointerArray[i-1]->setNext(temp);
            pointerArray[i] = temp;
            temp->setNext(linuxListEnd);
            temp->setPrevious(pointerArray[i-1]);
        }
        linuxListEnd->setPrevious(pointerArray[numberOfServers-1]);
    }
};


#endif //_DATACENTER_H
