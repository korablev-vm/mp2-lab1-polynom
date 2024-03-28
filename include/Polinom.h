#ifndef POLINOM_H
#define POLINOM_H

#include "List.h"
#include "Monom.h"
#include <map>
#include <string>


class Polinom
{
	List<Monom> expression;
	int max_degree;
	int next_degree;
public:
	Polinom(int p, std::string exp);
	Polinom(const Polinom& new_exp);
	Polinom& operator=(const Polinom& new_exp);
	double Calculation(std::map<std::string, double> values);
	void operator+=(Polinom& new_exp);
	void operator+=(const int& new_exp);
	void operator*=(Polinom& new_exp);
	void operator*=(const int& new_exp);
	Polinom Differentiation(std::string variable);
	Polinom Integration(std::string variable);
	int size();
	std::string ToString();
	std::vector<std::string> GetAllVariables();
private:
	bool CheckOfVariable(std::string variable);
};

Polinom operator+(Polinom& first, Polinom& second);
Polinom operator*(Polinom& first, Polinom& second);

#endif // !POLINOM_H
