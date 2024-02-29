#ifndef LINEARARRAYTABLE_H
#define LINEARARRAYTABLE_H

#include <iostream>

template <typename T>
class LinearArrayTable {
    T* array; // ������ ��� �������� ���������
    int capacity; // ����������� �������
    int currentSize; // ������� ������ �������
    void resize();
public:
    LinearArrayTable(int size);
    ~LinearArrayTable();

    void add(const T& element);
    void remove(int index);
    T& get(int index) const; // ��������� �������� �� �������
    int find(const T& element) const; // ����� ������� ��������
    void display() const;
    int getSize() const;
};

#endif // LINEARARRAYTABLE_H