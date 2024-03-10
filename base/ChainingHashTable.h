#ifndef CHAININGHASHTABLE_H
#define CHAININGHASHTABLE_H

#include "TableInterface.h"
#include <vector>
#include "List.h"

using namespace std;

template <typename T>
class ChainingHashTable : public TableInterface<T> {
private:
    vector<List<T>> table;
    int capacity;

    int hashFunction(const T& element) const {
        return hash<T>()(element) % capacity;
    }

public:
    ChainingHashTable(int size) : capacity(size) {
        table.resize(capacity);
    }

    void add(const T& element) override;
    void remove(const T& element) override;
    bool find(const T& element) const override;
    void display() const override;
};

#endif // CHAININGHASHTABLE_H