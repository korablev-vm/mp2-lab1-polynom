#ifndef SORTEDARRAYTABLE_H
#define SORTEDARRAYTABLE_H

#include <iostream>

template <typename T>
class SortedArrayTable {
    T* array; // Массив для хранения полиномов
    int capacity; // Вместимость таблицы
    int currentSize; // Текущий размер таблицы
    void resize();
    int binarySearch(const T& element) const;
public:
    SortedArrayTable(int size);
    ~SortedArrayTable();

    void add(const T& element);
    void remove(const T& element);
    T& get(int index) const; // Получение полинома по индексу
    int find(const T& element) const; // Поиск индекса полинома
    void display() const;
    int getSize() const;

};

#endif // SORTEDARRAYTABLE_H
