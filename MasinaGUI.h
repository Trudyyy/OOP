#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_QtGuiApplication1.h"

class MasinaGUI : public QMainWindow
{
	Q_OBJECT
public:
	MasinaGUI(QWidget *parent = Q_NULLPTR);

private:
	Ui::QtGuiApplication1 ui;
};