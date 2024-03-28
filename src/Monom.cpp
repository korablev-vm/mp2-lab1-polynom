#include "Monom.h"
#include <stdexcept>

Monom::Monom(double _key, double _coeff, std::map<std::string, int> _variables)
	: key(_key), coefficient(_coeff), variables(_variables) {}

Monom& Monom::operator=(const Monom& m)
{
	if (!(*this == m))
	{
		this->key = m.key;
		this->coefficient = m.coefficient;
		this->variables = m.variables;
	}
	return *this;
}

bool Monom::operator<(const Monom& new_monom)
{
	return (this->key < new_monom.key);
}

bool Monom::operator>(const Monom& new_monom)
{
	return (this->key > new_monom.key);
}

bool Monom::operator==(const Monom& new_monom)
{
	return (this->key == new_monom.key);
}

void Monom::operator+=(const Monom& new_monom)
{
	if (this->variables != new_monom.variables)
		throw std::invalid_argument("Monoms with different variables cannot be added");

	this->coefficient += new_monom.coefficient;
}

void Monom::operator*=(int num)
{
	this->coefficient *= num;
}

void Monom::operator*=(const Monom& new_monom)
{
	this->coefficient *= new_monom.coefficient;
	this->key += new_monom.key;
	this->variables.insert(new_monom.variables.begin(), new_monom.variables.end());
}

Monom Monom::Differentiation(int p, std::string variable)
{
	if (this->variables.count(variable) == 0)
	{
		this->coefficient = 0;
		return *this;
	}
	int v = this->key % (int)pow(p, this->variables[variable] + 1) / pow(p, this->variables[variable]);
	this->key -= pow(p, this->variables[variable]);
	this->coefficient *= v;
	if (v == 1)
		this->variables.erase(variable);
	return *this;
}

Monom Monom::Integration(int p, std::string variable, int degree)
{
	if (this->variables.count(variable) == 0)
		this->variables.emplace(variable, degree);
	int v = this->key % (int)pow(p, degree + 1) / pow(p, degree) + 1;
	this->key += pow(p, degree);
	this->coefficient /= v;
	return *this;
}

bool Monom::is_empty()
{
	return (this->coefficient == 0);
}

double Monom::Calculation(int p, const std::map<std::string, double>& values)
{
	double res = this->coefficient;
	for (auto it = this->variables.begin(); it != this->variables.end(); it++)
	{
		auto ss = values.find(it->first);
		res *= pow(ss->second, ((int)(this->key % (int)pow(p, it->second + 1) / pow(p, it->second))));
	}
	return res;
}

std::string Monom::ToString(int p)
{
	std::string str = "";
	if (this->coefficient > 0)
		str += '+';
	if (this->coefficient == (int)this->coefficient)
		str += std::to_string((int)this->coefficient);
	else
		str += std::to_string(this->coefficient);
	for (const auto& s : this->variables)
	{
		str += s.first;
		str += "^" + std::to_string((int)(this->key % (int)pow(p, s.second + 1) / pow(p, s.second)));
	}
	return str;
}

Monom operator+(const Monom& m1, const Monom& m2)
{
	Monom m(m1);
	m += m2;
	return m;
}

Monom operator*(const Monom& m1, const Monom& m2)
{
	Monom m(m1);
	m *= m2;
	return m;
}

