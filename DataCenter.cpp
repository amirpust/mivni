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
    linuxListHead = new Server(-2,linuxListEnd);//TODO: check if we can remove magic numbers


    windowsListEnd = new Server(-3);
    windowsListHead = new Server(-4,windowsListEnd);
    windowsListEnd->setPrevious(windowsListHead);

}
