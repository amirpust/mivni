#include "DataCenter.h"

DataCenter::DataCenter(int dataCenterId, int numberOfServers)
        : dataCenterID(dataCenterId), numberOfServers(numberOfServers) {
    pointerArray = new Server*[numberOfServers];
    linuxServerNumber = numberOfServers;
    windowsServerNumber =  0;

    linuxListEnd = new Server(-1);
    linuxListHead = new Server(-2);//TODO: check if we can remove magic numbers
    linuxListEnd->setPrevious(linuxListHead);
    linuxListHead->setNext(linuxListEnd);

    windowsListEnd = new Server(-3);
    windowsListHead = new Server(-4);
    windowsListEnd->setPrevious(windowsListHead);
    windowsListHead->setNext(windowsListEnd);

    unusedServers = numberOfServers;
    initializeListAndPointerArray();
}

int DataCenter::getDataCenterId() const {
    return dataCenterID;
}

int DataCenter::getNumberOfServers() const {
    return numberOfServers;
}

int DataCenter::getLinuxServerNumber() const {
    return linuxServerNumber;
}

int DataCenter::getwindowsServerNumber() const {
    return windowsServerNumber;
}

void DataCenter::initializeListAndPointerArray() {
    if(numberOfServers == 0)
        return;

    auto firstServer = new Server(0); //TODO: OOM throw

    firstServer->addServerToList(linuxListEnd,linuxListHead);
    pointerArray[0]=firstServer;

    for (int i = 1; i < numberOfServers; ++i) {
        auto temp = new  Server(i);
        temp->addServerToList(linuxListEnd,pointerArray[i-1]);
        pointerArray[i] = temp;
    }
}

const bool DataCenter::operator==(const int key) const {
    return this->getDataCenterId() == key;
}

const bool DataCenter::operator>(const int key) const {
    return this->getDataCenterId() > key;
}

const bool DataCenter::operator==(const DataCenter &dataCenter) const {
    return this->getDataCenterId() == dataCenter.getDataCenterId();
}

const bool DataCenter::operator>(const DataCenter &dataCenter) const {
    return this->getDataCenterId() > dataCenter.getDataCenterId();
}

void DataCenter::changeServerAmount(int os) {
    if (os == WINDOWS) {
        linuxServerNumber--;
        windowsServerNumber++;
        return;
    }
    linuxServerNumber++;
    windowsServerNumber--;
}

void DataCenter::giveServer(int serverId, int *assignedServerId) {

    pointerArray[serverId]->setTaken(true);
    pointerArray[serverId]->removeServerFromList();
    *assignedServerId = serverId;
}

void DataCenter::giveFreeServer(int serverId, int os, int *assignedServer) {
    if(pointerArray[serverId]->getOs() == os){
        giveServer(serverId,assignedServer);
    }
    else{
        pointerArray[serverId]->setOs(os);
        giveServer(serverId,assignedServer);
        changeServerAmount(os);
    }
}

void DataCenter::giveDifferentServer(int os, int *assignedServerId) {
    if(os == WINDOWS){
        if(windowsListHead->getNext() != windowsListEnd){
            giveServer(windowsListHead->getNext()->getId(),assignedServerId);
        }
        else {
            linuxListHead->getNext()->setOs(os);
            giveServer(linuxListHead->getNext()->getId(),assignedServerId);
            changeServerAmount(os);
        }
    }
    else{
        if(linuxListHead->getNext()!=linuxListEnd){
            giveServer(linuxListHead->getNext()->getId(),assignedServerId);
        } else{
            windowsListHead->getNext()->setOs(os);
            giveServer(windowsListHead->getNext()->getId(),assignedServerId);
            changeServerAmount(os);
        }
    }
}

ServerStatus DataCenter::requestServer(const int requestedId, const int os, int *assignedServerId) {
    if (unusedServers == 0)
        return FAILURE; //no more servers
    if (requestedId >= numberOfServers || requestedId < 0 || os > 1 || os < 0
            || assignedServerId == NULL )
        return INVALID_INPUT;
    if (!pointerArray[requestedId]->isTaken()) {
        giveFreeServer(requestedId,os,assignedServerId);
        unusedServers--;
        return SUCCESS; //success
    }
    giveDifferentServer(os,assignedServerId);
    unusedServers--;

    return SUCCESS;
}

ServerStatus DataCenter::freeServer(int serverId) {
    if (serverId >= numberOfServers || serverId < 0) {
        return INVALID_INPUT;
    }
    if (!pointerArray[serverId]->isTaken()) {
        return FAILURE;
    }

    pointerArray[serverId]->setTaken(false);

    if (pointerArray[serverId]->getOs() == WINDOWS) {
        pointerArray[serverId]->addServerToList(windowsListEnd, windowsListEnd->getPrevious());
    } else {
        pointerArray[serverId]->addServerToList(linuxListEnd, linuxListEnd->getPrevious());
    }
    unusedServers++;
    return SUCCESS;
}
