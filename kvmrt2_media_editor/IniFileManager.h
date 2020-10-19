#pragma once

#include <qobject.h>
#include "DefineMode.h"

#define INIMANAGER IniFileManager::m_iniManager

class IniFileManager : public QObject
{
	Q_OBJECT

public:
	explicit IniFileManager(QObject *parent = nullptr);
	virtual ~IniFileManager();

	static IniFileManager *m_iniManager;
	static IniFileManager *iniManager();
	static void setIniManager(IniFileManager *iniManager);

	static void createAccountIniFile();
	static void loadAccountIniFile();
	static void changeAccountPassword(const QString &groupname, const QString &pw);
	static const QString getAccountValue(const QString& keyname);

	static AccountType m_accountType;
	static AccountType accountType();
	static void setAccountType(const AccountType &accountType);
};

