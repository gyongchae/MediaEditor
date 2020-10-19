#pragma once

#include <QDialog>
#include "ui_changepassworddialog.h"

class ChangePasswordDialog : public QDialog
{
	Q_OBJECT

public:
	ChangePasswordDialog(QWidget *parent = Q_NULLPTR);
	~ChangePasswordDialog();

	void initDlg();

signals:
	void sigValidateCurrPW(bool);

private slots:
	void accept();
	void onValidateCurrPW(const QString &txt);
	void onValidateNewPW(const QString &txt);

private:
	Ui::ChangePasswordDialog ui;
	QString m_keyName = "";
	QString m_groupName = "";
	bool m_bCurrPwCorrect = false;
};
