#ifndef LINKEDLISTTABLE_H
#define LINKEDLISTTABLE_H

#include <iostream>

template <typename T>
class LinkedListTable {
    Node<T>* head; // ������ ������
    int size; // ������ ������
public:
    LinkedListTable();
    ~LinkedListTable();

    void add(const T& element); // ���������� ��������
    void remove(const T& element); // �������� ��������
    T* find(const T& element) const; // ����� ��������
    void display() const; // ����������� �������
    int getSize() const; // ��������� ������� �������

};

template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node(T data, Node* next = nullptr);
};

#endif // LINKEDLISTTABLE_H