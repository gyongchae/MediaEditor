#include "MapManage.h"
#include <qdebug.h>

MAPPARAM gImageType[]=
{
	{0,L""},
	{1,L"Text Pool"},
	{2,L"Bitmap Pool"},
};

MAPPARAM gAlignOrigin[]=
{
	{0,L""},
	{1,L"LEFT TOP"},
	{2,L"CENTER TOP"},
	{3,L"RIGHT TOP"},
	{4,L"LEFT MIDDLE"},
	{5,L"CENTER MIDDLE"},
	{6,L"RIGHT MIDDLE"},
	{7,L"LEFT BOTTOM"},
	{8,L"CENTER BOTTOM"},
	{9,L"RIGHT BOTTOM"},
};

wchar_t *g_szDisplayMode[]={L"Paging Mode",L"Scroll Mode"};
wchar_t *g_szHAlign[]={L"AlignLeft",L"AlignHCenter",L"AlignRight"};
wchar_t *g_szVAlign[]={L"AlignTop",L"AlignVCenter",L"AlignBottom"};

MAPPARAM gDisplayMode[]=
{
	{0,L"Paging Mode"},
	{1,L"Scroll Mode"},
};

MAPPARAM gDisplayItemType[] =
{
	{ 0,L"Display Item" },
	{ 1,L"Image List" },
};


MAPPARAM gVerticalAlign[]=
{
	{0,L"AlignTop"},
	{1,L"AlignVCenter"},
	{2,L"AlignBottom"},
};

MAPPARAM gHorizontalAlign[]=
{
	{0,L"AlignLeft"},
	{1,L"AlignHCenter"},
	{2,L"AlignRight"},
};


MAPPARAM gTransistionType[] =
{
	{ 0,L"Hold" },
	{ 1,L"Ramp" },
};



MAPPARAM gDoorOpenDirection[] =
{
	{ 0,L"" },
	{ 1,L"Left" },
	{ 2,L"Right" },
	{ 3,L"Forward" },
	{ 4,L"Backward" },
};

// 값 변경 시 MAL_PIDDRM 소스 void COperManage::initMappedValue()도 같이 변경 해야 함.
MAPPARAM gMappingVariables[] =
{
	{ 0, L"" },
	{ 1, L"Next station code" },			// use
	{ 2, L"Current station code" },			// use
	{ 3, L"Final station code" },		// use
	{ 4, L"Door opening side" },			// use
	{ 5, L"Evacuation Direction" },			// use
	{ 6, L"Day"},
	{ 7, L"Month"},
	{ 8, L"Year" },
	{ 9, L"Hour" },
	{ 10, L"Minute" },
	{ 11, L"Am/Pm"},
};


MAPPARAM gMessageTypes[] =
{
	{0,L""},
	{1,L"Normal" },
	{2,L"Special" },
	{3,L"Emergency" },
	{4,L"Opening"},
};


MAPPARAM gEventTypes[] =
{
	{ 0,L"Normal" },
	{ 1,L"Departure" },
	{ 2,L"Arrival" },
	{ 3,L"Special" },
};

MAPPARAM gDevTypes[] =
{
	{0,L""},
	{1,L"PID"},
	{2,L"DRMD"},
	{3,L"BOTH"},
};

MAPPARAM gDistanceType[] =
{
	{0,L"Start"},
	{1,L"Target"},
};

MAPPARAM gDisplayPoolType[] =
{
	{ 0,L"Fragment" },
	{ 1,L"DRMD Startup" },
	{ 2,L"PID Startup" },
	{ 3,L"Emergency"},
	{ 4,L"Operation"},
	{ 5,L"DRMD Pattern Test"},
	{ 6,L"PID Pattern Test"}
};

MAPPARAM gAudioType[] =
{
	{ 0,L"" },
	{ 1,L"Operational" },
	{ 2,L"Special" },
	{ 3,L"Emergency" },
};

MAPPARAM gPlayWithStnName[] =
{
	{ 0,L"" },
	{ 1,L"No" },
	{ 2,L"Yes" },
};

MAPPARAM gVideoDevice[] =
{
	{ 0,L"" },
	{ 1,L"DRMD" },
	{ 2,L"PID" },
};

MAPPARAM gVideoGroup[] =
{
	{ 0,L"DRMD" },
	{ 1,L"PID 1" },
	{ 2,L"PID 2" },
	{ 3,L"PID 3" },
};

MAPPARAM gImageIndexListType[] = 
{
	{ 0, L"Normal" },
	{ 1, L"Map Video Area" },
	{ 2, L"Tag Item" },
};

MAPPARAM gDateTimeDisplay[] =
{
	{0, L"No"},
	{1, L"Yes"},
};

MAPPARAM gStopPtnMode[] =
{
	{0, L"Operation"},
	{1, L"Simulation"},
};

CMapManage::CMapManage(void)
{
}

CMapManage::~CMapManage(void)
{
}


CMapManage *CMapManage::GetInstance()
{
	static CMapManage tMapManage;
	return &tMapManage;
}

void CMapManage::InitMaps()
{
	for(int i=0;i<(sizeof(gImageType)/sizeof(gImageType[0]));i++)
	{
		m_mImageType[gImageType[i].nValue]=std::wstring(gImageType[i].szFieldName);
	}

	for(int i=0;i<(sizeof(gAlignOrigin)/sizeof(gAlignOrigin[0]));i++)
	{
		m_mAlignType[gAlignOrigin[i].nValue]=std::wstring(gAlignOrigin[i].szFieldName);
	}

	for(int i=0;i<(sizeof(gVerticalAlign)/sizeof(gVerticalAlign[0]));i++)
	{
		m_mVerticalAlign[gVerticalAlign[i].nValue]=std::wstring(gVerticalAlign[i].szFieldName);
	}

	for(int i=0;i<(sizeof(gHorizontalAlign)/sizeof(gHorizontalAlign[0]));i++)
	{
		m_mHorizontalAlign[gHorizontalAlign[i].nValue]=std::wstring(gHorizontalAlign[i].szFieldName);
	}

	for(int i=0;i<(sizeof(gDisplayMode)/sizeof(gDisplayMode[0]));i++)
	{
		m_mDisplayMode[gDisplayMode[i].nValue]=std::wstring(gDisplayMode[i].szFieldName);
	}

	for (int i = 0; i<(sizeof(gDisplayItemType) / sizeof(gDisplayItemType[0])); i++)
	{
		m_mDisplayItemType[gDisplayItemType[i].nValue] = std::wstring(gDisplayItemType[i].szFieldName);
	}

	for (int i = 0; i<(sizeof(gTransistionType) / sizeof(gTransistionType[0])); i++)
	{
		m_mTransistionType[gTransistionType[i].nValue] = std::wstring(gTransistionType[i].szFieldName);
	}

	for (int i = 0; i<(sizeof(gDoorOpenDirection) / sizeof(gDoorOpenDirection[0])); i++)
	{
		m_mDoorOpenDirection[gDoorOpenDirection[i].nValue] = std::wstring(gDoorOpenDirection[i].szFieldName);
	}

	for (int i = 0; i<(sizeof(gMappingVariables) / sizeof(gMappingVariables[0])); i++)
	{
		m_mMappingVariables[gMappingVariables[i].nValue] = std::wstring(gMappingVariables[i].szFieldName);
	}

	for (int i = 0; i < (sizeof(gMessageTypes) / sizeof(gMessageTypes[0])); i++)
	{
		m_mMessageTypes[gMessageTypes[i].nValue] = std::wstring(gMessageTypes[i].szFieldName);
	}

	for (int i = 0; i < (sizeof(gEventTypes) / sizeof(gEventTypes[0])); i++)
	{
		m_mEventTypes[gEventTypes[i].nValue] = std::wstring(gEventTypes[i].szFieldName);
	}

	for (int i = 0; i<(sizeof(gDevTypes) / sizeof(gDevTypes[0])); i++)
	{
		m_mDevTypes[gDevTypes[i].nValue] = std::wstring(gDevTypes[i].szFieldName);
	}

	for (int i = 0; i < (sizeof(gDistanceType) / sizeof(gDistanceType[0])); i++)
	{
		m_mDistanceTypes[gDistanceType[i].nValue] = std::wstring(gDistanceType[i].szFieldName);
	}

	for (int i = 0; i < (sizeof(gDisplayPoolType) / sizeof(gDisplayPoolType[0])); i++)
	{
		m_mDisplayPoolType[gDisplayPoolType[i].nValue] = std::wstring(gDisplayPoolType[i].szFieldName);
	}

	for (int i = 0; i < (sizeof(gAudioType) / sizeof(gAudioType[0])); i++)
	{
		m_mAudioType[gAudioType[i].nValue] = std::wstring(gAudioType[i].szFieldName);
	}

	for (int i = 0; i < (sizeof(gPlayWithStnName) / sizeof(gPlayWithStnName[0])); i++)
	{
		m_mPlayWithStnName[gPlayWithStnName[i].nValue] = std::wstring(gPlayWithStnName[i].szFieldName);
	}

	for (int i = 0; i < (sizeof(gVideoDevice) / sizeof(gVideoDevice[0])); i++)
	{
		m_mVideoDevice[gVideoDevice[i].nValue] = std::wstring(gVideoDevice[i].szFieldName);
	}

	for (int i = 0; i < (sizeof(gVideoGroup) / sizeof(gVideoGroup[0])); i++)
	{
		m_mVideoGroup[gVideoGroup[i].nValue] = std::wstring(gVideoGroup[i].szFieldName);
	}

	for (int i = 0; i < (sizeof(gImageIndexListType) / sizeof(gImageIndexListType[0])); i++)
	{
		m_mImageIndexListType[gImageIndexListType[i].nValue] = std::wstring(gImageIndexListType[i].szFieldName);
	}

	for (int i = 0; i < (sizeof(gDateTimeDisplay) / sizeof(gDateTimeDisplay[0])); i++)
	{
		m_mDateTimeDisplay[gDateTimeDisplay[i].nValue] = std::wstring(gDateTimeDisplay[i].szFieldName);
	}
	for (int i = 0; i < (sizeof(gStopPtnMode) / sizeof(gStopPtnMode[0])); i++)
	{
		m_mStopPtnMode[gStopPtnMode[i].nValue] = std::wstring(gStopPtnMode[i].szFieldName);
	}
}