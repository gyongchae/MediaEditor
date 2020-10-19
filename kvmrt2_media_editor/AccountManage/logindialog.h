#pragma once

#include <QDialog>
#include "ui_logindialog.h"

class LogInDialog : public QDialog
{
	Q_OBJECT

public:
	LogInDialog(QWidget *parent = Q_NULLPTR);
	~LogInDialog();

	bool isIniFileExist(const QString &iniFile);

private slots:
	void checkAccount();
	void checkGuest(bool guest);

private:
	Ui::LogInDialog ui;
	bool m_bSuccessToLogin = false;

	QString m_id = "";
	QString m_pw = "";
};
