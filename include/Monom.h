#ifndef MONOM_H
#define MONOM_H

#include <vector>
#include <string>
#include <map>

class Monom
{
	int key;
	double coefficient;
	std::map<std::string, int> variables;
public:
	Monom(double _key, double _koeff, std::map<std::string, int> _variables);
	Monom(const Monom&) = default;
	Monom& operator=(const Monom& m);
	bool operator<(const Monom& new_monom);
	bool operator>(const Monom& new_monom);
	bool operator==(const Monom& new_monom);
	void operator+=(const Monom& new_monom);
	void operator*=(int num);
	void operator*=(const Monom& new_monom);
	Monom Differentiation(int p, std::string variable);
	Monom Integration(int p, std::string variable, int degree);
	bool is_empty();
	double Calculation(int p, const std::map<std::string, double>& values);
	std::string ToString(int p);
};

Monom operator*(const Monom& m1, const Monom& m2);
Monom operator+(const Monom& m1, const Monom& m2);

#endif // !MONOM_H
