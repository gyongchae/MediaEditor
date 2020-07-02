#include "ledindicatorpool.h"
#include "ledIndicatorDelegate.h"
#include "ledindicatorIndirectdelegate.h"
#include "ledindicatoredit.h"
#include "dataManage.h"
#include "dataModel.h"
#include "tableViewHelper.h"
#include <QSqlRelationalDelegate>
#include "editordelegate.h"
#include <QDebug>
#include "DefineMode.h"

LEDIndicatorPool::LEDIndicatorPool(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	auto *pDM = CDataManage::GetInstance();

	initEDDTable();
	initETNDTable();
	initEDDIndexListTable();
	initEDDIndexTable();

	SET_EVENT_TABLE(pDM,EDDIndex);
	SET_EVENT_TABLE(pDM,EDDIndexList);

	if (RELEASE_MODE == true)
	{
		SET_HIDE_TABLE_COLUMN(ETNDIndicator, 0);
		SET_HIDE_TABLE_COLUMN(ETNDIndicator, 2);
		SET_HIDE_TABLE_COLUMN_RANGE(ETNDIndicator, 4, 9);
		SET_HIDE_TABLE_COLUMN(EDDIndicator, 0);
		SET_HIDE_TABLE_COLUMN(EDDIndicator, 2);
		SET_HIDE_TABLE_COLUMN_RANGE(EDDIndicator, 4, 9);
		SET_HIDE_TABLE_COLUMN(EDDIndex, 0);
		SET_HIDE_TABLE_COLUMN(EDDIndex, 3);
		SET_HIDE_TABLE_COLUMN(EDDIndexList, 0);
		SET_HIDE_TABLE_COLUMN(EDDIndexList, 1);
		SET_HIDE_TABLE_COLUMN(EDDIndexList, 2);
	}
}

LEDIndicatorPool::~LEDIndicatorPool()
{
}

void LEDIndicatorPool::initEDDTable()
{
	auto *pDM = CDataManage::GetInstance();

	ui.m_tblEDDIndicator->setModel((QAbstractItemModel*)GET_TABLE_MODEL(pDM,EDDIndicator).get());
	ui.m_tblEDDIndicator->setItemDelegate(new QSqlRelationalDelegate(this));

	ui.m_tblEDDIndicator->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.m_tblEDDIndicator->setSelectionBehavior(QAbstractItemView::SelectRows);
	
	ui.m_tblEDDIndicator->resizeColumnsToContents();
	ui.m_tblEDDIndicator->setEditTriggers(QAbstractItemView::NoEditTriggers);

	ui.m_tblEDDIndicator->setItemDelegateForColumn(3,new LEDIndicatorDelegate(4,5,7,8,3,6,this));
	ui.m_tblEDDIndicator->installEventFilter(this);

	ui.m_tblEDDIndicator->resizeColumnsToContents();
	ui.m_tblEDDIndicator->resizeRowsToContents();



	connect(ui.m_tblEDDIndicator,SIGNAL(doubleClicked(const QModelIndex&)),this,SLOT(doubleClickedEDD(const QModelIndex&)));

}

void LEDIndicatorPool::initETNDTable()
{
	auto *pDM = CDataManage::GetInstance();

	ui.m_tblETNDIndicator->setModel((QAbstractItemModel*)GET_TABLE_MODEL(pDM,ETNDIndicator).get());
	ui.m_tblETNDIndicator->setItemDelegate(new QSqlRelationalDelegate(this));

	ui.m_tblETNDIndicator->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.m_tblETNDIndicator->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.m_tblETNDIndicator->resizeColumnsToContents();
	ui.m_tblETNDIndicator->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.m_tblETNDIndicator->setItemDelegateForColumn(1,new editorDelegate(this));

	ui.m_tblETNDIndicator->setItemDelegateForColumn(3,new LEDIndicatorDelegate(4,5,7,8,3,6,this));
	ui.m_tblETNDIndicator->installEventFilter(this);

	ui.m_tblETNDIndicator->resizeColumnsToContents();
	ui.m_tblETNDIndicator->resizeRowsToContents();

	connect(ui.m_tblETNDIndicator,SIGNAL(doubleClicked(const QModelIndex&)),this,SLOT(doubleClickedETND(const QModelIndex&)));

}


void LEDIndicatorPool::addETND(bool bInsert)
{
	int nRow;
	auto *pDM = CDataManage::GetInstance();
	std::shared_ptr<dataModel> pLEDM=pDM->m_pModETNDIndicator;
	QModelIndex index=ui.m_tblETNDIndicator->currentIndex();
	if(index.isValid())
	{
		nRow=index.row();
	}
	else
	{
		nRow=pLEDM->rowCount();
	}

	if(!bInsert)
		nRow=pLEDM->rowCount();

	pLEDM->insertRows(nRow,1);
	index=pLEDM->index(nRow,0);


	LEDIndicatorEdit modifyDlg(index,4,5,7,8,3,6,this);
	if(modifyDlg.exec()==QDialog::Accepted)
	{
		ui.m_tblETNDIndicator->setCurrentIndex(index);
	}
	else
	{
		nRow=index.row();
		pLEDM->removeRows(nRow,1);
	}

	ui.m_tblETNDIndicator->resizeColumnsToContents();
	ui.m_tblETNDIndicator->resizeRowsToContents();

}

void LEDIndicatorPool::deleteETND()
{
	int nRow;
	auto *pDM = CDataManage::GetInstance();
	std::shared_ptr<dataModel> pETND=pDM->m_pModETNDIndicator;
	QModelIndex index=ui.m_tblETNDIndicator->currentIndex();
	if(index.isValid())
	{
		int ret = QMessageBox::warning(this,QString::fromStdWString(APPLICATION_NAME),QString::fromStdWString(ARE_YOU_SURE),QMessageBox::Yes|QMessageBox::No);
		if(ret==QMessageBox::Yes)
		{
			nRow=index.row();
			pETND->removeRows(nRow,1);
		}
	}
}




void LEDIndicatorPool::doubleClickedETND(const QModelIndex& index)
{
	int nColumn=index.column();
	if(nColumn==3)
	{
		ui.m_tblETNDIndicator->setEditTriggers(QAbstractItemView::NoEditTriggers);
		LEDIndicatorEdit modifyDlg(index,4,5,7,8,3,6,this);
		modifyDlg.exec();
		ui.m_tblETNDIndicator->resizeColumnsToContents();
		ui.m_tblETNDIndicator->resizeRowsToContents();
	}
	else
		ui.m_tblETNDIndicator->setEditTriggers(QAbstractItemView::DoubleClicked);
}











void LEDIndicatorPool::addEDD(bool bInsert)
{
	int nRow;
	auto *pDM = CDataManage::GetInstance();
	std::shared_ptr<dataModel> pLEDM=pDM->m_pModEDDIndicator;
	QModelIndex index=ui.m_tblEDDIndicator->currentIndex();
	if(index.isValid())
	{
		nRow=index.row();
	}
	else
	{
		nRow=pLEDM->rowCount();
	}

	if(!bInsert)
		nRow=pLEDM->rowCount();

	pLEDM->insertRows(nRow,1);
	index=pLEDM->index(nRow,0);

	LEDIndicatorEdit modifyDlg(index,4,5,7,8,3,6,this);
	if(modifyDlg.exec()==QDialog::Accepted)
	{
		ui.m_tblEDDIndicator->setCurrentIndex(index);
	}
	else
	{
		nRow=index.row();
		pLEDM->removeRows(nRow,1);
	}

	ui.m_tblEDDIndicator->resizeColumnsToContents();
	ui.m_tblEDDIndicator->resizeRowsToContents();

}

void LEDIndicatorPool::deleteEDD()
{
	int nRow;
	auto *pDM = CDataManage::GetInstance();
	std::shared_ptr<dataModel> pEDD=pDM->m_pModEDDIndicator;
	QModelIndex index=ui.m_tblEDDIndicator->currentIndex();
	if(index.isValid())
	{
		int ret = QMessageBox::warning(this,QString::fromStdWString(APPLICATION_NAME),QString::fromStdWString(ARE_YOU_SURE),QMessageBox::Yes|QMessageBox::No);
		if(ret==QMessageBox::Yes)
		{
			nRow=index.row();
			pEDD->removeRows(nRow,1);
		}
	}
}




void LEDIndicatorPool::doubleClickedEDD(const QModelIndex& index)
{
	int nColumn=index.column();
	if(nColumn==3)
	{
		ui.m_tblEDDIndicator->setEditTriggers(QAbstractItemView::NoEditTriggers);
		LEDIndicatorEdit modifyDlg(index,4,5,7,8,3,6,this);
		modifyDlg.exec();
		ui.m_tblEDDIndicator->resizeColumnsToContents();
		ui.m_tblEDDIndicator->resizeRowsToContents();
	}
	else
		ui.m_tblEDDIndicator->setEditTriggers(QAbstractItemView::DoubleClicked);
}






void LEDIndicatorPool::addRowToTable(bool bInsert,QTableView *pView,dataModel *pModel)
{
	if(pView&&pModel)
	{
		int nRow;
		QModelIndex index=pView->currentIndex();
		if(index.isValid())
		{
			nRow=index.row();
		}
		else
		{
			nRow=pModel->rowCount();
		}
		if(bInsert)
			nRow=pModel->rowCount();
		pModel->insertRows(nRow,1);
		index=pModel->index(nRow,0);
		pView->setCurrentIndex(index);	
		pView->edit(index);
	}
}

void LEDIndicatorPool::deleteRowFromTable(QTableView *pView,dataModel *pModel)
{
	int nRow;
	if(pView&&pModel)
	{
		QModelIndex indexParent=pView->currentIndex();
		if(indexParent.isValid())
		{
			QModelIndex index=pView->currentIndex();
			if(index.isValid())
			{
				int ret = QMessageBox::warning(this,QString::fromStdWString(L"Delete?"),QString::fromStdWString(L"Delete?"),QMessageBox::Yes|QMessageBox::No);
				if(ret==QMessageBox::Yes)
				{
					nRow=index.row();
					pModel->removeRows(nRow,1);
				}
			}
		}
	}
}

bool LEDIndicatorPool::eventFilter(QObject *object, QEvent *event)
{
	std::map<QTableView*,std::shared_ptr<dataModel>>::iterator nit= m_mEventTable.find((QTableView*)object);
	if(event->type()==QEvent::KeyPress)
	{
		QKeyEvent *keyEvent=static_cast<QKeyEvent*>(event);
		if(nit!=m_mEventTable.end())
		{
			if(object==nit->first)
			{
				switch(keyEvent->key())
				{
				case Qt::Key_Delete://Delete
					
					deleteRowFromTable(nit->first,nit->second.get());
					break;
				case Qt::Key_Insert://Insert
					addRowToTable(false,nit->first,nit->second.get());
					break;
				case Qt::Key_F9://Append
					addRowToTable(true,nit->first,nit->second.get());
					break;
				}
				return QDialog::eventFilter(object,event);
			}
		}
		else if(object==ui.m_tblEDDIndicator)
		{
			switch(keyEvent->key())
			{
			case Qt::Key_Delete://Delete
				deleteEDD();
				return true;
			case Qt::Key_Insert://Insert
				addEDD(true);
				return true;
			case Qt::Key_F9://Append
				addEDD(false);
				return true;
			}
			return QDialog::eventFilter(object,event);
		}
		else if(object==ui.m_tblETNDIndicator)
		{
			switch(keyEvent->key())
			{
			case Qt::Key_Delete://Delete
				deleteETND();
				return true;
			case Qt::Key_Insert://Insert
				addETND(true);
				return true;
			case Qt::Key_F9://Append
				addETND(false);
				return true;
			}
			return QDialog::eventFilter(object,event);
		}
	}
	return QDialog::eventFilter(object,event);
}

bool LEDIndicatorPool::initEDDIndexTable()
{
	auto *pDM = CDataManage::GetInstance();
	ui.m_tblEDDIndex->setModel((QAbstractItemModel*)pDM->m_pModEDDIndex.get());
	ui.m_tblEDDIndex->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.m_tblEDDIndex->setSelectionMode(QAbstractItemView::SingleSelection);
	QHeaderView *header=ui.m_tblEDDIndex->horizontalHeader();
	ui.m_tblEDDIndex->installEventFilter(this);
	connect(ui.m_tblEDDIndex->selectionModel(),SIGNAL(currentRowChanged(const QModelIndex &,const QModelIndex &)),this,SLOT(updateEDDIndexList()));
	return true;
}

bool LEDIndicatorPool::initEDDIndexListTable()
{
	auto *pDM = CDataManage::GetInstance();
	auto *pTM=CTableManage::GetInstance();
	ui.m_tblEDDIndexList->setModel((QAbstractItemModel*)pDM->m_pModEDDIndexList.get());
	
	ui.m_tblEDDIndexList->setItemDelegateForColumn(3,new LEDIndicatorIndirectDelegate(128,32,4,4,5,7,8,3,6,&pTM->VECTOR_CLASS(EDDIndicator),this));

	ui.m_tblEDDIndexList->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.m_tblEDDIndexList->setSelectionMode(QAbstractItemView::SingleSelection);

	QHeaderView *header=ui.m_tblEDDIndexList->horizontalHeader();

	ui.m_tblEDDIndexList->installEventFilter(this);
	//connect(ui.m_tblEDDIndexList->selectionModel(),SIGNAL(currentRowChanged(const QModelIndex &,const QModelIndex &)),this,SLOT(updateDistanceEvent()));
	return true;
}


void LEDIndicatorPool::updateEDDIndexList()
{
	QModelIndex index=ui.m_tblEDDIndex->currentIndex();
	auto *pDM = CDataManage::GetInstance();
	auto *pTM=CTableManage::GetInstance();
	if(index.isValid())
	{
		int nRow=index.row();
		if(nRow<pTM->VECTOR_CLASS(EDDIndex).size())
		{
			GET_TABLE_MODEL(pDM,EDDIndexList)->setVectors(&pTM->VECTOR_CLASS(EDDIndex)[nRow]->m_vChildItem[0].vSQLData,&pTM->VECTOR_CLASS(EDDIndex)[nRow]->m_vChildItem[0].vSQLDataDelItems,pTM->VECTOR_CLASS(EDDIndex)[nRow].get()->GetIndex());
		}
	}
	else
	{
		GET_TABLE_MODEL(pDM,EDDIndexList)->setVectors(nullptr,nullptr);
	}
}