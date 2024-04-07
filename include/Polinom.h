#ifndef POLINOM_H
#define POLINOM_H

#include "List.h"
#include "Monom.h"
#include <map>
#include <string>
#include <sstream>


class Polinom
{
	List<Monom> expression;
	int max_degree;
public:
	Polinom(std::string exp = "", int p = 25);
	Polinom(const Polinom& new_exp);
	Polinom(const Polinom* new_exp);
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
	friend std::ostream& operator<<(std::ostream& ostr, const Polinom& exp);
private:
	bool CheckOfVariable(std::string variable);
};

Polinom operator+(Polinom& first, Polinom& second);
Polinom operator-(Polinom& first, Polinom& second);
Polinom operator*(Polinom& first, Polinom& second);

#endif // !POLINOM_H
