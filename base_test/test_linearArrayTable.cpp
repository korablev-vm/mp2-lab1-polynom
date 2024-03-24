//#include "LinearArrayTable.h"
//#include <iostream>
//#include <gtest\gtest.h>
//#include <gmock/gmock.h>
//
//TEST(TUnorderedTable, can_create_table) {
//    ASSERT_NO_THROW(TUnorderedTable<string, int> table);
//}
//
//TEST(TUnorderedTable, can_add_element_into_unordered_table) {
//	TUnorderedTable<std::string, int> table;
//	ASSERT_NO_THROW(table.add({ "testKey", 1 }););
//	auto* result = table.find({ "testKey", 0 });
//	ASSERT_NE(result, nullptr);
//	ASSERT_EQ(result->value, 1);
//}
//
//TEST(TUnorderedTable, can_not_add_element_with_the_same_key_into_unordered_table) {
//	TUnorderedTable<std::string, int> table;
//	table.add({ "testKey", 1 });
//	table.add({ "testKey", 2 });
//
//	auto* result = table.find({ "testKey", 0 });
//	ASSERT_NE(result, nullptr);
//	ASSERT_EQ(result->value, 1);
//}
//
//TEST(TUnorderedTable, can_remove_element_from_unordered_table) {
//	TUnorderedTable<std::string, int> table;
//	table.add({ "testKey", 1 });
//	ASSERT_NO_THROW(table.remove({ "testKey", 1 }););
//	ASSERT_EQ(table.find({ "testKey", 0 }), nullptr);
//}
//
//TEST(TUnorderedTable, can_find_element_in_unordered_table) {
//	TUnorderedTable<std::string, int> table;
//	table.add({ "testKey", 1 });
//	auto* result = table.find({ "testKey", 0 });
//	ASSERT_NE(result, nullptr);
//	ASSERT_EQ(result->value, 1);
//}
//
//TEST(TUnorderedTable, table_is_empty_on_creation) {
//	TUnorderedTable<std::string, int> table;
//	ASSERT_EQ(table.find({ "nonExistentKey", 0 }), nullptr);
//}
//
//TEST(TUnorderedTable, can_handle_multiple_elements) {
//	TUnorderedTable<std::string, int> table;
//	table.add({ "key1", 1 });
//	table.add({ "key2", 2 });
//	table.add({ "key3", 3 });
//
//	ASSERT_NE(table.find({ "key1", 0 }), nullptr);
//	ASSERT_NE(table.find({ "key2", 0 }), nullptr);
//	ASSERT_NE(table.find({ "key3", 0 }), nullptr);
//	ASSERT_EQ(table.find({ "key1", 0 })->value, 1);
//	ASSERT_EQ(table.find({ "key2", 0 })->value, 2);
//	ASSERT_EQ(table.find({ "key3", 0 })->value, 3);
//}
//
//TEST(TUnorderedTable, removing_non_existent_element_does_not_cause_failure) {
//	TUnorderedTable<std::string, int> table;
//	table.add({ "key1", 1 });
//	ASSERT_NO_THROW(table.remove({ "nonExistentKey", 0 }););
//}
