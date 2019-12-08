#ifndef MIVNI_OSKEY_H
#define MIVNI_OSKEY_H


class OSKey {
    int osSystem;
    int numberOfServers;
    int dataCenterID;
public:
    OSKey(int osSystem, int numberOfServers, int dataCenterId);
//TODO check who comes before..
    bool operator>(const OSKey& osNode)const {
        int result = numberOfServers - osNode.numberOfServers;

    }
};


#endif //MIVNI_OSKEY_H
