#include "kvmrt2_media_editor.h"
#include <QtWidgets/QApplication>
#include <QSurfaceFormat>
#include <qstring.h>
#include <qdebug.h>
#include <qdir.h>
#include <qmessagebox.h>

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

	QString &dbPath = QString(argv[1]);
	if (dbPath.length() > 0)
	{

	}
	else {
		
		dbPath = QDir::homePath() + "/Papis/" +  "OP_DATA.DB";
	}
	QString &currPath = QDir::currentPath();
	
	//QMessageBox::information(
	//	nullptr, 
	//	QString("ME Path Information"), 
	//	QString("DB Path: %1\n\nRun Path: %2").arg(dbPath).arg(currPath),
	//	QMessageBox::Ok);
	
	kvmrt2_media_editor w(dbPath, currPath);
	
	w.show();
	
	return a.exec();
}
