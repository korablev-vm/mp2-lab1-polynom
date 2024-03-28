#include <gtest.h>
#include "Polinom.h"

TEST(Polinom, can_create_polinom)
{
	ASSERT_NO_THROW(Polinom p(20, "x^2"));
}

TEST(Polinom, throws_when_try_to_create_polinom_with_too_big_max_degree)
{
	ASSERT_ANY_THROW(Polinom p(51, "x^2"));
}

TEST(Polinom, throws_when_try_to_create_polinom_with_too_small_max_degree)
{
	ASSERT_ANY_THROW(Polinom p(-1, "x^2"));
}

TEST(Polinom, throws_when_try_to_create_polinom_with_incorrect_variable)
{
	ASSERT_ANY_THROW(Polinom p(-1, "x]^2"));
}

TEST(Polinom, can_create_copy)
{
	Polinom p(3, "4x^2");
	ASSERT_NO_THROW(Polinom p1(p));
}

TEST(Polinom, can_invert_polinom_to_string)
{
	Polinom p(3, "13x^2");
	EXPECT_EQ("13x^2", p.ToString());
}

TEST(Polinom, can_assign_one_polinom_to_another)
{
	Polinom p1(3, "13x^2");
	Polinom p2(3, "2x^3");
	p2 = p1;
	EXPECT_EQ(p1.ToString(), p2.ToString());
}

TEST(Polinom, can_add_one_polinom_to_another)
{
	Polinom p1(3, "13x^2");
	Polinom p2(3, "2x^3");
	Polinom p = p1 + p2;
	EXPECT_EQ("13x^2+2x^3", p.ToString());
}

TEST(Polinom, can_multiply_one_polinom_to_another)
{
	Polinom p1(6, "13x^2");
	Polinom p2(6, "2x^3");
	Polinom p = p1 * p2;
	EXPECT_EQ("26x^5", p.ToString());
}

TEST(Polinom, can_integrate_polinom)
{
	Polinom p(6, "36x^5");
	p = p.Integration("x");
	EXPECT_EQ("6x^6", p.ToString());
}

TEST(Polinom, can_differentiate_polinom)
{
	Polinom p(6, "6x^6");
	p = p.Differentiation("x");
	EXPECT_EQ("36x^5", p.ToString());
}

TEST(List, can_calulate_polinom)
{
	Polinom p(6, "6x^6-y^2");
	std::map<std::string, double> values;
	values.emplace("x", 1);
	values.emplace("y", 2);
	EXPECT_EQ(2, p.Calculation(values));
}