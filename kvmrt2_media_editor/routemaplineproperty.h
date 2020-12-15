#pragma once

#include <QDialog>
#include "ui_routemaplineproperty.h"
#include "DefineTables.h"

class QIndexComboBox;

class RouteMapLineProperty : public QDialog
{
	Q_OBJECT

public:
	explicit RouteMapLineProperty(const int stnCode, QWidget *parent = Q_NULLPTR);
	virtual ~RouteMapLineProperty();

	void initWidget(const int stnCode);
	int getStationCode() const;
	QString getStationName() const;

private slots: 
	void acceptedChanges();
	void rejectedChanges();

private:
	Ui::RouteMapLineProperty ui;
};
