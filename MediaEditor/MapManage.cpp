#include "MapManage.h"
#include <qdebug.h>

MAPPARAM gImageType[] =
{
	{0,L""},
	{1,L"Text Pool"},
	{2,L"Bitmap Pool"},
};

MAPPARAM gAlignOrigin[] =
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

wchar_t *g_szDisplayMode[] = { L"Paging Mode",L"Scroll Mode" };
wchar_t *g_szHAlign[] = { L"AlignLeft",L"AlignHCenter",L"AlignRight" };
wchar_t *g_szVAlign[] = { L"AlignTop",L"AlignVCenter",L"AlignBottom" };

MAPPARAM gDisplayMode[] =
{
	{0,L"Paging Mode"},
	{1,L"Scroll Mode"},
};

MAPPARAM gDisplayItemType[] =
{
	{ 0,L"Display Item" },
	{ 1,L"Image List" },
};


MAPPARAM gVerticalAlign[] =
{
	{0,L"AlignTop"},
	{1,L"AlignVCenter"},
	{2,L"AlignBottom"},
};

MAPPARAM gHorizontalAlign[] =
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
	{ 12, L"GIF Animation"},
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
	{ 6,L"PID Pattern Test"},
	{ 7,L"Unused Station Icon"},
};

MAPPARAM gAudioType[] =
{
	{ 0,L"" },
	{ 1,L"Operational" },
	{ 2,L"Special" },
	{ 3,L"Emergency" },
};

MAPPARAM gYesOrNo[] =
{
	{ 0,L"No" },
	{ 1,L"Yes" },
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

MAPPARAM gBoundType[] =
{
	{0, L"North" },
	{1, L"South"},
	{2, L"-"},
};

MAPPARAM gDisplayMsgID[] =
{
	{ -1, L""},
	{ 0, L"Wait" },
	{ 1, L"Welcome" },
	{ 100, L"Next" },
	{ 200, L"Arrival" },
	{ 8886, L"Door Open" },
	{ 8887, L"Door Faulty" },
	{ 8889, L"Pattern Test" },
	{ 4000, L"Emergency 1" },
	{ 4001, L"Emergency 2" },
	{ 4002, L"Emergency 3" },
	{ 4003, L"Emergency 4" },
	{ 4004, L"Emergency 5" },
	{ 4005, L"Emergency 6" },
	{ 4006, L"Emergency 7" },
	{ 4007, L"Emergency 8" },
	{ 4008, L"Emergency 9" },
	{ 4009, L"Emergency 10" },
	{ 4010, L"Emergency 11" },
	{ 4011, L"Emergency 12" },
	{ 4012, L"Emergency 13" },
	{ 4013, L"Emergency 14" },
	{ 4014, L"Emergency 15" },
};

MAPPARAM gAudioMsgID[] =
{
	{ -1, L""},
	{ 1, L"Welcome" },
	{ 5000, L"Next BM" },
	{ 5500, L"Next EN" },
	{ 6000, L"Approaching BM" },
	{ 6500, L"Approaching EN" },
	{ 7000, L"Arrival BM" }, // 삭제 예정
	{ 7500, L"Arrival EN" }, // 삭제 예정
	{ 400, L"Door Open Left" },
	{ 401, L"Door Open Right" },
	{ 402, L"Door Open Both" },
	{ 2000, L"Final BM" },
	{ 2500, L"Final EN" },
	{ 1000, L"Final PH1 BM" },
	{ 1500, L"Final PH1 EN" },
	{ 900, L"Thank You" },
	{ 3000, L"Special 1" },
	{ 3001, L"Special 2" },
	{ 3002, L"Special 3" },
	{ 3003, L"Special 4" },
	{ 3004, L"Special 5" },
	{ 3005, L"Special 6" },
	{ 3006, L"Special 7" },
	{ 3007, L"Special 8" },
	{ 3008, L"Special 9" },
	{ 3009, L"Special 10" },
	{ 4000, L"Emergency 1" },
	{ 4001, L"Emergency 2" },
	{ 4002, L"Emergency 3" },
	{ 4003, L"Emergency 4" },
	{ 4004, L"Emergency 5" },
	{ 4005, L"Emergency 6" },
	{ 4006, L"Emergency 7" },
	{ 4007, L"Emergency 8" },
	{ 4008, L"Emergency 9" },
	{ 4009, L"Emergency 10" },
	{ 4010, L"Emergency 11" },
	{ 4011, L"Emergency 12" },
	{ 4012, L"Emergency 13" },
	{ 4013, L"Emergency 14" },
	{ 4014, L"Emergency 15" },
	{ 8101, L"Exchange BM 101" },
	{ 8601, L"Exchange EN 101" },
	{ 8104, L"Exchange BM 104" },
	{ 8604, L"Exchange EN 104" },
	{ 8108, L"Exchange BM 108" },
	{ 8608, L"Exchange EN 108" },
	{ 8113, L"Exchange BM 113" },
	{ 8613, L"Exchange EN 113" },
	{ 8117, L"Exchange BM 117" },
	{ 8617, L"Exchange EN 117" },
	{ 8120, L"Exchange BM 120" },
	{ 8620, L"Exchange EN 120" },
	{ 8123, L"Exchange BM 123" },
	{ 8623, L"Exchange EN 123" },
	{ 8124, L"Exchange BM 124" },
	{ 8624, L"Exchange EN 124" },
	{ 8129, L"Exchange BM 129" },
	{ 8629, L"Exchange EN 129" },
	{ 8141, L"Exchange BM 141" },
	{ 8641, L"Exchange EN 141" },
};

MAPPARAM gSpcEmgType[] =
{
	{0, L""},
	{ 2828, L"No Smoke, Eat, Drink" },
	{ 1004, L"Offer Seat" },
	{ 1005, L"Safety Children" },
	{ 1009, L"Move to Inner Space" },
	{ 4321, L"Disembark" },
	{ 5959, L"Resumre Normal OP" },
	{ 1357, L"Emergency Brake" },
	{ 5432, L"Resume Journey" },
	{ 4885, L"Skip Station" },
	{ 1111, L"Evacu M1" },
	{ 2222, L"Evacu M2" },
	{ 8282, L"Leaving Train" },
	{ 6016, L"Holding at Station" },
	{ 1122, L"Change Train" },
	{ 5555, L"Delayed Train Service" },
	{ 5556, L"Train Halt" },
	{ 9090, L"Out of Service" },
	{ 4444, L"Power Failure" },
	{ 7878, L"Intrusion" },
	{ 9911, L"Techincal Diff" },
	{ 1199, L"Rescue" },
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
	for (int i = 0; i < (sizeof(gImageType) / sizeof(gImageType[0])); i++)
	{
		m_mImageType[gImageType[i].nValue] = std::wstring(gImageType[i].szFieldName);
	}

	for (int i = 0; i < (sizeof(gAlignOrigin) / sizeof(gAlignOrigin[0])); i++)
	{
		m_mAlignType[gAlignOrigin[i].nValue] = std::wstring(gAlignOrigin[i].szFieldName);
	}

	for (int i = 0; i < (sizeof(gVerticalAlign) / sizeof(gVerticalAlign[0])); i++)
	{
		m_mVerticalAlign[gVerticalAlign[i].nValue] = std::wstring(gVerticalAlign[i].szFieldName);
	}

	for (int i = 0; i < (sizeof(gHorizontalAlign) / sizeof(gHorizontalAlign[0])); i++)
	{
		m_mHorizontalAlign[gHorizontalAlign[i].nValue] = std::wstring(gHorizontalAlign[i].szFieldName);
	}

	for (int i = 0; i < (sizeof(gDisplayMode) / sizeof(gDisplayMode[0])); i++)
	{
		m_mDisplayMode[gDisplayMode[i].nValue] = std::wstring(gDisplayMode[i].szFieldName);
	}

	for (int i = 0; i < (sizeof(gDisplayItemType) / sizeof(gDisplayItemType[0])); i++)
	{
		m_mDisplayItemType[gDisplayItemType[i].nValue] = std::wstring(gDisplayItemType[i].szFieldName);
	}

	for (int i = 0; i < (sizeof(gTransistionType) / sizeof(gTransistionType[0])); i++)
	{
		m_mTransistionType[gTransistionType[i].nValue] = std::wstring(gTransistionType[i].szFieldName);
	}

	for (int i = 0; i < (sizeof(gDoorOpenDirection) / sizeof(gDoorOpenDirection[0])); i++)
	{
		m_mDoorOpenDirection[gDoorOpenDirection[i].nValue] = std::wstring(gDoorOpenDirection[i].szFieldName);
	}

	for (int i = 0; i < (sizeof(gMappingVariables) / sizeof(gMappingVariables[0])); i++)
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

	for (int i = 0; i < (sizeof(gDevTypes) / sizeof(gDevTypes[0])); i++)
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

	for (int i = 0; i < (sizeof(gYesOrNo) / sizeof(gYesOrNo[0])); i++)
	{
		m_mYesOrNo[gYesOrNo[i].nValue] = std::wstring(gYesOrNo[i].szFieldName);
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

	for (int i = 0; i < (sizeof(gBoundType) / sizeof(gBoundType[0])); i++)
	{
		m_mBoundType[gBoundType[i].nValue] = std::wstring(gBoundType[i].szFieldName);
	}

	for (int i = 0; i < (sizeof(gDisplayMsgID) / sizeof(gDisplayMsgID[0])); i++)
	{
		m_mDisplayMsgID[gDisplayMsgID[i].nValue] = std::wstring(gDisplayMsgID[i].szFieldName);
	}

	for (int i = 0; i < (sizeof(gAudioMsgID) / sizeof(gAudioMsgID[0])); i++)
	{
		m_mAudioMsgID[gAudioMsgID[i].nValue] = std::wstring(gAudioMsgID[i].szFieldName);
	}

	for (int i = 0; i < (sizeof(gSpcEmgType) / sizeof(gSpcEmgType[0])); i++)
	{
		m_mSpcEmgType[gSpcEmgType[i].nValue] = std::wstring(gSpcEmgType[i].szFieldName);
	}
}
