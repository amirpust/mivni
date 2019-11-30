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

bool DataCenter::giveFreeServer(int serverId, int os, int *assignedServer) {
    if(pointerArray[serverId]->getOs() == os){
        giveServer(serverId,assignedServer);
        return false;
    }
    else{
        pointerArray[serverId]->setOs(os);
        giveServer(serverId,assignedServer);
        changeServerAmount(os);
        return true;
    }
}

bool DataCenter::giveDifferentServer(int os, int *assignedServerId) {
    if(os == WINDOWS){
        if(windowsListHead->getNext() != windowsListEnd){
            giveServer(windowsListHead->getNext()->getId(),assignedServerId);
            return false;
        }
        else {
            linuxListHead->getNext()->setOs(os);
            giveServer(linuxListHead->getNext()->getId(),assignedServerId);
            changeServerAmount(os);
            return true;
        }
    }
    else{
        if(linuxListHead->getNext()!=linuxListEnd){
            giveServer(linuxListHead->getNext()->getId(),assignedServerId);
            return false;
        }else{
            windowsListHead->getNext()->setOs(os);
            giveServer(windowsListHead->getNext()->getId(),assignedServerId);
            changeServerAmount(os);
            return true;
        }
    }
}

DataCenterStatus DataCenter::requestServer(const int requestedId, const int os, int *assignedServerId) {
    if (unusedServers == 0)
        return FAILURE_DC; //no more servers
    if (requestedId >= numberOfServers || requestedId < 0 || os > 1 || os < 0
            || assignedServerId == NULL )
        return INVALID_INPUT_DC;
    if (!pointerArray[requestedId]->isTaken()) {
        if(giveFreeServer(requestedId,os,assignedServerId)){
            unusedServers--;
            return SUCCESS_CHANGE_OS_DC;
        }
        unusedServers--;
        return SUCCESS_DC; //success
    }
    if(giveDifferentServer(os,assignedServerId)){
        unusedServers--;
        return SUCCESS_CHANGE_OS_DC;
    }
    unusedServers--;
    return SUCCESS_DC;
}

DataCenterStatus DataCenter::freeServer(int serverId) {
    if (serverId >= numberOfServers || serverId < 0) {
        return INVALID_INPUT_DC;
    }
    if (!pointerArray[serverId]->isTaken()) {
        return FAILURE_DC;
    }

    pointerArray[serverId]->setTaken(false);

    if (pointerArray[serverId]->getOs() == WINDOWS) {
        pointerArray[serverId]->addServerToList(windowsListEnd, windowsListEnd->getPrevious());
    } else {
        pointerArray[serverId]->addServerToList(linuxListEnd, linuxListEnd->getPrevious());
    }
    unusedServers++;
    return SUCCESS_DC;
}

DataCenter::~DataCenter() {
    for (int i = 0; i < numberOfServers; ++i) {
        delete pointerArray[i];
    }

    delete pointerArray;
    delete linuxListEnd;
    delete linuxListHead;
    delete windowsListEnd;
    delete windowsListHead;
}
