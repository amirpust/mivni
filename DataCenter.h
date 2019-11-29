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
    Server **pointerArray;
    Server *linuxListHead;
    Server *linuxListEnd;
    Server *windowsListHead;
    Server *windowsListEnd;

public:
    DataCenter(int dataCenterId, int numberOfServers);

    int getDataCenterId() const;

    int getLinuxServerNumber() const;

    int getWindowsServerNumber() const;

    int getNumberOfServers() const;

    const bool operator>(const DataCenter &dataCenter) const;

    const bool operator==(const DataCenter &dataCenter) const;

    const bool operator>(const int key) const;

    const bool operator==(const int key) const;

    //TODO: check return value
    const int requestServer(const int serverId, const int os, int *assignedServerId) {
        if (serverId > numberOfServers || pointerArray[serverId]->isTaken()) {

        }


    }

private:
    void initializeListAndPointerArray();

    bool getServerByOS
};


#endif //_DATACENTER_H
