#include <algorithm>
#include <iostream>

#include "bitmap.h"
#include "filetable.h"

using std::fill_n;

FileTable::FileTable() : openFiles(new int[MAX_FILES]),
                         openFilesMap(new BitMap(MAX_FILES)),
                         usage(1) {

    fill_n(openFiles, MAX_FILES, -1);

    // Reserve console FDs
    openFilesMap->Mark(0);
    openFilesMap->Mark(1);
    openFilesMap->Mark(2);
    openFiles[0] = 0;
    openFiles[1] = 1;
    openFiles[2] = 2;
}

FileTable::~FileTable() {
    delete openFilesMap;
    delete[] openFiles;
}

int FileTable::Open(int UnixHandle) {

    // Check if file is already open
    for (int i{0}; i < MAX_FILES; ++i) {
        if (openFilesMap->Test(i)) {
            if (UnixHandle == openFiles[i]) {
                return i;   // If so, return handle
            }
        }
    }

    // Find a new spot in the bitmap
    int handle{openFilesMap->Find()};

    // Check if out of space
    if (handle == -1) {
        return handle;
    }

    // Otherwise store and return
    openFiles[handle] = UnixHandle;

    return handle;
}

int FileTable::Close(int NachosHandle) {

    // Check handle is valid
    if (NachosHandle < 2 || NachosHandle >= MAX_FILES || !isOpened(NachosHandle)) {
        return -1;
    }

    int handle{openFiles[NachosHandle]};

    // Reset handle
    openFilesMap->Clear(NachosHandle);
    openFiles[NachosHandle] = -1;

    return handle;
}

bool FileTable::isOpened(int NachosHandle) {

    // Check handle is valid
    if (NachosHandle < 0 || NachosHandle >= MAX_FILES) {
        return false;
    }

    return openFilesMap->Test(NachosHandle);
}

int FileTable::getUnixHandle(int NachosHandle) {

    // Check handle is valid
    if (NachosHandle < 3 || NachosHandle >= MAX_FILES) {
        return -1;
    }

    return openFiles[NachosHandle];
}

void FileTable::addThread() {
    this->usage++;
}

int FileTable::delThread() {
    this->usage--;
    return this->usage;
}

void FileTable::Print() {
    for (int i{0}; i < MAX_FILES; ++i) {
        if (isOpened(i)) {
            printf("NachOS: %i, Unix: %i\n", i, openFiles[i]);
        }
    }
}							