#include "SortedArrayTable.h"
#include <gtest.h>

// Тест на добавление элемента в таблицу
TEST(TSortedTableTest, AddElement) {
    TSortedTable<int, std::string> table;
    table.add({ 42, "Answer" });
    EXPECT_EQ(*table.find(42), "Answer");
}

// Тест на удаление элемента из таблицы
TEST(TSortedTableTest, RemoveElement) {
    TSortedTable<int, std::string> table;
    table.add({ 42, "Answer" });
    table.remove(42);
    EXPECT_EQ(table.find(42), nullptr);
}

// Тест на поиск существующего элемента в таблице
TEST(TSortedTableTest, FindExistingElement) {
    TSortedTable<int, std::string> table;
    table.add({ 42, "Answer" });
    EXPECT_EQ(*table.find(42), "Answer");
}

// Тест на поиск несуществующего элемента в таблице
TEST(TSortedTableTest, FindNonExistentElement) {
    TSortedTable<int, std::string> table;
    EXPECT_EQ(table.find(42), nullptr);
}

// Тест на добавление нескольких элементов в таблицу
TEST(TSortedTableTest, AddMultipleElements) {
    TSortedTable<int, std::string> table;
    table.add({ 42, "Answer" });
    table.add({ 10, "Ten" });
    table.add({ 100, "Hundred" });
    EXPECT_EQ(*table.find(42), "Answer");
    EXPECT_EQ(*table.find(10), "Ten");
    EXPECT_EQ(*table.find(100), "Hundred");
}

// Тест на удаление несуществующего элемента из таблицы
TEST(TSortedTableTest, RemoveNonExistentElement) {
    TSortedTable<int, std::string> table;
    table.add({ 42, "Answer" });
    table.remove(10);
    EXPECT_EQ(*table.find(42), "Answer");
}

// Тест на удаление элемента из пустой таблицы
TEST(TSortedTableTest, RemoveElementFromEmptyTable) {
    TSortedTable<int, std::string> table;
    table.remove(42);
    EXPECT_EQ(table.find(42), nullptr);
}

// Тест на добавление элемента существующего ключа
TEST(TSortedTableTest, AddExistingKey) {
    TSortedTable<int, std::string> table;
    table.add({ 42, "Answer" });
    table.add({ 42, "DifferentAnswer" });
    EXPECT_EQ(*table.find(42), "Answer");
}

// Тест на добавление элемента с пустым значением
TEST(TSortedTableTest, AddEmptyValue) {
    TSortedTable<int, std::string> table;
    table.add({ 42, "" });
    EXPECT_EQ(*table.find(42), "");
}

// Тест на добавление элемента с ключом, равным минимальному значению
TEST(TSortedTableTest, AddMinKey) {
    TSortedTable<int, std::string> table;
    table.add({ std::numeric_limits<int>::min(), "MinValue" });
    EXPECT_EQ(*table.find(std::numeric_limits<int>::min()), "MinValue");
}

// Тест на добавление элемента с ключом, равным максимальному значению
TEST(TSortedTableTest, AddMaxKey) {
    TSortedTable<int, std::string> table;
    table.add({ std::numeric_limits<int>::max(), "MaxValue" });
    EXPECT_EQ(*table.find(std::numeric_limits<int>::max()), "MaxValue");
}

// Тест на поиск элемента в пустой таблице
TEST(TSortedTableTest, FindElementInEmptyTable) {
    TSortedTable<int, std::string> table;
    EXPECT_EQ(table.find(42), nullptr);
}