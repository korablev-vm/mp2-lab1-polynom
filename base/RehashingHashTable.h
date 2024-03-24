#ifndef REHASHINGHASHTABLE_H
#define REHASHINGHASHTABLE_H

#include <vector>
#include <optional>
#include <functional>
#include <iostream>
#include "TableInterface.h"

template<typename TKey, typename TValue>
class RehashingHashTable : public TableInterface<TKey, TValue> {
    using T = TRecord<TKey, TValue>;
    std::vector<std::optional<T>> data; // optional для хранения возможно пустых элементов
    size_t capacity;

    size_t hashKey(const TKey& key) const {
        return std::hash<TKey>{}(key) % capacity;
    }

public:
    RehashingHashTable(size_t initCapacity = 101) : capacity(initCapacity) {
        data.resize(capacity);
    }

    void add(const TRecord<TKey, TValue>& record) override {
        size_t index = hashKey(record.key);
        while (data[index].has_value()) {
            if (data[index]->key == record.key) {
                data[index] = record;
                return;
            }
            index = (index + 1) % capacity;
        }
        data[index] = record;
    }

    void remove(const TKey& key) override {
        size_t index = hashKey(key);
        while (data[index].has_value() && data[index]->key != key) {
            index = (index + 1) % capacity;
        }
        if (data[index].has_value()) {
            data[index].reset();
        }
    }

    TValue* find(const TKey& key) override {
        size_t index = hashKey(key);
        while (data[index].has_value() && data[index]->key != key) {
            index = (index + 1) % capacity;
        }
        if (data[index].has_value()) {
            return &(data[index]->value);
        }
        return nullptr;
    }

    void display() const override {
        for (const auto& item : data) {
            if (item.has_value()) {
                std::cout << "Key: " << item->key << ", Value: " << item->value << std::endl;
            }
        }
    }
};

#endif // REHASHINGHASHTABLE_H