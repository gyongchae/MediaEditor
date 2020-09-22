#pragma once

#include <QDialog>
#include "ui_DisplayDateTimePropEdit.h"

class QDataWidgetMapper;

class DisplayDateTimePropEdit : public QDialog
{
	Q_OBJECT

public:
	DisplayDateTimePropEdit(int nItem, int nProp, QWidget *parent = Q_NULLPTR);
	~DisplayDateTimePropEdit();

	QDataWidgetMapper *m_pProp;
	QDataWidgetMapper *m_pItem;

private slots:
	void acceptedChanges();
	void rejectedChanges();

private:
	Ui::DisplayDateTimePropEdit ui;
};
