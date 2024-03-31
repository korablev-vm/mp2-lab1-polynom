#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <map>
#include <vector>
#include <string>
#include <cmath>

template <typename T1, typename T2>
class Operations
{
    std::map<std::string, std::vector<int>> operation;

public:
    Operations()
    {
        operation.emplace("(", std::vector<int>{0, 0});
        operation.emplace(")", std::vector<int>{0, 0});
        operation.emplace("+", std::vector<int>{1, 2});
        operation.emplace("-", std::vector<int>{1, 2});
        operation.emplace("*", std::vector<int>{2, 2});
        operation.emplace("/", std::vector<int>{2, 2});
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

    T1 Calculation(const std::string& op, T1 first, T2 second)
    {
        if (op == "+")
            return (first + second);
        if (op == "-")
            return (second - first);
        if (op == "*")
            return (first * second);
        if (op == "/")
        {
            if (second == 0)
                throw std::runtime_error("Division by zero.");
            return (second / first);
        }
    };
};

#endif // OPERATIONS_H