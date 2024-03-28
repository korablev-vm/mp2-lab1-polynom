#include "Monom.h"
#include <gtest.h>

// Проверка возможности создания монома
TEST(Monom, can_create_monom) {
    std::map<std::string, int> vars = { {"x", 2}, {"y", 1} };
    ASSERT_NO_THROW(Monom m(123, 3.5, vars));
}

// Проверка возможности создания копии монома
TEST(Monom, can_create_copy) {
    std::map<std::string, int> vars = { {"x", 2}, {"y", 1} };
    Monom m(123, 3.5, vars);
    ASSERT_NO_THROW(Monom copy = m);
}

// Проверка возможности преобразования монома в строку
TEST(Monom, can_invert_monom_to_string) {
    std::map<std::string, int> vars = { {"x", 2}, {"y", 1} };
    Monom m(123, 3.5, vars);
    ASSERT_NO_THROW(std::string str = m.ToString(10));
}

// Проверка возможности присваивания одного монома другому
TEST(Monom, can_assign_one_monom_to_another) {
    std::map<std::string, int> vars = { {"x", 2}, {"y", 1} };
    Monom m1(123, 3.5, vars);
    Monom m2(456, 2.0, vars);
    ASSERT_NO_THROW(m1 = m2);
}

// Проверка возможности сложения двух мономов
TEST(Monom, can_add_one_monom_to_another) {
    std::map<std::string, int> vars = { {"x", 2}, {"y", 1} };
    Monom m1(123, 3.5, vars);
    Monom m2(456, 2.0, vars);
    ASSERT_NO_THROW(m1 += m2);
}

// Проверка возможности умножения двух мономов
TEST(Monom, can_multiply_one_monom_to_another) {
    std::map<std::string, int> vars1 = { {"x", 2}, {"y", 1} };
    std::map<std::string, int> vars2 = { {"x", 1}, {"z", 2} };
    Monom m1(123, 3.5, vars1);
    Monom m2(456, 2.0, vars2);
    ASSERT_NO_THROW(m1 *= m2);
}

// Проверка возможности интегрирования монома
TEST(Monom, can_integrate_monom) {
    std::map<std::string, int> vars = { {"x", 2}, {"y", 1} };
    Monom m(123, 3.5, vars);
    ASSERT_NO_THROW(m.Integration(10, "x", 3));
}

// Проверка возможности дифференцирования монома
TEST(Monom, can_differentiate_monom) {
    std::map<std::string, int> vars = { {"x", 2}, {"y", 1} };
    Monom m(123, 3.5, vars);
    ASSERT_NO_THROW(m.Differentiation(10, "x"));
}

// Проверка возможности вычисления значения монома
TEST(Monom, can_calculate_monom) {
    std::map<std::string, int> vars = { {"x", 2}, {"y", 1} };
    Monom m(123, 3.5, vars);
    std::map<std::string, double> values = { {"x", 2.0}, {"y", 3.0} };
    ASSERT_NO_THROW(m.Calculation(10, values));
}

// Проверка возможности сравнения мономов как подобных членов
TEST(Monom, can_compare_monoms_as_similar_terms) {
    std::map<std::string, int> vars1 = { {"x", 2}, {"y", 1} };
    std::map<std::string, int> vars2 = { {"x", 2}, {"y", 1} };
    Monom m1(123, 3.5, vars1);
    Monom m2(123, 3.5, vars2);
    ASSERT_TRUE(m1 == m2);
}