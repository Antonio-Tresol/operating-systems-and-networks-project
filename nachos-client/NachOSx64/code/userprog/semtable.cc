#include "semtable.h"

int SemTable::add(Semaphore semaphore) {
    int key;
    if (!availableKeys.empty()) {
        key = availableKeys.front();
        availableKeys.pop();
    } else {
        key = nextKey++;
    }

    map.insert({key, semaphore});
    return key;
}

int SemTable::remove(int key) {
    auto it = map.find(key);
    if (it == map.end()) {
        return -1;
    }
    availableKeys.push(key);
    return map.erase(key);
}

Semaphore* SemTable::get(int key) {
    auto it = map.find(key);
    if (it == map.end()) {
        return nullptr;
    }
    return &map.at(key);
}