#include "MasinaGUI.h"
#include "Masina.h"
#include "carGUI.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <qtablewidget.h>
#include <qinputdialog.h>
#include <string>
#include <algorithm>

void CarStoreGUI::initGUICmps() {
	QHBoxLayout* ly = new QHBoxLayout;
	setLayout(ly);

	//adaug lista si sub doua butoane de sort
	QWidget* widDreapta = new QWidget;
	QVBoxLayout* vl = new QVBoxLayout;
	widDreapta->setLayout(vl);
	lst = new QListWidget;
	vl->addWidget(lst);
	
	QWidget* widBtnDreapta = new QWidget;
	QHBoxLayout* lyBtnsDr = new QHBoxLayout;
	widBtnDreapta->setLayout(lyBtnsDr);
	btnSortByType = new QPushButton("Sorteaza dupa tip");
	lyBtnsDr->addWidget(btnSortByType);
	
	btnSortByProd = new QPushButton("Sorteaza dupa producator");
	lyBtnsDr->addWidget(btnSortByProd);
	vl->addWidget(widBtnDreapta);
	ly->addWidget(widDreapta);

	btnSortByNrInm = new QPushButton("Sorteaza dupa numar de inmatriculare");
	lyBtnsDr->addWidget(btnSortByNrInm);
	vl->addWidget(widBtnDreapta);
	ly->addWidget(widDreapta);

	filterType = new QPushButton("Filtrare tip");
	lyBtnsDr->addWidget(filterType);

	filterProd = new QPushButton("Filtrare producator");
	lyBtnsDr->addWidget(filterProd);

	ReportByType = new QPushButton("Raport dupa tip");
	lyBtnsDr->addWidget(ReportByType);


	ExportToCVS = new QPushButton("Exportare lista masini in fisier CSV");
	lyBtnsDr->addWidget(ExportToCVS);
	
	//fac un form pentru detalii
	QWidget* widDetalii = new QWidget;
	QFormLayout* formLDetalii = new QFormLayout;
	widDetalii->setLayout(formLDetalii);
	
	txtNrInm = new QLineEdit;
	formLDetalii->addRow(new QLabel("Numar inmatriculare:"), txtNrInm);

	
	txtType = new QLineEdit;
	formLDetalii->addRow(new QLabel("Tip:"), txtType);
	
	txtProd = new QLineEdit;
	formLDetalii->addRow(new QLabel("Producator:"), txtProd);
	
	txtMod = new QLineEdit;
	formLDetalii->addRow(new QLabel("Model:"), txtMod);


	
	btnAdd = new QPushButton("Adauga masina");
	btnDel = new QPushButton("Sterge masina");
	btnUndo = new QPushButton("Undo");
	 AdaugaSpalatorie=new QPushButton("Adauga in spalatorie");
	 GolesteSpalatorie=new QPushButton("Goleste spalatorie");
	 GenereazaSpalatorie=new QPushButton("Genereaza Spalatorie");
	 btnModifica = new QPushButton("Modfica");

	formLDetalii->addWidget(btnAdd);
	formLDetalii->addWidget(btnDel);
	formLDetalii->addWidget(btnUndo);
	formLDetalii->addWidget(btnModifica);
	formLDetalii->addWidget(AdaugaSpalatorie);
	formLDetalii->addWidget(GolesteSpalatorie);
	formLDetalii->addWidget(GenereazaSpalatorie);


	
	ly->addWidget(widDetalii);
	




/*	//ctr.add_observer(this);
	
	QHBoxLayout* lyy = new QHBoxLayout;
	lstt = new QTableWidget;
	lyy->addWidget(lst);
	btnn = new QPushButton("Clear cos");
	lyy->addWidget(btnn);

	btnRandom = new QPushButton("Add random 4");
	lyy->addWidget(btnRandom);
	setLayout(lyy);
	lyy->addWidget(widDetalii);
	*/
}


void CarStoreGUI::connectSignalsSlots() {
	//cand se emite semnalul clicked de pe buton reincarc lista
	QObject::connect(btnSortByNrInm, &QPushButton::clicked, [&]() {
		reloadList(ctr.sortByNrInm());
	});
	//cand se emite semnalul clicked de pe buton reincarc lista
	QObject::connect(btnSortByType, &QPushButton::clicked, [&]() {
		reloadList(ctr.sortByType());
	});
	QObject::connect(btnSortByProd, &QPushButton::clicked, [&]() {
		reloadList(ctr.sortByProdAndMod());
	});
	//cand se selecteaza elementul din lista incarc detaliile
	QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
		if (lst->selectedItems().isEmpty()) {
			//nu este nimic selectat (golesc detaliile)
			txtNrInm->setText("");
			txtType->setText("");
			txtProd->setText("");
			txtMod->setText("");
			return;
		}
		QListWidgetItem* selItem = lst->selectedItems().at(0);
		QString Nrinm = selItem->text();
		txtNrInm->setText(Nrinm);

		QString tip = selItem->data(Qt::UserRole).toString();
		txtType->setText(tip);


		try {
			//cautam Medicament
			Car c = ctr.cauta(Nrinm.toStdString());
			txtType->setText(QString::fromStdString(c.getType()));
			txtProd->setText(QString::fromStdString(c.getProd()));
			txtMod->setText(QString::fromStdString(c.getMod()));
		}
		catch (CarException& ex) {
			QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.getMsg()));
		}
	});
	QObject::connect(btnAdd, &QPushButton::clicked, this, &CarStoreGUI::addNewCar);
	QObject::connect(btnDel, &QPushButton::clicked, this, &CarStoreGUI::deleteCar);
	QObject::connect(btnUndo, &QPushButton::clicked, this, &CarStoreGUI::undo);

	QObject::connect(filterType, &QPushButton::clicked, this, [&]() {
		QString Type = QInputDialog::getText(this, "Filtrare dupa tip", "Dati tipul:");
		vector<Car> cars = ctr.filterByType(Type.toStdString());
		filterShow(cars);
	});

	QObject::connect(filterProd, &QPushButton::clicked, this, [&]() {
		QString Prod = QInputDialog::getText(this, "Filtrare dupa producator", "Dati producatorul:");
		vector<Car> cars = ctr.filterByProd(Prod.toStdString());
		filterShow(cars);
	});

	QObject::connect(ReportByType, &QPushButton::clicked, this, [&]() {
		auto vect=ctr.raportType();
		QString toShow;
		for_each(vect.begin(), vect.end(), [&](auto a) {toShow.append("Tipul: "); toShow.append(QString::fromStdString(a.Type));
		toShow.append("  Frecventa: "); toShow.append(QString::number(a.frecventa)); toShow.append("\n"); toShow.append("\n"); });
		
		QMessageBox::information(this, "Raport dupa tip", toShow);

	});

	QObject::connect(btnModifica, &QPushButton::clicked, this, [&]() {
		QString tip = QInputDialog::getText(this, "Dati noul tip:");
		QString prod = QInputDialog::getText(this, "Dati noul produator:");
		QString mod = QInputDialog::getText(this, "Dati noul model:");
		ctr.modif(txtNrInm->text().toStdString(), tip.toStdString(), prod.toStdString(), mod.toStdString());
		reloadList(ctr.getAll());

	});
}


void CarStoreGUI::filterShow(vector<Car> vect)
{



	if (vect.size() != 0)
	{
		QString toShow;
		for (auto a : vect)
		{
			toShow.append("Numar inmatriculare:");
			toShow.append(QString::fromStdString(a.getnrInm()));
			toShow.append("\n");
			toShow.append("Tip:");
			toShow.append(QString::fromStdString(a.getType()));
			toShow.append("\n");
			toShow.append("Producator:");
			toShow.append(QString::fromStdString(a.getProd()));
			toShow.append("\n");
			toShow.append("Model:");
			toShow.append(QString::fromStdString(a.getMod()));
			toShow.append("\n");
			toShow.append("\n");
		}
		QMessageBox::information(this, "Lista filtrata", toShow);

	}
	else
		QMessageBox::warning(this,"Warning", "Nu exista masini");
}




void CarStoreGUI::addNewCar() {
	try {
		ctr.addCar(txtNrInm->text().toStdString(), txtType->text().toStdString(), txtProd->text().toStdString(), txtMod->text().toStdString());
		reloadList(ctr.getAll());
		
	}
	catch (CarRepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.msg));
	}
}

void CarStoreGUI::undo()
{
	try {
		ctr.undo();
		reloadList(ctr.getAll());
	}
	catch (CarException &ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}
}

void CarStoreGUI::deleteCar()
{
	try {
		
		ctr.delCar(txtNrInm->text().toStdString());
		reloadList(ctr.getAll());
	}
	catch (CarException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}
}

void CarStoreGUI::reloadList(const std::vector<Car>& Cars) {
	
	lst->clear();

	for (auto p : Cars) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(p.getnrInm()), lst);
		item->setData(Qt::UserRole, QString::fromStdString(p.getProd()));//adaug in lista (invizibil) si type 

	}
}
/*
void MedicamentStoreGUI::reloadTable(const std::vector<Medicament>& meds) {
	lstt->clear();
	lstt->setRowCount(meds.size());
	lstt->setColumnCount(4);
	for (int i = 0; i < meds.size(); i++) {
		lstt->setItem(i, 0, new QTableWidgetItem(meds[i].get_denumire().c_str()));
		lstt->setItem(i, 1, new QTableWidgetItem(QString::number(meds[i].get_pret())));
		lstt->setItem(i, 2, new QTableWidgetItem(meds[i].get_producator().c_str()));
		lstt->setItem(i, 2, new QTableWidgetItem(meds[i].get_substanta_activa().c_str()));
	}
}*/