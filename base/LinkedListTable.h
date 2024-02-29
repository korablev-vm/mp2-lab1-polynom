#ifndef LINKEDLISTTABLE_H
#define LINKEDLISTTABLE_H

#include <iostream>

template <typename T>
class LinkedListTable {
    Node<T>* head; // Голова списка
    int size; // Размер списка
public:
    LinkedListTable();
    ~LinkedListTable();

    void add(const T& element); // Добавление полинома
    void remove(const T& element); // Удаление полинома
    T* find(const T& element) const; // Поиск полинома
    void display() const; // Отображение таблицы
    int getSize() const; // Получение размера таблицы

};

template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node(T data, Node* next = nullptr);
};

#endif // LINKEDLISTTABLE_H