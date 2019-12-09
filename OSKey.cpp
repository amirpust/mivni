//
// Created by Amir on 08/12/2019.
//

#include "OSKey.h"

OSKey::OSKey(int osSystem, int numberOfServers, int dataCenterId)
                : osSystem(osSystem), numberOfServers(numberOfServers),
                dataCenterID(dataCenterId) {}

void OSKey::setNumberOfServers(int numberOfServers) {
    OSKey::numberOfServers = numberOfServers;
}

bool OSKey::operator>(const OSKey &_key) const {
    assert(osSystem == _key.osSystem);

    if(numberOfServers < _key.numberOfServers)
        return true;

    if(numberOfServers > _key.numberOfServers)
        return false;

    if(dataCenterID > _key.dataCenterID)
        return true;

    return false;

}

bool OSKey::operator==(const OSKey &_key) const {
    assert(osSystem == _key.osSystem);
    return (numberOfServers == _key.numberOfServers &&
                                            dataCenterID == _key.dataCenterID);
}
