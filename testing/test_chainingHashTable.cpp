//#include "ChainingHashTable.h"
//#include <gtest.h>
//#include <string>
//
////TEST(ChainingHashTable, can_create_chaining_hash_table_with_explicit_capacity) {
////    ASSERT_NO_THROW(ChainingHashTable <string, int> table;);
////}
//
//TEST(ChainingHashTable, can_add_element_into_chaining_hash_table) {
//	ChainingHashTable<std::string, int> table;
//	ASSERT_NO_THROW(table.add({ "testKey", 1 }));
//}
//
//TEST(ChainingHashTable, can_not_add_element_with_the_same_key_into_chaining_hash_table) {
//	ChainingHashTable<std::string, int> table;
//	table.add({ "testKey", 1 }); // Добавляем элемент с ключом "testKey" и значением 1
//
//	table.add({ "testKey", 2 }); // Пытаемся добавить еще один элемент с тем же ключом, но другим значением
//
//	auto* result = table.find({ "testKey", 0 }); // Ищем элемент по ключу "testKey"
//	ASSERT_NE(result, nullptr); // Убедимся, что элемент найден
//	ASSERT_EQ(result->value, 1); // Проверяем, что значение осталось первоначальным (1), а не изменилось на 2
//}
//
//
//TEST(ChainingHashTable, can_remove_element_from_chaining_hash_table) {
//	ChainingHashTable<std::string, int> table;
//	table.add({ "testKey", 1 });
//
//	ASSERT_NO_THROW(table.remove({ "testKey", 1 }));
//	ASSERT_EQ(table.find({ "testKey", 1 }), nullptr);
//}
//
//TEST(ChainingHashTable, can_find_element_in_chaining_hash_table) {
//	ChainingHashTable<std::string, int> table;
//	table.add({ "testKey", 1 });
//
//	auto* result = table.find({ "testKey", 1 });
//	ASSERT_NE(result, nullptr);
//	ASSERT_EQ(result->value, 1);
//}
//
//TEST(ChainingHashTable, added_element_is_correct) {
//	ChainingHashTable<std::string, int> table;
//	table.add({ "testKey", 42 });
//
//	auto* result = table.find({ "testKey", 42 });
//	ASSERT_NE(result, nullptr);
//	ASSERT_EQ(result->value, 42);
//}
//
//TEST(ChainingHashTable, can_handle_collision) {
//	ChainingHashTable<int, std::string> table(10);
//	table.add({ 1, "value1" });
//	table.add({ 11, "value2" });
//
//	ASSERT_NE(table.find({ 1 }), nullptr);
//	ASSERT_NE(table.find({ 11 }), nullptr);
//	ASSERT_EQ(table.find({ 1 })->value, "value1");
//	ASSERT_EQ(table.find({ 11 })->value, "value2");
//}
//
//TEST(ChainingHashTable, cannot_find_non_existent_element) {
//	ChainingHashTable<std::string, int> table;
//	ASSERT_EQ(table.find({ "nonExistentKey", 0 }), nullptr);
//}
