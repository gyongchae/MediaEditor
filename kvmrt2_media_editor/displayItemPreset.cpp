#include "displayItemPreset.h"
#include "dataManage.h"
#include "TableManage.h"
#include "MapManage.h"
#include <QDebug>
#include <qbuttongroup.h>

displayItemPreset::displayItemPreset(int nRow, QWidget *parent)
	: QDialog(parent), m_nRow(nRow), m_pWidgetMapper(NULL)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	auto *pDM = CDataManage::GetInstance();
	auto *pMM = CMapManage::GetInstance();

	ui.m_spWidth->setRange(80, 1920);
	ui.m_spHeight->setRange(80, 1080);
	ui.m_spDuration->setRange(1, 30);

	for (auto it = pMM->m_mDisplayPoolType.begin(); it != pMM->m_mDisplayPoolType.end(); ++it)
	{
		ui.comboDisplayType->addItem(QString::number(it->first));
		ui.comboDisplayType->setItemData(it->first, QString::fromStdWString(it->second), Qt::DisplayRole);
	}
	
	for (auto it = pMM->m_mDateTimeDisplay.begin(); it != pMM->m_mDateTimeDisplay.end(); ++it)
	{
		ui.comboDateTimeDisplay->addItem(QString::number(it->first));
		ui.comboDateTimeDisplay->setItemData(it->first, QString::fromStdWString(it->second), Qt::DisplayRole);
	}

	if (!m_pWidgetMapper)
	{
		m_pWidgetMapper = new QDataWidgetMapper(this);
		m_pWidgetMapper->setModel((QAbstractItemModel*)pDM->m_pModDisplayItemPool.get());
		m_pWidgetMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
		m_pWidgetMapper->addMapping(ui.m_leDescription, 1,"text");
		m_pWidgetMapper->addMapping(ui.m_spWidth, 2);
		m_pWidgetMapper->addMapping(ui.m_spHeight, 3);
		m_pWidgetMapper->addMapping(ui.m_spDuration, 4);
		m_pWidgetMapper->addMapping(ui.comboDisplayType, 7, "currentIndex");
		m_pWidgetMapper->addMapping(ui.comboDateTimeDisplay, 8, "currentIndex");
		m_pWidgetMapper->setCurrentIndex(m_nRow);
	}

	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(acceptedChanges()));
	connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(rejectedChanges()));

	// spin box init value
	ui.m_spWidth->setValue(200);
	ui.m_spHeight->setValue(200);
}

displayItemPreset::~displayItemPreset()
{
}


void displayItemPreset::acceptedChanges()
{
	auto *pTM = CTableManage::GetInstance();
	m_pWidgetMapper->submit();
	accept();
}

void displayItemPreset::rejectedChanges()
{
	reject();
}