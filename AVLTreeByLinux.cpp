//
// Created by Amir on 30/11/2019.
//

#include "AVLTreeByLinux.h"

int AVLTreeByLinux::compare(DataCenter *dc1, DataCenter *dc2) {

    int difference = dc1->getLinuxServerNumber() - dc2->getLinuxServerNumber();
    if(!difference)
        return dc1->getDataCenterId() - dc2->getDataCenterId();
    return difference;
}
