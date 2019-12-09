#ifndef _DATASTRUCTURE_H
#define _DATASTRUCTURE_H

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
 * Inserts the dataCenter into the AVLTrees.
 * @param dataCenterId
 * @param numOfServers
 * @return
 * INVALID_INPUT - if numOfServers <= 0
 *                 or dataCenterID <= 0
 * FAILURE - if dataCenterID already exist.
 * SUCCESS - if succeeded.
 * ALLOCATION_ERROR - if failed to allocate data.
 */
    StatusType addDataCenter(int dataCenterId, int numOfServers);

    /**
     * Removes dataCenter from the AVLTrees.
     * @param dataCenterID
     * @return
     * INVALID_INPUT - if dataCenterID <= 0.
     * FAILURE - if dataCenter doesn't exist.
     * SUCCESS - if succeeded.
     * ALLOCATION_ERROR - if allocation fails.
     */

    StatusType removeDataCenter(int dataCenterID);

    /**
     * Searches the requested dataCenter and gives a free server if one is
     *      available.
     * This function also maintain the order in the different trees.
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
     * SUCCESS - if succeeded
     * ALLOCATION_ERROR - if allocation fails.
     */
    StatusType requestServerFromDataCenter(int dataCenterId, int serverID
            , int os, int *assignedID);

    /**
     *
     * @param dataCenterID
     * @param serverID
     * @return
     * INVALID_INPUT - if serverID < 0
     *                 or dataCenterID <= 0.
     * FAILURE - if dataCenterID doesn't match any key in the tree.
     *           if the server is already free.
     * SUCCESS - if succeeded
     */
    StatusType freeServerFromDataCenter(int dataCenterID, int serverID);

    /**
     *
     * @param os
     * @param dataCenters
     * @param numOfDataCenters
     * @return
     * INVALID_INPUT - if dataCenters is NULL
     *                 or numOfDataCenters is NULL.
     *                 or OS isn't 0 or 1.
     * ALLOCATION_ERROR - if allocation fails.
     * FAILURE - if the trees are empty.
     * SUCCESS - if succeeded
     */
    StatusType getDataCentersByOs(int os, int **dataCenters
            , int *numOfDataCenters);

};


#endif //_DATASTRUCTURE_H
