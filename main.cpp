#include "console.h"
#include "masiniRepo.h"
#include "CarGUI.h"
#include "masinaGUI.h"
#include "validator.h"
#include <QtWidgets/QApplication>
#include <fstream>
#include "service.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

void adaugaCeva(Service& ctr) {
	ctr.addCar("aa11aaa", "sport", "Koenigsegg", "Agera");
	ctr.addCar("bb22bbb", "lmuzina", "RollsRoys", "Phantom8");
	ctr.addCar("cc33ccc", "4x4", "Toyota", "Raw4");
	ctr.addCar("dd44ddd", "duba", "Mercedes", "Vitto");
}

void testAll() {
	testRepo();
	testService();
}

int main(int argc,char *argv[])
{
	QApplication a(argc, argv);
	testAll();
	std::ofstream ofs;
	ofs.open("masini.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
	ProbabRepo repp{ 0.5 };
	CarRepoFile rep{ "maisni.txt" };
	CarValidator valid;
	Service ctr{ rep,valid };
	adaugaCeva(ctr);
	ConsoleUI UI{ ctr,repp };
	CarStoreGUI gui{ ctr };
	UI.run();
	gui.show();
	_CrtDumpMemoryLeaks();
	return a.exec();
}