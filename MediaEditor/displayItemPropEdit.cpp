#include "displayItemPropEdit.h"
#include <QDataWidgetMapper>
#include "DataManage.h"
#include "MapManage.h"
#include <qdebug.h>

displayItemPropEdit::displayItemPropEdit(int nItem, int nProp, QWidget *parent)
	: QDialog(parent), m_pItem(NULL), m_pProp(NULL)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	auto *pDM = CDataManage::GetInstance();
	auto *pMM = CMapManage::GetInstance();
	if (!m_pItem)
	{
		for (auto nit : pMM->m_mAlignType)
		{
			ui.m_cboPivot->addItem(QString::fromStdWString(nit.second.c_str()), nit.first);
		}

		for (auto nit : pMM->m_mTransistionType)
		{
			ui.m_cboEasingPos->addItem(QString::fromStdWString(nit.second.c_str()), nit.first);
			ui.m_cboEasingAngle->addItem(QString::fromStdWString(nit.second.c_str()), nit.first);
			ui.m_cboEasingColor->addItem(QString::fromStdWString(nit.second.c_str()), nit.first);
			ui.m_cboEasingScale->addItem(QString::fromStdWString(nit.second.c_str()), nit.first);
		}
		m_pItem = new QDataWidgetMapper(this);
		m_pItem->setModel((QAbstractItemModel*)pDM->m_pModDisplayItem.get());
		m_pItem->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
		ui.m_ctlZOrder->setRange(0.0, 100000.0);
		m_pItem->addMapping(ui.m_ctlZOrder, 7);	//zorder
		m_pItem->addMapping(ui.m_cboPivot, 8, "currentIndex");	//Origin
		m_pItem->setCurrentIndex(nItem);
	}

	if (!m_pProp)
	{
		m_pProp = new QDataWidgetMapper(this);
		m_pProp->setModel((QAbstractItemModel*)pDM->m_pModDisplayProp.get());
		m_pProp->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
		ui.m_ctlX->setRange(-100000.0, 100000.0);
		ui.m_ctlY->setRange(-100000.0, 100000.0);
		ui.m_ctlAngle->setRange(-100000.0, 100000.0);
		ui.m_ctlScalingX->setRange(-100000.0, 100000.0);
		ui.m_ctlScalingY->setRange(-100000.0, 100000.0);
		m_pProp->addMapping(ui.m_ctlX, 2, "value");	//x
		m_pProp->addMapping(ui.m_ctlY, 3, "value");	//y
		m_pProp->addMapping(ui.m_ctlAngle, 4, "value");	//angle
		m_pProp->addMapping(ui.m_ctlScalingX, 5, "value");	//scalingx
		m_pProp->addMapping(ui.m_ctlScalingY, 6, "value");	//scalingy
		m_pProp->addMapping(ui.m_ctlImageColor, 10, "colorValue");	//scalingy
		m_pProp->addMapping(ui.m_cboEasingPos, 11,"currentIndex");
		m_pProp->addMapping(ui.m_cboEasingAngle, 12, "currentIndex");
		m_pProp->addMapping(ui.m_cboEasingScale, 13, "currentIndex");
		m_pProp->addMapping(ui.m_cboEasingColor, 15, "currentIndex");
		m_pProp->addMapping(ui.m_cbVisible, 9);	//Visible
		m_pProp->setCurrentIndex(nProp);
	}

	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(acceptedChanges()));
	connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(rejectedChanges()));

}

displayItemPropEdit::~displayItemPropEdit()
{
}

void displayItemPropEdit::acceptedChanges()
{
	auto *pTM = CTableManage::GetInstance();
	m_pProp->submit();
	m_pItem->submit();
	accept();
}

void displayItemPropEdit::rejectedChanges()
{
	reject();
}


