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

template <typename T, typename TKey>
class TPostfix
{
	std::vector<std::string> infix;
	std::string infix_str;
	std::vector<std::string> postfix;
	std::string postfix_str;
	std::map<std::string, double> operands;
	std::map<std::string, double> constants;
	TableManager<TKey, Polinom> manager;
public:
	TPostfix(std::string str, const TableManager<TKey, Polinom>& _manager);
	std::string GetInfix() { return infix_str; }
	std::string GetPostfix() { return postfix_str; }
private:
	void ToInfix();
	void CheckOfExpression();
	void ToPostfix();

public:
	std::vector<std::string> GetAllVariables();
	Polinom CreateNewPolinom();
	double Calculate(std::vector<double> values_of_operands = {});
};

template <typename T, typename TKey>
TPostfix<T, TKey>::TPostfix(std::string str, const TableManager<TKey, Polinom>& _manager)
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

template <typename T, typename TKey>
void TPostfix<T, TKey>::ToInfix()
{
	std::string element, operand;
	Operations<T, T> op;
	for (size_t i = 0; i < infix_str.size(); i++)
	{
		element = infix_str[i];
		if (element == " ");
		else if (!op.IfIsOperation(element))
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

template <typename T, typename TKey>
void TPostfix<T, TKey>::CheckOfExpression()
{
	int count_of_left = 0, count_of_right = 0;
	Operations<T, T> op;
	if (op.IfIsOperation(infix[0]))
	{
		if (infix[0] == "(")
			count_of_left++;
		if (infix[0] == ")")
			throw "Expression is wrong, check operations";
		if ((op.GetArity(infix[0]) > 1) && (infix[0] != "-") && (infix[0] == "Diff") && (infix[0] == "Integr"))
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
				&& (op.GetArity(infix[i]) > 1) && (infix[i] != "-") && (infix[i] != "Diff") && (infix[i] != "Integr") 
				&& (infix[i - 1] != ")"))
				throw "Expression is wrong, check operations";
				if ((infix[i] == "-") && (op.GetArity(infix[i - 1]) > 0))
					throw "Expression is wrong, check operations";
				if ((infix[i - 1] == ")") && ((op.GetArity(infix[i]) == 1) || (infix[i] == "Diff") || (infix[i] == "Integr")))
				throw "Expression is wrong, check operations";
				else if (!op.IfIsOperation(infix[i - 1]) && ((op.GetArity(infix[i]) < 2) && (infix[i] != ")")
					|| (infix[i] == "Diff") || (infix[i] == "Integr")))
					throw "Expression is wrong, check operations";
		}
		else
		{
			if ((!op.IfIsOperation(infix[i - 1])) && ((i > 1) && ((infix[i - 2] != "Diff") || (infix[i - 2] != "Integr"))) 
				|| (infix[i - 1] == ")"))
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

template <typename T, typename TKey>
void TPostfix<T, TKey>::ToPostfix()
{
	TStack<std::string> st(infix.size());
	Operations<T, T> op;
	for (size_t i = 0; i < infix.size(); i++)
	{
		if (op.IfIsOperation(infix[i]))
		{
			if ((infix[i] == "("))
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
				if (infix[i] != ",")
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

template <typename T, typename TKey>
double TPostfix<T, TKey>::Calculate(std::vector<double> values)
{
	Polinom res_polinom = CreateNewPolinom();
	std::map<std::string, double> values_of_variables;
	std::vector<std::string> variables = GetAllVariables();
	for (int i = 0; i < variables.size(); i++)
		values_of_variables.emplace(variables[i], values[i]);
	return res_polinom.Calculation(values_of_variables);
}

template <typename T, typename TKey>
std::vector<std::string> TPostfix<T, TKey>::GetAllVariables()
{
	Polinom tmp;
	return tmp.GetAllVariables();
}
template<typename T, typename TKey>
Polinom TPostfix<T, TKey>::CreateNewPolinom()
{
	Operations<Polinom, Polinom> op;
	TStack<Polinom> st;
	std::vector<std::string> variables = GetAllVariables();
	for (const std::string& element : postfix)
	{
		if (!op.IfIsOperation(element))
		{
			if ((operands.count(element) > 0) && (std::find(begin(variables), end(variables), element) == end(variables)))
			{
				if (manager.find(element) == nullptr)
					throw std::out_of_range("Не надено полинома с именем " + element);
				Polinom pol(manager.find(element));
				st.push(pol);
			}
			else
				st.push(Polinom(element));
		}
		else
		{
			if (element.size() > 2)
			{
				std::string variable_in_polinom = st.pop().ToString();
				std::string variable = "";
				for (int i = variable_in_polinom.find_first_not_of("0123456789,"); variable_in_polinom[i] != '^'; i++)
					variable += variable_in_polinom[i];
				Polinom val1 = st.pop();
				st.push(op.CalculationAr1(element, val1, variable));
			}
			else
			{
				Polinom val1 = st.pop();
				Polinom val2 = st.pop();
				Polinom res = op.CalculationAr2(element, val1, val2);
				st.push(res);
			}
		}
	}
	return st.pop();
}

#endif // POSTFIX_H
