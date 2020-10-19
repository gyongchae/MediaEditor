#include "IniFileManager.h"
#include <qsettings.h>
#include <qdebug.h>
#include <qcryptographichash.h>

IniFileManager::IniFileManager(QObject *parent) : QObject(parent)
{
}

IniFileManager::~IniFileManager()
{
}

IniFileManager *IniFileManager::m_iniManager = nullptr;

IniFileManager * IniFileManager::iniManager()
{
	return m_iniManager;
}

void IniFileManager::setIniManager(IniFileManager * iniManager)
{
	m_iniManager = iniManager;
}

void IniFileManager::createAccountIniFile()
{
	QSettings settings(QString(ME_FOLDER_PATH) + QString(INI_FILE_ME_ACCOUNT), QSettings::IniFormat);
	qInfo() << Q_FUNC_INFO << settings.fileName();

	// nimda
	settings.beginGroup("Admin");
	settings.setValue("id", "admin");
	settings.setValue("pw", QString("admin").toLocal8Bit().toBase64());
	settings.setValue("editing", true);
	settings.setValue("uploading", true);
	settings.endGroup();

	settings.beginGroup("Normal");
	settings.setValue("id", "me");
	settings.setValue("pw", QString("me").toLocal8Bit().toBase64());
	settings.setValue("editing", true);
	settings.setValue("uploading", false);
	settings.endGroup();
}

void IniFileManager::loadAccountIniFile()
{
}

void IniFileManager::changeAccountPassword(const QString & groupname, const QString & pw)
{
	QSettings settings(QString(ME_FOLDER_PATH) + QString(INI_FILE_ME_ACCOUNT), QSettings::IniFormat);
	qInfo() << Q_FUNC_INFO << settings.fileName();
	settings.beginGroup(groupname);
	settings.setValue("pw", pw.toLocal8Bit().toBase64());
	settings.endGroup();
}

const QString IniFileManager::getAccountValue(const QString & keyname)
{
	QSettings settings(QString(ME_FOLDER_PATH) + QString(INI_FILE_ME_ACCOUNT), QSettings::IniFormat);
	return settings.value(keyname).toString();
}

AccountType IniFileManager::m_accountType = ACC_UNDEFINED;

AccountType IniFileManager::accountType()
{
	return m_accountType;
}

void IniFileManager::setAccountType(const AccountType & accountType)
{
	qInfo() << Q_FUNC_INFO << accountType;
	m_accountType = accountType;
}
