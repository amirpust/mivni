
#include "AVLTreeById.h"

int AVLTreeById::compare(DataCenter *dc1, DataCenter *dc2) {

    return dc1->getDataCenterId() - dc2->getDataCenterId();
}
