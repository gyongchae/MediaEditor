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
m_tSettings[6].POINTER = (void*)(&nRouteMapStnIndex);
m_tSettings[7].POINTER = (void*)(&nRouteMapTransferIdx);
m_tSettings[8].POINTER = (void*)(&nDrmCurrStnIdx);
m_tSettings[9].POINTER = (void*)(&nDrmNextStnIdx);
m_tSettings[10].POINTER = (void*)(&nDrmCurrTransferIdx);
m_tSettings[11].POINTER = (void*)(&nDrmNextTransferIdx);
m_tSettings[12].POINTER = (void*)(&nDrmDestinationIdx);
m_tSettings[13].POINTER = (void*)(&nPidCurrStnIdx);
m_tSettings[14].POINTER = (void*)(&nPidNextStnIdx);
m_tSettings[15].POINTER = (void*)(&nPidCurrTransferIdx);
m_tSettings[16].POINTER = (void*)(&nPidNextTransferIdx);
m_tSettings[17].POINTER = (void*)(&nPidDestinationIdx);
m_tSettings[18].POINTER = (void*)(&nLedIndex);
END_MAPPING_MEMBERS
int nStationCode{ 0 };
TYC szStationName1[128]{ 0 };
TYC szStationName2[128]{ 0 };
TYC szDesc[256]{ 0 };
int nOrder{ 1 };
int nRouteMapStnIndex{ 0 };
int nRouteMapTransferIdx{ 0 };
int nDrmCurrStnIdx{ 0 };
int nDrmNextStnIdx{ 0 };
int nDrmCurrTransferIdx{ 0 };
int nDrmNextTransferIdx{ 0 };
int nDrmDestinationIdx{ 0 };
int nPidCurrStnIdx{ 0 };
int nPidNextStnIdx{ 0 };
int nPidCurrTransferIdx{ 0 };
int nPidNextTransferIdx{ 0 };
int nPidDestinationIdx{ 0 };
int nLedIndex{ 0 };
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

// TrainNumber
BEGIN_CLASS_FROM_SQLDATA(TrainNumber, , );
COMMON_VAL_FOR_SQLDATA;
DECLARE_TYPESETTINGS(8);
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC;
BEGIN_MAPPING_MEMBERS
m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
m_tSettings[1].POINTER = (void*)(&nTrainNumberIndex);
m_tSettings[2].POINTER = (void*)(&nDestinationIndex);
m_tSettings[3].POINTER = (void*)(&nStopPatternIndex);
m_tSettings[4].POINTER = (void*)(szTrainNumber);
m_tSettings[5].POINTER = (void*)(szTrainNumberPrefix);
m_tSettings[6].POINTER = (void*)(&nUpDnDirection);
m_tSettings[7].POINTER = (void*)(&nOrder);
END_MAPPING_MEMBERS
int nTrainNumberIndex{ 0 };
int nDestinationIndex{ 0 };
int nStopPatternIndex{ 0 };
int nUpDnDirection{ 0 };
TYC szTrainNumber[128]{ 0 };
TYC szTrainNumberPrefix[64]{ 0 };
int nOrder{ 1 };
END_CLASS_FROM_SQLDATA
DECLARE_EDITOR_CLASS(TrainNumber);
// !TrainNumber

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
m_tSettings[6].POINTER = (void*)(&nDriveMode);
END_MAPPING_MEMBERS
int nDepartStnIndex{ 0 };
int nArrivalStnIndex{ 0 };
TYC szDesc[256]{ 0 };
int nRelatedLineMapIndex{ 0 };
int nOrder{ 1 };
int nDriveMode{ 0 };
END_CLASS_FROM_SQLDATA
DECLARE_EDITOR_CLASS(StopPtnHeader);
// !StopPtnHeader

// StopPtnRoutes
BEGIN_CLASS_FROM_SQLDATA_WITH_CHILDS(StopPtnRoutes, , , 1);
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

// EventLists
BEGIN_CLASS_FROM_SQLDATA(EventLists, , );
COMMON_VAL_FOR_SQLDATA;
DECLARE_TYPESETTINGS(10);
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC;
BEGIN_MAPPING_MEMBERS
m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
m_tSettings[1].POINTER = (void*)(&nParentIndex);
m_tSettings[2].POINTER = (void*)(&nDistance);
m_tSettings[3].POINTER = (void*)(&nVoiceIndex);
m_tSettings[4].POINTER = (void*)(&nVideoIndex);
m_tSettings[5].POINTER = (void*)(&nOrder);
m_tSettings[6].POINTER = (void*)(szDesc);
m_tSettings[7].POINTER = (void*)(&nDRMIndex);
m_tSettings[8].POINTER = (void*)(&nEventType);
m_tSettings[9].POINTER = (void*)(&nDistanceType);
END_MAPPING_MEMBERS
// db fields
int nParentIndex{ 0 };
int nDistance{ 0 };
int nVoiceIndex{ 0 };
int nVideoIndex{ 0 };
int nOrder{ 1 };
TYC szDesc[256]{ 0 };
int nDRMIndex{ 0 };
int nEventType{ 0 };
int nDistanceType{ 0 };
// !db fields
int nRouteDistance{ 0 };
bool bRemoved{ false };
int nAppRouteDistance{ 0 };
END_CLASS_FROM_SQLDATA
DECLARE_EDITOR_CLASS(EventLists);
// !EventLists

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
DECLARE_TYPESETTINGS(5);
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC;
BEGIN_MAPPING_MEMBERS
m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
m_tSettings[1].POINTER = (void*)(&nOrder);
m_tSettings[2].POINTER = (void*)(&nMsgID);
m_tSettings[3].POINTER = (void*)(szFileName);
m_tSettings[4].POINTER = (void*)(szDesc);
END_MAPPING_MEMBERS
int nOrder{ 1 };
int nMsgID{ 0 };
TYC szFileName[128]{ 0 };
TYC szDesc[128]{ 0 };
END_CLASS_FROM_SQLDATA
DECLARE_EDITOR_CLASS(AudioStationName);
// !AudioStationName

// AudioTotal
BEGIN_CLASS_FROM_SQLDATA(AudioTotal, , );
COMMON_VAL_FOR_SQLDATA;
DECLARE_TYPESETTINGS(8);
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC;
BEGIN_MAPPING_MEMBERS
m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
m_tSettings[1].POINTER = (void*)(&nOrder);
m_tSettings[2].POINTER = (void*)(&nMsgID);
m_tSettings[3].POINTER = (void*)(&nMsgType);
m_tSettings[4].POINTER = (void*)(szFileBM);
m_tSettings[5].POINTER = (void*)(szFileEN);
m_tSettings[6].POINTER = (void*)(&nPlayCount);
m_tSettings[7].POINTER = (void*)(szDesc);
END_MAPPING_MEMBERS
int nOrder{ 1 };
int nMsgID{ 0 };
int nMsgType{ 0 };
TYC szFileBM[128]{ 0 };
TYC szFileEN[128]{ 0 };
int nPlayCount{ 0 };
TYC szDesc[128]{ 0 };
END_CLASS_FROM_SQLDATA
DECLARE_EDITOR_CLASS(AudioTotal);
// !AudioTotal

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
DECLARE_TYPESETTINGS(6);
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC;
BEGIN_MAPPING_MEMBERS
m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
m_tSettings[1].POINTER = (void*)(&nParents);
m_tSettings[2].POINTER = (void*)(&nOrder);
m_tSettings[3].POINTER = (void*)(&nVideoIndex);
m_tSettings[4].POINTER = (void*)(szFileName);
m_tSettings[5].POINTER = (void*)(szDesc);
END_MAPPING_MEMBERS
int nParents{ 0 };
int nOrder{ 1 };
int nVideoIndex{ 0 };
TYC szDesc[256]{ 0 };
TYC szFileName[256]{ 0 };
END_CLASS_FROM_SQLDATA;
DECLARE_EDITOR_CLASS(VideoPlayList);
// !VideoPlayList

// EditorTagTable
BEGIN_CLASS_FROM_SQLDATA(EditorTagTable, , );
COMMON_VAL_FOR_SQLDATA;
DECLARE_TYPESETTINGS(4);
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC;
BEGIN_MAPPING_MEMBERS
m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
m_tSettings[1].POINTER = (void*)(szDesc);
m_tSettings[2].POINTER = (void*)(&nVariable);
m_tSettings[3].POINTER = (void*)(&nOrder);
END_MAPPING_MEMBERS
TYC szDesc[128]{ 0 }; // title
int nVariable{ 0 }; // tag type
int nOrder{ 1 };
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

struct findTagNameByTagIndex : public std::unary_function<SHARED_PTRC(CSQLData), bool>
{
	findTagNameByTagIndex(int idx) : m_idx(idx)
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


