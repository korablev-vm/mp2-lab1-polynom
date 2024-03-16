#include "SortedArrayTable.h"
#include <gtest.h>

//TEST(TSortedTable, can_create_sorted_table) {
//    ASSERT_NO_THROW(TSortedTable<std::string, int> table;);
//}

TEST(TSortedTable, can_add_element_into_sorted_table) {
    TSortedTable<std::string, int> table;
    ASSERT_NO_THROW(table.add({ "key1", 1 }););
    auto* result = table.find({ "key1", 0 });
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result->value, 1);
}

TEST(TSortedTable, can_not_add_element_with_the_same_key_into_sorted_table) {
    TSortedTable<std::string, int> table;
    table.add({ "key1", 1 });
    table.add({ "key1", 2 });

    auto* result = table.find({ "key1", 0 });
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result->value, 1);
}

TEST(TSortedTable, can_remove_element_from_sorted_table) {
    TSortedTable<std::string, int> table;
    table.add({ "key1", 1 });
    ASSERT_NO_THROW(table.remove({ "key1", 1 }););
    ASSERT_EQ(table.find({ "key1", 0 }), nullptr);
}

TEST(TSortedTable, can_find_element_in_sorted_table) {
    TSortedTable<std::string, int> table;
    table.add({ "key1", 1 });
    auto* result = table.find({ "key1", 0 });
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result->value, 1);
}

TEST(TSortedTable, can_handle_multiple_elements) {
    TSortedTable<int, std::string> table;
    table.add({ 3, "value3" });
    table.add({ 1, "value1" });
    table.add({ 2, "value2" });

    ASSERT_NE(table.find({ 1, "" }), nullptr);
    ASSERT_EQ(table.find({ 1, "" })->value, "value1");
    ASSERT_NE(table.find({ 2, "" }), nullptr);
    ASSERT_EQ(table.find({ 2, "" })->value, "value2");
    ASSERT_NE(table.find({ 3, "" }), nullptr);
    ASSERT_EQ(table.find({ 3, "" })->value, "value3");
}

TEST(TSortedTable, can_remove_element_and_still_find_others) {
    TSortedTable<std::string, int> table;
    table.add({ "key1", 1 });
    table.add({ "key2", 2 });
    table.remove({ "key1", 1 });

    ASSERT_EQ(table.find({ "key1", 0 }), nullptr);
    ASSERT_NE(table.find({ "key2", 0 }), nullptr);
    ASSERT_EQ(table.find({ "key2", 0 })->value, 2);
}