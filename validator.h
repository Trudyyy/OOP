#pragma once
#include <string>
#include "masina.h"
#include <vector>

using namespace std;

class ValidateException {
	vector<string> mesaje;
public:
	ValidateException(const vector<string>& errors) :mesaje{errors}{}

	friend ostream& operator<<(ostream& out, const ValidateException& ex);
};

ostream& operator<<(ostream& out, const ValidateException& ex);

class CarValidator {
public:
	void validate(const Car& c);
};