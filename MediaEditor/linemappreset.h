#ifndef LINEMAPPRESET_H
#define LINEMAPPRESET_H

#include <QDialog>
#include <QdataWidgetMapper.h>
#include "ui_linemappreset.h"

class LineMapPreset : public QDialog
{
	Q_OBJECT

public:
	LineMapPreset(int nRow,QWidget *parent = 0);
	~LineMapPreset();
	int m_nRow;
	QDataWidgetMapper *m_pWidgetMapper;
private slots:	
	void acceptedChanges();
	void rejectedChanges();


private:
	Ui::LineMapPreset ui;
};

#endif // LINEMAPPRESET_H
