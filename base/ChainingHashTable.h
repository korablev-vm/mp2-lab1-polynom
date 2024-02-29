#ifndef CHAININGHASHTABLE_H
#define CHAININGHASHTABLE_H

#include "List.h"
#include <vector>

using namespace std;

template <typename T>
class ChainingHashTable {
    vector<TSinglyList<T>> table; // Вектор списков для хранения элементов
    int capacity; // Вместимость таблицы
    int hashFunction(const T& element) const; // Хеш-функция
public:
    ChainingHashTable(int size);
    ~ChainingHashTable();

    void add(const T& element);
    void remove(const T& element);
    bool find(const T& element) const;
    void display() const;

};

#endif