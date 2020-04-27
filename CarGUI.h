#pragma once
#include <qwidget.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qboxlayout.h>
#include <qlabel.h>
#include <qtablewidget.h>
#include <vector>
#include "masina.h"
#include "service.h"

class CarStoreGUI : public QWidget {
private:
	Service &ctr;
	QListWidget *lst;
	QPushButton *AdaugaSpalatorie;
	QPushButton* GolesteSpalatorie;
	QPushButton* GenereazaSpalatorie;
	QPushButton* btnSortByType;
	QPushButton* btnSortByProd;
	QPushButton* btnSortByNrInm;
	QPushButton* btnModifica;
	QPushButton* ReportByType;
	QPushButton *ExportToCVS;
	QLineEdit* txtNrInm;
	QLineEdit* txtType;
	QLineEdit* txtProd;
	QLineEdit* txtMod;
	QPushButton* btnAdd;
	QPushButton* btnn;
	QPushButton* btnRandom;
	QPushButton* btnDel;
	QPushButton *btnUndo;
	QPushButton *filterType;
	QPushButton *filterProd;
	QTableView* tblV = new QTableView;
	QTableWidget *lstt;
	void initGUICmps();
	void connectSignalsSlots();
	void reloadList(const std::vector<Car>& car);
	void addNewCar();
	void deleteCar();
	void undo();
	void filterShow(vector<Car> cars);
public:
	CarStoreGUI(Service &ctr) :ctr{ ctr } {
		initGUICmps();
		connectSignalsSlots();
		reloadList(ctr.getAll());
	}
};