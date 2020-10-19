#pragma once
#include "TableManage.h"
#include "defineSettings.h"
#include <QString>
#include <QMessageBox>
#include <QFileDialog>
#include <QPixmap>
#include <QDataWidgetMapper>

#define GET_MODEL_CLASS(CLASS_NAME)			m_pMod##CLASS_NAME
#define DECLARE_MODEL_CLASS(CLASS_NAME)		std::shared_ptr<dataModel> GET_MODEL_CLASS(CLASS_NAME);

#define APPLICATION_NAME		L"Media Editor"
#define ARE_YOU_SURE			L"Are you sure?"

class dataModel;
class CValueMonitor;

class CDataManage
{
public:
	CDataManage(void);
	~CDataManage(void);
		
	static CDataManage *GetInstance();

	// DECLARE_MODEL_CLASS (all tables)
	DECLARE_MODEL_CLASS(StationInformation)
	DECLARE_MODEL_CLASS(StationDistance)

	DECLARE_MODEL_CLASS(TrainNumber)
	DECLARE_MODEL_CLASS(StopPtnHeader)
	DECLARE_MODEL_CLASS(StopPtnRoutes)
	DECLARE_MODEL_CLASS(EventLists)

	DECLARE_MODEL_CLASS(PIDContents)
	DECLARE_MODEL_CLASS(PIDIndexList)
	DECLARE_MODEL_CLASS(AudioStationName)
	DECLARE_MODEL_CLASS(AudioTotal)
	DECLARE_MODEL_CLASS(VideoDeviceGroup)
	DECLARE_MODEL_CLASS(VideoPlayList)
	DECLARE_MODEL_CLASS(EditorTagTable)

	DECLARE_MODEL_CLASS(OPDataVersion)
	
	DECLARE_MODEL_CLASS(FontPool)
	DECLARE_MODEL_CLASS(AudioFilePool)
	DECLARE_MODEL_CLASS(VideoFilePool)
	DECLARE_MODEL_CLASS(StationImagePool)
	DECLARE_MODEL_CLASS(BitmapImagePool)
	DECLARE_MODEL_CLASS(ImageIndexList)
	DECLARE_MODEL_CLASS(ImageIndex)
	
	DECLARE_MODEL_CLASS(DisplayItemPool)
	DECLARE_MODEL_CLASS(DisplayItem)
	DECLARE_MODEL_CLASS(DisplayProp)
	DECLARE_MODEL_CLASS(DisplayMetaItem)
	DECLARE_MODEL_CLASS(DisplayMetaItemProp)

	DECLARE_MODEL_CLASS(LineMapPool)
	DECLARE_MODEL_CLASS(LineMapLink)
	DECLARE_MODEL_CLASS(LineMapNode)
	DECLARE_MODEL_CLASS(LineMapArrowTexture)
	DECLARE_MODEL_CLASS(LineMapDisplayItem)

	DECLARE_MODEL_CLASS(EDDIndicator)
	DECLARE_MODEL_CLASS(ETNDIndicator)
	DECLARE_MODEL_CLASS(EDDIndex)
	DECLARE_MODEL_CLASS(EDDIndexList)
	// !DECLARE_MODEL_CLASS
public:
	void SetModel();

	static CPathSettings m_tPathSettings;
	static std::shared_ptr<Mortimer::CSettingsStorageIniFile> m_pPathStorage;
	void InitSettings();
	bool BeforeLoadFromDB();
	bool OpenDatabase();

	QString DBPath();
	QString fontPath();
	QString audioPath();
	QString videoPath();
	
	bool queryExec(wchar_t *lpQuery,sqlite3 *pDB);
	void SetVideoFileVersion();

public:
	static bool rmDir(const QString &dirPath);
	static bool copyAtOnce(const QString &srcPath,const QString &dstPath);
	static unsigned short CheckCRCFile(QString strPath,int *pSize);
	static unsigned short crc16_ccitt(const void *buf, int len);

	static unsigned short m_crc16tab[256];

	static HBITMAP CreateBitmapByCreateDIBSection(HDC hdc, int cx, int cy, int bpp,LPVOID *pBuf);
public:

	static void reorderTimeLine(DisplayItem *pItem);
	static void reorderTimeLine(DisplayMetaItem *pItem);

public:
	static bool getMappedValue(wchar_t *pTagName,std::shared_ptr<CValueMonitor> *pVM);
	static void setStationCode(int nValue);
	static void setCarNumber(int nNumber);
	static void setDestinationCode(int nCode);
	static void setDBPath(const wchar_t *pszPath);
private:
	static void initMappedValue();
	static int m_nStationCode;
	static int m_nCarNumber;
	static int m_nDestinationCode;
	static std::map<std::wstring, int *> m_mMappedValue;
	static wchar_t m_szDBPath[256];

public:
	wchar_t GetVersion(wchar_t *pszSelectQuery, wchar_t *szVersionString, sqlite3 *pDB);
	bool sqlite3SetText(sqlite3_stmt *state, int nRow, TYC *lpStr, int nCount);

public:
	QColor m_txtPoolBack;
	QColor m_bmpPoolBack;
	QColor m_imgListBack;

public:
	void setCurrPath(QString &currPath);
	QString& currPath();
	QString m_currPath{ "" };

	// icon path
public:
	QIcon m_iconMain;
	QIcon m_iconQt;
	QIcon m_iconLicense;
	QIcon m_iconNew;
	QIcon m_iconSave;
	QIcon m_iconLoad;
	QIcon m_iconSetting;
	QIcon m_iconFont;
	QIcon m_iconAudioVideo;
	QIcon m_iconText;
	QIcon m_iconBitmap;
	QIcon m_iconImageList;
	QIcon m_iconDisplayPool;
	QIcon m_iconRouteMap;
	QIcon m_iconLED;
	QIcon m_iconUpdate;

	QIcon m_iconUserInfo;

	QIcon m_iconExit;
	QIcon m_iconTabStnInfo;
	QIcon m_iconTabTrainRoute;
	QIcon m_iconTabScreenCon;
	QIcon m_iconTabAudioCon;
	QIcon m_iconTabVideoCon;
	QIcon m_iconTabDataTag;
	QIcon m_iconTile01;
	QIcon m_iconTile02;
	QIcon m_iconTile03;
	QIcon m_iconTile04;
	QIcon m_iconTile05;
	QIcon m_iconTile06;
	QIcon m_iconTile07;
	QIcon m_iconTile08;
	QIcon m_iconTile09;
	QIcon m_iconTile10;
	QIcon m_iconTile11;
	QIcon m_iconTile12;
	QIcon m_iconTile13;
	QIcon m_iconTile14;
	QIcon m_iconTile15;
	QIcon m_iconTile16;

	// route map context menu
	QIcon m_iconAddNode;
	QIcon m_iconEditSpot;
	QIcon m_iconEditNode;
	QIcon m_iconDelMapItem;

	// display pool normal / meta item
	QIcon m_iconAddMeta;
	QIcon m_iconEditProp;
	QIcon m_iconDelDispItem;
	QIcon m_iconRemoveProp;
};



