#ifdef USER_PROGRAM

#include "memorymanager.h"

MemoryManager::MemoryManager() : pageMap(new BitMap(NumPhysPages)),
                                 managerLock(new Lock("Memory Manager")) {}

MemoryManager::~MemoryManager() {
    delete pageMap;
    delete managerLock;
}

void MemoryManager::lockMemory() {
    memoryLock->Acquire();
}

void MemoryManager::unlockMemory() {
    memoryLock->Release();
}

int MemoryManager::findPage() {
    managerLock->Acquire();
    int ret = pageMap->Find();
    managerLock->Release();
    return ret;
}

void MemoryManager::freePage(unsigned int pageNum) {
    managerLock->Acquire();
    pageMap->Clear(pageNum);
    managerLock->Release();
}

bool MemoryManager::isAllocated(unsigned int pageNum) {
    managerLock->Acquire();
    bool ret = pageMap->Test(pageNum);
    managerLock->Release();
    return ret;
}

unsigned int MemoryManager::numFreePages() {
    managerLock->Acquire();
    int ret = pageMap->NumClear();
    managerLock->Release();
    return ret;
}

#endif // USER_PROGRAM