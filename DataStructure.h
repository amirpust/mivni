#ifndef _DATASTRUCTURE_H
#define _DATASTRUCTURE_H

#include "CompareID.h"
#include "CompareLinux.h"
#include "CompareWindows.h"
#include "DataCenter.h"
#include "AVLTree.h"


typedef enum {
    ALLOCATION_ERROR, INVALID_INPUT, FAILURE, SUCCESS
} DataStructureStatus;

class DataStructure {
    AVLTree<DataCenter, int, CompareID> *idTree;
    AVLTree<DataCenter, int, CompareLinux> *linuxTree;
    AVLTree<DataCenter, int, CompareWindows> *windowsTree;

public:
    DataStructure();

    virtual ~DataStructure();

//TODO check allocation problem with catch throw
//TODO wrote new
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
    DataStructureStatus addDataCenter(int dataCenterId, int numOfServers) {
        if (numOfServers <= 0 || dataCenterId <= 0)
            return INVALID_INPUT;

        if (idTree->findData(dataCenterId)) {
            return FAILURE;
        }

        auto currentData = new DataCenter(dataCenterId, numOfServers);

        idTree->insert(currentData);
        linuxTree->insert(currentData);
        windowsTree->insert(currentData);

        return SUCCESS;
    }

    /**
     * @param dataCenterID
     * @return
     * INVALID_INPUT - if dataCenterID <= 0.
     * FAILURE - if dataCenter doesn't exist.
     * SUCCESS - if succeeded
     */

    //TODO : catch throw OOM
    DataStructureStatus removeDataCenter(int dataCenterID) {
        if (dataCenterID <= 0)
            return INVALID_INPUT;


        if (idTree->findData(dataCenterID) == nullptr) {
            return FAILURE;
        }

        windowsTree->remove(dataCenterID);
        linuxTree->remove(dataCenterID);
        idTree->remove(dataCenterID);

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
    DataStructureStatus requestServerFromDataCenter(int dataCenterId, int serverID, int os, int *assignedID) {
        if (dataCenterId <= 0 || assignedID == NULL || serverID < 0
            || os < LINUX || os > WINDOWS)
            return INVALID_INPUT;

        auto currentDataCenter = idTree->findData(dataCenterId);


        if (currentDataCenter == nullptr)
            return FAILURE;

        DataCenterStatus result = currentDataCenter->requestServer(serverID, os, assignedID);

        if (result == FAILURE_DC)
            return FAILURE;

        else if (result == INVALID_INPUT_DC)
            return INVALID_INPUT;

        if (result == SUCCESS_CHANGE_OS_DC) {
            windowsTree->remove(dataCenterId);
            windowsTree->insert(currentDataCenter);
            linuxTree->remove(dataCenterId);
            linuxTree->insert(currentDataCenter);
        }

        return SUCCESS;
    }

    DataStructureStatus freeServerFromDataCenter(int dataCenterID, int serverID) {
        if (serverID < 0 || dataCenterID <= 0)
            return INVALID_INPUT;

        auto currentDataCenter = idTree->findData(dataCenterID);

        if (currentDataCenter == nullptr)
            return FAILURE;

        DataCenterStatus result = currentDataCenter->freeServer(serverID);

        if (result == INVALID_INPUT_DC)
            return INVALID_INPUT;

        else if (result == FAILURE_DC)
            return FAILURE;

        return SUCCESS;
    }

};


#endif //_DATASTRUCTURE_H
