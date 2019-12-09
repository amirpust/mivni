#ifndef MIVNI_OSKEY_H
#define MIVNI_OSKEY_H

#include <cassert>

class OSKey {
    int osSystem;
    int numberOfServers;
    int dataCenterID;

public:
    OSKey(int osSystem, int numberOfServers, int dataCenterId);
    OSKey()= default;


    OSKey(const OSKey &toCopy) : osSystem(toCopy.osSystem),
    numberOfServers(toCopy.numberOfServers), dataCenterID(toCopy.dataCenterID) {};

    void setNumberOfServers(int numberOfServers);

/**
 * @param osNode
 * @return
 * true -  if 'this' key is bigger than the other key.
 * false - otherwise.
 */
    bool operator>(const OSKey &_key) const;

    bool operator==(const OSKey &_key) const;
};


#endif //MIVNI_OSKEY_H
