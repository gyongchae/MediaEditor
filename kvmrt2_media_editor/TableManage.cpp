#include "TableManage.h"

sqlite3 *CTableManage::m_dbSource;

CTableManage::CTableManage(void)
{
}

CTableManage::~CTableManage(void)
{
}

CTableManage *CTableManage::GetInstance()
{
	static CTableManage tDataManage;
	return &tDataManage;
}

bool CTableManage::InitDatabase(TYC *pszPath)
{
	int nRetVal=SQLITE3_OPEN(pszPath,&m_dbSource);
	if (nRetVal != SQLITE_OK)
	{

		return false;
	}
	return true;
}


bool CTableManage::CloseDatabase()
{
	if(m_dbSource&&(SQLITE_OK==sqlite3_close(m_dbSource)))
	{
		m_dbSource=nullptr;
		return true;
	}
	return false;
}


sqlite3* CTableManage::GetDB()
{
	return m_dbSource;
}

void CTableManage::LoadDatabase()
{
	// DECLARE_TEMP_VECTOR_CLASS (has parent table)
	DECLARE_TEMP_VECTOR_CLASS(StopPtnRoutes);
	DECLARE_TEMP_VECTOR_CLASS(EventLists);

	DECLARE_TEMP_VECTOR_CLASS(PIDIndexList);
	DECLARE_TEMP_VECTOR_CLASS(VideoPlayList);

	DECLARE_TEMP_VECTOR_CLASS(ImageIndex);
	
	DECLARE_TEMP_VECTOR_CLASS(DisplayItem);
	DECLARE_TEMP_VECTOR_CLASS(DisplayProp);
	DECLARE_TEMP_VECTOR_CLASS(DisplayMetaItem);
	DECLARE_TEMP_VECTOR_CLASS(DisplayMetaItemProp);

	DECLARE_TEMP_VECTOR_CLASS(LineMapLink);
	DECLARE_TEMP_VECTOR_CLASS(LineMapNode);
	DECLARE_TEMP_VECTOR_CLASS(LineMapArrowTexture);
	DECLARE_TEMP_VECTOR_CLASS(LineMapDisplayItem);
	
	DECLARE_TEMP_VECTOR_CLASS(EDDIndexList);

	// CREATE_EDITOR_CLASS_FOR_CLASS (all tables)
	CREATE_EDITOR_CLASS_FOR_CLASS(StationInformation)
	CREATE_EDITOR_CLASS_FOR_CLASS(StationDistance)
	CREATE_EDITOR_CLASS_FOR_CLASS(TrainNumber);
	CREATE_EDITOR_CLASS_FOR_CLASS(StopPtnHeader)
	CREATE_EDITOR_CLASS_FOR_CLASS(StopPtnRoutes)
	CREATE_EDITOR_CLASS_FOR_CLASS(EventLists)
	CREATE_EDITOR_CLASS_FOR_CLASS(PIDContents)
	CREATE_EDITOR_CLASS_FOR_CLASS(PIDIndexList)
	CREATE_EDITOR_CLASS_FOR_CLASS(AudioStationName);
	CREATE_EDITOR_CLASS_FOR_CLASS(AudioPlayList);
	CREATE_EDITOR_CLASS_FOR_CLASS(VideoDeviceGroup);
	CREATE_EDITOR_CLASS_FOR_CLASS(VideoPlayList);
	CREATE_EDITOR_CLASS_FOR_CLASS(EditorTagTable);

	CREATE_EDITOR_CLASS_FOR_CLASS(OPDataVersion);

	CREATE_EDITOR_CLASS_FOR_CLASS(FontPool);
	CREATE_EDITOR_CLASS_FOR_CLASS(AudioFilePool)
	CREATE_EDITOR_CLASS_FOR_CLASS(VideoFilePool)
	CREATE_EDITOR_CLASS_FOR_CLASS(StationImagePool);
	CREATE_EDITOR_CLASS_FOR_CLASS(BitmapImagePool);
	CREATE_EDITOR_CLASS_FOR_CLASS(ImageIndexList);
	CREATE_EDITOR_CLASS_FOR_CLASS(ImageIndex);
	CREATE_EDITOR_CLASS_FOR_CLASS(DisplayItemPool);
	CREATE_EDITOR_CLASS_FOR_CLASS(DisplayItem);
	CREATE_EDITOR_CLASS_FOR_CLASS(DisplayProp);
	CREATE_EDITOR_CLASS_FOR_CLASS(DisplayMetaItem);
	CREATE_EDITOR_CLASS_FOR_CLASS(DisplayMetaItemProp);

	CREATE_EDITOR_CLASS_FOR_CLASS(LineMapPool);
	CREATE_EDITOR_CLASS_FOR_CLASS(LineMapLink);
	CREATE_EDITOR_CLASS_FOR_CLASS(LineMapArrowTexture);
	CREATE_EDITOR_CLASS_FOR_CLASS(LineMapNode);
	CREATE_EDITOR_CLASS_FOR_CLASS(LineMapDisplayItem);
	// !CREATE_EDITOR_CLASS_FOR_CLASS

	// INIT_EDITORCLASS Parent (same as DECLARE_VECTOR_FOR_CLASS)
	INIT_EDITORCLASS(StationInformation, m_dbSource);
	INIT_EDITORCLASS(StationDistance, m_dbSource);

	INIT_EDITORCLASS(TrainNumber, m_dbSource);
	INIT_EDITORCLASS(StopPtnHeader, m_dbSource);

	INIT_EDITORCLASS(PIDContents, m_dbSource);
	INIT_EDITORCLASS(AudioStationName, m_dbSource);
	INIT_EDITORCLASS(AudioPlayList, m_dbSource);
	INIT_EDITORCLASS(VideoDeviceGroup, m_dbSource);
	INIT_EDITORCLASS(EditorTagTable, m_dbSource);

	INIT_EDITORCLASS(OPDataVersion, m_dbSource);

	INIT_EDITORCLASS(FontPool, m_dbSource);
	INIT_EDITORCLASS(AudioFilePool, m_dbSource);
	INIT_EDITORCLASS(VideoFilePool, m_dbSource);
	INIT_EDITORCLASS(StationImagePool, m_dbSource);
	INIT_EDITORCLASS(BitmapImagePool, m_dbSource);
	INIT_EDITORCLASS(ImageIndexList, m_dbSource);

	INIT_EDITORCLASS(DisplayItemPool, m_dbSource);
	INIT_EDITORCLASS(LineMapPool, m_dbSource);
	// !INIT_EDITORCLASS

	// temp vector (child table) editor initialize
	INIT_EDITORCLASS_WITH_TEMPVECTORS(StopPtnRoutes,		m_dbSource, &TEMP_VECTOR_CLASS(StopPtnRoutes),			nullptr);
	INIT_EDITORCLASS_WITH_TEMPVECTORS(EventLists,			m_dbSource, &TEMP_VECTOR_CLASS(EventLists),				nullptr);
	INIT_EDITORCLASS_WITH_TEMPVECTORS(PIDIndexList,			m_dbSource, &TEMP_VECTOR_CLASS(PIDIndexList),			nullptr);
	INIT_EDITORCLASS_WITH_TEMPVECTORS(VideoPlayList,		m_dbSource, &TEMP_VECTOR_CLASS(VideoPlayList),			nullptr);
	INIT_EDITORCLASS_WITH_TEMPVECTORS(DisplayItem,			m_dbSource, &TEMP_VECTOR_CLASS(DisplayItem),			nullptr);
	INIT_EDITORCLASS_WITH_TEMPVECTORS(DisplayProp,			m_dbSource, &TEMP_VECTOR_CLASS(DisplayProp),			nullptr);
	INIT_EDITORCLASS_WITH_TEMPVECTORS(DisplayMetaItem,		m_dbSource, &TEMP_VECTOR_CLASS(DisplayMetaItem),		nullptr);
	INIT_EDITORCLASS_WITH_TEMPVECTORS(DisplayMetaItemProp,	m_dbSource, &TEMP_VECTOR_CLASS(DisplayMetaItemProp),	nullptr);

	INIT_EDITORCLASS_WITH_TEMPVECTORS(ImageIndex,			m_dbSource, &TEMP_VECTOR_CLASS(ImageIndex),				nullptr);
	INIT_EDITORCLASS_WITH_TEMPVECTORS(LineMapLink,			m_dbSource, &TEMP_VECTOR_CLASS(LineMapLink),			nullptr);
	INIT_EDITORCLASS_WITH_TEMPVECTORS(LineMapNode,			m_dbSource, &TEMP_VECTOR_CLASS(LineMapNode),			nullptr);
	INIT_EDITORCLASS_WITH_TEMPVECTORS(LineMapDisplayItem,	m_dbSource, &TEMP_VECTOR_CLASS(LineMapDisplayItem),		nullptr);
	INIT_EDITORCLASS_WITH_TEMPVECTORS(LineMapArrowTexture,	m_dbSource, &TEMP_VECTOR_CLASS(LineMapArrowTexture),	nullptr);
	
	// MakeRelationShip2 parent - child
	MakeRelationShip2(&VECTOR_CLASS(StopPtnHeader),0,&TEMP_VECTOR_CLASS(StopPtnRoutes));		//부모 자식 관계
	MakeRelationShip2(&TEMP_VECTOR_CLASS(StopPtnRoutes),0,&TEMP_VECTOR_CLASS(EventLists));		//부모 자식 관계
	MakeRelationShip2(&VECTOR_CLASS(PIDContents), 0, &TEMP_VECTOR_CLASS(PIDIndexList));		//부모 자식 관계
	MakeRelationShip2(&VECTOR_CLASS(VideoDeviceGroup), 0, &TEMP_VECTOR_CLASS(VideoPlayList));		//부모 자식 관계
	MakeRelationShip2(&VECTOR_CLASS(DisplayItemPool), 0, &TEMP_VECTOR_CLASS(DisplayItem));		//부모 자식 관계
	MakeRelationShip2(&TEMP_VECTOR_CLASS(DisplayItem), 0, &TEMP_VECTOR_CLASS(DisplayProp));		//부모 자식 관계
	MakeRelationShip2(&VECTOR_CLASS(DisplayItemPool), 1, &TEMP_VECTOR_CLASS(DisplayMetaItem));		//부모 자식 관계
	MakeRelationShip2(&TEMP_VECTOR_CLASS(DisplayMetaItem), 0, &TEMP_VECTOR_CLASS(DisplayMetaItemProp));		//부모 자식 관계
	
	MakeRelationShip2(&VECTOR_CLASS(LineMapPool),0,&TEMP_VECTOR_CLASS(LineMapLink));		//부모 자식 관계
	MakeRelationShip2(&VECTOR_CLASS(LineMapPool),1, nullptr);
	MakeRelationShip2(&VECTOR_CLASS(LineMapPool),2,&TEMP_VECTOR_CLASS(LineMapNode));		//부모 자식 관계
	MakeRelationShip2(&VECTOR_CLASS(LineMapPool),3,&TEMP_VECTOR_CLASS(LineMapArrowTexture));		//부모 자식 관계
	MakeRelationShip2(&VECTOR_CLASS(LineMapPool),4,&TEMP_VECTOR_CLASS(LineMapDisplayItem));		//부모 자식 관계
	MakeRelationShip2(&VECTOR_CLASS(ImageIndexList),0,&TEMP_VECTOR_CLASS(ImageIndex));		//부모 자식 관계
	// !MakeRelationShip2
}

void CTableManage::SaveModified()
{
	// save db (same as DECLARE_VECTOR_FOR_CLASS)
	SAVEDATA_FOR_CLASS(StationInformation);
	SAVEDATA_FOR_CLASS(StationDistance);

	SAVEDATA_FOR_CLASS(TrainNumber);
	SAVEDATA_FOR_CLASS(StopPtnHeader);

	SAVEDATA_FOR_CLASS(PIDContents);
	SAVEDATA_FOR_CLASS(AudioStationName);
	SAVEDATA_FOR_CLASS(AudioPlayList);
	SAVEDATA_FOR_CLASS(VideoDeviceGroup);
	SAVEDATA_FOR_CLASS(EditorTagTable);

	SAVEDATA_FOR_CLASS(OPDataVersion);

	SAVEDATA_FOR_CLASS(FontPool);
	SAVEDATA_FOR_CLASS(AudioFilePool);
	SAVEDATA_FOR_CLASS(VideoFilePool);
	SAVEDATA_FOR_CLASS(StationImagePool);
	SAVEDATA_FOR_CLASS(BitmapImagePool);
	SAVEDATA_FOR_CLASS(ImageIndexList);
	
	SAVEDATA_FOR_CLASS(DisplayItemPool);
	SAVEDATA_FOR_CLASS(LineMapPool);
}

int CTableManage::BackupDb(
	sqlite3 *pDb,               /* Database to back up */
	const TYC *zFilename,      /* Name of file to back up to */
	void(*xProgress)(int, int)  /* Progress function to invoke */
) 
{
	int rc;                     /* Function return code */
	sqlite3 *pFile;             /* Database connection opened on zFilename */
	sqlite3_backup *pBackup;    /* Backup handle used to copy data */
	int nRemaining;
	int nPageCount;
								/* Open the database file identified by zFilename. */
	rc = SQLITE3_OPEN(zFilename, &pFile);
	if (rc == SQLITE_OK) {

		/* Open the sqlite3_backup object used to accomplish the transfer */
		pBackup = sqlite3_backup_init(pFile, "main", pDb, "main");
		if (pBackup) {

			/* Each iteration of this loop copies 5 database pages from database
			** pDb to the backup database. If the return value of backup_step()
			** indicates that there are still further pages to copy, sleep for
			** 250 ms before repeating. */
			do {
				rc = sqlite3_backup_step(pBackup, 5);
				nRemaining=sqlite3_backup_remaining(pBackup);
				nPageCount=sqlite3_backup_pagecount(pBackup);
				if (xProgress)
				{
					xProgress(
						sqlite3_backup_remaining(pBackup),
						sqlite3_backup_pagecount(pBackup)
					);
				}
				if (rc == SQLITE_OK || rc == SQLITE_BUSY || rc == SQLITE_LOCKED) {
					sqlite3_sleep(0);
				}
			} while (rc == SQLITE_OK || rc == SQLITE_BUSY || rc == SQLITE_LOCKED);

			/* Release resources allocated by backup_init(). */
			(void)sqlite3_backup_finish(pBackup);
		}
		rc = sqlite3_errcode(pFile);
	}

	/* Close the database connection opened on database file zFilename
	** and return the result of this function. */
	(void)sqlite3_close(pFile);
	return rc;
}