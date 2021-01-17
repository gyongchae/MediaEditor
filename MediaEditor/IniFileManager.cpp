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
	QSettings settings(QString(ME_APP_PATH) + QString(INI_FILE_ME_ACCOUNT), QSettings::IniFormat);
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
	QSettings settings(QString(ME_APP_PATH) + QString(INI_FILE_ME_ACCOUNT), QSettings::IniFormat);
	qInfo() << Q_FUNC_INFO << settings.fileName();
	settings.beginGroup(groupname);
	settings.setValue("pw", pw.toLocal8Bit().toBase64());
	settings.endGroup();
}

const QString IniFileManager::getAccountValue(const QString & keyname)
{
	QSettings settings(QString(ME_APP_PATH) + QString(INI_FILE_ME_ACCOUNT), QSettings::IniFormat);
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

void IniFileManager::createStationInfoIni()
{
	QSettings settings(QString(ME_DATA_PATH) + QString(INI_FILE_ME_STNINFO), QSettings::IniFormat);

	for (auto stIni : m_listStnAudioInfo)
	{
		bool hasEx = (stIni.hasExchange == 1) ? true : false;
		bool isPro = (stIni.isProvisional == 1) ? true : false;

		settings.beginGroup(QString("%1").arg(stIni.code));
		settings.setValue("fullName", stIni.nameF);
		settings.setValue("shortName", stIni.nameS);
		settings.setValue("hasExchange", hasEx);
		settings.setValue("isProvisional", isPro);
		settings.setValue("apprDistance", stIni.apprDistance);
		settings.setValue("paNextBM", stIni.paNextBM);
		settings.setValue("paNextEN", stIni.paNextEN);
		settings.setValue("paArrivingBM", stIni.paApprBM);
		settings.setValue("paArrivingEN", stIni.paApprEN);
		settings.setValue("paArrivalBM", stIni.paArrvBM);
		settings.setValue("paArrivalEN", stIni.paArrvEN);
		settings.setValue("paExchangeBM", stIni.paExchangeBM);
		settings.setValue("paExchangeEN", stIni.paExchangeEN);
		settings.endGroup();
	}
}

void IniFileManager::createPaInfoIni()
{
	QSettings settings(QString(ME_DATA_PATH) + QString(INI_FILE_ME_STNINFO), QSettings::IniFormat);

	int index = 0;
	settings.beginWriteArray("audios");
	for (auto a : m_listAudioInfo)
	{
		settings.setArrayIndex(index++);
		settings.setValue("id", a.id);
		settings.setValue("msgType", a.msgType);
		settings.setValue("desc", a.desc);
		settings.setValue("duration", a.duration);
	}
	settings.endArray();
}

void IniFileManager::addStnIniInfo(const StationIniInfo & stIni)
{
	m_listStnAudioInfo.append(stIni);
}

void IniFileManager::addAudioListInfo(const audioListInfo & st)
{
	m_listAudioInfo.append(st);
}

void IniFileManager::clearStnIniInfo()
{
	m_listStnAudioInfo.clear();
}

void IniFileManager::clearAudioListInfo()
{
	m_listAudioInfo.clear();
}

void IniFileManager::readStationInfoIni(const int &stnCode)
{
	QSettings settings(QString(ME_DATA_PATH) + QString(INI_FILE_ME_STNINFO), QSettings::IniFormat);

	settings.beginGroup(QString("%1").arg(stnCode));
	for (auto k : settings.allKeys())
		qDebug() << k << settings.value(k);
	settings.endGroup();
}

void IniFileManager::readAudioListInfoIni()
{
	QSettings settings(QString(ME_DATA_PATH) + QString(INI_FILE_ME_STNINFO), QSettings::IniFormat);

	settings.beginReadArray("audios");
	const int& size = settings.value("size").toInt();
	for (int i = 0; i < size; i++)
	{
		settings.setArrayIndex(i);
		qDebug() << settings.value("id").toInt()
			<< settings.value("msgType").toString()
			<< settings.value("desc").toString() 
			<< settings.value("duration").toInt();
	}
	settings.endArray();
}
