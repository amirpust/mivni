//
// Created by Amir on 08/12/2019.
//

#include "OSKey.h"

OSKey::OSKey(int osSystem, int numberOfServers, int dataCenterId) : osSystem(osSystem), numberOfServers(numberOfServers),
                                                              dataCenterID(dataCenterId) {}

void OSKey::setNumberOfServers(int numberOfServers) {
    OSKey::numberOfServers = numberOfServers;
}
