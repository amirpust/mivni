//
// Created by jonat on 29/11/2019.
//

#include "DataCenter.h"

DataCenter::DataCenter(int dataCenterId, int numberOfServers)
        : dataCenterID(dataCenterId), numberOfServers(numberOfServers) {
    pointerArray = new Server*[numberOfServers];
    linuxServerNumber = numberOfServers;
    WindowsServerNumber =  0;

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

int DataCenter::getWindowsServerNumber() const {
    return WindowsServerNumber;
}

void DataCenter::initializeListAndPointerArray() {
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
