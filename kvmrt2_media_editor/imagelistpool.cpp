#include "imagelistpool.h"
#include "DataManage.h"
#include "dataModel.h"
#include "SQLDelegate.h"
#include "qtextaligner.h"
#include "MapManage.h"
#include "comboBoxDelegate.h"
#include <QDebug>
#include <qmessagebox.h>
#include <qcolordialog.h>
#include "DefineMode.h"

#define IMAGE_LIST_POOL_CLASS imageListPool

imageListPool::imageListPool(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);


	auto *pDM = CDataManage::GetInstance();
	m_pSFMLView = new QTextAligner(ui.frame, QPoint(0, 0), QSize(1920, 1080), QTextAligner::IMAGELIST);
	m_pSFMLView->setBackgroundColor(pDM->m_imgListBack);

	CALL_INIT_FUNCTION(ImageIndexList);
	CALL_INIT_FUNCTION(ImageIndex);

	SET_EVENT_TABLE(pDM, ImageIndexList);
	SET_EVENT_TABLE(pDM, ImageIndex);

	connect(ui.btnAddImgListPool, SIGNAL(clicked()), this, SLOT(onAddImageListPool()));
	connect(ui.btnDelImgListPool, SIGNAL(clicked()), this, SLOT(onDelImageListPool()));
	connect(ui.btnAddImgIndex, SIGNAL(clicked()), this, SLOT(onAddImageIndex()));
	connect(ui.btnDelImgIndex, SIGNAL(clicked()), this, SLOT(onDelImageIndex()));
	connect(ui.btnClose, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui.btnColor, SIGNAL(clicked()), this, SLOT(changeBackgroundColor()));

	if (OFFICIAL_RELEASE == true)
	{
		SET_HIDE_TABLE_COLUMN(ImageIndexList, 0);
		SET_HIDE_TABLE_COLUMN(ImageIndexList, 1);
		SET_HIDE_TABLE_COLUMN(ImageIndexList, 2);
		SET_HIDE_TABLE_COLUMN(ImageIndex, 0);
		SET_HIDE_TABLE_COLUMN(ImageIndex, 1);
		SET_HIDE_TABLE_COLUMN(ImageIndex, 2);
	}
}

imageListPool::~imageListPool()
{
}

IMPLEMENT_INIT_FUNCTION_FOR_CLASS(IMAGE_LIST_POOL_CLASS, ImageIndexList)
{
	auto *pDM = CDataManage::GetInstance();
	auto *pMM = CMapManage::GetInstance();
	SET_MODEL_FOR_TABLE_VIEW(ImageIndexList, pDM);
	INSTALL_EVENT_FILTER(ImageIndexList);

	SET_SELECTION_BEHAVIOR(ImageIndexList, QAbstractItemView::SelectRows);
	SET_SELECTION_MODE(ImageIndexList, QAbstractItemView::SingleSelection);
	SET_DRAG_AND_DROP_ENABLED(ImageIndexList);

	QHeaderView *header = GET_TABLE(ImageIndexList)->horizontalHeader();
	header->resizeSections(QHeaderView::ResizeToContents);

	GET_TABLE(ImageIndexList)->setItemDelegateForColumn(4, new comboBoxDelegate(this, &pMM->m_mImageIndexListType));

	CONNECT_ROW_CHAHANGED_SLOT(ImageIndexList, updateImageIndexList(const QModelIndex &, const QModelIndex &));

	return false;
}

IMPLEMENT_INIT_FUNCTION_FOR_CLASS(IMAGE_LIST_POOL_CLASS, ImageIndex)
{
	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();
	auto *pMM = CMapManage::GetInstance();
	SET_MODEL_FOR_TABLE_VIEW(ImageIndex, pDM);
	INSTALL_EVENT_FILTER(ImageIndex);

	SET_DRAG_AND_DROP_ENABLED(ImageIndex);
	SET_SELECTION_BEHAVIOR(ImageIndex, QAbstractItemView::SelectRows);
	SET_SELECTION_MODE(ImageIndex, QAbstractItemView::SingleSelection);

	GET_TABLE(ImageIndex)->setItemDelegateForColumn(3, new comboBoxDelegate(this, &pMM->m_mImageType));
	GET_TABLE(ImageIndex)->setItemDelegateForColumn(4, new SQLDelegate(SQLDelegate::TEXT_IMAGE, this, &pTM->VECTOR_CLASS(StationImagePool), 0, 2, TYPE_TEXT));
	GET_TABLE(ImageIndex)->setItemDelegateForColumn(5, new SQLDelegate(SQLDelegate::BITMAP_IMAGE, this, &pTM->VECTOR_CLASS(BitmapImagePool), 0, 2, TYPE_TEXT));

	connect(GET_TABLE_MODEL(pDM, ImageIndex).get(),
		SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)),
		this,
		SLOT(updateImageIndexList(const QModelIndex &, const QModelIndex &)));

	connect((QObject*)m_pSFMLView, SIGNAL(posChanged(int, int, int)), this, SLOT(itemPositionChanged(int, int, int)));

	QHeaderView *header = GET_TABLE(ImageIndex)->horizontalHeader();
	header->resizeSections(QHeaderView::ResizeToContents);

	return false;
}

void imageListPool::updateImageIndexList(const QModelIndex & current, const QModelIndex & previous)
{
	QModelIndex index = GET_TABLE(ImageIndexList)->currentIndex();
	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();
	if (index.isValid())
	{
		int nRow = index.row();
		if (nRow < pTM->VECTOR_CLASS(ImageIndexList).size())
		{
			m_pSFMLView->clearAllSprite();
			pDM->GET_MODEL_CLASS(ImageIndex)->setVectors(
				&pTM->VECTOR_CLASS(ImageIndexList)[nRow]->m_vChildItem[0].vSQLData,
				&pTM->VECTOR_CLASS(ImageIndexList)[nRow]->m_vChildItem[0].vSQLDataDelItems,
				pTM->VECTOR_CLASS(ImageIndexList)[nRow].get()->GetIndex());

			std::vector<std::shared_ptr<CSQLData>>::iterator tit;
			std::vector<std::shared_ptr<CSQLData>>::iterator tnit;

			for (tit = pTM->VECTOR_CLASS(ImageIndexList)[nRow]->m_vChildItem[0].vSQLData.begin();
				tit != pTM->VECTOR_CLASS(ImageIndexList)[nRow]->m_vChildItem[0].vSQLData.end();
				tit++)
			{
				ImageIndex *pSI = (ImageIndex*)tit->get();
				switch (pSI->nType)
				{
				case 1:
					tnit = find_if(pTM->VECTOR_CLASS(StationImagePool).begin(),
						pTM->VECTOR_CLASS(StationImagePool).end(),
						findSQLData(pSI->nStationNameBitmapIndex));
					if (tnit != pTM->VECTOR_CLASS(StationImagePool).end())
					{
						StationImagePool *pSIP = (StationImagePool*)tnit->get();
						if (pSIP->nDataLength && (pSIP->pByte.get() != nullptr))
						{
							m_pSFMLView->setTexSprite(
								pSIP->GetIndex(),
								pSIP->nWidth,
								pSIP->nHeight,
								pSI->nXPos,
								pSI->nYPos,
								pSIP->pByte.get());
						}
					}
					break;
				case 2:
					tnit = find_if(pTM->VECTOR_CLASS(BitmapImagePool).begin(), pTM->VECTOR_CLASS(BitmapImagePool).end(), findSQLData(pSI->nStationBitmapIndex));
					if (tnit != pTM->VECTOR_CLASS(BitmapImagePool).end())
					{
						BitmapImagePool *pSIP = (BitmapImagePool*)tnit->get();
						if (pSIP->nDataLength && (pSIP->pByte.get() != nullptr))
						{
							m_pSFMLView->setTexSprite(
								pSIP->GetIndex(),
								pSIP->nWidth,
								pSIP->nHeight,
								pSI->nXPos,
								pSI->nYPos,
								pSIP->pByte.get());
						}
					}
					break;
				}
			}
			m_pSFMLView->update();
		}
	}
	else
	{
		pDM->GET_MODEL_CLASS(ImageIndex)->setVectors(nullptr, nullptr);
	}
}

void imageListPool::onAddImageListPool()
{
	auto *pDM = CDataManage::GetInstance();
	addRowToTable(false, ui.m_tblImageIndexList, pDM->m_pModImageIndexList.get());
}

void imageListPool::onDelImageListPool()
{
	auto *pDM = CDataManage::GetInstance();
	deleteRowFromTable(ui.m_tblImageIndexList, pDM->m_pModImageIndexList.get());
}

void imageListPool::onAddImageIndex()
{
	auto *pDM = CDataManage::GetInstance();
	if (ui.m_tblImageIndexList->currentIndex().isValid())
	{
		addRowToTable(false, ui.m_tblImageIndex, pDM->m_pModImageIndex.get());
	}
	else
	{
		QMessageBox::warning(this, "Fail to add index", "Choose an image list pool item", QMessageBox::Ok);
	}
}

void imageListPool::onDelImageIndex()
{
	auto *pDM = CDataManage::GetInstance();
	deleteRowFromTable(ui.m_tblImageIndex, pDM->m_pModImageIndex.get());
}

void imageListPool::changeBackgroundColor()
{
	auto *pDM = CDataManage::GetInstance();

	pDM->m_imgListBack = QColorDialog::getColor(m_pSFMLView->backgroundColor(), this);
	if (pDM->m_imgListBack.isValid())
	{
		m_pSFMLView->setBackgroundColor(pDM->m_imgListBack);
	}
}

bool imageListPool::eventFilter(QObject *object, QEvent *event)
{
	auto *pDM = CDataManage::GetInstance();
	QMap<QTableView*, std::shared_ptr<dataModel>>::iterator nit = m_mEventTable.find((QTableView*)object);
	if (event->type() == QEvent::KeyPress)
	{
		QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
		if (nit != m_mEventTable.end())
		{
			if (object == nit.key())
			{
				switch (keyEvent->key())
				{
				case Qt::Key_Delete://Delete
					deleteRowFromTable(nit.key(), nit.value().get());
					break;
				case Qt::Key_Insert://Insert
					addRowToTable(false, nit.key(), nit.value().get());
					break;
				case Qt::Key_F9://Append
					addRowToTable(true, nit.key(), nit.value().get());
					break;
				}

			}
		}
	}
	return QDialog::eventFilter(object, event);
}

void imageListPool::addRowToTable(bool bInsert, QTableView *pView, dataModel *pModel)
{
	if (pView&&pModel)
	{
		int nRow;
		QModelIndex index = pView->currentIndex();
		if (index.isValid())
		{
			nRow = index.row();
		}
		else
		{
			nRow = pModel->rowCount();
		}
		if (bInsert)
			nRow = pModel->rowCount();
		if (pModel->isValid())
		{
			pModel->insertRows(nRow, 1);
			index = pModel->index(nRow, 0);
			pView->setCurrentIndex(index);
			pView->edit(index);
		}
	}
}

bool imageListPool::deleteRowFromTable(QTableView *pView, dataModel *pModel)
{
	int nRow;
	if (pView&&pModel)
	{
		QModelIndex indexParent = pView->currentIndex();
		if (indexParent.isValid())
		{
			QModelIndex index = pView->currentIndex();
			if (index.isValid())
			{
				int ret = QMessageBox::warning(this, QString::fromStdWString(L"Delete?"), QString::fromStdWString(L"Delete?"), QMessageBox::Yes | QMessageBox::No);
				if (ret == QMessageBox::Yes)
				{
					nRow = index.row();
					pModel->removeRows(nRow, 1);
					return true;
				}
			}
		}
	}
	return false;
}

void imageListPool::itemPositionChanged(int nIndex, int x, int y)
{
	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();
	QModelIndex index = GET_TABLE(ImageIndexList)->currentIndex();
	if (index.isValid())
	{
		int nRow = index.row();
		if (nRow < pTM->VECTOR_CLASS(ImageIndexList).size())
		{
			std::vector<std::shared_ptr<CSQLData>>::iterator tit;
			for (tit = pTM->VECTOR_CLASS(ImageIndexList)[nRow]->m_vChildItem[0].vSQLData.begin(); tit != pTM->VECTOR_CLASS(ImageIndexList)[nRow]->m_vChildItem[0].vSQLData.end(); tit++)
			{
				ImageIndex *pSI = (ImageIndex*)tit->get();
				int nOrder = distance(pTM->VECTOR_CLASS(ImageIndexList)[nRow]->m_vChildItem[0].vSQLData.begin(), tit);
				switch (pSI->nType)
				{
				case 1: // text type
					if (nIndex == pSI->nStationNameBitmapIndex)
					{
						QAbstractItemModel *pModel = GET_TABLE(ImageIndex)->model();
						QModelIndex tempIndexX = pModel->index(nOrder, 6); // 6:pos x
						QModelIndex tempIndexY = pModel->index(nOrder, 7); // 7:pos y
						pModel->setData(tempIndexX, x);
						pModel->setData(tempIndexY, y);
					}
					break;
				case 2: // bitmap type
					if (nIndex == pSI->nStationBitmapIndex)
					{
						QAbstractItemModel *pModel = GET_TABLE(ImageIndex)->model();
						QModelIndex tempIndexX = pModel->index(nOrder, 6);
						QModelIndex tempIndexY = pModel->index(nOrder, 7);
						pModel->setData(tempIndexX, x);
						pModel->setData(tempIndexY, y);
					}
					break;
				}
			}
		}
	}
}