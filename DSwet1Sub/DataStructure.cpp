#include "DataStructure.h"

DataStructure::DataStructure() {
    numberOfDataCenters = 0;
    try {
        idTree = new AVLTree<DataCenter, int>();
    } catch (exception &e) {
        throw OutOfMemory();
    }
    try {
        linuxTree = new AVLTree<int, OSKey>();
    } catch (exception &e) {
        delete idTree;
        throw OutOfMemory();
    }

    try {
        windowsTree = new AVLTree<int, OSKey>();
    } catch (exception &e) {
        delete idTree;
        delete linuxTree;
        throw OutOfMemory();
    }

}

DataStructure::~DataStructure() {
    delete linuxTree;
    delete windowsTree;
    delete idTree;
}

StatusType DataStructure::removeDataCenter(int dataCenterID) {
    if (dataCenterID <= 0)
        return INVALID_INPUT;

    try {
        auto currentData = idTree->findData(dataCenterID);
        OSKey windowsKey(WINDOWS, currentData->getwindowsServerNumber()
                , dataCenterID);
        OSKey linuxKey(LINUX, currentData->getLinuxServerNumber()
                , dataCenterID);

        windowsTree->remove(windowsKey);
        linuxTree->remove(linuxKey);
        idTree->remove(dataCenterID);
    } catch (DataStructureException &d) {
        return d.getException();
    }
    numberOfDataCenters--;

    return SUCCESS;
}

StatusType DataStructure::addDataCenter(int dataCenterId, int numOfServers) {
    if (numOfServers <= 0 || dataCenterId <= 0)
        return INVALID_INPUT;

    try {
        DataCenter currentData(dataCenterId, numOfServers);
        OSKey windowsKey(WINDOWS, 0, dataCenterId);
        OSKey linuxKey(LINUX, numOfServers, dataCenterId);

        idTree->insert(currentData, dataCenterId);
        windowsTree->insert(dataCenterId, windowsKey);
        linuxTree->insert(dataCenterId, linuxKey);
        numberOfDataCenters++;
        return SUCCESS;
    } catch (std::bad_alloc &ba) {
        return ALLOCATION_ERROR;
    }
    catch (DataStructureException &d) {
        return d.getException();
    }
}

StatusType DataStructure::requestServerFromDataCenter(int dataCenterId
        , int serverID, int os, int *assignedID) {
    if (dataCenterId <= 0 || assignedID == NULL || serverID < 0
        || os < LINUX || os > WINDOWS)
        return INVALID_INPUT;

    try {
        auto currentDataCenter = idTree->findData(dataCenterId);

        OSKey windowsKey(WINDOWS, currentDataCenter->getwindowsServerNumber()
                , dataCenterId);
        OSKey linuxKey(LINUX, currentDataCenter->getLinuxServerNumber()
                , dataCenterId);

        if (currentDataCenter->requestServer(serverID, os, assignedID)) {
            windowsTree->remove(windowsKey);
            windowsKey.setNumberOfServers(
                    currentDataCenter->getwindowsServerNumber());
            windowsTree->insert(dataCenterId, windowsKey);
            linuxTree->remove(linuxKey);
            linuxKey.setNumberOfServers(
                    currentDataCenter->getLinuxServerNumber());
            linuxTree->insert(dataCenterId, linuxKey);
        }
    } catch (DataStructureException &d) {
        return d.getException();
    }

    return SUCCESS;
}

StatusType DataStructure::freeServerFromDataCenter(int dataCenterID, int serverID) {
    if (serverID < 0 || dataCenterID <= 0)
        return INVALID_INPUT;

    try {
        auto currentDataCenter = idTree->findData(dataCenterID);
        currentDataCenter->freeServer(serverID);
    } catch (DataStructureException &d) {
        return d.getException();
    }

    return SUCCESS;
}

StatusType DataStructure::getDataCentersByOs(int os, int **dataCenters, int *numOfDataCenters) {
    if (dataCenters == NULL || numOfDataCenters == NULL || os < 0
        || os > 1) {
        return INVALID_INPUT;
    }
    *dataCenters = (int *) malloc(sizeof(int) * numberOfDataCenters);
    if (*dataCenters == NULL) {
        return ALLOCATION_ERROR;
    }

    try {
        if (os == WINDOWS) {
            windowsTree->getDataInOrder(dataCenters, numberOfDataCenters);
        } else {
            linuxTree->getDataInOrder(dataCenters, numberOfDataCenters);
        }
    } catch (DataStructureException &d) {
        free(*dataCenters);
        return d.getException();
    }
    *numOfDataCenters = numberOfDataCenters;
    return SUCCESS;
}
