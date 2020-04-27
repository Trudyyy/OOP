#include "console.h"
#include <iostream>
#include <unordered_map>
#include "masina.h"
#include "CVSOptions.h"
#include <string>
#include <fstream>

using namespace std;

void ConsoleUI::raportUI()
{
	auto toate = ctr.getAll();
	unordered_map<string, int>rez;
	for (auto car : toate)
		rez[car.getType()] = 0;
	for (auto car : toate)
		rez[car.getType()]++;
	for (auto x : rez)
		cout << "\nTypul: " << x.first << " Numar: " << x.second;
}

void ConsoleUI::genereaza_lista_spalatUI()
{
	int nr = 0;
	cout << "Numar masini: "; cin >> nr;
	cout << endl;
	genereaza_lista_spalat(nr);
}

void ConsoleUI::adauga_la_spalatUI()
{
	string nrInm, Type, Prod, Mod;
	cout << "Numar de inmatriculare: "; cin >> nrInm;
	cout << "Producator: "; cin >> Prod;
	cout << "Model: "; cin >> Mod;
	cout << "Tip: "; cin >> Type;
	Car car{ nrInm,Type,Prod,Mod };
	adauga_la_spalat(car);
}

void ConsoleUI::tiparesteSpalatorie(const vector<Car>& cars)
{
	cout << "Masinile:\n";
	for (const auto &c : cars)
	{
		cout << ' ' << c.getnrInm() << ' ' << c.getType() << ' ' << c.getProd() << ' ' << c.getMod() << '\n';
	}
	cout << "Sfarsit lista masinilor\n";
}

void ConsoleUI::tiparesteSpalatorieCVS(const vector<Car>& cars)
{
	std::fstream f;
	f.open("fisier.cvs", std::fstream::out);
	for (const auto &c:cars)
	{
		f << c.getnrInm() << ' ' << c.getType() << ' ' << c.getProd() << ' ' << c.getMod() << '\n';
	}
}



void ConsoleUI::tipareste(const vector<Car>& cars) {
	cout << "\nMasinile:\n";
	for (const auto& c : cars) {
		cout << ' ' << c.getnrInm() << ' ' << c.getType() << ' ' << c.getProd() << ' ' << c.getMod() << '\n';
	}
	cout << "Sfarsit lista masinilor\n";
}

void ConsoleUI::adaugaUI() {
	string ty, mo, pr,nr;
	cout << "Dati numar de inmatriculare:";
	cin >> nr;
	cout << "Dati tipul:";
	cin >> ty;
	cout << "Dati producatorul:";
	cin >> pr;
	cout << "Dati modelul:";
	cin >> mo;
	ctr.addCar(nr, ty, pr, mo);
	cout << "Masina adaugata\n";
}

void ConsoleUI::stergeUI() {
	string nr;
	cout << "Dati numar de inmatriculare:";
	cin >> nr;
	ctr.delCar(nr);
	cout << "Masina stearsa\n";
}

void ConsoleUI::cautaUI() {
	string nr;
	cout << "Dati numar de inmatriculare:";
	cin >> nr;
	Car c = ctr.cauta(nr);
	cout << c.getnrInm() << ' ' << c.getType() << ' ' << c.getProd() << ' ' << c.getMod();
}

void ConsoleUI::modifica() {
	string ty, mo, pr, nr;
	cout << "Dati numar de inmatriculare:";
	cin >> nr;
	cout << "Dati tipul:";
	cin >> ty;
	cout << "Dati producatorul:";
	cin >> pr;
	cout << "Dati modelul:";
	cin >> mo;
	ctr.modif(nr, ty, pr, mo);
	cout << "Masina adaugata\n";
}

void ConsoleUI::run() {
	while (true) {
		cout << "\nMeniu:\n";
		cout << "0.iesire\n1.tipareste\n2.adauga\n3.sterge\n4.modifica\n5.cauta\n6.sortare dupa numar de inmatriculare\n7.sortare dupa tip\n8.sortare dupa producator si model\n9.filtrare dupa producator\n10.filtrare dupa tip\n11.Meniu spalatorie\n12.Raport";
		int cmd;
		string a;
		cin >> cmd;
		try{
			switch (cmd) {
			case 1:
			{
				tipareste(ctr.getAll());
				break;
			}
			case 2:
			{
				adaugaUI();
				break;
			}
			case 3:
			{
				stergeUI();
				break; 
			}
			case 4:
			{
				modifica();
				break;
			}
			case 5:
			{
				cautaUI();
				break;
			}
			case 6:
			{
				tipareste(ctr.sortByNrInm());
				break;
			}
			case 7:
			{	
				tipareste(ctr.sortByType());
				break;
			}
			case 8:
			{
				tipareste(ctr.sortByProdAndMod());
				break;
			}
			case 9:
			{
				cout << "Alegeti un producator:\n";
				cin >> a;
				tipareste(ctr.filterByProd(a));
				break;
			}
			case 10:
			{
				cout << "Alegeti un tip:\n";
				cin >> a;
				tipareste(ctr.filterByType(a));
				break; 
			}
			case 11:
			{
				int cmdd = 0;
				cout << "1.Goleste spalatoria\n2.Adauga la spalatorie\n3.Genereaza alator spalatoria\nComanda: "; cin >> cmdd;
				if (cmdd == 1) {
					goleste_spalaorie();
					cout << "\nNumar masini in spalatorei= 0\n";
				}
				if (cmdd == 2) {
					adauga_la_spalatUI();
					cout << "\nNumar masini in spalatorie= " << numar_masini()<<"\n";
				}
				if (cmdd == 3) {
					genereaza_lista_spalatUI();
					cout << "\nNumar masini in spalatorie= " << numar_masini()<<"\n";
				}
				break;
			}
			case 12:
			{
				raportUI(); 
				break;
			}
			case 0:
				return;
			default:
				cout << "Comanda invalida!!!";
			}
		}
		catch (const CarRepoException& ex) {
			cout << ex << '\n';
		}
		catch (const ValidateException& ex) {
			cout << ex << '\n';
		}
	}
}