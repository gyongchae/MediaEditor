#include "changepassworddialog.h"
#include "DefineMode.h"
#include "IniFileManager.h"
#include <qdebug.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qmessagebox.h>

ChangePasswordDialog::ChangePasswordDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	// find children only including specific word
	QRegularExpression exp("PW");
	for (auto a : this->findChildren<QLineEdit*>(exp))
	{
		a->setEchoMode(QLineEdit::Password);
		a->setMaxLength(16); // limit max length
	}

	// [ISSUE] if connect has established, accept() called twice.
	//connect(ui.buttonBox, &QDialogButtonBox::accepted, this, &ChangeAccountDialog::accept);

	connect(ui.comboAccount,
		static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
		[this](int idx)
	{
		if (idx == 0)
		{
			m_keyName = "Admin/pw";
			m_groupName = "Admin";
		}
		else if (idx == 1)
		{
			m_keyName = "Normal/pw";
			m_groupName = "Normal";
		}
	});

	// placeholder
	ui.editCurrPW->setPlaceholderText("Password");
	ui.editNewPW->setPlaceholderText("New password");
	ui.editVerifyPW->setPlaceholderText("New password");

	connect(ui.editCurrPW, SIGNAL(textChanged(QString)), this, SLOT(onValidateCurrPW(QString)));

	ui.editNewPW->setEnabled(m_bCurrPwCorrect);
	ui.editVerifyPW->setEnabled(m_bCurrPwCorrect);

	connect(this, SIGNAL(sigValidateCurrPW(bool)), ui.editNewPW, SLOT(setEnabled(bool)));
	connect(this, SIGNAL(sigValidateCurrPW(bool)), ui.editVerifyPW, SLOT(setEnabled(bool)));

	connect(ui.editNewPW, SIGNAL(textChanged(QString)), this, SLOT(onValidateNewPW(QString)));
	connect(ui.editVerifyPW, SIGNAL(textChanged(QString)), this, SLOT(onValidateNewPW(QString)));
}

ChangePasswordDialog::~ChangePasswordDialog()
{

}

void ChangePasswordDialog::initDlg()
{
	// window icon
	setWindowIcon(QIcon(QString(ME_FOLDER_PATH) + QString("Res/Free/Moon-dreamy.ico")));

	// get ID from ini file 
	ui.comboAccount->addItem(INIMANAGER->getAccountValue("Admin/id"));
	ui.comboAccount->addItem(INIMANAGER->getAccountValue("Normal/id"));
}

void ChangePasswordDialog::accept()
{
	QByteArray baPW;
	QString strPW;
	baPW.append(INIMANAGER->getAccountValue(m_keyName));
	strPW = QByteArray::fromBase64(baPW);
	if (ui.editCurrPW->text() == strPW)
	{
		if (ui.editNewPW->text() == ui.editVerifyPW->text())
		{
			qInfo() << Q_FUNC_INFO << m_keyName << "passworkd changed";
			INIMANAGER->changeAccountPassword(m_groupName, ui.editNewPW->text());
			QDialog::accept();
		}
		else
		{
			// can't change PW
			QMessageBox::warning(this, QString("Validation error"),
				QString("The passwords entered didn't match"));
		}
	}
	else
	{
		// can't change PW
		QMessageBox::warning(this, QString("Validation error"),
			QString("Wrong password. Please try again."));
	}
}

void ChangePasswordDialog::onValidateCurrPW(const QString & txt)
{
	QByteArray baPW;
	QString strPW;
	baPW.append(INIMANAGER->getAccountValue(m_keyName));
	strPW = QByteArray::fromBase64(baPW);
	if (txt == strPW)
	{
		ui.labelValidateCurrPW->setText("Correct Password!");
		ui.labelValidateCurrPW->setStyleSheet("QLabel {color:green;}");
		m_bCurrPwCorrect = true;
	}
	else
	{
		ui.labelValidateCurrPW->setText("That password doesn't match our records. Try again.");
		ui.labelValidateCurrPW->setStyleSheet("QLabel {color:red;}");
		m_bCurrPwCorrect = false;
	}

	emit sigValidateCurrPW(m_bCurrPwCorrect);
}

void ChangePasswordDialog::onValidateNewPW(const QString & txt)
{
	Q_UNUSED(txt);

	if (m_bCurrPwCorrect == true)
	{
		if (ui.editNewPW->text() == ui.editVerifyPW->text())
		{
			ui.labelValidateNewPW->setText("Confirm password matches.");
			ui.labelValidateNewPW->setStyleSheet("QLabel {color:green;}");
		}
		else
		{
			ui.labelValidateNewPW->setText("The passwords entered didn't match");
			ui.labelValidateNewPW->setStyleSheet("QLabel {color:red;}");
		}
	}
}
