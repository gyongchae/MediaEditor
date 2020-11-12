#pragma once

#include <qobject.h>
#include "DefineMode.h"

#define INIMANAGER IniFileManager::m_iniManager

struct StationIniInfo
{
	int code; // group(section) name
	QString nameF;
	QString nameS;
	int hasExchange;
	int isProvisional;
	int apprDistance;
	int paNextBM;
	int paNextEN;
	int paApprBM;
	int paApprEN;
	int paArrvBM;
	int paArrvEN;
	int paExchangeBM;
	int paExchangeEN;
};

struct audioOpDurInfo
{
	int nextBM;
	int nextEN;
	int arrivingBM;
	int arrivingEN;
	int arrivalBM;
	int arrivalEN;
};

struct audioListInfo
{
	int id;
	QString desc;
	int duration;
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
	void createPaInfoIni();
	void addStnIniInfo(const StationIniInfo& stIni);
	void addAudioListInfo(const audioListInfo& st);
	void clearStnIniInfo();
	void clearAudioListInfo();
	void readStationInfoIni(const int &stnCode);
	void readAudioListInfoIni();


	audioOpDurInfo m_opDuration{ 0 };

private:
	QList<StationIniInfo> m_listStnAudioInfo;
	QList<audioListInfo> m_listAudioInfo;
};

