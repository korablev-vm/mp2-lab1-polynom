#include "postfix.h"
#include <gtest.h>

//TEST(TPostfix, can_create_postfix)
//{
//	ASSERT_NO_THROW(TPostfix<int, std::string> p("a+b"));
//}
//
//TEST(TPostfix, can_create_postfix_with_compound_operand)
//{
//	ASSERT_NO_THROW(TPostfix<int, std::string> p("a+a1"));
//	ASSERT_NO_THROW(TPostfix<int, std::string> p("a13+abc"));
//}
//
//TEST(TPostfix, cant_create_postfix_with_operand_with_number_before_last_letter)
//{
//	ASSERT_ANY_THROW(TPostfix<int, std::string> p("a+a1t"));
//	ASSERT_ANY_THROW(TPostfix<int, std::string> p("a+abc1de"));
//}
//
//TEST(TPostfix, cant_create_postfix_with_operand_with_forbidden_symbol)
//{
//	ASSERT_ANY_THROW(TPostfix<int, std::string> p("a+a:t"));
//	ASSERT_ANY_THROW(TPostfix<int, std::string> p("at#-d"));
//}
//
//TEST(TPostfix, can_create_postfix_with_brackets)
//{
//	ASSERT_NO_THROW(TPostfix<int, std::string> p("(a+b)/c"));
//	ASSERT_NO_THROW(TPostfix<int, std::string> p("(s-r)/(s+r)+k"));
//}
//
//TEST(TPostfix, throws_when_create_postfix_with_different_count_of_left_and_right_brackets)
//{
//	ASSERT_ANY_THROW(TPostfix<int, std::string> p("(a+b)/(c-d"));
//	ASSERT_ANY_THROW(TPostfix<int, std::string> p("(a-d)/(b-f)^k)"));
//}
//
//TEST(TPostfix, can_create_postfix_with_several_operations_in_a_row)
//{
//	ASSERT_NO_THROW(TPostfix<int, std::string> p("m+sin(a)"));
//	ASSERT_NO_THROW(TPostfix<int, std::string> p("(-sqrt(x)+t)*a"));
//}
//
//TEST(TPostfix, throws_when_create_postfix_with_too_many_operations_in_a_row)
//{
//	ASSERT_ANY_THROW(TPostfix<int, std::string> p("a+*b"));
//	ASSERT_ANY_THROW(TPostfix<int, std::string> p("a+t-^k"));
//}
//
//TEST(TPostfix, can_create_postfix_with_constants)
//{
//	ASSERT_NO_THROW(TPostfix<int, std::string> p("a+2"));
//	ASSERT_NO_THROW(TPostfix<int, std::string> p("(a+4)/(a*2)"));
//}
//
//TEST(TPostfix, can_create_postfix_with_space_between_lexems_in_expression)
//{
//	ASSERT_NO_THROW(TPostfix<int, std::string> p("(a + 2) / 2 * (4 - b)"));
//}

TEST(TPostfix, can_return_infix_form)
{
	TPostfix <int, std::string> p("(a + b / 2) * 4");
	EXPECT_EQ("(a+b/2)*4", p.GetInfix());
}

TEST(TPostfix, can_convert_infix_form_to_postfix)
{
	TPostfix <int, std::string> p("(a+2)/2*(4-b)");
	EXPECT_EQ("a2+2/4b-*", p.GetPostfix());
}

TEST(TPostfix, can_calculate_in_postfix)
{
	int x = 4, y = 2, z = 5;
	TPostfix <int, std::string> p("(x+y)*z-x/y");
	EXPECT_EQ(((x + y) * z - x / y), p.Calculate(std::vector<double>{ 4, 2, 5}));
}