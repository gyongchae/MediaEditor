#ifndef SQLDATA
#define SQLDATA
#include <vector>
#include <memory>
#include <cstring>
#include <iostream>
#include <sqlite3.h>
#include <functional>
#include <cstdio>

#ifdef UNDER_CE
#include <loki/smartptr.h>
	#define SHARED_PTRC(ARG) Loki::SmartPtr<ARG,Loki::RefCounted,Loki::AllowConversion,Loki::AssertCheck,Loki::DefaultSPStorage>
	#define SHARED_PTRM(ARG) Loki::SmartPtr<ARG,Loki::RefCounted,Loki::AllowConversion,Loki::AssertCheck,Loki::HeapStorage>
	#define MALLOCFORSP(TYPEOFIT,SIZEOFIT) (TYPEOFIT*)malloc(SIZEOFIT)
	#define GET_POINTEROF(A) A
	#define GET_PTFROMSP(A) (&(*A))
	#define GET_PTFROMIT(A) (&(**A))
#else if
	#if defined(_MSC_VER)
		#if (_MSC_VER==1500)
			#define	SHARED_PTRC(ARG) std::tr1::shared_ptr<ARG>
			#define SHARED_PTRM(ARG) SHARED_PTRC(ARG)
		#else 
			#define	SHARED_PTRC(ARG) std::shared_ptr<ARG>
			#define SHARED_PTRM(ARG) SHARED_PTRC(ARG)
		#endif
	#else
		#define	SHARED_PTRC(ARG) std::shared_ptr<ARG>
		#define SHARED_PTRM(ARG) SHARED_PTRC(ARG)
	#endif
	#define GET_POINTEROF(A) A.get()
	#define GET_PTFROMSP(A) A.get()
	#define GET_PTFROMIT(A) A->get()
	#define MALLOCFORSP(TYPEOFIT,SIZEOFIT) (TYPEOFIT*)malloc(SIZEOFIT),free
#endif

#ifdef PAC_EDITOR
	//#pragma message("PAC_EDITOR")
	#include <windows.h>
	#define SQLITE3_COLUMN_TEXT sqlite3_column_text16
	#define SQLITE3_PREPARE		sqlite3_prepare16_v2
	#define SQLITE3_OPEN		sqlite3_open16
	#define SQLITE3_ERRMSG		sqlite3_errmsg16
	#define STRCAT				wcscat
	#define SPRINTF				swprintf
	#define STRCPY              wcscpy
	#define STRLEN              wcslen
	#define STRCMP              wcscmp
	#define STRNCPY             wcsncpy
	#define TYC wchar_t
	#define MAKE_T(A)			L##A
	#define TAIL_CASTING		(const void**)
	#define TSTRING				std::wstring
#else
	#ifndef UNDER_CE
		#define SQLITE3_COLUMN_TEXT sqlite3_column_text
		#define SQLITE3_PREPARE		sqlite3_prepare_v2
		#define SQLITE3_OPEN		sqlite3_open
		#define SQLITE3_ERRMSG		sqlite3_errmsg
		#define STRCAT				strcat
		#if defined(_MSC_VER)
			#if (_MSC_VER==1500)
				#define SPRINTF				sprintf_s
			#else 
				#define SPRINTF				snprintf
			#endif
		#else
			#define SPRINTF				snprintf
		#endif
		#define STRCPY              strcpy
		#define STRLEN              strlen
		#define STRCMP              strcmp
		#define STRNCPY             strncpy
		#define TYC char
		#define MAKE_T
		#define TAIL_CASTING		(const char**)
		#define TSTRING				std::string
    #else
		#define SQLITE3_COLUMN_TEXT sqlite3_column_text16
		#define SQLITE3_PREPARE		sqlite3_prepare16
		#define SQLITE3_OPEN		sqlite3_open16
		#define SQLITE3_ERRMSG		sqlite3_errmsg16
		#define STRCAT				wcscat
		#define SPRINTF				swprintf_s
		#define STRCPY              wcscpy
		#define STRLEN              wcslen
		#define STRCMP              wcscmp
		#define STRNCPY             wcsncpy
		#define TYC wchar_t
		#define MAKE_T(A)			L##A
		#define TAIL_CASTING		(const void**)
		#define TSTRING				std::wstring
	#endif
#endif

#define dim(x) (sizeof(x)/sizeof(x[0]))

#define MAKEUINT(a, b) ((unsigned int)(((unsigned short)(a)) | ((unsigned int)((unsigned short)(b))) << 16))
#define MAKEUSHORT(low, high) ((unsigned short)((((unsigned short)(high)) << 8) | ((unsigned char)(low))))

class CSQLData;
class CEditSQLData;
class CTreeInfo;

enum EDITSTATE
{
	EDIT_NOT_MODIFIED=0,
	EDIT_UPDATED,
	EDIT_INSERTED,
	EDIT_DELETED,
	EDIT_TO_BE_IGNORED,
};

enum TYPEDEFINE
{
	TYPE_INTEGER,
	TYPE_TEXT,
	TYPE_DOUBLE,
	TYPE_FLOAT,
	TYPE_DATALENGTH,		//데이터 길이
	TYPE_DATA,
};

typedef struct _TYPESETTINGS
{
	TYPEDEFINE nTYPE;
	TYC szFIELDNAME[256];
	int nLENGTH;
	void *POINTER;
	bool bPRIMARYKEY;
	bool bORDER;
	bool bPARENTINDEX;
	TYC szCOLUMNNAME[128];
	int nColWidth;
}TYPESETTINGS,*LPTYPESETTINGS;


void MakeRelationShip2(std::vector<SHARED_PTRC(CSQLData)> *pParent, int nChildIndex, std::vector<SHARED_PTRC(CSQLData)> *pChild);


#define DECLARE_EDITOR_CLASS(CLASS_NAME) class CLASS_NAME##Editor : public CEditSQLData { public :	TYC* GetTableName(){return CLASS_NAME::szTableName;}	TYPESETTINGS* GetTypeSettingsTable(){return CLASS_NAME::m_tSettings;}\
	sqlite3 *GetDatabase(){return CLASS_NAME::m_dbState;}	void SetMaxIndex(int nMaxIndex){CLASS_NAME::m_nTableMaxIdx=nMaxIndex;}	void SetDatabase(sqlite3 *pDB){CLASS_NAME::m_dbState=pDB;}	\
	CSQLData *FeedInserted(){return new CLASS_NAME(EDIT_INSERTED);}	CSQLData *FeedNotModified(){return new CLASS_NAME(EDIT_NOT_MODIFIED);} int GetTypeSettingsCount() {	return sizeof(CLASS_NAME::m_tSettings)/sizeof(CLASS_NAME::m_tSettings[0]);}};

#define COMMON_VAL_FOR_SQLDATA	static int m_nTableMaxIdx;static bool m_bBLOBExist;static sqlite3 *m_dbState;static TYC szTableName[128];static int m_nParentIndexCol;static int m_nOrderCol;static int m_nIndexCol;

#define DECLARE_TYPESETTINGS(SETTINGS_COUNT);	static TYPESETTINGS m_tSettings[SETTINGS_COUNT];

#define DECLARE_COMMON_FUNCTIONS	bool GetTypeSettingParam(TYPESETTINGS **pSettings,int *pParam){if(pSettings&&pParam){*pSettings=m_tSettings;*pParam=sizeof(m_tSettings)/sizeof(m_tSettings[0]);return true;}return false;}\
	sqlite3* GetDatabase(){return m_dbState;}	bool SetDatabase(sqlite3 *pDB){if(pDB){m_dbState=pDB;return true;}return false;}\
	bool GetBLOBExist(){return m_bBLOBExist;}	TYC* GetTableName(){return szTableName;}	int GetInsertIndex(){return ++m_nTableMaxIdx;}\
	int GetParentIndexCol(){return m_nParentIndexCol;}	int GetOrderCol(){return m_nOrderCol;}	int GetIndexCol(){return m_nIndexCol;}\
    void SetTableName(TYC *pTable){STRCPY(szTableName,pTable);};

#define DECLARE_ADDITIONAL(CLASS_NAME) \
void SetAdditionalMember(CSQLData *pData)\
{\
}\

#define DECLARE_CREATE_NEW(CLASS_NAME)  \
CSQLData* CreateNew()\
{\
	CLASS_NAME *pClone=new CLASS_NAME(EDIT_INSERTED);\
	pClone->SetIndex(pClone->GetInsertIndex());\
	return pClone;\
}\


#define BEGIN_CLASS_FROM_SQLDATA(CLASS_NAME,INITIALIZER,DESTRUCTOR)	\
	class CLASS_NAME :public CSQLData \
{\
public: CLASS_NAME(int nState):CSQLData(nState) {INITIALIZER;} \
DECLARE_CREATE_NEW(CLASS_NAME) \
virtual ~CLASS_NAME(void) {DESTRUCTOR}

#define BEGIN_CLASS_FROM_SQLDATA_WITH_CHILDS(CLASS_NAME,INITIALIZER,DESTRUCTOR,CHILDCOUNT)	class CLASS_NAME :public CSQLData { public: CLASS_NAME(int nState):CSQLData(nState,CHILDCOUNT){Initialize();INITIALIZER} DECLARE_CREATE_NEW(CLASS_NAME) virtual ~CLASS_NAME(void){DESTRUCTOR}


#define END_CLASS_FROM_SQLDATA	};

#define BEGIN_MAPPING_MEMBERS	void MappingMembers(){

#define END_MAPPING_MEMBERS		}

#define OVERRIDE_DUMMY_EDITOR_FUNC		CEditSQLData* GetEditor(int nRow){return nullptr;};

typedef struct _CHILDITEM
{
	SHARED_PTRC(CTreeInfo) m_pTreeInfo;
	std::vector<SHARED_PTRC(CSQLData)> vSQLData;
	std::vector<SHARED_PTRC(CSQLData)> vSQLDataDelItems;
}CHILDITEM,*LPCHILDITEM;



class CTreeInfo
{
public:
	CTreeInfo();
	~CTreeInfo();

	virtual void SetParent(void *pParent)=0;
	virtual CTreeInfo* GetParent()=0;
	virtual int GetChildCount()=0;
	virtual int GetType()=0;
	virtual CTreeInfo* GetChild(int nRow)=0;
	virtual CEditSQLData* GetEditor()=0;
	virtual void SetEditor(CEditSQLData *pSQLData)=0;
	virtual bool Insert(int nRow)=0;
	virtual bool Remove(int nRow)=0;
	virtual int GetRow()=0;
	virtual void GetNick(TYC *pChar,int nCount)=0;
	virtual void* GetPointer()=0;
};


class CTreeItem : public CTreeInfo
{
public:
	CTreeItem(void* pPointer);
	~CTreeItem();
	void SetParent(void *pParent);
	CTreeInfo* GetParent();
	int GetChildCount();
	CTreeInfo* GetChild(int nRow);
	int GetType();
	int GetRow();

	CEditSQLData* GetEditor()
	{
		return GET_POINTEROF(m_pSQLDataEditor);
	}
	void SetEditor(CEditSQLData *pSQLData)
	{
		if(pSQLData)
			m_pSQLDataEditor=SHARED_PTRC(CEditSQLData)(pSQLData);
	}


	bool Insert(int nRow);
	bool Remove(int nRow);

	SHARED_PTRC(CSQLData) Insert();
	int FindIndex(int nIndex);

	void GetNick(TYC *pChar,int nCount);


	void* GetPointer()
	{
		return (void*)m_pItem;
	}

private:
	SHARED_PTRC(CEditSQLData) m_pSQLDataEditor;
	CSQLData *m_pSQLDataParent;
	LPCHILDITEM m_pItem;
};



class CTreeSQLData : public CTreeInfo
{
public:
	CTreeSQLData(void* pPointer);
	~CTreeSQLData();
	void SetParent(void *pParent);
	CTreeInfo* GetParent();
	int GetChildCount();
	CTreeInfo* GetChild(int nRow);
	int GetType();

	CEditSQLData* GetEditor()
	{
		return nullptr;
	}
	void SetEditor(CEditSQLData *pSQLData)
	{
		
	}


	int GetRow();



	
	bool Insert(int nRow);
	bool Remove(int nRow);

	void GetNick(TYC *pChar,int nCount);


	void* GetPointer()
	{
		return (void*)m_pItem;
	}




private:
	//SHARED_PTRC(CEditSQLData> m_pSQLDataEditor;
	LPCHILDITEM m_pItemParent;
	CSQLData *m_pItem;
};

class CSQLData
{
public:
	CSQLData(int nState,int nChildCount=0);
	virtual ~CSQLData(void);

private:
	int m_nRecordState;	//기록상태
	int m_nChildCount;
public:
	int m_nParentIndex;
	int m_nTableIndex;
public:
	void SetRecordState(int nStatus);
	int GetRecordState();
	void SetIndex(int nIndex);
	int GetIndex();
	
	static void GetSelectQuery(TYC *lpStr,int nCount,TYC *pszTableName,TYPESETTINGS *pSettings,int nMember);
	static void GetCreateQuery(TYC *lpStr,int nCount,TYC *pszTableName,TYPESETTINGS *pSettings,int nMember);
	static void GetMaxIndexQuery		(TYC *lpStr, int nCount, TYC *pszTableName, TYPESETTINGS *pSettings, int nMember);
	static void GetAlterTableAddColumn	(TYC *lpStr, int nCount, TYC *pszTableName, TYPESETTINGS *pSettings, int nMember);
	void GetInsertQuery(TYC *lpStr,int nCount,TYC *pszTableName,TYPESETTINGS *pSettings,int nMember);
	void GetUpdateQuery(TYC *lpStr,int nCount,TYC *pszTableName,TYPESETTINGS *pSettings,int nMember);
	void GetDeleteQuery(TYC *lpStr,int nCount,TYC *pszTableName,TYPESETTINGS *pSettings,int nMember);
	bool InsertExec();
	bool DeleteExec();
	bool UpdateExec();
	bool CommitData(int nOrder);
	bool SetData(int nField,void *pValue,int nSize=0);
	int GetData(int nField,void *pValue);
	int GetChildCount();
	void Initialize();

	virtual void MappingMembers()=0;
	virtual bool GetTypeSettingParam(TYPESETTINGS **pSettings,int *pParam)=0;
	virtual sqlite3* GetDatabase()=0;
	virtual bool SetDatabase(sqlite3 *pDB)=0;
	virtual bool GetBLOBExist()=0;
	virtual TYC *GetTableName()=0;
	virtual void SetTableName(TYC *pTable)=0;
	virtual int GetInsertIndex()=0;

	virtual int GetParentIndexCol()=0;
	virtual int GetOrderCol()=0;
	virtual int GetIndexCol()=0;
	virtual CEditSQLData* GetEditor(int nRow)=0;

	CSQLData* Clone();
	virtual void SetAdditionalMembers(CSQLData *pData);
	virtual CSQLData* CreateNew()=0;

	/*void InsertData(int nRow,SHARED_PTRC(CSQLData> pData)
	{
		pData->SetRecordState(EDIT_INSERTED);
		pData.get()->SetIndex(pData.get()->GetInsertIndex());
		m_vSQLData.insert(m_vSQLData.begin()+nRow,1,pData);
	}*/

	void RemoveData(int nIndex,int nRow)
	{
		int nCount=GetChildCount();
		if(nIndex<nCount)
		{
			if(m_vChildItem[nIndex].vSQLData.size()>nRow)
			{
				switch(m_vChildItem[nIndex].vSQLData[nRow]->GetRecordState())
				{
				case EDIT_UPDATED:
					m_vChildItem[nIndex].vSQLData[nRow]->SetRecordState(EDIT_DELETED);
					break;
				case EDIT_NOT_MODIFIED:
					m_vChildItem[nIndex].vSQLData[nRow]->SetRecordState(EDIT_DELETED);
					break;
				default:
					m_vChildItem[nIndex].vSQLData[nRow]->SetRecordState(EDIT_TO_BE_IGNORED);//Inserted 이면
					break;
				}

				int nChildCount=m_vChildItem[nIndex].vSQLData[nRow]->m_vChildItem.size();
				for(int i=0;i<nChildCount;i++)
				{
					while(m_vChildItem[nIndex].vSQLData[nRow]->m_vChildItem[i].vSQLData.size())
					{
						m_vChildItem[nIndex].vSQLData[nRow]->RemoveData(i,0);
					}
				}

				m_vChildItem[nIndex].vSQLDataDelItems.insert(
					m_vChildItem[nIndex].vSQLDataDelItems.end(),
					m_vChildItem[nIndex].vSQLData.begin()+nRow,
					m_vChildItem[nIndex].vSQLData.begin()+nRow+1);
				m_vChildItem[nIndex].vSQLData.erase(m_vChildItem[nIndex].vSQLData.begin()+nRow);	
			}
		}
	}

	sqlite3 *m_dbSource;

	std::vector<CHILDITEM> m_vChildItem;


	SHARED_PTRC(CTreeInfo) m_pTreeInfo;
};


class CEditSQLData
{
public:
	CEditSQLData()
		:m_pvSQLData(nullptr),m_pvSQLDataDelItems(nullptr)
	{
	
	}
	virtual ~CEditSQLData()
	{
	}
	
	int m_nCurIndex;


	void SetCurParentIndex(int nIndex)
	{
		m_nCurIndex=nIndex;
	}
	int GetCurParentIndex()
	{
		return m_nCurIndex;
	}
	void InsertData(int nRow,SHARED_PTRC(CSQLData) &pData)
	{
		
		pData->SetRecordState(EDIT_INSERTED);
		pData->SetIndex(pData->GetInsertIndex());
		if(nRow==-1)
			m_pvSQLData->push_back(pData);
		else
			m_pvSQLData->insert(m_pvSQLData->begin()+nRow,1,pData);
	}

	bool RemoveData(int nRow)
	{
		int nChildCount,nChildCounts;
		if((*m_pvSQLData).size()>nRow)
		{
			switch((*m_pvSQLData)[nRow]->GetRecordState())
			{
			case EDIT_UPDATED:
				(*m_pvSQLData)[nRow]->SetRecordState(EDIT_DELETED);
				nChildCount=(*m_pvSQLData)[nRow]->GetChildCount();
				for(int i=0;i<nChildCount;i++)
				{
					while((*m_pvSQLData)[nRow]->m_vChildItem[i].vSQLData.size())
					{
						(*m_pvSQLData)[nRow]->RemoveData(i,0);
					}
				}
				break;
			case EDIT_NOT_MODIFIED:
				(*m_pvSQLData)[nRow]->SetRecordState(EDIT_DELETED);
				nChildCount=(*m_pvSQLData)[nRow]->GetChildCount();
				for(int i=0;i<nChildCount;i++)
				{
					while((*m_pvSQLData)[nRow]->m_vChildItem[i].vSQLData.size())
					{
						(*m_pvSQLData)[nRow]->RemoveData(i,0);
					}
				}
				break;
			default:
				(*m_pvSQLData)[nRow]->SetRecordState(EDIT_TO_BE_IGNORED);//Inserted 이면
				break;
			}
			(*m_pvSQLDataDelItems).insert((*m_pvSQLDataDelItems).end(),(*m_pvSQLData).begin()+nRow,(*m_pvSQLData).begin()+nRow+1);
			(*m_pvSQLData).erase((*m_pvSQLData).begin()+nRow);
			return true;
		}
		return false;
	}

	bool SaveData()
	{
		std::vector<SHARED_PTRC(CSQLData)>::iterator nit;
		if(m_pvSQLData&&m_pvSQLDataDelItems)
		{
			for(nit=m_pvSQLData->begin();nit!=m_pvSQLData->end();nit++)
			{
				int nOrder=distance(m_pvSQLData->begin(), nit)+1;
				(*nit)->CommitData(nOrder);
				//nit->get()->CommitData(nOrder);
			}
			for(nit=m_pvSQLDataDelItems->begin();nit!=m_pvSQLDataDelItems->end();nit++)
			{
				int nOrder = distance(m_pvSQLDataDelItems->begin(), nit)+1;
				(*nit)->CommitData(nOrder);
				//nit->get()->CommitData(nOrder);
			}
			return true;
		}
		return false;
	}
/////////////////////////////////////////////////////////
	bool sqlite3SetText(sqlite3_stmt *state,int nRow,TYC *lpStr,int nCount)
	{
		TYC *lpStrRet;
		lpStrRet=(TYC *)SQLITE3_COLUMN_TEXT(state,nRow);//Line Name
		if(lpStrRet)
		{
            STRCPY(lpStr,lpStrRet);
			return true;
		}
		else
		{
			memset(lpStr,0,nCount*sizeof(TYC));
		}
		return false;
	}

	bool sqlite3SetBlob(sqlite3_stmt *state,int nRow,unsigned char *lpStr)
	{
		unsigned char *pByte;
		int nBytes=sqlite3_column_bytes(state,nRow);
		if(nBytes)
		{
			memcpy(lpStr,sqlite3_column_blob(state,nRow),nBytes);
			return true;
		}
		return false;
	}

	void sqlite3SetInt(sqlite3_stmt *state,int nRow,int *pInt)
	{
		*pInt=sqlite3_column_int(state,nRow);
	}

	void sqlite3SetByte(sqlite3_stmt *state,int nRow,unsigned char *pByte)
	{
		int nValue=sqlite3_column_int(state,nRow);
		if(nValue)
			(*pByte)=(unsigned char)nValue;
	}

	void sqlite3SetUShort(sqlite3_stmt *state,int nRow,unsigned short *pUShort)
	{
		int nValue=sqlite3_column_int(state,nRow);
		if(nValue)
			(*pUShort)=(unsigned short)nValue;
	}

	void sqlite3SetBool(sqlite3_stmt *state,int nRow,bool *pBool)
	{
		int nRet;
		nRet=sqlite3_column_int(state,nRow);
		(*pBool)=nRet?true:false;
	}


	void sqlite3SetDouble(sqlite3_stmt *state,int nRow,double *pDouble)
	{
		*pDouble=sqlite3_column_double(state,nRow);
	}


	bool queryExec(sqlite3 *pSqlite3,const TYC *lpQuery)
	{
		sqlite3_stmt* state;
		const TYC *tail; 
        int nRetVal=SQLITE3_PREPARE(pSqlite3,lpQuery,STRLEN(lpQuery)*sizeof(TYC),&state, TAIL_CASTING&tail);
		if(SQLITE_OK!=nRetVal)
		{
            //OutputDebugString(lpQuery);
            //OutputDebugString(L"\n");
			return false;
		}
		int nColumns=sqlite3_column_count(state);
		nRetVal=sqlite3_step(state);
		sqlite3_finalize(state);
		if((!nColumns)&&(nRetVal==SQLITE_DONE))
		{
			return true;	
		}
		return false;
	}

	virtual void Insert(int nRow)
	{
		SHARED_PTRC(CSQLData) pData=SHARED_PTRC(CSQLData)(FeedInserted());
		InsertData(nRow,pData);	// 
	}

	virtual void Remove(int nRow)
	{
		RemoveData(nRow);
	}

	virtual bool CreateTable(sqlite3 *pDB)
	{
		if(pDB)
		{
			SetDatabase(pDB);
		}
		TYC szSelectQuery[4096];
		CSQLData::GetCreateQuery(szSelectQuery,dim(szSelectQuery),GetTableName(),GetTypeSettingsTable(),GetTypeSettingsCount());
		return queryExec(GetDatabase(),szSelectQuery);
	}

	virtual void AlterTable(sqlite3 *pDB)
	{
		if (pDB)
		{
			SetDatabase(pDB);
		}
		TYC szAlterQuery[1024];
		for (int i = 0; i < GetTypeSettingsCount(); i++)
		{
			CSQLData::GetAlterTableAddColumn(szAlterQuery, dim(szAlterQuery), GetTableName(), GetTypeSettingsTable(), i);
			queryExec(GetDatabase(), szAlterQuery);
		}
	}

	virtual bool InitData()
	{
		int nCount;
		TYC *lpStrRet;
		const TYC *tail;
		sqlite3_stmt* state;
		LPTYPESETTINGS pSettings;
		TYC szSelectQuery[4096];
		CSQLData::GetSelectQuery(szSelectQuery, dim(szSelectQuery),GetTableName(),GetTypeSettingsTable(),GetTypeSettingsCount());
        int nRetVal=SQLITE3_PREPARE(GetDatabase(),szSelectQuery,STRLEN(szSelectQuery)*sizeof(TYC),&state,TAIL_CASTING&tail);
		if(SQLITE_OK!=nRetVal)
		{
            std::cout<<szSelectQuery<<std::endl;
			return false;
		}
		nRetVal=sqlite3_step(state);
		while(nRetVal==SQLITE_ROW)
		{
			nRetVal=GetSelectData(state,FeedNotModified());
		}
		sqlite3_finalize(state);
		return true;
	}

	virtual bool GetMaxIndex()
	{
		int nCount;
		TYC *lpStrRet;
		const TYC *tail;
		sqlite3_stmt* state;
		LPTYPESETTINGS pSettings;
		TYC szSelectQuery[4096];
		CSQLData::GetMaxIndexQuery(szSelectQuery,dim(szSelectQuery),GetTableName(),GetTypeSettingsTable(),GetTypeSettingsCount());
        int nRetVal=SQLITE3_PREPARE(GetDatabase(),szSelectQuery,STRLEN(szSelectQuery)*sizeof(TYC),&state,TAIL_CASTING&tail);
		if(SQLITE_OK!=nRetVal)
		{
			return false;
		}
		nRetVal=sqlite3_step(state);
		while(nRetVal==SQLITE_ROW)
		{
			int nMaxIndex;
			sqlite3SetInt(state,0,&nMaxIndex);
			SetMaxIndex(nMaxIndex);
			nRetVal=sqlite3_step(state);
		}
		sqlite3_finalize(state);
		return true;
	}


public:
	virtual TYC *GetTableName()=0;
	virtual CSQLData *FeedInserted()=0;
	virtual CSQLData *FeedNotModified()=0;
protected:
	virtual TYPESETTINGS* GetTypeSettingsTable()=0;
	virtual int GetTypeSettingsCount()=0;
	virtual sqlite3 *GetDatabase()=0;
	virtual void SetMaxIndex(int nMaxIndex)=0;
	virtual void SetDatabase(sqlite3 *pDB)=0;


public:
	void SetVectors(std::vector<SHARED_PTRC(CSQLData)> *pSQL,std::vector<SHARED_PTRC(CSQLData)> *pSQLDel)
	{
		if(pSQL)
			m_pvSQLData=pSQL;
		if(pSQLDel)
			m_pvSQLDataDelItems=pSQLDel;
	}

	int GetSelectData(sqlite3_stmt* state,CSQLData *pData)
	{
		if(!m_pvSQLData)
			return SQLITE_ERROR;

		int nCount;
		LPTYPESETTINGS pSettings;
		SHARED_PTRC(CSQLData) pStn=SHARED_PTRC(CSQLData)(pData);
		pStn->GetTypeSettingParam(&pSettings,&nCount);
		pStn->MappingMembers();
		for(int nField=0;nField<nCount;nField++)
		{
			switch(pSettings[nField].nTYPE)
			{
			case TYPE_INTEGER:
				sqlite3SetInt(state,nField,(int*)pSettings[nField].POINTER);
				break;
			case TYPE_TEXT:
				sqlite3SetText(state,nField,(TYC *)pSettings[nField].POINTER,pSettings[nField].nLENGTH);
				break;
			case TYPE_FLOAT:
				{
					double dValue;
					sqlite3SetDouble(state, nField, (double*)&dValue);
					(*(float*)(pSettings[nField].POINTER)) = (float)dValue;	
				}
				break;
			case TYPE_DOUBLE:
				sqlite3SetDouble(state,nField,(double*)pSettings[nField].POINTER);
				break;
			case TYPE_DATALENGTH:
				{
					sqlite3SetInt(state,nField,(int*)pSettings[nField].POINTER);
					int nSize=(*((int*)pSettings[nField].POINTER));
					if(nSize>0)
					{
						SHARED_PTRM(unsigned char) *pByte=(SHARED_PTRM(unsigned char)*)pSettings[nField+1].POINTER;		//크기변경 -> 재할당
						*pByte= SHARED_PTRM(unsigned char)(MALLOCFORSP(unsigned char,nSize));
					}
				}
				break;
			case TYPE_DATA:
				{
					SHARED_PTRM(unsigned char) *pByte=(SHARED_PTRM(unsigned char)*)pSettings[nField].POINTER;
					if(GET_POINTEROF((*pByte)))
					{
						sqlite3SetBlob(state,nField,(unsigned char*)GET_POINTEROF((*pByte)));
					}
				}
				break;
			}
		}
		m_pvSQLData->push_back(pStn);
		return sqlite3_step(state);
	}



	std::vector<SHARED_PTRC(CSQLData)> *m_pvSQLData;
	std::vector<SHARED_PTRC(CSQLData)> *m_pvSQLDataDelItems;
};



struct findSQLData : public std::unary_function<SHARED_PTRC(CSQLData),bool>
{
	findSQLData(int nIndex)
		:m_nIndex(nIndex)
	{

	}
	bool operator ()(SHARED_PTRC(CSQLData) &pSI)
	{
		return (pSI->GetIndex()==m_nIndex);
	}
private:
	int m_nIndex;
};


#endif
