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
