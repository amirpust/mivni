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
     * @throws NoFreeServers
     * @throws InvalidInput - if requestedId is bigger or equal to the number
     *                          of servers in the DataCenter.
     *                or if requestedId is a negative number.
     *                or if the OS isn't 1 or 0.
     *                or if the assignedServerId pointer is NULL.
     */
    bool requestServer(int requestedId, int os, int *assignedServerId);

    /**
     *frees a given server and returns it to the end of the priority list of
     * free servers.
     * @param serverId
     * @throws AlreadyFree.
     * @throws InvalidInput - if serverId is bigger or equal to the number of
     *                                 servers.
     *                        or if serverId is negative.
     */
    void freeServer(int serverId);

    int operator*();

    virtual ~DataCenter();

private:

    /**
     * Allocates memory for the servers, inserts them into the lists and
     * into to pointer array.
     */
    void initializeListAndPointerArray();

/**
 * If the preferred server is taken the function, gives a different server.
 * @param os
 * @param assignedServerId
 * @return
 * true of os was changed
 * false otherwise
 */
    bool giveDifferentServer(int os, int *assignedServerId);

/**
 * Finds the best option for an available.
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
