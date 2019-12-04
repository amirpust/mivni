#ifndef _DATASTRUCTURE_H
#define _DATASTRUCTURE_H

#include "AVLTreeById.h"
#include "AVLTreeByWindows.h"
#include "AVLTreeByLinux.h"
#include "DataCenter.h"

typedef enum {
    ALLOCATION_ERROR, INVALID_INPUT, FAILURE, SUCCESS
} DataStructureStatus;

class DataStructure {
    AVLTreeById *idTree;
    AVLTreeByLinux *linuxTree;
    AVLTreeByWindows *windowsTree;

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

        auto dummyDataCenter = new DataCenter(dataCenterId, numOfServers);

        if (idTree->findDataCenter(dummyDataCenter) != nullptr) {
            delete dummyDataCenter;
            return FAILURE;
        }

        idTree->insert(dummyDataCenter);
        linuxTree->insert(dummyDataCenter);
        windowsTree->insert(dummyDataCenter);

        return SUCCESS;
    }

    /**
     *
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

        auto dummyDataCenter = new DataCenter(dataCenterID, 0);

        if (idTree->findDataCenter(dummyDataCenter) == nullptr) {
            delete dummyDataCenter;
            return FAILURE;
        }

        idTree->remove(dummyDataCenter);
        windowsTree->remove(dummyDataCenter);
        linuxTree->remove(dummyDataCenter);
        delete dummyDataCenter;

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
    DataStructureStatus requestServerFromDataCenter(int dataCenterId, int serverID
            , int os, int *assignedID) {
        if (dataCenterId <= 0 || assignedID == NULL || serverID < 0
            || os < LINUX || os > WINDOWS)
            return INVALID_INPUT;

        auto dummyDataCenter = new DataCenter(dataCenterId, 0);
        auto currentDataCenter = idTree->findDataCenter(dummyDataCenter);
        delete dummyDataCenter;

        if (currentDataCenter == nullptr)
            return FAILURE;

        DataCenterStatus result = currentDataCenter->requestServer(serverID, os, assignedID);

        if (result == FAILURE_DC)
            return FAILURE;

        else if (result == INVALID_INPUT_DC)
            return INVALID_INPUT;

        if (result == SUCCESS_CHANGE_OS_DC) {
            windowsTree->remove(currentDataCenter);
            windowsTree->insert(currentDataCenter);
            linuxTree->remove(currentDataCenter);
            linuxTree->insert(currentDataCenter);
        }

        return SUCCESS;
    }

    DataStructureStatus freeServerFromDataCenter(int dataCenterID, int serverID) {
        if (serverID < 0 || dataCenterID <= 0)
            return INVALID_INPUT;

        auto dummyDataCenter = new DataCenter(dataCenterID, 0);
        auto currentDataCenter = idTree->findDataCenter(dummyDataCenter);
        delete dummyDataCenter;

        if (currentDataCenter == nullptr)
            return FAILURE;

        DataCenterStatus result = currentDataCenter->freeServer(serverID);

        if (result == INVALID_INPUT_DC)
            return INVALID_INPUT;

        else if (result == FAILURE_DC)
            return FAILURE;

        return SUCCESS;
    }

    // I think this is too complicated and i will have to change it when we will
    //make the tree generic

    DataStructureStatus removeDataCenetr(int dataCenterID){
        if (dataCenterID <= 0)
            return INVALID_INPUT;

        DataCenter* dummy = new DataCenter(dataCenterID,0);
        DataCenter* result = idTree->findDataCenter(dummy);
        delete dummy;

        if (result == nullptr){

            return  FAILURE;
        }

        idTree->destroy(result);
        windowsTree->destroy(result);
        linuxTree->destroy(result);
        return SUCCESS;

    }

};


#endif //_DATASTRUCTURE_H
