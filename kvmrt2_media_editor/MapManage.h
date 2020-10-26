#pragma once
#include <string>
#include <map>

typedef struct _MAPPARAM
{
	int nValue;
	wchar_t szFieldName[64];
}MAPPARAM, *LPMAPPARAM;



class CMapManage
{
public:
	CMapManage(void);
	~CMapManage(void);

	static CMapManage *GetInstance();

	void InitMaps();
	std::map<int, std::wstring> m_mImageType;
	std::map<int, std::wstring> m_mAlignType;
	std::map<int, std::wstring> m_mVerticalAlign;
	std::map<int, std::wstring> m_mHorizontalAlign;
	std::map<int, std::wstring> m_mDisplayMode;
	std::map<int, std::wstring> m_mDisplayItemType;
	std::map<int, std::wstring> m_mTransistionType;
	std::map<int, std::wstring> m_mDoorOpenDirection;
	std::map<int, std::wstring> m_mMappingVariables;
	std::map<int, std::wstring> m_mMessageTypes;
	std::map<int, std::wstring> m_mEventTypes;
	std::map<int, std::wstring> m_mDevTypes;
	std::map<int, std::wstring> m_mDistanceTypes;
	std::map<int, std::wstring> m_mDisplayPoolType;
	std::map<int, std::wstring> m_mAudioType;
	std::map<int, std::wstring> m_mPlayWithStnName;
	std::map<int, std::wstring> m_mVideoDevice;
	std::map<int, std::wstring> m_mVideoGroup;
	std::map<int, std::wstring> m_mImageIndexListType;
	std::map<int, std::wstring> m_mStopPtnMode;
	
};
