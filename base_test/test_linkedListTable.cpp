#include "LinkedListTable.h"
#include <gtest.h>

//TEST(TLinearListTable, can_create_linked_list_table) {
//    ASSERT_NO_THROW(TLinearListTable<string, int> table;);
//}

TEST(TLinearListTable, can_add_element_into_linked_list_table) {
	TLinearListTable<std::string, int> table;
	ASSERT_NO_THROW(table.add({ "testKey", 123 }););
	ASSERT_NE(table.find("testKey"), nullptr);
}

TEST(TLinearListTable, can_not_add_element_with_the_same_key_into_linked_list_table) {
	TLinearListTable<std::string, int> table;
	table.add({ "testKey", 123 });
	table.add({ "testKey", 456 });

	auto* result = table.find("testKey");
	ASSERT_NE(result, nullptr);
	ASSERT_EQ(result->value, 123);
}

TEST(TLinearListTable, can_remove_element_from_linked_list_table) {
	TLinearListTable<std::string, int> table;
	table.add({ "testKey", 123 });
	ASSERT_NO_THROW(table.remove("testKey"););
	ASSERT_EQ(table.find("testKey"), nullptr);
}

TEST(TLinearListTable, can_find_element_in_linked_list_table) {
	TLinearListTable<std::string, int> table;
	table.add({ "testKey", 123 });
	auto* result = table.find("testKey");
	ASSERT_NE(result, nullptr);
	ASSERT_EQ(result->value, 123);
}

TEST(TLinearListTable, can_handle_multiple_distinct_elements) {
	TLinearListTable<std::string, int> table;
	table.add({ "key1", 100 });
	table.add({ "key2", 200 });

	ASSERT_NE(table.find("key1"), nullptr);
	ASSERT_EQ(table.find("key1")->value, 100);
	ASSERT_NE(table.find("key2"), nullptr);
	ASSERT_EQ(table.find("key2")->value, 200);
}

TEST(TLinearListTable, removing_nonexistent_element_does_nothing) {
	TLinearListTable<std::string, int> table;
	table.add({ "key1", 100 });
	ASSERT_NO_THROW(table.remove("keyNonExistent"););
	ASSERT_NE(table.find("key1"), nullptr);
}