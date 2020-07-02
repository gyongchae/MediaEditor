#ifndef REGISTRYSETTINGS_H
#define REGISTRYSETTINGS_H

/*******************************************************************************************
	considering QSetting class
	- ini file read/write
	- registry read/write
*******************************************************************************************/




#include <QDialog>
#include "ui_registrysettings.h"

class RegistrySettings : public QDialog
{
	Q_OBJECT

public:
	RegistrySettings(QWidget *parent = 0);
	~RegistrySettings();

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
};

#endif // REGISTRYSETTINGS_H
