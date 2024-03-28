#include <iostream>
#include <memory>
#include "AVLTree.h"
#include "ChainingHashTable.h"
#include "LinearArrayTable.h"
#include "LinkedListTable.h"
#include "RehashingHashTable.h"
#include "Polinom.h"
#include "SortedArrayTable.h"
#include <TableManager.h>

int main() {
    // �������� ��������� ������
    TableManager<std::string, int> manager;

    // �������� ������
    auto sortedTable = std::make_shared<TSortedTable<std::string, int>>();
    auto unorderedTable = std::make_shared<TUnorderedTable<std::string, int>>();
    auto chainingHashTable = std::make_shared<ChainingHashTable<std::string, int>>();
   

    // ���������� ������ � ��������
    manager.addTable(sortedTable);
    manager.addTable(unorderedTable);
    manager.addTable(chainingHashTable);

    // ����� �������� �������
    manager.setActiveTable(0);
    TRecord<std::string, int> recordm{ "test", 5 };
    manager.add(recordm);

    // �������� �������
    TRecord<std::string, int> record1{ "apple", 5 };
    TRecord<std::string, int> record2{ "banana", 2 };
    TRecord<std::string, int> record3{ "cherry", 12 };

    // ���������� ������� �� ��� �������
    manager.addAll(record1);
    manager.addAll(record2);
    manager.addAll(record3);

    // �������� ������ �� ���� ������
    manager.removeAll("banana");

    // ����������� �������� �������
    std::cout << "Active table:" << std::endl;
    manager.display();
    std::cout << std::endl;

    // ����������� ����������� ������ �������
    std::cout << "Sorted Table:" << std::endl;
    sortedTable->display();
    std::cout << std::endl;

    std::cout << "Unordered Table:" << std::endl;
    unorderedTable->display();
    std::cout << std::endl;

    std::cout << "Chaining Hash Table:" << std::endl;
    chainingHashTable->display();

    return 0;
}