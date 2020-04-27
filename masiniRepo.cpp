#include "masiniRepo.h"
#include <fstream>
#include "service.h"
#include "masina.h"
#include "validator.h"
#include <algorithm>
#include <assert.h>

/*adauga un nou Car
arunca exceptie daca nu e valid sau nu se poate salva*/
void CarRepo::store(const Car& c) {
	if (exist(c)) {
		throw CarRepoException("Exista deja o masina cu numarul de inmatriculare:"+c.getnrInm());
	}
	all.push_back(c);
}

/*sterge Car
aruca exceptie daca nu exista o astfel de masina*/
void CarRepo::del(string nrInm) {
	try {
		find(nrInm);
		vector<Car> nou;
		for (const Car& c : all) {
			if (nrInm!= c.getnrInm())
				nou.push_back(c);
		}
		all.clear();
		for (const Car& c : nou) {
			all.push_back(c);
		}
		nou.clear();
	}
	catch (CarRepoException&) {
		throw CarRepoException("Nu exista o masina cu numarul de inmatriculare:" + nrInm);
	}
}

/*schimba Car
arunca exceptie daca nu exista o astefel de masina*/
void CarRepo::change(string nrInm, string Type, string Prod, string Mod) {
	try {
		find(nrInm);
		vector<Car> nou;
		for (const Car& c : all) {
			if (nrInm != c.getnrInm())
				nou.push_back(c);
			else {
				Car schimbare = Car{ nrInm,Type,Prod,Mod };
				nou.push_back(schimbare);
			}
		}
		all.clear();
		for (const Car& c : nou) {
			all.push_back(c);
		}
		nou.clear();
	}
	catch (CarRepoException&) {
		throw CarRepoException("Nu exista o masina cu numarul de inmatriculare:" + nrInm);
	}
}

bool CarRepo::exist(const Car c) {
	try {
		find(c.getnrInm());
		return true;
	}
	catch (CarRepoException&) {
		return false;
	}
}
/*cauta Car*/
Car CarRepo::find(string nrInm) {
	for (const Car c : all) {
		if (c.getnrInm() == nrInm) {
			return c;
		}
	}
	throw CarRepoException("Nu exista o masina cu numarul de inmatriculare:" + nrInm);
}
/*returneaza toate masinile*/
const vector<Car>& CarRepo::getAll()const noexcept {
	return all;
}

ostream& operator<<(ostream& out, const CarRepoException& ex) {
	out << ex.mesaje;
	return out;
}

void CarRepoFile::load_from_file()
{
	ifstream in(file_name);
	if (!in.is_open())
	{
		throw CarRepoException("Nu se poate deschide fisierul");
	}
	while (!in.eof())
	{
		std::string nr, prod, mod, type;
		in >> nr;
		in >> type;
		in >> prod;
		in >> mod;
		if (in.eof())
			break;
		Car c{ nr,type,prod,mod };
		CarRepo::store(c);
	}
}

void CarRepoFile::write_to_file()
{
	std::ofstream out(file_name);
	if (!out.is_open()) {
		std::string msg("Unable to open file");
		throw CarRepoException(msg);
	}
	for (auto &car : getAll()) {
		out << car.getnrInm() << " ";
		out << car.getType() << " ";
		out << car.getProd() << " ";
		out << car.getMod() << " ";
	}
	out.close();
}

void testRepo() {
	CarRepo rep;
	rep.store(Car{ "11aaa","b","a","c" });
	assert(rep.getAll().size() == 1);
	assert(rep.find("11aaa").getMod() == "c");
	rep.store(Car{ "22bbb","m","n","p" });
	assert(rep.getAll().size() == 2);
	try {
		rep.store(Car{ "22bbb","f","d","s" });
		assert(false);
	}
	catch (CarRepoException&) {
		assert(true);
	}
	try {
		rep.del("66ddg");
		assert(false);
	}
	catch (CarRepoException&) {
		assert(true);
	}
	try {
		rep.change("7b6n5", "a", "b", "c");
		assert(false);
	}
	catch ( const CarRepoException& re) {
		cout << re<<"\n";
		assert(true);
	}
	rep.change("11aaa", "b", "c", "a");
	assert(rep.find("11aaa").getMod() == "a");
	assert(rep.find("11aaa").getProd() == "c");
	assert(rep.find("11aaa").getType() == "b");
	rep.del("11aaa");
	assert(rep.getAll().size() == 1);
	try {
		rep.find("11aaa");
		assert(false);
	}
	catch (CarRepoException&) {
		assert(true);
	}

}

void ProbabRepo::store(const Car & c)
{
	float nr = (float)rand() / RAND_MAX;
	if (nr < probability)
	{
		throw StorageException("EXCEPIE!");
	}
	vpr.push_back(c);
}
