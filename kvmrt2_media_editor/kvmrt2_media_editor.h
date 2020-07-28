#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_kvmrt2_media_editor.h"
#include "tableViewHelper.h"
#include <memory>

class dataModel;
class QTextAligner;
class CSQLData;

class kvmrt2_media_editor : public QMainWindow
{
	Q_OBJECT

public:
	explicit kvmrt2_media_editor(QString &dbPath, QString &currPath, QWidget *parent = Q_NULLPTR);
	virtual ~kvmrt2_media_editor();

public:
	void initTables();
	void initActions();
	void initMapData();
	void initIcons();
	QMap<QTableView*, std::shared_ptr<dataModel>> m_mEventTable;

	bool eventFilter(QObject *object, QEvent *event);
	void addRowToTable(bool bInsert, QTableView *pView, dataModel *pModel);
	bool deleteRowFromTable(QTableView *pView, dataModel *pModel);
	void closeEvent(QCloseEvent *event);

	// init table
	DECLARE_INIT_FUNCTION_FOR_CLASS(StationInformation);
	DECLARE_INIT_FUNCTION_FOR_CLASS(StationDistance);
	DECLARE_INIT_FUNCTION_FOR_CLASS(TrainNumber);
	DECLARE_INIT_FUNCTION_FOR_CLASS(StopPtnHeader);
	DECLARE_INIT_FUNCTION_FOR_CLASS(StopPtnRoutes);
	DECLARE_INIT_FUNCTION_FOR_CLASS(EventLists);
	DECLARE_INIT_FUNCTION_FOR_CLASS(PIDContents);
	DECLARE_INIT_FUNCTION_FOR_CLASS(PIDIndexList);
	DECLARE_INIT_FUNCTION_FOR_CLASS(AudioStationName);
	DECLARE_INIT_FUNCTION_FOR_CLASS(AudioTotal);
	DECLARE_INIT_FUNCTION_FOR_CLASS(VideoDeviceGroup);
	DECLARE_INIT_FUNCTION_FOR_CLASS(VideoPlayList);
	DECLARE_INIT_FUNCTION_FOR_CLASS(EditorTagTable);

	 // for copy and paste
	 void initContextMenu();
	 std::shared_ptr<CSQLData> m_pCopyStopPtnHeader;
	 std::shared_ptr<CSQLData> m_pCopyStopPtnRoutes;
	 std::shared_ptr<CSQLData> m_pCopyEventLists;
	 std::shared_ptr<CSQLData> m_pCopyPIDContents;
	 QTableView *m_pFocusedTableView;

	 void setHideItemsMainWindow(bool isRelease = false);

private:
	QAction *m_pActCopyItem;
	QAction *m_pActPasteItem;
	QMenu *m_pCopyMenu;

private slots:
	void updateVideoFileVersion();
	void aboutME();
	void licenseInfo();

	// parent-child related slot
	void updateStopPtnRoutes(	const QModelIndex & current, const QModelIndex & previous);
	void updateEventLists(		const QModelIndex & current, const QModelIndex & previous);
	void updatePIDIndexList(	const QModelIndex & current, const QModelIndex & previous);
	void updateVideoPlayList(	const QModelIndex & current, const QModelIndex & previous);
	void updateStationDistance(	const QModelIndex & current, const QModelIndex & previous);
	void updateStopPtnHeader(	const QModelIndex & current, const QModelIndex & previous);

	void selectionChangedStopPtnRoutes(	int, int);
	void selectionChangedEventLists(	int, int);
	void selectionChangedPIDIndexList(	int, int);

	// copy & paste context menu-related slot
	void showContextMenu(const QPoint &);
	void copyItemTriggered();
	void pasteItemTriggered();
	
	// action-related slot
	void onSaveDB();
	void onShowSetting();
	void onShowAudioVideoPool();
	void onShowFontPool();
	void onShowTextPool();
	void onShowImageListPool();
	void onShowBitmapPool();
	void onShowRouteMapPool();
	void onShowLedPool();
	void onShowDisplayListPool();
	void onShowFileUpload();

	// easy to use
	void onBtnRefreshDistanceTable(); // distance table's desc refresh
	void onBtnRouteAutoAdd(); // train route auto set
	void onBtnDelRoutes();
	void onAutoFillRouteDestination(const QModelIndex &topLeft, const QModelIndex &bottomRight);

private:
	Ui::kvmrt2_media_editorClass ui;

	// betatest
public slots:
	
public:
	void betaInit();
	
};
