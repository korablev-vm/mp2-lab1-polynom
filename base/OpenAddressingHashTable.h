#ifndef OPENADDRESSINGHASHTABLE_H
#define OPENADDRESSINGHASHTABLE_H

#include <vector>
using namespace std;

template <typename T>
class OpenAddressingHashTable {
    vector<T> table; // ������ ��� �������� ���������
    int capacity; // ����������� �������
    int hashFunction(const T& element) const; // ���-�������
public:
    OpenAddressingHashTable(int size);
    ~OpenAddressingHashTable();

    void add(const T& element);
    void remove(const T& element);
    bool find(const T& element) const;
    void display() const;
    
};

#endif // OPENADDRESSINGHASHTABLE_H