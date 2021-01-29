#include <QtGui>
#include <QtCore>
#include <QDir>
#include <qdebug>

#include "dataModel.h"
#include "MediaEditor.h"
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
#include "MapManage.h"
#include "editDisplayItemPool.h"
#include "WaveConcentate/Wave.h"
#include "StringScaler.h"
#include "SQLDelegate.h"
#include "tableViewHelper.h"
#include "comboBoxDelegate.h"
#include "DefineMode.h"
#include <stdarg.h>
#include "DefineMode.h"
#include "IniFileManager.h"

const int added_duration = 1000; // ms
const int added_operation_pa_duration = 500; // ms
const int added_stn_name_duration = 1000; // ms

MediaEditor::MediaEditor(QString & dbPath, QString & currPath, QWidget * parent) : QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowTitle(QString("%1")
		.arg(QApplication::applicationName()));

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

	initButtons();

	ui.rbCustomOrder->setChecked(true);

	if (pDM->m_pModOPDataVersion->rowCount() == 1)
	{
		QModelIndex index = pDM->m_pModOPDataVersion->index(0, 0);
		m_lastVersion[0] = pDM->m_pModOPDataVersion->data(index.sibling(0, 2), Qt::DisplayRole).toInt();
		m_lastVersion[1] = pDM->m_pModOPDataVersion->data(index.sibling(0, 3), Qt::DisplayRole).toInt();
		m_lastVersion[2] = pDM->m_pModOPDataVersion->data(index.sibling(0, 4), Qt::DisplayRole).toInt();
	}

	ui.statusBar->showMessage(QString("TOTAL_PAPIS_DATA.DB(v%1.%2.%3) loaded. (%4)")
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

MediaEditor::~MediaEditor()
{
}

void MediaEditor::setHideItemsMainWindow(bool isRelease)
{
	if (isRelease)
	{
		// hidden action
		ui.actionNew->setVisible(false);
		ui.actionLoad->setVisible(false);
		ui.actionSyncAudioDur->setVisible(false);

		auto *pDM = CDataManage::GetInstance();
		auto *pTM = CTableManage::GetInstance();

		SET_HIDE_TABLE_COLUMN(StationInformation, 0);
		SET_HIDE_TABLE_COLUMN(StationInformation, 4);
		SET_HIDE_TABLE_COLUMN_RANGE(StationInformation, 5, 13);
		SET_HIDE_TABLE_COLUMN(StationInformation, 17);
		SET_HIDE_TABLE_COLUMN(StationInformation, 18);
		SET_HIDE_TABLE_COLUMN(StationDistance, 0);
		SET_HIDE_TABLE_COLUMN(StationDistance, 5);
		SET_HIDE_TABLE_COLUMN(StationDistance, 6);
		SET_HIDE_TABLE_COLUMN(StationDistance, 7);
		SET_HIDE_TABLE_COLUMN(StopPtnHeader, 0);
		SET_HIDE_TABLE_COLUMN(StopPtnHeader, 5);
		//SET_HIDE_TABLE_COLUMN(StopPtnHeader, 6);

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
		SET_HIDE_TABLE_COLUMN(AudioStationName, 6);
		SET_HIDE_TABLE_COLUMN(AudioStationName, 7);
		SET_HIDE_TABLE_COLUMN(AudioStationName, 8);

		SET_HIDE_TABLE_COLUMN(AudioPlayList, 0);
		SET_HIDE_TABLE_COLUMN(AudioPlayList, 1);
		SET_HIDE_TABLE_COLUMN(AudioPlayList, 3);
		SET_HIDE_TABLE_COLUMN(AudioPlayList, 4);
		SET_HIDE_TABLE_COLUMN(AudioPlayList, 6);
		SET_HIDE_TABLE_COLUMN(AudioPlayList, 7);
		SET_HIDE_TABLE_COLUMN(AudioPlayList, 8);
		SET_HIDE_TABLE_COLUMN(AudioPlayList, 10);
		SET_HIDE_TABLE_COLUMN(AudioPlayList, 11);
		SET_HIDE_TABLE_COLUMN(AudioPlayList, 13);
		SET_HIDE_TABLE_COLUMN(AudioPlayList, 14);
		SET_HIDE_TABLE_COLUMN(AudioPlayList, 16);
		SET_HIDE_TABLE_COLUMN(AudioPlayList, 17);
		SET_HIDE_TABLE_COLUMN(AudioPlayList, 19);
		SET_HIDE_TABLE_COLUMN(AudioPlayList, 20);
		SET_HIDE_TABLE_COLUMN(AudioPlayList, 15); // 3rd audio index
		SET_HIDE_TABLE_COLUMN(AudioPlayList, 18); // 4th audio index

		SET_HIDE_TABLE_COLUMN(VideoDeviceGroup, 0);
		SET_HIDE_TABLE_COLUMN(VideoDeviceGroup, 1);
		SET_HIDE_TABLE_COLUMN(VideoDeviceGroup, 3); 
		SET_HIDE_TABLE_COLUMN(VideoDeviceGroup, 4); 

		SET_HIDE_TABLE_COLUMN(VideoPlayList, 0);
		SET_HIDE_TABLE_COLUMN(VideoPlayList, 1);
		SET_HIDE_TABLE_COLUMN(VideoPlayList, 2);
		SET_HIDE_TABLE_COLUMN(VideoPlayList, 4);
		SET_HIDE_TABLE_COLUMN(VideoPlayList, 5);
		SET_HIDE_TABLE_COLUMN(VideoPlayList, 6);

		SET_HIDE_TABLE_COLUMN(EditorTagTable, 0);
		SET_HIDE_TABLE_COLUMN(EditorTagTable, 3);
	}
}

void MediaEditor::initTables()
{
	// CALL_INIT_FUNCTION
	CALL_INIT_FUNCTION(StationInformation);
	CALL_INIT_FUNCTION(StationDistance);
	CALL_INIT_FUNCTION(StopPtnHeader);
	CALL_INIT_FUNCTION(StopPtnRoutes);
	CALL_INIT_FUNCTION(PIDContents);
	CALL_INIT_FUNCTION(PIDIndexList);
	CALL_INIT_FUNCTION(AudioStationName);
	CALL_INIT_FUNCTION(AudioPlayList);
	CALL_INIT_FUNCTION(VideoDeviceGroup);
	CALL_INIT_FUNCTION(VideoPlayList);
	CALL_INIT_FUNCTION(EditorTagTable);
	// !CALL_INIT_FUNCTION

	// splitter stretch
	ui.splitTab2->setStretchFactor(0, 2);
	ui.splitTab2->setStretchFactor(1, 1);
	ui.splitTab3->setStretchFactor(0, 2);
	ui.splitTab3->setStretchFactor(1, 1);
	ui.splitTab4->setStretchFactor(0, 1);
	ui.splitTab4->setStretchFactor(1, 2);
}

void MediaEditor::initActions()
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
	CONNECT_ACTION_TRIGGERED_SLOT(ui.actionDisplayListPool, onShowDisplayListPool);
	CONNECT_ACTION_TRIGGERED_SLOT(ui.actionUpdate, onShowFileUpload);
	CONNECT_ACTION_TRIGGERED_SLOT(ui.actionExit, close);
	// !CONNECT_ACTION_TRIGGERED_SLOT

	CONNECT_ACTION_TRIGGERED_SLOT(ui.actionLoad, onLoadDB);

	connect(ui.actionAboutME, &QAction::triggered, this, &MediaEditor::aboutME);
	connect(ui.actionAboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);
	connect(ui.actionLicenseInfo, &QAction::triggered, this, &MediaEditor::licenseInfo);
}

void MediaEditor::initMapData()
{
	auto *pDM = CDataManage::GetInstance();
	// SET_EVENT_TABLE
	SET_EVENT_TABLE(pDM, StationInformation);
	SET_EVENT_TABLE(pDM, StationDistance);
	SET_EVENT_TABLE(pDM, StopPtnHeader);
	SET_EVENT_TABLE(pDM, StopPtnRoutes);
	SET_EVENT_TABLE(pDM, PIDContents);
	SET_EVENT_TABLE(pDM, PIDIndexList);
	SET_EVENT_TABLE(pDM, AudioPlayList);
	SET_EVENT_TABLE(pDM, AudioStationName);
	SET_EVENT_TABLE(pDM, VideoDeviceGroup);
	SET_EVENT_TABLE(pDM, VideoPlayList);
	SET_EVENT_TABLE(pDM, EditorTagTable);
	// !SET_EVENT_TABLE
}

void MediaEditor::initIcons()
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

bool MediaEditor::eventFilter(QObject *object, QEvent *event)
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

void MediaEditor::closeEvent(QCloseEvent *event)
{
	auto *pTM = CTableManage::GetInstance();
	pTM->CloseDatabase();
}

// db file version up slot (no use yet)
void MediaEditor::updateVideoFileVersion()
{
	auto *pDM = CDataManage::GetInstance();
	pDM->SetVideoFileVersion();
}

void MediaEditor::addRowToTable(bool bInsert, QTableView *pView, dataModel *pModel)
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

bool MediaEditor::deleteRowFromTable(QTableView *pView, dataModel *pModel)
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

void MediaEditor::onSaveDB()
{
	auto *pTM = CTableManage::GetInstance();
	auto *pDM = CDataManage::GetInstance();

	int currVersion[3]{ 0 };
	QModelIndex index = pDM->m_pModOPDataVersion->index(0, 0);
	currVersion[0] = pDM->m_pModOPDataVersion->data(index.sibling(0, 2), Qt::DisplayRole).toInt();
	currVersion[1] = pDM->m_pModOPDataVersion->data(index.sibling(0, 3), Qt::DisplayRole).toInt();
	currVersion[2] = pDM->m_pModOPDataVersion->data(index.sibling(0, 4), Qt::DisplayRole).toInt();

	int mbResult = QMessageBox::information(this, QString("Save TOTAL_PAPIS_DATA.DB"),
		QString("Do you want to save TOTAL_PAPIS_DATA.DB(version %1.%2.%3)?").arg(currVersion[0]).arg(currVersion[1]).arg(currVersion[2]),
		QMessageBox::Ok | QMessageBox::Cancel);

	if (mbResult == QMessageBox::Ok)
	{
		setCursor(Qt::BusyCursor);
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
		pTM->SaveModified();

		ui.statusBar->showMessage(QString("TOTAL_PAPIS_DATA.DB(v%1.%2.%3) has been saved. (%4)")
			.arg(currVersion[0]).arg(currVersion[1]).arg(currVersion[2])
			.arg(QDateTime::currentDateTime().toString("hh:mm dd/MM/yyyy")));
		// refresh ini file
		onAudioSyncDuration();
		if (!copyDB())
		{
			QMessageBox::critical(this, "Critical error", "Audio/Video DB (OP_DATA.DB) didn't saved.");
		}
		setCursor(Qt::ArrowCursor);
	}
	else
	{
		QMessageBox::information(this, "Save canceled", "TOTAL_PAPIS_DATA.DB didn't saved.");
	}
}

// for test func
void MediaEditor::onLoadDB()
{
	copyDB();
}

void MediaEditor::onShowSetting() // DB version setting
{
	RegistrySettings regDialog(this);
	if (regDialog.exec())
	{

	}
}

void MediaEditor::onShowAudioVideoPool()
{
	ContentsPool audioVideoPool(this);
	if (audioVideoPool.exec())
	{

	}
}

void MediaEditor::onShowFontPool()
{
	fontPool fontPool(this);
	if (fontPool.exec())
	{

	}
}

void MediaEditor::onShowRouteMapPool()
{
	auto *pTM = CTableManage::GetInstance();
	LineMapPoolEdit mapPoolEdit(this);
	if (mapPoolEdit.exec())
	{

	}
}

void MediaEditor::onShowTextPool()
{
	stationImagePool textPool(this);
	if (textPool.exec())
	{

	}
}

void MediaEditor::onShowBitmapPool()
{
	bitmapImagePool bitmapPool(this);
	if (bitmapPool.exec())
	{

	}
}

void MediaEditor::onShowImageListPool()
{
	imageListPool imageListPool(this);
	if (imageListPool.exec())
	{

	}
}

void MediaEditor::onShowDisplayListPool()
{
	editDisplayItemPool displayListPool(this);
	if (displayListPool.exec())
	{

	}
}

void MediaEditor::onShowFileUpload()
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

void MediaEditor::onShowUserInfo()
{
	m_widgetUserInfo->setWindowFlags(Qt::Window);
	m_widgetUserInfo->show();
}

void MediaEditor::onBtnRefreshDistanceTable()
{
	/*
	전체 행 개수 파악
	각 행 별로
	departure, arrival, distance
	전체 설명란 자동 수정

	[개선사항]
	station information table에 역명/역코드가 변경될 경우 departure/arrival에 값이 자동으로 바뀌어야 함.
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

void MediaEditor::onBtnRouteAutoAdd()
{
	/*
	전제 조건
	1. 역 코드는 1씩 증가한다. (안 쓰는 역 발생함)
	2. 거리 테이블에 역 쌍들은 출발역-도착역 간 코드가 1씩 차이난다.
	역 코드가 아니라 table order로 변경함.
	*/

	/*
	1. check stop ptn header validation
	2. route table row check
	3. if row > 0 -> all clear
	4. get stop ptn header's start / final station codes
	5. check north / south bound (start < north -> north, start > north -> south)
	6. in case of NORTH
		start station code로 station name table의 table index get
		해당 table index로 distance 테이블의 departure index 같은 값 찾기
		start station 코드 1 증가 (final stn code - 1 까지)
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

					// code, code + 1로 등록된 distance index가 있는지 확인
					itDep = find_if(
						pTM->VECTOR_CLASS(StationDistance).begin(),
						pTM->VECTOR_CLASS(StationDistance).end(),
						findDistanceDepartureCode(startCode, startCode + 1));

					if (itDep != pTM->VECTOR_CLASS(StationDistance).end())
					{
						// distance index가 있을 경우 stop ptn routes에 등록
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

					// code, code - 1로 등록된 distance index가 있는지 확인
					itDep = find_if(
						pTM->VECTOR_CLASS(StationDistance).begin(),
						pTM->VECTOR_CLASS(StationDistance).end(),
						findDistanceDepartureCode(startCode, startCode - 1));

					if (itDep != pTM->VECTOR_CLASS(StationDistance).end())
					{
						// distance index가 있을 경우 stop ptn routes에 등록
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

void MediaEditor::onBtnDelRoutes()
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

void MediaEditor::onAutoFillRouteDestination(const QModelIndex & topLeft, const QModelIndex & bottomRight)
{
	// 0번째 destination 항목과 나머지 항목 동일하게 업데이트
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

			// 전체 row 순차적으로 첫 번째 destination index와 동일한 값으로 변경
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

void MediaEditor::onAutoFillDisplayItem(const QModelIndex & topLeft, const QModelIndex & bottomRight)
{
	// Display List에 0번째 아이템의 Index 값으로 전체 list에 할당
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

			// 전체 row 순차적으로 첫 번째 destination index와 동일한 값으로 변경
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

void MediaEditor::onVideoIndexChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight)
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

void MediaEditor::onAudioIndexChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight)
{
	const int col = topLeft.column();
	const int row = topLeft.row();
	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();
	// message id
	if (col == 2)
	{
		const int msgID = topLeft.data().toInt();
		if (msgID == MSG_ID_NEXT_BM || msgID == MSG_ID_NEXT_EN || 
			msgID == MSG_ID_ARRIVING_BM || msgID == MSG_ID_ARRIVING_EN || 
			msgID == MSG_ID_ARRIVAL_BM || msgID == MSG_ID_ARRIVAL_EN)
		{
			GET_TABLE_MODEL(pDM, AudioPlayList)->setData(topLeft.sibling(row, 8/*stnPA*/), 1, Qt::EditRole);
		}
		else
		{
			GET_TABLE_MODEL(pDM, AudioPlayList)->setData(topLeft.sibling(row, 8/*stnPA*/), 0, Qt::EditRole);
		}
	}
	// column 변경 시 column 위치 주의
	if (col == 9 || col == 12 || col == 15 || col == 18 || col == 4 /*bell T or F*/ || col == 5 /*bell Index*/) // audio index
	{
		const int audioFileIdx = ui.m_tblAudioPlayList->currentIndex().data(Qt::EditRole).toInt();
		std::vector<std::shared_ptr<CSQLData>>::iterator it;
		it = find_if(pTM->VECTOR_CLASS(AudioFilePool).begin(), pTM->VECTOR_CLASS(AudioFilePool).end(),
			findAudioFileNameByAudioIndex(audioFileIdx));
		QString fileName = "";
		int duration = 0;

		if (col != 4) // bell column이 선택됐을 때는 무시한다.
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

void MediaEditor::onAudioStnIndexChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight)
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

		// column 변경 시 column 위치 주의
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

		// column 변경 시 column 위치 주의
		GET_TABLE_MODEL(pDM, AudioStationName)->setData(topLeft.sibling(row, col + 1/*filename*/), fileName, Qt::EditRole);
		GET_TABLE_MODEL(pDM, AudioStationName)->setData(topLeft.sibling(row, col + 2/*duration*/), duration, Qt::EditRole);
	}
}

void MediaEditor::onAudioSyncDuration()
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

		stIni.paNextBM = (index.sibling(index.row(), 6).data().toInt() != 0) ? index.sibling(index.row(), 6).data().toInt() + added_operation_pa_duration : 0;
		stIni.paNextEN = (index.sibling(index.row(), 7).data().toInt() != 0) ? index.sibling(index.row(), 7).data().toInt() + added_operation_pa_duration : 0;
		stIni.paApprBM = (index.sibling(index.row(), 8).data().toInt() != 0) ? index.sibling(index.row(), 8).data().toInt() + added_operation_pa_duration : 0;
		stIni.paApprEN = (index.sibling(index.row(), 9).data().toInt() != 0) ? index.sibling(index.row(), 9).data().toInt() + added_operation_pa_duration : 0;
		stIni.paArrvBM = (index.sibling(index.row(), 10).data().toInt() != 0) ? index.sibling(index.row(), 10).data().toInt() + added_operation_pa_duration : 0;
		stIni.paArrvEN = (index.sibling(index.row(), 11).data().toInt() != 0) ? index.sibling(index.row(), 11).data().toInt() + added_operation_pa_duration : 0;

		if (stIni.hasExchange == 1) // 1 = true
		{
			stIni.paExchangeBM = index.sibling(index.row(), 12).data().toInt() + added_operation_pa_duration;
			stIni.paExchangeEN = index.sibling(index.row(), 13).data().toInt() + added_operation_pa_duration;
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
		int msgType = index.sibling(index.row(), 22/*msg type*/).data().toInt();
		QString desc = index.sibling(index.row(), 21/*desc*/).data().toString().simplified();
		int duration =
			(
				index.sibling(index.row(), 7).data().toInt() // bell duration (ms)
				+ index.sibling(index.row(), 11).data().toInt() // audio file 1 duration (ms)
				+ index.sibling(index.row(), 14).data().toInt() // audio file 2 duration (ms)
				+ index.sibling(index.row(), 17).data().toInt() // audio file 3 duration (ms)
				+ index.sibling(index.row(), 20).data().toInt() // audio file 4 duration (ms)
				) + added_duration;


		audioListInfo st = { 0 };
		st.id = msgID;
		st.msgType = msgType;
		st.desc = desc;
		st.duration = duration;
		
		iniMan->addAudioListInfo(st);
	} // for (int i = 0; i < totalAudioListRows; i++)
	iniMan->createPaInfoIni();
}

void MediaEditor::initAccountType(AccountType type)
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


void MediaEditor::initButtons()
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

void MediaEditor::onAddStnBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	addRowToTable(false, ui.m_tblStationInformation, pDM->m_pModStationInformation.get());
}

void MediaEditor::onDelStnBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	deleteRowFromTable(ui.m_tblStationInformation, pDM->m_pModStationInformation.get());
}

void MediaEditor::onDelAllStnBtnClicked()
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

void MediaEditor::onAddPairBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	addRowToTable(false, ui.m_tblStationDistance, pDM->m_pModStationDistance.get());
}

void MediaEditor::onDelPairBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	deleteRowFromTable(ui.m_tblStationDistance, pDM->m_pModStationDistance.get());
}

void MediaEditor::onDelAllPairBtnClicked()
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

void MediaEditor::onAddPatternBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	addRowToTable(false, ui.m_tblStopPtnHeader, pDM->m_pModStopPtnHeader.get());
}

void MediaEditor::onDelPatternBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	deleteRowFromTable(ui.m_tblStopPtnHeader, pDM->m_pModStopPtnHeader.get());
}

void MediaEditor::onDelAllPatternBtnClicked()
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

void MediaEditor::onAddRouteBtnClicked()
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

void MediaEditor::onDelRouteBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	deleteRowFromTable(ui.m_tblStopPtnRoutes, pDM->m_pModStopPtnRoutes.get());
}

void MediaEditor::onAddDisplayListBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	addRowToTable(false, ui.m_tblPIDContents, pDM->m_pModPIDContents.get());
}

void MediaEditor::onDelDisplayListBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	deleteRowFromTable(ui.m_tblPIDContents, pDM->m_pModPIDContents.get());
}

void MediaEditor::onDelAllDisplayListBtnClicked()
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

void MediaEditor::onAddDisplayItemBtnClicked()
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

void MediaEditor::onDelDisplayItemBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	deleteRowFromTable(ui.m_tblPIDIndexList, pDM->m_pModPIDIndexList.get());
}

void MediaEditor::onDelAllDisplayItemBtnClicked()
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

void MediaEditor::onAddStnAudioBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	addRowToTable(false, ui.m_tblAudioStationName, pDM->m_pModAudioStationName.get());
}

void MediaEditor::onDelStnAudioBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	deleteRowFromTable(ui.m_tblAudioStationName, pDM->m_pModAudioStationName.get());
}

void MediaEditor::onDelAllStnAudioBtnClicked()
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

void MediaEditor::onAddAudioListBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	addRowToTable(false, ui.m_tblAudioPlayList, pDM->m_pModAudioPlayList.get());
}

void MediaEditor::onDelAudioListBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	deleteRowFromTable(ui.m_tblAudioPlayList, pDM->m_pModAudioPlayList.get());
}

void MediaEditor::onDelAllAudioListBtnClicked()
{
	auto *pDM = CDataManage::GetInstance();
	const int rowCount = pDM->m_pModAudioPlayList.get()->rowCount();
	int ret = QMessageBox::question(this,
		"Delete All",
		QString("Do you want to delete all audio list? (total %1)")
		.arg(rowCount));

	if (ret == QMessageBox::Yes)
	{
		for (int r = 0; r < rowCount; ++r)
		{
			ui.m_tblAudioPlayList->model()->removeRows(0, 1);
		}
	}
	else {}
}

void MediaEditor::onAddVideoGroupBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	addRowToTable(false, ui.m_tblVideoDeviceGroup, pDM->m_pModVideoDeviceGroup.get());
}

void MediaEditor::onDelVideoGroupBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	deleteRowFromTable(ui.m_tblVideoDeviceGroup, pDM->m_pModVideoDeviceGroup.get());
}

void MediaEditor::onDelAllVideoGroupBtnClicked()
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

void MediaEditor::onAddVideoListBtnClicked()
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

void MediaEditor::onDelVideoListBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	deleteRowFromTable(ui.m_tblVideoPlayList, pDM->m_pModVideoPlayList.get());
}

void MediaEditor::onDelAllVideoListBtnClicked()
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

void MediaEditor::onAddDataTagBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	addRowToTable(false, ui.m_tblEditorTagTable, pDM->m_pModEditorTagTable.get());
}

void MediaEditor::onDelDataTagBtnClicked()
{
	qDebug() << Q_FUNC_INFO;
	auto *pDM = CDataManage::GetInstance();
	deleteRowFromTable(ui.m_tblEditorTagTable, pDM->m_pModEditorTagTable.get());
}

void MediaEditor::onDelAllDataTagBtnClicked()
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

void MediaEditor::aboutME()
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

void MediaEditor::licenseInfo()
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

void MediaEditor::updateStopPtnRoutes(const QModelIndex & current, const QModelIndex & previous)
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
		}
	}
	else
	{
		pDM->GET_MODEL_CLASS(StopPtnRoutes)->setVectors(nullptr, nullptr);
	}
}

void MediaEditor::updatePIDIndexList(const QModelIndex & current, const QModelIndex & previous)
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

void MediaEditor::updateVideoPlayList(const QModelIndex & current, const QModelIndex & previous)
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

void MediaEditor::updateStationDistance(const QModelIndex & topLeft, const QModelIndex & bottomRight)
{
	// 자동입력 로직 추가하면 update 제대로 안 됨

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

void MediaEditor::updateStopPtnHeader(const QModelIndex & topLeft, const QModelIndex & bottomRight)
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


#define PARENT_EDITOR_CLASS MediaEditor

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
	header->resizeSection(1, 200);
	header->resizeSection(2, 200);
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
	header->resizeSection(1, 200);
	header->resizeSection(2, 200);

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

	connect(GET_TABLE(StopPtnRoutes)->model(), SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)),
		this, SLOT(onAutoFillRouteDestination(const QModelIndex &, const QModelIndex &)));

	connect(ui.btnRouteAutoAdd, SIGNAL(clicked()), this, SLOT(onBtnRouteAutoAdd()));
	connect(ui.btnDelRoutes, SIGNAL(clicked()), this, SLOT(onBtnDelRoutes()));
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
	header->setStretchLastSection(true);

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
	header->resizeSections(QHeaderView::ResizeToContents);
	header->resizeSection(2, 200);

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


	GET_TABLE(PIDContents)->setItemDelegateForColumn(2, new comboBoxDelegate(this, &pMM->m_mDisplayMsgID));
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

IMPLEMENT_INIT_FUNCTION_FOR_CLASS(PARENT_EDITOR_CLASS, AudioStationName)
{
	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();
	SET_MODEL_FOR_TABLE_VIEW(AudioStationName, pDM);
	INSTALL_EVENT_FILTER(AudioStationName);
	SET_DRAG_AND_DROP_ENABLED(AudioStationName);

	QHeaderView *header = GET_TABLE(AudioStationName)->horizontalHeader();
	header->resizeSections(QHeaderView::ResizeToContents);
	header->setStretchLastSection(true);

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
	header->setStretchLastSection(true);

	GET_TABLE(AudioPlayList)->setItemDelegateForColumn(2, new comboBoxDelegate(this, &pMM->m_mAudioMsgID, true)); // message type
	GET_TABLE(AudioPlayList)->setItemDelegateForColumn(4, new comboBoxDelegate(this, &pMM->m_mYesOrNo)); // start bell
	GET_TABLE(AudioPlayList)->setItemDelegateForColumn(8, new comboBoxDelegate(this, &pMM->m_mYesOrNo)); // with station
	GET_TABLE(AudioPlayList)->setItemDelegateForColumn(5, new SQLDelegate(SQLDelegate::AUDIO_FILE_IDX_TYPE, this, &pTM->VECTOR_CLASS(AudioFilePool), 3, 3, TYPE_TEXT));
	GET_TABLE(AudioPlayList)->setItemDelegateForColumn(9, new SQLDelegate(SQLDelegate::AUDIO_FILE_IDX_TYPE, this, &pTM->VECTOR_CLASS(AudioFilePool), 3, 3, TYPE_TEXT));
	GET_TABLE(AudioPlayList)->setItemDelegateForColumn(12, new SQLDelegate(SQLDelegate::AUDIO_FILE_IDX_TYPE, this, &pTM->VECTOR_CLASS(AudioFilePool), 3, 3, TYPE_TEXT));
	GET_TABLE(AudioPlayList)->setItemDelegateForColumn(15, new SQLDelegate(SQLDelegate::AUDIO_FILE_IDX_TYPE, this, &pTM->VECTOR_CLASS(AudioFilePool), 3, 3, TYPE_TEXT));
	GET_TABLE(AudioPlayList)->setItemDelegateForColumn(18, new SQLDelegate(SQLDelegate::AUDIO_FILE_IDX_TYPE, this, &pTM->VECTOR_CLASS(AudioFilePool), 3, 3, TYPE_TEXT));
	GET_TABLE(AudioPlayList)->setItemDelegateForColumn(22, new comboBoxDelegate(this, &pMM->m_mSpcEmgType, true)); // msg type

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

	header->setStretchLastSection(true);

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

	header->setStretchLastSection(true);

	GET_TABLE(VideoPlayList)->setItemDelegateForColumn(3, new SQLDelegate(this, &pTM->VECTOR_CLASS(VideoFilePool), 3, 3, TYPE_TEXT));

	SET_DRAG_AND_DROP_ENABLED(VideoPlayList);
	SET_SELECTION_BEHAVIOR(VideoPlayList, QAbstractItemView::SelectRows);
	SET_SELECTION_MODE(VideoPlayList, QAbstractItemView::SingleSelection);

	connect(pDM->m_pModVideoPlayList.get(),
		SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
		this, SLOT(onVideoIndexChanged(const QModelIndex&, const QModelIndex&)));

	// row 추가 될때마다 VideoDeviceGroup 및 PlayList DB 저장 (parent index refresh 됨)
	connect(ui.m_tblVideoPlayList->model(), &QAbstractItemModel::rowsInserted, []()
	{
		qDebug() << Q_FUNC_INFO;
		auto *pTM = CTableManage::GetInstance();
		pTM->SAVEDATA_FOR_CLASS(VideoDeviceGroup);
	});

	return false;
}

void MediaEditor::showContextMenu(const QPoint &pos)
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

	else if (sender() == GET_TABLE(PIDContents))
	{
		QModelIndex index = GET_TABLE(PIDContents)->indexAt(pos);
		m_pFocusedTableView = GET_TABLE(PIDContents);

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

void MediaEditor::initContextMenu()
{
	m_pActCopyItem = new QAction("&Copy", this);
	m_pActPasteItem = new QAction("&Paste", this);
	connect(m_pActCopyItem, SIGNAL(triggered()), this, SLOT(copyItemTriggered()));
	connect(m_pActPasteItem, SIGNAL(triggered()), this, SLOT(pasteItemTriggered()));
}

void MediaEditor::copyItemTriggered()
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
	else if (GET_TABLE(PIDContents) == m_pFocusedTableView)
	{
		m_pCopyPIDContents = pDM->GET_MODEL_CLASS(PIDContents)->getVector()->at(nValue);
	}
}

void MediaEditor::pasteItemTriggered()
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

void MediaEditor::selectionChangedStopPtnRoutes(int nTop, int nBottom)
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

void MediaEditor::selectionChangedPIDIndexList(int nTop, int nBottom)
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

bool MediaEditor::copyDB()
{
	setCursor(Qt::BusyCursor);
	// delete OP_DATA.DB
	bool rmResult = QDir().remove(QString("C:/PapisProgram/PapisData/OP_DATA.DB"));
	if (!rmResult)
	{
		QMessageBox::warning(this, "Remove failed", "OP_DATA.DB didn't removed.");
	}

	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("C:/PapisProgram/PapisData/TOTAL_PAPIS_DATA.DB");
	if (!db.open())
	{
		setCursor(Qt::ArrowCursor);
		QMessageBox::critical(nullptr, QString("Cannot open database"),
			QString("Unable to establish a db connection."), QMessageBox::Cancel);
		return false;
	}

	const QString copiedDB = "target";
	QSqlQuery query;
	// attach sqlite
	query.exec(QString("ATTACH 'C:/PapisProgram/PapisData/OP_DATA.DB' as %1").arg(copiedDB));

	// create table
	query.exec(QString("CREATE TABLE %1.AUDIO_FILE_POOL ("
		"TABLE_INDEX	INTEGER,	"
		"FILE_CODE		INTEGER,	"
		"SPARE_CODE		INTEGER,	"
		"FILE_NAME		TEXT(256),	"
		"FILE_CRC	INTEGER,	"
		"FILE_SIZE		INTEGER,	"
		"TABLE_ORDER	INTEGER,	"
		"AUDIO_LEN		INTEGER,	"
		"PRIMARY KEY(TABLE_INDEX)); ").arg(copiedDB));

	query.exec(QString("CREATE TABLE %1.AUDIO_PLAY_LIST ( "
		"TABLE_INDEX	INTEGER,   "
		"TABLE_ORDER	INTEGER,   "
		"MESSAGE_ID	INTEGER,   "
		"PLAY_COUNT	INTEGER,   "
		"BELL_ALARM	INTEGER,   "
		"BELL_INDEX	INTEGER,   "
		"BELL_NAME	TEXT(128),	   "
		"BELL_DURATION	INTEGER,   "
		"STATION_PA	INTEGER,   "
		"AUDIO_IDX1	INTEGER,   "
		"AUDIO_FILE1	TEXT(128), "
		"AUDIO_DUR1	INTEGER,   "
		"AUDIO_IDX2	INTEGER,   "
		"AUDIO_FILE2	TEXT(128), "
		"AUDIO_DUR2	INTEGER,   "
		"AUDIO_IDX3	INTEGER,   "
		"AUDIO_FILE3	TEXT(128), "
		"AUDIO_DUR3	INTEGER,   "
		"AUDIO_IDX4	INTEGER,   "
		"AUDIO_FILE4	TEXT(128), "
		"AUDIO_DUR4	INTEGER,   "
		"DESCRIPTION	TEXT(128), "
		"MSG_TYPE_NAME TEXT(32),"
		"PRIMARY KEY(TABLE_INDEX)); ").arg(copiedDB));

	query.exec(QString("CREATE TABLE %1.AUDIO_STATION_NAME ( "
		"TABLE_INDEX	INTEGER,   "
		"TABLE_ORDER	INTEGER,   "
		"MESSAGE_ID	INTEGER,   "
		"AUDIO_IDX1	INTEGER,   "
		"AUDIO_FILE1	TEXT(128), "
		"AUDIO_DUR1	INTEGER,   "
		"AUDIO_IDX2	INTEGER,   "
		"AUDIO_FILE2	TEXT(128), "
		"AUDIO_DUR2	INTEGER, "
		"PRIMARY KEY(TABLE_INDEX));").arg(copiedDB));

	query.exec(QString("CREATE TABLE %1.DATA_VERSION ( "
		"TABLE_INDEX	INTEGER, "
		"VERSION_STRING	TEXT(32), "
		"VERSION_1	INTEGER, "
		"VERSION_2	INTEGER, "
		"VERSION_3	INTEGER, "
		"PRIMARY KEY(TABLE_INDEX)); ").arg(copiedDB));

	query.exec(QString("CREATE TABLE %1.VIDEO_DEVICE_GROUP ( "
		"TABLE_INDEX	INTEGER,  "
		"TABLE_ORDER	INTEGER,  "
		"DEVICE_TYPE	INTEGER,  "
		"GROUP_ID	INTEGER,	  "
		"DESCRIPTION	TEXT(256),"
		"PRIMARY KEY(TABLE_INDEX)); ").arg(copiedDB));

	query.exec(QString("CREATE TABLE %1.VIDEO_PLAY_LIST ( "
		"TABLE_INDEX	INTEGER,  "
		"PARENT_INDEX	INTEGER,  "
		"TABLE_ORDER	INTEGER,  "
		"VIDEO_INDEX	INTEGER,  "
		"FILE_NAME	TEXT(256),	  "
		"DESCRIPTION	TEXT(256),"
		"DEVICE_TYPE	INTEGER,  "
		"PRIMARY KEY(TABLE_INDEX)); ").arg(copiedDB));

	query.exec(QString("CREATE TABLE %1.VIDEO_FILE_POOL ( "
		"TABLE_INDEX	INTEGER, "
		"FILE_CODE	INTEGER,	 "
		"SPARE_CODE	INTEGER, "
		"FILE_NAME	TEXT(256),	 "
		"FILE_CRC	INTEGER,	 "
		"FILE_SIZE	INTEGER,	 "
		"TABLE_ORDER	INTEGER, "
		"PRIMARY KEY(TABLE_INDEX)); ").arg(copiedDB));

	query.exec(QString("CREATE TABLE %1.[EDITOR_TAG_TABLE] ([TABLE_INDEX] INTEGER PRIMARY KEY,[DESCRIPTION] TEXT(128),[VARIABLE] INTEGER,[TABLE_ORDER] INTEGER, GIF_FRAME INTEGER)").arg(copiedDB));
	query.exec(QString("CREATE TABLE %1.[IMAGE_INDEX] ([TABLE_INDEX] INTEGER PRIMARY KEY,[PARENT_INDEX] INTEGER,[TABLE_ORDER] INTEGER,[TYPE] INTEGER,[TEXT_INDEX] INTEGER,[BITMAP_INDEX] INTEGER,[XPOS] INTEGER,[YPOS] INTEGER)").arg(copiedDB));
	query.exec(QString("CREATE TABLE %1.[IMAGE_INDEX_LIST] ([TABLE_INDEX] INTEGER PRIMARY KEY,[TABLE_ORDER] INTEGER,[DURATION] INTEGER,[DESCRIPTION] TEXT(128), TYPE INTEGER)").arg(copiedDB));
	query.exec(QString("CREATE TABLE %1.[LINEMAP_POOL] ([TABLE_INDEX] INTEGER PRIMARY KEY,[MAP_NAME] TEXT(256),[TILE_SIZE] INTEGER,[LINE_THICKNESS] INTEGER,[DATALENGTH] INTEGER,[DATAPOINTER] LONGBINARY,[WIDTH] INTEGER,[HEIGHT] INTEGER,[DATALENGTHSPOT] INTEGER,[DATAPOINTERSPOT] LONGBINARY,[BACK_COLOR] INTEGER,[LINE_COLOR] INTEGER,[PASSED_COLOR] INTEGER,[FOCUSED_COLOR] INTEGER,[REMAIN_COLOR] INTEGER,[FOCUSED_COLOR1] INTEGER,[FORWARD_ARROW_OFFSET] INTEGER,[BACKWARD_ARROW_OFFSET] INTEGER,[ARROW_THICKNESS] FLOAT,[ARROW_PASSED_COLOR] INTEGER,[ARROW_FOCUSED_COLOR] INTEGER,[ARROW_LEFT_COLOR] INTEGER,[ARROW_FOCUSED_COLOR1] INTEGER,[TABLE_ORDER] INTEGER, ROUTE_BOUND INTEGER, USUSED_LINE_COLOR INTEGER)").arg(copiedDB));
	query.exec(QString("CREATE TABLE %1.[PID_CONTENTS] ([TABLE_INDEX] INTEGER PRIMARY KEY,[DESCRIPTION] TEXT(256),[MESSAGE_ID] INTEGER,[MESSAGE_TYPE] INTEGER,[STATION_INDEX] INTEGER,[DESTINATION_INDEX] INTEGER,[MESSAGE_TYPE_ID] INTEGER,[INTERNAL_INDEX] INTEGER,[TABLE_ORDER] INTEGER,[DEV_TYPE] INTEGER)").arg(copiedDB));
	query.exec(QString("CREATE TABLE %1.[PID_INDEX_LIST] ([TABLE_INDEX] INTEGER PRIMARY KEY,[PARENT_INDEX] INTEGER,[TABLE_ORDER] INTEGER,[CONTENTS_POOL_INDEX] INTEGER)").arg(copiedDB));
	query.exec(QString("CREATE TABLE %1.[STATION_DISTANCE] ([TABLE_INDEX] INTEGER PRIMARY KEY, [DEPARTURE_STATION] INTEGER, [ARRIVAL_STATION] INTEGER, [DISTANCE] INTEGER, [DESC] TEXT(256), [TABLE_ORDER] INTEGER, [DEPARTURE_CODE] INTEGER, [ARRIVAL_CODE] INTEGER)").arg(copiedDB));
	query.exec(QString("CREATE TABLE %1.[STOP_PATTERN_HEADER] ([TABLE_INDEX] INTEGER PRIMARY KEY,[DEPARTURE_STATION] INTEGER,[ARRIVAL_STATION] INTEGER,[DESCRIPTION] TEXT(256),[LINE_MAP_INDEX] INTEGER,[TABLE_ORDER] INTEGER, DRIVE_MODE INTEGER, BOUND INTEGER)").arg(copiedDB));

	query.exec(QString("CREATE TABLE %1.STATION_INFORMATION ( "
		"TABLE_INDEX	INTEGER,	"
		"STATION_CODE	INTEGER,	"
		"STATION_NAME1	TEXT(128),	"
		"STATION_NAME2	TEXT(128),	"
		"DESCRIPTION	TEXT(256),	"
		"TABLE_ORDER	INTEGER,	"
		"DUR_NEXT_BM	INTEGER,	"
		"DUR_NEXT_EN	INTEGER,	"
		"DUR_ARRIVING_BM	INTEGER,"
		"DUR_ARRIVING_EN	INTEGER,"
		"DUR_ARRIVAL_BM	INTEGER,"
		"DUR_ARRIVAL_EN	INTEGER,"
		"DUR_EXCHANGE_BM	INTEGER,"
		"DUR_EXCHANGE_EN	INTEGER,"
		"HAS_EXCHANGE	INTEGER,	"
		"IS_PROVISIONAL	INTEGER,"
		"APPR_PA_DISTANCE	INTEGER,"
		"SPARE1	INTEGER,		"
		"SPARE2	INTEGER,		"
		"PRIMARY KEY(TABLE_INDEX)) ").arg(copiedDB));

	query.exec(QString("CREATE TABLE %1.STOP_PATTERN_ROUTES ("
		"TABLE_INDEX	INTEGER,		"
		"PARENT_INDEX	INTEGER,		"
		"TABLE_ORDER	INTEGER,		"
		"DISTANCE_INDEX	INTEGER,	"
		"DESTINATION_INDEX_LED	INTEGER,"
		"DOOR_DIRECTION	INTEGER,	"
		"DESTINATION_INDEX	INTEGER,	"
		"DOORCLOSE_VOICEEVENT	INTEGER,"
		"DOORCLOSE_VIDEOEVENT	INTEGER,"
		"DOORCLOSE_DRMEVENT	INTEGER,"
		"DOOROPEN_VOICEEVENT	INTEGER,"
		"DOOROPEN_VIDEOEVENT	INTEGER,"
		"DOOROPEN_DRMEVENT	INTEGER,    "
		"PRIMARY KEY(TABLE_INDEX))").arg(copiedDB));
	

	// copy except bitmap related
	query.exec(QString("INSERT OR REPLACE INTO %1.AUDIO_FILE_POOL SELECT * FROM AUDIO_FILE_POOL").arg(copiedDB));
	query.exec(QString("INSERT OR REPLACE INTO %1.AUDIO_PLAY_LIST SELECT * FROM AUDIO_PLAY_LIST").arg(copiedDB));
	query.exec(QString("INSERT OR REPLACE INTO %1.AUDIO_STATION_NAME SELECT * FROM AUDIO_STATION_NAME").arg(copiedDB));
	query.exec(QString("INSERT OR REPLACE INTO %1.DATA_VERSION SELECT * FROM DATA_VERSION").arg(copiedDB));
	query.exec(QString("INSERT OR REPLACE INTO %1.VIDEO_DEVICE_GROUP SELECT * FROM VIDEO_DEVICE_GROUP").arg(copiedDB));
	query.exec(QString("INSERT OR REPLACE INTO %1.VIDEO_PLAY_LIST SELECT * FROM VIDEO_PLAY_LIST").arg(copiedDB));
	query.exec(QString("INSERT OR REPLACE INTO %1.VIDEO_FILE_POOL SELECT * FROM VIDEO_FILE_POOL").arg(copiedDB));
	query.exec(QString("INSERT OR REPLACE INTO %1.EDITOR_TAG_TABLE SELECT * FROM EDITOR_TAG_TABLE").arg(copiedDB));
	query.exec(QString("INSERT OR REPLACE INTO %1.IMAGE_INDEX SELECT * FROM IMAGE_INDEX").arg(copiedDB));
	query.exec(QString("INSERT OR REPLACE INTO %1.IMAGE_INDEX_LIST SELECT * FROM IMAGE_INDEX_LIST").arg(copiedDB));
	query.exec(QString("INSERT OR REPLACE INTO %1.LINEMAP_POOL SELECT * FROM LINEMAP_POOL").arg(copiedDB));
	query.exec(QString("INSERT OR REPLACE INTO %1.PID_CONTENTS SELECT * FROM PID_CONTENTS").arg(copiedDB));
	query.exec(QString("INSERT OR REPLACE INTO %1.PID_INDEX_LIST SELECT * FROM PID_INDEX_LIST").arg(copiedDB));
	query.exec(QString("INSERT OR REPLACE INTO %1.STATION_DISTANCE SELECT * FROM STATION_DISTANCE").arg(copiedDB));
	query.exec(QString("INSERT OR REPLACE INTO %1.STATION_INFORMATION SELECT * FROM STATION_INFORMATION").arg(copiedDB));
	query.exec(QString("INSERT OR REPLACE INTO %1.STOP_PATTERN_HEADER SELECT * FROM STOP_PATTERN_HEADER").arg(copiedDB));
	query.exec(QString("INSERT OR REPLACE INTO %1.STOP_PATTERN_ROUTES SELECT * FROM STOP_PATTERN_ROUTES").arg(copiedDB));
	//query.exec(QString("VACUUM"));
	query.exec(QString("DETACH '%1'").arg(copiedDB));
	
	setCursor(Qt::ArrowCursor);
	return true;
}