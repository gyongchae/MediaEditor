#include "QLineMapEdit.h"
#include "TileMapSupport.h"
#include "TableManage.h"
#include "DataManage.h"
#include "dataModel.h"
#include "TableviewHelper.h"
#include "QGLESLineMapCanvas.h"
#include <qdebug.h>
#include "DefineMode.h"

QLineMapEdit::QLineMapEdit(int nIndexRow, QWidget *parent)
	: QDialog(parent),m_nRow(nIndexRow)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	
	auto *pDM = CDataManage::GetInstance();
	auto *pTMS = CTileMapSupport::GetInstance();
	auto *pLMP=(LineMapPool*)pDM->GET_MODEL_CLASS(LineMapPool)->getVector()->at(nIndexRow).get();
	
	m_nTileSize = pLMP->nProp;
	m_nLineThick = pLMP->nWidth;
	m_ScreenSize = QSize(pLMP->nWholeWidth, pLMP->nWholeHeight);
	pTMS->GenerateTilePath(m_nTileSize, m_nLineThick);

	initModels(nIndexRow);
	initWidgets();
	initMapper();

	CALL_INIT_FUNCTION(LineMapLink);
	CALL_INIT_FUNCTION(LineMapNode);
	CALL_INIT_FUNCTION(DisplayItemPool);
	CALL_INIT_FUNCTION(ImageIndexList);

	connect(ui.btnClose, SIGNAL(clicked()), this, SLOT(acceptedChanges()));

	if (RELEASE_MODE)
	{
		ui.m_ctlArrow->setVisible(false);
		ui.m_ctlImageList->setVisible(false);
	}
}

QLineMapEdit::~QLineMapEdit()
{
}

void QLineMapEdit::initModels(int nRow)
{
	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();
	pDM->GET_MODEL_CLASS(LineMapLink)->setVectors(&pTM->VECTOR_CLASS(LineMapPool)[nRow]->m_vChildItem[0].vSQLData, &pTM->VECTOR_CLASS(LineMapPool)[nRow]->m_vChildItem[0].vSQLDataDelItems, pTM->VECTOR_CLASS(LineMapPool)[nRow].get()->GetIndex());
	pDM->GET_MODEL_CLASS(LineMapNode)->setVectors(&pTM->VECTOR_CLASS(LineMapPool)[nRow]->m_vChildItem[2].vSQLData, &pTM->VECTOR_CLASS(LineMapPool)[nRow]->m_vChildItem[2].vSQLDataDelItems, pTM->VECTOR_CLASS(LineMapPool)[nRow].get()->GetIndex());
	pDM->GET_MODEL_CLASS(LineMapArrowTexture)->setVectors(&pTM->VECTOR_CLASS(LineMapPool)[nRow]->m_vChildItem[3].vSQLData, &pTM->VECTOR_CLASS(LineMapPool)[nRow]->m_vChildItem[3].vSQLDataDelItems, pTM->VECTOR_CLASS(LineMapPool)[nRow].get()->GetIndex());
	pDM->GET_MODEL_CLASS(LineMapDisplayItem)->setVectors(&pTM->VECTOR_CLASS(LineMapPool)[nRow]->m_vChildItem[4].vSQLData, &pTM->VECTOR_CLASS(LineMapPool)[nRow]->m_vChildItem[4].vSQLDataDelItems, pTM->VECTOR_CLASS(LineMapPool)[nRow].get()->GetIndex());
}

void QLineMapEdit::resizeEvent(QResizeEvent *)
{
	ui.openGLWidget->setFixedSize(m_ScreenSize);
}

void QLineMapEdit::initWidgets()
{
	ui.openGLWidget->initxxx(m_nRow);

	m_editGroup = new QButtonGroup(this);
	m_editGroup->addButton(ui.m_ctlTile, 1);
	m_editGroup->addButton(ui.m_ctlNode, 2);
	m_editGroup->addButton(ui.m_ctlArrow, 3);
	m_editGroup->addButton(ui.m_ctlDisplayItem, 4);
	m_editGroup->addButton(ui.m_ctlImageList, 5);
	m_editGroup->setExclusive(true);
	
	connect(m_editGroup, SIGNAL(buttonClicked(int)), ui.openGLWidget, SLOT(setCurrentEditMode(int)));
	connect(m_editGroup, SIGNAL(buttonClicked(int)), ui.m_ctlStackedWidget, SLOT(setCurrentIndex(int)));

	connect(ui.m_pbApplyColor, SIGNAL(clicked()), this, SLOT(colorApply()));
	connect(ui.m_pbApplyArrowOffset, SIGNAL(clicked()), this, SLOT(arrowOffsetApply()));
	
	ui.m_ctlTile->setChecked(true);
	ui.m_ctlStackedWidget->setCurrentIndex(1);

	ui.editTileSize->setReadOnly(true);
	ui.editLineThick->setReadOnly(true);

	// node data copy
	connect(ui.btnCopyProp, SIGNAL(clicked()), this, SLOT(copyNodeProperty()));
	connect(ui.btnPasteNode, SIGNAL(clicked()), this, SLOT(pasteNodeProperty()));
	connect(ui.btnPasteSpot, SIGNAL(clicked()), this, SLOT(pasteSpotProperty()));

	m_showSpotGroup = new QButtonGroup(this);
	m_showSpotGroup->addButton(ui.btnShowSpotCustom, 0);
	m_showSpotGroup->addButton(ui.btnShowSpotDefault, 1);
	
	connect(m_showSpotGroup, SIGNAL(buttonClicked(int)),
		this, SLOT(clickedSetSpotButton(int)));
}

IMPLEMENT_INIT_FUNCTION_FOR_CLASS(QLineMapEdit, LineMapLink)
{
	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();
	SET_MODEL_FOR_TABLE_VIEW(LineMapLink, pDM);
	INSTALL_EVENT_FILTER(LineMapLink);
	QHeaderView *header = GET_TABLE(LineMapLink)->horizontalHeader();
	header->resizeSections(QHeaderView::ResizeToContents);
	SET_SELECTION_BEHAVIOR(LineMapLink, QAbstractItemView::SelectRows);
	SET_SELECTION_MODE(LineMapLink, QAbstractItemView::SingleSelection);
	SET_DRAG_AND_DROP_ENABLED(LineMapLink);
	return false;
}

IMPLEMENT_INIT_FUNCTION_FOR_CLASS(QLineMapEdit, LineMapNode)
{
	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();
	SET_MODEL_FOR_TABLE_VIEW(LineMapNode, pDM);
	INSTALL_EVENT_FILTER(LineMapNode);
	QHeaderView *header = GET_TABLE(LineMapNode)->horizontalHeader();
	header->resizeSections(QHeaderView::ResizeToContents);
	SET_SELECTION_BEHAVIOR(LineMapNode, QAbstractItemView::SelectRows);
	SET_SELECTION_MODE(LineMapNode, QAbstractItemView::SingleSelection);
	SET_DRAG_AND_DROP_ENABLED(LineMapNode);
	return false;
}

IMPLEMENT_INIT_FUNCTION_FOR_CLASS(QLineMapEdit, DisplayItemPool)
{
	auto *pDM = CDataManage::GetInstance();
	SET_MODEL_FOR_TABLE_VIEW(DisplayItemPool, pDM);
	INSTALL_EVENT_FILTER(DisplayItemPool);
	SET_SELECTION_BEHAVIOR(DisplayItemPool, QAbstractItemView::SelectRows);
	SET_SELECTION_MODE(DisplayItemPool, QAbstractItemView::SingleSelection);
	SET_EDIT_TRIGGERS(DisplayItemPool, QAbstractItemView::NoEditTriggers);

	ui.m_tblDisplayItemPool->setDragEnabled(true);
	ui.m_tblDisplayItemPool->setAcceptDrops(true);
	ui.m_tblDisplayItemPool->setDropIndicatorShown(false);
	ui.m_tblDisplayItemPool->setDragDropMode(QAbstractItemView::DragOnly);

	QHeaderView *header = GET_TABLE(DisplayItemPool)->horizontalHeader();
	header->resizeSections(QHeaderView::ResizeToContents);

	return false;
}
IMPLEMENT_INIT_FUNCTION_FOR_CLASS(QLineMapEdit, ImageIndexList)
{
	auto *pDM = CDataManage::GetInstance();
	SET_MODEL_FOR_TABLE_VIEW(ImageIndexList, pDM);
	INSTALL_EVENT_FILTER(ImageIndexList);
	SET_SELECTION_BEHAVIOR(ImageIndexList, QAbstractItemView::SelectRows);
	SET_SELECTION_MODE(ImageIndexList, QAbstractItemView::SingleSelection);
	SET_EDIT_TRIGGERS(ImageIndexList, QAbstractItemView::NoEditTriggers);

	ui.m_tblImageIndexList->setDragEnabled(true);
	ui.m_tblImageIndexList->setAcceptDrops(true);
	ui.m_tblImageIndexList->setDropIndicatorShown(false);
	ui.m_tblImageIndexList->setDragDropMode(QAbstractItemView::DragOnly);

	QHeaderView *header = GET_TABLE(ImageIndexList)->horizontalHeader();
	header->resizeSections(QHeaderView::ResizeToContents);

	return false;
}

void QLineMapEdit::acceptedChanges()
{
	auto *pTM = CTableManage::GetInstance();
	m_pLineMapMapper->submit();
	accept();
}

void QLineMapEdit::copyNodeProperty()
{
	auto *pDM = CDataManage::GetInstance();

	int totalRows = GET_TABLE_MODEL(pDM, LineMapNode)->rowCount();

	QModelIndex fromIndex = GET_TABLE(LineMapNode)->currentIndex();
	
	if (fromIndex.isValid())
	{
		m_selectedRow = fromIndex.row();
		std::shared_ptr<dataModel> model = pDM->GET_MODEL_CLASS(LineMapNode);
		m_pCopyLineMapNode = pDM->GET_MODEL_CLASS(LineMapNode)->getVector()->at(fromIndex.row());

		m_pCopyLineMapNode.get()->GetData(7, &m_tNode.nOffsetX[0]);
		m_pCopyLineMapNode.get()->GetData(8, &m_tNode.nOffsetY[0]);
		m_pCopyLineMapNode.get()->GetData(9, &m_tNode.nCenterSpot[0]);
		m_pCopyLineMapNode.get()->GetData(10, &m_tNode.nRotAngle[0]);
		m_pCopyLineMapNode.get()->GetData(11, &m_tNode.nType[0]);
		m_pCopyLineMapNode.get()->GetData(12, &m_tNode.nColored[0]);
		m_pCopyLineMapNode.get()->GetData(13, &m_tNode.nRelatedIndex[0]);

		m_pCopyLineMapNode.get()->GetData(14, &m_tNode.nOffsetX[1]);
		m_pCopyLineMapNode.get()->GetData(15, &m_tNode.nOffsetY[1]);
		m_pCopyLineMapNode.get()->GetData(16, &m_tNode.nCenterSpot[1]);
		m_pCopyLineMapNode.get()->GetData(17, &m_tNode.nRotAngle[1]);
		m_pCopyLineMapNode.get()->GetData(18, &m_tNode.nType[1]);
		m_pCopyLineMapNode.get()->GetData(19, &m_tNode.nColored[1]);
		m_pCopyLineMapNode.get()->GetData(20, &m_tNode.nRelatedIndex[1]);

		m_pCopyLineMapNode.get()->GetData(21, &m_tNode.nOffsetX[2]);
		m_pCopyLineMapNode.get()->GetData(22, &m_tNode.nOffsetY[2]);
		m_pCopyLineMapNode.get()->GetData(23, &m_tNode.nCenterSpot[2]);
		m_pCopyLineMapNode.get()->GetData(24, &m_tNode.nRotAngle[2]);
		m_pCopyLineMapNode.get()->GetData(25, &m_tNode.nType[2]);
		m_pCopyLineMapNode.get()->GetData(26, &m_tNode.nColored[2]);
		m_pCopyLineMapNode.get()->GetData(27, &m_tNode.nRelatedIndex[2]);

		m_pCopyLineMapNode.get()->GetData(28, &m_tSpot.nSOffsetX[0]);
		m_pCopyLineMapNode.get()->GetData(29, &m_tSpot.nSOffsetY[0]);
		m_pCopyLineMapNode.get()->GetData(30, &m_tSpot.nSCenterSpot[0]);
		m_pCopyLineMapNode.get()->GetData(31, &m_tSpot.nSUseDefault[0]);
		m_pCopyLineMapNode.get()->GetData(32, &m_tSpot.nSRelatedIndex[0]);

		m_pCopyLineMapNode.get()->GetData(33, &m_tSpot.nSOffsetX[1]);
		m_pCopyLineMapNode.get()->GetData(34, &m_tSpot.nSOffsetY[1]);
		m_pCopyLineMapNode.get()->GetData(35, &m_tSpot.nSCenterSpot[1]);
		m_pCopyLineMapNode.get()->GetData(36, &m_tSpot.nSUseDefault[1]);
		m_pCopyLineMapNode.get()->GetData(37, &m_tSpot.nSRelatedIndex[1]);

		m_pCopyLineMapNode.get()->GetData(38, &m_tSpot.nSOffsetX[2]);
		m_pCopyLineMapNode.get()->GetData(39, &m_tSpot.nSOffsetY[2]);
		m_pCopyLineMapNode.get()->GetData(40, &m_tSpot.nSCenterSpot[2]);
		m_pCopyLineMapNode.get()->GetData(41, &m_tSpot.nSUseDefault[2]);
		m_pCopyLineMapNode.get()->GetData(42, &m_tSpot.nSRelatedIndex[2]);

		m_pCopyLineMapNode.get()->GetData(43, &m_tSpot.nSType[0]);
		m_pCopyLineMapNode.get()->GetData(44, &m_tSpot.nSType[1]);
		m_pCopyLineMapNode.get()->GetData(45, &m_tSpot.nSType[2]);
	}
}

void QLineMapEdit::pasteNodeProperty()
{
	// what to do
	// copy selected prop to all
	// auto increment station index

	auto *pDM = CDataManage::GetInstance();
	std::shared_ptr<dataModel> pVLMN = pDM->GET_MODEL_CLASS(LineMapNode);

	for (int i = 0; i < pVLMN->rowCount(); ++i)
	{
		if (i != m_selectedRow)
		{
			qDebug() << "i:" << i << m_tNode.nOffsetX[0];
			QModelIndex index = pVLMN->index(i, 0);
			pVLMN->setData(index.sibling(i,  7), m_tNode.nOffsetX[0], Qt::EditRole);
			pVLMN->setData(index.sibling(i,  8), m_tNode.nOffsetY[0], Qt::EditRole);
			pVLMN->setData(index.sibling(i,  9), m_tNode.nCenterSpot[0], Qt::EditRole);
			pVLMN->setData(index.sibling(i, 10), m_tNode.nRotAngle[0], Qt::EditRole);
			pVLMN->setData(index.sibling(i, 11), m_tNode.nType[0], Qt::EditRole); // indicates node image refer to display pool or image list pool
			pVLMN->setData(index.sibling(i, 12), m_tNode.nColored[0], Qt::EditRole);
			pVLMN->setData(index.sibling(i, 13), m_tNode.nRelatedIndex[0], Qt::EditRole);
			pVLMN->setData(index.sibling(i, 14), m_tNode.nOffsetX[1], Qt::EditRole);
			pVLMN->setData(index.sibling(i, 15), m_tNode.nOffsetY[1], Qt::EditRole);
			pVLMN->setData(index.sibling(i, 16), m_tNode.nCenterSpot[1], Qt::EditRole);
			pVLMN->setData(index.sibling(i, 17), m_tNode.nRotAngle[1], Qt::EditRole);
			pVLMN->setData(index.sibling(i, 18), m_tNode.nType[1], Qt::EditRole); // indicates node image refer to display pool or image list pool
			pVLMN->setData(index.sibling(i, 19), m_tNode.nColored[1], Qt::EditRole);
			pVLMN->setData(index.sibling(i, 20), m_tNode.nRelatedIndex[1], Qt::EditRole);
			pVLMN->setData(index.sibling(i, 21), m_tNode.nOffsetX[2], Qt::EditRole);
			pVLMN->setData(index.sibling(i, 22), m_tNode.nOffsetY[2], Qt::EditRole);
			pVLMN->setData(index.sibling(i, 23), m_tNode.nCenterSpot[2], Qt::EditRole);
			pVLMN->setData(index.sibling(i, 24), m_tNode.nRotAngle[2], Qt::EditRole);
			pVLMN->setData(index.sibling(i, 25), m_tNode.nType[2], Qt::EditRole); // indicates node image refer to display pool or image list pool
			pVLMN->setData(index.sibling(i, 26), m_tNode.nColored[2], Qt::EditRole);
			pVLMN->setData(index.sibling(i, 27), m_tNode.nRelatedIndex[2], Qt::EditRole);
		}
		else
		{
			qDebug() << "selected row and i val are same:" << m_selectedRow << i;
		}
	}

}

void QLineMapEdit::pasteSpotProperty()
{
	auto *pDM = CDataManage::GetInstance();
	std::shared_ptr<dataModel> pVLMN = pDM->GET_MODEL_CLASS(LineMapNode);

	for (int i = 0; i < pVLMN->rowCount(); ++i)
	{
		if (i != m_selectedRow)
		{
			qDebug() << "i:" << i << m_tNode.nOffsetX[0];
			QModelIndex index = pVLMN->index(i, 0);
			pVLMN->setData(index.sibling(i, 28), m_tSpot.nSOffsetX[0], Qt::EditRole);
			pVLMN->setData(index.sibling(i, 29), m_tSpot.nSOffsetY[0], Qt::EditRole);
			pVLMN->setData(index.sibling(i, 30), m_tSpot.nSCenterSpot[0], Qt::EditRole);
			pVLMN->setData(index.sibling(i, 31), m_tSpot.nSUseDefault[0], Qt::EditRole);
			pVLMN->setData(index.sibling(i, 32), m_tSpot.nSRelatedIndex[0], Qt::EditRole);
			pVLMN->setData(index.sibling(i, 33), m_tSpot.nSOffsetX[1], Qt::EditRole);
			pVLMN->setData(index.sibling(i, 34), m_tSpot.nSOffsetY[1], Qt::EditRole);
			pVLMN->setData(index.sibling(i, 35), m_tSpot.nSCenterSpot[1], Qt::EditRole);
			pVLMN->setData(index.sibling(i, 36), m_tSpot.nSUseDefault[1], Qt::EditRole);
			pVLMN->setData(index.sibling(i, 37), m_tSpot.nSRelatedIndex[1], Qt::EditRole);
			pVLMN->setData(index.sibling(i, 38), m_tSpot.nSOffsetX[2], Qt::EditRole);
			pVLMN->setData(index.sibling(i, 39), m_tSpot.nSOffsetY[2], Qt::EditRole);
			pVLMN->setData(index.sibling(i, 40), m_tSpot.nSCenterSpot[2], Qt::EditRole);
			pVLMN->setData(index.sibling(i, 41), m_tSpot.nSUseDefault[2], Qt::EditRole);
			pVLMN->setData(index.sibling(i, 42), m_tSpot.nSRelatedIndex[2], Qt::EditRole);
			pVLMN->setData(index.sibling(i, 43), m_tSpot.nSType[0], Qt::EditRole); // indicates spot image refer display pool or image list pool
			pVLMN->setData(index.sibling(i, 44), m_tSpot.nSType[1], Qt::EditRole); // indicates spot image refer display pool or image list pool
			pVLMN->setData(index.sibling(i, 45), m_tSpot.nSType[2], Qt::EditRole); // indicates spot image refer display pool or image list pool
		}
		else
		{
			qDebug() << "selected row and i val are same:" << m_selectedRow << i;
		}
	}
}

void QLineMapEdit::clickedSetSpotButton(int id)
{
	// id와 실제 db에 저장되는 값이 같아야 함!!!!!
	qDebug() << id;
	auto *pDM = CDataManage::GetInstance();
	std::shared_ptr<dataModel> pVLMN = pDM->GET_MODEL_CLASS(LineMapNode);

	for (int i = 0; i < pVLMN->rowCount(); ++i)
	{
		QModelIndex index = pVLMN->index(i, 0);
		pVLMN->setData(index.sibling(i, 31), id, Qt::EditRole);
		pVLMN->setData(index.sibling(i, 36), id, Qt::EditRole);
		pVLMN->setData(index.sibling(i, 41), id, Qt::EditRole);
	}
}

void QLineMapEdit::colorApply()
{
	m_pLineMapMapper->submit();
	Sleep(50);
	ui.openGLWidget->update();
	update();
}

void QLineMapEdit::arrowOffsetApply()
{
	m_pLineMapMapper->submit();
	Sleep(50);
	ui.openGLWidget->update();
	update();
}

void QLineMapEdit::initMapper()
{
	if (!m_pLineMapMapper)
	{
		auto *pDM = CDataManage::GetInstance();
		m_pLineMapMapper = new QDataWidgetMapper(this);
		m_pLineMapMapper->setModel((QAbstractItemModel*)pDM->GET_MODEL_CLASS(LineMapPool).get());
		m_pLineMapMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

		m_pLineMapMapper->addMapping(ui.editTitle, 1);
		m_pLineMapMapper->addMapping(ui.editTileSize, 2);
		m_pLineMapMapper->addMapping(ui.editLineThick, 3);
		m_pLineMapMapper->addMapping(ui.editWidth, 6);
		m_pLineMapMapper->addMapping(ui.editHeight, 7);
		m_pLineMapMapper->addMapping(ui.m_ctlBackgroundColor, 10, "colorValue");
		m_pLineMapMapper->addMapping(ui.m_ctlForegroundColor, 11, "colorValue");
		m_pLineMapMapper->addMapping(ui.m_ctlPassedColor, 12, "colorValue");
		m_pLineMapMapper->addMapping(ui.m_ctlFocusedColor, 13, "colorValue");
		m_pLineMapMapper->addMapping(ui.m_ctlLeftColor, 14, "colorValue");
		m_pLineMapMapper->addMapping(ui.m_spForwardArrowOffset, 16);
		m_pLineMapMapper->addMapping(ui.m_spBackwardArrowOffset, 17);
		m_pLineMapMapper->addMapping(ui.m_spArrowPenWidth, 18);
		m_pLineMapMapper->addMapping(ui.m_ctlArrowPassedColor, 19, "colorValue");
		m_pLineMapMapper->addMapping(ui.m_ctlArrowFocusedColor, 20, "colorValue");
		m_pLineMapMapper->addMapping(ui.m_ctlArrowSecondFocusedColor, 21, "colorValue");
		m_pLineMapMapper->addMapping(ui.m_ctlArrowRemainedColor, 22, "colorValue");
		m_pLineMapMapper->setCurrentIndex(m_nRow);
	}
}
