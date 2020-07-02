#pragma once
#include "DefineTables.h"

////////////////////////////////// LED RELATED //////////////////////////////////
// ETNDIndicator
BEGIN_CLASS_FROM_SQLDATA(ETNDIndicator,
	nWidth = CSQLData::m_nETNDWidth;
nHeight = CSQLData::m_nETNDHeight;
nPage = 1;
nBit = 4;
nDataLength = (nWidth*nHeight*nBit*nPage) / 8;
pByte = SHARED_PTRM(unsigned char)(MALLOCFORSP(unsigned char, (nWidth*nHeight*nBit*nPage) / 8));
memset(GET_POINTEROF(pByte), 0, ((nWidth*nHeight*nBit*nPage) / 8));
,
);
COMMON_VAL_FOR_SQLDATA;
DECLARE_TYPESETTINGS(10);
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC;
BEGIN_MAPPING_MEMBERS
m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
m_tSettings[1].POINTER = (void*)(&nCode);
m_tSettings[2].POINTER = (void*)(&nDataLength);
m_tSettings[3].POINTER = (void*)(&pByte);
m_tSettings[4].POINTER = (void*)(&nWidth);
m_tSettings[5].POINTER = (void*)(&nHeight);
m_tSettings[6].POINTER = (void*)(&nBit);
m_tSettings[7].POINTER = (void*)(&nPage);
m_tSettings[8].POINTER = (void*)(&nMode);
m_tSettings[9].POINTER = (void*)(&nOrder);
END_MAPPING_MEMBERS
int nCode{ 0 };
int nDataLength;
int nWidth;
int nHeight;
int nBit;
int nPage;
int nMode{ 0 };
int nOrder{ 1 };
SHARED_PTRM(unsigned char) pByte;
SHARED_PTRM(unsigned char) pConvByte; // no use
END_CLASS_FROM_SQLDATA
DECLARE_EDITOR_CLASS(ETNDIndicator);
// !ETNDIndicator

// EDDIndicator
BEGIN_CLASS_FROM_SQLDATA(EDDIndicator,
	nWidth = CSQLData::m_nEDDWidth;
nHeight = CSQLData::m_nEDDHeight;
nPage = 1;
nBit = 4;
nDataLength = (nWidth*nHeight*nBit*nPage) / 8;
pByte = SHARED_PTRM(unsigned char)(MALLOCFORSP(unsigned char, (nWidth*nHeight*nBit*nPage) / 8));
memset(GET_POINTEROF(pByte), 0, ((nWidth*nHeight*nBit*nPage) / 8));
,
);
COMMON_VAL_FOR_SQLDATA;
DECLARE_TYPESETTINGS(10);
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC;
BEGIN_MAPPING_MEMBERS
m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
m_tSettings[1].POINTER = (void*)(&nCode);
m_tSettings[2].POINTER = (void*)(&nDataLength);
m_tSettings[3].POINTER = (void*)(&pByte);
m_tSettings[4].POINTER = (void*)(&nWidth);
m_tSettings[5].POINTER = (void*)(&nHeight);
m_tSettings[6].POINTER = (void*)(&nBit);
m_tSettings[7].POINTER = (void*)(&nPage);
m_tSettings[8].POINTER = (void*)(&nMode);
m_tSettings[9].POINTER = (void*)(&nOrder);
END_MAPPING_MEMBERS
int nCode{ 0 };
int nDataLength;
int nWidth;
int nHeight;
int nBit;
int nPage;
int nMode{ 0 };
int nOrder{ 1 };
SHARED_PTRM(unsigned char) pByte;
SHARED_PTRM(unsigned char) pConvByte; // no use
END_CLASS_FROM_SQLDATA
DECLARE_EDITOR_CLASS(EDDIndicator);
// !EDDIndicator

// EDDIndex
BEGIN_CLASS_FROM_SQLDATA_WITH_CHILDS(EDDIndex, , , 1);
COMMON_VAL_FOR_SQLDATA;
DECLARE_TYPESETTINGS(4);
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC;
BEGIN_MAPPING_MEMBERS
m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
m_tSettings[1].POINTER = (void*)(szDesc);
m_tSettings[2].POINTER = (void*)(&nCode);
m_tSettings[3].POINTER = (void*)(&nOrder);
END_MAPPING_MEMBERS
TYC szDesc[128]{ 0 };
int nCode{ 0 };
int nOrder{ 1 };
END_CLASS_FROM_SQLDATA
DECLARE_EDITOR_CLASS(EDDIndex);
// !EDDIndex

// EDDIndexList
BEGIN_CLASS_FROM_SQLDATA(EDDIndexList, , );
COMMON_VAL_FOR_SQLDATA;
DECLARE_TYPESETTINGS(4);
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC;
BEGIN_MAPPING_MEMBERS
m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
m_tSettings[1].POINTER = (void*)(&nParent);
m_tSettings[2].POINTER = (void*)(&nOrder);
m_tSettings[3].POINTER = (void*)(&nEDDIndex);
END_MAPPING_MEMBERS
int nParent{ 0 };
int nOrder{ 0 };
int nEDDIndex{ 0 };
END_CLASS_FROM_SQLDATA
DECLARE_EDITOR_CLASS(EDDIndexList);
// !EDDIndexList
