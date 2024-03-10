#ifndef SORTEDARRAYTABLE_H
#define SORTEDARRAYTABLE_H

#include "TableInterface.h"
using namespace std;

template<typename TKey, typename TValue>
struct TRecord {
    TKey key;
    TValue value;

    // Операторы сравнения необходимы для работы алгоритмов lower_bound и binary_search
    bool operator<(const TRecord& other) const {
        return key < other.key;
    }

    bool operator==(const TRecord& other) const {
        return key == other.key;
    }
};

template<typename TKey, typename TValue>
class TSortedTable : public TableInterface<TRecord<TKey, TValue>> {
    using T = TRecord<TKey, TValue>;
    vector<T> data;

public:
    TSortedTable() = default;

    void add(const T& element) override {
        // lower_bound - функция, которая за логарифмическое время в отсортированном массиве находит наименьший элемент, который больше заданного значения k или равен ему.
        auto it = lower_bound(data.begin(), data.end(), element);
        if (it == data.end() || it->key != element.key) {
            data.insert(it, element);
        }
    }

    void remove(const T& element) override {
        auto it = lower_bound(data.begin(), data.end(), element);
        if (it != data.end() && it->key == element.key) {
            data.erase(it);
        }
    }

    T* find(const T& element) const override {
        // Используем бинарный поиск для нахождения элемента
        auto it = lower_bound(data.begin(), data.end(), element);
        if (it != data.end() && it->key == element.key) {
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

#endif // SORTEDARRAYTABLE_H
