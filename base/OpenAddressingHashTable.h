#ifndef OPENADDRESSINGHASHTABLE_H
#define OPENADDRESSINGHASHTABLE_H

#include "TableInterface.h"
#include <vector>
#include <optional>

template <typename T>
class OpenAddressingHashTable : public TableInterface<T> {
private:
    std::vector<std::optional<T>> table;
    int capacity;
    int size;

    int hashFunction(const T& element, int attempt) const {

        return (std::hash<T>()(element) + attempt) % capacity;
    }

public:
    OpenAddressingHashTable(int size) : capacity(size), size(0) {
        table.resize(capacity);
    }

    ~OpenAddressingHashTable() {}

    void add(const T& element) override;
    void remove(const T& element) override;
    bool find(const T& element) const override;
    void display() const override;
};

#endif // OPENADDRESSINGHASHTABLE_H
