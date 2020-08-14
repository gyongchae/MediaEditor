#include "stationImagePool.h"
#include "DataManage.h"
#include "dataModel.h"
#include <shlwapi.h>
#include <QtGui>
#include "ini.h"
#include "stringscaler.h"
#include "DefineTables.h"
#include "qtextaligner.h"
#include "SQLDelegate.h"
#include <QDebug>
#include <qcolordialog.h>
#include "DefineMode.h"

#pragma comment(lib,"shlwapi")

stationImagePool::stationImagePool(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	CALL_INIT_FUNCTION(StationImagePool);

	connect(ui.btnAddText, SIGNAL(clicked(bool)), this, SLOT(addStationImagePool(bool)));
	connect(ui.btnDelText, SIGNAL(clicked()), this, SLOT(deleteStationImagePool()));
	connect(ui.btnClose, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui.btnColor, SIGNAL(clicked()), this, SLOT(changeBackgroundColor()));

	if (OFFICIAL_RELEASE == true)
	{
		SET_HIDE_TABLE_COLUMN(StationImagePool, 0);
		SET_HIDE_TABLE_COLUMN(StationImagePool, 1);
		SET_HIDE_TABLE_COLUMN_RANGE(StationImagePool, 5, 14);
	}
}

stationImagePool::~stationImagePool()
{
}

IMPLEMENT_INIT_FUNCTION_FOR_CLASS(stationImagePool,StationImagePool)
{
	auto *pDM = CDataManage::GetInstance();
	auto *pTM=CTableManage::GetInstance();
	SET_MODEL_FOR_TABLE_VIEW(StationImagePool,pDM)
	INSTALL_EVENT_FILTER(StationImagePool)

	SET_SELECTION_BEHAVIOR(StationImagePool,QAbstractItemView::SelectRows)	
	SET_SELECTION_MODE(StationImagePool,QAbstractItemView::SingleSelection)

	GET_TABLE(StationImagePool)->setItemDelegateForColumn(3,new SQLDelegate(this,&pTM->VECTOR_CLASS(FontPool),0,4,TYPE_TEXT));

	SET_DRAG_AND_DROP_ENABLED(StationImagePool);

	QHeaderView *header=GET_TABLE(StationImagePool)->horizontalHeader();
	header->resizeSections(QHeaderView::ResizeToContents);
	header->setStretchLastSection(true);
	
	CONNECT_ROW_CHAHANGED_SLOT(StationImagePool,updateStationImage(const QModelIndex &, const QModelIndex &));
	connect(GET_TABLE_MODEL(pDM,StationImagePool).get(),
			SIGNAL(dataChanged(const QModelIndex &,const QModelIndex &)),
			this,
			SLOT(updateStationImagePool(const QModelIndex &,const QModelIndex &)));

	m_pSFMLView = new QTextAligner(ui.frame, QPoint(0, 0), QSize(999, 999), QTextAligner::TEXT);
	m_pSFMLView->setBackgroundColor(pDM->m_txtPoolBack);

	return false;
}

void stationImagePool::addStationImagePool(bool bInsert)
{
	int nRow;
	auto *pDM = CDataManage::GetInstance();
	auto *pTM=CTableManage::GetInstance();
	std::vector<std::shared_ptr<CSQLData>>::iterator nit;
	std::shared_ptr<dataModel> pVFM=pDM->GET_MODEL_CLASS(StationImagePool);
	QModelIndex index=GET_TABLE(StationImagePool)->currentIndex();
	if(index.isValid())
	{
		nRow=index.row();
	}
	else
	{
		nRow=pVFM->rowCount();
	}

	if(!bInsert)
		nRow=pVFM->rowCount();

	pVFM->insertRows(nRow,1);
}

void stationImagePool::deleteStationImagePool()
{
	int nRow;
	auto *pDM = CDataManage::GetInstance();
	std::shared_ptr<dataModel> pVFM=pDM->GET_MODEL_CLASS(StationImagePool);
	QModelIndex index=GET_TABLE(StationImagePool)->currentIndex();

	if(index.isValid())
	{
		int nRet=QMessageBox::warning(this,QString::fromStdWString(APPLICATION_NAME),QString::fromStdWString(ARE_YOU_SURE),QMessageBox::Yes|QMessageBox::No);
		if(nRet==QMessageBox::Yes)
		{
			nRow=index.row();
			pVFM->removeRows(nRow,1);
		}
	}
}

bool stationImagePool::eventFilter(QObject *object, QEvent *event)
{
	auto *pDM = CDataManage::GetInstance();
	QModelIndex index;

	if(event->type()==QEvent::KeyPress)
	{
		QKeyEvent *keyEvent=static_cast<QKeyEvent*>(event);
		qDebug() << Q_FUNC_INFO << keyEvent->key();
		if(keyEvent->key()==Qt::Key_Delete)
		{
			if(object==GET_TABLE(StationImagePool))
			{	
				deleteStationImagePool();
			}
			return true;
		}
		else if(keyEvent->key()==Qt::Key_F9)
		{
			if(object==GET_TABLE(StationImagePool))
			{	
				addStationImagePool(false);
			}
			return true;
		}
		else if(keyEvent->key()==Qt::Key_Insert)
		{
			if(object==GET_TABLE(StationImagePool))
			{	
				addStationImagePool(true);
			}
			return true;
		}
	}
	return false;
}

void stationImagePool::updateStationImage(const QModelIndex & current, const QModelIndex & previous)
{
	QModelIndex index=GET_TABLE(StationImagePool)->currentIndex();
	auto *pDM = CDataManage::GetInstance();
	auto *pTM=CTableManage::GetInstance();
	if(current.isValid())
	{
		int nRow=current.row();
		if(nRow<pTM->VECTOR_CLASS(StationImagePool).size())
		{
			m_pSFMLView->clearAllSprite();
			StationImagePool *pImage=(StationImagePool*)pTM->m_vStationImagePool[nRow].get();
			if(pImage->nWidth&&pImage->nHeight)
			{
				m_pSFMLView->setTexSprite(pImage->GetIndex(),pImage->nWidth,pImage->nHeight,0,0,pImage->pByte.get());
			}
		}
		m_pSFMLView->update();
	}
}


void stationImagePool::updateStationImagePool(const QModelIndex & topLeft,const QModelIndex & bottomRight)
{
	wchar_t szTitle[256];
	auto *pDM = CDataManage::GetInstance();
	auto *pTM=CTableManage::GetInstance();
	int nFontIndex,nFontSize,nWidthLimit,nHeightLimit,nProperty1,nProperty2,nActualWidth,nActualHeight;
	nFontIndex=nFontSize=nWidthLimit=nHeightLimit=nProperty1=nProperty2=nActualWidth=nActualHeight=0;
	std::shared_ptr<dataModel> pVFM=pDM->GET_MODEL_CLASS(StationImagePool);
	if(topLeft.isValid()&&bottomRight.isValid())
	{
		int nRow=topLeft.row();
		int nColumn=topLeft.column();
		switch(nColumn)
		{
		case 2:
		case 3:
		case 4:
		case 6:
		case 7:
		case 10:
		case 11:
			wcscpy(szTitle,topLeft.sibling(topLeft.row(),2).data().toString().toStdWString().c_str());
			nFontIndex=topLeft.sibling(topLeft.row(),3).data().toInt();
			nFontSize=topLeft.sibling(topLeft.row(),4).data().toInt();
			nWidthLimit = topLeft.sibling(topLeft.row(),6).data().toInt();
			nHeightLimit = topLeft.sibling(topLeft.row(),7).data().toInt();
			nProperty1=topLeft.sibling(topLeft.row(),10).data().toInt();
			nProperty2=topLeft.sibling(topLeft.row(),11).data().toInt();
			break;
		default:
			break;
		}
		if(wcslen(szTitle)&&nFontIndex&&nFontSize&&nWidthLimit&&nHeightLimit)
		{
			std::vector<std::shared_ptr<CSQLData>>::iterator tit;
			tit=find_if(pTM->VECTOR_CLASS(FontPool).begin(),pTM->VECTOR_CLASS(FontPool).end(),findSQLData(nFontIndex));
			if(tit!=pTM->VECTOR_CLASS(FontPool).end())
			{
				//하나씩 추가
				FontPool *pFP=(FontPool*)tit->get();
				QString strPath=pDM->fontPath()+"/"+QString::fromStdWString(pFP->szFileName);
				CFontScaler *pSS=CFontScaler::GetInstance();
				

				int nActualWidth,nActualHeight;
				void *pBuffer;
				std::shared_ptr<unsigned char> pByte=pSS->GetScaledBitmap(
					QDir::toNativeSeparators(strPath).toStdString().c_str(),
					pFP->nSpareCode,
					szTitle,
					nFontSize,
					nWidthLimit,
					nHeightLimit,
					&nActualWidth,
					&nActualHeight,
					4);
				if(pByte.get())
				{
					StationImagePool *pImage=(StationImagePool*)pTM->m_vStationImagePool[topLeft.row()].get();
					pImage->nWidth=nActualWidth;
					pImage->nHeight=nActualHeight;
					pImage->nDataLength=nActualWidth*nActualHeight*4;
					pImage->pByte=pByte;

					TCHAR szBuffer[256];
					_stprintf_s(szBuffer,_countof(szBuffer),_T("Debug! %d %d\n"),nActualWidth,nActualHeight);
					OutputDebugString(szBuffer);
					m_pSFMLView->setTexSprite(pImage->GetIndex(),nActualWidth,nActualHeight,0,0,pByte.get());
					m_pSFMLView->update();
				}
			}
		}
	}
}

void stationImagePool::changeBackgroundColor()
{
	auto *pDM = CDataManage::GetInstance();

	pDM->m_txtPoolBack = QColorDialog::getColor(m_pSFMLView->backgroundColor(), this);
	if (pDM->m_txtPoolBack.isValid())
	{
		m_pSFMLView->setBackgroundColor(pDM->m_txtPoolBack);
	}
}
