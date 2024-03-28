#ifndef LINEARLISTTABLE_H
#define LINEARLISTTABLE_H

#include "TableInterface.h"
#include <list>
#include <iostream>

template<typename TKey, typename TValue>
class TLinearListTable : public TableInterface<TKey, TValue> {
    using T = TRecord<TKey, TValue>;
    std::list<T> data;

public:
    TLinearListTable() = default;

    void add(const TRecord<TKey, TValue>& record) override {
        data.push_back(record);
    }

    void remove(const TKey& key) override {
        auto it = data.begin();
        while (it != data.end()) {
            if (it->key == key) {
                it = data.erase(it);
            }
            else {
                ++it;
            }
        }
    }

    TValue* find(const TKey& key) override {
        for (auto& record : data) {
            if (record.key == key) {
                return &(record.value);
            }
        }
        return nullptr;
    }

    void display() const override {
        for (const auto& record : data) {
            std::cout << "Key: " << record.key << ", Value: " << record.value << std::endl;
        }
    }
};

#endif // LINEARLISTTABLE_H
