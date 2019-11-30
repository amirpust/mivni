//
// Created by Amir on 30/11/2019.
//

#include "AVLTreeByWindows.h"

int AVLTreeByWindows::compare(DataCenter *dc1, DataCenter *dc2) {
    int difference = dc1->getwindowsServerNumber() - dc2->getLinuxServerNumber();
    if(!difference){
        return dc1->getDataCenterId() - dc2->getDataCenterId();
    }
    return difference;
}
