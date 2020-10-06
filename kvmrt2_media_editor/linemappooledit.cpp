#include "linemappooledit.h"
#include "tableViewHelper.h"
#include "DataManage.h"
#include "dataModel.h"
#include "DefineTables.h"
#include "LineMapPreset.h"
#include "QLineMapEdit.h"
#include <QtGui>
#include <qdebug.h>
#include "DefineMode.h"

LineMapPoolEdit::LineMapPoolEdit(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	CALL_INIT_FUNCTION(LineMapPool);

	connect(ui.btnClose, SIGNAL(clicked()), this, SLOT(close()));

	connect(ui.btnAddMap, &QPushButton::clicked, [this]() {
		addLineMapPool(false);
	});

	connect(ui.btnDelMap, &QPushButton::clicked, [this]() {
		deleteLineMapPool();
	});

	if (OFFICIAL_RELEASE == true)
	{
		SET_HIDE_TABLE_COLUMN(LineMapPool, 0);
		SET_HIDE_TABLE_COLUMN(LineMapPool, 4);
		SET_HIDE_TABLE_COLUMN(LineMapPool, 5);
		SET_HIDE_TABLE_COLUMN_RANGE(LineMapPool, 8, 23);
	}
}

LineMapPoolEdit::~LineMapPoolEdit()
{
}

IMPLEMENT_INIT_FUNCTION_FOR_CLASS(LineMapPoolEdit,LineMapPool)
{
	auto *pDM = CDataManage::GetInstance();
	SET_MODEL_FOR_TABLE_VIEW(LineMapPool, pDM);
	INSTALL_EVENT_FILTER(LineMapPool);

	SET_SELECTION_BEHAVIOR(LineMapPool, QAbstractItemView::SelectRows);
	SET_SELECTION_MODE(LineMapPool, QAbstractItemView::SingleSelection);
	SET_DRAG_AND_DROP_ENABLED(LineMapPool);
	SET_EDIT_TRIGGERS(LineMapPool, QAbstractItemView::NoEditTriggers);

	QHeaderView *header=GET_TABLE(LineMapPool)->horizontalHeader();
	header->resizeSections(QHeaderView::ResizeToContents);

	connect(GET_TABLE(LineMapPool),SIGNAL(doubleClicked(const QModelIndex&)),this,SLOT(insertmodifyLineMapPool(const QModelIndex&)));	
	return false;
}

void LineMapPoolEdit::addLineMapPool(bool bInsert)
{
	bool bAccepted=false;
	auto *pTM=CTableManage::GetInstance();
	auto *pDM = CDataManage::GetInstance();
	std::shared_ptr<dataModel> pLMP=pDM->m_pModLineMapPool;
	int nRow;
	QModelIndex index=GET_TABLE(LineMapPool)->currentIndex();
	if(index.isValid())
	{
		nRow=index.row();
	}
	else
	{
		nRow=pLMP->rowCount();
	}

	if(!bInsert)
		nRow=pLMP->rowCount();

	pLMP->insertRows(nRow,1);
	index=pLMP->index(nRow,0);
	if(index.isValid())
	{
		LineMapPreset lineMapPreset(nRow,this);
		if(lineMapPreset.exec()==QDialog::Accepted)
		{
			bAccepted=true;
		}
		else
		{
			bAccepted=false;
			pDM->GET_MODEL_CLASS(LineMapLink)->setVectors(nullptr,nullptr);
			nRow=index.row();
			pLMP->removeRows(nRow,1);
		}
	}

	if(bAccepted&&(nRow<pTM->VECTOR_CLASS(LineMapPool).size()))
	{
		QLineMapEdit linemapEdit(nRow, this);
		if(linemapEdit.exec()!=QDialog::Accepted)
		{
			pDM->GET_MODEL_CLASS(LineMapLink)->setVectors(nullptr,nullptr);
			nRow=index.row();
			pLMP->removeRows(nRow,1);
		}
	}
}


void LineMapPoolEdit::deleteLineMapPool()
{
	int nRow;
	auto *pDM = CDataManage::GetInstance();
	std::shared_ptr<dataModel> pVFM=pDM->GET_MODEL_CLASS(LineMapPool);
	QModelIndex index=GET_TABLE(LineMapPool)->currentIndex();
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


bool LineMapPoolEdit::eventFilter(QObject *object, QEvent *event)
{
	auto *pDM = CDataManage::GetInstance();
	QModelIndex index;
	if(event->type()==QEvent::KeyPress)
	{
		QKeyEvent *keyEvent=static_cast<QKeyEvent*>(event);
		if(keyEvent->key()==Qt::Key_Delete)
		{
			if(object==GET_TABLE(LineMapPool))
			{	
				deleteLineMapPool();
			}
			return true;
		}
		else if(keyEvent->key()==Qt::Key_F9)
		{
			if(object==GET_TABLE(LineMapPool))
			{	
				addLineMapPool(false);
			}
			return true;
		}
		else if(keyEvent->key()==Qt::Key_Insert)
		{
			if(object==GET_TABLE(LineMapPool))
			{	
				addLineMapPool(true);
			}
			return true;
		}
	}
	return false;
}

void LineMapPoolEdit::insertmodifyLineMapPool(const QModelIndex &index)
{
	auto *pDM = CDataManage::GetInstance();
	auto *pTM=CTableManage::GetInstance();
	int nRow=index.row();
	if(GET_TABLE(LineMapPool)==sender())
	{
		if(nRow<pTM->VECTOR_CLASS(LineMapPool).size())
		{
			QLineMapEdit linemapEdit(nRow, this);
			if(linemapEdit.exec()==QDialog::Accepted)
			{
				GET_TABLE(LineMapPool)->setCurrentIndex(index);
			}
		}
		GET_TABLE(LineMapPool)->resizeRowsToContents();
		GET_TABLE(LineMapPool)->resizeColumnsToContents();
	}
}
