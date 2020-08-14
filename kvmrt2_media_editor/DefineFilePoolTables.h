#pragma once
#include "DefineTables.h"

////////////////////////////////////////////////// FILE POOL RELATED /////////////////////////////////////////
// FontPool
BEGIN_CLASS_FROM_SQLDATA(FontPool, , );
COMMON_VAL_FOR_SQLDATA;
DECLARE_TYPESETTINGS(6);
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC;
BEGIN_MAPPING_MEMBERS
m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
m_tSettings[1].POINTER = (void*)(&nCode);
m_tSettings[2].POINTER = (void*)(&nSpareCode);
m_tSettings[3].POINTER = (void*)(szFileName);
m_tSettings[4].POINTER = (void*)(szFontFace);
m_tSettings[5].POINTER = (void*)(&nOrder);
END_MAPPING_MEMBERS
int nCode{ 0 };
int nSpareCode{ 0 };
TYC szFileName[128]{ 0 };
TYC szFontFace[128]{ 0 };
int nOrder{ 1 };
END_CLASS_FROM_SQLDATA
DECLARE_EDITOR_CLASS(FontPool);
// !FontPool

// AudioFilePool
BEGIN_CLASS_FROM_SQLDATA(AudioFilePool, , );
COMMON_VAL_FOR_SQLDATA;
DECLARE_TYPESETTINGS(7);
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC;
BEGIN_MAPPING_MEMBERS
m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
m_tSettings[1].POINTER = (void*)(&nCode);
m_tSettings[2].POINTER = (void*)(&nSpareCode);
m_tSettings[3].POINTER = (void*)(szFileName);
m_tSettings[4].POINTER = (void*)(&uCRC);
m_tSettings[5].POINTER = (void*)(&uSize);
m_tSettings[6].POINTER = (void*)(&nOrder);
END_MAPPING_MEMBERS
int nCode{ 0 };
int nSpareCode{ 0 };
TYC szFileName[256]{ 0 };
unsigned short uCRC{ 0 };
unsigned int uSize{ 0 };
int nOrder{ 1 };
END_CLASS_FROM_SQLDATA
DECLARE_EDITOR_CLASS(AudioFilePool);
// !AudioFilePool

// VideoFilePool
BEGIN_CLASS_FROM_SQLDATA(VideoFilePool, , );
COMMON_VAL_FOR_SQLDATA;
DECLARE_TYPESETTINGS(7);
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC;
BEGIN_MAPPING_MEMBERS
m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
m_tSettings[1].POINTER = (void*)(&nCode);
m_tSettings[2].POINTER = (void*)(&nSpareCode);
m_tSettings[3].POINTER = (void*)(szFileName);
m_tSettings[4].POINTER = (void*)(&uCRC);
m_tSettings[5].POINTER = (void*)(&uSize);
m_tSettings[6].POINTER = (void*)(&nOrder);
END_MAPPING_MEMBERS
int nCode{ 0 };
int nSpareCode{ 0 };
TYC szFileName[256]{ 0 };
unsigned short uCRC{ 0 };
unsigned int uSize{ 0 };
int nOrder{ 1 };
END_CLASS_FROM_SQLDATA
DECLARE_EDITOR_CLASS(VideoFilePool);
// !VideoFilePool

// StationImagePool
BEGIN_CLASS_FROM_SQLDATA(StationImagePool, , );
COMMON_VAL_FOR_SQLDATA;
DECLARE_TYPESETTINGS(16);
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC;
BEGIN_MAPPING_MEMBERS
m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
m_tSettings[1].POINTER = (void*)(&nType);
m_tSettings[2].POINTER = (void*)szFileName;
m_tSettings[3].POINTER = (void*)(&nFontIndex);
m_tSettings[4].POINTER = (void*)(&nFontSize);
m_tSettings[5].POINTER = (void*)(&nFontAttrib);
m_tSettings[6].POINTER = (void*)(&nWidthLimit);
m_tSettings[7].POINTER = (void*)(&nHeightLimit);
m_tSettings[8].POINTER = (void*)(&nWidth);
m_tSettings[9].POINTER = (void*)(&nHeight);
m_tSettings[10].POINTER = (void*)(&nProp1);
m_tSettings[11].POINTER = (void*)(&nProp2);
m_tSettings[12].POINTER = (void*)(&nDataLength);
m_tSettings[13].POINTER = (void*)(&pByte);
m_tSettings[14].POINTER = (void*)(&nOrder);
m_tSettings[15].POINTER = (void*)(szDesc);
END_MAPPING_MEMBERS
// fields
int nType{ 0 };
TYC szFileName[256]{ 0 };
int nFontIndex{ 0 };
int nFontSize{ 14 };
int nFontAttrib{ 0 };
int nWidthLimit{ 999 };
int nHeightLimit{ 999 };
int nWidth{ 0 };
int nHeight{ 0 };
int nProp1{ 0 };
int nProp2{ 0 };
int nDataLength{ 0 };
SHARED_PTRM(unsigned char) pByte { 0 };
int nOrder{ 1 };
TYC szDesc[256]{ 0 };
// !fields
int nTextureIndex{ 0 };
END_CLASS_FROM_SQLDATA
DECLARE_EDITOR_CLASS(StationImagePool);
// !StationImagePool

// BitmapImagePool
BEGIN_CLASS_FROM_SQLDATA(BitmapImagePool, , );
COMMON_VAL_FOR_SQLDATA;
DECLARE_TYPESETTINGS(8);
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC;
BEGIN_MAPPING_MEMBERS
m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
m_tSettings[1].POINTER = (void*)(&nType);
m_tSettings[2].POINTER = (void*)szFileName;
m_tSettings[3].POINTER = (void*)(&nWidth);
m_tSettings[4].POINTER = (void*)(&nHeight);
m_tSettings[5].POINTER = (void*)(&nDataLength);
m_tSettings[6].POINTER = (void*)(&pByte);
m_tSettings[7].POINTER = (void*)(&nOrder);
END_MAPPING_MEMBERS
// fields
int nType{ 0 };
TYC szFileName[256]{ 0 };
int nDataLength{ 0 };
int nWidth{ 0 };
int nHeight{ 0 };
SHARED_PTRM(unsigned char) pByte { 0 };
int nOrder{ 1 };
// !fields
int nTextureIndex{ 0 };
END_CLASS_FROM_SQLDATA
DECLARE_EDITOR_CLASS(BitmapImagePool);
// !BitmapImagePool

BEGIN_CLASS_FROM_SQLDATA_WITH_CHILDS(ImageIndexList, , , 1);
COMMON_VAL_FOR_SQLDATA;
DECLARE_TYPESETTINGS(4);
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC;
BEGIN_MAPPING_MEMBERS
m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
m_tSettings[1].POINTER = (void*)(&nOrder);
m_tSettings[2].POINTER = (void*)(&nDuration);
m_tSettings[3].POINTER = (void*)szDesc;
END_MAPPING_MEMBERS
// fields
int nOrder{ 1 };
int nDuration{ 0 };
TYC szDesc[128]{ 0 };
// !fields
float fRect[4]{ 0.0 };
END_CLASS_FROM_SQLDATA
DECLARE_EDITOR_CLASS(ImageIndexList);

BEGIN_CLASS_FROM_SQLDATA(ImageIndex, , );
COMMON_VAL_FOR_SQLDATA;
DECLARE_TYPESETTINGS(8);
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC;
BEGIN_MAPPING_MEMBERS
m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
m_tSettings[1].POINTER = (void*)(&nParentIndex);
m_tSettings[2].POINTER = (void*)(&nOrder);
m_tSettings[3].POINTER = (void*)(&nType);
m_tSettings[4].POINTER = (void*)(&nStationNameBitmapIndex);
m_tSettings[5].POINTER = (void*)(&nStationBitmapIndex);
m_tSettings[6].POINTER = (void*)(&nXPos);
m_tSettings[7].POINTER = (void*)(&nYPos);
END_MAPPING_MEMBERS
int nParentIndex{ 0 };
int nOrder{ 1 };
int nType{ 0 };
int nStationNameBitmapIndex{ 0 };
int nStationBitmapIndex{ 0 };
int nXPos{ 0 };
int nYPos{ 0 };
END_CLASS_FROM_SQLDATA
DECLARE_EDITOR_CLASS(ImageIndex);