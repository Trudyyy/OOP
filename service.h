#pragma once
#include "masina.h"
#include "masiniRepo.h"
#include <string>
#include <vector>
#include <functional>
#include "validator.h"

using namespace std;

class StorageException : public std::exception
{
	std::string msg;
public:
	StorageException(std::string m) {
		msg = m;
	}
	string getMsg() const { return msg; }
};

typedef bool(*F)(const Car&, const Car&);

class Service {
	CarRepo& repo;
	CarValidator& val;
	vector<Car> generalSort(F maiMic)const;
	vector<Car> filtreaza(function<bool(const Car&)>fct)const;
public:
	Service(CarRepo& repo,CarValidator& val)noexcept:repo{repo},val{val}{}
	Service(const Service& ot) = delete;
	const vector<Car> getAll()const {
		return repo.getAll();
	}
	/*adauga o noua masina
	arunca exceptie daca nu se poate salva sau nu e valid*/
	void addCar(string nrInm, const string Type, const string Prod, const string Mod);
	/*sterge masina care are un anumit numar de inmatriculare
	arunca exceptie daca nu exista o asemenea masina*/
	void delCar(string nrInm);
	/*modifica tipul,producatorul si modelul unei masini
	arunca exceptie daca nu exista o masina cu acel numar de inmatriculare*/
	void modif(string nrInm, string Type, string Prod, string Mod);
	/*returneaza masina care are un anume numar de inmatriculare
	arunca exceptie daca nu exista o asemenea masina*/
	Car cauta(string nrInm);
	/*sorteaza dupa numarul de inmatriculare*/
	vector<Car>sortByNrInm()const;
	/*sorteaza dupa tip*/
	vector<Car>sortByType()const;
	/*sorteaza dupa producator si model*/
	vector<Car>sortByProdAndMod()const;
	/*filtreaza dupa producator*/
	vector<Car>filterByProd(const string Prod)const;
	/*filtreaza dupa tip*/
	vector<Car>filterByType(const string Type)const;
};

void testService();