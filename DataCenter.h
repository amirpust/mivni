#ifndef _DATACENTER_H
#define _DATACENTER_H

#include "Server.h"
#include "DataStructureExceptions.h"


class DataCenter {
    int dataCenterID;
    int numberOfServers;
    int linuxServerNumber;
    int windowsServerNumber;
    int unusedServers;
    Server **pointerArray{};
    Server *linuxListHead{};
    Server *linuxListEnd{};
    Server *windowsListHead{};
    Server *windowsListEnd{};

public:
    DataCenter(int dataCenterId, int numberOfServers);

    DataCenter();

    DataCenter(DataCenter &toCopy);;

    int getDataCenterId() const;

    int getLinuxServerNumber() const;

    int getwindowsServerNumber() const;

    int getNumberOfServers() const;

    /**
     * This function decides if the server is free, if so it assigns it with the
     * compatible OS system.
     * Otherwise it assigns a different server than requested.
     * @param requestedId
     * @param os
     * @param assignedServerId
     * @return
     * true - if the number of os servers was changed.
     * false - otherwise.
     */
    bool requestServer(int requestedId, int os, int *assignedServerId);

    /**
     *frees a given server and returns it to the end of the priority list of
     * free servers.
     * @param serverId
     */
    void freeServer(int serverId);

    int operator*() {
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
