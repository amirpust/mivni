//
// Created by jonat on 29/11/2019.
//

#include "DataCenter.h"

DataCenter::DataCenter(int dataCenterId, int numberOfServers)
        : dataCenterID(dataCenterId), numberOfServers(numberOfServers) {
    *pointerArray = new Server(numberOfServers);
    linuxServerNumber = numberOfServers;
    WindowsServerNumber =  0;


}
