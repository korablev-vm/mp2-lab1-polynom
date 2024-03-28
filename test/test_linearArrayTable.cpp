#include <gtest.h>
#include "LinearArrayTable.h"

// Тест проверяет добавление и поиск элемента
TEST(UnorderedTableTest, AddAndFind) {
    TUnorderedTable<int, std::string> table;

    TRecord<int, std::string> record = { 1, "Value1" };
    table.add(record);

    EXPECT_EQ(*table.find(1), "Value1");
}

// Тест проверяет удаление элемента
TEST(UnorderedTableTest, Remove) {
    TUnorderedTable<int, std::string> table;

    TRecord<int, std::string> record = { 1, "Value1" };
    table.add(record);
    table.remove(1);

    EXPECT_EQ(table.find(1), nullptr);
}

// Тест проверяет поиск отсутствующего элемента
TEST(UnorderedTableTest, FindNonExistent) {
    TUnorderedTable<int, std::string> table;

    EXPECT_EQ(table.find(1), nullptr);
}

// Тест проверяет добавление нескольких элементов с разными ключами
TEST(UnorderedTableTest, AddMultipleDifferentKeys) {
    TUnorderedTable<int, std::string> table;

    TRecord<int, std::string> record1 = { 1, "Value1" };
    TRecord<int, std::string> record2 = { 2, "Value2" };

    table.add(record1);
    table.add(record2);

    EXPECT_EQ(*table.find(1), "Value1");
    EXPECT_EQ(*table.find(2), "Value2");
}

// Тест проверяет добавление нескольких элементов с одинаковыми ключами
TEST(UnorderedTableTest, AddMultipleSameKeys) {
    TUnorderedTable<int, std::string> table;

    TRecord<int, std::string> record1 = { 1, "Value1" };
    TRecord<int, std::string> record2 = { 1, "Value2" };

    table.add(record1);
    table.add(record2);

    EXPECT_EQ(*table.find(1), "Value1");
}

// Тест проверяет удаление элемента, отсутствующего в таблице
TEST(UnorderedTableTest, RemoveNonExistent) {
    TUnorderedTable<int, std::string> table;

    table.remove(1); // Удаляем элемент, который не существует

    // Ожидается, что ничего не изменится
    EXPECT_EQ(table.find(1), nullptr);
}

// Тест проверяет добавление большого количества элементов
TEST(UnorderedTableTest, AddLargeNumber) {
    TUnorderedTable<int, std::string> table;

    const int numElements = 1000;

    // Добавление большого количества элементов
    for (int i = 0; i < numElements; ++i) {
        TRecord<int, std::string> record = { i, "Value" + std::to_string(i) };
        table.add(record);
    }

    // Проверка наличия добавленных элементов
    for (int i = 0; i < numElements; ++i) {
        EXPECT_EQ(*table.find(i), "Value" + std::to_string(i));
    }
}

// Тест проверяет отображение содержимого таблицы
TEST(UnorderedTableTest, Display) {
    TUnorderedTable<int, std::string> table;

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

// Тест проверяет удаление всех элементов из таблицы
TEST(UnorderedTableTest, RemoveAll) {
    TUnorderedTable<int, std::string> table;

    TRecord<int, std::string> record1 = { 1, "Value1" };
    TRecord<int, std::string> record2 = { 2, "Value2" };

    table.add(record1);
    table.add(record2);

    table.remove(1);
    table.remove(2);

    EXPECT_EQ(table.find(1), nullptr);
    EXPECT_EQ(table.find(2), nullptr);
}

// Тест проверяет работу методов после множества добавлений и удалений
TEST(UnorderedTableTest, AddRemoveMultiple) {
    TUnorderedTable<int, std::string> table;

    const int numElements = 100;

    // Добавление элементов
    for (int i = 0; i < numElements; ++i) {
        TRecord<int, std::string> record = { i, "Value" + std::to_string(i) };
        table.add(record);
    }

    // Удаление четных элементов
    for (int i = 0; i < numElements; ++i) {
        if (i % 2 == 0) {
            table.remove(i);
        }
    }

    // Проверка наличия добавленных элементов
    for (int i = 0; i < numElements; ++i) {
        if (i % 2 == 0) {
            EXPECT_EQ(table.find(i), nullptr);
        }
        else {
            EXPECT_EQ(*table.find(i), "Value" + std::to_string(i));
        }
    }
}