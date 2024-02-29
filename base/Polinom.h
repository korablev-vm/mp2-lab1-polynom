#ifndef POLINOM_H
#define POLINOM_H

#include "List.h"
#include "Monom.h"
#include <map>
#include <string>

using namespace std;


class Polinom
{
	List<Monom> expression;
	int max_degree;
	int next_degree;
public:
	Polinom(int p, string exp);
	Polinom(const Polinom& new_exp);
	Polinom& operator=(const Polinom& new_exp);
	double Calculation(map<string, double> values);
	void operator+=(Polinom& new_exp);
	void operator+=(const int& new_exp);
	void operator*=(Polinom& new_exp);
	void operator*=(const int& new_exp);
	Polinom Differentiation(string variable);
	Polinom Integration(string variable);
	int size();
	string ToString();
	vector<string> GetAllVariables();
private:
	bool CheckOfVariable(string variable);
};

Polinom operator+(Polinom& first, Polinom& second);
Polinom operator*(Polinom& first, Polinom& second);

#endif // !POLINOM_H
