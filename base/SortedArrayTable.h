#ifndef SORTEDARRAYTABLE_H
#define SORTEDARRAYTABLE_H

#include <iostream>

template <typename T>
class SortedArrayTable {
    T* array; // ������ ��� �������� ���������
    int capacity; // ����������� �������
    int currentSize; // ������� ������ �������
    void resize();
    int binarySearch(const T& element) const;
public:
    SortedArrayTable(int size);
    ~SortedArrayTable();

    void add(const T& element);
    void remove(const T& element);
    T& get(int index) const; // ��������� �������� �� �������
    int find(const T& element) const; // ����� ������� ��������
    void display() const;
    int getSize() const;

};

#endif // SORTEDARRAYTABLE_H
