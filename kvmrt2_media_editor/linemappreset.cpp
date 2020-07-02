#include "linemappreset.h"
#include "dataManage.h"
#include "TileMapSupport.h"
#include "TableManage.h"
#include <QDebug>


LineMapPreset::LineMapPreset(int nRow, QWidget *parent)
	: QDialog(parent), m_nRow(nRow), m_pWidgetMapper(NULL)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	auto *pDM = CDataManage::GetInstance();

	if (!m_pWidgetMapper)
	{
		m_pWidgetMapper = new QDataWidgetMapper(this);
		m_pWidgetMapper->setModel((QAbstractItemModel*)pDM->m_pModLineMapPool.get());
		m_pWidgetMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
		m_pWidgetMapper->addMapping(ui.editTitle, 1);
		m_pWidgetMapper->addMapping(ui.m_cbTileSize, 2);
		m_pWidgetMapper->addMapping(ui.m_cbLineThick, 3);
		m_pWidgetMapper->addMapping(ui.m_cbMapWidth, 6);
		m_pWidgetMapper->addMapping(ui.m_cbMapHeight, 7);
		m_pWidgetMapper->setCurrentIndex(m_nRow);
	}

	ui.m_cbTileSize->setCurrentIndex(0);
	ui.m_cbLineThick->setCurrentIndex(0);
	ui.m_cbMapWidth->setCurrentIndex(0);
	ui.m_cbMapHeight->setCurrentIndex(0);

	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(acceptedChanges()));
	connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(rejectedChanges()));
}

LineMapPreset::~LineMapPreset()
{
}

void LineMapPreset::acceptedChanges()
{
	int nWidth, nHeight;
	auto *pTM = CTableManage::GetInstance();
	CTileMapSupport *pTMS = CTileMapSupport::GetInstance();
	m_pWidgetMapper->submit();
	LineMapPool *pLMP = (LineMapPool *)pTM->m_vLineMapPool[m_nRow].get();
	pLMP->pByte = pTMS->GenerateTileBitmap(pLMP->nProp, pLMP->nWidth, &nWidth, &nHeight);
	pLMP->pByteSpot = pTMS->GenerateStationSpot(pLMP->nWidth);
	pLMP->nSizeSpot = pLMP->nWidth*pLMP->nWidth * 4;
	pLMP->nSize = nWidth*nHeight * 4;
	accept();
}

void LineMapPreset::rejectedChanges()
{
	reject();
}
