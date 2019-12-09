#ifndef MIVNI_OSKEY_H
#define MIVNI_OSKEY_H


class OSKey {
    int osSystem;
    int numberOfServers;
    int dataCenterID;

public:
    OSKey(int osSystem, int numberOfServers, int dataCenterId);
//TODO check who comes before.

/**
 *
 * @param osNode
 * @return
 * true -  if 'this' number of servers smaller then the key sent.
 * false - otherwise.
 */
    bool operator>(const OSKey& _key)const {
        int result = numberOfServers - _key.numberOfServers;

        if(result > 0) {
          return false;
        }

        if(result > 0)
            return result;
        return false;
    }
};


#endif //MIVNI_OSKEY_H
