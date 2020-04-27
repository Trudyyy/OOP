#include "service.h"
#include <functional>
#include "Masina.h"
#include <vector>
#include <algorithm>
#include <assert.h>

using namespace std;

vector<Car>Service::generalSort(F maiMic)const {
	vector<Car> v{ repo.getAll() };
	sort(v.begin(), v.end(), maiMic);
	return v;
}
/*adauga Car
arunca exceptie daca nu se poate salva sau nu e valida*/
void Service::addCar(string nrInm, string Type, string Prod, string Mod) {
	Car c{ nrInm,Type,Prod,Mod };
	val.validate(c);
	repo.store(c);
}
/*sterge Car
arunca exceptie daca nu exista*/
void Service::delCar(string nrInm) {
	repo.del(nrInm);
}
/*modifica Car
arunca exceptie daca nu exista*/
void Service::modif(string nrInm, string Type, string Prod, string Mod) {
	repo.change(nrInm, Type, Prod, Mod);
}
/*cauta Car
arunca exceptie daca nu exista*/
Car Service::cauta(string nrInm) {
	try {
		Car c = repo.find(nrInm);
		return c;
	}
	catch (CarRepoException&) {
		throw CarRepoException("Nu exista o masina cu numarul de inmatriculare:" + nrInm);
	}
}
//sorteaza dupa numar de inmatriculare
vector<Car> Service::sortByNrInm()const {
	return generalSort(cmpnrInm);
}
//sorteaza dupa tip
vector<Car> Service::sortByType()const {
	return generalSort(cmpType);
}
//sorteaza dupa producator si model
vector<Car> Service::sortByProdAndMod()const {
	return generalSort(cmpProAndMod);
}

vector<Car> Service::filtreaza(function<bool(const Car&)>fct)const {
	vector<Car> rez;
	for (const auto& car : repo.getAll()) {
		if (fct(car)) {
			rez.push_back(car);
		}
	}
	return rez;
}

vector<Car> Service::filterByProd(const string Prod)const {
	return filtreaza([Prod](const Car&c) {
		return c.getProd() < Prod;
	});
}

vector<Car> Service::filterByType(const string Type)const {
	return filtreaza([Type](const Car& c){
		return c.getType() < Type;
	});
}

void testAdaugaCtr() {
	CarRepo rep;
	CarValidator val;
	Service crt{ rep,val };
	crt.addCar("aa11aaa", "a", "a", "a");
	crt.modif("aa11aaa", "b", "b", "b");
	assert(crt.cauta("aa11aaa").getMod() == "b");
	crt.modif("aa11aaa", "a", "a", "a");
	assert(crt.getAll().size() == 1);
	try {
		crt.addCar(""," "," "," ");
		assert(false);
	}
	catch (const ValidateException& ve) {
		cout << ve;
		assert(true);
	}
	try {
		crt.addCar("aa11aaa", "a", "a", "a");
		assert(false);
	}
	catch (CarRepoException&) {
		assert(true);
	}
	assert(crt.cauta("aa11aaa").getMod() == "a");
	try {
		crt.cauta("bb22bbb");
		assert(false);
	}
	catch (CarRepoException&) {
		assert(true);
	}
	crt.delCar("aa11aaa");
	assert(crt.getAll().size() == 0);
}

void testFiltrare() {
	CarRepo rep;
	CarValidator val;
	Service crt{ rep,val };
	crt.addCar("ff77fff", "a", "b", "b");
	crt.addCar("aa22aaa", "a", "c", "b");
	crt.addCar("cc33ccc", "b", "b", "b");
	crt.addCar("dd44ddd", "b", "b", "b");
	assert(crt.filterByType("a").size() == 0);
	assert(crt.filterByType("b").size() == 2);
	assert(crt.filterByProd("g").size() == 4);
	assert(crt.filterByProd("c").size() == 3);
}

void testSortare() {
	CarRepo rep;
	CarValidator val;
	Service crt{ rep,val };
	crt.addCar("ff77fff", "a", "b", "q");
	crt.addCar("aa22aaa", "c", "c", "c");
	crt.addCar("cc33ccc", "b", "b", "p");
	crt.addCar("dd44ddd", "d", "d", "d");
	auto c = crt.sortByNrInm().at(2);
	assert(c.getMod() == "d");
	c = crt.sortByType().at(2);
	assert(c.getnrInm() == "aa22aaa");
	c = crt.sortByProdAndMod().at(0);
	assert(c.getMod() == "p");
}

void testService(){
	testAdaugaCtr();
	testFiltrare();
	testSortare();
}