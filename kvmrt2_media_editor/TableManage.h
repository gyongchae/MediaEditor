#ifndef TABLE_MANAGE
#define TABLE_MANAGE

#define LINEMAP_USED


#include "DefineTables.h"
#include <memory>
#include <vector>
#include <sqlite3.h>


#define DATABASE_FILE_NAME				_T("OP_DATA.DB")
#define VECTOR_CLASS(CLASS_NAME)		m_v##CLASS_NAME
#define VECTOR_DELETE_CLASS(CLASS_NAME) m_v##CLASS_NAME##DelItems
#define EDITOR_POINTER(CLASS_NAME)		m_p##CLASS_NAME##Editor
#define TEMP_VECTOR_CLASS(CLASS_NAME)	vTemp##CLASS_NAME

#define DECLARE_VECTOR_FOR_CLASS(CLASS_NAME)\
	std::vector<std::shared_ptr<CSQLData>> VECTOR_CLASS(CLASS_NAME);\
	std::vector<std::shared_ptr<CSQLData>> VECTOR_DELETE_CLASS(CLASS_NAME);

#define DECLARE_EDITOR_POINTER_FOR_CLASS(CLASS_NAME) std::shared_ptr<CEditSQLData> EDITOR_POINTER(CLASS_NAME);
#define CREATE_EDITOR_CLASS_FOR_CLASS(CLASS_NAME) EDITOR_POINTER(CLASS_NAME)=std::shared_ptr<CEditSQLData> (new CLASS_NAME##Editor());

#define	INIT_EDITORCLASS(CLASS_NAME,DBSOURCE)\
	EDITOR_POINTER(CLASS_NAME)->SetVectors(&VECTOR_CLASS(CLASS_NAME),&VECTOR_DELETE_CLASS(CLASS_NAME));	\
	EDITOR_POINTER(CLASS_NAME)->AlterTable(DBSOURCE);\
	EDITOR_POINTER(CLASS_NAME)->CreateTable(DBSOURCE);\
	EDITOR_POINTER(CLASS_NAME)->InitData();\
	EDITOR_POINTER(CLASS_NAME)->GetMaxIndex();	

#define INIT_EDITORCLASS_WITH_TEMPVECTORS(CLASS_NAME,DBSOURCE,VECTOR,VECTORDEL)	EDITOR_POINTER(CLASS_NAME)->SetVectors(VECTOR,VECTORDEL);	\
																				EDITOR_POINTER(CLASS_NAME)->AlterTable(DBSOURCE); EDITOR_POINTER(CLASS_NAME)->CreateTable(DBSOURCE);	EDITOR_POINTER(CLASS_NAME)->InitData();	EDITOR_POINTER(CLASS_NAME)->GetMaxIndex();	

#define DECLARE_TEMP_VECTOR_CLASS(CLASS_NAME)	std::vector<std::shared_ptr<CSQLData>> TEMP_VECTOR_CLASS(CLASS_NAME);


#define SAVEDATA_FOR_CLASS(CLASS_NAME)	EDITOR_POINTER(CLASS_NAME)->SaveData();


class CTableManage
{
public:
	CTableManage(void);
	~CTableManage(void);
private:
	static sqlite3 *m_dbSource;
public:
	static CTableManage *GetInstance();
	static sqlite3* GetDB();

	bool InitDatabase(TYC *pszPath);
	bool CloseDatabase();
	void LoadDatabase();
	void SaveModified();
	int BackupDb(sqlite3 *pDb, const TYC *zFilename, void(*xProgress)(int, int) = 0);

	// DECLARE_VECTOR_FOR_CLASS (at least table is parent role) for child table, init temp vector on void CTableManage::LoadDatabase()
	DECLARE_VECTOR_FOR_CLASS(StationInformation);
	DECLARE_VECTOR_FOR_CLASS(StationDistance);

	DECLARE_VECTOR_FOR_CLASS(TrainNumber);
	DECLARE_VECTOR_FOR_CLASS(StopPtnHeader);
	
	DECLARE_VECTOR_FOR_CLASS(PIDContents);
	DECLARE_VECTOR_FOR_CLASS(AudioStationName);
	DECLARE_VECTOR_FOR_CLASS(AudioTotal);
	DECLARE_VECTOR_FOR_CLASS(VideoDeviceGroup);
	DECLARE_VECTOR_FOR_CLASS(EditorTagTable);
	
	DECLARE_VECTOR_FOR_CLASS(FontPool);
	DECLARE_VECTOR_FOR_CLASS(AudioFilePool);
	DECLARE_VECTOR_FOR_CLASS(VideoFilePool);
	DECLARE_VECTOR_FOR_CLASS(StationImagePool);
	DECLARE_VECTOR_FOR_CLASS(BitmapImagePool);
	DECLARE_VECTOR_FOR_CLASS(ImageIndexList);
	
	DECLARE_VECTOR_FOR_CLASS(DisplayItemPool);
	DECLARE_VECTOR_FOR_CLASS(LineMapPool);
	
	DECLARE_VECTOR_FOR_CLASS(EDDIndicator);
	DECLARE_VECTOR_FOR_CLASS(ETNDIndicator);
	DECLARE_VECTOR_FOR_CLASS(EDDIndex);
	// !DECLARE_VECTOR_FOR_CLASS

	// DECLARE_EDITOR_POINTER_FOR_CLASS (all tables)
	DECLARE_EDITOR_POINTER_FOR_CLASS(StationInformation);
	DECLARE_EDITOR_POINTER_FOR_CLASS(StationDistance);

	DECLARE_EDITOR_POINTER_FOR_CLASS(TrainNumber);
	DECLARE_EDITOR_POINTER_FOR_CLASS(StopPtnHeader);
	DECLARE_EDITOR_POINTER_FOR_CLASS(StopPtnRoutes);
	DECLARE_EDITOR_POINTER_FOR_CLASS(EventLists);

	DECLARE_EDITOR_POINTER_FOR_CLASS(PIDContents);
	DECLARE_EDITOR_POINTER_FOR_CLASS(PIDIndexList);
	DECLARE_EDITOR_POINTER_FOR_CLASS(AudioStationName);
	DECLARE_EDITOR_POINTER_FOR_CLASS(AudioTotal);
	DECLARE_EDITOR_POINTER_FOR_CLASS(VideoDeviceGroup);
	DECLARE_EDITOR_POINTER_FOR_CLASS(VideoPlayList);
	DECLARE_EDITOR_POINTER_FOR_CLASS(EditorTagTable);

	DECLARE_EDITOR_POINTER_FOR_CLASS(FontPool);
	DECLARE_EDITOR_POINTER_FOR_CLASS(AudioFilePool);
	DECLARE_EDITOR_POINTER_FOR_CLASS(VideoFilePool);
	DECLARE_EDITOR_POINTER_FOR_CLASS(StationImagePool);
	DECLARE_EDITOR_POINTER_FOR_CLASS(BitmapImagePool);
	DECLARE_EDITOR_POINTER_FOR_CLASS(ImageIndexList);
	DECLARE_EDITOR_POINTER_FOR_CLASS(ImageIndex);

	DECLARE_EDITOR_POINTER_FOR_CLASS(DisplayItemPool);
	DECLARE_EDITOR_POINTER_FOR_CLASS(DisplayItem);
	DECLARE_EDITOR_POINTER_FOR_CLASS(DisplayProp);
	DECLARE_EDITOR_POINTER_FOR_CLASS(DisplayMetaItem);
	DECLARE_EDITOR_POINTER_FOR_CLASS(DisplayMetaItemProp);

	DECLARE_EDITOR_POINTER_FOR_CLASS(LineMapLink);
	DECLARE_EDITOR_POINTER_FOR_CLASS(LineMapNode);
	DECLARE_EDITOR_POINTER_FOR_CLASS(LineMapArrowTexture);
	DECLARE_EDITOR_POINTER_FOR_CLASS(LineMapPool);
	DECLARE_EDITOR_POINTER_FOR_CLASS(LineMapDisplayItem);

	DECLARE_EDITOR_POINTER_FOR_CLASS(EDDIndicator)
	DECLARE_EDITOR_POINTER_FOR_CLASS(ETNDIndicator)
	DECLARE_EDITOR_POINTER_FOR_CLASS(EDDIndex)
	DECLARE_EDITOR_POINTER_FOR_CLASS(EDDIndexList)
	// !DECLARE_EDITOR_POINTER_FOR_CLASS
};


#endif
