#pragma once
#include "Service.h"
#include "masina.h"
#include "masiniRepo.h"
class ConsoleUI {

	Service& ctr;
	ProbabRepo &pr;
	void adaugaUI();
	void tipareste(const vector<Car>& masini);
	void stergeUI();
	void cautaUI();
	void modifica();
	void adauga_la_spalatUI();
	void tiparesteSpalatorie(const vector<Car>&cars);
	void tiparesteSpalatorieCVS(const vector<Car>&cars);
	void genereaza_lista_spalatUI();
	void raportUI();

public:

	ConsoleUI(Service& ctr, ProbabRepo& pr)noexcept :ctr{ ctr }, pr{ pr }{}
	ConsoleUI(const ConsoleUI& ot) = delete;
	void run();
};