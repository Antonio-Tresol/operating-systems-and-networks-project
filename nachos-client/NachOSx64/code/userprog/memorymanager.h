#ifdef USER_PROGRAM

#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include "thread.h"

class Thread;

#ifndef BITMAP_H

#include "bitmap.h"

#endif

#ifndef SYNCH_H

#include "synch.h"

#endif

class Lock;

extern Lock *memoryLock;

class MemoryManager {
public:
    MemoryManager();

    ~MemoryManager();

    void lockMemory();

    void unlockMemory();

    int findPage();

    void freePage(unsigned int pageNum);

    bool isAllocated(unsigned int pageNum);

    unsigned int numFreePages();

private:
    BitMap *pageMap;
    Lock *managerLock;
};

#endif // MEMORYMANAGER_H
#endif // USER_PROGRAM