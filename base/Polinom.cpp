#include "Polinom.h"

map<string, int> all_variables;

Polinom::Polinom(int p, string exp)
{
	if ((p > 50) || (p < 0))
		throw "Incorrect max degree";
	int coeff;
	string variable;
	string str;
	int key;
	map<string, int> var;
	max_degree = p * 2;
	next_degree = 0;
	for (int i = 0; i < exp.size(); )
	{
		coeff = 1;
		str = "";
		key = 0;
		var.clear();
		if (exp[i] == '-')
		{
			coeff *= -1;
			i++;
		}
		if (exp[i] == '+')
			i++;
		while ((i < exp.size()) && ((isdigit(exp[i]) || (exp[i] == '.'))))
			str += exp[i++];
		if (str != "")
			coeff *= stoi(str);
		while ((i < exp.size()) && (exp[i] != '+') && (exp[i] != '-'))
		{
			variable = "";
			str = "";
			while ((i < exp.size()) && (exp[i] != '^') && (exp[i] != '+') && (exp[i] != '-'))
				variable += exp[i++];
			i++;
			if (CheckOfVariable(variable))
			{
				var.emplace(variable, all_variables[variable]);
				while ((i < exp.size()) && (isdigit(exp[i])))
					str += exp[i++];
			}
			else throw "Incorrect variable";
			if (str != "")
			{
				if (stoi(str) > p)
					throw "Incorrect degree";
				key += stoi(str) * pow(max_degree, all_variables[variable]);
			}
			else
				key += pow(max_degree, all_variables[variable]);
		}
		if (coeff != 0)
			expression.insertInOrder(Monom(key, coeff, var));
	}
}

Polinom::Polinom(const Polinom& new_exp)
{
	this->expression = new_exp.expression;
	this->max_degree = new_exp.max_degree;
	this->next_degree = new_exp.next_degree;
}

Polinom& Polinom::operator=(const Polinom& new_exp)
{
	this->expression = new_exp.expression;
	this->max_degree = new_exp.max_degree;
	this->next_degree = new_exp.next_degree;
	return *this;
}

double Polinom::Calculation(map<string, double> values)
{
	double result = 0.0;
	for (int i = 0; i < expression.size(); i++)
		result += expression[i].Calculation(max_degree, values);
	return result;
}

void Polinom::operator+=(Polinom& new_exp)
{
	this->next_degree = max(this->next_degree, new_exp.next_degree);
	int i = 0, j = 0;
	if ((i < this->expression.size()) && (this->expression[0].is_empty()))
		this->expression.erase(i);
	while ((i < this->expression.size()) && (j < new_exp.expression.size()))
	{
		if (this->expression[i] < new_exp.expression[j])
			i++;
		else if (this->expression[i] > new_exp.expression[j])
		{
			this->expression.insertInOrder(new_exp.expression[j]);
			j++;
		}
		else
		{
			this->expression[i] += new_exp.expression[j];
			j++;
		}
		if ((i < this->expression.size()) && (this->expression[i].is_empty()))
			this->expression.erase(i);
	}
	while (j < new_exp.expression.size())
	{
		this->expression.insertInOrder(new_exp.expression[j]);
		j++;
	}
	return;
}

void Polinom::operator+=(const int& new_exp)
{
	Polinom m(2, to_string(new_exp));
	*this += m;
}

void Polinom::operator*=(Polinom& new_exp)
{
	this->next_degree = max(this->next_degree, new_exp.next_degree);
	List<Monom> new_list;
	for (int i = 0; i < this->expression.size(); i++)
		for (int j = 0; j < new_exp.expression.size(); j++)
			new_list.insertInOrder(this->expression[i] * new_exp.expression[j]);
	this->expression = new_list;
	return;
}

void Polinom::operator*=(const int& new_exp)
{
	Polinom m(2, to_string(new_exp));
	*this *= m;
}

Polinom Polinom::Differentiation(string variable)
{
	Polinom diff_polinom(*this);
	for (int i = 0; i < diff_polinom.size();)
	{
		diff_polinom.expression[i].Differentiation(max_degree, variable);
		if (diff_polinom.expression[i].is_empty())
			diff_polinom.expression.erase(i);
		else i++;
	}
	return diff_polinom;
}

Polinom Polinom::Integration(string variable)
{
	Polinom integr_polinom(*this);
	for (int i = 0; i < integr_polinom.size(); i++)
		integr_polinom.expression[i].Integration(max_degree, variable, all_variables[variable]);
	return integr_polinom;
}

int Polinom::size()
{
	return expression.size();
}

string Polinom::ToString()
{
	string str = "";
	for (int i = 0; i < this->size(); i++)
		str += this->expression[i].ToString(max_degree);
	if (str == "")
		str += '0';
	if (str[0] == '+')
		str.erase(0, 1);
	return str;
}

vector<string> Polinom::GetAllVariables()
{
	vector<string> res;
	for (auto it = all_variables.begin(); it != all_variables.end(); it++)
		res.push_back(it->first);
	return res;
}

bool Polinom::CheckOfVariable(string variable)
{
	if ((((variable.find_first_of("0123456789") > variable.find_last_not_of("0123456789"))
		&& (variable.find_first_of(".,<>?/|!@#$&={}[]:;\"'") == string::npos))))
	{
		if (all_variables.count(variable) == 0)
		{
			all_variables.emplace(variable, next_degree);
			next_degree++;
		}
		return true;
	}
	return false;
}

Polinom operator+(Polinom& first, Polinom& second)
{
	Polinom res(first);
	res += second;
	return res;
}

Polinom operator*(Polinom& first, Polinom& second)
{
	Polinom res(first);
	res *= second;
	return res;
}