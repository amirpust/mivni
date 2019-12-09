#ifndef MIVNI_OSKEY_H
#define MIVNI_OSKEY_H

#include <cassert>

class OSKey {
    int osSystem;
    int numberOfServers;
    int dataCenterID;

public:
    OSKey(int osSystem, int numberOfServers, int dataCenterId);


    OSKey(const OSKey &toCopy) : osSystem(toCopy.osSystem),
                                 numberOfServers(toCopy.numberOfServers)
                                 , dataCenterID(toCopy.dataCenterID) {};


//TODO check who comes before.
/**
 * @param osNode
 * @return
 * true -  if 'this' number of servers smaller then the key sent.
 * false - otherwise.
 */
    bool operator>(const OSKey &_key) const {
        assert(osSystem == _key.osSystem);
        int result = numberOfServers - _key.numberOfServers;

        if (result > 0) {
            return false;
        }

        if (result == 0) {
            result = dataCenterID - _key.dataCenterID;
            if (result > 0)
                return true;
        }

        return false;
    }
};


#endif //MIVNI_OSKEY_H
