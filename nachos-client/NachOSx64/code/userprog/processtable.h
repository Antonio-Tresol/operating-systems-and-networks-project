#ifndef PROCESSTABLE_H
#define PROCESSTABLE_H

#ifndef BITMAP_H
#include "bitmap.h"
#endif

#ifndef SYNCH_H
#include "synch.h"
#endif

class Process{
public:
    ~Process();

	void set(int threadId, void *object);
	void *get();
    int wait();
    void release();

    int returnValue;

private:
	int id{-1};
	void *process{nullptr};
    Semaphore* parent{new Semaphore("Process semaphore", 0)};
};

class ProcessTable{
public:
	explicit ProcessTable(int size);
	~ProcessTable();
    int alloc(void *object);
	void release(int index, int returnValue);
    int wait(int index);
    int maxSize;
	int currentSize;
private:
	Lock *lock;
	BitMap *bitMap;
	Process **processes;
};

#endif