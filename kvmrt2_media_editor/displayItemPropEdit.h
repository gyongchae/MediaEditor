#pragma once

#include <QDialog>
#include "ui_displayItemPropEdit.h"

class QDataWidgetMapper;

class displayItemPropEdit : public QDialog
{
	Q_OBJECT

public:
	displayItemPropEdit(int nItem,int nProp,QWidget *parent = Q_NULLPTR);
	~displayItemPropEdit();
	QDataWidgetMapper *m_pProp;
	QDataWidgetMapper *m_pItem;
private slots:
	void acceptedChanges();
	void rejectedChanges();
private:
	Ui::displayItemPropEdit ui;
};
