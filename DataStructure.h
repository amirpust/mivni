#ifndef _DATASTRUCTURE_H
#define _DATASTRUCTURE_H

#include "CompareID.h"
#include "CompareLinux.h"
#include "CompareWindows.h"
#include "DataCenter.h"
#include "AVLTree.h"
#include <exception>



class DataStructure {
    AVLTree<DataCenter, int, CompareID> *idTree;
    AVLTree<DataCenter, int, CompareLinux> *linuxTree;
    AVLTree<DataCenter, int, CompareWindows> *windowsTree;

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

        DataCenter* currentData = nullptr;
        try{
           currentData = new DataCenter(dataCenterId, numOfServers);

            idTree->insert(currentData);
            linuxTree->insert(currentData);
            windowsTree->insert(currentData);

            return SUCCESS;
        }catch (std::bad_alloc& ba){
            return ALLOCATION_ERROR;
        }
        catch(DataStructureException& d){
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

        try{
            windowsTree->remove(dataCenterID);
            linuxTree->remove(dataCenterID);
            idTree->remove(dataCenterID);
        }catch(DataStructureException& d){
            return d.statusType;
        }

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

            DataCenterStatus result = currentDataCenter->requestServer(serverID, os, assignedID);
            if (result == SUCCESS_CHANGE_OS_DC) {
                windowsTree->remove(dataCenterId);
                windowsTree->insert(currentDataCenter);
                linuxTree->remove(dataCenterId);
                linuxTree->insert(currentDataCenter);
            }
        }catch(DataStructureException& d){
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
        }catch (DataStructureException& d){
            return d.statusType;
        }

        return SUCCESS;
    }

    StatusType getDataCentersByOs(int os, int **dataCenters,int* numOfDataCenters){
        if(dataCenters == NULL || numOfDataCenters == NULL || os < 0 || os > 1){
            return INVALID_INPUT;
        }

        try {
            dataCenters = new int*[*numOfDataCenters]();
        }catch (exception& e){
            return ALLOCATION_ERROR;
        }
        try {
            if(os == WINDOWS){
                windowsTree->getKeysInOrder(dataCenters,*numOfDataCenters);
            }else{
                linuxTree->getKeysInOrder(dataCenters,*numOfDataCenters);
            }
        }catch (DataStructureException& d){
            return d.statusType;
        }
        return SUCCESS;

    }

};


#endif //_DATASTRUCTURE_H
