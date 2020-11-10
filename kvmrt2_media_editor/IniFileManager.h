#pragma once

#include <qobject.h>
#include "DefineMode.h"

#define INIMANAGER IniFileManager::m_iniManager
#define STATIONLIST IniFileManager::m_iniManager->m_listStnInfo
#define OPDURLIST IniFileManager::m_iniManager->m_opDuration

struct StationInfo
{
	QString nameF;
	QString nameS;
};

struct audioStnDurInfo
{
	int code;
	int nameBM;
	int nameEN;
};

struct audioOpDurInfo
{
	int nextBM;
	int nextEN;
	int arrivingBM;
	int arrivingEN;
	int arrivalBM;
	int arrivalEN;
	int exchangeBM;
	int exchangeEN;
	int finalBM;
	int finalEN;
	int finalPh1BM;
	int finalPh1EN;
};

class IniFileManager : public QObject
{
	Q_OBJECT

public:
	explicit IniFileManager(QObject *parent = nullptr);
	virtual ~IniFileManager();

	static IniFileManager *m_iniManager;
	static IniFileManager *iniManager();
	static void setIniManager(IniFileManager *iniManager);

	// related to user account
	static void createAccountIniFile();
	static void loadAccountIniFile();
	static void changeAccountPassword(const QString &groupname, const QString &pw);
	static const QString getAccountValue(const QString& keyname);

	static AccountType m_accountType;
	static AccountType accountType();
	static void setAccountType(const AccountType &accountType);

	// related to stationinfo ini
	// station code
	void createStationInfoIni();

	QList<StationInfo> m_listStnInfo;
	audioOpDurInfo m_opDuration{ 0 };
};

