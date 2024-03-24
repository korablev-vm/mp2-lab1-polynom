#ifndef SORTEDARRAYTABLE_H
#define SORTEDARRAYTABLE_H

#include "TableInterface.h"
#include <algorithm>
#include <vector>
#include <iostream>

template<typename TKey, typename TValue>
class TSortedTable : public TableInterface<TKey, TValue> {
    using T = TRecord<TKey, TValue>;
    std::vector<T> data;

public:
    TSortedTable() = default;

    void add(const TRecord<TKey, TValue>& record) override {
        auto it = std::lower_bound(data.begin(), data.end(), record);
        if (it == data.end() || it->key != record.key) {
            data.insert(it, record);
        }
    }

    void remove(const TKey& key) override {
        T element{ key, TValue() };
        auto it = std::lower_bound(data.begin(), data.end(), element);
        if (it != data.end() && it->key == key) {
            data.erase(it);
        }
    }

    TValue* find(const TKey& key) override {
        T element{ key, TValue() };
        auto it = std::lower_bound(data.begin(), data.end(), element);
        if (it != data.end() && it->key == key) {
            return const_cast<TValue*>(&it->value);
        }
        return nullptr;
    }

    void display() const override {
        for (const auto& item : data) {
            std::cout << "Key: " << item.key << ", Value: " << item.value << std::endl;
        }
    }
};

#endif // SORTEDARRAYTABLE_H