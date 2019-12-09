#ifndef _DATASTRUCTURE_H
#define _DATASTRUCTURE_H

#include "CompareID.h"
#include "CompareLinux.h"
#include "CompareWindows.h"
#include "DataCenter.h"
#include "AVLTree.h"
#include <exception>
#include "OSKey.h"


//TODO: when inserting to OSTree data = DataCenterID, key = OSKey
class DataStructure {
    AVLTree<DataCenter, int> *idTree;
    AVLTree<int, OSKey> *linuxTree;
    AVLTree<int, OSKey> *windowsTree;

    int numberOfDataCenters;

public:
    DataStructure();

    virtual ~DataStructure();

/**
 *
 * @param dataCenterId
 * @param numOfServers
 * @return
 * INVALID_INPUT - if numOfServers <= 0
 *                 or dataCenterID <= 0
 * FAILURE - if dataCenterID already exist
 * SUCCESS - if succeeded
 */
    StatusType addDataCenter(int dataCenterId, int numOfServers) {
        if (numOfServers <= 0 || dataCenterId <= 0)
            return INVALID_INPUT;

        DataCenter *currentData = nullptr;
        OSKey *windowsKey = nullptr;
        OSKey *linuxKey = nullptr;
        try {
            currentData = new DataCenter(dataCenterId, numOfServers);
            windowsKey = new OSKey(WINDOWS, 0, dataCenterId);
            linuxKey = new OSKey(LINUX, numOfServers + 1, dataCenterId);

            idTree->insert(*currentData, dataCenterId);
            windowsTree->insert(dataCenterId,*windowsKey);
            linuxTree->insert(dataCenterId,*linuxKey);
            numberOfDataCenters++;
            return SUCCESS;
        } catch (std::bad_alloc &ba) {
            return ALLOCATION_ERROR;
        }
        catch (DataStructureException &d) {
            delete currentData;
            return d.statusType;
        }
    }

    /**
     * @param dataCenterID
     * @return
     * INVALID_INPUT - if dataCenterID <= 0.
     * FAILURE - if dataCenter doesn't exist.
     * SUCCESS - if succeeded
     */

    StatusType removeDataCenter(int dataCenterID) {
        if (dataCenterID <= 0)
            return INVALID_INPUT;

        try {
            auto currentData = idTree->findData(dataCenterID);
            auto windowsKey = new OSKey(WINDOWS, currentData->getwindowsServerNumber(), dataCenterID);
            auto linuxKey = new OSKey(LINUX, currentData->getLinuxServerNumber(), dataCenterID);
    //TODO check OOM
            windowsTree->remove(*windowsKey);
            linuxTree->remove(*linuxKey);
            idTree->remove(dataCenterID);
        } catch (DataStructureException &d) {
            return d.statusType;
        }
        numberOfDataCenters--;

        return SUCCESS;
    }

    /**
     * @param dataCenterId
     * @param serverID
     * @param os
     * @param assignedID
     * @return
     * INVALID_INPUT - if assignedID is NULL
     *                 or dataCenterID <= 0
     *                 or serverID < 0
     *                 or serverID >= number of servers
     *                 or OS isn't in range.
     * FAILURE - dataCenterID doesn't exist
     *           or all servers are taken
     * SUCCESS - all succeeded
     */
    StatusType requestServerFromDataCenter(int dataCenterId, int serverID, int os, int *assignedID) {
        if (dataCenterId <= 0 || assignedID == NULL || serverID < 0
            || os < LINUX || os > WINDOWS)
            return INVALID_INPUT;

        try {
            auto currentDataCenter = idTree->findData(dataCenterId);
            auto windowsKey = new OSKey(WINDOWS, currentDataCenter->getwindowsServerNumber(), dataCenterId);
            auto linuxKey = new OSKey(LINUX, currentDataCenter->getLinuxServerNumber(), dataCenterId);

            if (currentDataCenter->requestServer(serverID, os, assignedID)) {
                windowsTree->remove(*windowsKey);
                windowsKey->setNumberOfServers(currentDataCenter->getwindowsServerNumber());
                windowsTree->insert(dataCenterId,*windowsKey);
                linuxTree->remove(*linuxKey);
                linuxKey->setNumberOfServers(currentDataCenter->getLinuxServerNumber());
                linuxTree->insert(dataCenterId,*linuxKey);
            }
        } catch (DataStructureException &d) {
            return d.statusType;
        }

        return SUCCESS;
    }

    StatusType freeServerFromDataCenter(int dataCenterID, int serverID) {
        if (serverID < 0 || dataCenterID <= 0)
            return INVALID_INPUT;

        try {
            auto currentDataCenter = idTree->findData(dataCenterID);
            currentDataCenter->freeServer(serverID);
        } catch (DataStructureException &d) {
            return d.statusType;
        }

        return SUCCESS;
    }

    StatusType getDataCentersByOs(int os, int **dataCenters, int *numOfDataCenters) {
        if (dataCenters == NULL || numOfDataCenters == NULL || os < 0 || os > 1) {
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
            return d.statusType;
        }
        *numOfDataCenters = numberOfDataCenters;
        return SUCCESS;
    }

};


#endif //_DATASTRUCTURE_H
