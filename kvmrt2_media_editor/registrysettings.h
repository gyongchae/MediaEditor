#ifndef REGISTRYSETTINGS_H
#define REGISTRYSETTINGS_H

/*******************************************************************************************
	considering QSetting class
	- ini file read/write
	- registry read/write
*******************************************************************************************/

#include <QDialog>
#include "ui_registrysettings.h"

class dataModel;

class RegistrySettings : public QDialog
{
	Q_OBJECT

public:
	RegistrySettings(QWidget *parent = 0);
	~RegistrySettings();

	void initVersionSpinBox();
	bool initOPDataVersion();

private:
	Ui::RegistrySettings ui;

protected:
	void closeEvent(QCloseEvent *event);

private slots:

	void acceptedChanges();
	void rejectedChanges();
	void loadDatabasePath();
	void loadVideoFileSavePath();
	void loadAudioFileSavePath();
	void loadFontFileSavePath();
	void changeDataVersion(int val);
};

#endif // REGISTRYSETTINGS_H
