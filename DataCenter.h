#ifndef _DATACENTER_H
#define _DATACENTER_H

#include "Server.h"
#include "DataStructureExceptions.h"
typedef enum {
    ALLOCATION_ERROR_DC, INVALID_INPUT_DC, FAILURE_DC, SUCCESS_CHANGE_OS_DC,SUCCESS_DC
} DataCenterStatus;

class DataCenter {
    int dataCenterID;
    int numberOfServers;
    int linuxServerNumber;
    int windowsServerNumber;
    int unusedServers;
    Server **pointerArray;
    Server *linuxListHead;
    Server *linuxListEnd;
    Server *windowsListHead;
    Server *windowsListEnd;

public:
    DataCenter(int dataCenterId, int numberOfServers);

    int getDataCenterId() const;

    int getLinuxServerNumber() const;

    int getwindowsServerNumber() const;

    int getNumberOfServers() const;

    const bool operator>(const DataCenter &dataCenter) const;

    const bool operator==(const DataCenter &dataCenter) const;

    const bool operator>(const int key) const;

    const bool operator==(const int key) const;

    /**
     * This function decides if the server is free, if so it assigns it with the
     * compatible OS system.
     * Otherwise it assigns a different server than requested.
     * @param requestedId
     * @param os
     * @param assignedServerId
     * @return
     * FAILURE_DC - there are no more free servers to assign.
     * INVALID_INPUT_DC - if serverId >= number of servers or serverId < 0 or
     *                 OS < 0 or OS > 1 or assignedId = NULL
     * SUCCESS_DC - if succeeded and os stayed the same
     * SUCCESS_CHANGE_OS_DC - if succeeded and
     */
    DataCenterStatus requestServer(const int requestedId, const int os, int *assignedServerId);


    /**
     *frees a given server and returns it to the end of the priority list of
     * free servers.
     * @param serverId
     * @return
     * INVALID_INPUT_DC - if serverId >= numOfServers or serverId < 0.
     * FAILURE_DC - if the server is already freed.
     * SUCCESS_DC - if succeeded
     */
    DataCenterStatus freeServer(int serverId);

    const int operator*() const {
        return dataCenterID;
    }

    virtual ~DataCenter();

private:
    void initializeListAndPointerArray();

/**
 *
 * @param os
 * @param assignedServerId
 * @return
 * true of os was changed
 * false otherwise
 */
    bool giveDifferentServer(int os, int *assignedServerId);

/**
 *
 * @param serverId
 * @param os
 * @param assignedServer
 * @return
 * true if os was changed
 * false otherwise
 */
    bool giveFreeServer(int serverId, int os, int *assignedServer);

    void giveServer(int serverId, int *assignedServerId);

    void changeServerAmount(int os);

    void initializePointerArray();

    void initializeLinuxEnd();

    void initializeLinuxHead();

    void initializeWindowsEnd();

    void initializeWindowsHead();
};


#endif //_DATACENTER_H
