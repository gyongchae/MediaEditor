#pragma once

#include "SQLData.h"
#include "DefineDisplayTables.h"
#include "DefineFilePoolTables.h"
#include "DefineLEDTables.h"
#include "DefineLinemapTables.h"
#include "DefineNormalTables.h"

#define DECLARE_STATIC_VARIABLES(CLASS_NAME,BLOBEXIST,TABLENAME,PARENT_INDEX_COL,ORDER_COL,INDEX_COL)\
	sqlite3* CLASS_NAME::m_dbState=nullptr;\
	bool CLASS_NAME::m_bBLOBExist=BLOBEXIST;\
    TYC CLASS_NAME::szTableName[128]={MAKE_T(#TABLENAME)};\
	int CLASS_NAME::m_nTableMaxIdx=0;\
	int CLASS_NAME::m_nParentIndexCol=PARENT_INDEX_COL;\
	int CLASS_NAME::m_nOrderCol=ORDER_COL;\
	int CLASS_NAME::m_nIndexCol=INDEX_COL;

#define DECLARE_STATIC_TYPESETTINGS(CLASS_NAME,COUNT) TYPESETTINGS CLASS_NAME::m_tSettings[COUNT]
