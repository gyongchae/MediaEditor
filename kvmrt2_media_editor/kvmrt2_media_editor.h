#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_kvmrt2_media_editor.h"
#include "tableViewHelper.h"
#include <memory>
#include "userinfowidget.h"
#include "DefineMode.h"

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
	DECLARE_INIT_FUNCTION_FOR_CLASS(AudioPlayList);
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
	void updateStopPtnRoutes(const QModelIndex & current, const QModelIndex & previous);
	void updateEventLists(const QModelIndex & current, const QModelIndex & previous);
	void updatePIDIndexList(const QModelIndex & current, const QModelIndex & previous);
	void updateVideoPlayList(const QModelIndex & current, const QModelIndex & previous);
	void updateStationDistance(const QModelIndex & current, const QModelIndex & previous);
	void updateStopPtnHeader(const QModelIndex & current, const QModelIndex & previous);

	void selectionChangedStopPtnRoutes(int, int);
	void selectionChangedEventLists(int, int);
	void selectionChangedPIDIndexList(int, int);

	// copy & paste context menu-related slot
	void showContextMenu(const QPoint &);
	void copyItemTriggered();
	void pasteItemTriggered();

	// action-related slot
	void onSaveDB();
	void onLoadDB(); // not implemented yet.
	void onShowSetting();
	void onShowAudioVideoPool();
	void onShowFontPool();
	void onShowTextPool();
	void onShowImageListPool();
	void onShowBitmapPool();
	void onShowRouteMapPool();
	void onShowDisplayListPool();
	void onShowFileUpload();
	void onShowUserInfo();

	// easy to use
	void onBtnRefreshDistanceTable(); // distance table's desc refresh
	void onBtnRouteAutoAdd(); // train route auto set
	void onBtnDelRoutes();
	void onAutoFillRouteDestination(const QModelIndex &topLeft, const QModelIndex &bottomRight);
	void onAutoFillDisplayItem(const QModelIndex &topLeft, const QModelIndex &bottomRight);

	// audio / video file index changed
	void onVideoIndexChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
	void onAudioIndexChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
	void onAudioStnIndexChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);

	// audio duration sync
	void onAudioSyncDuration();


	// account type
public:
	void initAccountType(AccountType type);

private:
	Ui::kvmrt2_media_editorClass ui;
	int m_lastVersion[3]{ 0 };
	UserInfoWidget *m_widgetUserInfo = nullptr; // user info widget

public:
	void initButtons();

	public slots:
	void onAddStnBtnClicked();
	void onDelStnBtnClicked();
	void onDelAllStnBtnClicked();
	void onAddPairBtnClicked();
	void onDelPairBtnClicked();
	void onDelAllPairBtnClicked();
	void onAddPatternBtnClicked();
	void onDelPatternBtnClicked();
	void onDelAllPatternBtnClicked();
	void onAddRouteBtnClicked();
	void onDelRouteBtnClicked();
	void onAddDisplayListBtnClicked();
	void onDelDisplayListBtnClicked();
	void onDelAllDisplayListBtnClicked();
	void onAddDisplayItemBtnClicked();
	void onDelDisplayItemBtnClicked();
	void onDelAllDisplayItemBtnClicked();
	void onAddStnAudioBtnClicked();
	void onDelStnAudioBtnClicked();
	void onDelAllStnAudioBtnClicked();
	void onAddAudioListBtnClicked();
	void onDelAudioListBtnClicked();
	void onDelAllAudioListBtnClicked();
	void onAddVideoGroupBtnClicked();
	void onDelVideoGroupBtnClicked();
	void onDelAllVideoGroupBtnClicked();
	void onAddVideoListBtnClicked();
	void onDelVideoListBtnClicked();
	void onDelAllVideoListBtnClicked();
	void onAddDataTagBtnClicked();
	void onDelDataTagBtnClicked();
	void onDelAllDataTagBtnClicked();

public:
	bool copyDB();
};
