﻿#ifndef CHAININGHASHTABLE_H
#define CHAININGHASHTABLE_H

#include <vector>
#include <list>
#include <functional>
#include "TableInterface.h"

template<typename TKey, typename TValue>
class ChainingHashTable : public TableInterface<TKey, TValue> {
    using T = TRecord<TKey, TValue>;
    std::vector<std::list<T>> data;
    size_t capacity;

    size_t hashKey(const TKey& key) const {
        return std::hash<TKey>{}(key) % capacity;
    }

public:
    ChainingHashTable(size_t initCapacity = 101) : capacity(initCapacity) {
        data.resize(capacity);
    }

    void add(const TRecord<TKey, TValue>& record) override {
        size_t index = hashKey(record.key);
        auto& chain = data[index];
        auto it = std::find_if(chain.begin(), chain.end(), [&record](const T& item) { return item.key == record.key; });
        if (it == chain.end()) {
            chain.push_back(record);
        }
    }

    void remove(const TKey& key) override {
        size_t index = hashKey(key);
        auto& chain = data[index];
        chain.remove_if([&key](const T& item) { return item.key == key; });
    }

    TValue* find(const TKey& key) override {
        size_t index = hashKey(key);
        const auto& chain = data[index];
        for (const auto& item : chain) {
            if (item.key == key) {
                return &const_cast<TValue&>(item.value);
            }
        }
        return nullptr;
    }

    void display() const override {
        for (const auto& chain : data) {
            for (const auto& item : chain) {
                std::cout << "Key: " << item.key << ", Value: " << item.value << std::endl;
            }
        }
    }
};

#endif // CHAININGHASHTABLE_H