#ifndef LINEARLISTTABLE_H
#define LINEARLISTTABLE_H

#include "TableInterface.h"
#include "List.h"
#include <iostream>

template<typename TKey, typename TValue>
class TLinearListTable : public TableInterface<TKey, TValue> {
    using T = TRecord<TKey, TValue>;
    List<T> data;

public:
    TLinearListTable() = default;

    void add(const TRecord<TKey, TValue>& record) override {
        data.insertInOrder(record);
    }

    void remove(const TKey& key) override {
        for (int i = 0; i < data.size(); ++i) {
            if (data[i].key == key) {
                data.erase(i);
                return;
            }
        }
    }

    TValue* find(const TKey& key) override {
        for (int i = 0; i < data.size(); ++i) {
            if (data[i].key == key) {
                return &data[i].value;
            }
        }
        return nullptr;
    }

    void display() const override {
        for (int i = 0; i < data.size(); ++i) {
            std::cout << "Key: " << data[i].key << ", Value: " << data[i].value << std::endl;
        }
    }
};

#endif // LINEARLISTTABLE_H
