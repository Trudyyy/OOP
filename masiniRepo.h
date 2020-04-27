#pragma once
#include "masina.h"
#include <vector>
#include <string>

using namespace std;

class AbstractRepo
{
public:
	virtual void store(const Car &car) = 0;
	virtual ~AbstractRepo() {};
};

class ProbabRepo :public AbstractRepo
{
private:
	float probability;
public:
	vector<Car> vpr;
	ProbabRepo(float poro) :probability{ poro } {}
	void store(const Car &c);
};

class CarRepo:public AbstractRepo {
	
public:
	CarRepo() = default;
	CarRepo(const CarRepo& ot) = delete;
	virtual ~CarRepo() = default;
	virtual void store(const Car& c);
	virtual void del(string nrInm);
	virtual void change(string nrInm, string Type, string Prod, string Mod);
	Car find(string nrInm);
	const vector<Car>& getAll()const noexcept;
	vector<Car> all;
	bool exist(const Car c);
};


/*folosit pentru a arunca exceptii*/
class CarRepoException {
	string mesaje;
public:
	CarRepoException(string m) :mesaje{m}{}

	friend ostream& operator<<(ostream& out, const CarRepoException& ex);
};

class repoException {
	string msg;
public:
	repoException(string m) :msg{ m } {}
	string getMsg()const { return msg; }
};

class CarRepoFile :public CarRepo
{
private:
	std::string file_name;
	void load_from_file();
	void write_to_file();
public:
	CarRepoFile(std::string fine_name) :CarRepo(), file_name{file_name}{load_from_file(); }
	void store(const Car &c)override {
		CarRepo::store(c);
		write_to_file();
	}
	void del(const string a)override {
		CarRepo::del(a);
		write_to_file();
	}
	void change(string nrInm, string Type, string Prod, string Mod)override {
		CarRepo::change(nrInm, Type, Prod, Mod);
		write_to_file();
	}
};

ostream& operator<<(ostream& out, const CarRepoException& ex);

void testRepo();