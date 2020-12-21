#include <QtGui>
#include <QtCore>
#include <QDir>
#include <qdebug>

#include "dataModel.h"
#include "kvmrt2_media_editor.h"
#include "TableManage.h"
#include "DataManage.h"
#include "registrySettings.h"
#include "contentsPool.h"
#include "fontPool.h"
#include "stationImagePool.h"
#include "bitmapImagePool.h"
#include "lineMapPoolEdit.h"
#include "qtextaligner.h"
#include "TileMapSupport.h"
#include "imageListPool.h"
#include "ledindicatorpool.h"
#include "MapManage.h"
#include "editDisplayItemPool.h"
#include "QLineMapPreview.h"
#include "WaveConcentate/Wave.h"
#include "StringScaler.h"
#include "SQLDelegate.h"
#include "tableViewHelper.h"
#include "comboBoxDelegate.h"
#include "DefineMode.h"
#include <stdarg.h>
#include "DefineMode.h"
#include "IniFileManager.h"

const int added_duration = 0;
const int added_stn_name_duration = 0;

kvmrt2_media_editor::kvmrt2_media_editor(QString & dbPath, QString & currPath, QWidget * parent) : QMainWindow(parent)
{
	ui.setupUi(this);

	setWindowTitle(QString("%1")
		.arg(QApplication::applicationName()));

	CSQLData::SetLEDIndicatorParam(256, 24, 64, 32); // led size???
	auto *pDM = CDataManage::GetInstance();
	auto *pMM = CMapManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();

	pDM->setDBPath(dbPath.toStdWString().c_str());
	pDM->InitSettings(); // no use
	pDM->OpenDatabase();
	pDM->BeforeLoadFromDB(); // no use
	pMM->InitMaps();
	pTM->LoadDatabase();
	pDM->SetModel();
	
	pDM->setCurrPath(currPath);

	initTables();
	initActions();
	initMapData();
	initContextMenu();
	initIcons();

	initNewFeature();

	ui.rbCustomOrder->setChecked(true);

	if (pDM->m_pModOPDataVersion->rowCount() == 1)
	{
		QModelIndex index = pDM->m_pModOPDataVersion->index(0, 0);
		m_lastVersion[0] = pDM->m_pModOPDataVersion->data(index.sibling(0, 2), Qt::DisplayRole).toInt();
		m_lastVersion[1] = pDM->m_pModOPDataVersion->data(index.sibling(0, 3), Qt::DisplayRole).toInt();
		m_lastVersion[2] = pDM->m_pModOPDataVersion->data(index.sibling(0, 4), Qt::DisplayRole).toInt();
	}

	ui.statusBar->showMessage(QString("OP_DATA.DB(v%1.%2.%3) loaded. (%4)")
		.arg(m_lastVersion[0]).arg(m_lastVersion[1]).arg(m_lastVersion[2])
		.arg(QDateTime::currentDateTime().toString("hh:mm dd/MM/yyyy")));


	setHideItemsMainWindow(OFFICIAL_RELEASE);

	// audio sync duration
	connect(ui.actionSyncAudioDur, SIGNAL(triggered()), this, SLOT(onAudioSyncDuration()));

	// user info widget init
	m_widgetUserInfo = new UserInfoWidget;
	m_widgetUserInfo->setWindowIcon(pDM->m_iconUserInfo);
	connect(ui.actionUserInfo, SIGNAL(triggered()), this, SLOT(onShowUserInfo()));
}

kvmrt2_media_editor::~kvmrt2_media_editor()
{
}

void kvmrt2_media_editor::setHideItemsMainWindow(bool isRelease)
{
	if (isRelease)
	{
		// hidden action
		ui.actionNew->setVisible(false);
		ui.actionLoad->setVisible(false);
		ui.actionLedPool->setVisible(false);

		auto *pDM = CDataManage::GetInstance();
		auto *pTM = CTableManage::GetInstance();

		QGroupBox *parentTN = qobject_cast<QGroupBox*>(GET_TABLE(TrainNumber)->parent());
		QGroupBox *parentEL = qobject_cast<QGroupBox*>(GET_TABLE(EventLists)->parent());
		parentTN->setVisible(false);
		parentEL->setVisible(false);

		SET_HIDE_TABLE_COLUMN(StationInformation, 0);
		SET_HIDE_TABLE_COLUMN_RANGE(StationInformation, 5, 13);
		SET_HIDE_TABLE_COLUMN(StationInformation, 17);
		SET_HIDE_TABLE_COLUMN(StationInformation, 18);
		SET_HIDE_TABLE_COLUMN(StationDistance, 0);
		SET_HIDE_TABLE_COLUMN(StationDistance, 5);
		SET_HIDE_TABLE_COLUMN(StationDistance, 6);
		SET_HIDE_TABLE_COLUMN(StationDistance, 7);
		SET_HIDE_TABLE_COLUMN(StopPtnHeader, 0);
		SET_HIDE_TABLE_COLUMN(StopPtnHeader, 5);
		SET_HIDE_TABLE_COLUMN(StopPtnHeader, 6);

		SET_HIDE_TABLE_COLUMN(StopPtnRoutes, 0);
		SET_HIDE_TABLE_COLUMN(StopPtnRoutes, 1);
		SET_HIDE_TABLE_COLUMN(StopPtnRoutes, 2);
		SET_HIDE_TABLE_COLUMN(StopPtnRoutes, 4);
		SET_HIDE_TABLE_COLUMN(StopPtnRoutes, 5);
		SET_HIDE_TABLE_COLUMN(StopPtnRoutes, 6);
		SET_HIDE_TABLE_COLUMN_RANGE(StopPtnRoutes, 7, 12);
		SET_HIDE_TABLE_COLUMN(PIDContents, 0);
		SET_HIDE_TABLE_COLUMN_RANGE(PIDContents, 3, 8);
		SET_HIDE_TABLE_COLUMN_RANGE(PIDIndexList, 0, 2);

		SET_HIDE_TABLE_COLUMN(AudioStationName, 0);
		SET_HIDE_TABLE_COLUMN(AudioStationName, 1);
		SET_HIDE_TABLE_COLUMN(AudioStationName, 4);
		SET_HIDE_TABLE_COLUMN(AudioStationName, 5);
		SET_HIDE_TABLE_COLUMN(AudioStationName, 7);
		SET_HIDE_TABLE_COLUMN(AudioStationName, 8);

		SET_HIDE_TABLE_COLUMN(AudioPlayList, 0);
		SET_HIDE_TABLE_COLUMN(AudioPlayList, 1);
		SET_HIDE_TABLE_COLUMN(AudioPlayList, 3);
		SET_HIDE_TABLE_COLUMN(AudioPlayList, 4);
		SET_HIDE_TABLE_COLUMN(AudioPlayList, 6);
		SET_HIDE_TABLE_COLUMN(AudioPlayList, 7);
		SET_HIDE_TABLE_COLUMN(AudioPlayList, 10);
		SET_HIDE_TABLE_COLUMN(AudioPlayList, 11);
		SET_HIDE_TABLE_COLUMN(AudioPlayList, 13);
		SET_HIDE_TABLE_COLUMN(AudioPlayList, 14);
		SET_HIDE_TABLE_COLUMN(AudioPlayList, 16);
		SET_HIDE_TABLE_COLUMN(AudioPlayList, 17);
		SET_HIDE_TABLE_COLUMN(AudioPlayList, 19);
		SET_HIDE_TABLE_COLUMN(AudioPlayList, 20);

		SET_HIDE_TABLE_COLUMN(VideoDeviceGroup, 0);
		SET_HIDE_TABLE_COLUMN(VideoDeviceGroup, 1);
		SET_HIDE_TABLE_COLUMN(VideoDeviceGroup, 3); // group id (no use)
		SET_HIDE_TABLE_COLUMN(VideoPlayList, 0);
		SET_HIDE_TABLE_COLUMN(VideoPlayList, 1);
		SET_HIDE_TABLE_COLUMN(VideoPlayList, 4);
		SET_HIDE_TABLE_COLUMN(VideoPlayList, 6);
		SET_HIDE_TABLE_COLUMN(EditorTagTable, 0);
		SET_HIDE_TABLE_COLUMN(EditorTagTable, 3);
	}
}

void kvmrt2_media_editor::initTables()
{
	// CALL_INIT_FUNCTION
	CALL_INIT_FUNCTION(StationInformation);
	CALL_INIT_FUNCTION(StationDistance);
	CALL_INIT_FUNCTION(TrainNumber);
	CALL_INIT_FUNCTION(StopPtnHeader);
	CALL_INIT_FUNCTION(StopPtnRoutes);
	CALL_INIT_FUNCTION(EventLists);
	CALL_INIT_FUNCTION(PIDContents);
	CALL_INIT_FUNCTION(PIDIndexList);
	CALL_INIT_FUNCTION(AudioStationName);
	CALL_INIT_FUNCTION(AudioPlayList);
	CALL_INIT_FUNCTION(VideoDeviceGroup);
	CALL_INIT_FUNCTION(VideoPlayList);
	CALL_INIT_FUNCTION(EditorTagTable);
	// !CALL_INIT_FUNCTION
}

void kvmrt2_media_editor::initActions()
{
	// CONNECT_ACTION_TRIGGERED_SLOT
	CONNECT_ACTION_TRIGGERED_SLOT(ui.actionSave, onSaveDB);
	CONNECT_ACTION_TRIGGERED_SLOT(ui.actionSetting, onShowSetting);
	CONNECT_ACTION_TRIGGERED_SLOT(ui.actionAudioVideoPool, onShowAudioVideoPool);
	CONNECT_ACTION_TRIGGERED_SLOT(ui.actionFontPool, onShowFontPool);
	CONNECT_ACTION_TRIGGERED_SLOT(ui.actionTextPool, onShowTextPool);
	CONNECT_ACTION_TRIGGERED_SLOT(ui.actionRouteMapPool, onShowRouteMapPool);
	CONNECT_ACTION_TRIGGERED_SLOT(ui.actionBitmapPool, onShowBitmapPool);
	CONNECT_ACTION_TRIGGERED_SLOT(ui.actionImageListPool, onShowImageListPool);
	CONNECT_ACTION_TRIGGERED_SLOT(ui.actionLedPool, onShowLedPool);
	CONNECT_ACTION_TRIGGERED_SLOT(ui.actionDisplayListPool, onShowDisplayListPool);
	CONNECT_ACTION_TRIGGERED_SLOT(ui.actionUpdate, onShowFileUpload);
	CONNECT_ACTION_TRIGGERED_SLOT(ui.actionExit, close);
	// !CONNECT_ACTION_TRIGGERED_SLOT

	CONNECT_ACTION_TRIGGERED_SLOT(ui.actionLoad, onLoadDB);

	connect(ui.actionAboutME, &QAction::triggered, this, &kvmrt2_media_editor::aboutME);
	connect(ui.actionAboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);
	connect(ui.actionLicenseInfo, &QAction::triggered, this, &kvmrt2_media_editor::licenseInfo);
}

void kvmrt2_media_editor::initMapData()
{
	auto *pDM = CDataManage::GetInstance();
	// SET_EVENT_TABLE
	SET_EVENT_TABLE(pDM, StationInformation);
	SET_EVENT_TABLE(pDM, StationDistance);
	SET_EVENT_TABLE(pDM, TrainNumber);
	SET_EVENT_TABLE(pDM, StopPtnHeader);
	SET_EVENT_TABLE(pDM, StopPtnRoutes);
	SET_EVENT_TABLE(pDM, EventLists);
	SET_EVENT_TABLE(pDM, PIDContents);
	SET_EVENT_TABLE(pDM, PIDIndexList);
	SET_EVENT_TABLE(pDM, AudioPlayList);
	SET_EVENT_TABLE(pDM, AudioStationName);
	SET_EVENT_TABLE(pDM, VideoDeviceGroup);
	SET_EVENT_TABLE(pDM, VideoPlayList);
	SET_EVENT_TABLE(pDM, EditorTagTable);
	// !SET_EVENT_TABLE
}

void kvmrt2_media_editor::initIcons()
{
	auto *pDM = CDataManage::GetInstance();
	setWindowIcon(pDM->m_iconMain);

	// action on toolbar
	ui.actionNew->setIcon(pDM->m_iconNew);
	ui.actionSave->setIcon(pDM->m_iconSave);
	ui.actionLoad->setIcon(pDM->m_iconLoad);
	ui.actionSetting->setIcon(pDM->m_iconSetting);
	ui.actionFontPool->setIcon(pDM->m_iconFont);
	ui.actionAudioVideoPool->setIcon(pDM->m_iconAudioVideo);
	ui.actionTextPool->setIcon(pDM->m_iconText);
	ui.actionBitmapPool->setIcon(pDM->m_iconBitmap);
	ui.actionImageListPool->setIcon(pDM->m_iconImageList);
	ui.actionDisplayListPool->setIcon(pDM->m_iconDisplayPool);
	ui.actionRouteMapPool->setIcon(pDM->m_iconRouteMap);
	ui.actionLedPool->setIcon(pDM->m_iconLED);
	ui.actionUpdate->setIcon(pDM->m_iconUpdate);

	ui.actionUserInfo->setIcon(pDM->m_iconUserInfo);

	ui.actionExit->setIcon(pDM->m_iconExit);

	ui.actionAboutME->setIcon(pDM->m_iconMain);
	ui.actionAboutQt->setIcon(pDM->m_iconQt);
	ui.actionLicenseInfo->setIcon(pDM->m_iconLicense);

	ui.tabMain->setTabIcon(0, pDM->m_iconTabStnInfo);
	ui.tabMain->setTabIcon(1, pDM->m_iconTabTrainRoute);
	ui.tabMain->setTabIcon(2, pDM->m_iconTabScreenCon);
	ui.tabMain->setTabIcon(3, pDM->m_iconTabAudioCon);
	ui.tabMain->setTabIcon(4, pDM->m_iconTabVideoCon);
	ui.tabMain->setTabIcon(5, pDM->m_iconTabDataTag);
}

bool kvmrt2_media_editor::eventFilter(QObject *object, QEvent *event)
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
					addRowToTable(true, nit.key(), nit.value().get());
					break;
				case Qt::Key_F9://Append
					addRowToTable(false, nit.key(), nit.value().get());
					break;
				}
				return QMainWindow::eventFilter(object, event);
			}
		}
	}
	return QMainWindow::eventFilter(object, event);
}

void kvmrt2_media_editor::closeEvent(QCloseEvent *event)
{
	auto *pTM = CTableManage::GetInstance();
	pTM->CloseDatabase();
}

// db file version up slot (no use yet)
void kvmrt2_media_editor::updateVideoFileVersion()
{
	auto *pDM = CDataManage::GetInstance();
	pDM->SetVideoFileVersion();
}

void kvmrt2_media_editor::addRowToTable(bool bInsert, QTableView *pView, dataModel *pModel)
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
		if (!bInsert)
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

bool kvmrt2_media_editor::deleteRowFromTable(QTableView *pView, dataModel *pModel)
{
	int nRow;
	if (pView)
	{
		QModelIndex index = pView->currentIndex();
		if (index.isValid())
		{
			int ret = QMessageBox::warning(this, QString::fromStdWString(L"Delete seletcted item"), QString::fromStdWString(ARE_YOU_SURE), QMessageBox::Yes | QMessageBox::No);
			if (ret == QMessageBox::Yes)
			{
				nRow = index.row();
				pView->model()->removeRows(nRow, 1);
				return true;
			}
		}
	}
	return false;
}

void kvmrt2_media_editor::onSaveDB()
{
	auto *pTM = CTableManage::GetInstance();
	auto *pDM = CDataManage::GetInstance();


	int currVersion[3]{ 0 };
	QModelIndex index = pDM->m_pModOPDataVersion->index(0, 0);
	currVersion[0] = pDM->m_pModOPDataVersion->data(index.sibling(0, 2), Qt::DisplayRole).toInt();
	currVersion[1] = pDM->m_pModOPDataVersion->data(index.sibling(0, 3), Qt::DisplayRole).toInt();
	currVersion[2] = pDM->m_pModOPDataVersion->data(index.sibling(0, 4), Qt::DisplayRole).toInt();

	int mbResult = QMessageBox::information(this, QString("Save OP_DATA.DB"),
		QString("Do you want to save OP_DATA.DB(version %1.%2.%3)?").arg(currVersion[0]).arg(currVersion[1]).arg(currVersion[2]),
		QMessageBox::Ok | QMessageBox::Cancel);

	if (mbResult == QMessageBox::Ok)
	{
		for (int i = 0; i < 3; ++i)
		{
			if (currVersion[i] != m_lastVersion[i])
			{
				qDebug("version[%d] %d -> %d changed", i, m_lastVersion[i], currVersion[i]);
			}
			else
			{

			}
		}

		setCursor(Qt::WaitCursor);
		pTM->SaveModified();

		ui.statusBar->showMessage(QString("OP_DATA.DB(v%1.%2.%3) has been saved. (%4)")
			.arg(currVersion[0]).arg(currVersion[1]).arg(currVersion[2])
			.arg(QDateTime::currentDateTime().toString("hh:mm dd/MM/yyyy")));
		// refresh ini file
		onAudioSyncDuration();
		setCursor(Qt::ArrowCursor);
	}
	else
	{
		QMessageBox::information(this,  "Save canceled", "OP_DATA.DB didn't saved.");
	}
}

// for test func
void kvmrt2_media_editor::onLoadDB()
{
	auto *ini = IniFileManager::iniManager();
	int totalStationInfoRows = GET_TABLE(StationInformation)->model()->rowCount();
	for (int i = 0; i < totalStationInfoRows; i++)
	{
		QModelIndex stnIndex = GET_TABLE(StationInformation)->model()->index(i, 0);
		int stnCode = stnIndex.sibling(stnIndex.row(), 1).data().toInt();
		ini->readStationInfoIni(stnCode);
	}
	ini->readAudioListInfoIni();
}

void kvmrt2_media_editor::onShowSetting() // DB version setting
{
	RegistrySettings regDialog(this);
	if (regDialog.exec())
	{

	}
}

void kvmrt2_media_editor::onShowAudioVideoPool()
{
	ContentsPool audioVideoPool(this);
	if (audioVideoPool.exec())
	{

	}
}

void kvmrt2_media_editor::onShowFontPool()
{
	fontPool fontPool(this);
	if (fontPool.exec())
	{

	}
}

void kvmrt2_media_editor::onShowRouteMapPool()
{
	auto *pTM = CTableManage::GetInstance();
	LineMapPoolEdit mapPoolEdit(this);
	if (mapPoolEdit.exec())
	{

	}
}

void kvmrt2_media_editor::onShowTextPool()
{
	stationImagePool textPool(this);
	if (textPool.exec())
	{

	}
}

void kvmrt2_media_editor::onShowBitmapPool()
{
	bitmapImagePool bitmapPool(this);
	if (bitmapPool.exec())
	{

	}
}

void kvmrt2_media_editor::onShowImageListPool()
{
	imageListPool imageListPool(this);
	if (imageListPool.exec())
	{

	}
}

void kvmrt2_media_editor::onShowLedPool()
{
	LEDIndicatorPool ledPool(this);
	if (ledPool.exec())
	{

	}
}

void kvmrt2_media_editor::onShowDisplayListPool()
{
	editDisplayItemPool displayListPool(this);
	if (displayListPool.exec())
	{

	}
}

void kvmrt2_media_editor::onShowFileUpload()
{
	QProcess *process = new QProcess(this);
	QStringList arguments;
	arguments << "ME";
	process->start(QString(WIZARD_FILE_PATH), arguments);
	process->waitForFinished();
	int exitCode = process->exitCode();
	qDebug() << Q_FUNC_INFO << "exit code" << exitCode;
	//process->close();
}

void kvmrt2_media_editor::onShowUserInfo()
{
	m_widgetUserInfo->setWindowFlags(Qt::Window);
	m_widgetUserInfo->show();
}

void kvmrt2_media_editor::onBtnRefreshDistanceTable()
{
	/*
	��ü �� ���� �ľ�
	�� �� ����
	departure, arrival, distance
	��ü ����� �ڵ� ����

	[��������]
	station information table�� ����/���ڵ尡 ����� ��� departure/arrival�� ���� �ڵ����� �ٲ��� ��.
	*/
	auto *pTM = CTableManage::GetInstance();
	auto *pDM = CDataManage::GetInstance();
	bool bOKDep;
	bool bOKArr;
	bool bOKDistance;
	int nDistance;
	QString strDesc;

	int totalRow = GET_TABLE(StationDistance)->model()->rowCount();
	for (int i = 0; i < totalRow; ++i)
	{
		QModelIndex topLeft = GET_TABLE(StationDistance)->model()->index(i, 0);
		int nTotalDistance = 0;
		if (topLeft.isValid())
		{
			int nRow = topLeft.row();
			int nColumn = topLeft.column();
			bool bOk, bParentOk;
			int nDepStn = 0, nArrStn = 0;

			nDepStn = topLeft.sibling(topLeft.row(), 1/*departure col*/).data().toInt(&bOKDep);
			nArrStn = topLeft.sibling(topLeft.row(), 2/*arrival col*/).data().toInt(&bOKArr);
			nDistance = topLeft.sibling(topLeft.row(), 3/*distance col*/).data().toInt(&bOKDistance);

			if ((nDepStn&&nArrStn) || nDistance)
			{
				std::vector<std::shared_ptr<CSQLData>>::iterator itSt, itEn;
				itSt = find_if(pTM->VECTOR_CLASS(StationInformation).begin(), pTM->VECTOR_CLASS(StationInformation).end(), findSQLData(nDepStn));
				itEn = find_if(pTM->VECTOR_CLASS(StationInformation).begin(), pTM->VECTOR_CLASS(StationInformation).end(), findSQLData(nArrStn));
				if ((itSt != pTM->VECTOR_CLASS(StationInformation).end()) && (itEn != pTM->VECTOR_CLASS(StationInformation).end()))
				{
					StationInformation *pSt = (StationInformation*)itSt->get();
					StationInformation *pEn = (StationInformation*)itEn->get();
					StationDistance* pDistance = (StationDistance*)pTM->VECTOR_CLASS(StationDistance).at(topLeft.row()).get();
					strDesc = QString("[%1]%2 -> [%3]%4 (%5m)")
						.arg(QString::number(pSt->nStationCode))
						.arg(QString::fromStdWString(pSt->szStationName1))
						.arg(QString::number(pEn->nStationCode))
						.arg(QString::fromStdWString(pEn->szStationName1))
						.arg(QString::number(pDistance->nDistance))
						;
					GET_TABLE_MODEL(pDM, StationDistance)->setData(topLeft.sibling(topLeft.row(), 4), strDesc, Qt::EditRole);
					GET_TABLE_MODEL(pDM, StationDistance)->setData(topLeft.sibling(topLeft.row(), 6), pSt->nStationCode, Qt::EditRole);
					GET_TABLE_MODEL(pDM, StationDistance)->setData(topLeft.sibling(topLeft.row(), 7), pEn->nStationCode, Qt::EditRole);
				}
			}
		}
	}
}

void kvmrt2_media_editor::onBtnRouteAutoAdd()
{
	/*
	���� ����
	1. �� �ڵ�� 1�� �����Ѵ�. (�� ���� �� �߻���)
	2. �Ÿ� ���̺� �� �ֵ��� ��߿�-������ �� �ڵ尡 1�� ���̳���.
	�� �ڵ尡 �ƴ϶� table order�� ������.
	*/

	/*
	1. check stop ptn header validation
	2. route table row check
	3. if row > 0 -> all clear
	4. get stop ptn header's start / final station codes
	5. check north / south bound (start < north -> north, start > north -> south)
	6. in case of NORTH
		start station code�� station name table�� table index get
		�ش� table index�� distance ���̺��� departure index ���� �� ã��
		start station �ڵ� 1 ���� (final stn code - 1 ����)
	*/

	auto *pTM = CTableManage::GetInstance();
	auto *pDM = CDataManage::GetInstance();
	int rowCount = GET_TABLE_MODEL(pDM, StopPtnRoutes)->rowCount();
	int hdrRow = GET_TABLE(StopPtnHeader)->currentIndex().row();
	if (hdrRow != -1/*unselected*/) // check stop pattern header validation
	{
		if (rowCount != 0)
		{
			int result = QMessageBox::warning(this,
				"Train route is not empty",
				"Do you want to delete current items and refresh all?",
				QMessageBox::Ok | QMessageBox::Cancel);

			if (result == QMessageBox::Ok)
			{
				// delete current rows
				for (int i = rowCount - 1; i >= 0; --i)
				{
					GET_TABLE_MODEL(pDM, StopPtnRoutes)->removeRows(i, 1);
				}
			}
			else
			{
				return;
			}
		}

		// get start - end point table index from stop ptn hdr
		int startStnTableIdx = 0;
		int finalStnTableIdx = 0;
		bool bOK_S;
		bool bOK_F;

		QModelIndex headerIdx = GET_TABLE(StopPtnHeader)->model()->index(hdrRow, 0);
		startStnTableIdx = headerIdx.sibling(headerIdx.row(), 1/*start*/).data().toInt(&bOK_S);
		finalStnTableIdx = headerIdx.sibling(headerIdx.row(), 2/*final*/).data().toInt(&bOK_F);

		std::vector<std::shared_ptr<CSQLData>>::iterator itSt, itEn;

		itSt = find_if(
			pTM->VECTOR_CLASS(StationInformation).begin(),
			pTM->VECTOR_CLASS(StationInformation).end(),
			findSQLData(startStnTableIdx));

		itEn = find_if(
			pTM->VECTOR_CLASS(StationInformation).begin(),
			pTM->VECTOR_CLASS(StationInformation).end(),
			findSQLData(finalStnTableIdx));

		if ((itSt != pTM->VECTOR_CLASS(StationInformation).end()) && (itEn != pTM->VECTOR_CLASS(StationInformation).end()))
		{
			auto *pSt = (StationInformation*)itSt->get();
			auto *pEn = (StationInformation*)itEn->get();

			int startCode = pSt->nStationCode; // station code
			int finalCode = pEn->nStationCode; // station code

			// compare code with station distance departure code

			std::vector<std::shared_ptr<CSQLData>>::iterator it;

			// add row
			int totalRows = std::abs(finalCode - startCode);

			if (startCode - finalCode < 0) // north bound (startCode < finalCode)
			{
				int rowNum = 0;
				while (startCode <= finalCode)
				{
					GET_TABLE(StopPtnRoutes)->model()->insertRows(rowNum, 1);
					GET_TABLE(StopPtnRoutes)->selectRow(rowNum);
					QModelIndex curIdx(GET_TABLE(StopPtnRoutes)->currentIndex());
					std::vector<std::shared_ptr<CSQLData>>::iterator itDep;

					// code, code + 1�� ��ϵ� distance index�� �ִ��� Ȯ��
					itDep = find_if(
						pTM->VECTOR_CLASS(StationDistance).begin(),
						pTM->VECTOR_CLASS(StationDistance).end(),
						findDistanceDepartureCode(startCode, startCode + 1));

					if (itDep != pTM->VECTOR_CLASS(StationDistance).end())
					{
						// distance index�� ���� ��� stop ptn routes�� ���
						int distanceIdx = itDep->get()->m_nTableIndex;
						GET_TABLE_MODEL(pDM, StopPtnRoutes)->setData(curIdx.sibling(rowNum, 3/*dist col*/), distanceIdx, Qt::EditRole);
					}
					rowNum++;
					startCode++;
				}
			}
			else if (startCode - finalCode > 0) // south bound (finalCode > startCode)
			{
				int rowNum = 0;
				while (startCode >= finalCode)
				{
					GET_TABLE(StopPtnRoutes)->model()->insertRows(rowNum, 1);
					GET_TABLE(StopPtnRoutes)->selectRow(rowNum);
					QModelIndex curIdx(GET_TABLE(StopPtnRoutes)->currentIndex());
					std::vector<std::shared_ptr<CSQLData>>::iterator itDep;

					// code, code - 1�� ��ϵ� distance index�� �ִ��� Ȯ��
					itDep = find_if(
						pTM->VECTOR_CLASS(StationDistance).begin(),
						pTM->VECTOR_CLASS(StationDistance).end(),
						findDistanceDepartureCode(startCode, startCode - 1));

					if (itDep != pTM->VECTOR_CLASS(StationDistance).end())
					{
						// distance index�� ���� ��� stop ptn routes�� ���
						int distanceIdx = itDep->get()->m_nTableIndex;
						GET_TABLE_MODEL(pDM, StopPtnRoutes)->setData(curIdx.sibling(rowNum, 3/*dist col*/), distanceIdx, Qt::EditRole);
					}
					rowNum++;
					startCode--;
				}
			}
			else
			{
				// start == final means invalid
			}
		}
	}
	else
	{
		QMessageBox::warning(this, "Invalid Stop Pattern", "Select stop pattern first!");
	}
}

void kvmrt2_media_editor::onBtnDelRoutes()
{
	auto *pTM = CTableManage::GetInstance();
	auto *pDM = CDataManage::GetInstance();
	int rowCount = GET_TABLE_MODEL(pDM, StopPtnRoutes)->rowCount();
	int hdrRow = GET_TABLE(StopPtnHeader)->currentIndex().row();
	if (hdrRow != -1/*unselected*/) // check stop pattern header validation
	{
		if (rowCount != 0)
		{
			int result = QMessageBox::warning(this, "Train route is not empty", "Do you want to delete current routes?", QMessageBox::Ok | QMessageBox::Cancel);
			if (result == QMessageBox::Ok)
			{
				// delete current rows
				for (int i = rowCount - 1; i >= 0; --i)
				{
					GET_TABLE_MODEL(pDM, StopPtnRoutes)->removeRows(i, 1);
				}
			}
			else
			{
				return;
			}
		}
	}
	else
	{
		QMessageBox::warning(this, "Invalid Stop Pattern", "Select stop pattern first!");
	}
}

void kvmrt2_media_editor::onAutoFillRouteDestination(const QModelIndex & topLeft, const QModelIndex & bottomRight)
{
	// 0��° destination �׸�� ������ �׸� �����ϰ� ������Ʈ
	auto *pTM = CTableManage::GetInstance();
	auto *pDM = CDataManage::GetInstance();
	int totalRows = GET_TABLE(StopPtnRoutes)->model()->rowCount();

	int row = topLeft.row();
	int col = topLeft.column();

	if (row != 0) return;

	if (col == 4 || col == 6) // LED or LCD destination index
	{
		if (totalRows > 1)
		{
			int targetIdx = GET_TABLE(StopPtnRoutes)->model()->data(topLeft).toInt();

			// ��ü row ���������� ù ��° destination index�� ������ ������ ����
			for (int r = 1; r < totalRows; ++r)
			{
				GET_TABLE(StopPtnRoutes)->selectRow(r);
				QModelIndex currIdx = GET_TABLE(StopPtnRoutes)->currentIndex();
				GET_TABLE_MODEL(pDM, StopPtnRoutes)->setData(currIdx.sibling(r, col), targetIdx, Qt::EditRole);
			}
		}

		GET_TABLE(StopPtnRoutes)->selectRow(0);
	}
}

void kvmrt2_media_editor::onAutoFillDisplayItem(const QModelIndex & topLeft, const QModelIndex & bottomRight)
{
	// Display List�� 0��° �������� Index ������ ��ü list�� �Ҵ�
	auto *pTM = CTableManage::GetInstance();
	auto *pDM = CDataManage::GetInstance();
	int totalRows = GET_TABLE(PIDIndexList)->model()->rowCount();

	int row = topLeft.row();
	int col = topLeft.column();

	if (row != 0) return;

	if (col == 3) // Display Item Index column
	{
		if (totalRows > 1)
		{
			int targetIdx = GET_TABLE(PIDIndexList)->model()->data(topLeft).toInt();

			// ��ü row ���������� ù ��° destination index�� ������ ������ ����
			for (int r = 1; r < totalRows; ++r)
			{
				GET_TABLE(PIDIndexList)->selectRow(r);
				QModelIndex currIdx = GET_TABLE(PIDIndexList)->currentIndex();
				GET_TABLE_MODEL(pDM, PIDIndexList)->setData(currIdx.sibling(r, col), targetIdx, Qt::EditRole);
			}
		}

		GET_TABLE(PIDIndexList)->selectRow(0);
	}
}

void kvmrt2_media_editor::onVideoIndexChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight)
{
	const int col = topLeft.column();
	const int row = topLeft.row();
	if (col == 3) // video index
	{
		const int videoFileIdx = ui.m_tblVideoPlayList->currentIndex().data(Qt::EditRole).toInt();
		const int parentIdx = ui.m_tblVideoPlayList->currentIndex().sibling(row, 1 /*parent index*/).data().toInt();

		auto *pDM = CDataManage::GetInstance();
		auto *pTM = CTableManage::GetInstance();

		std::vector<std::shared_ptr<CSQLData>>::iterator it;
		it = find_if(pTM->VECTOR_CLASS(VideoFilePool).begin(), pTM->VECTOR_CLASS(VideoFilePool).end(),
			findVideoFileNameByVideoIndex(videoFileIdx));
		if (it != pTM->VECTOR_CLASS(VideoFilePool).end())
		{
			auto *c = dynamic_cast<VideoFilePool*>(it->get());
			QString fileName = QString::fromWCharArray(c->szFileName);
			qDebug() << "video file name:" << fileName;
			GET_TABLE_MODEL(pDM, VideoPlayList)->setData(topLeft.sibling(row, 4/*file name*/), fileName, Qt::EditRole);
		}

		it = find_if(pTM->VECTOR_CLASS(VideoDeviceGroup).begin(), pTM->VECTOR_CLASS(VideoDeviceGroup).end(),
			findDeviceTypeByIndex(parentIdx));
		if (it != pTM->VECTOR_CLASS(VideoDeviceGroup).end())
		{
			auto *c = dynamic_cast<VideoDeviceGroup*>(it->get());
			int nDevType = c->nDevType;
			qDebug() << "dev type:" << nDevType;
			GET_TABLE_MODEL(pDM, VideoPlayList)->setData(topLeft.sibling(row, 6/*dev type*/), nDevType, Qt::EditRole);
		}
	}
}

void kvmrt2_media_editor::onAudioIndexChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight)
{
	const int col = topLeft.column();
	const int row = topLeft.row();

	// column ���� �� column ��ġ ����
	if (col == 9 || col == 12 || col == 15 || col == 18 || col == 4 /*bell T or F*/ || col == 5 /*bell Index*/) // audio index
	{

		const int audioFileIdx = ui.m_tblAudioPlayList->currentIndex().data(Qt::EditRole).toInt();

		auto *pDM = CDataManage::GetInstance();
		auto *pTM = CTableManage::GetInstance();

		std::vector<std::shared_ptr<CSQLData>>::iterator it;
		it = find_if(pTM->VECTOR_CLASS(AudioFilePool).begin(), pTM->VECTOR_CLASS(AudioFilePool).end(),
			findAudioFileNameByAudioIndex(audioFileIdx));
		QString fileName = "";
		int duration = 0;

		if (col != 4) // bell column�� ���õ��� ���� �����Ѵ�.
		{

			if (it != pTM->VECTOR_CLASS(AudioFilePool).end())
			{
				auto *c = dynamic_cast<AudioFilePool*>(it->get());
				fileName = QString::fromWCharArray(c->szFileName);
				duration = c->nAudioLen;
				qDebug() << "audio file name & duration:" << fileName << duration;
			}

			GET_TABLE_MODEL(pDM, AudioPlayList)->setData(topLeft.sibling(row, col + 1/*filename*/), fileName, Qt::EditRole);
			GET_TABLE_MODEL(pDM, AudioPlayList)->setData(topLeft.sibling(row, col + 2/*duration*/), duration, Qt::EditRole);

			if (col == 5) // when bell index column selected
			{
				int isBell = 0;
				if (fileName.length() > 0)
				{
					isBell = 1; // bell alaram 'Yes'
				}
				else
				{
					isBell = 0; // bell alaram 'No'
				}
				GET_TABLE_MODEL(pDM, AudioPlayList)->setData(topLeft.sibling(row, 4/*bell alaram*/), isBell, Qt::EditRole);
			}
		}

		int fileCount = 0;
		if (GET_TABLE_MODEL(pDM, AudioPlayList)->data(topLeft.sibling(row, 4), Qt::EditRole).toInt() == 1) { fileCount++; }
		if (GET_TABLE_MODEL(pDM, AudioPlayList)->data(topLeft.sibling(row, 9), Qt::EditRole).toInt() != 0) { fileCount++; }
		if (GET_TABLE_MODEL(pDM, AudioPlayList)->data(topLeft.sibling(row, 12), Qt::EditRole).toInt() != 0) { fileCount++; }
		if (GET_TABLE_MODEL(pDM, AudioPlayList)->data(topLeft.sibling(row, 15), Qt::EditRole).toInt() != 0) { fileCount++; }
		if (GET_TABLE_MODEL(pDM, AudioPlayList)->data(topLeft.sibling(row, 18), Qt::EditRole).toInt() != 0) { fileCount++; }

		GET_TABLE_MODEL(pDM, AudioPlayList)->setData(topLeft.sibling(row, 3/*count*/), fileCount, Qt::EditRole);
	}
}

void kvmrt2_media_editor::onAudioStnIndexChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight)
{
	const int col = topLeft.column();
	const int row = topLeft.row();

	if (col == 3) // BM Audio Index
	{
		const int audioFileIdx = ui.m_tblAudioStationName->currentIndex().data(Qt::EditRole).toInt();

		auto *pDM = CDataManage::GetInstance();
		auto *pTM = CTableManage::GetInstance();

		std::vector<std::shared_ptr<CSQLData>>::iterator it;
		it = find_if(pTM->VECTOR_CLASS(AudioFilePool).begin(), pTM->VECTOR_CLASS(AudioFilePool).end(),
			findAudioFileNameByAudioIndex(audioFileIdx));
		QString fileName = "";
		int duration = 0;
		if (it != pTM->VECTOR_CLASS(AudioFilePool).end())
		{
			auto *c = dynamic_cast<AudioFilePool*>(it->get());
			fileName = QString::fromWCharArray(c->szFileName);
			duration = c->nAudioLen;
			qDebug() << "audio file:" << fileName << duration;
		}

		// column ���� �� column ��ġ ����
		GET_TABLE_MODEL(pDM, AudioStationName)->setData(topLeft.sibling(row, col + 1/*filename*/), fileName, Qt::EditRole);
		GET_TABLE_MODEL(pDM, AudioStationName)->setData(topLeft.sibling(row, col + 2/*duration*/), duration, Qt::EditRole);
		GET_TABLE_MODEL(pDM, AudioStationName)->setData(topLeft.sibling(row, 6/*filename*/), audioFileIdx, Qt::EditRole);
		GET_TABLE_MODEL(pDM, AudioStationName)->setData(topLeft.sibling(row, 7/*filename*/), fileName, Qt::EditRole);
		GET_TABLE_MODEL(pDM, AudioStationName)->setData(topLeft.sibling(row, 8/*duration*/), duration, Qt::EditRole);
	}
	else if (col == 6) // audio index
	{
		const int audioFileIdx = ui.m_tblAudioStationName->currentIndex().data(Qt::EditRole).toInt();

		auto *pDM = CDataManage::GetInstance();
		auto *pTM = CTableManage::GetInstance();

		std::vector<std::shared_ptr<CSQLData>>::iterator it;
		it = find_if(pTM->VECTOR_CLASS(AudioFilePool).begin(), pTM->VECTOR_CLASS(AudioFilePool).end(),
			findAudioFileNameByAudioIndex(audioFileIdx));
		QString fileName = "";
		int duration = 0;
		if (it != pTM->VECTOR_CLASS(AudioFilePool).end())
		{
			auto *c = dynamic_cast<AudioFilePool*>(it->get());
			fileName = QString::fromWCharArray(c->szFileName);
			duration = c->nAudioLen;
			qDebug() << "audio file:" << fileName << duration;
		}

		// column ���� �� column ��ġ ����
		GET_TABLE_MODEL(pDM, AudioStationName)->setData(topLeft.sibling(row, col + 1/*filename*/), fileName, Qt::EditRole);
		GET_TABLE_MODEL(pDM, AudioStationName)->setData(topLeft.sibling(row, col + 2/*duration*/), duration, Qt::EditRole);
	}
}

void kvmrt2_media_editor::onAudioSyncDuration()
{
	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();
	auto *iniMan = IniFileManager::iniManager();

	int totalAudioListRows = GET_TABLE(AudioPlayList)->model()->rowCount();
	int totalAudioStnRows = GET_TABLE(AudioStationName)->model()->rowCount();
	int totalStationInfoRows = GET_TABLE(StationInformation)->model()->rowCount();

	// audio duration
	for (int i = 0; i < totalAudioListRows; i++)
	{
		QModelIndex index = GET_TABLE(AudioPlayList)->model()->index(i, 0);
		int msg = index.sibling(index.row(), 2/*message id*/).data().toInt();
		int *val = new int;
		switch (msg)
		{
		case MSG_ID_NEXT_BM:
			val = &iniMan->m_opDuration.nextBM;
			break;
		case MSG_ID_NEXT_EN:
			val = &iniMan->m_opDuration.nextEN;
			break;
		case MSG_ID_ARRIVING_BM:
			val = &iniMan->m_opDuration.arrivingBM;
			break;
		case MSG_ID_ARRIVING_EN:
			val = &iniMan->m_opDuration.arrivingEN;
			break;
		case MSG_ID_ARRIVAL_BM:
			val = &iniMan->m_opDuration.arrivalBM;
			break;
		case MSG_ID_ARRIVAL_EN:
			val = &iniMan->m_opDuration.arrivalEN;
			break;
		default:
			break;
		}

		*val = index.sibling(index.row(), 7).data().toInt() + index.sibling(index.row(), 11).data().toInt()
			+ index.sibling(index.row(), 14).data().toInt() + index.sibling(index.row(), 17).data().toInt() +
			index.sibling(index.row(), 20).data().toInt();
	} // for (int i = 0; i < totalAudioListRows; i++)

	// next, approching, arrival + stn name
	for (int i = 0; i < totalStationInfoRows; i++)
	{
		QModelIndex stnIndex = GET_TABLE(StationInformation)->model()->index(i, 0);
		for (int j = 0; j < totalAudioStnRows; j++)
		{
			QModelIndex audioNameIndex = GET_TABLE(AudioStationName)->model()->index(j, 0);
			int audioCode = audioNameIndex.sibling(audioNameIndex.row(), 2).data().toInt();
			int stnCode = stnIndex.sibling(stnIndex.row(), 1).data().toInt();

			if (stnCode == audioCode)
			{
				qDebug() << stnCode << "founded.";

				const int stnAudioBM = audioNameIndex.sibling(audioNameIndex.row(), 5).data().toInt() + added_stn_name_duration;
				const int stnAudioEN = audioNameIndex.sibling(audioNameIndex.row(), 8).data().toInt() + added_stn_name_duration;
				int nextBM = iniMan->m_opDuration.nextBM + stnAudioBM;
				int nextEN = iniMan->m_opDuration.nextEN + stnAudioEN;
				int apprBM = iniMan->m_opDuration.arrivingBM + stnAudioBM;
				int apprEN = iniMan->m_opDuration.arrivingEN + stnAudioEN;
				int arrvBM = iniMan->m_opDuration.arrivalBM + stnAudioBM;
				int arrvEN = iniMan->m_opDuration.arrivalEN + stnAudioEN;

				GET_TABLE_MODEL(pDM, StationInformation)->setData(stnIndex.sibling(stnIndex.row(), 6 /*nextBM*/), nextBM, Qt::EditRole);
				GET_TABLE_MODEL(pDM, StationInformation)->setData(stnIndex.sibling(stnIndex.row(), 7 /*nextEN*/), nextEN, Qt::EditRole);
				GET_TABLE_MODEL(pDM, StationInformation)->setData(stnIndex.sibling(stnIndex.row(), 8 /*apprBM*/), apprBM, Qt::EditRole);
				GET_TABLE_MODEL(pDM, StationInformation)->setData(stnIndex.sibling(stnIndex.row(), 9 /*apprEN*/), apprEN, Qt::EditRole);
				GET_TABLE_MODEL(pDM, StationInformation)->setData(stnIndex.sibling(stnIndex.row(), 10/*arrvBM*/), arrvBM, Qt::EditRole);
				GET_TABLE_MODEL(pDM, StationInformation)->setData(stnIndex.sibling(stnIndex.row(), 11/*arrvEN*/), arrvEN, Qt::EditRole);

				break;
			}
		} // for (int j = 0; j < totalAudioStnRows; j++)
	} // for (int i = 0; i < totalStationInfoRows; i++)

	// get exchange info
	for (int i = 0; i < totalStationInfoRows; i++)
	{
		QModelIndex stnIndex = GET_TABLE(StationInformation)->model()->index(i, 0);
		bool foundBM = false;
		bool foundEN = false;

		for (int j = 0; j < totalAudioListRows; j++)
		{

			QModelIndex playIndex = GET_TABLE(AudioPlayList)->model()->index(j, 0);
			const int msg = playIndex.sibling(playIndex.row(), 2/*message id*/).data().toInt();
			const int stnCode = stnIndex.sibling(stnIndex.row(), 1).data().toInt();

			if (msg == stnCode + MSG_ID_EXCHANGE_BM_OFFSET)
			{
				int exchangeBM = playIndex.sibling(playIndex.row(), 11/*audio file 1 col*/).data().toInt();
				GET_TABLE_MODEL(pDM, StationInformation)->setData(stnIndex.sibling(stnIndex.row(), 12 /*exBM*/), exchangeBM, Qt::EditRole);
				foundBM = true;
			}

			if (msg == stnCode + MSG_ID_EXCHANGE_EN_OFFSET)
			{
				int exchangeEN = playIndex.sibling(playIndex.row(), 11/*audio file 1 col*/).data().toInt();
				GET_TABLE_MODEL(pDM, StationInformation)->setData(stnIndex.sibling(stnIndex.row(), 13 /*exEN*/), exchangeEN, Qt::EditRole);
				foundEN = true;
			}

			if (foundBM && foundEN)
			{
				qDebug() << stnCode << "exchange audio founded.";
				break;
			}
		} // for (int j = 0; j < totalAudioListRows; j++)
	} // for (int i = 0; i < totalStationInfoRows; i++)

	// make ini file
	iniMan->clearStnIniInfo();
	for (int i = 0; i < totalStationInfoRows; i++)
	{
		QModelIndex index = GET_TABLE(StationInformation)->model()->index(i, 0);
		StationIniInfo stIni = { 0 };

		stIni.code = index.sibling(index.row(), 1).data().toInt();
		stIni.nameF = index.sibling(index.row(), 2).data().toString();
		stIni.nameS = index.sibling(index.row(), 3).data().toString();
		stIni.hasExchange = index.sibling(index.row(), 14).data().toInt();
		stIni.isProvisional = index.sibling(index.row(), 15).data().toInt();
		stIni.apprDistance = index.sibling(index.row(), 16).data().toInt();

		stIni.paNextBM = (index.sibling(index.row(), 6).data().toInt()  != 0) ? index.sibling(index.row(), 6).data().toInt()  /*/ 1000*/ + added_duration : 0;
		stIni.paNextEN = (index.sibling(index.row(), 7).data().toInt()  != 0) ? index.sibling(index.row(), 7).data().toInt()  /*/ 1000*/ + added_duration : 0;
		stIni.paApprBM = (index.sibling(index.row(), 8).data().toInt()  != 0) ? index.sibling(index.row(), 8).data().toInt()  /*/ 1000*/ + added_duration : 0;
		stIni.paApprEN = (index.sibling(index.row(), 9).data().toInt()  != 0) ? index.sibling(index.row(), 9).data().toInt()  /*/ 1000*/ + added_duration : 0;
		stIni.paArrvBM = (index.sibling(index.row(), 10).data().toInt() != 0) ? index.sibling(index.row(), 10).data().toInt() /*/ 1000*/ + added_duration : 0;
		stIni.paArrvEN = (index.sibling(index.row(), 11).data().toInt() != 0) ? index.sibling(index.row(), 11).data().toInt() /*/ 1000*/ + added_duration : 0;
		
		if (stIni.hasExchange == 1) // 1 = true
		{
			stIni.paExchangeBM = index.sibling(index.row(), 12).data().toInt() /*/ 1000*/ + added_duration;
			stIni.paExchangeEN = index.sibling(index.row(), 13).data().toInt() /*/ 1000*/ + added_duration;
		}
		else
		{
			stIni.paExchangeBM = 0;
			stIni.paExchangeEN = 0;
		}

		iniMan->addStnIniInfo(stIni);
	} // for (int i = 0; i < totalStationInfoRows; i++)
	iniMan->createStationInfoIni();

	// get other PA (special, emg, door...)
	iniMan->clearAudioListInfo();
	for (int i = 0; i < totalAudioListRows; i++)
	{
		QModelIndex index = GET_TABLE(AudioPlayList)->model()->index(i, 0);
		int msgID = index.sibling(index.row(), 2/*message id*/).data().toInt();
		QString desc = index.sibling(index.row(), 21/*desc*/).data().toString().simplified();
		qDebug() << msgID << desc;
		int duration =
			(
				index.sibling(index.row(), 7).data().toInt() // bell duration (ms)
				+ index.sibling(index.row(), 11).data().toInt() // audio file 1 duration (ms)
				+ index.sibling(index.row(), 14).data().toInt() // audio file 2 duration (ms)
				+ index.sibling(index.row(), 17).data().toInt() // audio file 3 duration (ms)
				+ index.sibling(index.row(), 20).data().toInt() // audio file 4 duration (ms)
				) /*/ 1000*/ + added_duration;


		audioListInfo st = { 0 };
		st.id = msgID;
		st.desc = desc;
		st.duration = duration;

		iniMan->addAudioListInfo(st);
	} // for (int i = 0; i < totalAudioListRows; i++)
	iniMan->createPaInfoIni();
}

void kvmrt2_media_editor::initAccountType(AccountType type)
{
	switch (type)
	{
	case ACC_ADMIN:
		qInfo() << Q_FUNC_INFO << "Administrator";
		break;
	case ACC_NORMAL:
		qInfo() << Q_FUNC_INFO << "Normal";
		ui.actionUpdate->setEnabled(false);
		break;
	case ACC_GUEST:
	case ACC_UNDEFINED:
	default:
		for (auto a : this->findChildren<QAction*>())
		{
			a->setEnabled(false);
		}
		for (auto a : this->findChildren<QTableView*>())
		{
			a->setEnabled(false);
		}
		break;
	}
}


void kvmrt2_media_editor::initNewFeature()
{
	// station name table
	connect(ui.btnAddStation, SIGNAL(clicked()), this, SLOT(onAddStnBtnClicked()));
	connect(ui.btnDelStation, SIGNAL(clicked()), this, SLOT(onDelStnBtnClicked()));
	connect(ui.btnDelAllStation, SIGNAL(clicked()), this, SLOT(onDelAllStnBtnClicked()));
	// station distance (pair) table
	connect(ui.btnAddPair, SIGNAL(clicked()), this, SLOT(onAddPairBtnClicked()));
	connect(ui.btnDelPair, SIGNAL(clicked()), this, SLOT(onDelPairBtnClicked()));
	connect(ui.btnDelAllPair, SIGNAL(clicked()), this, SLOT(onDelAllPairBtnClicked()));
	// stop pattern table
	connect(ui.btnAddStopPattern, SIGNAL(clicked()), this, SLOT(onAddPatternBtnClicked()));
	connect(ui.btnDelStopPattern, SIGNAL(clicked()), this, SLOT(onDelPatternBtnClicked()));
	connect(ui.btnDelAllStopPattern, SIGNAL(clicked()), this, SLOT(onDelAllPatternBtnClicked()));
	// train route
	connect(ui.btnAddRoute, SIGNAL(clicked()), this, SLOT(onAddRouteBtnClicked()));
	connect(ui.btnDelRoute, SIGNAL(clicked()), this, SLOT(onDelRouteBtnClicked()));
	// display list / display list item
	connect(ui.btnAddDisplayList, SIGNAL(clicked()), this, SLOT(onAddDisplayListBtnClicked()));
	connect(ui.btnDelDisplayList, SIGNAL(clicked()), this, SLOT(onDelDisplayListBtnClicked()));
	connect(ui.btnDelAllDisplayList, SIGNAL(clicked()), this, SLOT(onDelAllDisplayListBtnClicked()));
	connect(ui.btnAddDisplayItem, SIGNAL(clicked()), this, SLOT(onAddDisplayItemBtnClicked()));
	connect(ui.btnDelDisplayItem, SIGNAL(clicked()), this, SLOT(onDelDisplayItemBtnClicked()));
	connect(ui.btnDelAllDisplayItem, SIGNAL(clicked()), this, SLOT(onDelAllDisplayItemBtnClicked()));
	// audio stn name / aduio list
	connect(ui.btnAddVideoGroup, SIGNAL(clicked()), this, SLOT(onAddVideoGroupBtnClicked()));
	connect(ui.btnDelVideoGroup, SIGNAL(clicked()), this, SLOT(onDelVideoGroupBtnClicked()));
	connect(ui.btnDelAllVideoGroup, SIGNAL(clicked()), this, SLOT(onDelAllVideoGroupBtnClicked()));
	connect(ui.btnAddAudioList, SIGNAL(clicked()), this, SLOT(onAddAudioListBtnClicked()));
	connect(ui.btnDelAudioList, SIGNAL(clicked()), this, SLOT(onDelAudioListBtnClicked()));
	connect(ui.btnDelAllAudioList, SIGNAL(clicked()), this, SLOT(onDelAllAudioListBtnClicked()));
	// video stn name / video list
	connect(ui.btnAddStnAudio, SIGNAL(clicked()), this, SLOT(onAddStnAudioBtnClicked()));
	connect(ui.btnDelStnAudio, SIGNAL(clicked()), this, SLOT(onDelStnAudioBtnClicked()));
	connect(ui.btnDelAllStnAudio, SIGNAL(clicked()), this, SLOT(onDelAllStnAudioBtnClicked()));
	connect(ui.btnAddVideoList, SIGNAL(clicked()), this, SLOT(onAddVideoListBtnClicked()));
	connect(ui.btnDelVideoList, SIGNAL(clicked()), this, SLOT(onDelVideoListBtnClicked()));
	connect(ui.btnDelAllVideoList, SIGNAL(clicked()), this, SLOT(onDelAllVideoListBtnClicked()));
	// editor tag table
	connect(ui.btnAddDataTag, SIGNAL(clicked()), this, SLOT(onAddDataTagBtnClicked()));
	connect(ui.btnDelDataTag, SIGNAL(clicked()), this, SLOT(onDelDataTagBtnClicked()));
	connect(ui.btnDelAllDataTag, SIGNAL(clicked()), this, SLOT(onDelAllDataTagBtnClicked()));
}

void kvmrt2_media_editor::onAddStnBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	addRowToTable(false, ui.m_tblStationInformation, pDM->m_pModStationInformation.get());
}

void kvmrt2_media_editor::onDelStnBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	deleteRowFromTable(ui.m_tblStationInformation, pDM->m_pModStationInformation.get());
}

void kvmrt2_media_editor::onDelAllStnBtnClicked()
{
	auto *pDM = CDataManage::GetInstance();
	const int rowCount = pDM->m_pModStationInformation.get()->rowCount();
	int ret = QMessageBox::question(this,
		"Delete All",
		QString("Do you want to delete all station information? (total %1)")
		.arg(rowCount));

	if (ret == QMessageBox::Yes)
	{
		for (int r = 0; r < rowCount; ++r)
		{
			ui.m_tblStationInformation->model()->removeRows(0, 1);
		}
	}
	else {}
}

void kvmrt2_media_editor::onAddPairBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	addRowToTable(false, ui.m_tblStationDistance, pDM->m_pModStationDistance.get());
}

void kvmrt2_media_editor::onDelPairBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	deleteRowFromTable(ui.m_tblStationDistance, pDM->m_pModStationDistance.get());
}

void kvmrt2_media_editor::onDelAllPairBtnClicked()
{
	auto *pDM = CDataManage::GetInstance();
	const int rowCount = pDM->m_pModStationDistance.get()->rowCount();
	int ret = QMessageBox::question(this,
		"Delete All",
		QString("Do you want to delete all station pairs? (total %1)")
		.arg(rowCount));

	if (ret == QMessageBox::Yes)
	{
		for (int r = 0; r < rowCount; ++r)
		{
			ui.m_tblStationDistance->model()->removeRows(0, 1);
		}
	}
	else {}
}

void kvmrt2_media_editor::onAddPatternBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	addRowToTable(false, ui.m_tblStopPtnHeader, pDM->m_pModStopPtnHeader.get());
}

void kvmrt2_media_editor::onDelPatternBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	deleteRowFromTable(ui.m_tblStopPtnHeader, pDM->m_pModStopPtnHeader.get());
}

void kvmrt2_media_editor::onDelAllPatternBtnClicked()
{
	auto *pDM = CDataManage::GetInstance();
	const int rowCount = pDM->m_pModStopPtnHeader.get()->rowCount();
	int ret = QMessageBox::question(this,
		"Delete All",
		QString("Do you want to delete all stop patterns? (total %1)")
		.arg(rowCount));

	if (ret == QMessageBox::Yes)
	{
		for (int r = 0; r < rowCount; ++r)
		{
			ui.m_tblStopPtnHeader->model()->removeRows(0, 1);
		}
	}
	else {}
}

void kvmrt2_media_editor::onAddRouteBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pTM = CTableManage::GetInstance();
	auto *pDM = CDataManage::GetInstance();
	int hdrRow = GET_TABLE(StopPtnHeader)->currentIndex().row();
	if (hdrRow != -1/*unselected*/) // check stop pattern header validation
	{
		addRowToTable(false, ui.m_tblStopPtnRoutes, pDM->m_pModStopPtnRoutes.get());
	}
	else
	{
		QMessageBox::warning(this, "Invalid Stop Pattern", "Select stop pattern first!");
	}
}

void kvmrt2_media_editor::onDelRouteBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	deleteRowFromTable(ui.m_tblStopPtnRoutes, pDM->m_pModStopPtnRoutes.get());
}

void kvmrt2_media_editor::onAddDisplayListBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	addRowToTable(false, ui.m_tblPIDContents, pDM->m_pModPIDContents.get());
}

void kvmrt2_media_editor::onDelDisplayListBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	deleteRowFromTable(ui.m_tblPIDContents, pDM->m_pModPIDContents.get());
}

void kvmrt2_media_editor::onDelAllDisplayListBtnClicked()
{
	auto *pDM = CDataManage::GetInstance();
	const int rowCount = pDM->m_pModPIDContents.get()->rowCount();
	int ret = QMessageBox::question(this,
		"Delete All",
		QString("Do you want to delete all display list? (total %1)")
		.arg(rowCount));

	if (ret == QMessageBox::Yes)
	{
		for (int r = 0; r < rowCount; ++r)
		{
			ui.m_tblPIDContents->model()->removeRows(0, 1);
		}
	}
	else {}
}

void kvmrt2_media_editor::onAddDisplayItemBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();
	int hdrRow = GET_TABLE(PIDContents)->currentIndex().row();
	if (hdrRow != -1/*unselected*/)
	{
		addRowToTable(false, ui.m_tblPIDIndexList, pDM->m_pModPIDIndexList.get());
	}
	else
	{
		QMessageBox::warning(this, "Invalid Display List", "Select display list first!");
	}
}

void kvmrt2_media_editor::onDelDisplayItemBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	deleteRowFromTable(ui.m_tblPIDIndexList, pDM->m_pModPIDIndexList.get());
}

void kvmrt2_media_editor::onDelAllDisplayItemBtnClicked()
{
	auto *pDM = CDataManage::GetInstance();
	const int rowCount = pDM->m_pModPIDIndexList.get()->rowCount();
	int ret = QMessageBox::question(this,
		"Delete All",
		QString("Do you want to delete all display items? (total %1)")
		.arg(rowCount));

	if (ret == QMessageBox::Yes)
	{
		for (int r = 0; r < rowCount; ++r)
		{
			ui.m_tblPIDIndexList->model()->removeRows(0, 1);
		}
	}
	else {}
}

void kvmrt2_media_editor::onAddStnAudioBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	addRowToTable(false, ui.m_tblAudioStationName, pDM->m_pModAudioStationName.get());
}

void kvmrt2_media_editor::onDelStnAudioBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	deleteRowFromTable(ui.m_tblAudioStationName, pDM->m_pModAudioStationName.get());
}

void kvmrt2_media_editor::onDelAllStnAudioBtnClicked()
{
	auto *pDM = CDataManage::GetInstance();
	const int rowCount = pDM->m_pModAudioStationName.get()->rowCount();
	int ret = QMessageBox::question(this,
		"Delete All",
		QString("Do you want to delete all station audio list? (total %1)")
		.arg(rowCount));

	if (ret == QMessageBox::Yes)
	{
		for (int r = 0; r < rowCount; ++r)
		{
			ui.m_tblAudioStationName->model()->removeRows(0, 1);
		}
	}
	else {}
}

void kvmrt2_media_editor::onAddAudioListBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	addRowToTable(false, ui.m_tblVideoPlayList, pDM->m_pModVideoPlayList.get());
}

void kvmrt2_media_editor::onDelAudioListBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	deleteRowFromTable(ui.m_tblVideoPlayList, pDM->m_pModVideoPlayList.get());
}

void kvmrt2_media_editor::onDelAllAudioListBtnClicked()
{
	auto *pDM = CDataManage::GetInstance();
	const int rowCount = pDM->m_pModVideoPlayList.get()->rowCount();
	int ret = QMessageBox::question(this,
		"Delete All",
		QString("Do you want to delete all audio list? (total %1)")
		.arg(rowCount));

	if (ret == QMessageBox::Yes)
	{
		for (int r = 0; r < rowCount; ++r)
		{
			ui.m_tblVideoPlayList->model()->removeRows(0, 1);
		}
	}
	else {}
}

void kvmrt2_media_editor::onAddVideoGroupBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	addRowToTable(false, ui.m_tblVideoDeviceGroup, pDM->m_pModVideoDeviceGroup.get());
}

void kvmrt2_media_editor::onDelVideoGroupBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	deleteRowFromTable(ui.m_tblVideoDeviceGroup, pDM->m_pModVideoDeviceGroup.get());
}

void kvmrt2_media_editor::onDelAllVideoGroupBtnClicked()
{
	auto *pDM = CDataManage::GetInstance();
	const int rowCount = pDM->m_pModVideoDeviceGroup.get()->rowCount();
	int ret = QMessageBox::question(this,
		"Delete All",
		QString("Do you want to delete all video group list? (total %1)")
		.arg(rowCount));

	if (ret == QMessageBox::Yes)
	{
		for (int r = 0; r < rowCount; ++r)
		{
			ui.m_tblVideoDeviceGroup->model()->removeRows(0, 1);
		}
	}
	else {}
}

void kvmrt2_media_editor::onAddVideoListBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();
	int hdrRow = GET_TABLE(VideoDeviceGroup)->currentIndex().row();
	if (hdrRow != -1/*unselected*/)
	{
		addRowToTable(false, ui.m_tblVideoPlayList, pDM->m_pModVideoPlayList.get());
	}
	else
	{
		QMessageBox::warning(this, "Invalid Video List", "Select video list first!");
	}
}

void kvmrt2_media_editor::onDelVideoListBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	deleteRowFromTable(ui.m_tblVideoPlayList, pDM->m_pModVideoPlayList.get());
}

void kvmrt2_media_editor::onDelAllVideoListBtnClicked()
{
	auto *pDM = CDataManage::GetInstance();
	const int rowCount = pDM->m_pModVideoPlayList.get()->rowCount();
	int ret = QMessageBox::question(this,
		"Delete All",
		QString("Do you want to delete all video list? (total %1)")
		.arg(rowCount));

	if (ret == QMessageBox::Yes)
	{
		for (int r = 0; r < rowCount; ++r)
		{
			ui.m_tblVideoPlayList->model()->removeRows(0, 1);
		}
	}
	else {}
}

void kvmrt2_media_editor::onAddDataTagBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	addRowToTable(false, ui.m_tblEditorTagTable, pDM->m_pModEditorTagTable.get());
}

void kvmrt2_media_editor::onDelDataTagBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	deleteRowFromTable(ui.m_tblEditorTagTable, pDM->m_pModEditorTagTable.get());
}

void kvmrt2_media_editor::onDelAllDataTagBtnClicked()
{
	auto *pDM = CDataManage::GetInstance();
	const int rowCount = pDM->m_pModEditorTagTable.get()->rowCount();
	int ret = QMessageBox::question(this,
		"Delete All",
		QString("Do you want to delete all editor tags? (total %1)")
		.arg(rowCount));

	if (ret == QMessageBox::Yes)
	{
		for (int r = 0; r < rowCount; ++r)
		{
			ui.m_tblEditorTagTable->model()->removeRows(0, 1);
		}
	}
	else {}
}

void kvmrt2_media_editor::aboutME()
{
	QString text = QString(
		"<b>Organization</b>: %1<br>"
		"<b>Application</b>: %2<br>"
		"<b>Version</b>: %3<br>"
		"<b>Contact</b>: <a href='mailto: kcjeong@wjis.co.kr'>kcjeong@wjis.co.kr</a><br>")
		.arg(QApplication::organizationName())
		.arg(QApplication::applicationName())
		.arg(QApplication::applicationVersion());

	QMessageBox aboutMyApp(this);
	aboutMyApp.setIcon(QMessageBox::Information);
	aboutMyApp.setWindowTitle(QString("About %1").arg(QApplication::applicationName()));
	aboutMyApp.setTextFormat(Qt::RichText);
	aboutMyApp.setText(text);
	aboutMyApp.exec();
}

void kvmrt2_media_editor::licenseInfo()
{
	// icon license info goes here...
	// space icon link
	// http://www.iconarchive.com/show/free-space-icons-by-goodstuff-no-nonsense.2.html

	QString text = QString(
		"<b>Artist</b>: <a href='http://www.iconarchive.com/artist/goodstuff-no-nonsense.html'>Good Stuff No Nonsense</a> (Available for custom work)<br>"
		"<b>Iconset Homepage</b> : <a href='https://goodstuffnononsense.com/hand-drawn-icons/space-icons'>goodstuffnononsense</a><br>"
		"<b>License</b>: <a href='https://creativecommons.org/licenses/by/4.0/'>CC Attribution 4.0</a><br>"
		"<b>Commercial usage</b> : Allowed");

	QMessageBox licenseMsg(this);
	licenseMsg.setIcon(QMessageBox::Information);
	licenseMsg.setWindowTitle("Icon Licesnse Information");
	licenseMsg.setTextFormat(Qt::RichText);
	licenseMsg.setText(text);
	licenseMsg.exec();
}

void kvmrt2_media_editor::updateStopPtnRoutes(const QModelIndex & current, const QModelIndex & previous)
{
	QModelIndex index = GET_TABLE(StopPtnHeader)->currentIndex();

	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();
	if (index.isValid())
	{
		int nRow = index.row();
		if (nRow < pTM->VECTOR_CLASS(StopPtnHeader).size())
		{
			pDM->GET_MODEL_CLASS(StopPtnRoutes)->setVectors(
				&pTM->VECTOR_CLASS(StopPtnHeader)[nRow]->m_vChildItem[0].vSQLData,
				&pTM->VECTOR_CLASS(StopPtnHeader)[nRow]->m_vChildItem[0].vSQLDataDelItems,
				pTM->VECTOR_CLASS(StopPtnHeader)[nRow].get()->GetIndex());
			pDM->GET_MODEL_CLASS(EventLists)->setVectors(nullptr, nullptr);
		}
	}
	else
	{
		pDM->GET_MODEL_CLASS(StopPtnRoutes)->setVectors(nullptr, nullptr);
		pDM->GET_MODEL_CLASS(EventLists)->setVectors(nullptr, nullptr);
	}
}

void kvmrt2_media_editor::updateEventLists(const QModelIndex & current, const QModelIndex & previous)
{
	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();
	QModelIndex index = GET_TABLE(StopPtnHeader)->currentIndex();
	QModelIndex indexSub = GET_TABLE(StopPtnRoutes)->currentIndex();
	if (index.isValid() && indexSub.isValid())
	{
		int nRow = index.row();
		int nRow2 = indexSub.row();
		if ((nRow < pTM->VECTOR_CLASS(StopPtnHeader).size()) && (nRow2 < pTM->VECTOR_CLASS(StopPtnHeader)[nRow]->m_vChildItem[0].vSQLData.size()))
			pDM->GET_MODEL_CLASS(EventLists)->setVectors(
				&pTM->VECTOR_CLASS(StopPtnHeader)[nRow]->m_vChildItem[0].vSQLData[nRow2]->m_vChildItem[0].vSQLData,
				&pTM->VECTOR_CLASS(StopPtnHeader)[nRow]->m_vChildItem[0].vSQLData[nRow2]->m_vChildItem[0].vSQLDataDelItems);
		else
		{
			pDM->GET_MODEL_CLASS(EventLists)->setVectors(nullptr, nullptr);
		}
	}
}

void kvmrt2_media_editor::updatePIDIndexList(const QModelIndex & current, const QModelIndex & previous)
{
	QModelIndex index = GET_TABLE(PIDContents)->currentIndex();
	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();

	if (index.isValid())
	{
		int nRow = index.row();
		if (nRow < pTM->VECTOR_CLASS(PIDContents).size())
		{
			pDM->GET_MODEL_CLASS(PIDIndexList)->setVectors(&pTM->VECTOR_CLASS(PIDContents)[nRow]->m_vChildItem[0].vSQLData, &pTM->VECTOR_CLASS(PIDContents)[nRow]->m_vChildItem[0].vSQLDataDelItems, pTM->VECTOR_CLASS(PIDContents)[nRow].get()->GetIndex());
		}
	}
	else
	{
		pDM->GET_MODEL_CLASS(PIDIndexList)->setVectors(nullptr, nullptr);
	}
}

void kvmrt2_media_editor::updateVideoPlayList(const QModelIndex & current, const QModelIndex & previous)
{
	QModelIndex index = GET_TABLE(VideoDeviceGroup)->currentIndex();
	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();

	if (index.isValid())
	{
		int nRow = index.row();
		if (nRow < pTM->VECTOR_CLASS(VideoDeviceGroup).size())
		{
			pDM->GET_MODEL_CLASS(VideoPlayList)->setVectors(
				&pTM->VECTOR_CLASS(VideoDeviceGroup)[nRow]->m_vChildItem[0].vSQLData,
				&pTM->VECTOR_CLASS(VideoDeviceGroup)[nRow]->m_vChildItem[0].vSQLDataDelItems,
				pTM->VECTOR_CLASS(VideoDeviceGroup)[nRow].get()->GetIndex());
		}
	}
	else
	{
		pDM->GET_MODEL_CLASS(VideoPlayList)->setVectors(nullptr, nullptr);
	}
}

void kvmrt2_media_editor::updateStationDistance(const QModelIndex & topLeft, const QModelIndex & bottomRight)
{
	// �ڵ��Է� ���� �߰��ϸ� update ����� �� ��

	bool bOKDep;
	bool bOKArr;
	bool bOKDistance;
	QString strDesc;
	auto *pTM = CTableManage::GetInstance();
	auto *pDM = CDataManage::GetInstance();

	if (topLeft.isValid() && bottomRight.isValid())
	{
		int nRow = topLeft.row();
		int nColumn = topLeft.column();
		int nDepStn = 0;
		int nArrStn = 0;
		int nDistance = 0;;
		int depCode = 0;
		int arrCode = 0;

		int depOrder = 0;
		int arrOrder = 0;

		switch (nColumn)
		{
		case 1: // departure
		{
			nDepStn = topLeft.data().toInt(&bOKDep);
			//nArrStn = topLeft.sibling(topLeft.row(), 2/*arrival col*/).data().toInt(&bOKArr);
			//nDistance = topLeft.sibling(topLeft.row(), 3/*distance col*/).data().toInt(&bOKDistance);

			std::vector<std::shared_ptr<CSQLData>>::iterator it_dep;
			it_dep = find_if(pTM->VECTOR_CLASS(StationInformation).begin(), pTM->VECTOR_CLASS(StationInformation).end(), findSQLData(nDepStn));

			if (it_dep != pTM->VECTOR_CLASS(StationInformation).end())
			{
				// parent class to child class
				auto *c = dynamic_cast<StationInformation*>(it_dep->get());
				depCode = c->nStationCode;
				depOrder = c->nOrder;
				GET_TABLE_MODEL(pDM, StationDistance)->setData(topLeft.sibling(topLeft.row(), 6/*dep code*/), depCode, Qt::EditRole);
			}

			if (ui.rbInOrder->isChecked()) // in order radio is checked
			{
				// find and check departure + 1 order is valid
				arrOrder = depOrder + 1;

				std::vector<std::shared_ptr<CSQLData>>::iterator it_arrOrder;

				// find using station order
				it_arrOrder = find_if(pTM->VECTOR_CLASS(StationInformation).begin(), pTM->VECTOR_CLASS(StationInformation).end(), findStationNameOrder(arrOrder));

				if (it_arrOrder != pTM->VECTOR_CLASS(StationInformation).end())
				{
					// get target's table index
					int arrTableIndex = it_arrOrder->get()->m_nTableIndex;
					StationInformation *c = dynamic_cast<StationInformation*>(it_arrOrder->get());
					int findCode = c->nStationCode;
					GET_TABLE_MODEL(pDM, StationDistance)->setData(topLeft.sibling(topLeft.row(), 2/*arrival col*/), arrTableIndex, Qt::EditRole);
					GET_TABLE_MODEL(pDM, StationDistance)->setData(topLeft.sibling(topLeft.row(), 7/*arr code*/), findCode, Qt::EditRole);
				}
			}
			else if (ui.rbInReverseOrder->isChecked()) // in reverse order is checked
			{
				// find and check departure - 1 code is valid
				arrOrder = depOrder - 1;

				std::vector<std::shared_ptr<CSQLData>>::iterator it_arrOrder;

				// find using station code
				it_arrOrder = find_if(pTM->VECTOR_CLASS(StationInformation).begin(), pTM->VECTOR_CLASS(StationInformation).end(), findStationNameOrder(arrOrder));

				if (it_arrOrder != pTM->VECTOR_CLASS(StationInformation).end())
				{
					// get target's table index
					int arrTableIndex = it_arrOrder->get()->m_nTableIndex;
					StationInformation *c = dynamic_cast<StationInformation*>(it_arrOrder->get());
					int findCode = c->nStationCode;

					GET_TABLE_MODEL(pDM, StationDistance)->setData(topLeft.sibling(topLeft.row(), 2/*arrival col*/), arrTableIndex, Qt::EditRole);
					GET_TABLE_MODEL(pDM, StationDistance)->setData(topLeft.sibling(topLeft.row(), 7/*arr code*/), findCode, Qt::EditRole);
				}
			}
			else
			{
			}
		}
		break;
		case 2: // arrival
		{
			nArrStn = topLeft.data().toInt(&bOKArr);

			std::vector<std::shared_ptr<CSQLData>>::iterator it_arr;
			it_arr = find_if(pTM->VECTOR_CLASS(StationInformation).begin(), pTM->VECTOR_CLASS(StationInformation).end(), findSQLData(nArrStn));

			if (it_arr != pTM->VECTOR_CLASS(StationInformation).end())
			{
				// parent class to child class
				auto *c = dynamic_cast<StationInformation*>(it_arr->get());
				arrCode = c->nStationCode;
				GET_TABLE_MODEL(pDM, StationDistance)->setData(topLeft.sibling(topLeft.row(), 7/*arr code*/), arrCode, Qt::EditRole);
			}
		}
		break;
		case 3: // distnace
			nDistance = topLeft.data().toInt(&bOKDistance);
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		default:
			break;
		}
	}
}

void kvmrt2_media_editor::updateStopPtnHeader(const QModelIndex & topLeft, const QModelIndex & bottomRight)
{
	bool bOKDep;
	bool bOKArr;
	wchar_t szSt[32];
	wchar_t szEn[32];
	QString strDesc;
	std::vector<std::wstring> vPath;
	std::vector<std::wstring>::iterator itPath;
	std::vector<std::wstring>::iterator itPrevPath;
	std::vector<std::shared_ptr<CSQLData>>::iterator itEdge;
	int nTotalDistance = 0;
	if (topLeft.isValid() && bottomRight.isValid())
	{
		int nRow = topLeft.row();
		int nColumn = topLeft.column();
		bool bOk, bParentOk;
		int nArrStn = 0, nDepStn = 0;
		switch (nColumn)
		{
		case 1:
			nArrStn = topLeft.data().toInt(&bOKDep);
			nDepStn = topLeft.sibling(topLeft.row(), 2).data().toInt(&bOKArr);
			break;
		case 2:
			nArrStn = topLeft.sibling(topLeft.row(), 1).data().toInt(&bOKDep);
			nDepStn = topLeft.data().toInt(&bOKArr);
			break;
		default:
			break;
		}

		if (nArrStn&&nDepStn)
		{
			auto *pTM = CTableManage::GetInstance();
			auto *pDM = CDataManage::GetInstance();
			std::vector<std::shared_ptr<CSQLData>>::iterator itSt, itEn;
			itSt = find_if(pTM->VECTOR_CLASS(StationInformation).begin(), pTM->VECTOR_CLASS(StationInformation).end(), findSQLData(nArrStn));
			itEn = find_if(pTM->VECTOR_CLASS(StationInformation).begin(), pTM->VECTOR_CLASS(StationInformation).end(), findSQLData(nDepStn));
			if ((itSt != pTM->VECTOR_CLASS(StationInformation).end()) && (itEn != pTM->VECTOR_CLASS(StationInformation).end()))
			{
				StationInformation *pSt = (StationInformation*)itSt->get();
				StationInformation *pEn = (StationInformation*)itEn->get();
				strDesc = QString("%1 -> %2")
					.arg(QString::fromStdWString(pSt->szStationName1))
					.arg(QString::fromStdWString(pEn->szStationName1));
				GET_TABLE_MODEL(pDM, StopPtnHeader)->setData(topLeft.sibling(topLeft.row(), 3), strDesc, Qt::EditRole);
			}
		}
	}
}


#define PARENT_EDITOR_CLASS kvmrt2_media_editor

IMPLEMENT_INIT_FUNCTION_FOR_CLASS(PARENT_EDITOR_CLASS, StationInformation)
{
	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();
	auto *pMM = CMapManage::GetInstance();

	SET_MODEL_FOR_TABLE_VIEW(StationInformation, pDM);
	INSTALL_EVENT_FILTER(StationInformation);

	QHeaderView *header = GET_TABLE(StationInformation)->horizontalHeader();
	header->resizeSections(QHeaderView::ResizeToContents);

	SET_DRAG_AND_DROP_ENABLED(StationInformation);
	SET_SELECTION_BEHAVIOR(StationInformation, QAbstractItemView::SelectRows);
	SET_SELECTION_MODE(StationInformation, QAbstractItemView::SingleSelection);

	GET_TABLE(StationInformation)->setItemDelegateForColumn(14, new comboBoxDelegate(this, &pMM->m_mYesOrNo));
	GET_TABLE(StationInformation)->setItemDelegateForColumn(15, new comboBoxDelegate(this, &pMM->m_mYesOrNo));

	return false;
}

IMPLEMENT_INIT_FUNCTION_FOR_CLASS(PARENT_EDITOR_CLASS, StationDistance)
{
	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();
	SET_MODEL_FOR_TABLE_VIEW(StationDistance, pDM);
	INSTALL_EVENT_FILTER(StationDistance);

	GET_TABLE(StationDistance)->setItemDelegateForColumn(1, new SQLDelegate(this, &pTM->VECTOR_CLASS(StationInformation), 0, 2, TYPE_TEXT));
	GET_TABLE(StationDistance)->setItemDelegateForColumn(2, new SQLDelegate(this, &pTM->VECTOR_CLASS(StationInformation), 0, 2, TYPE_TEXT));

	SET_SELECTION_BEHAVIOR(StationDistance, QAbstractItemView::SelectRows);
	SET_SELECTION_MODE(StationDistance, QAbstractItemView::SingleSelection);
	SET_DRAG_AND_DROP_ENABLED(StationDistance);

	QHeaderView *header = GET_TABLE(StationDistance)->horizontalHeader();
	header->resizeSections(QHeaderView::ResizeToContents);
	header->setStretchLastSection(true);


	connect(GET_TABLE_MODEL(pDM, StationDistance).get(), SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(updateStationDistance(const QModelIndex &, const QModelIndex &)));

	connect(ui.btnRefreshDistanceTable, SIGNAL(clicked()), this, SLOT(onBtnRefreshDistanceTable()));

	return false;
}

IMPLEMENT_INIT_FUNCTION_FOR_CLASS(PARENT_EDITOR_CLASS, StopPtnHeader)
{
	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();
	auto *pMM = CMapManage::GetInstance();

	SET_MODEL_FOR_TABLE_VIEW(StopPtnHeader, pDM);
	INSTALL_EVENT_FILTER(StopPtnHeader);

	GET_TABLE(StopPtnHeader)->setItemDelegateForColumn(1, new SQLDelegate(this, &pTM->VECTOR_CLASS(StationInformation), 0, 2, TYPE_TEXT));
	GET_TABLE(StopPtnHeader)->setItemDelegateForColumn(2, new SQLDelegate(this, &pTM->VECTOR_CLASS(StationInformation), 0, 2, TYPE_TEXT));
	GET_TABLE(StopPtnHeader)->setItemDelegateForColumn(4, new SQLDelegate(this, &pTM->VECTOR_CLASS(LineMapPool), 0, 1, TYPE_TEXT));
	GET_TABLE(StopPtnHeader)->setItemDelegateForColumn(6, new comboBoxDelegate(this, &pMM->m_mBoundType));
	GET_TABLE(StopPtnHeader)->setContextMenuPolicy(Qt::CustomContextMenu);

	SET_SELECTION_BEHAVIOR(StopPtnHeader, QAbstractItemView::SelectRows);
	SET_SELECTION_MODE(StopPtnHeader, QAbstractItemView::SingleSelection);

	SET_DRAG_AND_DROP_ENABLED(StopPtnHeader);

	QHeaderView *header = GET_TABLE(StopPtnHeader)->horizontalHeader();
	header->resizeSections(QHeaderView::ResizeToContents);

	connect(GET_TABLE(StopPtnHeader), SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showContextMenu(const QPoint &)));
	CONNECT_ROW_CHAHANGED_SLOT(StopPtnHeader, updateStopPtnRoutes(const QModelIndex &, const QModelIndex &));

	connect(GET_TABLE_MODEL(pDM, StopPtnHeader).get(), 
		SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), 
		this, SLOT(updateStopPtnHeader(const QModelIndex &, const QModelIndex &)));

	return false;
}

IMPLEMENT_INIT_FUNCTION_FOR_CLASS(PARENT_EDITOR_CLASS, StopPtnRoutes)
{
	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();
	auto *pMM = CMapManage::GetInstance();
	SET_MODEL_FOR_TABLE_VIEW(StopPtnRoutes, pDM);
	INSTALL_EVENT_FILTER(StopPtnRoutes);
	SET_SELECTION_BEHAVIOR(StopPtnRoutes, QAbstractItemView::SelectRows);
	SET_SELECTION_MODE(StopPtnRoutes, QAbstractItemView::SingleSelection);

	GET_TABLE(StopPtnRoutes)->setItemDelegateForColumn(3, new SQLDelegate(this, &pTM->VECTOR_CLASS(StationDistance), 0, 4, TYPE_TEXT));
	GET_TABLE(StopPtnRoutes)->setItemDelegateForColumn(4, new SQLDelegate(this, &pTM->VECTOR_CLASS(EDDIndex), 0, 1, TYPE_TEXT));
	GET_TABLE(StopPtnRoutes)->setItemDelegateForColumn(5, new comboBoxDelegate(this, &pMM->m_mDoorOpenDirection));
	GET_TABLE(StopPtnRoutes)->setItemDelegateForColumn(6, new SQLDelegate(this, &pTM->VECTOR_CLASS(StationInformation), 0, 2, TYPE_TEXT));

	//GET_TABLE(StopPtnRoutes)->setItemDelegateForColumn(7, new SQLDelegate(this, &pTM->VECTOR_CLASS(AudioContents), 0, 1, TYPE_TEXT));
	GET_TABLE(StopPtnRoutes)->setItemDelegateForColumn(8, new SQLDelegate(this, &pTM->VECTOR_CLASS(PIDContents), 0, 1, TYPE_TEXT));
	GET_TABLE(StopPtnRoutes)->setItemDelegateForColumn(9, new SQLDelegate(this, &pTM->VECTOR_CLASS(PIDContents), 0, 1, TYPE_TEXT));

	//GET_TABLE(StopPtnRoutes)->setItemDelegateForColumn(10, new SQLDelegate(this, &pTM->VECTOR_CLASS(AudioContents), 0, 1, TYPE_TEXT));
	GET_TABLE(StopPtnRoutes)->setItemDelegateForColumn(11, new SQLDelegate(this, &pTM->VECTOR_CLASS(PIDContents), 0, 1, TYPE_TEXT));
	GET_TABLE(StopPtnRoutes)->setItemDelegateForColumn(12, new SQLDelegate(this, &pTM->VECTOR_CLASS(PIDContents), 0, 1, TYPE_TEXT));

	GET_TABLE(StopPtnRoutes)->setContextMenuPolicy(Qt::CustomContextMenu);

	SET_DRAG_AND_DROP_ENABLED(StopPtnRoutes);
	SET_SELECTION_CHANGED_FOR_TABLE(pDM, StopPtnRoutes, selectionChangedStopPtnRoutes(int, int));

	QHeaderView *header = GET_TABLE(StopPtnRoutes)->horizontalHeader();
	//header->resizeSections(QHeaderView::ResizeToContents);
	header->setStretchLastSection(true);

	connect(GET_TABLE(StopPtnRoutes), SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showContextMenu(const QPoint &)));
	CONNECT_ROW_CHAHANGED_SLOT(StopPtnRoutes, updateEventLists(const QModelIndex &, const QModelIndex &));


	connect(GET_TABLE(StopPtnRoutes)->model(), SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)),
		this, SLOT(onAutoFillRouteDestination(const QModelIndex &, const QModelIndex &)));

	connect(ui.btnRouteAutoAdd, SIGNAL(clicked()), this, SLOT(onBtnRouteAutoAdd()));
	connect(ui.btnDelRoutes, SIGNAL(clicked()), this, SLOT(onBtnDelRoutes()));
	return false;
}

IMPLEMENT_INIT_FUNCTION_FOR_CLASS(PARENT_EDITOR_CLASS, EventLists)
{
	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();
	auto *pMM = CMapManage::GetInstance();
	SET_MODEL_FOR_TABLE_VIEW(EventLists, pDM);
	INSTALL_EVENT_FILTER(EventLists);
	SET_SELECTION_BEHAVIOR(EventLists, QAbstractItemView::SelectRows);
	SET_SELECTION_MODE(EventLists, QAbstractItemView::SingleSelection);

	//GET_TABLE(EventLists)->setItemDelegateForColumn(3, new SQLDelegate(this, &pTM->VECTOR_CLASS(AudioContents), 0, 1, TYPE_TEXT));
	GET_TABLE(EventLists)->setItemDelegateForColumn(4, new SQLDelegate(this, &pTM->VECTOR_CLASS(PIDContents), 0, 1, TYPE_TEXT));
	GET_TABLE(EventLists)->setItemDelegateForColumn(7, new SQLDelegate(this, &pTM->VECTOR_CLASS(PIDContents), 0, 1, TYPE_TEXT));
	GET_TABLE(EventLists)->setItemDelegateForColumn(8, new comboBoxDelegate(this, &pMM->m_mEventTypes));
	GET_TABLE(EventLists)->setItemDelegateForColumn(9, new comboBoxDelegate(this, &pMM->m_mDistanceTypes));
	GET_TABLE(EventLists)->setContextMenuPolicy(Qt::CustomContextMenu);

	SET_DRAG_AND_DROP_ENABLED(EventLists);
	SET_SELECTION_CHANGED_FOR_TABLE(pDM, EventLists, selectionChangedEventLists(int, int));
	connect(GET_TABLE(EventLists), SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showContextMenu(const QPoint &)));

	QHeaderView *header = GET_TABLE(EventLists)->horizontalHeader();
	header->resizeSections(QHeaderView::ResizeToContents);

	return false;
}

IMPLEMENT_INIT_FUNCTION_FOR_CLASS(PARENT_EDITOR_CLASS, PIDIndexList)
{
	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();
	SET_MODEL_FOR_TABLE_VIEW(PIDIndexList, pDM);
	INSTALL_EVENT_FILTER(PIDIndexList);
	SET_SELECTION_BEHAVIOR(PIDIndexList, QAbstractItemView::SelectRows);
	SET_SELECTION_MODE(PIDIndexList, QAbstractItemView::SingleSelection);

	SET_DRAG_AND_DROP_ENABLED(PIDIndexList);
	SET_SELECTION_CHANGED_FOR_TABLE(pDM, PIDIndexList, selectionChangedPIDIndexList(int, int));

	GET_TABLE(PIDIndexList)->setItemDelegateForColumn(3, new SQLDelegate(this, &pTM->VECTOR_CLASS(DisplayItemPool), 0, 1, TYPE_TEXT));

	connect(GET_TABLE(PIDIndexList)->model(), SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)),
		this, SLOT(onAutoFillDisplayItem(const QModelIndex &, const QModelIndex &)));

	QHeaderView *header = GET_TABLE(PIDIndexList)->horizontalHeader();
	header->resizeSections(QHeaderView::ResizeToContents);

	return false;
}

IMPLEMENT_INIT_FUNCTION_FOR_CLASS(PARENT_EDITOR_CLASS, EditorTagTable)
{
	auto *pDM = CDataManage::GetInstance();
	auto *pMM = CMapManage::GetInstance();
	SET_MODEL_FOR_TABLE_VIEW(EditorTagTable, pDM);
	INSTALL_EVENT_FILTER(EditorTagTable);

	SET_SELECTION_BEHAVIOR(EditorTagTable, QAbstractItemView::SelectRows);
	SET_SELECTION_MODE(EditorTagTable, QAbstractItemView::SingleSelection);

	SET_EDIT_TRIGGERS(EditorTagTable, QAbstractItemView::DoubleClicked);
	SET_DRAG_AND_DROP_ENABLED(EditorTagTable);
	GET_TABLE(EditorTagTable)->setItemDelegateForColumn(2, new comboBoxDelegate(this, &pMM->m_mMappingVariables));

	auto *spbox = new QSpinBox();
	spbox->setMinimum(0);
	GET_TABLE(EditorTagTable)->setItemDelegateForColumn(4, new QItemDelegate(spbox));
	QHeaderView *header = GET_TABLE(EditorTagTable)->horizontalHeader();
	//header->resizeSections(QHeaderView::ResizeToContents);

	return false;
}

IMPLEMENT_INIT_FUNCTION_FOR_CLASS(PARENT_EDITOR_CLASS, PIDContents)
{
	auto *pMM = CMapManage::GetInstance();
	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();

	SET_MODEL_FOR_TABLE_VIEW(PIDContents, pDM);
	INSTALL_EVENT_FILTER(PIDContents);
	SET_SELECTION_BEHAVIOR(PIDContents, QAbstractItemView::SelectRows);
	SET_SELECTION_MODE(PIDContents, QAbstractItemView::SingleSelection);
	SET_DRAG_AND_DROP_ENABLED(PIDContents);

	GET_TABLE(PIDContents)->setItemDelegateForColumn(3, new SQLDelegate(this, &pTM->VECTOR_CLASS(TrainNumber), 0, 4, TYPE_TEXT));
	GET_TABLE(PIDContents)->setItemDelegateForColumn(4, new SQLDelegate(this, &pTM->VECTOR_CLASS(StationInformation), 0, 2, TYPE_TEXT));
	GET_TABLE(PIDContents)->setItemDelegateForColumn(5, new SQLDelegate(this, &pTM->VECTOR_CLASS(StationInformation), 0, 2, TYPE_TEXT));

	GET_TABLE(PIDContents)->setItemDelegateForColumn(6, new comboBoxDelegate(this, &pMM->m_mMessageTypes));
	GET_TABLE(PIDContents)->setItemDelegateForColumn(9, new comboBoxDelegate(this, &pMM->m_mDevTypes));
	GET_TABLE(PIDContents)->setContextMenuPolicy(Qt::CustomContextMenu);

	QHeaderView *header = GET_TABLE(PIDContents)->horizontalHeader();
	header->resizeSections(QHeaderView::ResizeToContents);

	CONNECT_ROW_CHAHANGED_SLOT(PIDContents, updatePIDIndexList(const QModelIndex &, const QModelIndex &));
	connect(GET_TABLE(PIDContents), SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showContextMenu(const QPoint &)));
	return false;
}

IMPLEMENT_INIT_FUNCTION_FOR_CLASS(PARENT_EDITOR_CLASS, TrainNumber)
{
	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();
	SET_MODEL_FOR_TABLE_VIEW(TrainNumber, pDM);
	INSTALL_EVENT_FILTER(TrainNumber);

	GET_TABLE(TrainNumber)->setItemDelegateForColumn(2, new SQLDelegate(this, &pTM->VECTOR_CLASS(StationInformation), 0, 2, TYPE_TEXT));
	GET_TABLE(TrainNumber)->setItemDelegateForColumn(3, new SQLDelegate(this, &pTM->VECTOR_CLASS(StopPtnHeader), 0, 3, TYPE_TEXT));
	SET_DRAG_AND_DROP_ENABLED(TrainNumber);

	QHeaderView *header = GET_TABLE(TrainNumber)->horizontalHeader();
	header->resizeSections(QHeaderView::ResizeToContents);

	SET_SELECTION_BEHAVIOR(TrainNumber, QAbstractItemView::SelectRows)
		SET_SELECTION_MODE(TrainNumber, QAbstractItemView::SingleSelection)

		return false;
}

IMPLEMENT_INIT_FUNCTION_FOR_CLASS(PARENT_EDITOR_CLASS, AudioStationName)
{
	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();
	SET_MODEL_FOR_TABLE_VIEW(AudioStationName, pDM);
	INSTALL_EVENT_FILTER(AudioStationName);
	SET_DRAG_AND_DROP_ENABLED(AudioStationName);

	QHeaderView *header = GET_TABLE(AudioStationName)->horizontalHeader();
	header->resizeSections(QHeaderView::ResizeToContents);

	// audio file column
	GET_TABLE(AudioStationName)->setItemDelegateForColumn(3, new SQLDelegate(this, &pTM->VECTOR_CLASS(AudioFilePool), 3, 3, TYPE_TEXT));
	GET_TABLE(AudioStationName)->setItemDelegateForColumn(6, new SQLDelegate(this, &pTM->VECTOR_CLASS(AudioFilePool), 3, 3, TYPE_TEXT));

	SET_SELECTION_BEHAVIOR(AudioStationName, QAbstractItemView::SelectRows);
	SET_SELECTION_MODE(AudioStationName, QAbstractItemView::SingleSelection);

	connect(pDM->m_pModAudioStationName.get(),
		SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
		this, SLOT(onAudioStnIndexChanged(const QModelIndex&, const QModelIndex&)));
	return false;
}

IMPLEMENT_INIT_FUNCTION_FOR_CLASS(PARENT_EDITOR_CLASS, AudioPlayList)
{
	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();
	auto *pMM = CMapManage::GetInstance();

	SET_MODEL_FOR_TABLE_VIEW(AudioPlayList, pDM);
	INSTALL_EVENT_FILTER(AudioPlayList);
	SET_DRAG_AND_DROP_ENABLED(AudioPlayList);

	QHeaderView *header = GET_TABLE(AudioPlayList)->horizontalHeader();
	//header->resizeSections(QHeaderView::ResizeToContents);

	GET_TABLE(AudioPlayList)->setItemDelegateForColumn(4, new comboBoxDelegate(this, &pMM->m_mYesOrNo)); // start bell
	GET_TABLE(AudioPlayList)->setItemDelegateForColumn(8, new comboBoxDelegate(this, &pMM->m_mYesOrNo)); // with station
	GET_TABLE(AudioPlayList)->setItemDelegateForColumn(5, new SQLDelegate(SQLDelegate::AUDIO_FILE_IDX_TYPE, this, &pTM->VECTOR_CLASS(AudioFilePool), 3, 3, TYPE_TEXT));
	GET_TABLE(AudioPlayList)->setItemDelegateForColumn(9, new SQLDelegate(SQLDelegate::AUDIO_FILE_IDX_TYPE, this, &pTM->VECTOR_CLASS(AudioFilePool), 3, 3, TYPE_TEXT));
	GET_TABLE(AudioPlayList)->setItemDelegateForColumn(12, new SQLDelegate(SQLDelegate::AUDIO_FILE_IDX_TYPE, this, &pTM->VECTOR_CLASS(AudioFilePool), 3, 3, TYPE_TEXT));
	GET_TABLE(AudioPlayList)->setItemDelegateForColumn(15, new SQLDelegate(SQLDelegate::AUDIO_FILE_IDX_TYPE, this, &pTM->VECTOR_CLASS(AudioFilePool), 3, 3, TYPE_TEXT));
	GET_TABLE(AudioPlayList)->setItemDelegateForColumn(18, new SQLDelegate(SQLDelegate::AUDIO_FILE_IDX_TYPE, this, &pTM->VECTOR_CLASS(AudioFilePool), 3, 3, TYPE_TEXT));

	SET_SELECTION_BEHAVIOR(AudioPlayList, QAbstractItemView::SelectRows);
	SET_SELECTION_MODE(AudioPlayList, QAbstractItemView::SingleSelection);

	connect(pDM->m_pModAudioPlayList.get(),
		SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
		this, SLOT(onAudioIndexChanged(const QModelIndex&, const QModelIndex&)));

	return false;
}

IMPLEMENT_INIT_FUNCTION_FOR_CLASS(PARENT_EDITOR_CLASS, VideoDeviceGroup)
{
	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();
	auto *pMM = CMapManage::GetInstance();

	SET_MODEL_FOR_TABLE_VIEW(VideoDeviceGroup, pDM);
	INSTALL_EVENT_FILTER(VideoDeviceGroup);
	QHeaderView *header = GET_TABLE(VideoDeviceGroup)->horizontalHeader();

	header->resizeSections(QHeaderView::ResizeToContents);

	GET_TABLE(VideoDeviceGroup)->setItemDelegateForColumn(2, new comboBoxDelegate(this, &pMM->m_mVideoDevice));
	GET_TABLE(VideoDeviceGroup)->setItemDelegateForColumn(3, new comboBoxDelegate(this, &pMM->m_mVideoGroup));

	SET_DRAG_AND_DROP_ENABLED(VideoDeviceGroup);
	SET_SELECTION_BEHAVIOR(VideoDeviceGroup, QAbstractItemView::SelectRows);
	SET_SELECTION_MODE(VideoDeviceGroup, QAbstractItemView::SingleSelection);

	CONNECT_ROW_CHAHANGED_SLOT(VideoDeviceGroup, updateVideoPlayList(const QModelIndex &, const QModelIndex &));

	return false;
}

IMPLEMENT_INIT_FUNCTION_FOR_CLASS(PARENT_EDITOR_CLASS, VideoPlayList)
{
	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();
	SET_MODEL_FOR_TABLE_VIEW(VideoPlayList, pDM);
	INSTALL_EVENT_FILTER(VideoPlayList);
	QHeaderView *header = GET_TABLE(VideoPlayList)->horizontalHeader();

	header->resizeSections(QHeaderView::ResizeToContents);

	GET_TABLE(VideoPlayList)->setItemDelegateForColumn(3, new SQLDelegate(this, &pTM->VECTOR_CLASS(VideoFilePool), 3, 3, TYPE_TEXT));

	SET_DRAG_AND_DROP_ENABLED(VideoPlayList);
	SET_SELECTION_BEHAVIOR(VideoPlayList, QAbstractItemView::SelectRows);
	SET_SELECTION_MODE(VideoPlayList, QAbstractItemView::SingleSelection);

	connect(pDM->m_pModVideoPlayList.get(),
		SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
		this, SLOT(onVideoIndexChanged(const QModelIndex&, const QModelIndex&)));

	// row �߰� �ɶ����� VideoDeviceGroup �� PlayList DB ���� (parent index refresh ��)
	connect(ui.m_tblVideoPlayList->model(), &QAbstractItemModel::rowsInserted, []()
	{
		qDebug() << Q_FUNC_INFO;
		auto *pTM = CTableManage::GetInstance();
		pTM->SAVEDATA_FOR_CLASS(VideoDeviceGroup);
	});

	return false;
}

void kvmrt2_media_editor::showContextMenu(const QPoint &pos)
{
	int nValue = 0;
	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();
	if (sender() == GET_TABLE(StopPtnHeader))
	{
		QModelIndex index = GET_TABLE(StopPtnHeader)->indexAt(pos);
		m_pFocusedTableView = GET_TABLE(StopPtnHeader);
		//	m_pCopyStopPtnHeader=pDM->GET_MODEL_CLASS(StopPtnHeader)->getVector()->at(index.row());

		QMenu *menu = new QMenu(this);
		menu->addAction(m_pActCopyItem);
		m_pActCopyItem->setData(index.row());
		m_pActPasteItem->setData(index.row());

		if (!m_pCopyStopPtnHeader.get())
			m_pActPasteItem->setEnabled(false);
		else
			m_pActPasteItem->setEnabled(true);
		menu->addAction(m_pActPasteItem);
		menu->popup(GET_TABLE(StopPtnHeader)->viewport()->mapToGlobal(pos));
	}
	else if (sender() == GET_TABLE(StopPtnRoutes))
	{
		QModelIndex index = GET_TABLE(StopPtnRoutes)->indexAt(pos);
		m_pFocusedTableView = GET_TABLE(StopPtnRoutes);
		//m_pCopyStopPtnRoutes = pDM->GET_MODEL_CLASS(StopPtnRoutes)->getVector()->at(index.row());

		QMenu *menu = new QMenu(this);
		menu->addAction(m_pActCopyItem);
		m_pActCopyItem->setData(index.row());
		m_pActPasteItem->setData(index.row());
		if (!m_pCopyStopPtnRoutes.get())
			m_pActPasteItem->setEnabled(false);
		else
			m_pActPasteItem->setEnabled(true);

		menu->addAction(m_pActPasteItem);
		menu->popup(GET_TABLE(StopPtnRoutes)->viewport()->mapToGlobal(pos));
	}
	else if (sender() == GET_TABLE(EventLists))
	{
		QModelIndex index = GET_TABLE(EventLists)->indexAt(pos);
		m_pFocusedTableView = GET_TABLE(EventLists);
		//m_pCopyEventLists = pDM->GET_MODEL_CLASS(EventLists)->getVector()->at(index.row());

		QMenu *menu = new QMenu(this);
		menu->addAction(m_pActCopyItem);
		m_pActCopyItem->setData(index.row());
		m_pActPasteItem->setData(index.row());
		if (!m_pCopyEventLists.get())
			m_pActPasteItem->setEnabled(false);
		else
			m_pActPasteItem->setEnabled(true);
		menu->addAction(m_pActPasteItem);
		menu->popup(GET_TABLE(EventLists)->viewport()->mapToGlobal(pos));
	}

	else if (sender() == GET_TABLE(PIDContents))
	{
		QModelIndex index = GET_TABLE(PIDContents)->indexAt(pos);
		m_pFocusedTableView = GET_TABLE(PIDContents);
		//m_pCopyEventLists = pDM->GET_MODEL_CLASS(EventLists)->getVector()->at(index.row());

		QMenu *menu = new QMenu(this);
		menu->addAction(m_pActCopyItem);
		m_pActCopyItem->setData(index.row());
		m_pActPasteItem->setData(index.row());
		if (!m_pCopyPIDContents.get())
			m_pActPasteItem->setEnabled(false);
		else
			m_pActPasteItem->setEnabled(true);
		menu->addAction(m_pActPasteItem);
		menu->popup(GET_TABLE(PIDContents)->viewport()->mapToGlobal(pos));
	}
}

void kvmrt2_media_editor::initContextMenu()
{
	m_pActCopyItem = new QAction("&Copy", this);
	m_pActPasteItem = new QAction("&Paste", this);
	connect(m_pActCopyItem, SIGNAL(triggered()), this, SLOT(copyItemTriggered()));
	connect(m_pActPasteItem, SIGNAL(triggered()), this, SLOT(pasteItemTriggered()));
}

void kvmrt2_media_editor::copyItemTriggered()
{
	int nValue = m_pActCopyItem->data().toInt();
	auto *pDM = CDataManage::GetInstance();
	if (GET_TABLE(StopPtnHeader) == m_pFocusedTableView)
	{
		m_pCopyStopPtnHeader = pDM->GET_MODEL_CLASS(StopPtnHeader)->getVector()->at(nValue);
	}
	else if (GET_TABLE(StopPtnRoutes) == m_pFocusedTableView)
	{
		m_pCopyStopPtnRoutes = pDM->GET_MODEL_CLASS(StopPtnRoutes)->getVector()->at(nValue);
	}
	else if (GET_TABLE(EventLists) == m_pFocusedTableView)
	{
		m_pCopyEventLists = pDM->GET_MODEL_CLASS(EventLists)->getVector()->at(nValue);
	}
	else if (GET_TABLE(PIDContents) == m_pFocusedTableView)
	{
		m_pCopyPIDContents = pDM->GET_MODEL_CLASS(PIDContents)->getVector()->at(nValue);
	}
}

void kvmrt2_media_editor::pasteItemTriggered()
{
	int nValue = m_pActPasteItem->data().toInt();
	std::shared_ptr<CSQLData> pSQLData;
	auto *pDM = CDataManage::GetInstance();
	std::vector<std::shared_ptr<CSQLData>> *pVector = 0;
	std::vector<std::shared_ptr<CSQLData>> *pDelVector = 0;
	if (GET_TABLE(StopPtnHeader) == m_pFocusedTableView)
	{
		std::shared_ptr<CSQLData> pSQLData(m_pCopyStopPtnHeader->Clone());
		pVector = pDM->GET_MODEL_CLASS(StopPtnHeader)->getVector();
		pDelVector = pDM->GET_MODEL_CLASS(StopPtnHeader)->getDeletedItemsVector();
		if (nValue != -1)
			pVector->insert(pVector->begin() + nValue, pSQLData);
		else
			pVector->push_back(pSQLData);
		pDM->GET_MODEL_CLASS(StopPtnHeader)->setVectors(pVector, pDelVector);
	}
	else if (GET_TABLE(StopPtnRoutes) == m_pFocusedTableView)
	{
		std::shared_ptr<CSQLData> pSQLData(m_pCopyStopPtnRoutes->Clone());
		pVector = pDM->GET_MODEL_CLASS(StopPtnRoutes)->getVector();
		pDelVector = pDM->GET_MODEL_CLASS(StopPtnRoutes)->getDeletedItemsVector();
		if (nValue != -1)
			pVector->insert(pVector->begin() + nValue, pSQLData);
		else
			pVector->push_back(pSQLData);
		pDM->GET_MODEL_CLASS(StopPtnRoutes)->setVectors(pVector, pDelVector);
	}
	else if (GET_TABLE(EventLists) == m_pFocusedTableView)
	{
		std::shared_ptr<CSQLData> pSQLData(m_pCopyEventLists->Clone());
		pVector = pDM->GET_MODEL_CLASS(EventLists)->getVector();
		pDelVector = pDM->GET_MODEL_CLASS(EventLists)->getDeletedItemsVector();
		if (nValue != -1)
			pVector->insert(pVector->begin() + nValue, pSQLData);
		else
			pVector->push_back(pSQLData);
		pDM->GET_MODEL_CLASS(EventLists)->setVectors(pVector, pDelVector);
	}

	else if (GET_TABLE(PIDContents) == m_pFocusedTableView)
	{
		std::shared_ptr<CSQLData> pSQLData(m_pCopyPIDContents->Clone());
		pVector = pDM->GET_MODEL_CLASS(PIDContents)->getVector();
		pDelVector = pDM->GET_MODEL_CLASS(PIDContents)->getDeletedItemsVector();
		if (nValue != -1)
			pVector->insert(pVector->begin() + nValue, pSQLData);
		else
			pVector->push_back(pSQLData);
		pDM->GET_MODEL_CLASS(PIDContents)->setVectors(pVector, pDelVector);
	}
}

void kvmrt2_media_editor::selectionChangedStopPtnRoutes(int nTop, int nBottom)
{
	QItemSelection selectedItems;
	auto *pDM = CDataManage::GetInstance();
	dataModel *pTmpDM = (dataModel*)pDM->GET_MODEL_CLASS(StopPtnRoutes).get();
	QModelIndex topLeft = pTmpDM->index(nTop, 0, QModelIndex());
	QModelIndex bottomRight = pTmpDM->index(nBottom, pTmpDM->columnCount() - 1, QModelIndex());
	selectedItems.select(topLeft, bottomRight);
	GET_TABLE(StopPtnRoutes)->selectionModel()->clearSelection();
	GET_TABLE(StopPtnRoutes)->selectionModel()->select(selectedItems, QItemSelectionModel::Select);
}
void kvmrt2_media_editor::selectionChangedEventLists(int nTop, int nBottom)
{
	QItemSelection selectedItems;
	auto *pDM = CDataManage::GetInstance();
	dataModel *pTmpDM = (dataModel*)pDM->GET_MODEL_CLASS(EventLists).get();
	QModelIndex topLeft = pTmpDM->index(nTop, 0, QModelIndex());
	QModelIndex bottomRight = pTmpDM->index(nBottom, pTmpDM->columnCount() - 1, QModelIndex());
	selectedItems.select(topLeft, bottomRight);
	GET_TABLE(EventLists)->selectionModel()->clearSelection();
	GET_TABLE(EventLists)->selectionModel()->select(selectedItems, QItemSelectionModel::Select);
}

void kvmrt2_media_editor::selectionChangedPIDIndexList(int nTop, int nBottom)
{
	QItemSelection selectedItems;
	auto *pDM = CDataManage::GetInstance();
	dataModel *pTmpDM = (dataModel*)pDM->GET_MODEL_CLASS(PIDIndexList).get();
	QModelIndex topLeft = pTmpDM->index(nTop, 0, QModelIndex());
	QModelIndex bottomRight = pTmpDM->index(nBottom, pTmpDM->columnCount() - 1, QModelIndex());
	selectedItems.select(topLeft, bottomRight);
	GET_TABLE(PIDIndexList)->selectionModel()->clearSelection();
	GET_TABLE(PIDIndexList)->selectionModel()->select(selectedItems, QItemSelectionModel::Select);
}

