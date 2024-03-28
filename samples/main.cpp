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
    // Создание менеджера таблиц
    TableManager<std::string, int> manager;

    // Создание таблиц
    auto sortedTable = std::make_shared<TSortedTable<std::string, int>>();
    auto unorderedTable = std::make_shared<TUnorderedTable<std::string, int>>();
    auto chainingHashTable = std::make_shared<ChainingHashTable<std::string, int>>();
   

    // Добавление таблиц в менеджер
    manager.addTable(sortedTable);
    manager.addTable(unorderedTable);
    manager.addTable(chainingHashTable);

    // Выбор активной таблицы
    manager.setActiveTable(0);
    TRecord<std::string, int> recordm{ "test", 5 };
    manager.add(recordm);

    // Создание записей
    TRecord<std::string, int> record1{ "apple", 5 };
    TRecord<std::string, int> record2{ "banana", 2 };
    TRecord<std::string, int> record3{ "cherry", 12 };

    // Добавление записей во все таблицы
    manager.addAll(record1);
    manager.addAll(record2);
    manager.addAll(record3);

    // Удаление записи из всех таблиц
    manager.removeAll("banana");

    // Отображение активной таблицы
    std::cout << "Active table:" << std::endl;
    manager.display();
    std::cout << std::endl;

    // Отображение содержимого каждой таблицы
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