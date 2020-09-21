#include "registrysettings.h"
#include <QtGui>
#include "DataManage.h"
#include <qdebug.h>

RegistrySettings::RegistrySettings(QWidget *parent)
	: QDialog(parent)
{
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	ui.setupUi(this);
	auto *pDM = CDataManage::GetInstance();
	ui.m_leDBPath->setText(pDM->DBPath());
	ui.m_leAudioFileSavePath->setText(pDM->audioPath());
	ui.m_leVideoFileSavePath->setText(pDM->videoPath());
	ui.m_leFontFileSavePath->setText(pDM->fontPath());

	connect(ui.m_pbCancel,SIGNAL(clicked()),this,SLOT(rejectedChanges()));
	connect(ui.m_pbApply,SIGNAL(clicked()),this,SLOT(acceptedChanges()));

	connect(ui.btnDB,SIGNAL(clicked()),this,SLOT(loadDatabasePath()));
	connect(ui.btnVideo,SIGNAL(clicked()),this,SLOT(loadVideoFileSavePath()));
	connect(ui.btnAudio,SIGNAL(clicked()),this,SLOT(loadAudioFileSavePath()));
	connect(ui.btnFont, SIGNAL(clicked()), this, SLOT(loadFontFileSavePath()));
}

RegistrySettings::~RegistrySettings()
{
}

void RegistrySettings::loadDatabasePath()
{
	QString strVal;
	auto *pDM = CDataManage::GetInstance();
	QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
	QString directory = QFileDialog::getExistingDirectory(this,"Select Path for DB File",pDM->DBPath(),options);
	if (!directory.isEmpty())
	{
		QDir dirDB(directory);
		strVal=dirDB.path();
		ui.m_leDBPath->setText(strVal);			
	}
}

void RegistrySettings::loadVideoFileSavePath()
{
	QString strVal;
	auto *pDM = CDataManage::GetInstance();
	QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
	QString directory = QFileDialog::getExistingDirectory(this,"Select Path for Video File save",pDM->videoPath(),options);
	if (!directory.isEmpty())
	{
		QDir dirDB(directory);
		strVal=dirDB.path();
		ui.m_leVideoFileSavePath->setText(strVal);			
	}
}

void RegistrySettings::loadAudioFileSavePath()
{
	QString strVal;
	auto *pDM = CDataManage::GetInstance();
	QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
	QString directory = QFileDialog::getExistingDirectory(this,"Select Path for Audio File save",pDM->audioPath(),options);
	if (!directory.isEmpty())
	{
		QDir dirDB(directory);
		strVal=dirDB.path();
		ui.m_leAudioFileSavePath->setText(strVal);				
	}
}

void RegistrySettings::loadFontFileSavePath()
{
	QString strVal;
	auto *pDM = CDataManage::GetInstance();
	QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
	QString directory = QFileDialog::getExistingDirectory(this, "Select Path for Font File save", pDM->fontPath(), options);
	if (!directory.isEmpty())
	{
		QDir dirDB(directory);
		strVal = dirDB.path();
		ui.m_leFontFileSavePath->setText(strVal);
	}
}

void RegistrySettings::acceptedChanges()
{
	auto *pDM = CDataManage::GetInstance();

	wcscpy(pDM->m_tPathSettings.DATABASE_FILE_PATH,QDir::toNativeSeparators(ui.m_leDBPath->text()).toStdWString().c_str());
	wcscpy(pDM->m_tPathSettings.AUDIO_FILE_SAVE_PATH,QDir::toNativeSeparators(ui.m_leAudioFileSavePath->text()).toStdWString().c_str());
	wcscpy(pDM->m_tPathSettings.VIDEO_FILE_SAVE_PATH,QDir::toNativeSeparators(ui.m_leVideoFileSavePath->text()).toStdWString().c_str());
	wcscpy(pDM->m_tPathSettings.FONT_FILE_SAVE_PATH, QDir::toNativeSeparators(ui.m_leFontFileSavePath->text()).toStdWString().c_str());

	// error
	
	pDM->m_tPathSettings.Save(*pDM->m_pPathStorage.get());
	accept();
}
void RegistrySettings::rejectedChanges()
{
	reject();
}

void RegistrySettings::closeEvent(QCloseEvent *event)
{
	event->ignore();
	rejectedChanges();
}


