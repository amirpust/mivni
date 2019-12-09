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


//TODO check who comes before.
/**
 * @param osNode
 * @return
 * true -  if 'this' number of servers smaller then the key sent.
 * false - otherwise.
 */
    bool operator>(const OSKey &_key) const {
        assert(osSystem == _key.osSystem);

        if(numberOfServers < _key.numberOfServers)
            return true;

        if(numberOfServers > _key.numberOfServers)
            return false;

        if(dataCenterID > _key.dataCenterID)
            return true;

        return false;

    }

    bool operator==(const OSKey &_key) const {
        assert(osSystem == _key.osSystem);
        return (numberOfServers == _key.numberOfServers && dataCenterID == _key.dataCenterID);
    }
};


#endif //MIVNI_OSKEY_H
