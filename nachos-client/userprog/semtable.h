#ifndef AUTOTABLE_H
#define AUTOTABLE_H

#include <unordered_map>
#include <queue>

#include "synch.h"

class SemTable {
public:
    int add(Semaphore semaphore);

    int remove(int key);

    Semaphore* get(int key);
private:
    std::unordered_map<int, Semaphore> map{};
    std::queue<int> availableKeys{};
    int nextKey{0};
};


#endif //AUTOTABLE_H
