#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <map>
#include <vector>
#include <string>
#include <cmath>
#include "Polinom.h"

template <typename T1, typename T2>
class Operations
{
    std::map<std::string, std::vector<int>> operation;

public:
    Operations()
    {
        operation.emplace("(", std::vector<int>{0, 0});
        operation.emplace(")", std::vector<int>{0, 0});
        operation.emplace(",", std::vector<int>{1, 2});
        operation.emplace("+", std::vector<int>{2, 2});
        operation.emplace("-", std::vector<int>{2, 2});
        operation.emplace("*", std::vector<int>{3, 2});
        operation.emplace("Integr", std::vector<int>{4, 2});
        operation.emplace("Diff", std::vector<int>{4, 2});
    };

    bool IfIsOperation(std::string op) const
    {
        return !(operation.find(op) == operation.end());
    };

    int GetPriority(std::string op) const
    {
        return operation.at(op)[0];
    };

    int GetArity(std::string op) const
    {
        return operation.at(op)[1];
    };

    Polinom CalculationAr1(const std::string op, Polinom first, std::string second)
    {
        if (op == "Integr")
        {
            return first.Integration(second);
        }
        if (op == "Diff")
        {
            return first.Differentiation(second);
        }
    }

    T1 CalculationAr2(const std::string& op, T1 first, T2 second)
    {
        if (op == "+")
            return (first + second);
        if (op == "-")
            return (second - first);
        if (op == "*")
            return (first * second);
    };
};

#endif // OPERATIONS_H