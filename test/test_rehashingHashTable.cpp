#include <gtest.h>
#include "RehashingHashTable.h"

// Тест на добавление элемента и его успешное нахождение
TEST(RehashingHashTableTest, AddAndFind) {
    RehashingHashTable<int, std::string> hashTable;
    hashTable.add({ 42, "Answer" });
    EXPECT_EQ(*hashTable.find(42), "Answer");
}

// Тест на успешное удаление элемента
TEST(RehashingHashTableTest, Remove) {
    RehashingHashTable<int, std::string> hashTable;
    hashTable.add({ 42, "Answer" });
    hashTable.remove(42);
    EXPECT_EQ(hashTable.find(42), nullptr);
}

// Тест на успешное добавление нескольких элементов и их нахождение
TEST(RehashingHashTableTest, AddMultipleAndFind) {
    RehashingHashTable<int, std::string> hashTable;
    hashTable.add({ 42, "Answer" });
    hashTable.add({ 10, "Ten" });
    hashTable.add({ 100, "Hundred" });
    EXPECT_EQ(*hashTable.find(42), "Answer");
    EXPECT_EQ(*hashTable.find(10), "Ten");
    EXPECT_EQ(*hashTable.find(100), "Hundred");
}

// Тест на успешное добавление элементов и последующее удаление
TEST(RehashingHashTableTest, AddAndRemove) {
    RehashingHashTable<int, std::string> hashTable;
    hashTable.add({ 42, "Answer" });
    hashTable.add({ 10, "Ten" });
    hashTable.add({ 100, "Hundred" });
    hashTable.remove(10);
    EXPECT_EQ(hashTable.find(10), nullptr);
}

// Тест на попытку удаления несуществующего элемента
TEST(RehashingHashTableTest, RemoveNonExistentElement) {
    RehashingHashTable<int, std::string> hashTable;
    hashTable.add({ 42, "Answer" });
    hashTable.remove(10);
    EXPECT_EQ(*hashTable.find(42), "Answer");
}

// Тест на успешное добавление и поиск элементов с коллизиями
TEST(RehashingHashTableTest, AddAndFindWithCollisions) {
    RehashingHashTable<int, std::string> hashTable(5); // Установка небольшой емкости для удобства тестирования коллизий
    hashTable.add({ 0, "Zero" });
    hashTable.add({ 5, "Five" }); // Коллизия с 0
    hashTable.add({ 10, "Ten" }); // Коллизия с 0 и 5
    EXPECT_EQ(*hashTable.find(0), "Zero");
    EXPECT_EQ(*hashTable.find(5), "Five");
    EXPECT_EQ(*hashTable.find(10), "Ten");
}

// Тест на попытку поиска в пустой таблице
TEST(RehashingHashTableTest, FindInEmptyTable) {
    RehashingHashTable<int, std::string> hashTable;
    EXPECT_EQ(hashTable.find(42), nullptr);
}

// Тест на успешное добавление и удаление элементов, снова добавление и поиск
TEST(RehashingHashTableTest, AddRemoveAddAndFind) {
    RehashingHashTable<int, std::string> hashTable;
    hashTable.add({ 42, "Answer" });
    hashTable.remove(42);
    hashTable.add({ 42, "AnswerAgain" });
    EXPECT_EQ(*hashTable.find(42), "AnswerAgain");
}