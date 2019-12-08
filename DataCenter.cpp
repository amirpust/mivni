#include "DataCenter.h"

DataCenter::DataCenter(int dataCenterId, int numberOfServers)
        : dataCenterID(dataCenterId),numberOfServers(numberOfServers + 1){

    initializePointerArray();

    linuxServerNumber = numberOfServers + 1;
    unusedServers = linuxServerNumber;
    windowsServerNumber =  0;

    initializeLinuxEnd();

    initializeLinuxHead();

    linuxListEnd->setPrevious(linuxListHead);
    linuxListHead->setNext(linuxListEnd);

    initializeWindowsEnd();

    initializeWindowsHead();

    windowsListEnd->setPrevious(windowsListHead);
    windowsListHead->setNext(windowsListEnd);

    initializeListAndPointerArray();
}

void DataCenter::initializeLinuxEnd(){
    try {
        linuxListEnd = new Server(-1);
    }catch (exception& e){
        delete pointerArray;
        throw OutOfMemory();
    }
}
void DataCenter::initializePointerArray(){
    try{
        pointerArray = new Server*[numberOfServers];
    }catch (exception& e){
        throw OutOfMemory();
    }

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

    Server* firstServer;
    try {
        firstServer = new Server(0);
    }catch(exception& e) {
        delete pointerArray;
        delete linuxListEnd;
        delete linuxListHead;
        delete windowsListHead;
        delete windowsListEnd;
        throw OutOfMemory();
    }


    firstServer->addServerToList(linuxListEnd,linuxListHead);
    pointerArray[0]=firstServer;

    for (int i = 1; i < numberOfServers; ++i) {
        try {
            auto temp = new  Server(i);
            temp->addServerToList(linuxListEnd,pointerArray[i-1]);
            pointerArray[i] = temp;
        }catch (exception& e){
            for (int j = i-1; j >= 0; --j) {
                pointerArray[j]->removeServerFromList();
                delete pointerArray[j];
            }
            delete linuxListEnd;
            delete linuxListHead;
            delete windowsListHead;
            delete windowsListEnd;
            delete firstServer;
            delete pointerArray;
            throw OutOfMemory();
        }
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

bool DataCenter::requestServer(const int requestedId, const int os, int *assignedServerId) {
    if (unusedServers == 0)
        throw NoFreeServers();
    if (requestedId >= numberOfServers || requestedId < 0 || os > 1 || os < 0
            || assignedServerId == NULL )
        throw InvalidInput();
    if (!pointerArray[requestedId]->isTaken()) {
        if(giveFreeServer(requestedId,os,assignedServerId)){
            unusedServers--;
            return true;
        }
        unusedServers--;
        return false;
    }
    if(giveDifferentServer(os,assignedServerId)){
        unusedServers--;
        return true;
    }
    unusedServers--;
    return false;
}

void DataCenter::freeServer(int serverId) {
    if (serverId >= numberOfServers || serverId < 0) {
        throw InvalidInput();
    }
    if (pointerArray[serverId]->isTaken() == false) {
        throw AlreadyFree();
    }

    pointerArray[serverId]->setTaken(false);

    if (pointerArray[serverId]->getOs() == WINDOWS) {
        pointerArray[serverId]->addServerToList(windowsListEnd, windowsListEnd->getPrevious());
    } else {
        pointerArray[serverId]->addServerToList(linuxListEnd, linuxListEnd->getPrevious());
    }
    unusedServers++;
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

void DataCenter::initializeWindowsHead() {
    try {
        windowsListHead = new Server(-4);
    }catch (exception& e){
        delete pointerArray;
        delete linuxListHead;
        delete linuxListEnd;
        delete windowsListEnd;
        throw OutOfMemory();
    }
}

void DataCenter::initializeWindowsEnd() {
    try {
        windowsListEnd = new Server(-3);
    }catch (exception& e){
        delete pointerArray;
        delete linuxListEnd;
        delete linuxListHead;
        throw OutOfMemory();
    }
}

void DataCenter::initializeLinuxHead() {
    try {
        linuxListHead = new Server(-2);
    } catch (exception &e) {
        delete pointerArray;
        delete linuxListEnd;
        throw OutOfMemory();

    }
}
