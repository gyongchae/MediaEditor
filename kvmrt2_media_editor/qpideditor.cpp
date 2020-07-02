#include "qpideditor.h"
#include "QTimeEvent.h"
#include "DataManage.h"
#include <QtOpenGL>
#include <QGLWidget>
#include <QDataWidgetMapper>
#include "dataModel.h"
#include <qdebug.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include "MapManage.h"

QPIDEditor::QPIDEditor(int nRow,int nWidth, int nHeight, int nDuration,QWidget *parent)
	: QDialog(parent)
	, m_canvas(0)
	, m_ScreenSize(nWidth, nHeight)
	, m_labelCoordXY(0)
	, m_pDataMapper(0)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();
	auto *pMM = CMapManage::GetInstance();


	// childVector[0]: displayItem
	// childVector[1]: displayMetaItem
	pDM->GET_MODEL_CLASS(DisplayItem)->setVectors(
		&pTM->VECTOR_CLASS(DisplayItemPool)[nRow]->m_vChildItem[0].vSQLData, 
		&pTM->VECTOR_CLASS(DisplayItemPool)[nRow]->m_vChildItem[0].vSQLDataDelItems, 
		 pTM->VECTOR_CLASS(DisplayItemPool)[nRow].get()->GetIndex());
	
	pDM->GET_MODEL_CLASS(DisplayMetaItem)->setVectors(
		&pTM->VECTOR_CLASS(DisplayItemPool)[nRow]->m_vChildItem[1].vSQLData, 
		&pTM->VECTOR_CLASS(DisplayItemPool)[nRow]->m_vChildItem[1].vSQLDataDelItems, 
		 pTM->VECTOR_CLASS(DisplayItemPool)[nRow].get()->GetIndex());

	m_canvas = new QGLESPIDCanvas(this);
	m_timeEvent = new QTimeEvent(nDuration, this);
	m_tblItemList = new QTableView(this);
	m_btnAccept = new QPushButton("Accept", this);
	m_labelCoordXY = new QLabel(this);
	m_editTitle = new QLineEdit(this);
	m_editWidth = new QLineEdit(this);
	m_editHeight = new QLineEdit(this);
	m_editDuration = new QLineEdit(this);
	m_comboDisplayType = new QComboBox(this);

	// combobox init same as displayItemPreset class
	QStringList typeList;
	for (auto it = pMM->m_mDisplayPoolType.begin(); it != pMM->m_mDisplayPoolType.end(); ++it)
	{
		m_comboDisplayType->addItem(QString::number(it->first));
		m_comboDisplayType->setItemData(it->first, QString::fromStdWString(it->second), Qt::DisplayRole);
	}

	scrollAreaView = new QScrollArea;
	scrollAreaTime = new QScrollArea;

	m_loMain = new QGridLayout(this);
	
	auto *loSize = new QHBoxLayout;
	auto *loProperty = new QGridLayout;
	auto *loItemList = new QVBoxLayout;
	auto *loRight = new QVBoxLayout;
	auto *gbProperty = new QGroupBox("Property");
	auto *gbImagePool = new QGroupBox("Image List Pool");
	
	scrollAreaView->setWidget(m_canvas);
	scrollAreaTime->setWidget(m_timeEvent);

	loSize->addWidget(new QLabel("W:"));
	loSize->addWidget(m_editWidth);
	loSize->addWidget(new QLabel("H:"));
	loSize->addWidget(m_editHeight);

	loProperty->addWidget(new QLabel("Title"), 0, 0);
	loProperty->addWidget(new QLabel("Size"), 1, 0);
	loProperty->addWidget(new QLabel("Duration"), 2, 0);
	loProperty->addWidget(new QLabel("Display Type"), 3, 0);

	loProperty->addWidget(m_editTitle, 0, 1);
	loProperty->addLayout(loSize, 1, 1);
	loProperty->addWidget(m_editDuration, 2, 1);
	loProperty->addWidget(m_comboDisplayType, 3, 1);

	loProperty->setColumnStretch(1, 10);

	loItemList->addWidget(m_tblItemList);

	gbProperty->setLayout(loProperty);
	gbImagePool->setLayout(loItemList);
	gbProperty->setMaximumWidth(200);
	gbImagePool->setMaximumWidth(200);
	gbProperty->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	gbImagePool->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

	loRight->addWidget(gbProperty);
	loRight->addWidget(gbImagePool);
	loRight->addWidget(m_labelCoordXY);
	loRight->addWidget(m_btnAccept);
	loRight->setStretch(1, 10); // table view location (row)
	
	m_loMain->addWidget(scrollAreaView, 0, 0);
	m_loMain->addWidget(scrollAreaTime, 1, 0);
	m_loMain->addLayout(loRight, 0, 1, 2, 2);
	
	m_loMain->setRowStretch(0, 10);
	m_loMain->setColumnStretch(0, 10);

	initTableView();
	initWidgetMapper(nRow);

	m_timeEvent->setTimeVector(&m_canvas->vKeyFrames);
	
	connect(m_btnAccept, SIGNAL(clicked()), this, SLOT(acceptedChanges()));
	connect(m_timeEvent,SIGNAL(timeChanged(int)),m_canvas,SLOT(setCurrentTime(int)));
	connect(m_canvas, SIGNAL(positionChanged(const QString&)), m_labelCoordXY, SLOT(setText(const QString&)));
	connect(m_canvas, SIGNAL(selectionChanged()), m_timeEvent, SLOT(update()));
}

QPIDEditor::~QPIDEditor()
{
}

void QPIDEditor::resizeEvent(QResizeEvent *)
{
	if(m_canvas)
		m_canvas->setMinimumSize(m_ScreenSize);
}

void QPIDEditor::initTableView()
{
	auto *pDM = CDataManage::GetInstance();
	m_tblItemList->setModel((QAbstractItemModel*)pDM->m_pModImageIndexList.get());
	m_tblItemList->setSelectionMode(QAbstractItemView::SingleSelection);
	m_tblItemList->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_tblItemList->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_tblItemList->setDragEnabled(true);
	m_tblItemList->setAcceptDrops(true);
	m_tblItemList->setDropIndicatorShown(false);
	m_tblItemList->setDragDropMode(QAbstractItemView::DragOnly);

	QHeaderView *header = m_tblItemList->horizontalHeader();
	header->resizeSections(QHeaderView::ResizeToContents);
}

void QPIDEditor::acceptedChanges()
{
	qDebug() << Q_FUNC_INFO;
	m_pDataMapper->submit();
	accept();
}

void QPIDEditor::initWidgetMapper(int nRow)
{
	if (!m_pDataMapper)
	{
		auto *pDM = CDataManage::GetInstance();
		m_pDataMapper = new QDataWidgetMapper(this);
		m_pDataMapper->setModel((QAbstractItemModel*)pDM->GET_MODEL_CLASS(DisplayItemPool).get());
		m_pDataMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

		m_pDataMapper->addMapping(m_editTitle, 1); // ui label과 db column중 title에 해당하는 1번 칼럼과 매핑
		m_pDataMapper->addMapping(m_editWidth, 2);
		m_pDataMapper->addMapping(m_editHeight, 3);
		m_pDataMapper->addMapping(m_editDuration, 4);
		m_pDataMapper->addMapping(m_comboDisplayType, 7, "currentIndex");
		
		m_pDataMapper->setCurrentIndex(nRow);
	}
}