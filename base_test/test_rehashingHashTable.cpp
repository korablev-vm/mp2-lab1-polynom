#include "RehashingHashTable.h"
#include <gtest.h>

//TEST(RehashingHashTable, can_create_open_addressing_hash_table) {
//    ASSERT_NO_THROW(RehashingHashTable<string, int> table(10););
//}

TEST(RehashingHashTable, can_add_element_into_open_addressing_hash_table) {
    RehashingHashTable<std::string, int> table(10);
    ASSERT_NO_THROW(table.add({ "key1", 1 }););
    auto result = table.find({ "key1", 0 });
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result->value, 1);
}

TEST(RehashingHashTable, can_not_add_element_with_the_same_key_into_open_addressing_hash_table) {
    RehashingHashTable<std::string, int> table(10);
    table.add({ "key1", 1 });
    table.add({ "key1", 2 }); // Попытка добавить элемент с тем же ключом
    auto result = table.find({ "key1", 0 });
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result->value, 1); // Значение не изменилось на новое
}

TEST(RehashingHashTable, can_remove_element_from_open_addressing_hash_table) {
    RehashingHashTable<std::string, int> table(10);
    table.add({ "key1", 1 });
    ASSERT_NO_THROW(table.remove({ "key1", 1 }););
    ASSERT_EQ(table.find({ "key1", 0 }), nullptr);
}

TEST(RehashingHashTable, can_find_element_in_open_addressing_hash_table) {
    RehashingHashTable<std::string, int> table(10);
    table.add({ "key1", 1 });
    auto result = table.find({ "key1", 0 });
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result->value, 1);
}

TEST(RehashingHashTable, table_handles_collisions_properly) {
    RehashingHashTable<int, std::string> table(10);
    // Добавляем элементы, ключи которых приведут к коллизии в таблице с небольшой вместимостью
    table.add({ 1, "value1" });
    table.add({ 11, "value2" }); // Должен вызвать коллизию с ключом 1 при размере таблицы 10
    auto result1 = table.find({ 1, "" });
    auto result2 = table.find({ 11, "" });
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    ASSERT_EQ(result1->value, "value1");
    ASSERT_EQ(result2->value, "value2");
}

TEST(RehashingHashTable, removing_non_existent_element_does_nothing) {
    RehashingHashTable<std::string, int> table(10);
    table.add({ "key1", 1 });
    ASSERT_NO_THROW(table.remove({ "nonExistentKey", 0 }););
    auto result = table.find({ "key1", 0 });
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result->value, 1);
}