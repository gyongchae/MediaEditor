#include "editDisplayItemPool.h"
#include "tableViewHelper.h"
#include "DataManage.h"
#include "dataModel.h"
#include "DefineTables.h"
#include "qpideditor.h"
#include "displayItemPreset.h"
#include "comboBoxDelegate.h"
#include "MapManage.h"
#include <QDebug>
#include <map>
#include "DefineMode.h"

editDisplayItemPool::editDisplayItemPool(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	CALL_INIT_FUNCTION(DisplayItemPool);

	connect(ui.btnClose, SIGNAL(clicked()), this, SLOT(close()));

	if (OFFICIAL_RELEASE == true)
	{
		SET_HIDE_TABLE_COLUMN(DisplayItemPool, 0);
		SET_HIDE_TABLE_COLUMN(DisplayItemPool, 5);
		SET_HIDE_TABLE_COLUMN(DisplayItemPool, 6);
	}
}

editDisplayItemPool::~editDisplayItemPool()
{
}

IMPLEMENT_INIT_FUNCTION_FOR_CLASS(editDisplayItemPool, DisplayItemPool)
{
	auto *pDM = CDataManage::GetInstance();
	auto *pMM = CMapManage::GetInstance();

	SET_MODEL_FOR_TABLE_VIEW(DisplayItemPool, pDM);
	INSTALL_EVENT_FILTER(DisplayItemPool);
	SET_SELECTION_BEHAVIOR(DisplayItemPool, QAbstractItemView::SelectRows);
	SET_SELECTION_MODE(DisplayItemPool, QAbstractItemView::SingleSelection);
	SET_EDIT_TRIGGERS(DisplayItemPool, QAbstractItemView::NoEditTriggers);
	SET_DRAG_AND_DROP_ENABLED(DisplayItemPool);

	QHeaderView *header = GET_TABLE(DisplayItemPool)->horizontalHeader();
	header->resizeSections(QHeaderView::ResizeToContents);

	GET_TABLE(DisplayItemPool)->setItemDelegateForColumn(7, new comboBoxDelegate(this, &pMM->m_mDisplayPoolType));

	connect(GET_TABLE(DisplayItemPool), SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(insertmodifyDisplayItemPool(const QModelIndex&)));

	return false;
}

void editDisplayItemPool::addDisplayItemPool(bool bInsert)
{
	bool bAccepted = false;
	auto *pTM = CTableManage::GetInstance();
	auto *pDM = CDataManage::GetInstance();
	std::shared_ptr<dataModel> pDP = pDM->m_pModDisplayItemPool;
	int nRow;
	QModelIndex index = GET_TABLE(DisplayItemPool)->currentIndex();
	if (index.isValid())
	{
		nRow = index.row();
	}
	else
	{
		nRow = pDP->rowCount();
	}

	if (!bInsert)
		nRow = pDP->rowCount();

	pDP->insertRows(nRow, 1);
	index = pDP->index(nRow, 0);


	// display item editor 창 띄우기 전에 나오는 preset 다이얼로그
	displayItemPreset preset(nRow, this);
	if (preset.exec() == QDialog::Accepted)
	{
		bAccepted = true;
	}
	else
	{
		bAccepted = false;
		pDM->GET_MODEL_CLASS(DisplayItem)->setVectors(nullptr, nullptr);
		nRow = index.row();
		pDP->removeRows(nRow, 1);
		return;
	}

	if (index.isValid() && bAccepted && (nRow < pTM->VECTOR_CLASS(DisplayItemPool).size()))
	{
		DisplayItemPool *pTmpItm = (DisplayItemPool*)pTM->m_vDisplayItemPool[nRow].get();

		// display editor
		QPIDEditor tEditor(nRow, pTmpItm->nWidth, pTmpItm->nHeight, pTmpItm->nDuration * 1000, this);
		if (tEditor.exec() == QDialog::Accepted)
		{
			GET_TABLE(DisplayItemPool)->setCurrentIndex(index);
		}
		else
		{
			pDM->GET_MODEL_CLASS(DisplayItem)->setVectors(nullptr, nullptr);
			nRow = index.row();
			pDP->removeRows(nRow, 1);
		}
	}
	else
	{
		pDM->GET_MODEL_CLASS(DisplayItem)->setVectors(nullptr, nullptr);
		nRow = index.row();
		pDP->removeRows(nRow, 1);
	}
}

struct findInitScreenIndex : public std::unary_function<SHARED_PTRC(CSQLData), bool>
{
	findInitScreenIndex(const int index) { m_index = index; }
	bool operator()(SHARED_PTRC(CSQLData) &r) {
		auto *p = (DisplayItemPool*)GET_POINTEROF(r);
		return p->nDisplayType == m_index;
	}

	int m_index;
};

void editDisplayItemPool::deleteDisplayItemPool()
{
	int nRow;
	auto *pDM = CDataManage::GetInstance();
	std::shared_ptr<dataModel> pVFM = pDM->GET_MODEL_CLASS(DisplayItemPool);
	QModelIndex index = GET_TABLE(DisplayItemPool)->currentIndex();
	if (index.isValid())
	{
		int nRet = QMessageBox::warning(this, QString::fromStdWString(APPLICATION_NAME), QString::fromStdWString(ARE_YOU_SURE), QMessageBox::Yes | QMessageBox::No);
		if (nRet == QMessageBox::Yes)
		{
			nRow = index.row();
			pVFM->removeRows(nRow, 1);
		}
	}
}


bool editDisplayItemPool::eventFilter(QObject *object, QEvent *event)
{
	auto *pDM = CDataManage::GetInstance();
	QModelIndex index;
	if (event->type() == QEvent::KeyPress)
	{
		QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
		if (keyEvent->key() == Qt::Key_Delete)
		{
			if (object == GET_TABLE(DisplayItemPool))
			{
				deleteDisplayItemPool();
			}

			return true;
		}
		else if (keyEvent->key() == Qt::Key_F9)
		{
			if (object == GET_TABLE(DisplayItemPool))
			{
				addDisplayItemPool(false);
			}

			return true;
		}
		else if (keyEvent->key() == Qt::Key_Insert)
		{
			if (object == GET_TABLE(DisplayItemPool))
			{
				addDisplayItemPool(true);
			}

			return true;
		}

	}
	return false;
}

void editDisplayItemPool::closeEvent(QCloseEvent * ev)
{
	auto *pMM = CMapManage::GetInstance();

	/**************************************************************************************************************************************************************
	// how to get matching key using the value in a map C++ (link:https://stackoverflow.com/questions/12742472/how-to-get-matching-key-using-the-value-in-a-map-c)
	auto findResult = std::find_if(std::begin(pMM->m_mDisplayPoolType), std::end(pMM->m_mDisplayPoolType), [&](const std::pair<int, std::wstring> &pair)
	{
		return pair.second == L"PID Startup";
	}
	);

	int foundKey = 0;
	std::wstring foundVal;

	if (findResult != std::end(pMM->m_mDisplayPoolType))
	{
		foundKey = findResult->first;
		foundVal = std::wstring(findResult->second);
	}
	**************************************************************************************************************************************************************/

	int nDrmStartupIndex = -1;
	int nPidStartupIndex = -1;
	for (auto &i : pMM->m_mDisplayPoolType) {
		if (i.second == L"DRMD Startup") {
			nDrmStartupIndex = i.first;
		}

		if (i.second == L"PID Startup") {
			nPidStartupIndex = i.first;
		}
	}

	int nDrmStartupCount = 0;
	int nPidStartupCount = 0;

	auto *pTM = CTableManage::GetInstance();

	for (auto a : pTM->m_vDisplayItemPool)
	{
		auto *p = (DisplayItemPool*)a.get();
		if (p->nDisplayType == nDrmStartupIndex)
		{
			++nDrmStartupCount;
		}

		if (p->nDisplayType == nPidStartupIndex)
		{
			++nPidStartupCount;
		}
	}
	
	if (nDrmStartupCount == 1 && nPidStartupCount == 1)
	{
		ev->accept();
	}
	else
	{
		// get output
		/*
				QMessageBox box(this);
		box.setWindowTitle("Startup Display Selection Warning");
		box.setText(QString("DRMD Startup Display: %1\n"
			"PID Startup Display: %2\n\n"
			"Please select DRMD & PID Startup displays one each.\n\n"
			"Do you want to close?").arg(nDrmStartupCount).arg(nPidStartupCount));
		*/
		int result = QMessageBox::warning(this, "Startup Display Selection Error",
			QString("DRMD Startup Display: %1\n"
				"PID Startup Display: %2\n\n"
				"Please select DRMD & PID Startup displays one each.\n\n"
				"Do you want to close? (If multiple startup types are set, the values set in the row below are ignored.)").arg(nDrmStartupCount).arg(nPidStartupCount),
			QMessageBox::Ok | QMessageBox::Cancel);
		
		if(QMessageBox::Ok == result)
			ev->accept();
		else
			ev->accept();
	}
}

void editDisplayItemPool::insertmodifyDisplayItemPool(const QModelIndex &index)
{
	auto *pTM = CTableManage::GetInstance();
	int nRow = index.row();
	if (GET_TABLE(DisplayItemPool) == sender())
	{
		if (nRow < pTM->VECTOR_CLASS(DisplayItemPool).size())
		{
			DisplayItemPool *pTmpItm = (DisplayItemPool*)pTM->m_vDisplayItemPool[nRow].get();
			QPIDEditor tEditor(nRow, pTmpItm->nWidth, pTmpItm->nHeight, pTmpItm->nDuration * 1000, this);
			if (tEditor.exec() == QDialog::Accepted)
			{
				GET_TABLE(DisplayItemPool)->setCurrentIndex(index);
			}
		}
		GET_TABLE(DisplayItemPool)->resizeRowsToContents();
		GET_TABLE(DisplayItemPool)->resizeColumnsToContents();
	}
}
