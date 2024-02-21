#ifndef __OPERATIONS_H__
#define __OPERATIONS_H__

#include <map>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

template <class T>
class Operations
{
	map<string, vector<int>> operation;

public:
	Operations()
	{
		operation.emplace("(", vector<int>{ 0, 0 });
		operation.emplace(")", vector<int>{ 0, 0 });
		operation.emplace("+", vector<int>{ 1, 2 });
		operation.emplace("-", vector<int>{ 1, 2 });
		operation.emplace("*", vector<int>{ 2, 2 });
		operation.emplace("^", vector<int>{ 3, 2 });
	};

	bool IfIsOperation(string op) const
	{
		return(!(operation.find(op) == operation.end()));
	};

	int GetPriority(string op) const
	{
		return operation.at(op)[0];
	};

	int GetArity(string op) const
	{
		return operation.at(op)[1];
	};

	T Calculation(const string& op, T first, int second)
	{
			T result(first);
			for (int i = 0; i < second; i++)
				result += first;
			return result;
	};

	T Calculation(const string& op, T first, T second)
	{
		if (op == "+")
			return (first + second);
		if (op == "-")
			return (second - first);
		if (op == "*")
			return (first * second);
		//return 0;
	};
};

#endif