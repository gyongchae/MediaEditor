#include "logindialog.h"
#include "IniFileManager.h"
#include "DefineMode.h"
#include <qfileinfo.h>
#include <qmessagebox.h>
#include <qlineedit.h>
#include <qdebug.h>

LogInDialog::LogInDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	setWindowIcon(QIcon(QString(ME_FOLDER_PATH) + QString("/Res/Free/Rick.ico")));

	connect(ui.btnClose, SIGNAL(clicked(bool)), this, SLOT(close()));
	connect(ui.btnLogIn, SIGNAL(clicked(bool)), this, SLOT(checkAccount()));
	connect(ui.chkGuest, SIGNAL(toggled(bool)), this, SLOT(checkGuest(bool)));

	ui.editUserName->setFocus();
	ui.editUserName->setMaxLength(16);
	ui.editUserName->setPlaceholderText("Enter user name");
	ui.editPassword->setEchoMode(QLineEdit::Password);
	ui.editPassword->setMaxLength(16);
	ui.editPassword->setPlaceholderText("Enter the password");

	if (!isIniFileExist(INI_FILE_ME_ACCOUNT))
	{
		INIMANAGER->createAccountIniFile();
	}
}

LogInDialog::~LogInDialog()
{
}

bool LogInDialog::isIniFileExist(const QString & iniFile)
{
	QFileInfo checkFile(QString(ME_FOLDER_PATH) + iniFile);
	if (checkFile.exists() && checkFile.isFile())
	{
		qInfo() << checkFile.absoluteFilePath() << "is existed.";
		return true;
	}
	else
	{
		qInfo() << checkFile.absoluteFilePath() << "is created.";
		return false;
	}
}

void LogInDialog::checkAccount()
{
	bool bAccepted = false;

	if (INIMANAGER->accountType() == ACC_GUEST)
	{
		bAccepted = true;
	}
	else
	{
		QByteArray ba;
		QString decrypt;
		if (ui.editUserName->text() == INIMANAGER->getAccountValue("Admin/id"))
		{
			ba.append(INIMANAGER->getAccountValue("Admin/pw"));
			decrypt = QByteArray::fromBase64(ba);
			if (ui.editPassword->text() == decrypt)
			{
				INIMANAGER->setAccountType(ACC_ADMIN);
				bAccepted = true;
			}
			else
			{
				bAccepted = false;
			}
		}
		else if (ui.editUserName->text() == INIMANAGER->getAccountValue("Normal/id"))
		{
			ba.append(INIMANAGER->getAccountValue("Normal/pw"));
			decrypt = QByteArray::fromBase64(ba);
			if (ui.editPassword->text() == decrypt)
			{
				INIMANAGER->setAccountType(ACC_NORMAL);
				bAccepted = true;
			}
			else
			{
				bAccepted = false;
			}
		}
		else
		{
			bAccepted = false;
		}
	}

	if (bAccepted)
	{
		emit QDialog::accept();
	}
	else // wrong info
	{
		QMessageBox::warning(this, QString("Login Failed"),
			QString("Invalid ID or incorrent password, try again."));
		INIMANAGER->setAccountType(ACC_UNDEFINED);
		ui.editUserName->setFocus();
	}
}

void LogInDialog::checkGuest(bool guest)
{
	if (guest)
	{
		ui.editUserName->clear();
		ui.editPassword->clear();
		INIMANAGER->setAccountType(ACC_GUEST);
	}
	else
	{
		INIMANAGER->setAccountType(ACC_UNDEFINED);
	}

	ui.editUserName->setEnabled(!guest);
	ui.editPassword->setEnabled(!guest);
}
