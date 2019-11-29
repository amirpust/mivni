#ifndef _DATACENTER_H
#define _DATACENTER_H

#include "Server.h"

class DataCenter {
    int dataCenterID;
    int numberOfServers;
    int linuxServerNumber;
    int windowsServerNumber;
    Server **pointerArray;
    Server *linuxListHead;
    Server *linuxListEnd;
    Server *windowsListHead;
    Server *windowsListEnd;

public:
    DataCenter(int dataCenterId, int numberOfServers);

    int getDataCenterId() const;

    int getLinuxServerNumber() const;

    int getwindowsServerNumber() const;

    int getNumberOfServers() const;

    const bool operator>(const DataCenter &dataCenter) const;

    const bool operator==(const DataCenter &dataCenter) const;

    const bool operator>(const int key) const;

    const bool operator==(const int key) const;

    //TODO: check return value
    const int requestServer(const int serverId, const int os, int *assignedServerId) {
        if(linuxServerNumber + windowsServerNumber == numberOfServers)
            return -1; //no more servers
        if (serverId > numberOfServers || pointerArray[serverId]->isTaken()) {
            getServerByOs(os,assignedServerId);
            return 1; //success
        }

        pointerArray[serverId]->setTaken(true);
        pointerArray[serverId]->removeServerFromList();
        *assignedServerId = serverId;
        return 1;
    }

private:
    void initializeListAndPointerArray();

    void getServerByOs(int os, int *assignedServerId) {
        if (os && windowsListHead->getNext() != windowsListEnd) {
            assignServer(assignedServerId,windowsListHead->getNext()->getId());
        } else if (os) {
            assignServer(assignedServerId,linuxListHead->getNext()->getId());
            pointerArray[linuxListHead->getNext()->getId()]->setOs(os);
            linuxServerNumber--;
            windowsServerNumber++;
        } else if(linuxListHead->getNext() != linuxListEnd){
            assignServer(assignedServerId,linuxListHead->getNext()->getId());
        }else {
            assignServer(assignedServerId,windowsListHead->getNext()->getId());
            pointerArray[windowsListHead->getNext()->getId()]->setOs(os);
            linuxServerNumber++;
            windowsServerNumber++;
        }
    }

    void assignServer(int* assignedServerId, int serverId){
        pointerArray[serverId]->setTaken(true);
        pointerArray[serverId]->removeServerFromList();
        *assignedServerId = serverId;
    }
};


#endif //_DATACENTER_H
