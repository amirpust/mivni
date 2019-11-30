#include <iostream>
#include "DataCenter.h"
#include <assert.h>
int main() {

    auto dc1 = new DataCenter(12,10);
    int assignId = 0;
    assert(dc1->getDataCenterId() == 12);
    assert(dc1->getNumberOfServers() == 10);
    assert(dc1->getLinuxServerNumber() == 10);
    assert(dc1->getwindowsServerNumber() == 0);
    assert(dc1->requestServer(1,2,&assignId) == INVALID_INPUT);
    assert(dc1->requestServer(1,1,NULL) == INVALID_INPUT);
    assert(dc1->requestServer(-1,1,&assignId) == INVALID_INPUT);
    assert(dc1->requestServer(10,0,&assignId) == INVALID_INPUT);
    assert(dc1->requestServer(1,1,&assignId) == SUCCESS);
    assert(dc1->freeServer(assignId) == SUCCESS);
    for (int i = 0; i < 10; ++i) {
        assert(dc1->requestServer(i,0,&assignId) == SUCCESS);
    }
    assert(dc1->requestServer(1,1,&assignId) == FAILURE);
    assert(dc1->freeServer(-3) == INVALID_INPUT);
    assert(dc1->freeServer(11) == INVALID_INPUT);
    for (int j = 0; j < 10; ++j) {
        assert(dc1->freeServer(j) == SUCCESS);
    }
    assert(dc1->freeServer(1) == FAILURE);


    std::cout<< "go start DS class" << std::endl;



    return 0;
}