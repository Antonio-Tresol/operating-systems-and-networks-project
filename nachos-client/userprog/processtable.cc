#include "processtable.h"

ProcessTable::ProcessTable(int size) : maxSize(size), currentSize(0), lock(new Lock("Process Table")),
                                       bitMap(new BitMap(size)), processes(new Process *[size]) {
    for (int i{0}; i < size; ++i){
        processes[i] = new Process();
    }
}

ProcessTable::~ProcessTable() {
    delete lock;
    delete bitMap;

    for (int i{0}; i < maxSize; ++i)
        delete processes[i];
    delete[] processes;
}

int ProcessTable::alloc(void *object)
{
    if(bitMap->NumClear() == 0) {
        return -1;
    }

    lock->Acquire();

    processes[currentSize] = new Process();

    int temp{bitMap->Find()};
    processes[currentSize]->set(temp, object);

    currentSize++;

    lock->Release();

    return temp;
}

void Process::set(int threadId, void *object) {
    id = threadId;
    process = object;
}

void *Process::get() {
    return process;
}

void Process::release() {
    parent->V();
}

int Process::wait() {
    parent->P();
    return returnValue;
}

Process::~Process() {
    delete parent;
}

void ProcessTable::release(int index, int returnValue) {
    lock->Acquire();
    if (bitMap->Test(index) == true) {
        processes[index]->returnValue = returnValue;
        processes[index]->release();
    }
    lock->Release();
}

int ProcessTable::wait(int index) {
    lock->Acquire();
    if (bitMap->Test(index) == true) {
        bitMap->Clear(index);
        --currentSize;
    }
    lock->Release();

    return processes[index]->wait();
}
