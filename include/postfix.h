#ifndef POSTFIX_H
#define POSTFIX_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <typeinfo>
#include "stack.h"
#include "Operations.h"
#include "Polinom.h"
#include "TableManager.h"

template <typename T, typename TKey/*, typename TValue*/>
class TPostfix
{
	std::vector<std::string> infix;
	std::string infix_str;
	std::vector<std::string> postfix;
	std::string postfix_str;
	std::map<std::string, double> operands;
	std::map<std::string, double> constants;
	TableManager<TKey, Polinom/*TValue*/>* manager;
public:
	TPostfix(std::string str, TableManager<TKey, /*TValue*/Polinom>* _manager = nullptr);
	~TPostfix();
	std::string GetInfix() { return infix_str; }
	std::string GetPostfix() { return postfix_str; }
private:
	void ToInfix();
	void CheckOfExpression();
	void ToPostfix();

public:
	std::vector<std::string> GetAllVariables();
	double Calculate(std::vector<double> values_of_operands = {}); //Зависит от доступа к полиномам по именам
};

template <typename T, typename TKey/*, typename TValue*/>
TPostfix<T, TKey/*, TValue*/>::TPostfix(std::string str, TableManager<TKey, /*TValue*/Polinom>* _manager) //: manager(_manager)
{
	manager = _manager;
	for (size_t i = 0; i < str.size(); i++)
		if (str[i] == ' ')
			str.erase(i, 1);
	infix_str = str;
	ToInfix();
	CheckOfExpression();
	ToPostfix();
}

template <typename T, typename TKey/*, typename TValue*/>
TPostfix<T, TKey/*, TValue*/>::~TPostfix()
{
	manager = nullptr;
}

template <typename T, typename TKey/*, typename TValue*/>
void TPostfix<T, TKey/*, TValue*/>::ToInfix()
{
	std::string element, operand;
	Operations<T, T> op;
	for (size_t i = 0; i < infix_str.size(); i++)
	{
		element = infix_str[i];
		if (!op.IfIsOperation(element))
			operand += element;
		else
		{
			if (operand != "")
			{
				infix.push_back(operand);
				operand = "";
			}
			if ((element == "-") && ((infix.size() == 0) || (infix[infix.size() - 1] == "(")))
			{
				infix.push_back("0");
			}
			infix.push_back(element);
		}
	}
	if (operand != "")
		infix.push_back(operand);
}

template <typename T, typename TKey/*, typename TValue*/>
void TPostfix<T, TKey/*, TValue*/>::CheckOfExpression()
{
	int count_of_left = 0, count_of_right = 0;
	Operations<T, T> op;
	if (op.IfIsOperation(infix[0]))
	{
		if (infix[0] == "(")
			count_of_left++;
		if (infix[0] == ")")
			throw "Expression is wrong, check operations";
		if ((op.GetArity(infix[0]) > 1) && (infix[0] != "-"))
			throw "Expression is wrong, check operations";
	}
	else
	{
		if (!((infix[0].find_first_not_of("0123456789,") == std::string::npos)
			|| ((infix[0].find_first_of("0123456789") > infix[0].find_last_not_of("0123456789"))
				&& (infix[0].find_first_of(".,<>?/|!@#$&={}[]:;\"'") == std::string::npos))))
			throw "Expression is wrong, check operands";
	}
	if ((op.IfIsOperation(infix[infix.size() - 1])) && (infix[infix.size() - 1] != ")"))
		throw "Expression is wrong, check operations";
	for (size_t i = 1; i < infix.size(); i++)
	{
		if (op.IfIsOperation(infix[i]))
		{
			if (infix[i] == "(")
				count_of_left++;
			if (infix[i] == ")")
				count_of_right++;
			if ((op.IfIsOperation(infix[i - 1]))
				&& ((op.GetArity(infix[i]) > 1) && (infix[i] != "-") && (infix[i - 1] != ")")
					|| (infix[i] == "-") && (op.GetArity(infix[i - 1]) > 0)
					|| (infix[i - 1] == ")") && (op.GetArity(infix[i]) == 1)))
				throw "Expression is wrong, check operations";
			else if (!op.IfIsOperation(infix[i - 1]) && (op.GetArity(infix[i]) < 2) && (infix[i] != ")"))
				throw "Expression is wrong, check operations";
		}
		else
		{
			if ((!op.IfIsOperation(infix[i - 1])) || (infix[i - 1] == ")"))
				throw "Expression is wrong, check operands";
			if (!((infix[i].find_first_not_of("0123456789,") == std::string::npos)
				|| ((infix[i].find_first_of("0123456789") > infix[i].find_last_not_of("0123456789"))
					&& (infix[i].find_first_of(".,<>?/|!@#$&={}[]:;\"'") == std::string::npos))))
				throw "Expression is wrong, check operands";
		}
	}
	if (count_of_left != count_of_right)
		throw "Expression is wrong, check brackets";
}

template <typename T, typename TKey/*, typename TValue*/>
void TPostfix<T, TKey/*, TValue*/>::ToPostfix()
{
	TStack<std::string> st(infix.size());
	Operations<T, T> op;
	for (size_t i = 0; i < infix.size(); i++)
	{
		if (op.IfIsOperation(infix[i]))
		{
			if (infix[i] == "(")
				st.push(infix[i]);
			else if (infix[i] == ")")
			{
				while (st.getTop() != "(")
					postfix.push_back(st.pop());
				st.pop();
			}
			else
			{
				while (!((st.empty()) || (op.GetPriority(infix[i]) > op.GetPriority(st.getTop()))))
					postfix.push_back(st.pop());
				st.push(infix[i]);
			}
		}
		else
		{
			if ((infix[i].find_first_not_of("0123456789,") == std::string::npos) && (constants.count(infix[i]) == 0))
				constants.emplace(infix[i], stod(infix[i]));
			else if ((infix[i].find_first_not_of("0123456789,") != std::string::npos) && (operands.count(infix[i]) == 0))
				operands.emplace(infix[i], 0.0);
			postfix.push_back(infix[i]);
		}
	}
	while (!st.empty())
		postfix.push_back(st.pop());
	for (std::string element : postfix)
	{
		postfix_str += element;
	}
}

template <typename T, typename TKey/*, typename TValue*/>
double TPostfix<T, TKey/*, TValue*/>::Calculate(std::vector<double> values)
{
	Operations<double, double> op;
	TStack<double> st;
	TKey key;
	std::map<std::string, double> values_of_variables;
	if (manager != nullptr)
	{
		std::vector<std::string> variables = GetAllVariables();
		for (int i = 0; i < variables.size(); i++)
			values_of_variables.emplace(variables[i], values[i]);
		/*TValue**/Polinom* tmp;
		for (auto it = operands.begin(); it != operands.end(); it++)
		{
			key = it->first;

			tmp = manager->find(key);
			if (tmp != nullptr)
				it->second = tmp->Calculation(values_of_variables);
			else
				it->second = values_of_variables[key];
		}
	}
	else
	{
		int i = 0;
		for (auto it = operands.begin(); it != operands.end(); it++, i++)
		{
			key = it->first;
			it->second = values[i];
		}
	}

	for (const std::string& element : postfix)
	{
		if (!op.IfIsOperation(element))
		{
			if (operands.count(element) > 0)
				st.push(operands.at(element));
			else
				st.push(constants.at(element));
		}
		else
		{
				double first = st.pop();
				st.push(op.Calculation(element, first, st.pop()));
		}
	}
	double res = st.pop();
	return res;
}

template <typename T, typename TKey/*, typename TValue*/>
std::vector<std::string> TPostfix<T, TKey/*, TValue*/>::GetAllVariables()
{
	Polinom* tmp;
	return tmp->GetAllVariables();
}

#endif // POSTFIX_H
