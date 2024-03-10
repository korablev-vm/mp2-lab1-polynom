#ifndef LINKEDLISTTABLE_H
#define LINKEDLISTTABLE_H

#include "TableInterface.h"
#include <iostream>

template <typename T>
class LinkedListTable : public TableInterface<T> {
private:
    class Node {
    public:
        T data;
        Node* next;

        Node(T data, Node* next = nullptr) : data(data), next(next) {}
    };

    Node* head;
    int size;

public:
    LinkedListTable() : head(nullptr), size(0) {}
    ~LinkedListTable();

    void add(const T& element) override;
    void remove(const T& element) override;
    bool find(const T& element) const override;
    void display() const override;
};


#endif // LINKEDLISTTABLE_H
