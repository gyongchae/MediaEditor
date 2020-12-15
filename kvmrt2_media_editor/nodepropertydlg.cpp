#include "nodepropertydlg.h"
#include "TableManage.h"
#include "MapManage.h"
#include "DataManage.h"
#include "dataModel.h"
#include <qdatawidgetmapper.h>

NodePropertyDlg::NodePropertyDlg(propertytype type, int row, QString title, QWidget *parent)
	: QDialog(parent)
	, m_propType(type)
	, m_row(row)
	, m_title(title)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	auto *pDM = CDataManage::GetInstance();

	m_pMapper = new QDataWidgetMapper(this);
	m_pMapper->setModel((QAbstractItemModel*)pDM->GET_MODEL_CLASS(LineMapNode).get());

	initMappingColumn(type);
	initUI();
	initDisplayReferType();
	initWidgetMapper(row);

	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(acceptedChanges()));
	connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(rejectedChanges()));
	connect(ui.btnApply, SIGNAL(clicked()), parent, SLOT(update()));
	connect(ui.btnCopyAll, SIGNAL(clicked()), this, SLOT(copyPassedDataToAll()));

	setWindowTitle(title);
}

NodePropertyDlg::~NodePropertyDlg()
{
}

void NodePropertyDlg::initUI()
{
	auto *pTM = CTableManage::GetInstance();
	auto *pMM = CMapManage::GetInstance();
	
	ui.comboDisplayPool_P->Initialize(&pTM->VECTOR_CLASS(DisplayItemPool), 0, 1, TYPE_TEXT);
	ui.comboDisplayPool_T->Initialize(&pTM->VECTOR_CLASS(DisplayItemPool), 0, 1, TYPE_TEXT);
	ui.comboDisplayPool_R->Initialize(&pTM->VECTOR_CLASS(DisplayItemPool), 0, 1, TYPE_TEXT);

	ui.comboImgListPool_P->Initialize(&pTM->VECTOR_CLASS(ImageIndexList), 0, 3, TYPE_TEXT);
	ui.comboImgListPool_T->Initialize(&pTM->VECTOR_CLASS(ImageIndexList), 0, 3, TYPE_TEXT);
	ui.comboImgListPool_R->Initialize(&pTM->VECTOR_CLASS(ImageIndexList), 0, 3, TYPE_TEXT);

	ui.comboStationInfo->Initialize(&pTM->VECTOR_CLASS(StationInformation), 0, 2, TYPE_TEXT);

	for (auto nit : pMM->m_mAlignType)
	{
		ui.comboPivot_P->addItem(QString::fromStdWString(nit.second.c_str()), nit.first);
		ui.comboPivot_T->addItem(QString::fromStdWString(nit.second.c_str()), nit.first);
		ui.comboPivot_R->addItem(QString::fromStdWString(nit.second.c_str()), nit.first);
	}

	ui.comboPivot_P->setCurrentIndex(5); // {5,L"CENTER MIDDLE"},
	ui.comboPivot_T->setCurrentIndex(5); // {5,L"CENTER MIDDLE"},
	ui.comboPivot_R->setCurrentIndex(5); // {5,L"CENTER MIDDLE"},
	ui.comboPivot_P->setEnabled(false);
	ui.comboPivot_T->setEnabled(false);
	ui.comboPivot_R->setEnabled(false);

	for (auto nit : pMM->m_mDisplayItemType)
	{
		ui.comboType_P->addItem(QString::fromStdWString(nit.second.c_str()), nit.first);
		ui.comboType_T->addItem(QString::fromStdWString(nit.second.c_str()), nit.first);
		ui.comboType_R->addItem(QString::fromStdWString(nit.second.c_str()), nit.first);
	}

	connect(ui.comboType_P, SIGNAL(currentIndexChanged(int)), this, SLOT(typeChanged(int)));
	connect(ui.comboType_T, SIGNAL(currentIndexChanged(int)), this, SLOT(typeChanged(int)));
	connect(ui.comboType_R, SIGNAL(currentIndexChanged(int)), this, SLOT(typeChanged(int)));

	// hide ui widget
	switch (m_propType)
	{
	case NodePropertyDlg::propertytype::NODE:
		ui.chkUseDefaultSpot_P->setHidden(true);
		ui.chkUseDefaultSpot_T->setHidden(true);
		ui.chkUseDefaultSpot_R->setHidden(true);
		break;
	case NodePropertyDlg::propertytype::SPOT:
		ui.spAngle_P->setHidden(true);
		ui.spAngle_T->setHidden(true);
		ui.spAngle_R->setHidden(true);
		ui.labelAngle_P->setHidden(true);
		ui.labelAngle_T->setHidden(true);
		ui.labelAngle_R->setHidden(true);
		ui.comboStationInfo->setHidden(true);
		ui.labelStationInfo->setHidden(true);
		break;
	default:
		break;
	}
}

void NodePropertyDlg::initMappingColumn(propertytype type)
{
	switch (type)
	{
	case NodePropertyDlg::propertytype::NODE:
		m_stationIndex = 6;
		m_tDBColumn[Pa].offsetX = 7;
		m_tDBColumn[Ta].offsetX = 14;
		m_tDBColumn[Re].offsetX = 21;
		m_tDBColumn[Pa].offsetY = 8;
		m_tDBColumn[Ta].offsetY = 15;
		m_tDBColumn[Re].offsetY = 22;
		m_tDBColumn[Pa].pivot = 9;
		m_tDBColumn[Ta].pivot = 16;
		m_tDBColumn[Re].pivot = 23;
		m_tDBColumn[Pa].angle = 10;
		m_tDBColumn[Ta].angle = 17;
		m_tDBColumn[Re].angle = 24;
		m_tDBColumn[Pa].imgRefType = 11;
		m_tDBColumn[Ta].imgRefType = 18;
		m_tDBColumn[Re].imgRefType = 25;
		m_tDBColumn[Pa].imgIndex = 13;
		m_tDBColumn[Ta].imgIndex = 20;
		m_tDBColumn[Re].imgIndex = 27;
		break;
	case NodePropertyDlg::propertytype::SPOT:
		m_tDBColumn[Pa].offsetX = 28;
		m_tDBColumn[Ta].offsetX = 33;
		m_tDBColumn[Re].offsetX = 38;
		m_tDBColumn[Pa].offsetY = 29;
		m_tDBColumn[Ta].offsetY = 34;
		m_tDBColumn[Re].offsetY = 39;
		m_tDBColumn[Pa].pivot = 30;
		m_tDBColumn[Ta].pivot = 35;
		m_tDBColumn[Re].pivot = 40;
		m_tDBColumn[Pa].useDefaultSpotImage = 31;
		m_tDBColumn[Ta].useDefaultSpotImage = 36;
		m_tDBColumn[Re].useDefaultSpotImage = 41;
		m_tDBColumn[Pa].imgRefType = 43;
		m_tDBColumn[Ta].imgRefType = 44;
		m_tDBColumn[Re].imgRefType = 45;
		m_tDBColumn[Pa].imgIndex = 32;
		m_tDBColumn[Ta].imgIndex = 37;
		m_tDBColumn[Re].imgIndex = 42;
		break;
	default:
		break;
	}
}

void NodePropertyDlg::initWidgetMapper(int row)
{
	m_pMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
	
	m_pMapper->addMapping(ui.spPosX_P, m_tDBColumn[Pa].offsetX);
	m_pMapper->addMapping(ui.spPosX_T, m_tDBColumn[Ta].offsetX);
	m_pMapper->addMapping(ui.spPosX_R, m_tDBColumn[Re].offsetX);

	m_pMapper->addMapping(ui.spPosY_P, m_tDBColumn[Pa].offsetY);
	m_pMapper->addMapping(ui.spPosY_T, m_tDBColumn[Ta].offsetY);
	m_pMapper->addMapping(ui.spPosY_R, m_tDBColumn[Re].offsetY);

	m_pMapper->addMapping(ui.comboPivot_P, m_tDBColumn[Pa].pivot, "currentIndex");
	m_pMapper->addMapping(ui.comboPivot_T, m_tDBColumn[Ta].pivot, "currentIndex");
	m_pMapper->addMapping(ui.comboPivot_R, m_tDBColumn[Re].pivot, "currentIndex");

	m_pMapper->addMapping(ui.comboType_P, m_tDBColumn[Pa].imgRefType, "currentIndex");
	m_pMapper->addMapping(ui.comboType_T, m_tDBColumn[Ta].imgRefType, "currentIndex");
	m_pMapper->addMapping(ui.comboType_R, m_tDBColumn[Re].imgRefType, "currentIndex");

	switch (m_propType)
	{
	case NodePropertyDlg::propertytype::NODE:
		// only node
		m_pMapper->addMapping(ui.comboStationInfo, m_stationIndex, "dataIndex");//StationIndex
		m_pMapper->addMapping(ui.spAngle_P, m_tDBColumn[Pa].angle);
		m_pMapper->addMapping(ui.spAngle_T, m_tDBColumn[Ta].angle);
		m_pMapper->addMapping(ui.spAngle_R, m_tDBColumn[Re].angle);
		break;
	case NodePropertyDlg::propertytype::SPOT:
		// only spot
		m_pMapper->addMapping(ui.chkUseDefaultSpot_P, m_tDBColumn[Pa].useDefaultSpotImage);
		m_pMapper->addMapping(ui.chkUseDefaultSpot_T, m_tDBColumn[Ta].useDefaultSpotImage);
		m_pMapper->addMapping(ui.chkUseDefaultSpot_R, m_tDBColumn[Re].useDefaultSpotImage);
		break;
	default:
		break;
	}
	
	m_pMapper->setCurrentIndex(row);

}

void NodePropertyDlg::initDisplayReferType()
{
	auto *pTM = CTableManage::GetInstance();
	auto *pDM = CDataManage::GetInstance();
	
	auto pVEC = pDM->GET_MODEL_CLASS(LineMapNode)->getVector();
	auto pLMN = (LineMapNode*)pVEC->at(m_row).get();
	switch (m_propType)
	{
	case NodePropertyDlg::propertytype::NODE:
		setItemType(pLMN->nType[Pa], m_tDBColumn[Pa].imgIndex, ui.comboImgListPool_P, ui.comboDisplayPool_P);
		setItemType(pLMN->nType[Ta], m_tDBColumn[Ta].imgIndex, ui.comboImgListPool_T, ui.comboDisplayPool_T);
		setItemType(pLMN->nType[Re], m_tDBColumn[Re].imgIndex, ui.comboImgListPool_R, ui.comboDisplayPool_R);
		break;
	case NodePropertyDlg::propertytype::SPOT:
		setItemType(pLMN->nSType[Pa], m_tDBColumn[Pa].imgIndex, ui.comboImgListPool_P, ui.comboDisplayPool_P);
		setItemType(pLMN->nSType[Ta], m_tDBColumn[Ta].imgIndex, ui.comboImgListPool_T, ui.comboDisplayPool_T);
		setItemType(pLMN->nSType[Re], m_tDBColumn[Re].imgIndex, ui.comboImgListPool_R, ui.comboDisplayPool_R);
		break;
	default:
		break;
	}
}

void NodePropertyDlg::setItemType(int index, int column, QIndexComboBox * comboImgListPool, QIndexComboBox * comboDisplayPool)
{
	switch (index)
	{
	case 0: // display pool
		comboImgListPool->setEnabled(false);
		comboDisplayPool->setEnabled(true);
		m_pMapper->removeMapping(comboImgListPool);
		m_pMapper->addMapping(comboDisplayPool, column, "dataIndex");
		break;
	case 1: // image list pool
		comboImgListPool->setEnabled(true);
		comboDisplayPool->setEnabled(false);
		m_pMapper->removeMapping(comboDisplayPool);
		m_pMapper->addMapping(comboImgListPool, column, "dataIndex");
		break;
	default:
		break;
	}
}

void NodePropertyDlg::acceptedChanges()
{
	m_pMapper->submit();
	accept();
}

void NodePropertyDlg::rejectedChanges()
{
	reject();
}

void NodePropertyDlg::typeChanged(int index)
{
	if (sender() == ui.comboType_P)
		setItemType(index, m_tDBColumn[Pa].imgIndex, ui.comboImgListPool_P, ui.comboDisplayPool_P);
	else if(sender() == ui.comboType_T)
		setItemType(index, m_tDBColumn[Ta].imgIndex, ui.comboImgListPool_T, ui.comboDisplayPool_T);
	else if(sender() == ui.comboType_R)
		setItemType(index, m_tDBColumn[Re].imgIndex, ui.comboImgListPool_R, ui.comboDisplayPool_R);
}

void NodePropertyDlg::copyPassedDataToAll()
{
	// target / remain property copied from passed property
	ui.spPosX_T->setValue(ui.spPosX_P->value());
	ui.spPosX_R->setValue(ui.spPosX_P->value());
	ui.spPosY_T->setValue(ui.spPosY_P->value());
	ui.spPosY_R->setValue(ui.spPosY_P->value());
	ui.spAngle_T->setValue(ui.spAngle_P->value());
	ui.spAngle_R->setValue(ui.spAngle_P->value());
	ui.comboPivot_T->setCurrentIndex(ui.comboPivot_P->currentIndex());
	ui.comboPivot_R->setCurrentIndex(ui.comboPivot_P->currentIndex());
	ui.comboType_T->setCurrentIndex(ui.comboType_P->currentIndex());
	ui.comboType_R->setCurrentIndex(ui.comboType_P->currentIndex());
	ui.comboDisplayPool_T->setCurrentIndex(ui.comboDisplayPool_P->currentIndex());
	ui.comboDisplayPool_R->setCurrentIndex(ui.comboDisplayPool_P->currentIndex());
	ui.comboImgListPool_T->setCurrentIndex(ui.comboImgListPool_P->currentIndex());
	ui.comboImgListPool_R->setCurrentIndex(ui.comboImgListPool_P->currentIndex());
	ui.chkUseDefaultSpot_T->setChecked(ui.chkUseDefaultSpot_P->isChecked());
	ui.chkUseDefaultSpot_R->setChecked(ui.chkUseDefaultSpot_P->isChecked());
}
