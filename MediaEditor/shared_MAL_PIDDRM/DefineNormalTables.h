#pragma once
#include "DefineTables.h"

//StationInformation
BEGIN_CLASS_FROM_SQLDATA_WITH_CHILDS(StationInformation, , , 0);
COMMON_VAL_FOR_SQLDATA;
DECLARE_TYPESETTINGS(19);
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC;
BEGIN_MAPPING_MEMBERS
m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
m_tSettings[1].POINTER = (void*)(&nStationCode);
m_tSettings[2].POINTER = (void*)szStationName1;
m_tSettings[3].POINTER = (void*)szStationName2;
m_tSettings[4].POINTER = (void*)szDesc;
m_tSettings[5].POINTER = (void*)(&nOrder);
m_tSettings[6].POINTER = (void*)(&nDurNextBM);
m_tSettings[7].POINTER = (void*)(&nDurNextEN);
m_tSettings[8].POINTER = (void*)(&nDurArrivingBM);
m_tSettings[9].POINTER = (void*)(&nDurArrivingEN);
m_tSettings[10].POINTER = (void*)(&nDurArrivalBM);
m_tSettings[11].POINTER = (void*)(&nDurArrivalEN);
m_tSettings[12].POINTER = (void*)(&nDurExchangeBM);
m_tSettings[13].POINTER = (void*)(&nDurExchangeEN);
m_tSettings[14].POINTER = (void*)(&nHasExchange);
m_tSettings[15].POINTER = (void*)(&nIsProVisional);
m_tSettings[16].POINTER = (void*)(&nApprPaDistance);
m_tSettings[17].POINTER = (void*)(&nSpare1);
m_tSettings[18].POINTER = (void*)(&nSpare2);
END_MAPPING_MEMBERS
int nStationCode{ 0 };
TYC szStationName1[128]{ 0 };
TYC szStationName2[128]{ 0 };
TYC szDesc[256]{ 0 };
int nOrder{ 1 };
int nDurNextBM{ 0 };
int nDurNextEN{ 0 };
int nDurArrivingBM{ 0 };
int nDurArrivingEN{ 0 };
int nDurArrivalBM{ 0 };
int nDurArrivalEN{ 0 };
int nDurExchangeBM{ 0 };
int nDurExchangeEN{ 0 };
int nHasExchange{ 0 };
int nIsProVisional{ 0 };
int nApprPaDistance{ 0 };
int nSpare1{ 0 };
int nSpare2{ 0 };
END_CLASS_FROM_SQLDATA
DECLARE_EDITOR_CLASS(StationInformation);
// !StationInformation

// StationDistance
BEGIN_CLASS_FROM_SQLDATA(StationDistance, , );
COMMON_VAL_FOR_SQLDATA;
DECLARE_TYPESETTINGS(8);
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC;
BEGIN_MAPPING_MEMBERS
m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
m_tSettings[1].POINTER = (void*)(&nDepartStn);
m_tSettings[2].POINTER = (void*)(&nArrivalStn);
m_tSettings[3].POINTER = (void*)(&nDistance);
m_tSettings[4].POINTER = (void*)(szDesc);
m_tSettings[5].POINTER = (void*)(&nOrder);
m_tSettings[6].POINTER = (void*)(&nDepCode);
m_tSettings[7].POINTER = (void*)(&nArrCode);
END_MAPPING_MEMBERS
int nDepartStn{ 0 };
int nArrivalStn{ 0 };
int nDistance{ 999 };
TYC szDesc[256]{ 0 };
int nOrder{ 1 };
int nDepCode{-1};
int nArrCode{-1};
END_CLASS_FROM_SQLDATA;
DECLARE_EDITOR_CLASS(StationDistance)
// !StationDistance

// StopPtnHeader
BEGIN_CLASS_FROM_SQLDATA_WITH_CHILDS(StopPtnHeader, , , 1);
COMMON_VAL_FOR_SQLDATA;
DECLARE_TYPESETTINGS(7);
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC;
BEGIN_MAPPING_MEMBERS
m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
m_tSettings[1].POINTER = (void*)(&nDepartStnIndex);
m_tSettings[2].POINTER = (void*)(&nArrivalStnIndex);
m_tSettings[3].POINTER = (void*)(szDesc);
m_tSettings[4].POINTER = (void*)(&nRelatedLineMapIndex);
m_tSettings[5].POINTER = (void*)(&nOrder);
m_tSettings[6].POINTER = (void*)(&nBound);
END_MAPPING_MEMBERS
int nDepartStnIndex{ 0 };
int nArrivalStnIndex{ 0 };
TYC szDesc[256]{ 0 };
int nRelatedLineMapIndex{ 0 };
int nOrder{ 1 };
int nBound{ 0 };
END_CLASS_FROM_SQLDATA
DECLARE_EDITOR_CLASS(StopPtnHeader);
// !StopPtnHeader

// StopPtnRoutes
BEGIN_CLASS_FROM_SQLDATA_WITH_CHILDS(StopPtnRoutes, , , 0);
COMMON_VAL_FOR_SQLDATA;
DECLARE_TYPESETTINGS(13);
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC;
BEGIN_MAPPING_MEMBERS
m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
m_tSettings[1].POINTER = (void*)(&nParentIndex);
m_tSettings[2].POINTER = (void*)(&nOrder);
m_tSettings[3].POINTER = (void*)(&nDistIndex);
m_tSettings[4].POINTER = (void*)(&nDestIndexLED);
m_tSettings[5].POINTER = (void*)(&nDoorDirection);
m_tSettings[6].POINTER = (void*)(&nDestIndexLCD);
m_tSettings[7].POINTER = (void*)(&nDCVoiceIndex);
m_tSettings[8].POINTER = (void*)(&nDCVideoIndex);
m_tSettings[9].POINTER = (void*)(&nDCDRMIndex);
m_tSettings[10].POINTER = (void*)(&nDOVoiceIndex);
m_tSettings[11].POINTER = (void*)(&nDOVideoIndex);
m_tSettings[12].POINTER = (void*)(&nDODRMIndex);
END_MAPPING_MEMBERS
// db field
int nParentIndex{ 0 };
int nOrder{ 1 };
int nDistIndex{ 0 };
int nDestIndexLED{ 0 };
int nDoorDirection{ 0 };
int nDestIndexLCD{ 0 };
int nDCVoiceIndex{ 0 };
int nDCVideoIndex{ 0 };
int nDCDRMIndex{ 0 };
int nDOVoiceIndex{ 0 };
int nDOVideoIndex{ 0 };
int nDODRMIndex{ 0 };
// !db field
int nDistance{ 0 };
int nRouteDistance{ 0 };
int nArrStnIndex{ 0 };
int nDepStnIndex{ 0 };
int nDepStnCode{ 0 };
int nArrStnCode{ 0 };
bool bDepSkipped{ false };       //Is departure station skipped?
bool bArrSkipped{ false };       //Is arrival station skipped?
END_CLASS_FROM_SQLDATA
DECLARE_EDITOR_CLASS(StopPtnRoutes);
// !StopPtnRoutes

// PIDContents
BEGIN_CLASS_FROM_SQLDATA_WITH_CHILDS(PIDContents, , , 1);
COMMON_VAL_FOR_SQLDATA;
DECLARE_TYPESETTINGS(10);
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC;
BEGIN_MAPPING_MEMBERS
m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
m_tSettings[1].POINTER = (void*)(szDesc);
m_tSettings[2].POINTER = (void*)(&nMsgID);
m_tSettings[3].POINTER = (void*)(&nType);
m_tSettings[4].POINTER = (void*)(&nStationIndex);
m_tSettings[5].POINTER = (void*)(&nDestIndex);
m_tSettings[6].POINTER = (void*)(&nMessageTypeID);
m_tSettings[7].POINTER = (void*)(&nInternalIndex);
m_tSettings[8].POINTER = (void*)(&nOrder);
m_tSettings[9].POINTER = (void*)(&nDevType);
END_MAPPING_MEMBERS
TYC szDesc[256]{ 0 }; // title
int nMsgID{ 0 };
int nType{ 0 }; // msg type
int nStationIndex{ 0 };
int nDestIndex{ 0 };
int nMessageTypeID{ 0 };
int nInternalIndex{ 0 };
int nOrder{ 1 };
int nDevType{ 0 };
END_CLASS_FROM_SQLDATA
DECLARE_EDITOR_CLASS(PIDContents);
// !PIDContents

// PIDIndexList
BEGIN_CLASS_FROM_SQLDATA(PIDIndexList, , );
COMMON_VAL_FOR_SQLDATA;
DECLARE_TYPESETTINGS(4);
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC;
BEGIN_MAPPING_MEMBERS
m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
m_tSettings[1].POINTER = (void*)(&nParents);
m_tSettings[2].POINTER = (void*)(&nOrder);
m_tSettings[3].POINTER = (void*)(&nContentsPoolIndex);
END_MAPPING_MEMBERS
int nParents{ 0 };
int nOrder{ 0 };
int nContentsPoolIndex{ 0 }; // diplay pool index
END_CLASS_FROM_SQLDATA
DECLARE_EDITOR_CLASS(PIDIndexList);
// !PIDIndexList

// AudioStationName
BEGIN_CLASS_FROM_SQLDATA(AudioStationName, , );
COMMON_VAL_FOR_SQLDATA;
DECLARE_TYPESETTINGS(9);
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC;
BEGIN_MAPPING_MEMBERS
m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
m_tSettings[1].POINTER = (void*)(&nOrder);
m_tSettings[2].POINTER = (void*)(&nMsgID);
m_tSettings[3].POINTER = (void*)(&nAudioIdx1);
m_tSettings[4].POINTER = (void*)(szFileName1);
m_tSettings[5].POINTER = (void*)(&nStnDuration1);
m_tSettings[6].POINTER = (void*)(&nAudioIdx2);
m_tSettings[7].POINTER = (void*)(szFileName2);
m_tSettings[8].POINTER = (void*)(&nStnDuration2);
END_MAPPING_MEMBERS
int nOrder{ 1 };
int nMsgID{ 0 };
int nAudioIdx1{ 0 };
int nAudioIdx2{ 0 };
int nStnDuration1{ 0 };
int nStnDuration2{ 0 };
TYC szFileName1[128]{ 0 };
TYC szFileName2[128]{ 0 };
END_CLASS_FROM_SQLDATA
DECLARE_EDITOR_CLASS(AudioStationName);
// !AudioStationName

// AudioPlayList
BEGIN_CLASS_FROM_SQLDATA(AudioPlayList, , );
COMMON_VAL_FOR_SQLDATA;
DECLARE_TYPESETTINGS(22);
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC;
BEGIN_MAPPING_MEMBERS
m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
m_tSettings[1].POINTER = (void*)(&nOrder);
m_tSettings[2].POINTER = (void*)(&nMsgID);
m_tSettings[3].POINTER = (void*)(&nPlayCount);
m_tSettings[4].POINTER = (void*)(&nWithBell);
m_tSettings[5].POINTER = (void*)(&nBellIdx);
m_tSettings[6].POINTER = (void*)(szBellName);
m_tSettings[7].POINTER = (void*)(&nBellDur);
m_tSettings[8].POINTER = (void*)(&nWithStation);
m_tSettings[9].POINTER = (void*)(&nFileIdx1);
m_tSettings[10].POINTER = (void*)(szFileName1);
m_tSettings[11].POINTER = (void*)(&nFileDur1);
m_tSettings[12].POINTER = (void*)(&nFileIdx2);
m_tSettings[13].POINTER = (void*)(szFileName2);
m_tSettings[14].POINTER = (void*)(&nFileDur2);
m_tSettings[15].POINTER = (void*)(&nFileIdx3);
m_tSettings[16].POINTER = (void*)(szFileName3);
m_tSettings[17].POINTER = (void*)(&nFileDur3);
m_tSettings[18].POINTER = (void*)(&nFileIdx4);
m_tSettings[19].POINTER = (void*)(szFileName4);
m_tSettings[20].POINTER = (void*)(&nFileDur4);
m_tSettings[21].POINTER = (void*)(szDesc);
END_MAPPING_MEMBERS
int nOrder{ 1 };
int nMsgID{ 0 };
int nPlayCount{ 0 };
int nWithBell{ 0 };
int nWithStation{ 0 };
int nBellIdx{ 0 };
int nBellDur{ 0 };
TYC szBellName[128]{ 0 };
int nFileIdx1{ 0 };
int nFileIdx2{ 0 };
int nFileIdx3{ 0 };
int nFileIdx4{ 0 };
int nFileDur1{ 0 };
int nFileDur2{ 0 };
int nFileDur3{ 0 };
int nFileDur4{ 0 };
TYC szFileName1[128]{ 0 };
TYC szFileName2[128]{ 0 };
TYC szFileName3[128]{ 0 };
TYC szFileName4[128]{ 0 };
TYC szDesc[128]{ 0 };
END_CLASS_FROM_SQLDATA
DECLARE_EDITOR_CLASS(AudioPlayList);
// !AudioPlayList

// VideoDeviceGroup
BEGIN_CLASS_FROM_SQLDATA_WITH_CHILDS(VideoDeviceGroup, , , 1);
COMMON_VAL_FOR_SQLDATA;
DECLARE_TYPESETTINGS(5);
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC;
BEGIN_MAPPING_MEMBERS
m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
m_tSettings[1].POINTER = (void*)(&nOrder);
m_tSettings[2].POINTER = (void*)(&nDevType);
m_tSettings[3].POINTER = (void*)(&nGroupID);
m_tSettings[4].POINTER = (void*)(szDesc);
END_MAPPING_MEMBERS
int nOrder{ 1 };
int nDevType{ 0 };
int nGroupID{ 0 };
TYC szDesc[256]{ 0 };
END_CLASS_FROM_SQLDATA
DECLARE_EDITOR_CLASS(VideoDeviceGroup);
// !VideoDeviceGroup

// VideoPlayList
BEGIN_CLASS_FROM_SQLDATA(VideoPlayList, , );
COMMON_VAL_FOR_SQLDATA;
DECLARE_TYPESETTINGS(7);
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC;
BEGIN_MAPPING_MEMBERS
m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
m_tSettings[1].POINTER = (void*)(&nParents);
m_tSettings[2].POINTER = (void*)(&nOrder);
m_tSettings[3].POINTER = (void*)(&nVideoIndex);
m_tSettings[4].POINTER = (void*)(szFileName);
m_tSettings[5].POINTER = (void*)(szDesc);
m_tSettings[6].POINTER = (void*)(&nDevType);
END_MAPPING_MEMBERS
int nParents{ 0 };
int nOrder{ 1 };
int nVideoIndex{ 0 };
TYC szDesc[256]{ 0 };
TYC szFileName[256]{ 0 };
int nDevType{ 0 };
END_CLASS_FROM_SQLDATA;
DECLARE_EDITOR_CLASS(VideoPlayList);
// !VideoPlayList

// EditorTagTable
BEGIN_CLASS_FROM_SQLDATA(EditorTagTable, , );
COMMON_VAL_FOR_SQLDATA;
DECLARE_TYPESETTINGS(5);
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC;
BEGIN_MAPPING_MEMBERS
m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
m_tSettings[1].POINTER = (void*)(szDesc);
m_tSettings[2].POINTER = (void*)(&nVariable);
m_tSettings[3].POINTER = (void*)(&nOrder);
m_tSettings[4].POINTER = (void*)(&nGifFrame);
END_MAPPING_MEMBERS
TYC szDesc[128]{ 0 }; // title
int nVariable{ 0 }; // tag type
int nOrder{ 1 };
int nGifFrame{ 0 };
END_CLASS_FROM_SQLDATA
DECLARE_EDITOR_CLASS(EditorTagTable);
// !EditorTagTable

// OPDataVersion
BEGIN_CLASS_FROM_SQLDATA(OPDataVersion, , );
COMMON_VAL_FOR_SQLDATA;
DECLARE_TYPESETTINGS(5);
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC;
BEGIN_MAPPING_MEMBERS
m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
m_tSettings[1].POINTER = (void*)(szVersion);
m_tSettings[2].POINTER = (void*)(&nVer1);
m_tSettings[3].POINTER = (void*)(&nVer2);
m_tSettings[4].POINTER = (void*)(&nVer3);
END_MAPPING_MEMBERS
TYC szVersion[32]{ 0 }; // title
int nVer1{ 0 };
int nVer2{ 0 };
int nVer3{ 0 };

END_CLASS_FROM_SQLDATA
DECLARE_EDITOR_CLASS(OPDataVersion);
// !OPDataVersion

struct findStationNameCode : public std::unary_function<SHARED_PTRC(CSQLData), bool>
{
	findStationNameCode(int nCode)
		:m_nCode(nCode)
	{

	}
	bool operator ()(SHARED_PTRC(CSQLData) &p)
	{
		StationInformation *c = dynamic_cast<StationInformation*>(p.get());
		return (c->nStationCode == m_nCode);
		//return (p->nStationCode == m_nIndex);
	}
private:
	int m_nCode;
};

struct findStationNameCodeByTableOrder : public std::unary_function<SHARED_PTRC(CSQLData), bool>
{
	findStationNameCodeByTableOrder(int order)
		:m_nOrder(order)
	{

	}
	bool operator ()(SHARED_PTRC(CSQLData) &p)
	{
		StationInformation *c = dynamic_cast<StationInformation*>(p.get());
		return (c->nOrder == m_nOrder);
	}
private:
	int m_nOrder;
};

struct findStationNameCodeByTableIndex : public std::unary_function<SHARED_PTRC(CSQLData), bool>
{
	findStationNameCodeByTableIndex(int nIndex)
		:m_nIndex(nIndex)
	{

	}
	bool operator ()(SHARED_PTRC(CSQLData) &p)
	{
		StationInformation *c = dynamic_cast<StationInformation*>(p.get());
		return (c->m_nTableIndex == m_nIndex);
	}
private:
	int m_nIndex;
};

struct findStationNameOrder : public std::unary_function<SHARED_PTRC(CSQLData), bool>
{
	findStationNameOrder(int nOrder)
		:m_nOrder(nOrder)
	{

	}
	bool operator ()(SHARED_PTRC(CSQLData) &p)
	{
		StationInformation *c = dynamic_cast<StationInformation*>(p.get());
		return (c->nOrder == m_nOrder);
		//return (p->nStationCode == m_nIndex);
	}
private:
	int m_nOrder;
};

struct findDistanceDepartureCode : public std::unary_function<SHARED_PTRC(CSQLData), bool>
{
	findDistanceDepartureCode(int dep, int arr)
		:m_nDepCode(dep), m_nArrCode(arr)
	{

	}
	bool operator ()(SHARED_PTRC(CSQLData) &p)
	{
		auto *c = dynamic_cast<StationDistance*>(p.get());
		return (c->nDepCode == m_nDepCode && c->nArrCode == m_nArrCode);
	}
private:
	int m_nDepCode;
	int m_nArrCode;
};

struct findDeviceTypeByIndex : public std::unary_function<SHARED_PTRC(CSQLData), bool>
{
	findDeviceTypeByIndex(int idx) : m_idx(idx)
	{

	}
	bool operator()(SHARED_PTRC(CSQLData) &p)
	{
		auto *c = dynamic_cast<VideoDeviceGroup*>(p.get());
		return(c->m_nTableIndex == m_idx);
	}
private:
	int m_idx;
};

struct findTagValuebyTagIndex : public std::unary_function<SHARED_PTRC(CSQLData), bool>
{
	findTagValuebyTagIndex(int idx) : m_idx(idx)
	{

	}
	bool operator()(SHARED_PTRC(CSQLData) &p)
	{
		auto *c = dynamic_cast<EditorTagTable*>(p.get());
		return(c->m_nTableIndex == m_idx);
	}
private:
	int m_idx;
};