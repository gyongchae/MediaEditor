#include "kvmrt2_media_editor.h"
#include <QtWidgets/QApplication>
#include <QSurfaceFormat>
#include <qstring.h>
#include <qdebug.h>
#include <qdir.h>
#include <qmessagebox.h>

#include "DefineMode.h"
#include "IniFileManager.h"
#include "logindialog.h"

#undef NOMINMAX
#include <windows.h>
#include <gdiplus.h>
#define NOMINMAX
#pragma comment(lib, "gdiplus")

class CGdiPlusStarter
{
private:
	ULONG_PTR m_gpToken;
public:
	bool m_bSuccess;
	CGdiPlusStarter()
	{
		Gdiplus::GdiplusStartupInput gpsi;
		m_bSuccess = (Gdiplus::GdiplusStartup(&m_gpToken, &gpsi, nullptr) == Gdiplus::Ok);
	}
	~CGdiPlusStarter()
	{
		Gdiplus::GdiplusShutdown(m_gpToken);
	}
};

int main(int argc, char *argv[])
{

	CGdiPlusStarter g_gps;
	QApplication a(argc, argv);
	
	QCoreApplication::addLibraryPath("./");
	QSurfaceFormat format;
	format.setDepthBufferSize(24);
	QSurfaceFormat::setDefaultFormat(format);

	QCoreApplication::setOrganizationName(MY_ORGANIZATION_NAME);
	QCoreApplication::setApplicationName(MY_APPLICATION_NAME);
	QCoreApplication::setApplicationVersion(MY_APP_VERSION);

	qInfo() << Q_FUNC_INFO << "organizationName:" << QCoreApplication::organizationName();
	qInfo() << Q_FUNC_INFO << "applicationName:" << QCoreApplication::applicationName();
	qInfo() << Q_FUNC_INFO << "applicationVersion:" << QCoreApplication::applicationVersion();

	IniFileManager *iniManager = new IniFileManager;
	IniFileManager::setIniManager(iniManager);

	QString &dbPath = QString(argv[1]);
	if (dbPath.length() > 0)
	{

	}
	else {

		dbPath = OP_DATA_DB_PATH;
	}
	QString &currAppPath = QDir::currentPath();

	if (OFFICIAL_RELEASE == true)
	{
		// login
		LogInDialog logindlg;
		if (logindlg.exec() == QDialog::Accepted)
		{
			qInfo() << "Log-In Dialog acceplted";
		}
		else
		{
			qInfo() << "Log-In Dialog didn't accepted";
			INIMANAGER->setAccountType(ACC_UNDEFINED);
		}
	}
	else // debugging
	{
		INIMANAGER->setAccountType(ACC_ADMIN);

		QMessageBox::information(
			nullptr,
			QString("ME Path Information"),
			QString("DB Path: %1\n\nApp Path: %2\nApp Version: %3")
			.arg(dbPath)
			.arg(currAppPath)
			.arg(QCoreApplication::applicationVersion()),
			QMessageBox::Ok);
	}

	kvmrt2_media_editor w(dbPath, currAppPath);

	w.initAccountType(INIMANAGER->accountType());
	w.show();

	return a.exec();
}
