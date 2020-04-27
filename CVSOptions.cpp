#include "CVSOptions.h"
#include "masina.h"
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>
#include <cstdio>
#include <limits.h>
using namespace std;

void adauga_la_spalat(const Car &car)
{
	std::fstream f;
	f.open("file.cvs", std::fstream::app);
	string nrInm, Prod, Mod, Type;
	nrInm = car.getnrInm();
	Prod = car.getProd();
	Type = car.getType();
	Mod = car.getMod();
	f << nrInm << "," << Type << "," << Prod << "," << Mod << endl;
}

void goleste_spalaorie()
{
	std::fstream f;
	f.open("file.cvs", std::fstream::out);
	f.close();
}

void genereaza_lista_spalat(const int numar)
{
	string nrInm, Prod, Mod, Type;
	goleste_spalaorie();
	for (int i = 0; i < numar; i++)
	{
		nrInm = genereaza_nrInm();
		Prod = genereaza_str();
		Mod = genereaza_str();
		Type = genereaza_str();
		Car c{ nrInm,Type,Prod,Mod };
		adauga_la_spalat(c);
	}

}

int numar_masini()
{
	std::fstream f;
	f.open("file.cvs", std::fstream::in);
	int nr = 0;
	string line;
	while (getline(f, line))
		nr++;
	return nr;
}

string genereaza_str()
{
	string str = "qwertyuiopasdfghjklzxcvbnm",rez="";
	unsigned pos = 0, len = 0;
	len = rand() % (25 - 1 + 1) + 25;
	while (rez.size() != len)
	{
		pos = ((rand() % (str.size() - 1)));
		rez += str.substr(pos, 1);
	}
	return rez;
}

string genereaza_nrInm()
{
	string rez="", str = "qwertyuiopasdfghjklzxcvbnm", nr = "1234567890";
	unsigned poz, len = 7;
	for (poz = 0; poz < len; poz++)
	{
		if (poz == 2 || poz == 3)
		{
			rez += nr.substr(poz, 1);
		}
		else
		{
			rez += str.substr(poz, 1);
		}
	}
	return rez;
}