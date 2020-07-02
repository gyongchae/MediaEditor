#include "QLineMapPreview.h"
#include "QTimeEvent.h"
#include "DataManage.h"
#include <QtOpenGL>
#include <QGLWidget>
#include "QGLESLineMapPreview.h"
#include "dataModel.h"
#include "tableViewHelper.h"
#include "SQLDelegate.h"

QLineMapPreview::QLineMapPreview(QWidget *parent)
	: QDialog(parent), m_ScreenSize(1920, 1080), m_nStopPtnIdx(0), m_nProgress(0), m_nLineMapIdx(0), m_nDistIdx(0), m_nRoutesIdx(0)
{
	ui.setupUi(this);

	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();

	m_canvas = new QGLESLineMapPreview(this);
	m_layout = new QGridLayout(this);
	m_timeEvent = new QTimeEvent(1000, this);
	m_btnAccept = new QPushButton(this);
	m_lbLocation = new QLabel(this);

	QScrollArea *scrollAreaView = new QScrollArea;
	scrollAreaView->setWidget(m_canvas);

	QScrollArea *scrollAreaTime = new QScrollArea;
	scrollAreaTime->setWidget(m_timeEvent);

	m_layout->addWidget(scrollAreaView, 0, 0, 82, 95);
	m_layout->addWidget(scrollAreaTime, 82, 0, 4, 101);

	m_layout->addWidget(m_lbLocation, 0, 96, 2, 5);
	m_layout->addWidget(ui.m_grpTrainNum, 2, 96, 4, 5);
	m_layout->addWidget(ui.m_grpDistList, 6, 96, 72, 5);
	m_layout->addWidget(ui.m_grpProgBar, 78, 96, 2, 5);

	m_layout->addWidget(m_btnAccept, 80, 96, 2, 5);


	m_canvas->mapLineMapIdx(&m_nLineMapIdx);
	m_canvas->mapDistIdx(&m_nDistIdx);
	m_canvas->mapStopPtnIdx(&m_nStopPtnIdx);
	m_canvas->mapProgress(&m_nProgress);
	m_canvas->mapRoutesIdx(&m_nRoutesIdx);


	ui.m_ctlProgress->setRange(0, 1000);

	connect(m_timeEvent, SIGNAL(timeChanged(int)), m_canvas, SLOT(setCurrentTime(int)));

	connect(ui.m_ctlProgress, SIGNAL(valueChanged(int)), this, SLOT(setCurProgress(int)));
	initStopPtnRoutes();
	connect(ui.m_pbTNInput, SIGNAL(clicked()), this, SLOT(setTrainNumber()));
}


QLineMapPreview::~QLineMapPreview()
{
}

void QLineMapPreview::setCurProgress(int nProg)
{
	m_nProgress = nProg;
	qDebug() << m_nProgress;
	m_canvas->update();
}


void QLineMapPreview::resizeEvent(QResizeEvent *)
{
	if (m_canvas)
		m_canvas->setMinimumSize(m_ScreenSize);
}



void QLineMapPreview::acceptedChanges()
{
	accept();
}

void QLineMapPreview::initTableView()
{
}


void QLineMapPreview::setTrainNumber()
{
	auto *pTM = CTableManage::GetInstance();
	auto *pDM = CDataManage::GetInstance();
	wcscpy(m_szTrainNum,ui.m_leTrainNumber->text().toStdWString().c_str());
	auto it = find_if(pTM->m_vTrainNumber.begin(), pTM->m_vTrainNumber.end(), [this](std::shared_ptr<CSQLData> &pData)
	{
		TrainNumber *pTN=(TrainNumber*)pData.get();
		return !wcscmp(pTN->szTrainNumber, m_szTrainNum);
	});

	if (it != pTM->m_vTrainNumber.end())
	{
		TrainNumber *pTN = (TrainNumber*)it->get();
		auto subit = find_if(pTM->m_vStopPtnHeader.begin(), pTM->m_vStopPtnHeader.end(), findSQLData(pTN->nStopPatternIndex));
		if (subit != pTM->m_vStopPtnHeader.end())
		{
			StopPtnHeader *pSPH=(StopPtnHeader*)subit->get();
			m_nLineMapIdx = pSPH->nRelatedLineMapIndex;
			m_nStopPtnIdx = pSPH->GetIndex();
			pDM->GET_MODEL_CLASS(StopPtnRoutes)->setVectors(&pSPH->m_vChildItem[0].vSQLData, &pSPH->m_vChildItem[0].vSQLDataDelItems,pSPH->GetIndex());
			ui.m_tblStopPtnRoutes->update();
			m_canvas->update();
		}
	}
}

void QLineMapPreview::initStopPtnRoutes()
{
	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();
	SET_MODEL_FOR_TABLE_VIEW(StopPtnRoutes, pDM)
	INSTALL_EVENT_FILTER(StopPtnRoutes)
	SET_SELECTION_BEHAVIOR(StopPtnRoutes, QAbstractItemView::SelectRows)
	SET_SELECTION_MODE(StopPtnRoutes, QAbstractItemView::SingleSelection)

	GET_TABLE(StopPtnRoutes)->setItemDelegateForColumn(3, new SQLDelegate(this, &pTM->VECTOR_CLASS(StationDistance), 0, 4, TYPE_TEXT));
	GET_TABLE(StopPtnRoutes)->setItemDelegateForColumn(4, new SQLDelegate(this, &pTM->VECTOR_CLASS(EDDIndex), 0, 1, TYPE_TEXT));


	//SET_DRAG_AND_DROP_ENABLED(StopPtnRoutes);
	//SET_SELECTION_CHANGED_FOR_TABLE(pDM, StopPtnRoutes, selectionChangedStopPtnRoutes(int, int));


	// section hide, jkc
	QHeaderView *header = GET_TABLE(StopPtnRoutes)->horizontalHeader();
	//header->hideSection(0);
	//header->hideSection(1);
	//header->hideSection(2);
	header->resizeSections(QHeaderView::ResizeToContents);

	CONNECT_ROW_CHAHANGED_SLOT(StopPtnRoutes, updateEventLists(const QModelIndex &, const QModelIndex &));

}


void QLineMapPreview::updateEventLists(const QModelIndex &current, const QModelIndex &previous)
{
	auto *pDM = CDataManage::GetInstance();
	int nRow=current.row();
	m_nRoutesIdx=pDM->GET_MODEL_CLASS(StopPtnRoutes)->getVector()->at(nRow)->GetIndex();
	m_canvas->update();
}