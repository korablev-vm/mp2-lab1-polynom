//#ifndef OPERATIONS_H
//#define OPERATIONS_H
//
//#include <map>
//#include <vector>
//#include <string>
//#include <cmath>
//
//template <class T>
//class Operations
//{
//	std::map<std::string, std::vector<int>> operation;
//
//public:
//	Operations()
//	{
//		operation.emplace("(", std::vector<int>{ 0, 0 });
//		operation.emplace(")", std::vector<int>{ 0, 0 });
//		operation.emplace("+", std::vector<int>{ 1, 2 });
//		operation.emplace("-", std::vector<int>{ 1, 2 });
//		operation.emplace("*", std::vector<int>{ 2, 2 });
//		operation.emplace("/", std::vector<int>{ 2, 2 });
//		operation.emplace("^", std::vector<int>{ 3, 2 });
//	};
//
//	bool IfIsOperation(string op) const
//	{
//		return(!(operation.find(op) == operation.end()));
//	};
//
//	int GetPriority(string op) const
//	{
//		return operation.at(op)[0];
//	};
//
//	int GetArity(string op) const
//	{
//		return operation.at(op)[1];
//	};
//
//	T Calculation(const string& op, T first, int second)
//	{
//		T result(first);
//		for (int i = 0; i < second; i++)
//			result += first;
//		return result;
//	};
//
//	T Calculation(const string& op, T first, T second)
//	{
//		if (op == "+")
//			return (first + second);
//		if (op == "-")
//			return (second - first);
//		if (op == "*")
//			return (first * second);
//		if (op == "/")
//		{
//			if (second == 0) throw runtime_error("Division by zero.");
//			return (first / second);
//		}
//		// Добавить исключение или возвращаемое значение по умолчанию для неподдерживаемых операций
//		throw invalid_argument("Unsupported operation: " + op);
//	};
//};
//
//#endif // OPERATIONS_H