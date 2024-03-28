#include <gtest.h>
#include "ChainingHashTable.h"

// Тест проверяет добавление и поиск элементов в хэш-таблице
TEST(ChainingHashTableTest, AddAndFind) {
    ChainingHashTable<int, std::string> table;

    // Добавление записей
    TRecord<int, std::string> record1 = { 1, "Value1" };
    TRecord<int, std::string> record2 = { 2, "Value2" };
    table.add(record1);
    table.add(record2);

    // Проверка нахождения добавленных записей
    EXPECT_EQ(*table.find(1), "Value1");
    EXPECT_EQ(*table.find(2), "Value2");
}

// Тест проверяет удаление элементов из хэш-таблицы
TEST(ChainingHashTableTest, Remove) {
    ChainingHashTable<int, std::string> table;

    // Добавление записи и её последующее удаление
    TRecord<int, std::string> record1 = { 1, "Value1" };
    table.add(record1);
    table.remove(1);

    // Ожидается, что запись больше не будет найдена в таблице
    EXPECT_EQ(table.find(1), nullptr);
}

// Тест проверяет корректность обработки дублирующихся ключей
TEST(ChainingHashTableTest, AddDuplicate) {
    ChainingHashTable<int, std::string> table;

    // Добавление записи с ключом, который уже существует
    TRecord<int, std::string> record1 = { 1, "Value1" };
    TRecord<int, std::string> record2 = { 1, "Value2" };
    table.add(record1);
    table.add(record2);

    // Ожидается, что будет добавлена только одна запись с ключом 1
    EXPECT_EQ(*table.find(1), "Value1");
}

// Тест проверяет поиск элемента, которого нет в хэш-таблице
TEST(ChainingHashTableTest, FindNonExistent) {
    ChainingHashTable<int, std::string> table;

    // Поиск записи по ключу, который отсутствует в таблице
    EXPECT_EQ(table.find(1), nullptr);
}

// Тест проверяет отображение содержимого хэш-таблицы
TEST(ChainingHashTableTest, Display) {
    ChainingHashTable<int, std::string> table;

    // Добавление нескольких записей в таблицу
    TRecord<int, std::string> record1 = { 1, "Value1" };
    TRecord<int, std::string> record2 = { 2, "Value2" };
    table.add(record1);
    table.add(record2);

    // Перенаправление вывода для проверки отображения
    std::stringstream output;
    std::streambuf* coutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    // Отображение таблицы
    table.display();

    std::cout.rdbuf(coutBuffer); // Восстановление вывода

    // Проверка корректности вывода
    std::string expectedOutput = "Key: 1, Value: Value1\nKey: 2, Value: Value2\n";
    EXPECT_EQ(output.str(), expectedOutput);
}

// Тест проверяет добавление и последующее удаление нескольких элементов
TEST(ChainingHashTableTest, AddRemoveMultiple) {
    ChainingHashTable<int, std::string> table;

    // Добавление нескольких записей и их последующее удаление
    TRecord<int, std::string> record1 = { 1, "Value1" };
    TRecord<int, std::string> record2 = { 2, "Value2" };
    TRecord<int, std::string> record3 = { 3, "Value3" };
    TRecord<int, std::string> record4 = { 4, "Value4" };

    table.add(record1);
    table.add(record2);
    table.add(record3);
    table.add(record4);

    table.remove(2);
    table.remove(3);

    // Проверка отсутствия удаленных записей в таблице
    EXPECT_EQ(table.find(2), nullptr);
    EXPECT_EQ(table.find(3), nullptr);
}

// Тест проверяет удаление всех элементов из хэш-таблицы
TEST(ChainingHashTableTest, AddRemoveAll) {
    ChainingHashTable<int, std::string> table;

    // Добавление нескольких записей и их последующее удаление
    TRecord<int, std::string> record1 = { 1, "Value1" };
    TRecord<int, std::string> record2 = { 2, "Value2" };
    TRecord<int, std::string> record3 = { 3, "Value3" };
    TRecord<int, std::string> record4 = { 4, "Value4" };

    table.add(record1);
    table.add(record2);
    table.add(record3);
    table.add(record4);

    table.remove(1);
    table.remove(2);
    table.remove(3);
    table.remove(4);

    // Проверка отсутствия всех записей в таблице
    EXPECT_EQ(table.find(1), nullptr);
    EXPECT_EQ(table.find(2), nullptr);
    EXPECT_EQ(table.find(3), nullptr);
    EXPECT_EQ(table.find(4), nullptr);
}

// Тест проверяет корректность обработки дублирующихся ключей при добавлении
TEST(ChainingHashTableTest, AddRemoveDuplicateKeys) {
    ChainingHashTable<int, std::string> table;

    // Добавление двух записей с одинаковым ключом
    TRecord<int, std::string> record1 = { 1, "Value1" };
    TRecord<int, std::string> record2 = { 1, "Value2" };

    table.add(record1);
    table.add(record2);

    // Ожидается, что в таблице останется только одна запись с ключом 1
    EXPECT_EQ(*table.find(1), "Value1");

    // Удаление записи
    table.remove(1);

    EXPECT_EQ(table.find(1), nullptr);
}

// Тест проверяет добавление и поиск элементов с коллизиями хэшей
TEST(ChainingHashTableTest, AddFindWithCollision) {
    ChainingHashTable<int, std::string> table(5);

    // Добавление записей с ключами, которые вызовут коллизии
    TRecord<int, std::string> record1 = { 1, "Value1" };
    TRecord<int, std::string> record2 = { 6, "Value6" };

    table.add(record1);
    table.add(record2);

    // Проверка нахождения добавленных записей
    EXPECT_EQ(*table.find(1), "Value1");
    EXPECT_EQ(*table.find(6), "Value6");
}