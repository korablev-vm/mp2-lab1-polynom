#include "postfix.h"
#include <gtest.h>
#include "LinearArrayTable.h"

static TableManager<std::string, Polinom> manager;

TEST(TPostfix, can_create_postfix)
{
	auto unorderedTable = std::make_shared<TUnorderedTable<std::string, Polinom>>();
	manager.addTable(unorderedTable);
	ASSERT_NO_THROW(TPostfix<std::string> p("a+b", manager));
}

TEST(TPostfix, can_create_postfix_with_compound_operand)
{
	auto unorderedTable = std::make_shared<TUnorderedTable<std::string, Polinom>>();
	manager.addTable(unorderedTable);
	ASSERT_NO_THROW(TPostfix<std::string> p("a+a1", manager));
	ASSERT_NO_THROW(TPostfix<std::string> p("a13+abc", manager));
}

TEST(TPostfix, cant_create_postfix_with_operand_with_number_before_last_letter)
{
	auto unorderedTable = std::make_shared<TUnorderedTable<std::string, Polinom>>();
	manager.addTable(unorderedTable);
	ASSERT_ANY_THROW(TPostfix<std::string> p("a+a1t", manager));
	ASSERT_ANY_THROW(TPostfix<std::string> p("a+abc1de", manager));
}

TEST(TPostfix, cant_create_postfix_with_operand_with_forbidden_symbol)
{
	auto unorderedTable = std::make_shared<TUnorderedTable<std::string, Polinom>>();
	manager.addTable(unorderedTable);
	ASSERT_ANY_THROW(TPostfix<std::string> p("a+a:t", manager));
	ASSERT_ANY_THROW(TPostfix<std::string> p("at#-d", manager));
}

TEST(TPostfix, can_create_postfix_with_brackets)
{
	auto unorderedTable = std::make_shared<TUnorderedTable<std::string, Polinom>>();
	manager.addTable(unorderedTable);
	ASSERT_NO_THROW(TPostfix<std::string> p("(a+b)*c", manager));
	ASSERT_NO_THROW(TPostfix<std::string> p("(s-r)*(s+r)+k", manager));
}

TEST(TPostfix, throws_when_create_postfix_with_different_count_of_left_and_right_brackets)
{
	auto unorderedTable = std::make_shared<TUnorderedTable<std::string, Polinom>>();
	manager.addTable(unorderedTable);
	ASSERT_ANY_THROW(TPostfix<std::string> p("(a+b)*(c-d", manager));
	ASSERT_ANY_THROW(TPostfix<std::string> p("(a-d)*(b-f)^k)", manager));
}

TEST(TPostfix, can_create_postfix_with_several_operations_in_a_row)
{
	auto unorderedTable = std::make_shared<TUnorderedTable<std::string, Polinom>>();
	manager.addTable(unorderedTable);
	ASSERT_NO_THROW(TPostfix<std::string> p("m+s*w", manager));
}

TEST(TPostfix, throws_when_create_postfix_with_too_many_operations_in_a_row)
{
	auto unorderedTable = std::make_shared<TUnorderedTable<std::string, Polinom>>();
	manager.addTable(unorderedTable);
	ASSERT_ANY_THROW(TPostfix<std::string> p("a+*b", manager));
	ASSERT_ANY_THROW(TPostfix<std::string> p("a+t**k", manager));
}

TEST(TPostfix, can_create_postfix_with_constants)
{
	auto unorderedTable = std::make_shared<TUnorderedTable<std::string, Polinom>>();
	manager.addTable(unorderedTable);
	ASSERT_NO_THROW(TPostfix<std::string> p("a+2", manager));
	ASSERT_NO_THROW(TPostfix<std::string> p("(a+4)-(a*2)", manager));
}

TEST(TPostfix, can_create_postfix_with_space_between_lexems_in_expression)
{
	auto unorderedTable = std::make_shared<TUnorderedTable<std::string, Polinom>>();
	manager.addTable(unorderedTable);
	ASSERT_NO_THROW(TPostfix<std::string> p("(a +  2) +2 * (4    - b)", manager));
}

TEST(TPostfix, can_return_infix_form)
{
	auto unorderedTable = std::make_shared<TUnorderedTable<std::string, Polinom>>();
	manager.addTable(unorderedTable);
	TPostfix <std::string> p("(a + b) * 4", manager);
	EXPECT_EQ("(a+b)*4", p.GetInfix());
}

TEST(TPostfix, can_convert_infix_form_to_postfix)
{
	auto unorderedTable = std::make_shared<TUnorderedTable<std::string, Polinom>>();
	manager.addTable(unorderedTable);
	TPostfix <std::string> p("(a+2)-2*(4-b)", manager);
	EXPECT_EQ("a2+24b-*-", p.GetPostfix());
}

TEST(TPostfix, can_work_with_polynoms)
{
	auto unorderedTable = std::make_shared<TUnorderedTable<std::string, Polinom>>();
	manager.addTable(unorderedTable);
	manager.addAll(TRecord<std::string, Polinom>{ "p", Polinom ("13x^2")});
	TPostfix <std::string> p("(Diff(p,x)+2)-2*(4-b)", manager);
	EXPECT_EQ("pxDiff2+24b-*-", p.GetPostfix());
}

TEST(TPostfix, can_calculate_polynoms_in_postfix)
{
	auto unorderedTable = std::make_shared<TUnorderedTable<std::string, Polinom>>();
	manager.addTable(unorderedTable);
	Polinom p1("13x^2+3y^2"), p2("2y");
	manager.addAll(TRecord<std::string, Polinom>{"p1", p1});
	manager.addAll(TRecord<std::string, Polinom>{"p2", p2});
	double x = 4, y = 2;
	TPostfix <std::string> p("Diff(p1, x)+Integr(p2, y)-p1*p2", manager);
	EXPECT_EQ((double)(26 * x + pow(y, 2) - (13 * 2 * pow(x, 2) * y + 6 * pow(y, 3))), p.Calculate(std::vector<double>{x, y}));
}