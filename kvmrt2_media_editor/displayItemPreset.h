#pragma once

#include <QDialog>
#include "ui_displayItemPreset.h"

class QDataWidgetMapper;

class displayItemPreset : public QDialog
{
	Q_OBJECT

public:
	displayItemPreset(int nRow,QWidget *parent = Q_NULLPTR);
	~displayItemPreset();

private slots:
	void acceptedChanges();
	void rejectedChanges();

private:
	Ui::displayItemPreset ui;
	QDataWidgetMapper *m_pWidgetMapper;
	int m_nRow;
};
