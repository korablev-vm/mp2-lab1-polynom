#include "List.h"
#include <gtest.h>

TEST(List, can_create)
{
	ASSERT_NO_THROW(List<int> list);
}

TEST(List, can_insert_element)
{
	List<int> list;
	ASSERT_NO_THROW(list.insertInOrder(13));
}

TEST(List, can_return_size_of_list)
{
	List<int> list;
	EXPECT_EQ(0, list.size());
}

TEST(List, can_return_elem_by_index)
{
	List<int> list;
	list.insertInOrder(13);
	ASSERT_NO_THROW(list[0]);
	EXPECT_EQ(13, list[0]);
}

TEST(List, throws_when_take_element_with_too_big_index)
{
	List<int> list;
	list.insertInOrder(13);
	ASSERT_ANY_THROW(list[1]);
}

TEST(List, throws_when_take_element_with_too_small_index)
{
	List<int> list;
	list.insertInOrder(13);
	ASSERT_ANY_THROW(list[-1]);
}

TEST(List, elements_are_added_in_ascending_order)
{
	List<int> list;
	list.insertInOrder(13);
	list.insertInOrder(3);
	EXPECT_EQ(3, list[0]);
	EXPECT_EQ(13, list[1]);
}

TEST(List, inserting_is_changing_size_of_list)
{
	List<int> list;
	list.insertInOrder(13);
	EXPECT_EQ(1, list.size());
	list.insertInOrder(3);
	EXPECT_EQ(2, list.size());
}

TEST(List, can_change_element_by_its_index)
{
	List<int> list;
	list.insertInOrder(3);
	list[0] = 13;
	EXPECT_EQ(13, list[0]);
}

TEST(List, can_erase_element_by_its_index)
{
	List<int> list;
	list.insertInOrder(3);
	list.insertInOrder(5);
	list.insertInOrder(13);
	list.erase(1);
	EXPECT_EQ(3, list[0]);
	EXPECT_EQ(13, list[1]);
}

TEST(List, erasing_is_changing_size_of_list)
{
	List<int> list;
	list.insertInOrder(13);
	list.insertInOrder(3);
	EXPECT_EQ(2, list.size());
	list.erase(0);
	EXPECT_EQ(1, list.size());
}

TEST(List, can_compare_lists)
{
	List<int> list1, list2;
	list1.insertInOrder(13);
	EXPECT_EQ(true, list1 != list2);
	list2.insertInOrder(13);
	EXPECT_EQ(true, list1 == list2);
}

TEST(List, can_assign_one_list_to_another)
{
	List<int> list1, list2;
	list1.insertInOrder(13);
	list2.insertInOrder(3);
	list2 = list1;
	EXPECT_EQ(13, list2[0]);
}