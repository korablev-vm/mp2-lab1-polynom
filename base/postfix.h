#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "stack.h"
#include "Operations.h"
#include "Polinom.h"

using namespace std;

template <class T>
class TPostfix
{
	vector<string> infix;
	string infix_str;
	vector<string> postfix;
	string postfix_str;
	vector<string> operands;
	map<string, double> constants;
public:
	TPostfix(string str);
	string GetInfix() { return infix_str; }
	string GetPostfix() { return postfix_str; }
private:
	void ToInfix();
	void CheckOfExpression();
	void ToPostfix();

public:
	//double Calculate(vector<double> values_or_operands = {}); //Зависит от доступа к полиномам по именам
};

template <class T>
TPostfix<T>::TPostfix(string str)
{
	for (size_t i = 0; i < str.size(); i++)
		if (str[i] == ' ')
			str.erase(i, 1);
	infix_str = str;
	ToInfix();
	CheckOfExpression();
	ToPostfix();
}

template <class T>
void TPostfix<T>::ToInfix()
{
	string element, operand;
	Operations<T> op;
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

template <class T>
void TPostfix<T>::CheckOfExpression()
{
	int count_of_left = 0, count_of_right = 0;
	Operations<T> op;
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
		if (!((infix[0].find_first_not_of("0123456789,") == string::npos)
			|| ((infix[0].find_first_of("0123456789") > infix[0].find_last_not_of("0123456789"))
				&& (infix[0].find_first_of(".,<>?/|!@#$&={}[]:;\"'") == string::npos))))
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
			if (!((infix[i].find_first_not_of("0123456789,") == string::npos)
				|| ((infix[i].find_first_of("0123456789") > infix[i].find_last_not_of("0123456789"))
					&& (infix[i].find_first_of(".,<>?/|!@#$&={}[]:;\"'") == string::npos))))
				throw "Expression is wrong, check operands";
		}
	}
	if (count_of_left != count_of_right)
		throw "Expression is wrong, check brackets";
}

template <class T>
void TPostfix<T>::ToPostfix()
{
	TStack<string> st(infix.size());
	Operations<T> op;
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
			if ((infix[i].find_first_not_of("0123456789,") == string::npos) && (constants.count(infix[i]) == 0))
				constants.emplace(infix[i], stod(infix[i]));
			else if ((infix[i].find_first_not_of("0123456789,") != string::npos) && (operands.count(infix[i]) == 0))
				operands.push_back(infix[i]);
			postfix.push_back(infix[i]);
		}
	}
	while (!st.empty())
		postfix.push_back(st.pop());
	for (string element : postfix)
	{
		postfix_str += element;
	}
}

//template <class T>
//double TPostfix<T>::Calculate(vector<double> values_of_operands) {}

#endif