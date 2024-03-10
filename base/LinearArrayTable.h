#ifndef LINEARARRAYTABLE_H
#define LINEARARRAYTABLE_H

#include <iostream>
#include "TableInterface.h"
using namespace std;

template<typename TKey, typename TValue>
struct TRecord {
    TKey key;
    TValue value;
};

template<typename TKey, typename TValue>
class TUnorderedTable : public TableInterface<TRecord<TKey, TValue>> {
    using T = TRecord<TKey, TValue>;
    vector<T> data;

public:
    TUnorderedTable() = default;

    void add(const T& element) override {
        // лямбда-выражение для сравнения ключей
        auto it = find_if(data.begin(), data.end(), [&element](const T& item) {return item.key == element.key; });
        if (it == data.end())
            data.push_back(element);
    }

    void remove(const T& element) override {
        auto it = find_if(data.begin(), data.end(), [&element](const T& item) {
            return item.key == element.key;
            });
        if (it != data.end()) {
            data.erase(it);
        }
    }

    T* find(const T& element) const override {
        auto it = find_if(data.begin(), data.end(), [&element](const T& item) {
            return item.key == element.key;
            });
        if (it != data.end()) {
            return &(*it); 
        }
        return nullptr;
    }

    void display() const override {
        for (const auto& item : data) {
            cout << "Key: " << item.key << ", Value: " << item.value << endl;
        }
    }
};


#endif // LINEARARRAYTABLE_H