#ifndef LINEARARRAYTABLE_H
#define LINEARARRAYTABLE_H

#include <iostream>

template <typename T>
class LinearArrayTable {
    T* array; // Массив для хранения полиномов
    int capacity; // Вместимость таблицы
    int currentSize; // Текущий размер таблицы
    void resize();
public:
    LinearArrayTable(int size);
    ~LinearArrayTable();

    void add(const T& element);
    void remove(int index);
    T& get(int index) const; // Получение полинома по индексу
    int find(const T& element) const; // Поиск индекса полинома
    void display() const;
    int getSize() const;
};

#endif // LINEARARRAYTABLE_H