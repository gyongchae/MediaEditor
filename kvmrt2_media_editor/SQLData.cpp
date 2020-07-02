
#include "SQLData.h"
#include <algorithm>
#include <qdebug.h>

#define	MIN(X,Y) ((X)<(Y)?(X):(Y))
#define	MAX(X,Y) ((X)>(Y)?(X):(Y))

#define SQL_CREATE		MAKE_T("CREATE TABLE ")
#define SQL_SELECT		MAKE_T("SELECT ")
#define SQL_MAX			MAKE_T("MAX(")
#define SQL_MAXEND		MAKE_T(") FROM ")
#define SQL_INSERT		MAKE_T("INSERT INTO ")
#define SQL_UPDATE		MAKE_T("UPDATE ")
#define SQL_DELETE		MAKE_T("DELETE FROM ")
#define SQL_ALTER		MAKE_T("ALTER TABLE ")

CSQLData::CSQLData(int nState, int nChildCount)
	:m_nRecordState(nState), m_nChildCount(nChildCount)
{
	m_nTableIndex = 0;
	if (m_nChildCount)
		m_vChildItem.reserve(nChildCount);
	m_pTreeInfo = SHARED_PTRC(CTreeInfo)(new CTreeSQLData(this));

}

int CSQLData::m_nETNDWidth=32;
int CSQLData::m_nETNDHeight=64;
int CSQLData::m_nEDDWidth= 256;
int CSQLData::m_nEDDHeight=64;

CSQLData::~CSQLData(void)
{

}


void CSQLData::Initialize()
{
	for (int i = 0; i<m_nChildCount; i++)
	{
		CHILDITEM item;
		CEditSQLData *pEdit = this->GetEditor(i);
		m_vChildItem.push_back(item);
		m_vChildItem.at(i).m_pTreeInfo = SHARED_PTRC(CTreeInfo)(new CTreeItem(&m_vChildItem.at(i)));
		m_vChildItem.at(i).m_pTreeInfo->SetParent((void*)this);
		if (pEdit)
		{
			pEdit->SetVectors(&m_vChildItem.at(i).vSQLData, &m_vChildItem.at(i).vSQLDataDelItems);
			m_vChildItem.at(i).m_pTreeInfo->SetEditor(pEdit);
		}
	}
}

void CSQLData::SetLEDIndicatorParam(int nEDDWidth,int nEDDHeight,int nETNDWidth,int nETNDHeight)
{
	m_nETNDWidth = nETNDWidth;
	m_nETNDHeight = nETNDHeight;
	m_nEDDWidth = nEDDWidth;
	m_nEDDHeight = nEDDHeight;
	qDebug() << Q_FUNC_INFO << "EDD  size(w,h):" << m_nEDDWidth << m_nEDDHeight;
	qDebug() << Q_FUNC_INFO << "ETND size(w,h):" << m_nETNDWidth << m_nETNDHeight;
}




void CSQLData::SetRecordState(int nStatus)
{
	m_nRecordState = nStatus;
}

int CSQLData::GetRecordState()
{
	return m_nRecordState;
}

void CSQLData::SetIndex(int nIndex)
{
	m_nTableIndex = nIndex;
}

int CSQLData::GetIndex()
{
	return m_nTableIndex;
}





void CSQLData::GetSelectQuery(TYC *lpStr, int nCount, TYC *pszTableName, TYPESETTINGS *pSettings, int nMember)
{
	int nOrder = -1;
	memset((void*)lpStr, 0, nCount);
	STRCAT(lpStr, SQL_SELECT);
	for (int i = 0; i<nMember; i++)
	{
		switch (pSettings[i].nTYPE)
		{
		case TYPE_INTEGER:
			STRCAT(lpStr, pSettings[i].szFIELDNAME);
			break;
		case TYPE_TEXT:
			STRCAT(lpStr, pSettings[i].szFIELDNAME);
			break;
		case TYPE_FLOAT:
		case TYPE_DOUBLE:
			STRCAT(lpStr, pSettings[i].szFIELDNAME);
			break;
		case TYPE_DATALENGTH:
			STRCAT(lpStr, pSettings[i].szFIELDNAME);
			STRCAT(lpStr, MAKE_T(",")); i++;
		case TYPE_DATA:
			STRCAT(lpStr, pSettings[i].szFIELDNAME);
			break;
		}
		if (pSettings[i].bORDER)
		{
			nOrder = i;
		}

		if (i == (nMember - 1))
		{
			STRCAT(lpStr, MAKE_T(" FROM "));
			STRCAT(lpStr, pszTableName);
		}
		else
		{
			STRCAT(lpStr, MAKE_T(","));
		}
	}
	if (nOrder != -1)
	{
		STRCAT(lpStr, MAKE_T(" ORDER BY "));
		STRCAT(lpStr, pSettings[nOrder].szFIELDNAME);
	}
}


void CSQLData::SetAdditionalMembers(CSQLData *pData)
{

}

void CSQLData::GetInsertQuery(TYC *lpStr, int nCount, TYC *pszTableName, TYPESETTINGS *pSettings, int nMember)
{
	memset((void*)lpStr, 0, nCount);
	STRCAT(lpStr, SQL_INSERT);
	STRCAT(lpStr, pszTableName);
	STRCAT(lpStr, MAKE_T(" "));
	for (int i = 0; i<nMember; i++)
	{
		if (!i)
		{
			STRCAT(lpStr, MAKE_T("("));
		}
		switch (pSettings[i].nTYPE)
		{
		case TYPE_INTEGER:
			STRCAT(lpStr, pSettings[i].szFIELDNAME);
			break;
		case TYPE_TEXT:
			printf("\n\nstr leng:%d\n\n", pSettings[i].nLENGTH);
			STRCAT(lpStr, pSettings[i].szFIELDNAME);
			break;
		case TYPE_FLOAT:
		case TYPE_DOUBLE:
			STRCAT(lpStr, pSettings[i].szFIELDNAME);
			break;
		case TYPE_DATALENGTH:
			STRCAT(lpStr, pSettings[i].szFIELDNAME);
			STRCAT(lpStr, MAKE_T(",")); i++;
		case TYPE_DATA:
			STRCAT(lpStr, pSettings[i].szFIELDNAME);
			break;
		}
		if (i == (nMember - 1))
		{
			STRCAT(lpStr, MAKE_T(")"));
		}
		else
		{
			STRCAT(lpStr, MAKE_T(","));
		}
	}

	STRCAT(lpStr, MAKE_T(" VALUES "));

	TYC szTemp[256];




	for (int i = 0; i<nMember; i++)
	{
		memset(szTemp, 0, sizeof(szTemp));
		if (!i)
		{
			STRCAT(lpStr, MAKE_T("("));
		}
		switch (pSettings[i].nTYPE)
		{
		case TYPE_INTEGER:
			SPRINTF(szTemp, 256, MAKE_T("%d"), *((int*)pSettings[i].POINTER));
			STRCAT(lpStr, szTemp);
			break;
		case TYPE_TEXT:
			SPRINTF(szTemp, 256, MAKE_T(" '%s'"), (TYC *)pSettings[i].POINTER);
			STRCAT(lpStr, szTemp);
			break;
		case TYPE_FLOAT:
			SPRINTF(szTemp, 256, MAKE_T(" %f"), *((float*)pSettings[i].POINTER));
			STRCAT(lpStr, szTemp);
			break;
		case TYPE_DOUBLE:
			SPRINTF(szTemp, 256, MAKE_T(" %lf"), *((double*)pSettings[i].POINTER));
			STRCAT(lpStr, szTemp);
			break;
		case TYPE_DATALENGTH:
			SPRINTF(szTemp, 256, MAKE_T(" %d"), *((int*)pSettings[i].POINTER));
			STRCAT(lpStr, szTemp);
			break;
		case TYPE_DATA:
			SPRINTF(szTemp, 256, MAKE_T(" :%s"), pSettings[i].szFIELDNAME);
			STRCAT(lpStr, szTemp);
			break;
		}
		if (i == (nMember - 1))
		{
			STRCAT(lpStr, MAKE_T(")"));
		}
		else
		{
			STRCAT(lpStr, MAKE_T(","));
		}
	}
}

int CSQLData::GetChildCount()
{
	return m_nChildCount;
}

void CSQLData::GetUpdateQuery(TYC *lpStr, int nCount, TYC *pszTableName, TYPESETTINGS *pSettings, int nMember)
{
	TYC szTemp[256];
	memset((void*)lpStr, 0, nCount);
	STRCAT(lpStr, SQL_UPDATE);
	STRCAT(lpStr, pszTableName);
	STRCAT(lpStr, MAKE_T(" SET "));
	for (int i = 0; i<nMember; i++)
	{
		memset(szTemp, 0, sizeof(szTemp));
		if (!i)
		{
			//STRCAT(lpStr,MAKE_T("(");
		}
		switch (pSettings[i].nTYPE)
		{
		case TYPE_INTEGER:
			STRCAT(lpStr, pSettings[i].szFIELDNAME);
			SPRINTF(szTemp, 256, MAKE_T("=%d"), *((int*)pSettings[i].POINTER));
			STRCAT(lpStr, szTemp);
			break;
		case TYPE_TEXT:
			STRCAT(lpStr, pSettings[i].szFIELDNAME);
			SPRINTF(szTemp, 256, MAKE_T("='%s'"), (TYC *)pSettings[i].POINTER);
			STRCAT(lpStr, szTemp);
			break;
		case TYPE_FLOAT:
			STRCAT(lpStr, pSettings[i].szFIELDNAME);
			SPRINTF(szTemp, 256, MAKE_T("=%f"), *((float*)pSettings[i].POINTER));
			STRCAT(lpStr, szTemp);
			break;
		case TYPE_DOUBLE:
			STRCAT(lpStr, pSettings[i].szFIELDNAME);
			SPRINTF(szTemp, 256, MAKE_T("=%lf"), *((double*)pSettings[i].POINTER));
			STRCAT(lpStr, szTemp);
			break;
		case TYPE_DATALENGTH:
			STRCAT(lpStr, pSettings[i].szFIELDNAME);
			SPRINTF(szTemp, 256, MAKE_T("=%d"), *((int*)pSettings[i].POINTER));
			STRCAT(lpStr, szTemp);
			STRCAT(lpStr, MAKE_T(",")); i++;
		case TYPE_DATA:
			STRCAT(lpStr, pSettings[i].szFIELDNAME);
			SPRINTF(szTemp, 256, MAKE_T("=:%s"), pSettings[i].szFIELDNAME);
			STRCAT(lpStr, szTemp);
			break;
		}
		if (i == (nMember - 1))
		{
			//STRCAT(lpStr,MAKE_T(")");
		}
		else
		{
			STRCAT(lpStr, MAKE_T(","));
		}
	}

	STRCAT(lpStr, MAKE_T(" WHERE "));


	for (int i = 0; i<nMember; i++)
	{
		memset(szTemp, 0, sizeof(szTemp));
		if (pSettings[i].bPRIMARYKEY)
		{
			switch (pSettings[i].nTYPE)
			{
			case TYPE_INTEGER:
				STRCAT(lpStr, pSettings[i].szFIELDNAME);
				SPRINTF(szTemp, 256, MAKE_T("=%d"), *((int*)pSettings[i].POINTER));
				STRCAT(lpStr, szTemp);
				break;
			case TYPE_TEXT:
				STRCAT(lpStr, pSettings[i].szFIELDNAME);
				SPRINTF(szTemp, 256, MAKE_T("='%s'"), (TYC *)pSettings[i].POINTER);
				STRCAT(lpStr, szTemp);
				break;
			case TYPE_FLOAT:
				STRCAT(lpStr, pSettings[i].szFIELDNAME);
				SPRINTF(szTemp, 256, MAKE_T("=%f"), *((float*)pSettings[i].POINTER));
				STRCAT(lpStr, szTemp);
				break;
			case TYPE_DOUBLE:
				STRCAT(lpStr, pSettings[i].szFIELDNAME);
				SPRINTF(szTemp, 256, MAKE_T("=%lf"), *((double*)pSettings[i].POINTER));
				STRCAT(lpStr, szTemp);
				break;
			case TYPE_DATALENGTH:
				STRCAT(lpStr, pSettings[i].szFIELDNAME);
				SPRINTF(szTemp, 256, MAKE_T("=%d"), *((int*)pSettings[i].POINTER));
				STRCAT(lpStr, szTemp); i++;
			case TYPE_DATA:
				STRCAT(lpStr, pSettings[i].szFIELDNAME);
				SPRINTF(szTemp, 256, MAKE_T("=:%s"), pSettings[i].szFIELDNAME);
				STRCAT(lpStr, szTemp);
				break;
			}
		}
	}
}



void CSQLData::GetDeleteQuery(TYC *lpStr, int nCount, TYC *pszTableName, TYPESETTINGS *pSettings, int nMember)
{
	TYC szTemp[256];
	memset((void*)lpStr, 0, nCount);
	STRCAT(lpStr, SQL_DELETE);
	STRCAT(lpStr, pszTableName);
	STRCAT(lpStr, MAKE_T(" WHERE "));
	for (int i = 0; i<nMember; i++)
	{
		if (pSettings[i].bPRIMARYKEY)
		{
			memset(szTemp, 0, sizeof(szTemp));
			switch (pSettings[i].nTYPE)
			{
			case TYPE_INTEGER:
				STRCAT(lpStr, pSettings[i].szFIELDNAME);
				SPRINTF(szTemp, 256, MAKE_T("=%d"), *((int*)pSettings[i].POINTER));
				STRCAT(lpStr, szTemp);
				break;
			case TYPE_TEXT:
				STRCAT(lpStr, pSettings[i].szFIELDNAME);
				SPRINTF(szTemp, 256, MAKE_T("='%s'"), (TYC *)pSettings[i].POINTER);
				STRCAT(lpStr, szTemp);
				break;
			case TYPE_FLOAT:
				STRCAT(lpStr, pSettings[i].szFIELDNAME);
				SPRINTF(szTemp, 256, MAKE_T("=%f"), *((float*)pSettings[i].POINTER));
				STRCAT(lpStr, szTemp);
				break;
			case TYPE_DOUBLE:
				STRCAT(lpStr, pSettings[i].szFIELDNAME);
				SPRINTF(szTemp, 256, MAKE_T("=%lf"), *((double*)pSettings[i].POINTER));
				STRCAT(lpStr, szTemp);
				break;
			case TYPE_DATALENGTH:
				STRCAT(lpStr, pSettings[i].szFIELDNAME);
				SPRINTF(szTemp, 256, MAKE_T("=%d"), *((int*)pSettings[i].POINTER));
				STRCAT(lpStr, szTemp);
				break;
			case TYPE_DATA:
				STRCAT(lpStr, pSettings[i].szFIELDNAME);
				SPRINTF(szTemp, 256, MAKE_T("=:%s"), pSettings[i].szFIELDNAME);
				STRCAT(lpStr, szTemp);
				break;
			}
		}
	}
}
void CSQLData::GetMaxIndexQuery(TYC *lpStr, int nCount, TYC *pszTableName, TYPESETTINGS *pSettings, int nMember)
{
	memset(lpStr, 0, nCount);
	STRCAT(lpStr, SQL_SELECT);
	STRCAT(lpStr, SQL_MAX);
	for (int i = 0; i<nMember; i++)
	{
		if (pSettings[i].bPRIMARYKEY)
		{
			STRCAT(lpStr, pSettings[i].szFIELDNAME);
		}
	}
	STRCAT(lpStr, SQL_MAXEND);
	STRCAT(lpStr, pszTableName);
}

void CSQLData::GetCreateQuery(TYC *lpStr, int nCount, TYC *pszTableName, TYPESETTINGS *pSettings, int nMember)
{
	TYC szTemp[256];
	memset(lpStr, 0, nCount);
	STRCAT(lpStr, SQL_CREATE);
	STRCAT(lpStr, MAKE_T("["));
	STRCAT(lpStr, pszTableName);
	STRCAT(lpStr, MAKE_T("] "));
	for (int i = 0; i<nMember; i++)
	{
		if (!i)
		{
			STRCAT(lpStr, MAKE_T("("));
		}
		switch (pSettings[i].nTYPE)
		{
		case TYPE_INTEGER:
			STRCAT(lpStr, MAKE_T("["));
			STRCAT(lpStr, pSettings[i].szFIELDNAME);
			STRCAT(lpStr, MAKE_T("] INTEGER"));
			if (pSettings[i].bPRIMARYKEY)
			{
				STRCAT(lpStr, MAKE_T(" PRIMARY KEY"));
			}
			break;
		case TYPE_TEXT:
			STRCAT(lpStr, MAKE_T("["));
			STRCAT(lpStr, pSettings[i].szFIELDNAME);
			SPRINTF(szTemp, 256, MAKE_T("] TEXT(%d)"), pSettings[i].nLENGTH);
			STRCAT(lpStr, szTemp);
			if (pSettings[i].bPRIMARYKEY)
			{
				STRCAT(lpStr, MAKE_T(" PRIMARY KEY"));
			}
			break;
		case TYPE_FLOAT:
		case TYPE_DOUBLE:
			STRCAT(lpStr, MAKE_T("["));
			STRCAT(lpStr, pSettings[i].szFIELDNAME);
			STRCAT(lpStr, MAKE_T("] FLOAT"));
			if (pSettings[i].bPRIMARYKEY)
			{
				STRCAT(lpStr, MAKE_T(" PRIMARY KEY"));
			}
			break;
		case TYPE_DATALENGTH:
			STRCAT(lpStr, MAKE_T("["));
			STRCAT(lpStr, pSettings[i].szFIELDNAME);
			STRCAT(lpStr, MAKE_T("] INTEGER"));
			if (pSettings[i].bPRIMARYKEY)
			{
				STRCAT(lpStr, MAKE_T(" PRIMARY KEY"));
			}
			break;
		case TYPE_DATA:
			STRCAT(lpStr, MAKE_T("["));
			STRCAT(lpStr, pSettings[i].szFIELDNAME);
			STRCAT(lpStr, MAKE_T("] LONGBINARY"));
			if (pSettings[i].bPRIMARYKEY)
			{
				STRCAT(lpStr, MAKE_T(" PRIMARY KEY"));
			}
			break;
		}

		if (i == (nMember - 1))
		{
			STRCAT(lpStr, MAKE_T(")"));
		}
		else
		{
			STRCAT(lpStr, MAKE_T(","));
		}
	}
}


bool CSQLData::SetData(int nField, void *pValue, int nSize)
{
	LPTYPESETTINGS pSettings;
	int nCount;
	MappingMembers();
	GetTypeSettingParam(&pSettings, &nCount);
	switch (pSettings[nField].nTYPE)
	{
	case TYPE_INTEGER:
	{
		int nValue = (*((int*)pValue));
		if (nValue != (*((int*)pSettings[nField].POINTER)))
		{
			(*((int*)pSettings[nField].POINTER)) = nValue;
			if (GetRecordState() == EDIT_NOT_MODIFIED)
				SetRecordState(EDIT_UPDATED);
		}
	}
	break;
	case TYPE_TEXT:
	{
        if (STRCMP((TYC *)pValue, (TYC *)pSettings[nField].POINTER))
		{
            STRNCPY((TYC *)pSettings[nField].POINTER, (TYC *)pValue, pSettings[nField].nLENGTH - 1);
			if (GetRecordState() == EDIT_NOT_MODIFIED)
				SetRecordState(EDIT_UPDATED);
		}
	}
	break;
	case TYPE_DOUBLE:
	{
		double dValue = (*((double*)pValue));
		if (dValue != (*((double*)pSettings[nField].POINTER)))
		{
			(*((double*)pSettings[nField].POINTER)) = dValue;
			if (GetRecordState() == EDIT_NOT_MODIFIED)
				SetRecordState(EDIT_UPDATED);
		}
	}
	break;
	case TYPE_FLOAT:
	{
		float fValue = (*((float*)pValue));
		if (fValue != (*((float*)pSettings[nField].POINTER)))
		{
			(*((float*)pSettings[nField].POINTER)) = fValue;
			if (GetRecordState() == EDIT_NOT_MODIFIED)
				SetRecordState(EDIT_UPDATED);
		}
	}
	break;
	case TYPE_DATALENGTH:
	{
		int nValue = (*((int*)pValue));
		if (nValue != (*((int*)pSettings[nField].POINTER)))
		{
			(*((int*)pSettings[nField].POINTER)) = nValue;
			SHARED_PTRM(unsigned char) *pByte = (SHARED_PTRM(unsigned char)*)pSettings[nField + 1].POINTER;		//크기변경 -> 재할당
			*pByte = SHARED_PTRM(unsigned char)(MALLOCFORSP(unsigned char, nValue));
			if (GetRecordState() == EDIT_NOT_MODIFIED)
				SetRecordState(EDIT_UPDATED);
		}
	}
	break;
	case TYPE_DATA:
	{
		SHARED_PTRM(unsigned char) *pByte = (SHARED_PTRM(unsigned char)*)pSettings[nField].POINTER;
		memcpy(GET_POINTEROF((*pByte)), (unsigned char*)pValue, *((int*)pSettings[nField - 1].POINTER));
		if (GetRecordState() == EDIT_NOT_MODIFIED)
			SetRecordState(EDIT_UPDATED);
	}
	break;
	}
	return false;
}



int CSQLData::GetData(int nField, void *pValue)
{
	LPTYPESETTINGS pSettings;
	int nCount;
	MappingMembers();
	GetTypeSettingParam(&pSettings, &nCount);
	switch (pSettings[nField].nTYPE)
	{
	case TYPE_INTEGER:
	{
		int *pInt = (int*)pValue;
		(*pInt) = (int)(*((int*)(pSettings[nField].POINTER)));
		return TYPE_INTEGER;
	}
	break;
	case TYPE_TEXT:
	{
        STRCPY((TYC *)pValue, (TYC *)pSettings[nField].POINTER);
		return TYPE_TEXT;
	}
	break;
	case TYPE_FLOAT:
	{
		float *pDouble = (float*)pValue;
		*pDouble = (float)(*(float*)pSettings[nField].POINTER);
		return TYPE_FLOAT;
	}
	break;
	case TYPE_DOUBLE:
	{
		double *pDouble = (double*)pValue;
		*pDouble = (double)(*(double*)pSettings[nField].POINTER);
		return TYPE_DOUBLE;
	}
	break;
	case TYPE_DATALENGTH:
	{
		int *pInt = (int*)pValue;
		(*pInt) = (int)(*((int*)(pSettings[nField].POINTER)));
		return TYPE_DATALENGTH;
	}
	break;
	case TYPE_DATA:
	{
		unsigned int **pUChar = (unsigned int**)pValue;
		SHARED_PTRM(unsigned char) *pByte = (SHARED_PTRM(unsigned char)*)pSettings[nField].POINTER;
		(*pUChar) = (unsigned int*)(*(GET_POINTEROF((*pByte))));
		return TYPE_DATA;
	}
	break;
	}
	return -1;
}





/*ALTER TABLE 테이블명
ADD 추가할 컬럼명  데이터 유형;*/


void CSQLData::GetAlterTableAddColumn(TYC *lpStr, int nCount, TYC *pszTableName, TYPESETTINGS *pSettings, int nMember)
{
	TYC szTemp[256];
	memset(lpStr, 0, sizeof(TYC)*nCount);
	STRCAT(lpStr, SQL_ALTER);
	STRCAT(lpStr, pszTableName);
	STRCAT(lpStr, MAKE_T(" ADD "));
	switch (pSettings[nMember].nTYPE)
	{
	case TYPE_INTEGER:
		STRCAT(lpStr, MAKE_T(" "));
		STRCAT(lpStr, pSettings[nMember].szFIELDNAME);
		STRCAT(lpStr, MAKE_T(" INTEGER "));
		if (pSettings[nMember].bPRIMARYKEY)
		{
			STRCAT(lpStr, MAKE_T(" PRIMARYKEY "));
		}
		break;
	case TYPE_TEXT:
		STRCAT(lpStr, MAKE_T(" "));
		STRCAT(lpStr, pSettings[nMember].szFIELDNAME);
		SPRINTF(szTemp, 256, MAKE_T(" TEXT(%d) "), pSettings[nMember].nLENGTH);
		STRCAT(lpStr, szTemp);
		if (pSettings[nMember].bPRIMARYKEY)
		{
			STRCAT(lpStr, MAKE_T(" PRIMARYKEY "));
		}
		break;
	case TYPE_FLOAT:
	case TYPE_DOUBLE:
		STRCAT(lpStr, MAKE_T(" "));
		STRCAT(lpStr, pSettings[nMember].szFIELDNAME);
		STRCAT(lpStr, MAKE_T(" FLOAT "));
		if (pSettings[nMember].bPRIMARYKEY)
		{
			STRCAT(lpStr, MAKE_T(" PRIMARYKEY "));
		}
		break;
	case TYPE_DATALENGTH:
		STRCAT(lpStr, MAKE_T(" "));
		STRCAT(lpStr, pSettings[nMember].szFIELDNAME);
		STRCAT(lpStr, MAKE_T(" INTEGER "));
		if (pSettings[nMember].bPRIMARYKEY)
		{
			STRCAT(lpStr, MAKE_T(" PRIMARYKEY "));
		}
		break;
	case TYPE_DATA:
		STRCAT(lpStr, MAKE_T(" "));
		STRCAT(lpStr, pSettings[nMember].szFIELDNAME);
		STRCAT(lpStr, MAKE_T(" LONGBINARY "));
		if (pSettings[nMember].bPRIMARYKEY)
		{
			STRCAT(lpStr, MAKE_T(" PRIMARYKEY "));
		}
		break;
	}
}


bool CSQLData::InsertExec()
{
	int rc, nRetVal;
	TYC *tail;
	sqlite3_stmt *state;
	sqlite3* pDB = GetDatabase();
	TYC szQueryBuffer[8192];
	LPTYPESETTINGS pSettings;
	int nCount;
	MappingMembers();
	GetTypeSettingParam(&pSettings, &nCount);
	TYC *pTableName = GetTableName();
	if (pTableName)
	{
		GetInsertQuery(szQueryBuffer, dim(szQueryBuffer), pTableName, pSettings, nCount);
        rc = SQLITE3_PREPARE(pDB, szQueryBuffer, STRLEN(szQueryBuffer) * sizeof(TYC), &state, TAIL_CASTING&tail);

		qDebug() << "[insert query]" << QString::fromWCharArray(szQueryBuffer);
		if (rc != SQLITE_OK)
		{
			return false;
		}
		if (GetBLOBExist())
		{
			for (int i = 0; i<nCount; i++)
			{
				if (pSettings[i].nTYPE == TYPE_DATALENGTH)
				{
					char chBuffer[128];
					SHARED_PTRM(unsigned char) *pByte = (SHARED_PTRM(unsigned char)*)pSettings[i + 1].POINTER;
#ifdef PAC_EDITOR
					snprintf(chBuffer, dim(chBuffer), ":%S", pSettings[i + 1].szFIELDNAME);
#else if
	#ifndef UNDER_CE
					SPRINTF(chBuffer, dim(chBuffer), ":%s", pSettings[i + 1].szFIELDNAME);
	#else if
					sprintf_s(chBuffer,dim(chBuffer),":%s",pSettings[i+1].szFIELDNAME);
	#endif
#endif
					sqlite3_bind_blob(state, sqlite3_bind_parameter_index(state, chBuffer), GET_POINTEROF((*pByte)), *((int*)pSettings[i].POINTER), SQLITE_TRANSIENT);
				}
			}
		}
		nRetVal = sqlite3_step(state);
		if (nRetVal == SQLITE_DONE)
		{
			nRetVal = sqlite3_finalize(state);
			if (nRetVal == SQLITE_OK)
				return true;
		}
	}
	return false;
}

bool CSQLData::UpdateExec()
{
	int rc, nRetVal;
	TYC *tail;
	sqlite3_stmt *state;
	sqlite3* pDB = GetDatabase();
	TYC szQueryBuffer[8192];
	LPTYPESETTINGS pSettings;
	int nCount;
	MappingMembers();
	GetTypeSettingParam(&pSettings, &nCount);
	TYC *pTableName = GetTableName();
	if (pTableName)
	{
		GetUpdateQuery(szQueryBuffer, dim(szQueryBuffer), pTableName, pSettings, nCount);
        rc = SQLITE3_PREPARE(pDB, szQueryBuffer, STRLEN(szQueryBuffer) * sizeof(TYC), &state, TAIL_CASTING&tail);
		if (rc != SQLITE_OK)
		{
#ifdef PAC_EDITOR
			OutputDebugStringW((TYC *)SQLITE3_ERRMSG(pDB));
			OutputDebugStringW(MAKE_T("\n"));
#endif
			return false;
		}
		if (GetBLOBExist())
		{
			for (int i = 0; i<nCount; i++)
			{
				if (pSettings[i].nTYPE == TYPE_DATALENGTH)
				{
					char chBuffer[128];
					SHARED_PTRM(unsigned char) *pByte = (SHARED_PTRM(unsigned char)*)pSettings[i + 1].POINTER;
#ifdef PAC_EDITOR
					snprintf(chBuffer, dim(chBuffer), ":%S", pSettings[i + 1].szFIELDNAME);
#else if
	#ifndef UNDER_CE
					SPRINTF(chBuffer, dim(chBuffer), ":%s", pSettings[i + 1].szFIELDNAME);
	#else if
					sprintf_s(chBuffer,dim(chBuffer),":%s",pSettings[i+1].szFIELDNAME);
	#endif
#endif
					int nSize = (*((int*)pSettings[i].POINTER));
					sqlite3_bind_blob(state, sqlite3_bind_parameter_index(state, chBuffer), GET_POINTEROF((*pByte)), *((int*)pSettings[i].POINTER), SQLITE_TRANSIENT);
				}
			}
		}
		nRetVal = sqlite3_step(state);
		if (nRetVal == SQLITE_DONE)
		{
			nRetVal = sqlite3_finalize(state);
			if (nRetVal == SQLITE_OK)
				return true;
		}
	}
	return false;
}


bool CSQLData::DeleteExec()
{
	int rc, nRetVal;
	sqlite3_stmt* state;
	const TYC *tail;
	sqlite3* pDB = GetDatabase();
	TYC szQueryBuffer[8192];
	TYC *pTableName;
	LPTYPESETTINGS pSettings;
	int nCount;
	GetTypeSettingParam(&pSettings, &nCount);
	pTableName = GetTableName();
	if (pTableName)
	{
		GetDeleteQuery(szQueryBuffer, dim(szQueryBuffer), pTableName, pSettings, nCount);
        rc = SQLITE3_PREPARE(pDB, szQueryBuffer, STRLEN(szQueryBuffer) * sizeof(TYC), &state, TAIL_CASTING&tail);
		if (SQLITE_OK != rc)
		{
#ifdef PAC_EDITOR
			OutputDebugStringW((TYC *)SQLITE3_ERRMSG(pDB));
			OutputDebugStringW(MAKE_T("\n"));
#endif
			return false;
		}
		int nColumns = sqlite3_column_count(state);
		nRetVal = sqlite3_step(state);
		sqlite3_finalize(state);
		if ((!nColumns) && (nRetVal == SQLITE_DONE))
		{
			return true;
		}
	}
	return false;
}

bool CSQLData::CommitData(int nOrder)
{
	TYPESETTINGS *pSettings;
	int nCompCount;
	bool bRet = GetTypeSettingParam(&pSettings, &nCompCount);
	if (bRet)
	{
		MappingMembers();
		for(int i=0;i<nCompCount;i++)
		{
			if (pSettings[i].bORDER)
			{
				int* pInt=(int*)pSettings[i].POINTER;
				if ((*pInt) != nOrder)
				{
					(*pInt) = nOrder;
					int nRecordState=GetRecordState();
					switch (GetRecordState())
					{
					case EDIT_NOT_MODIFIED:
						SetRecordState(EDIT_UPDATED);
						break;
					case EDIT_DELETED:
					case EDIT_UPDATED:
					case EDIT_INSERTED:
						break;
					}
				}
			}
		}

		switch (GetRecordState())
		{
		case EDIT_NOT_MODIFIED:
			break;
		case EDIT_UPDATED:
			bRet = UpdateExec();
			if (bRet)
				SetRecordState(EDIT_NOT_MODIFIED);
			break;
		case EDIT_INSERTED:
			bRet = InsertExec();
			if (bRet)
				SetRecordState(EDIT_NOT_MODIFIED);
			break;
		case EDIT_DELETED:
			bRet = DeleteExec();
			break;
		case EDIT_TO_BE_IGNORED:
		default:
			bRet = false;
			break;
		}

		int nSubCount = GetChildCount();
		for (int i = 0; i<nSubCount; i++)
		{
			if (m_vChildItem[i].vSQLData.size())
			{
				int nParentIndexCol = 0;
				int nOrderCol = 0;
				int nIndexCol = 0;
				int nParentIndex = GetIndex();
				int nOrder = 1;
				for (int j = 0; j<m_vChildItem[i].vSQLData.size(); j++)
				{
					nParentIndexCol = m_vChildItem[i].vSQLData[j]->GetParentIndexCol();
					nOrderCol = m_vChildItem[i].vSQLData[j]->GetOrderCol();
					nIndexCol = m_vChildItem[i].vSQLData[j]->GetIndexCol();

					qDebug() << Q_FUNC_INFO << "parentcol:" << nParentIndexCol << "ordercol:" << nOrderCol << "nIndexCol" << nIndexCol;

					if (nParentIndexCol != -1)
						m_vChildItem[i].vSQLData[j]->SetData(nParentIndexCol, (void*)&nParentIndex);
					if (nOrderCol != -1)
						m_vChildItem[i].vSQLData[j]->SetData(nOrderCol, (void*)&nOrder);
					nOrder++;
					m_vChildItem[i].vSQLData[j]->CommitData(j+1);
				}
			}

			for (int j = 0; j<m_vChildItem[i].vSQLDataDelItems.size(); j++)
			{
				m_vChildItem[i].vSQLDataDelItems[j]->CommitData(j+1);
			}
			m_vChildItem[i].vSQLDataDelItems.clear();
		}
	}
	return bRet;
}



CSQLData* CSQLData::Clone()
{
    CSQLData *pClone=CreateNew();
    LPTYPESETTINGS pSettingsSoc,pSettingsTgt;
    int nCountSoc,nCountTgt;
    GetTypeSettingParam(&pSettingsSoc,&nCountSoc);
	pClone->GetTypeSettingParam(&pSettingsTgt,&nCountTgt);
    MappingMembers();
	int nParentIndex=pClone->GetIndex();
    for(int nField=0;nField<nCountTgt;nField++)
    {
        switch(pSettingsTgt[nField].nTYPE)
        {
        case TYPE_INTEGER:
            {
				if(!pSettingsTgt[nField].bPRIMARYKEY)
				{
					MappingMembers();
					int *pValueSoc=(int*)pSettingsSoc[nField].POINTER;
					pClone->MappingMembers();
					int *pValueTgt=(int*)pSettingsTgt[nField].POINTER;
					(*pValueTgt)=(*pValueSoc);
				}
            }
            break;
        case TYPE_TEXT:
            {
				MappingMembers();
                TYC *pValueSoc=(TYC *)pSettingsSoc[nField].POINTER;
				pClone->MappingMembers();
                TYC *pValueTgt=(TYC *)pSettingsTgt[nField].POINTER;
                memcpy(pValueTgt,pValueSoc,pSettingsSoc[nField].nLENGTH*sizeof(TYC));
            }
            break;
        case TYPE_FLOAT:
            {
				MappingMembers();
                float *pValueSoc=(float*)pSettingsSoc[nField].POINTER;
				pClone->MappingMembers();
                float *pValueTgt=(float*)pSettingsTgt[nField].POINTER;
                (*pValueTgt)=(*pValueSoc);
            }
            break;
        case TYPE_DOUBLE:
            {
				MappingMembers();
                double *pValueSoc=(double*)pSettingsSoc[nField].POINTER;
				pClone->MappingMembers();
                double *pValueTgt=(double*)pSettingsTgt[nField].POINTER;
                (*pValueTgt)=(*pValueSoc);
            }
            break;
        case TYPE_DATALENGTH:
            {
				MappingMembers();
                int *pValueSoc=(int*)pSettingsSoc[nField].POINTER;
				pClone->MappingMembers();
                int *pValueTgt=(int*)pSettingsTgt[nField].POINTER;
                (*pValueTgt)=(*pValueSoc);
            }
            break;
        case TYPE_DATA:
            {
				 MappingMembers();
                 SHARED_PTRM(unsigned char) *pByteSoc=(SHARED_PTRM(unsigned char)*)pSettingsSoc[nField+1].POINTER;
				 pClone->MappingMembers();
				 int *pValueTgt = (int*)pSettingsTgt[nField].POINTER; 
                 SHARED_PTRM(unsigned char) *pByteTgt=(SHARED_PTRM(unsigned char)*)pSettingsTgt[nField+1].POINTER;
                 (*pByteTgt)= SHARED_PTRM(unsigned char)(MALLOCFORSP(unsigned char,(*pValueTgt)));
				
                 memcpy(GET_POINTEROF((*pByteTgt)),GET_POINTEROF((*pByteSoc)),(*pValueTgt));
            }
            break;
        }
    }
	SetAdditionalMembers(pClone);
    std::vector<SHARED_PTRC(CSQLData)>::iterator vit;
    for(int i=0;i<GetChildCount();i++)
    {
       for(vit=m_vChildItem[i].vSQLData.begin();vit!=m_vChildItem[i].vSQLData.end();vit++)
       {
		   int nDistance=std::distance(m_vChildItem[i].vSQLData.begin(),vit)+1;
           SHARED_PTRC(CSQLData) pValue=SHARED_PTRC(CSQLData)( (*vit)->Clone());
		   int nParentCol=pValue->GetParentIndexCol();
		   if(nParentCol!=-1)
			   pValue->SetData(nParentCol,&nParentIndex);
		   int nOrderCol=pValue->GetOrderCol();
		   if(nOrderCol!=-1)
			   pValue->SetData(nOrderCol,&nDistance);
           pClone->m_vChildItem[i].vSQLData.push_back(pValue);
       }
    }
    return pClone;
}




CTreeInfo::CTreeInfo()
{

}

CTreeInfo::~CTreeInfo()
{
}


////////////////////////////////////////////////////
CTreeItem::CTreeItem(void* pPointer)
	:m_pItem((LPCHILDITEM)pPointer)
{

}

CTreeItem::~CTreeItem()
{

}


void CTreeItem::SetParent(void *pParent)
{
	m_pSQLDataParent = (CSQLData*)pParent;
}

CTreeInfo* CTreeItem::GetParent()
{
	return GET_POINTEROF(m_pSQLDataParent->m_pTreeInfo);
}


int CTreeItem::GetChildCount()
{
	return m_pItem->vSQLData.size();
}

////////////////////////////////////////////////////
CTreeInfo* CTreeItem::GetChild(int nRow)
{
	CTreeInfo *pTI = NULL;
	try
	{
		if (m_pItem->vSQLData.size()>nRow)
			pTI = GET_POINTEROF(m_pItem->vSQLData.at(nRow)->m_pTreeInfo);
	}
	catch (std::exception &e)
	{
		e.what();
	}
	return pTI;
}

void CTreeItem::GetNick(TYC *pChar, int nCount)
{
	if (GetEditor())
		SPRINTF(pChar, nCount, MAKE_T("%s"), GetEditor()->GetTableName());
	else
		memset(pChar, 0, nCount * sizeof(TYC));
}



int CTreeItem::GetType()
{
	return 1;
}


bool CTreeItem::Insert(int nRow)
{
	try
	{
		SHARED_PTRC(CSQLData) pData = SHARED_PTRC(CSQLData)(m_pSQLDataEditor->FeedInserted());
		pData->m_pTreeInfo = SHARED_PTRC(CTreeInfo)(new CTreeSQLData((void*)GET_POINTEROF(pData)));
		pData->m_pTreeInfo->SetParent(m_pItem);
		m_pSQLDataEditor->InsertData(nRow, pData);
	}
	catch (std::exception &e)
	{
		e.what();
	}
	return true;
}

bool CTreeItem::Remove(int nRow)
{
	return m_pSQLDataEditor->RemoveData(nRow);
}



SHARED_PTRC(CSQLData) CTreeItem::Insert()
{
	try
	{
		SHARED_PTRC(CSQLData) pData = SHARED_PTRC(CSQLData)(m_pSQLDataEditor->FeedInserted());
		pData->m_pTreeInfo = SHARED_PTRC(CTreeInfo)(new CTreeSQLData((void*)GET_POINTEROF(pData)));
		pData->m_pTreeInfo->SetParent(m_pItem);
		m_pSQLDataEditor->InsertData(-1, pData);
		return pData;
	}
	catch (std::exception &e)
	{
		e.what();
	}
	return SHARED_PTRC(CSQLData)();
}

int CTreeItem::GetRow()
{
	try
	{
		if (m_pSQLDataParent)
		{
			int nCount = m_pSQLDataParent->m_vChildItem.size();
			for (int i = 0; i<nCount; i++)
			{
				if (m_pItem == (&m_pSQLDataParent->m_vChildItem.at(i)))
				{
					return i;
				}
			}
		}
	}
	catch (std::exception &e)
	{
		e.what();
	}

	return 0;
}

int CTreeItem::FindIndex(int nIndex)
{
	std::vector<SHARED_PTRC(CSQLData)>::iterator nit;
	nit = find_if(m_pSQLDataEditor->m_pvSQLData->begin(), m_pSQLDataEditor->m_pvSQLData->end(), findSQLData(nIndex));
	if (nit != m_pSQLDataEditor->m_pvSQLData->end())
	{
		int nOffset = distance(m_pSQLDataEditor->m_pvSQLData->begin(), nit);
		return nOffset;
	}
	return -1;
}









CTreeSQLData::CTreeSQLData(void* pPointer)
	:m_pItem((CSQLData*)pPointer)
{

}

CTreeSQLData::~CTreeSQLData()
{
}


void CTreeSQLData::SetParent(void *pParent)
{
	m_pItemParent = (LPCHILDITEM)pParent;
}

CTreeInfo* CTreeSQLData::GetParent()
{
	return GET_POINTEROF(m_pItemParent->m_pTreeInfo);
}


int CTreeSQLData::GetChildCount()
{
	return m_pItem->m_vChildItem.size();
}

CTreeInfo* CTreeSQLData::GetChild(int nRow)
{

	CTreeInfo *pTreeInfo = 0;
	try
	{
		pTreeInfo = GET_POINTEROF(m_pItem->m_vChildItem.at(nRow).m_pTreeInfo);
	}
	catch (std::exception &e)
	{
		e.what();
	}
	return pTreeInfo;
}

int CTreeSQLData::GetType()
{
	return 2;
}


bool CTreeSQLData::Insert(int nRow)
{
	return false;
}

bool CTreeSQLData::Remove(int nRow)
{
	return false;
}


void CTreeSQLData::GetNick(TYC *pChar, int nCount)
{
	SPRINTF(pChar, nCount, MAKE_T("%s #%d"), m_pItem->GetTableName(), m_pItem->GetIndex());
}

int CTreeSQLData::GetRow()
{
	try
	{
		if (m_pItemParent)
		{
			int nIndex = m_pItem->GetIndex();
			int nCount = m_pItemParent->vSQLData.size();
			for (int i = 0; i<nCount; i++)
			{
				if (nIndex == (m_pItemParent->vSQLData.at(i)->GetIndex()))
				{
					return i;
				}
			}
		}
	}
	catch (std::exception &e)
	{
		e.what();
	}
	return 0;
}

// table mange만 사용
void MakeRelationShip2(std::vector<SHARED_PTRC(CSQLData)> *pParent, int nChildIndex, std::vector<SHARED_PTRC(CSQLData)> *pChild)
{
	int nParentIndexCol = 0;
	int nParentIndex;
	int nChildCount;
	std::vector<SHARED_PTRC(CSQLData)>::iterator nit;
	std::vector<SHARED_PTRC(CSQLData)>::iterator knit;
	if (pParent&&pChild&&pParent->size() && pChild->size())
	{
		nParentIndexCol = pChild->at(0)->GetParentIndexCol();
		if (nParentIndexCol != -1)
		{
			for (nit = pChild->begin(); nit != pChild->end(); nit++)
			{
				(*nit)->GetData(nParentIndexCol, &nParentIndex);
				knit = find_if(pParent->begin(), pParent->end(), findSQLData(nParentIndex));
				if (knit != pParent->end())
				{
					nChildCount = pParent->at(0)->GetChildCount();
					if (nChildIndex<nChildCount)
					{
						(*nit)->m_pTreeInfo = SHARED_PTRC(CTreeInfo)(new CTreeSQLData((void*)GET_POINTEROF((*nit))));
						(*nit)->m_pTreeInfo->SetParent(&(*knit)->m_vChildItem.at(nChildIndex));
						(*knit)->m_vChildItem[nChildIndex].vSQLData.push_back(*nit);
					}
				}
			}
		}
	}
}