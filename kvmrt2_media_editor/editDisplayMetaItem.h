#pragma once

#include <QDialog>
#include "ui_editDisplayMetaItem.h"

class QDataWidgetMapper;

class editDisplayMetaItem : public QDialog
{
	Q_OBJECT

public:
	editDisplayMetaItem(int nRow,int nSubRow,QWidget *parent = Q_NULLPTR);
	~editDisplayMetaItem();
	QDataWidgetMapper *m_pProp;
	QDataWidgetMapper *m_pItem;

	void initWidgets();
	void initWidgetMapper();
	void setComboBox();

private slots:
	void applyDisplayItem();
	void acceptedChanges();
	void rejectedChanges();

private:
	Ui::editDisplayMetaItem ui;
	int m_nRow;
	int m_nSubRow;
};
