#include "library1.h"
#include "DataStructure.h"


void *Init(){
    DataStructure *DS;
    try {
        DS = new DataStructure();
    }catch(exception& e) {
        return nullptr;
    }
    return (void*)DS;
}

StatusType AddDataCenter(void *DS, int dataCenterID, int numOfServers){
    if(!DS)
        return INVALID_INPUT;
    return ((DataStructure*)(DS))->addDataCenter(dataCenterID, numOfServers);
}

StatusType RemoveDataCenter(void *DS, int dataCenterID){
    if(!DS)
        return INVALID_INPUT;
    return ((DataStructure*)(DS))->removeDataCenter(dataCenterID);
}

StatusType RequestServer(void *DS, int dataCenterID, int serverID, int os, int *assignedID){
    if(!DS)
        return INVALID_INPUT;
    return ((DataStructure*)(DS))->requestServerFromDataCenter(dataCenterID,serverID,os,assignedID);
}

StatusType FreeServer(void *DS, int dataCenterID, int serverID){
    if(!DS)
        return INVALID_INPUT;
    return ((DataStructure*)(DS))->freeServerFromDataCenter(dataCenterID,serverID);
}

StatusType GetDataCentersByOS(void *DS, int os, int **dataCenters, int* numOfDataCenters){
    if(!DS)
        return INVALID_INPUT;
    return ((DataStructure*)(DS))->getDataCentersByOs(os, dataCenters, numOfDataCenters);
}

void Quit(void** DS){
    if(!DS)
        return;
    delete *((DataStructure**)(DS));
    *DS = nullptr;
}