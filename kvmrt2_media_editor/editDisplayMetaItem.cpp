#include "editDisplayMetaItem.h"
#include <QDataWidgetMapper>
#include "DataManage.h"
#include "dataModel.h"
#include "MapManage.h"
#include <qdebug.h>

editDisplayMetaItem::editDisplayMetaItem(int nRow, int nSubRow, QWidget *parent)
	: QDialog(parent), m_nRow(nRow), m_nSubRow(nSubRow), m_pItem(0), m_pProp(0)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	initWidgets();
	initWidgetMapper();
	setComboBox();
	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(acceptedChanges()));
	connect(ui.buttonBox, SIGNAL(rejected()), this, SLOT(rejectedChanges()));
	connect(ui.m_pbTagApply, SIGNAL(clicked()), this, SLOT(applyDisplayItem()));
}

editDisplayMetaItem::~editDisplayMetaItem()
{
}

void editDisplayMetaItem::applyDisplayItem()
{
	auto *pTM = CTableManage::GetInstance();
	ui.m_cboImageListIndex->clear();
	ui.m_cboImageListIndex->Initialize(&pTM->VECTOR_CLASS(ImageIndexList), 0, 3, TYPE_TEXT);
	setComboBox();
}

void editDisplayMetaItem::acceptedChanges()
{
	auto *pTM = CTableManage::GetInstance();
	auto *pDM = CDataManage::GetInstance();
	pDM->m_pModDisplayMetaItem->getVector();
	QString strTag = ui.m_cboEditorTag->currentText();
	if (strTag.length())
	{
		int nIndex=ui.m_cboImageListIndex->currentIndex();
		if (nIndex >= 0)
		{
			nIndex=ui.m_cboImageListIndex->itemData(nIndex).toInt();
			DisplayMetaItem *pDMI = (DisplayMetaItem*)pDM->GET_MODEL_CLASS(DisplayMetaItem)->getVector()->at(m_nRow).get();
			pDMI->nRelatedIndex = nIndex;
		}
		m_pProp->submit();
		m_pItem->submit();
		accept();
	}
	else
		reject();
}

void editDisplayMetaItem::rejectedChanges()
{
	reject();
}

void editDisplayMetaItem::setComboBox()
{
	int nTh = 0;
	QString strTag=ui.m_cboEditorTag->currentText();
	if (strTag.length())
	{
		QString strDetailedTag = QString("[") + strTag + QString(":");
		int nCount = ui.m_cboImageListIndex->count();
		while (nTh < nCount)
		{
			QString strTitle = ui.m_cboImageListIndex->itemText(nTh);
			int nLen = strTitle.length();
			if (nLen&&strTitle.at(0) == '['&&strTitle.at(nLen - 1) == ']'&&strTitle.contains(strDetailedTag))
				nTh++;
			else
			{
				ui.m_cboImageListIndex->removeItem(nTh);
				nCount--;
			}
		}
		for (int i = 0; i < nCount; i++)
		{
			ui.m_cboImageListIndex->itemText(i);
		}
	}
}

void editDisplayMetaItem::initWidgets()
{
	auto *pMM = CMapManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();

	ui.m_cboEditorTag->Initialize(&pTM->VECTOR_CLASS(EditorTagTable), 0, 1, TYPE_TEXT);
	ui.m_cboImageListIndex->Initialize(&pTM->VECTOR_CLASS(ImageIndexList), 0, 3, TYPE_TEXT);
	for (auto nit = pMM->m_mVerticalAlign.begin(); nit != pMM->m_mVerticalAlign.end(); nit++)
	{
		ui.m_cboVA->addItem(QString::fromStdWString(nit->second.c_str()), nit->first);
	}
	for (auto nit = pMM->m_mHorizontalAlign.begin(); nit != pMM->m_mHorizontalAlign.end(); nit++)
	{
		ui.m_cboHA->addItem(QString::fromStdWString(nit->second.c_str()), nit->first);
	}
	for (auto nit : pMM->m_mAlignType)
	{
		ui.m_cboCenter->addItem(QString::fromStdWString(nit.second.c_str()), nit.first);
	}


	for (auto nit : pMM->m_mTransistionType)
	{
		ui.m_cboEasing->addItem(QString::fromStdWString(nit.second.c_str()), nit.first);
		ui.m_cboEasing_2->addItem(QString::fromStdWString(nit.second.c_str()), nit.first);
		ui.m_cboEasing_3->addItem(QString::fromStdWString(nit.second.c_str()), nit.first);
	}
	ui.m_ctlWidth->setRange(0.0, 100000.0);
	ui.m_ctlHeight->setRange(0.0, 100000.0);
	//ui.m_cbLimitBound->setLayoutDirection(Qt::RightToLeft);
	ui.m_ctlX->setRange(-100000.0, 100000.0);
	ui.m_ctlY->setRange(-100000.0, 100000.0);
	ui.m_ctlAngle->setRange(0.0, 100000.0);

}

void editDisplayMetaItem::initWidgetMapper()
{
	auto *pDM = CDataManage::GetInstance();
	if (!m_pItem)
	{
		m_pItem = new QDataWidgetMapper(this);
		m_pItem->setModel((QAbstractItemModel*)pDM->GET_MODEL_CLASS(DisplayMetaItem).get());
		m_pItem->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
		//m_pItem->addMapping(ui.m_ctlLineEdit, 2);	//TAG


		m_pItem->addMapping(ui.m_cboEditorTag, 14, "dataIndex");//StationIndex
		m_pItem->addMapping(ui.m_ctlWidth, 5);	//Width
		m_pItem->addMapping(ui.m_ctlHeight, 6);	//Height
		m_pItem->addMapping(ui.m_cboHA, 7, "currentIndex");	//Horizontal Align
		m_pItem->addMapping(ui.m_cboVA, 8,"currentIndex");	//Vertical Align
		m_pItem->addMapping(ui.m_cbLimitBound, 9);
		m_pItem->addMapping(ui.m_ctlZOrder, 12);
		m_pItem->addMapping(ui.m_cboCenter, 13, "currentIndex");	//Origin
		m_pItem->setCurrentIndex(m_nRow);
	}

	if (!m_pProp)
	{
		m_pProp = new QDataWidgetMapper(this);
		m_pProp->setModel((QAbstractItemModel*)pDM->GET_MODEL_CLASS(DisplayMetaItemProp).get());
		m_pProp->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
		m_pProp->addMapping(ui.m_ctlX, 2, "value");	//x
		m_pProp->addMapping(ui.m_ctlY, 3, "value");	//y
		m_pProp->addMapping(ui.m_ctlAngle, 4, "value");	//angle
		m_pProp->addMapping(ui.m_ctlImageColor, 10, "colorValue");	//scalingy

		m_pProp->addMapping(ui.m_cboEasing, 11, "currentIndex");
		m_pProp->addMapping(ui.m_cboEasing_2, 12, "currentIndex");
		m_pProp->addMapping(ui.m_cboEasing_3, 15, "currentIndex");
		m_pProp->addMapping(ui.m_cbVisible, 9);	//Visible
		m_pProp->setCurrentIndex(m_nSubRow);
	}
}