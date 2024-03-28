#ifndef LINEARARRAYTABLE_H
#define LINEARARRAYTABLE_H

#include <algorithm>
#include <iostream>
#include "TableInterface.h"

template<typename TKey, typename TValue>
class TUnorderedTable : public TableInterface<TKey, TValue> {
    using T = TRecord<TKey, TValue>;
    std::vector<T> data;

public:
    TUnorderedTable() = default;

    void add(const TRecord<TKey, TValue>& record) override {
        auto it = std::find_if(data.begin(), data.end(), [&record](const T& item) { return item.key == record.key; });
        if (it == data.end()) {
            data.push_back(record);
        }
    }

    void remove(const TKey& key) override {
        auto it = std::find_if(data.begin(), data.end(), [&key](const T& item) { return item.key == key; });
        if (it != data.end()) {
            data.erase(it);
        }
    }

    TValue* find(const TKey& key) override {
        auto it = std::find_if(data.begin(), data.end(), [&key](const T& item) { return item.key == key; });
        if (it != data.end()) {
            return &(it->value);
        }
        return nullptr;
    }

    void display() const override {
        for (const auto& item : data) {
            std::cout << "Key: " << item.key << ", Value: " << item.value << std::endl;
        }
    }
};

#endif // LINEARARRAYTABLE_H