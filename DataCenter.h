#ifndef _DATACENTER_H
#define _DATACENTER_H

#include "Server.h"

typedef enum {
    ALLOCATION_ERROR, INVALID_INPUT, FAILURE, SUCCESS
} ServerStatus;

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
     * FAILURE - there are no more free servers to assign.
     * INVALID_INPUT - if serverId >= number of servers or serverId < 0 or
     *                 OS < 0 or OS > 1 or assignedId = NULL
     * SUCCESS - if succeeded
     */
    ServerStatus requestServer(const int requestedId, const int os, int *assignedServerId);


    /**
     *frees a given server and returns it to the end of the priority list of
     * free servers.
     * @param serverId
     * @return
     * INVALID_INPUT - if serverId >= numOfServers or serverId < 0.
     * FAILURE - if the server is already freed.
     * SUCCESS - if succeeded
     */
    ServerStatus freeServer(int serverId);

private:
    void initializeListAndPointerArray();

    void giveDifferentServer(int os, int *assignedServerId);

    void giveFreeServer(int serverId, int os, int *assignedServer);

    void giveServer(int serverId, int *assignedServerId);

    void changeServerAmount(int os);
};


#endif //_DATACENTER_H
