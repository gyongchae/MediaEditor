#include "userinfowidget.h"
#include <qpushbutton.h>
#include "changepassworddialog.h"
#include "IniFileManager.h"

UserInfoWidget::UserInfoWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.btnChangeInfo, &QPushButton::clicked, this, &UserInfoWidget::onChangeAccInfo);
	connect(ui.btnClose, &QPushButton::clicked, this, &UserInfoWidget::close);

	QList<QCheckBox*> chk = this->findChildren<QCheckBox*>();
	for (auto a : chk)
	{
		SetReadOnly(a, true);
	}
}

UserInfoWidget::~UserInfoWidget()
{
}

void UserInfoWidget::SetReadOnly(QCheckBox * checkBox, bool readOnly)
{
	//reference: https://stackoverflow.com/questions/35190259/how-to-make-qcheckbox-readonly-but-not-grayed-out
	checkBox->setAttribute(Qt::WA_TransparentForMouseEvents, readOnly);
	checkBox->setFocusPolicy(readOnly ? Qt::NoFocus : Qt::StrongFocus);
}

void UserInfoWidget::show()
{
	if (INIMANAGER->accountType() != ACC_ADMIN)
	{
		ui.btnChangeInfo->setEnabled(false);
	}
	else // only admin
	{
		ui.btnChangeInfo->setEnabled(true);
	}

	ui.editAdminID->setText(INIMANAGER->getAccountValue("Admin/id"));
	ui.editNormalID->setText(INIMANAGER->getAccountValue("Normal/id"));

	QWidget::show();
}

void UserInfoWidget::onChangeAccInfo()
{
	ChangePasswordDialog dlg;
	dlg.initDlg();
	if (dlg.exec() == QDialog::Accepted)
	{

	}
	else
	{

	}
}
