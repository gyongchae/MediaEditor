#include "registrysettings.h"
#include <QtGui>
#include "DataManage.h"
#include <qdebug.h>
#include "tableViewHelper.h"
#include "MapManage.h"
#include "TableManage.h"
#include "dataModel.h"
#include "DefineMode.h"

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

	initOPDataVersion();
	initVersionSpinBox();

	connect(ui.m_pbCancel,SIGNAL(clicked()),this,SLOT(rejectedChanges()));
	connect(ui.m_pbApply,SIGNAL(clicked()),this,SLOT(acceptedChanges()));

	connect(ui.btnDB,SIGNAL(clicked()),this,SLOT(loadDatabasePath()));
	connect(ui.btnVideo,SIGNAL(clicked()),this,SLOT(loadVideoFileSavePath()));
	connect(ui.btnAudio,SIGNAL(clicked()),this,SLOT(loadAudioFileSavePath()));
	connect(ui.btnFont, SIGNAL(clicked()), this, SLOT(loadFontFileSavePath()));

	connect(ui.sbVer1, SIGNAL(valueChanged(int)), this, SLOT(changeDataVersion(int)));
	connect(ui.sbVer2, SIGNAL(valueChanged(int)), this, SLOT(changeDataVersion(int)));
	connect(ui.sbVer3, SIGNAL(valueChanged(int)), this, SLOT(changeDataVersion(int)));

	if (OFFICIAL_RELEASE == true)
	{
		ui.gbFilePath->setVisible(false);
		ui.m_tblOPDataVersion->setVisible(false);
		this->adjustSize();
	}
}

RegistrySettings::~RegistrySettings()
{
}

void RegistrySettings::initVersionSpinBox()
{
	auto *pTM = CTableManage::GetInstance();
	auto *pDM = CDataManage::GetInstance();
	
	QModelIndex topLeft = ui.m_tblOPDataVersion->model()->index(0, 0);
	
	int ver1 = pDM->m_pModOPDataVersion->data(topLeft.sibling(0, 2), Qt::DisplayRole).toInt();
	int ver2 = pDM->m_pModOPDataVersion->data(topLeft.sibling(0, 3), Qt::DisplayRole).toInt();
	int ver3 = pDM->m_pModOPDataVersion->data(topLeft.sibling(0, 4), Qt::DisplayRole).toInt();

	// version 1, 2, 3는 합쳐서 1바이트
	// version 1(2bits), 2(3bits), 3(3bits)는 합쳐서 1바이트
	// 가능한 범위
	// version1 0~3
	// version2 0~7
	// version3 0~7

	ui.sbVer1->setRange(0, 3);
	ui.sbVer2->setRange(0, 7);
	ui.sbVer3->setRange(0, 7);

	ui.sbVer1->setValue(ver1);
	ui.sbVer2->setValue(ver2);
	ui.sbVer3->setValue(ver3);

	QString strVer = (QString("0%1.0%2.0%3")
		.arg(ui.sbVer1->value())
		.arg(ui.sbVer2->value())
		.arg(ui.sbVer3->value())
		);

	pDM->m_pModOPDataVersion->setData(topLeft.sibling(0, 1), strVer, Qt::EditRole);
}

bool RegistrySettings::initOPDataVersion()
{
	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();

	ui.m_tblOPDataVersion->setModel((QAbstractItemModel*)pDM->m_pModOPDataVersion.get());
	ui.m_tblOPDataVersion->setSelectionMode(QAbstractItemView::NoSelection);

	QHeaderView *header = ui.m_tblOPDataVersion->horizontalHeader();
	header->resizeSections(QHeaderView::ResizeToContents);
	header->setStretchLastSection(true);

	if (pDM->m_pModOPDataVersion->rowCount() != 1)
	{
		if (pDM->m_pModOPDataVersion->rowCount() > 1)
		{
			pDM->m_pModOPDataVersion->removeRows(0, pDM->m_pModOPDataVersion->rowCount());
		}

		ui.m_tblOPDataVersion->model()->insertRows(0, 1);
	}

	return false;
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

void RegistrySettings::changeDataVersion(int val)
{
	auto *pDM = CDataManage::GetInstance();
	QModelIndex topLeft = ui.m_tblOPDataVersion->model()->index(0, 0);

	pDM->m_pModOPDataVersion->setData(topLeft.sibling(0, 2), ui.sbVer1->value(), Qt::EditRole);
	pDM->m_pModOPDataVersion->setData(topLeft.sibling(0, 3), ui.sbVer2->value(), Qt::EditRole);
	pDM->m_pModOPDataVersion->setData(topLeft.sibling(0, 4), ui.sbVer3->value(), Qt::EditRole);

	QString strVer = (QString("0%1.0%2.0%3")
		.arg(ui.sbVer1->value())
		.arg(ui.sbVer2->value())
		.arg(ui.sbVer3->value())
		);

	pDM->m_pModOPDataVersion->setData(topLeft.sibling(0, 1), strVer, Qt::EditRole);
}

void RegistrySettings::acceptedChanges()
{
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
