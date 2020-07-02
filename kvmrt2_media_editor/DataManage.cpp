#include "DataManage.h"
#include "TableManage.h"
#include "dataModel.h"
#include "ValueMonitor.h"
#if QT_VERSION >= 0x050000
#include <filesystem>				
#else if
#include <boost/filesystem/path.hpp>			
#include <boost/filesystem/operations.hpp>		
#endif

#include <QDir>
#include <qdebug.h>

#define CREATE_VIDEOFILE_VERSION				L"CREATE TABLE [VIDEOFILE_VERSION] ([TABLE_INDEX] INTEGER PRIMARY KEY,[VERSION_STRING] TEXT(32))"
#define	INSERT_VIDEOFILE_VERSION				L"INSERT INTO VIDEOFILE_VERSION (TABLE_INDEX,VERSION_STRING) VALUES (1,'')"
#define UPDATE_VIDEOFILE_VERSION				L"UPDATE VIDEOFILE_VERSION SET VERSION_STRING='%s' WHERE TABLE_INDEX=1"
#define SELECT_VIDEOFILE_VERSION				L"SELECT VERSION_STRING FROM VIDEOFILE_VERSION WHERE TABLE_INDEX=1"

#define INIT_MODEL_FOR_CLASS(CLASS_NAME)							GET_MODEL_CLASS(CLASS_NAME)=std::shared_ptr<dataModel>(new dataModel(CLASS_NAME::m_tSettings,dim(CLASS_NAME::m_tSettings)));
#define SET_EDITOR_FOR_MODEL(TABLE_MANAGE_CLASS,CLASS_NAME)			GET_MODEL_CLASS(CLASS_NAME)->setEditor(TABLE_MANAGE_CLASS->EDITOR_POINTER(CLASS_NAME));
#define SET_VECTOR_FOR_MODEL_PARENT(TABLE_MANAGE_CLASS,CLASS_NAME)	SET_EDITOR_FOR_MODEL(TABLE_MANAGE_CLASS,CLASS_NAME);	GET_MODEL_CLASS(CLASS_NAME)->setVectors(&TABLE_MANAGE_CLASS->VECTOR_CLASS(CLASS_NAME),&TABLE_MANAGE_CLASS->VECTOR_DELETE_CLASS(CLASS_NAME));



CPathSettings CDataManage::m_tPathSettings;
std::shared_ptr<Mortimer::CSettingsStorageIniFile> CDataManage::m_pPathStorage;

wchar_t CDataManage::m_szDBPath[256] = { 0 };

unsigned short CDataManage::m_crc16tab[256] = {
	0x0000,0x1021,0x2042,0x3063,0x4084,0x50a5,0x60c6,0x70e7,
	0x8108,0x9129,0xa14a,0xb16b,0xc18c,0xd1ad,0xe1ce,0xf1ef,
	0x1231,0x0210,0x3273,0x2252,0x52b5,0x4294,0x72f7,0x62d6,
	0x9339,0x8318,0xb37b,0xa35a,0xd3bd,0xc39c,0xf3ff,0xe3de,
	0x2462,0x3443,0x0420,0x1401,0x64e6,0x74c7,0x44a4,0x5485,
	0xa56a,0xb54b,0x8528,0x9509,0xe5ee,0xf5cf,0xc5ac,0xd58d,
	0x3653,0x2672,0x1611,0x0630,0x76d7,0x66f6,0x5695,0x46b4,
	0xb75b,0xa77a,0x9719,0x8738,0xf7df,0xe7fe,0xd79d,0xc7bc,
	0x48c4,0x58e5,0x6886,0x78a7,0x0840,0x1861,0x2802,0x3823,
	0xc9cc,0xd9ed,0xe98e,0xf9af,0x8948,0x9969,0xa90a,0xb92b,
	0x5af5,0x4ad4,0x7ab7,0x6a96,0x1a71,0x0a50,0x3a33,0x2a12,
	0xdbfd,0xcbdc,0xfbbf,0xeb9e,0x9b79,0x8b58,0xbb3b,0xab1a,
	0x6ca6,0x7c87,0x4ce4,0x5cc5,0x2c22,0x3c03,0x0c60,0x1c41,
	0xedae,0xfd8f,0xcdec,0xddcd,0xad2a,0xbd0b,0x8d68,0x9d49,
	0x7e97,0x6eb6,0x5ed5,0x4ef4,0x3e13,0x2e32,0x1e51,0x0e70,
	0xff9f,0xefbe,0xdfdd,0xcffc,0xbf1b,0xaf3a,0x9f59,0x8f78,
	0x9188,0x81a9,0xb1ca,0xa1eb,0xd10c,0xc12d,0xf14e,0xe16f,
	0x1080,0x00a1,0x30c2,0x20e3,0x5004,0x4025,0x7046,0x6067,
	0x83b9,0x9398,0xa3fb,0xb3da,0xc33d,0xd31c,0xe37f,0xf35e,
	0x02b1,0x1290,0x22f3,0x32d2,0x4235,0x5214,0x6277,0x7256,
	0xb5ea,0xa5cb,0x95a8,0x8589,0xf56e,0xe54f,0xd52c,0xc50d,
	0x34e2,0x24c3,0x14a0,0x0481,0x7466,0x6447,0x5424,0x4405,
	0xa7db,0xb7fa,0x8799,0x97b8,0xe75f,0xf77e,0xc71d,0xd73c,
	0x26d3,0x36f2,0x0691,0x16b0,0x6657,0x7676,0x4615,0x5634,
	0xd94c,0xc96d,0xf90e,0xe92f,0x99c8,0x89e9,0xb98a,0xa9ab,
	0x5844,0x4865,0x7806,0x6827,0x18c0,0x08e1,0x3882,0x28a3,
	0xcb7d,0xdb5c,0xeb3f,0xfb1e,0x8bf9,0x9bd8,0xabbb,0xbb9a,
	0x4a75,0x5a54,0x6a37,0x7a16,0x0af1,0x1ad0,0x2ab3,0x3a92,
	0xfd2e,0xed0f,0xdd6c,0xcd4d,0xbdaa,0xad8b,0x9de8,0x8dc9,
	0x7c26,0x6c07,0x5c64,0x4c45,0x3ca2,0x2c83,0x1ce0,0x0cc1,
	0xef1f,0xff3e,0xcf5d,0xdf7c,0xaf9b,0xbfba,0x8fd9,0x9ff8,
	0x6e17,0x7e36,0x4e55,0x5e74,0x2e93,0x3eb2,0x0ed1,0x1ef0
};

CDataManage::CDataManage(void)
{
	initMappedValue();
	m_txtPoolBack = QColor(0, 0, 0);
	m_bmpPoolBack = QColor(255, 255, 255);
	m_imgListBack = QColor(192, 192, 192);
}

CDataManage::~CDataManage(void)
{
}
void CDataManage::setDBPath(const wchar_t *pszPath)
{
	wcscpy(m_szDBPath, pszPath);
}

CDataManage *CDataManage::GetInstance()
{
	static CDataManage tDataManage;
	return &tDataManage;
}

void CDataManage::SetModel()
{
	auto *pTM = CTableManage::GetInstance();

	// INIT_MODEL_FOR_CLASS (all tables)
	INIT_MODEL_FOR_CLASS(StationInformation);
	INIT_MODEL_FOR_CLASS(StationDistance);

	INIT_MODEL_FOR_CLASS(TrainNumber);
	INIT_MODEL_FOR_CLASS(StopPtnHeader);
	INIT_MODEL_FOR_CLASS(StopPtnRoutes);
	INIT_MODEL_FOR_CLASS(EventLists);

	INIT_MODEL_FOR_CLASS(PIDContents);
	INIT_MODEL_FOR_CLASS(PIDIndexList);
	INIT_MODEL_FOR_CLASS(AudioStationName);
	INIT_MODEL_FOR_CLASS(AudioTotal);
	INIT_MODEL_FOR_CLASS(VideoDeviceGroup);
	INIT_MODEL_FOR_CLASS(VideoPlayList);
	INIT_MODEL_FOR_CLASS(EditorTagTable);

	INIT_MODEL_FOR_CLASS(FontPool);
	INIT_MODEL_FOR_CLASS(AudioFilePool);
	INIT_MODEL_FOR_CLASS(VideoFilePool);
	INIT_MODEL_FOR_CLASS(StationImagePool);
	INIT_MODEL_FOR_CLASS(BitmapImagePool);
	INIT_MODEL_FOR_CLASS(ImageIndexList);
	INIT_MODEL_FOR_CLASS(ImageIndex);

	INIT_MODEL_FOR_CLASS(DisplayItemPool);
	INIT_MODEL_FOR_CLASS(DisplayItem);
	INIT_MODEL_FOR_CLASS(DisplayProp);
	INIT_MODEL_FOR_CLASS(DisplayMetaItem);
	INIT_MODEL_FOR_CLASS(DisplayMetaItemProp);

	INIT_MODEL_FOR_CLASS(LineMapPool);
	INIT_MODEL_FOR_CLASS(LineMapLink);
	INIT_MODEL_FOR_CLASS(LineMapNode);
	INIT_MODEL_FOR_CLASS(LineMapArrowTexture);
	INIT_MODEL_FOR_CLASS(LineMapDisplayItem);

	INIT_MODEL_FOR_CLASS(EDDIndex);
	INIT_MODEL_FOR_CLASS(EDDIndexList);
	INIT_MODEL_FOR_CLASS(EDDIndicator);
	INIT_MODEL_FOR_CLASS(ETNDIndicator);
	// !INIT_MODEL_FOR_CLASS

	/************************************************************************************************************* 
		SET_EDITOR_FOR_MODEL & SET_VECTOR_FOR_MODEL_PARENT에 선언된 클래스가 전체 테이블과 같아야 함 (버전 제외)
	*************************************************************************************************************/

	// SET_EDITOR_FOR_MODEL (same as DECLARE_TEMP_VECTOR_CLASS)
	SET_EDITOR_FOR_MODEL(pTM, StopPtnRoutes);
	SET_EDITOR_FOR_MODEL(pTM, EventLists);

	SET_EDITOR_FOR_MODEL(pTM, PIDIndexList);
	SET_EDITOR_FOR_MODEL(pTM, VideoPlayList);

	SET_EDITOR_FOR_MODEL(pTM, ImageIndex);

	SET_EDITOR_FOR_MODEL(pTM, DisplayItem);
	SET_EDITOR_FOR_MODEL(pTM, DisplayProp);
	SET_EDITOR_FOR_MODEL(pTM, DisplayMetaItem);
	SET_EDITOR_FOR_MODEL(pTM, DisplayMetaItemProp);

	SET_EDITOR_FOR_MODEL(pTM, LineMapLink);
	SET_EDITOR_FOR_MODEL(pTM, LineMapNode);
	SET_EDITOR_FOR_MODEL(pTM, LineMapArrowTexture);
	SET_EDITOR_FOR_MODEL(pTM, LineMapDisplayItem);

	SET_EDITOR_FOR_MODEL(pTM, EDDIndexList);
	// !SET_EDITOR_FOR_MODEL

	// SET_VECTOR_FOR_MODEL_PARENT (same as DECLARE_VECTOR_FOR_CLASS)
	SET_VECTOR_FOR_MODEL_PARENT(pTM, StationInformation);
	SET_VECTOR_FOR_MODEL_PARENT(pTM, StationDistance);

	SET_VECTOR_FOR_MODEL_PARENT(pTM, TrainNumber);
	SET_VECTOR_FOR_MODEL_PARENT(pTM, StopPtnHeader);

	SET_VECTOR_FOR_MODEL_PARENT(pTM, PIDContents);
	SET_VECTOR_FOR_MODEL_PARENT(pTM, AudioStationName);
	SET_VECTOR_FOR_MODEL_PARENT(pTM, AudioTotal);
	SET_VECTOR_FOR_MODEL_PARENT(pTM, VideoDeviceGroup);
	SET_VECTOR_FOR_MODEL_PARENT(pTM, EditorTagTable);

	SET_VECTOR_FOR_MODEL_PARENT(pTM, FontPool);
	SET_VECTOR_FOR_MODEL_PARENT(pTM, AudioFilePool);
	SET_VECTOR_FOR_MODEL_PARENT(pTM, VideoFilePool);
	SET_VECTOR_FOR_MODEL_PARENT(pTM, StationImagePool);
	SET_VECTOR_FOR_MODEL_PARENT(pTM, BitmapImagePool);
	SET_VECTOR_FOR_MODEL_PARENT(pTM, ImageIndexList);

	SET_VECTOR_FOR_MODEL_PARENT(pTM, DisplayItemPool);
	SET_VECTOR_FOR_MODEL_PARENT(pTM, LineMapPool);

	SET_VECTOR_FOR_MODEL_PARENT(pTM, EDDIndicator);
	SET_VECTOR_FOR_MODEL_PARENT(pTM, ETNDIndicator);
	SET_VECTOR_FOR_MODEL_PARENT(pTM, EDDIndex);
	// !SET_VECTOR_FOR_MODEL_PARENT
}

void CDataManage::InitSettings()
{
}

bool CDataManage::OpenDatabase()
{
	QString strPath;
	auto *pTM = CTableManage::GetInstance();
#if QT_VERSION >= 0x050000

	if (wcslen(m_szDBPath))
	{
		QFileInfo file(QString::fromStdWString(m_szDBPath));

		wcscpy(m_tPathSettings.DATABASE_FILE_PATH, m_szDBPath);

		strPath = file.absolutePath();
		wcscpy(m_tPathSettings.DATABASE_FILE_PATH, strPath.toStdWString().c_str());

		strPath = file.absolutePath() + "/Audio";
		wcscpy(m_tPathSettings.AUDIO_FILE_SAVE_PATH, strPath.toStdWString().c_str());

		strPath = file.absolutePath() + "/Font";
		wcscpy(m_tPathSettings.FONT_FILE_SAVE_PATH, strPath.toStdWString().c_str());

		strPath = file.absolutePath() + "/Video";
		wcscpy(m_tPathSettings.VIDEO_FILE_SAVE_PATH, strPath.toStdWString().c_str());

		DBPath();
		audioPath();
		videoPath();
		fontPath();

		return pTM->InitDatabase(m_szDBPath);

	}
	else
		return pTM->InitDatabase((wchar_t*)L"C:\\PAPIS_ME\\papisdata.db");
#else if
	boost::filesystem::path full_path = boost::filesystem::path(m_tPathSettings.DATABASE_FILE_PATH) / boost::filesystem::path(DATABASE_FILE_NAME);
	return pTM->InitDatabase((wchar_t*)full_path.wstring().c_str());
#endif
}

bool CDataManage::BeforeLoadFromDB()
{
	auto *pTM = CTableManage::GetInstance();
	queryExec(CREATE_VIDEOFILE_VERSION, pTM->GetDB());
	queryExec(INSERT_VIDEOFILE_VERSION, pTM->GetDB());
	return true;
}

void CDataManage::SetVideoFileVersion()
{
	auto *pTM = CTableManage::GetInstance();
	wchar_t szVersionBuffer[256];
	wchar_t szBuffer[256];
	GetVersion(SELECT_VIDEOFILE_VERSION, szVersionBuffer, pTM->GetDB());
	int nVersion = 1;
	QStringList tList = QString::fromStdWString(szVersionBuffer).split(".");

	if (tList.size() == 3)
	{
		nVersion = (tList.at(0).toInt() * 10000) + (tList.at(1).toInt() * 100) + tList.at(2).toInt();
		nVersion++;
	}

	swprintf_s(szVersionBuffer, _countof(szVersionBuffer), _T("%02d.%02d.%02d"), (nVersion / 10000), ((nVersion % 10000) / 100), nVersion % 100);
	swprintf(szBuffer, UPDATE_VIDEOFILE_VERSION, szVersionBuffer);
	queryExec(szBuffer, pTM->GetDB());
}

wchar_t CDataManage::GetVersion(wchar_t *pszSelectQuery, wchar_t *szVersionString, sqlite3 *pDB)
{
	int nCount;
	TYC *lpStrRet;
	const TYC *tail;
	sqlite3_stmt* state;
	LPTYPESETTINGS pSettings;
	TYC szSelectQuery[4096];
	int nRetVal = SQLITE3_PREPARE(pDB, pszSelectQuery, wcslen(pszSelectQuery) * sizeof(wchar_t), &state, TAIL_CASTING&tail);
	if (SQLITE_OK != nRetVal)
	{
		return false;
	}
	nRetVal = sqlite3_step(state);
	while (nRetVal == SQLITE_ROW)
	{
		int nMaxIndex;
		sqlite3SetText(state, 0, szVersionString, wcslen(szVersionString));
		nRetVal = sqlite3_step(state);
	}
	sqlite3_finalize(state);
	return true;
}

bool CDataManage::sqlite3SetText(sqlite3_stmt *state, int nRow, TYC *lpStr, int nCount)
{
	TYC *lpStrRet;
	lpStrRet = (TYC *)SQLITE3_COLUMN_TEXT(state, nRow);//Line Name
	if (lpStrRet)
	{
		STRCPY(lpStr, lpStrRet);
		return true;
	}
	else
	{
		memset(lpStr, 0, nCount * sizeof(TYC));
	}
	return false;
}

void CDataManage::setCurrPath(QString & currPath)
{
	m_currPath = currPath;
	qDebug() << Q_FUNC_INFO << m_currPath;
	// main window
	m_iconMain = QIcon(m_currPath + "/Res/Free/Rick.ico");
	m_iconQt = QIcon(m_currPath + "/Res/Qt.ico");;
	m_iconLicense = QIcon(m_currPath + "/Res/info.ico");;

	// action
	m_iconNew =				QIcon(m_currPath + "/Res/Free/Alien-2.ico");
	m_iconSave =			QIcon(m_currPath + "/Res/Free/Alien-3.ico");
	m_iconLoad =			QIcon(m_currPath + "/Res/Free/Alien-4.ico");
	m_iconSetting =			QIcon(m_currPath + "/Res/Free/Alien-5.ico");
	m_iconFont =			QIcon(m_currPath + "/Res/Free/Alien-obduction.ico");
	m_iconAudioVideo =		QIcon(m_currPath + "/Res/Free/Alien-ship.ico");
	m_iconText =			QIcon(m_currPath + "/Res/Free/Alien-ship-2.ico");
	m_iconBitmap =			QIcon(m_currPath + "/Res/Free/Asteroid.ico");
	m_iconImageList =		QIcon(m_currPath + "/Res/Free/Comet.ico");
	m_iconDisplayPool =		QIcon(m_currPath + "/Res/Free/Chewbacca.ico");
	m_iconRouteMap =		QIcon(m_currPath + "/Res/Free/Black-hole.ico");
	m_iconLED =				QIcon(m_currPath + "/Res/Free/Bb-8.ico");
	m_iconUpdate =			QIcon(m_currPath + "/Res/Free/Atom.ico");
	m_iconExit =			QIcon(m_currPath + "/Res/Free/Astronaut.ico");

	// tab
	m_iconTabStnInfo =		QIcon(m_currPath + "/Res/Free/Venus.ico");
	m_iconTabTrainRoute =	QIcon(m_currPath + "/Res/Free/Uranus.ico");
	m_iconTabScreenCon =	QIcon(m_currPath + "/Res/Free/Saturn.ico");
	m_iconTabAudioCon =		QIcon(m_currPath + "/Res/Free/Pluto.ico");
	m_iconTabVideoCon =		QIcon(m_currPath + "/Res/Free/Neptune.ico");
	m_iconTabDataTag =		QIcon(m_currPath + "/Res/Free/Mars.ico");

	// tile
	m_iconTile01 = QIcon(m_currPath + "/Res/Tile/tile_1none.png");
	m_iconTile02 = QIcon(m_currPath + "/Res/Tile/tile_2h_u.png");
	m_iconTile03 = QIcon(m_currPath + "/Res/Tile/tile_3h_d.png");
	m_iconTile04 = QIcon(m_currPath + "/Res/Tile/tile_4h_l.png");
	m_iconTile05 = QIcon(m_currPath + "/Res/Tile/tile_5h_r.png");
	m_iconTile06 = QIcon(m_currPath + "/Res/Tile/tile_6f_ud.png");
	m_iconTile07 = QIcon(m_currPath + "/Res/Tile/tile_7f_lr.png");
	m_iconTile08 = QIcon(m_currPath + "/Res/Tile/tile_8cross.png");
	m_iconTile09 = QIcon(m_currPath + "/Res/Tile/tile_9f_ud_h_l.png");
	m_iconTile10 = QIcon(m_currPath + "/Res/Tile/tile_10f_ud_h_r.png");
	m_iconTile11 = QIcon(m_currPath + "/Res/Tile/tile_11f_lr_h_u.png");
	m_iconTile12 = QIcon(m_currPath + "/Res/Tile/tile_12f_lr_h_d.png");
	m_iconTile13 = QIcon(m_currPath + "/Res/Tile/tile_13c_lu.png");
	m_iconTile14 = QIcon(m_currPath + "/Res/Tile/tile_14c_ld.png");
	m_iconTile15 = QIcon(m_currPath + "/Res/Tile/tile_15c_rd.png");
	m_iconTile16 = QIcon(m_currPath + "/Res/Tile/tile_16c_ru.png");

	// spot context menu
	m_iconAddNode =		QIcon(m_currPath + "/Res/Context/node_red.ico");
	m_iconEditNode =	QIcon(m_currPath + "/Res/Kidcon OS Win/Icons/Apps 2.ico");
	m_iconEditSpot =	QIcon(m_currPath + "/Res/Kidcon OS Win/Icons/triangle 2.ico");
	m_iconDelete =		QIcon(m_currPath + "/Res/Context/delete.ico");
}

QString & CDataManage::currPath()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_currPath;
}

QString CDataManage::DBPath()
{
	QString strPath = QDir::fromNativeSeparators(QString::fromStdWString(m_tPathSettings.DATABASE_FILE_PATH));
	QDir path;
	path.mkpath(strPath);
	return strPath;
}


QString CDataManage::audioPath()
{
	QString strPath = QDir::fromNativeSeparators(QString::fromStdWString(m_tPathSettings.AUDIO_FILE_SAVE_PATH));
	QDir path;
	path.mkpath(strPath);
	return strPath;
}

QString CDataManage::videoPath()
{
	QString strPath = QDir::fromNativeSeparators(QString::fromStdWString(m_tPathSettings.VIDEO_FILE_SAVE_PATH));
	QDir path;
	path.mkpath(strPath);
	return strPath;
}

QString CDataManage::fontPath()
{
	QString strPath = QDir::fromNativeSeparators(QString::fromStdWString(m_tPathSettings.FONT_FILE_SAVE_PATH));
	QDir path;
	path.mkpath(strPath);
	return strPath;
}

bool CDataManage::copyAtOnce(const QString &srcPath, const QString &dstPath)
{
	QFileInfo dstInfo(dstPath);
	QDir dir;
	dir.mkpath(dstInfo.absolutePath());
	return QFile::copy(srcPath, dstPath);
}

bool CDataManage::rmDir(const QString &dirPath)
{
	QDir dir(dirPath);
	if (!dir.exists())
		return true;
	foreach(const QFileInfo &info, dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot))
	{
		if (info.isDir())
		{
			if (!rmDir(info.filePath()))
				return false;
		}
		else
		{
			if (!dir.remove(info.fileName()))
				return false;
		}
	}
	QDir parentDir(QFileInfo(dirPath).path());
	return parentDir.rmdir(QFileInfo(dirPath).fileName());
}


unsigned short CDataManage::CheckCRCFile(QString strPath, int *pSize)
{
	char *pBuffer;
	QFile file;
	bool bRet = false;
	int nFileSize;
	HANDLE hMem;
	unsigned short uCRCCode = 0;
	file.setFileName(strPath);
	if (file.exists())
	{
		*pSize = nFileSize = file.size();
		if (nFileSize)
		{
			hMem = GlobalAlloc(GMEM_MOVEABLE, nFileSize);
			pBuffer = (char*)GlobalLock(hMem);
			if (file.open(QIODevice::ReadOnly/*|QIODevice::Text*/))
			{
				file.read(pBuffer, nFileSize);
				file.close();
				uCRCCode = crc16_ccitt(pBuffer, nFileSize);
				GlobalUnlock(hMem);
				GlobalFree(hMem);
			}
			bRet = true;
		}
		else
			file.remove();
	}
	return uCRCCode;
}

unsigned short CDataManage::crc16_ccitt(const void *buf, int len)
{
	register int counter;
	register unsigned short crc = 0;
	char *pBuf = (char *)buf;
	for (counter = 0; counter < len; counter++)
	{
		crc = (crc << 8) ^ m_crc16tab[((crc >> 8) ^ *(pBuf++)) & 0x00FF];
	}
	return crc;
}

bool CDataManage::queryExec(wchar_t *lpQuery, sqlite3 *pDB)
{
	sqlite3_stmt* state;
	const wchar_t *tail;
	auto *pTM = CTableManage::GetInstance();
	sqlite3* dbSource = pTM->GetDB();
	if (dbSource)
	{
		int nRetVal = sqlite3_prepare16_v2(dbSource, lpQuery, wcslen(lpQuery) * sizeof(wchar_t), &state, (const void **)&tail);
		if (SQLITE_OK != nRetVal)
		{
			OutputDebugStringW((wchar_t*)sqlite3_errmsg16(dbSource));
			OutputDebugStringW(L"\n");
			return false;
		}
		int nColumns = sqlite3_column_count(state);
		nRetVal = sqlite3_step(state);
		sqlite3_finalize(state);
		if ((!nColumns) && (nRetVal == SQLITE_DONE))
		{
			return true;
		}
		else
		{
			OutputDebugStringW((wchar_t*)sqlite3_errmsg16(dbSource));
			OutputDebugStringW(L"\n");
		}
		return false;
	}
	return false;
}

HBITMAP CDataManage::CreateBitmapByCreateDIBSection(HDC hdc, int cx, int cy, int bpp, LPVOID *pBuf)
{
	int i;
	unsigned int cbPalette;
	RGBQUAD *pPalette;
	HPALETTE hPal;
	PALETTEENTRY pe[256];
	// 	LPVOID pBits=(*pBuf);

	// 비트맵 정보를 위한 헤더와 팔레트 공간. 팔레트 최대 사이즈(8비트인 경우)를 고려한다.
	byte pbi[sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 256] = { 0 };
	// 참고로 malloc 사용시
	//BITMAPINFO *pbi = (BITMAPINFO *)malloc(sizeof(BITMAPINFOHEADER) + cbPalette);
	//if(!pbi) return 0;
	//memset(pbi, 0, sizeof(BITMAPINFOHEADER)+cbPalette);
	// bpp가 0인 경우 hdc의 bpp로 설정한다.
	if (bpp == 0) {
		bpp = GetDeviceCaps(hdc, BITSPIXEL);
	}
	// 팔레트 사이즈 구하기
	cbPalette = (bpp > 8 ? 0 : 1 << bpp) * sizeof(RGBQUAD); // 8비트보다 크면 필요없다.
	// 이미지 사이즈
	//unsigned int cbImageSize=((((cx * bpp) + 31) & ~31) >> 3) * cy;
	// 헤더파일 입력
	((BITMAPINFOHEADER *)pbi)->biSize = sizeof(BITMAPINFOHEADER);
	((BITMAPINFOHEADER *)pbi)->biWidth = cx;
	((BITMAPINFOHEADER *)pbi)->biHeight = -cy;
	((BITMAPINFOHEADER *)pbi)->biPlanes = 1;
	((BITMAPINFOHEADER *)pbi)->biBitCount = bpp;
	((BITMAPINFOHEADER *)pbi)->biCompression = BI_RGB;
	//((BITMAPINFOHEADER *)pbi)->biSizeImage = iImageSize;
	// 팔레트 설정
	pPalette = (RGBQUAD *)((byte *)pbi + sizeof(BITMAPINFOHEADER));
	switch (bpp)
	{
	case 1:
		// 흑백 팔레트
		memset(pPalette, 0, sizeof(RGBQUAD) * 2);
		pPalette[1].rgbBlue = 125;
		pPalette[1].rgbGreen = 255;
		pPalette[1].rgbRed = 125;
		break;
	case 4:
		// 16색(4비트) 팔레트
		hPal = (HPALETTE)GetStockObject(DEFAULT_PALETTE);
		GetPaletteEntries(hPal, 0, 16, pe);

		pPalette[0].rgbRed = 0;
		pPalette[0].rgbGreen = 0;
		pPalette[0].rgbBlue = 0;
		pPalette[0].rgbReserved = 0;

		pPalette[1].rgbRed = 255;
		pPalette[1].rgbGreen = 0;
		pPalette[1].rgbBlue = 0;
		pPalette[1].rgbReserved = 0;

		pPalette[2].rgbRed = 195;
		pPalette[2].rgbGreen = 255;
		pPalette[2].rgbBlue = 0;
		pPalette[2].rgbReserved = 0;

		pPalette[3].rgbRed = 255;
		pPalette[3].rgbGreen = 125;
		pPalette[3].rgbBlue = 0;
		pPalette[3].rgbReserved = 0;

		pPalette[4].rgbRed = 0;
		pPalette[4].rgbGreen = 0;
		pPalette[4].rgbBlue = 0;
		pPalette[4].rgbReserved = 0;

		pPalette[5].rgbRed = 0;
		pPalette[5].rgbGreen = 0;
		pPalette[5].rgbBlue = 0;
		pPalette[5].rgbReserved = 0;

		pPalette[6].rgbRed = 0;
		pPalette[6].rgbGreen = 0;
		pPalette[6].rgbBlue = 0;
		pPalette[6].rgbReserved = 0;

		pPalette[7].rgbRed = 0;
		pPalette[7].rgbGreen = 0;
		pPalette[7].rgbBlue = 0;
		pPalette[7].rgbReserved = 0;

		pPalette[8].rgbRed = 0;
		pPalette[8].rgbGreen = 0;
		pPalette[8].rgbBlue = 0;
		pPalette[8].rgbReserved = 0;

		pPalette[9].rgbRed = 0;
		pPalette[9].rgbGreen = 0;
		pPalette[9].rgbBlue = 0;
		pPalette[9].rgbReserved = 0;

		pPalette[10].rgbRed = 0;
		pPalette[10].rgbGreen = 0;
		pPalette[10].rgbBlue = 0;
		pPalette[10].rgbReserved = 0;

		pPalette[11].rgbRed = 0;
		pPalette[11].rgbGreen = 0;
		pPalette[11].rgbBlue = 0;
		pPalette[11].rgbReserved = 0;

		pPalette[12].rgbRed = 0;
		pPalette[12].rgbGreen = 0;
		pPalette[12].rgbBlue = 0;
		pPalette[12].rgbReserved = 0;

		pPalette[13].rgbRed = 0;
		pPalette[13].rgbGreen = 0;
		pPalette[13].rgbBlue = 0;
		pPalette[13].rgbReserved = 0;

		pPalette[14].rgbRed = 0;
		pPalette[14].rgbGreen = 0;
		pPalette[14].rgbBlue = 0;
		pPalette[14].rgbReserved = 0;


		pPalette[15].rgbRed = 0;
		pPalette[15].rgbGreen = 0;
		pPalette[15].rgbBlue = 0;
		pPalette[15].rgbReserved = 0;
		break;

	case 8:
		// 256색(8비트) 팔레트
		hPal = CreateHalftonePalette(hdc);
		GetPaletteEntries(hPal, 0, 256, pe);
		DeleteObject(hPal);
		for (i = 0; i < 256; i++) {
			pPalette[i].rgbRed = pe[i].peRed;
			pPalette[i].rgbGreen = pe[i].peGreen;
			pPalette[i].rgbBlue = pe[i].peBlue;
			pPalette[i].rgbReserved = 0;
		}
		break;
	}
	return CreateDIBSection(hdc, (BITMAPINFO *)pbi, DIB_RGB_COLORS, (void**)(pBuf), nullptr, 0);
}

void CDataManage::reorderTimeLine(DisplayMetaItem *pItem)
{
	//시간순서대로 정렬
	std::sort(pItem->m_vChildItem[0].vSQLData.begin(), pItem->m_vChildItem[0].vSQLData.end(), [](std::shared_ptr<CSQLData> &pL, std::shared_ptr<CSQLData> &pR)
	{
		DisplayMetaItemProp *pDPL = (DisplayMetaItemProp*)pL.get();
		DisplayMetaItemProp *pDPR = (DisplayMetaItemProp*)pR.get();
		return pDPL->nAtMiliseconds < pDPR->nAtMiliseconds;
	});
	bool bFirst = true;

	GLfloat fX, fY;
	GLfloat fAngle;
	GLfloat fScalingX, fScalingY;
	GLfloat fOrigX, fOrigY;
	GLfloat fZorder;
	GLfloat fR, fG, fB, fA;
	int nAtMiliseconds = 0;
	int nTransistionType;
	int nVisible;

	pItem->tLine.clear();
	pItem->tLine.jumpTo((GLfloat)0);
	pItem->tLine.setDefaultRemoveOnFinish(false);
	if (!pItem->m_vChildItem[0].vSQLData.size())
		return;

	DisplayMetaItemProp *p = (DisplayMetaItemProp*)pItem->m_vChildItem[0].vSQLData.begin()->get();
	choreograph::MotionOptions<GLfloat> timelineForfX = pItem->tLine.apply(&pItem->m_fTrans[0]).set(p->fX);
	choreograph::MotionOptions<GLfloat> timelineForfY = pItem->tLine.apply(&pItem->m_fTrans[1]).set(p->fY);
	choreograph::MotionOptions<GLfloat> timelineForfAngle = pItem->tLine.apply(&pItem->m_fRotation).set(p->fAngle);
	choreograph::MotionOptions<GLfloat> timelineForfScalingX = pItem->tLine.apply(&pItem->m_fScale[0]).set(p->fScalingX);
	choreograph::MotionOptions<GLfloat> timelineForfScalingY = pItem->tLine.apply(&pItem->m_fScale[1]).set(p->fScalingY);
	choreograph::MotionOptions<GLfloat> timelineForfA = pItem->tLine.apply(&pItem->m_fColor[0]).set(((GLfloat)((p->uColor >> 24) & 0xFF)) / (255.0f));
	choreograph::MotionOptions<GLfloat> timelineForfB = pItem->tLine.apply(&pItem->m_fColor[1]).set(((GLfloat)((p->uColor >> 16) & 0xFF)) / (255.0f));
	choreograph::MotionOptions<GLfloat> timelineForfG = pItem->tLine.apply(&pItem->m_fColor[2]).set(((GLfloat)((p->uColor >> 8) & 0xFF)) / (255.0f));
	choreograph::MotionOptions<GLfloat> timelineForfR = pItem->tLine.apply(&pItem->m_fColor[3]).set(((GLfloat)((p->uColor) & 0xFF)) / (255.0f));
	choreograph::MotionOptions<int> timelineFornVisible = pItem->tLine.apply(&pItem->m_nVisible).set(p->nVisible);

	int nLastTimeForfX;
	int nLastTimeForfY;
	int nLastTimeForfAngle;
	int nLastTimeForfScalingX;
	int nLastTimeForfScalingY;
	int nLastTimeForfOrigX;
	int nLastTimeForfOrigY;
	int nLastTimeFornVisible;
	int nLastTimeForfR;
	int nLastTimeForfG;
	int nLastTimeForfB;
	int nLastTimeForfA;

	nLastTimeForfX = nAtMiliseconds;
	nLastTimeForfY = nAtMiliseconds;
	nLastTimeForfX = nAtMiliseconds;
	nLastTimeForfY = nAtMiliseconds;
	nLastTimeForfAngle = nAtMiliseconds;
	nLastTimeForfScalingX = nAtMiliseconds;
	nLastTimeForfScalingY = nAtMiliseconds;
	nLastTimeForfOrigX = nAtMiliseconds;
	nLastTimeForfOrigY = nAtMiliseconds;
	nLastTimeFornVisible = nAtMiliseconds;

	int nLastTrans[5] = { 0 };
#define INIT_TILELINE_HOLD2(A,B) timelineFor##A.then<Hold>(B,(float)p->nAtMiliseconds);
#define INIT_TILELINE_HOLD(A,B) timelineFor##A.then<Hold>(B,(float)p->nAtMiliseconds);
#define INIT_TIMELINE(A,B) timelineFor##A.rampTo(B, (float)p->nAtMiliseconds);
#define INIT_TIMELINE_COND(A,B,C)	\
	switch(p->nTransType[C])\
	{\
	case 0:\
		INIT_TILELINE_HOLD(A,B)\
		break;\
	case 1:\
		INIT_TIMELINE(A,B)\
		break;\
	}\

#define CALC_LAST_TIME_TRANS(A,B,C) /*if(A!=B)*/\
{switch(p->nTransType[C])\
{\
	case 0:\
		timelineFor##A.then<Hold>(B, (float)(p->nAtMiliseconds - nLastTimeFor##A-1.0f));\
		break;\
	case 1:\
		timelineFor##A.rampTo(B, (float)(p->nAtMiliseconds - nLastTimeFor##A));\
		break;\
}}

#define CALC_LAST_TIME_HOLD2(A,B) timelineFor##A.then<Hold>(B, (float)(p->nAtMiliseconds - nLastTimeFor##A));

	for (auto it : pItem->m_vChildItem[0].vSQLData)
	{
		DisplayMetaItemProp *p = (DisplayMetaItemProp*)it.get();
		if (!bFirst)
		{
			CALC_LAST_TIME_TRANS(fX, p->fX, 0);
			CALC_LAST_TIME_TRANS(fY, p->fY, 0);
			CALC_LAST_TIME_TRANS(fAngle, p->fAngle, 1);
			CALC_LAST_TIME_TRANS(fScalingX, p->fScalingX, 2);
			CALC_LAST_TIME_TRANS(fScalingY, p->fScalingY, 2);
			CALC_LAST_TIME_HOLD2(nVisible, p->nVisible);
			CALC_LAST_TIME_TRANS(fA, ((GLfloat)((p->uColor >> 24) & 0xFF)) / (255.0f), 4);
			CALC_LAST_TIME_TRANS(fB, ((GLfloat)((p->uColor >> 16) & 0xFF)) / (255.0f), 4);
			CALC_LAST_TIME_TRANS(fG, ((GLfloat)((p->uColor >> 8) & 0xFF)) / (255.0f), 4);
			CALC_LAST_TIME_TRANS(fR, ((GLfloat)((p->uColor) & 0xFF)) / (255.0f), 4);
		}
		else
		{
			if (p->nAtMiliseconds)
			{
				INIT_TIMELINE_COND(fX, p->fX, 0);
				INIT_TIMELINE_COND(fY, p->fY, 0);
				INIT_TIMELINE_COND(fAngle, p->fAngle, 1);
				INIT_TIMELINE_COND(fScalingX, p->fScalingX, 2);
				INIT_TIMELINE_COND(fScalingY, p->fScalingY, 2);
				INIT_TILELINE_HOLD2(nVisible, p->nVisible);
				INIT_TIMELINE_COND(fA, ((GLfloat)((p->uColor >> 24) & 0xFF)) / (255.0f), 4);
				INIT_TIMELINE_COND(fB, ((GLfloat)((p->uColor >> 16) & 0xFF)) / (255.0f), 4);
				INIT_TIMELINE_COND(fG, ((GLfloat)((p->uColor >> 8) & 0xFF)) / (255.0f), 4);
				INIT_TIMELINE_COND(fR, ((GLfloat)((p->uColor) & 0xFF)) / (255.0f), 4);
			}
		}
		
		nAtMiliseconds = p->nAtMiliseconds;
		nLastTimeForfX = nAtMiliseconds;
		nLastTimeForfY = nAtMiliseconds;
		nLastTimeForfAngle = nAtMiliseconds;
		nLastTimeForfScalingX = nAtMiliseconds;
		nLastTimeForfScalingY = nAtMiliseconds;
		nLastTimeForfOrigX = nAtMiliseconds;
		nLastTimeForfOrigY = nAtMiliseconds;
		nLastTimeFornVisible = nAtMiliseconds;
		nLastTimeForfR = nAtMiliseconds;
		nLastTimeForfG = nAtMiliseconds;
		nLastTimeForfB = nAtMiliseconds;
		nLastTimeForfA = nAtMiliseconds;
		bFirst = false;
	}
}

void CDataManage::reorderTimeLine(DisplayItem *pItem)
{
	//시간순서대로 정렬
	std::sort(pItem->m_vChildItem[0].vSQLData.begin(), pItem->m_vChildItem[0].vSQLData.end(), [](std::shared_ptr<CSQLData> &pL, std::shared_ptr<CSQLData> &pR)
	{
		DisplayProp *pDPL = (DisplayProp*)pL.get();
		DisplayProp *pDPR = (DisplayProp*)pR.get();
		return pDPL->nAtMiliseconds < pDPR->nAtMiliseconds;
	});
	bool bFirst = true;

	GLfloat fX, fY;
	GLfloat fAngle;
	GLfloat fScalingX, fScalingY;
	GLfloat fOrigX, fOrigY;
	GLfloat fZorder;
	GLfloat fR, fG, fB, fA;
	int nAtMiliseconds = 0;
	int nTransistionType;
	int nVisible;

	pItem->tLine.clear();
	pItem->tLine.jumpTo((GLfloat)0);
	pItem->tLine.setDefaultRemoveOnFinish(false);
	if (!pItem->m_vChildItem[0].vSQLData.size())
		return;

	DisplayProp *p = (DisplayProp*)pItem->m_vChildItem[0].vSQLData.begin()->get();
	choreograph::MotionOptions<GLfloat> timelineForfX = pItem->tLine.apply(&pItem->m_fTrans[0]).set(p->fX);
	choreograph::MotionOptions<GLfloat> timelineForfY = pItem->tLine.apply(&pItem->m_fTrans[1]).set(p->fY);
	choreograph::MotionOptions<GLfloat> timelineForfAngle = pItem->tLine.apply(&pItem->m_fRotation).set(p->fAngle);
	choreograph::MotionOptions<GLfloat> timelineForfScalingX = pItem->tLine.apply(&pItem->m_fScale[0]).set(p->fScalingX);
	choreograph::MotionOptions<GLfloat> timelineForfScalingY = pItem->tLine.apply(&pItem->m_fScale[1]).set(p->fScalingY);
	choreograph::MotionOptions<GLfloat> timelineForfA = pItem->tLine.apply(&pItem->m_fColor[0]).set(((GLfloat)((p->uColor >> 24) & 0xFF)) / (255.0f));
	choreograph::MotionOptions<GLfloat> timelineForfB = pItem->tLine.apply(&pItem->m_fColor[1]).set(((GLfloat)((p->uColor >> 16) & 0xFF)) / (255.0f));
	choreograph::MotionOptions<GLfloat> timelineForfG = pItem->tLine.apply(&pItem->m_fColor[2]).set(((GLfloat)((p->uColor >> 8) & 0xFF)) / (255.0f));
	choreograph::MotionOptions<GLfloat> timelineForfR = pItem->tLine.apply(&pItem->m_fColor[3]).set(((GLfloat)((p->uColor) & 0xFF)) / (255.0f));
	choreograph::MotionOptions<int> timelineFornVisible = pItem->tLine.apply(&pItem->m_nVisible).set(p->nVisible);


	int nLastTimeForfX;
	int nLastTimeForfY;
	int nLastTimeForfAngle;
	int nLastTimeForfScalingX;
	int nLastTimeForfScalingY;
	int nLastTimeForfOrigX;
	int nLastTimeForfOrigY;
	int nLastTimeFornVisible;
	int nLastTimeForfR;
	int nLastTimeForfG;
	int nLastTimeForfB;
	int nLastTimeForfA;

	nLastTimeForfX = nAtMiliseconds;
	nLastTimeForfY = nAtMiliseconds;
	nLastTimeForfX = nAtMiliseconds;
	nLastTimeForfY = nAtMiliseconds;
	nLastTimeForfAngle = nAtMiliseconds;
	nLastTimeForfScalingX = nAtMiliseconds;
	nLastTimeForfScalingY = nAtMiliseconds;
	nLastTimeForfOrigX = nAtMiliseconds;
	nLastTimeForfOrigY = nAtMiliseconds;
	nLastTimeFornVisible = nAtMiliseconds;

	int nLastTrans[5] = { 0 };
#define INIT_TILELINE_HOLD2(A,B) timelineFor##A.then<Hold>(B,(float)p->nAtMiliseconds);
#define INIT_TILELINE_HOLD(A,B) timelineFor##A.then<Hold>(B,(float)p->nAtMiliseconds);
#define INIT_TIMELINE(A,B) timelineFor##A.rampTo(B, (float)p->nAtMiliseconds);

#define INIT_TIMELINE_COND(A,B,C)	\
	switch(p->nTransType[C])\
	{\
	case 0:\
		INIT_TILELINE_HOLD(A,B)\
		break;\
	case 1:\
		INIT_TIMELINE(A,B)\
		break;\
	}\

#define CALC_LAST_TIME_TRANS(A,B,C) /*if(A!=B)*/\
{switch(p->nTransType[C])\
{\
	case 0:\
		timelineFor##A.then<Hold>(B, (float)(p->nAtMiliseconds - nLastTimeFor##A-1.0f));\
		break;\
	case 1:\
		timelineFor##A.rampTo(B, (float)(p->nAtMiliseconds - nLastTimeFor##A));\
		break;\
}}

#define CALC_LAST_TIME_HOLD2(A,B) timelineFor##A.then<Hold>(B, (float)(p->nAtMiliseconds - nLastTimeFor##A));

	for (auto it : pItem->m_vChildItem[0].vSQLData)
	{
		DisplayProp *p = (DisplayProp*)it.get();
		if (!bFirst)
		{
			CALC_LAST_TIME_TRANS(fX, p->fX, 0)
				CALC_LAST_TIME_TRANS(fY, p->fY, 0)
				CALC_LAST_TIME_TRANS(fAngle, p->fAngle, 1)
				CALC_LAST_TIME_TRANS(fScalingX, p->fScalingX, 2)
				CALC_LAST_TIME_TRANS(fScalingY, p->fScalingY, 2)
				CALC_LAST_TIME_HOLD2(nVisible, p->nVisible)
				CALC_LAST_TIME_TRANS(fA, ((GLfloat)((p->uColor >> 24) & 0xFF)) / (255.0f), 4)
				CALC_LAST_TIME_TRANS(fB, ((GLfloat)((p->uColor >> 16) & 0xFF)) / (255.0f), 4)
				CALC_LAST_TIME_TRANS(fG, ((GLfloat)((p->uColor >> 8) & 0xFF)) / (255.0f), 4)
				CALC_LAST_TIME_TRANS(fR, ((GLfloat)((p->uColor) & 0xFF)) / (255.0f), 4)
		}
		else
		{
			if (p->nAtMiliseconds)
			{
				INIT_TIMELINE_COND(fX, p->fX, 0)
					INIT_TIMELINE_COND(fY, p->fY, 0)
					INIT_TIMELINE_COND(fAngle, p->fAngle, 1)
					INIT_TIMELINE_COND(fScalingX, p->fScalingX, 2)
					INIT_TIMELINE_COND(fScalingY, p->fScalingY, 2)
					INIT_TILELINE_HOLD2(nVisible, p->nVisible)
					INIT_TIMELINE_COND(fA, ((GLfloat)((p->uColor >> 24) & 0xFF)) / (255.0f), 4)
					INIT_TIMELINE_COND(fB, ((GLfloat)((p->uColor >> 16) & 0xFF)) / (255.0f), 4)
					INIT_TIMELINE_COND(fG, ((GLfloat)((p->uColor >> 8) & 0xFF)) / (255.0f), 4)
					INIT_TIMELINE_COND(fR, ((GLfloat)((p->uColor) & 0xFF)) / (255.0f), 4)
			}
		}

		nAtMiliseconds = p->nAtMiliseconds;
		nLastTimeForfX = nAtMiliseconds;
		nLastTimeForfY = nAtMiliseconds;
		nLastTimeForfAngle = nAtMiliseconds;
		nLastTimeForfScalingX = nAtMiliseconds;
		nLastTimeForfScalingY = nAtMiliseconds;
		nLastTimeForfOrigX = nAtMiliseconds;
		nLastTimeForfOrigY = nAtMiliseconds;
		nLastTimeFornVisible = nAtMiliseconds;
		nLastTimeForfR = nAtMiliseconds;
		nLastTimeForfG = nAtMiliseconds;
		nLastTimeForfB = nAtMiliseconds;
		nLastTimeForfA = nAtMiliseconds;
		bFirst = false;
	}
}

int CDataManage::m_nStationCode = 0;
int CDataManage::m_nCarNumber = 0;
int CDataManage::m_nDestinationCode = 0;

std::map<std::wstring, int *> CDataManage::m_mMappedValue;

void CDataManage::initMappedValue()
{
	m_mMappedValue[L"STATION_NAME"] = &m_nStationCode;
	m_mMappedValue[L"DESTINATION_NAME"] = &m_nDestinationCode;
	m_mMappedValue[L"CAR_NUMBER:"] = &m_nCarNumber;
	m_mMappedValue[L"STATION_NUMBER"] = &m_nStationCode;
}

bool CDataManage::getMappedValue(wchar_t *pTagName, std::shared_ptr<CValueMonitor> *pVM)
{
	auto it = m_mMappedValue.find(pTagName);
	if (it != m_mMappedValue.end())
	{
		(*pVM) = std::shared_ptr<CValueMonitor>(new CIntValueMonitor());
		(*pVM)->setValue(it->second);
		return true;
	}
	return false;
}

void CDataManage::setStationCode(int nValue)
{
	m_nStationCode = nValue;
}
void CDataManage::setCarNumber(int nNumber)
{
	m_nCarNumber = nNumber;
}
void CDataManage::setDestinationCode(int nCode)
{
	m_nDestinationCode = nCode;
}