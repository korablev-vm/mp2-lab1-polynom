#ifndef MONOM_H
#define MONOM_H

#include <vector>
#include <string>
#include <map>

using namespace std;

class Monom
{
	int key;
	double coefficient;
	map<string, int> variables;
public:
	Monom(double _key, double _koeff, map<string, int> _variables);
	Monom(const Monom&) = default;
	Monom& operator=(const Monom& m);
	bool operator<(const Monom& new_monom);
	bool operator>(const Monom& new_monom);
	bool operator==(const Monom& new_monom);
	void operator+=(const Monom& new_monom);
	void operator*=(int num);
	void operator*=(const Monom& new_monom);
	Monom Differentiation(int p, string variable);
	Monom Integration(int p, string variable, int degree);
	bool is_empty();
	double Calculation(int p, const map<string, double>& values);
	string ToString(int p);
};

Monom operator*(const Monom& m1, const Monom& m2);
Monom operator+(const Monom& m1, const Monom& m2);

#endif // !MONOM_H
