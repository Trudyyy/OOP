#pragma once
#include <string>
#include <iostream>

using namespace std;
class CarException {
	std::string msg;
public:
	CarException(const string& m) :msg{ m } {};
	string getMsg()const { return msg; }
};

class Car {
	std::string nrInm;
	std::string Type;
	std::string Prod;
	std::string Mod;
public:
	Car(const string n, const string t, const string p, const string m) :nrInm{ n }, Type{ t }, Prod{ p }, Mod{ m }{};
	Car(const Car &c) : nrInm{ c.getnrInm() }, Type{ c.getType() }, Prod{ c.getProd() }, Mod{ c.getMod() }{cout << 1; };

	string getnrInm()const noexcept{
		return nrInm;
	}

	string getType()const {
		return Type;
	}

	string getProd()const {
		return Prod;
	}

	string getMod()const {
		return Mod;
	}
	void setNrInm(string n) {
		this->nrInm = n;
	}
	void setProd(string p) {
		this->Prod = p;
	}
	void setType(string t)
	{
		this->Type = t;
	}
	void setMod(string m)
	{
		this->Mod = m;
	}
};
/*comparare dupa tip
returneaza 1 daca c1.tip e mai mic decat c2.tip*/
bool cmpType(const Car& c1, const Car& c2);

/*comparare dupa tip
returneaza 1 daca c1.nrInm e mai mic decat c2.nrInm*/
bool cmpnrInm(const Car& c1, const Car& c2)noexcept;

/*comparare dupa tip
returneaza 1 daca c1.Prod e mai mic decat c2.Prod,ia in caz de egaltate,c1.Mod mai mic decat c2.Mod*/
bool cmpProAndMod(const Car& c1, const Car& c2);