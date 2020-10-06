#include "DefineNormalTables.h"

DECLARE_STATIC_VARIABLES(StationInformation, false, STATION_INFORMATION, -1, 5, 0)
DECLARE_STATIC_TYPESETTINGS(StationInformation, 19) =
{
	{ TYPE_INTEGER,	MAKE_T("TABLE_INDEX"),			0,	nullptr,true,	false,	false,	MAKE_T("Table Index"),			100 },
	{ TYPE_INTEGER,	MAKE_T("STATION_CODE"),			0,	nullptr,false,	false,	false,	MAKE_T("Station Code"),			100 },
	{ TYPE_TEXT,	MAKE_T("STATION_NAME1"),		128,nullptr,false,	false,	false,	MAKE_T("Station Name"),			100 },
	{ TYPE_TEXT,	MAKE_T("STATION_NAME2"),		128,nullptr,false,	false,	false,	MAKE_T("Station Name2"),		100 },
	{ TYPE_TEXT,	MAKE_T("DESCRIPTION"),			256,nullptr,false,	false,	false,	MAKE_T("Description"),			100 },
	{ TYPE_INTEGER,	MAKE_T("TABLE_ORDER"),			0,	nullptr,false,	true,	false,	MAKE_T("Order"),				100 },
	{ TYPE_INTEGER,	MAKE_T("ROUTEMAP_STN_IDX"),		0,	nullptr,false,	false,	false,	MAKE_T("Route Map Station"),	100 },
	{ TYPE_INTEGER,	MAKE_T("ROUTEMAP_TRANSFER_IDX"),0,	nullptr,false,	false,	false,	MAKE_T("Route Map Transfer"),	100 },
	{ TYPE_INTEGER,	MAKE_T("DRM_CURR_STN_IDX"),		0,	nullptr,false,	false,	false,	MAKE_T("DRMD Current Station"),	100 },
	{ TYPE_INTEGER,	MAKE_T("DRM_NEXT_STN_IDX"),		0,	nullptr,false,	false,	false,	MAKE_T("DRMD Next Station"),	100 },
	{ TYPE_INTEGER,	MAKE_T("DRM_CURR_TANSFER_IDX"), 0,	nullptr,false,	false,	false,	MAKE_T("DRMD Current Transfer"),100 },
	{ TYPE_INTEGER,	MAKE_T("DRM_NEXT_TANSFER_IDX"), 0,	nullptr,false,	false,	false,	MAKE_T("DRMD Next Transfer"),	100 },
	{ TYPE_INTEGER,	MAKE_T("DRM_DESTINATION_IDX"),	0,	nullptr,false,	false,	false,	MAKE_T("DRMD Destination"),		100 },
	{ TYPE_INTEGER,	MAKE_T("PID_CURR_STN_IDX"),		0,	nullptr,false,	false,	false,	MAKE_T("PID Current Station"),	100 },
	{ TYPE_INTEGER,	MAKE_T("PID_NEXT_STN_IDX"),		0,	nullptr,false,	false,	false,	MAKE_T("PID Next Station"),		100 },
	{ TYPE_INTEGER,	MAKE_T("PID_CURR_TANSFER_IDX"), 0,	nullptr,false,	false,	false,	MAKE_T("PID Current Transfer"),	100 },
	{ TYPE_INTEGER,	MAKE_T("PID_NEXT_TANSFER_IDX"), 0,	nullptr,false,	false,	false,	MAKE_T("PID Next Transfer"),	100 },
	{ TYPE_INTEGER,	MAKE_T("PID_DESTINATION_IDX"),	0,	nullptr,false,	false,	false,	MAKE_T("PID Destination"),		100 },
	{ TYPE_INTEGER,	MAKE_T("LED_INDEX"),			0,	nullptr,false,	false,	false,	MAKE_T("FDI & SDI Indicator"),	100 },
};

DECLARE_STATIC_VARIABLES(StationDistance, false, STATION_DISTANCE, -1, 5, 0)
DECLARE_STATIC_TYPESETTINGS(StationDistance, 8) =
{
	{ TYPE_INTEGER,	MAKE_T("TABLE_INDEX"),		0,	nullptr,true, false,false, MAKE_T("Table Index"),		100 },
	{ TYPE_INTEGER,	MAKE_T("DEPARTURE_STATION"),0,	nullptr,false,false,false, MAKE_T("Departure Station"), 100 },
	{ TYPE_INTEGER,	MAKE_T("ARRIVAL_STATION"),	0,	nullptr,false,false,false, MAKE_T("Arrival Station"),	100 },
	{ TYPE_INTEGER,	MAKE_T("DISTANCE"),			0,	nullptr,false,false,false, MAKE_T("Distance"),			100 },
	{ TYPE_TEXT,	MAKE_T("DESC"),				256,nullptr,false,false,false, MAKE_T("Desc"),				100 },
	{ TYPE_INTEGER,	MAKE_T("TABLE_ORDER"),		0,	nullptr,false,true, false, MAKE_T("Order"),				100 },
	{ TYPE_INTEGER,	MAKE_T("DEPARTURE_CODE"),	0,	nullptr,false,false,false, MAKE_T("Departure Code"),	100 },
	{ TYPE_INTEGER,	MAKE_T("ARRIVAL_CODE"),		0,	nullptr,false,false,false, MAKE_T("Arrival Code"),		100 },
};

DECLARE_STATIC_VARIABLES(TrainNumber, false, TRAIN_NUMBER, -1, 7, 0)
DECLARE_STATIC_TYPESETTINGS(TrainNumber, 8) =
{
	{ TYPE_INTEGER,	MAKE_T("TABLE_INDEX"),			0,	nullptr,true, false,false, MAKE_T("Table Index"),			100 },
	{ TYPE_INTEGER,	MAKE_T("TRAIN_NUMBER_INDEX"),	0,	nullptr,false,false,false, MAKE_T("Train Number Index"),	100 },
	{ TYPE_INTEGER,	MAKE_T("DESTINATION_INDEX"),	0,	nullptr,false,false,false, MAKE_T("Destination Index"),		100 },
	{ TYPE_INTEGER,	MAKE_T("STOP_PATTERN_INDEX"),	0,	nullptr,false,false,false, MAKE_T("Stop Pattern Index"),	100 },
	{ TYPE_TEXT,	MAKE_T("TRAIN_NUMBER"),			128,nullptr,false,false,false, MAKE_T("Train Number"),			100 },
	{ TYPE_TEXT,	MAKE_T("TRAIN_NUMBER_PREFIX"),	64,	nullptr,false,false,false, MAKE_T("Train Number Prefix"),	100 },
	{ TYPE_INTEGER,	MAKE_T("UPDN_DIRECTION"),		0,	nullptr,false,false,false, MAKE_T("Direction"),				100 },
	{ TYPE_INTEGER,	MAKE_T("TABLE_ORDER"),			0,	nullptr,false,true, false, MAKE_T("Order"),					100 },

};

DECLARE_STATIC_VARIABLES(StopPtnHeader, false, STOP_PATTERN_HEADER, -1, 5, 0)
DECLARE_STATIC_TYPESETTINGS(StopPtnHeader, 7) =
{
	{ TYPE_INTEGER,	MAKE_T("TABLE_INDEX"),		0,	nullptr,true, false,false, MAKE_T("Table Index"),		100 },
	{ TYPE_INTEGER,	MAKE_T("DEPARTURE_STATION"),0,	nullptr,false,false,false, MAKE_T("Start Station"),		100 },
	{ TYPE_INTEGER,	MAKE_T("ARRIVAL_STATION"),	0,	nullptr,false,false,false, MAKE_T("Destination"),		100 },
	{ TYPE_TEXT,	MAKE_T("DESCRIPTION"),		256,nullptr,false,false,false, MAKE_T("Description"),		100 },
	{ TYPE_INTEGER,	MAKE_T("LINE_MAP_INDEX"),	0,	nullptr,false,false,false, MAKE_T("Route Map Index"),	100 },
	{ TYPE_INTEGER,	MAKE_T("TABLE_ORDER"),		0,	nullptr,false,true, false, MAKE_T("Order"),				100 },
	{ TYPE_INTEGER,	MAKE_T("DRIVE_MODE"),	0,	nullptr,false,false,false, MAKE_T("Drive Mode"),	100 },

};

DECLARE_STATIC_VARIABLES(StopPtnRoutes, false, STOP_PATTERN_ROUTES, 1, 2, 0)
DECLARE_STATIC_TYPESETTINGS(StopPtnRoutes, 13) =
{
	{ TYPE_INTEGER,MAKE_T("TABLE_INDEX"),			0,nullptr,true, false,false,	MAKE_T("Table Index"),					100 },
	{ TYPE_INTEGER,MAKE_T("PARENT_INDEX"),			0,nullptr,false,false,true,		MAKE_T("Parent Index"),					100 },
	{ TYPE_INTEGER,MAKE_T("TABLE_ORDER"),			0,nullptr,false,true, false,	MAKE_T("Order"),						100 },
	{ TYPE_INTEGER,MAKE_T("DISTANCE_INDEX"),		0,nullptr,false,false,false,	MAKE_T("Distance Index"),				100 },
	{ TYPE_INTEGER,MAKE_T("DESTINATION_INDEX_LED"),	0,nullptr,false,false,false,	MAKE_T("Destination Index(LED)"),		100 },
	{ TYPE_INTEGER,MAKE_T("DOOR_DIRECTION"),		0,nullptr,false,false,false,	MAKE_T("Door Direction"),				100 },
	{ TYPE_INTEGER,MAKE_T("DESTINATION_INDEX_LCD"),	0,nullptr,false,false,false,	MAKE_T("Destination Index(PID&DRMD)"),	100 },
	{ TYPE_INTEGER,MAKE_T("DOORCLOSE_VOICEEVENT"),	0,nullptr,false,false,false,	MAKE_T("Door Close Voice Event"),		100 },
	{ TYPE_INTEGER,MAKE_T("DOORCLOSE_VIDEOEVENT"),	0,nullptr,false,false,false,	MAKE_T("Door Close Video Event"),		100 },
	{ TYPE_INTEGER,MAKE_T("DOORCLOSE_DRMEVENT"),	0,nullptr,false,false,false,	MAKE_T("Door Close DRM Event"),			100 },
	{ TYPE_INTEGER,MAKE_T("DOOROPEN_VOICEEVENT"),	0,nullptr,false,false,false,	MAKE_T("Door Open Voice Event"),		100 },
	{ TYPE_INTEGER,MAKE_T("DOOROPEN_VIDEOEVENT"),	0,nullptr,false,false,false,	MAKE_T("Door Open Video Event"),		100 },
	{ TYPE_INTEGER,MAKE_T("DOOROPEN_DRMEVENT"),		0,nullptr,false,false,false,	MAKE_T("Door Open DRM Event"),			100 },
};

DECLARE_STATIC_VARIABLES(EventLists, false, EVENT_LISTS, 1, 5, 0)
DECLARE_STATIC_TYPESETTINGS(EventLists, 10) =
{
	{ TYPE_INTEGER,	MAKE_T("TABLE_INDEX"),		0,	nullptr,true, false,false,	MAKE_T("Table Index"),	100 },
	{ TYPE_INTEGER,	MAKE_T("PARENT_INDEX"),		0,	nullptr,false,false,true,	MAKE_T("Parent Index"), 100 },
	{ TYPE_INTEGER,	MAKE_T("DISTANCE"),			0,	nullptr,false,false,false,	MAKE_T("Distance"),		100 },
	{ TYPE_INTEGER,	MAKE_T("VOICE_EVENT_INDEX"),0,	nullptr,false,false,false,	MAKE_T("Audio Index"),	100 },
	{ TYPE_INTEGER,	MAKE_T("VIDEO_EVENT_INDEX"),0,	nullptr,false,false,false,	MAKE_T("PID Index"),	100 },
	{ TYPE_INTEGER,	MAKE_T("TABLE_ORDER"),		0,	nullptr,false,true, false,	MAKE_T("Order"),		100 },
	{ TYPE_TEXT,	MAKE_T("DESCRIPTION"),		256,nullptr,false,false,false,	MAKE_T("Description"),	100 },
	{ TYPE_INTEGER,	MAKE_T("DRM_EVENT_INDEX"),	0,	nullptr,false,false,false,	MAKE_T("DRMD Index"),	100 },
	{ TYPE_INTEGER,	MAKE_T("EVENT_TYPES"),		0,	nullptr,false,false,false,	MAKE_T("Event Type"),	100 },
	{ TYPE_INTEGER,	MAKE_T("DISTANCE_TYPES"),	0,	nullptr,false,false,false,	MAKE_T("Distance Type"),100 },
};

DECLARE_STATIC_VARIABLES(PIDContents, false, PID_CONTENTS, -1, 8, 0)
DECLARE_STATIC_TYPESETTINGS(PIDContents, 10) =
{
	{ TYPE_INTEGER,	MAKE_T("TABLE_INDEX"),		0,	nullptr,true, false,false, MAKE_T("Table Index"),		100 },
	{ TYPE_TEXT,	MAKE_T("DESCRIPTION"),		256,nullptr,false,false,false, MAKE_T("Title"),				100 },
	{ TYPE_INTEGER,	MAKE_T("MESSAGE_ID"),		0,	nullptr,false,false,false, MAKE_T("Message ID"),		100 },
	{ TYPE_INTEGER,	MAKE_T("MESSAGE_TYPE"),		0,	nullptr,false,false,false, MAKE_T("Message Type"),		100 },
	{ TYPE_INTEGER,	MAKE_T("STATION_INDEX"),	0,	nullptr,false,false,false, MAKE_T("Station Index"),		100 },
	{ TYPE_INTEGER,	MAKE_T("DESTINATION_INDEX"),0,	nullptr,false,false,false, MAKE_T("Destination Index"), 100 },
	{ TYPE_INTEGER,	MAKE_T("MESSAGE_TYPE_ID"),	0,	nullptr,false,false,false, MAKE_T("Message TypeID"),	100 },
	{ TYPE_INTEGER,	MAKE_T("INTERNAL_INDEX"),	0,	nullptr,false,false,false, MAKE_T("Internal Index"),	100 },
	{ TYPE_INTEGER,	MAKE_T("TABLE_ORDER"),		0,	nullptr,false,true, false, MAKE_T("Order"),				100 },
	{ TYPE_INTEGER,	MAKE_T("DEV_TYPE"),			0,	nullptr,false,false,false, MAKE_T("Device Type"),		100 },
};

DECLARE_STATIC_VARIABLES(PIDIndexList, false, PID_INDEX_LIST, 1, 2, 0)
DECLARE_STATIC_TYPESETTINGS(PIDIndexList, 4) =
{
	{ TYPE_INTEGER,MAKE_T("TABLE_INDEX"),			0,nullptr,true, false,false, MAKE_T("Table Index"), 100 },
	{ TYPE_INTEGER,MAKE_T("PARENT_INDEX"),			0,nullptr,false,false, true, MAKE_T("Parent Index"), 100 },
	{ TYPE_INTEGER,MAKE_T("TABLE_ORDER"),			0,nullptr,false,true, false, MAKE_T("Order"), 100 },
	{ TYPE_INTEGER,MAKE_T("CONTENTS_POOL_INDEX"),	0,nullptr,false,false,false, MAKE_T("Display Item Index"), 100 },
};

DECLARE_STATIC_VARIABLES(AudioStationName, false, STATION_NAME_AUDIO, -1, 1, 0)
DECLARE_STATIC_TYPESETTINGS(AudioStationName, 5) =
{
	{ TYPE_INTEGER,	MAKE_T("TABLE_INDEX"),	0,	nullptr,true, false,false, MAKE_T("Table Index"),	100 },
	{ TYPE_INTEGER,	MAKE_T("TABLE_ORDER"),	0,	nullptr,false,true, false, MAKE_T("Order"),			100 },
	{ TYPE_INTEGER,	MAKE_T("MESSAGE_ID"),	0,	nullptr,false,false,false, MAKE_T("Message ID"),	200 },
	{ TYPE_TEXT,	MAKE_T("FILE_NAME"),	128,nullptr,false,false,false, MAKE_T("File Name"),		400 },
	{ TYPE_TEXT,	MAKE_T("DESCRIPTION"),	128,nullptr,false,false,false, MAKE_T("Description"),	400 },
};

DECLARE_STATIC_VARIABLES(AudioTotal, false, TOTAL_AUDIO, -1, 1, 0)
DECLARE_STATIC_TYPESETTINGS(AudioTotal, 8) =
{
	{ TYPE_INTEGER,	MAKE_T("TABLE_INDEX"),	0,	nullptr,true, false,false, MAKE_T("Table Index"),		100 },
	{ TYPE_INTEGER,	MAKE_T("TABLE_ORDER"),	0,	nullptr,false,true, false, MAKE_T("Order"),				100 },
	{ TYPE_INTEGER,	MAKE_T("MESSAGE_ID"),	0,	nullptr,false,false,false, MAKE_T("Message ID"),		200 },
	{ TYPE_INTEGER,	MAKE_T("MESSAGE_TYPE"),	0,	nullptr,false,false,false, MAKE_T("Message Type"),		200 },
	{ TYPE_TEXT,	MAKE_T("BM_AUDIO_NAME"),128,nullptr,false,false,false, MAKE_T("Audio (BM)"),		400 },
	{ TYPE_TEXT,	MAKE_T("EN_AUDIO_NAME"),128,nullptr,false,false,false, MAKE_T("Audio (ENG)"),		400 },
	{ TYPE_INTEGER,	MAKE_T("TOTAL_COUNT"),	0,	nullptr,false,false,false, MAKE_T("Play with Station"), 200 },
	{ TYPE_TEXT,	MAKE_T("DESCRIPTION"),	128,nullptr,false,false,false, MAKE_T("Description"),		400 },
};

DECLARE_STATIC_VARIABLES(VideoDeviceGroup, false, VIDEO_DEVICE_GROUP, -1, 1, 0)
DECLARE_STATIC_TYPESETTINGS(VideoDeviceGroup, 5) =
{
	{ TYPE_INTEGER,	MAKE_T("TABLE_INDEX"),	0,	nullptr,true, false,false, MAKE_T("Table Index"),	100 },
	{ TYPE_INTEGER,	MAKE_T("TABLE_ORDER"),	0,	nullptr,false,true, false, MAKE_T("Order"),			100 },
	{ TYPE_INTEGER,	MAKE_T("DEVICE_TYPE"),	0,	nullptr,false,false,false, MAKE_T("Device Type"),	100 },
	{ TYPE_INTEGER,	MAKE_T("GROUP_ID"),		0,	nullptr,false,false,false, MAKE_T("Group ID"),		100 },
	{ TYPE_TEXT,	MAKE_T("DESCRIPTION"),	256,nullptr,false,false,false, MAKE_T("Description"),	100 },
};

DECLARE_STATIC_VARIABLES(VideoPlayList, false, VIDEO_PLAY_LIST, 1, 2, 0)
DECLARE_STATIC_TYPESETTINGS(VideoPlayList, 6) =
{
	{ TYPE_INTEGER,	MAKE_T("TABLE_INDEX"),	0,	nullptr,true, false,false,	MAKE_T("Table Index"),	100 },
	{ TYPE_INTEGER,	MAKE_T("PARENT_INDEX"),	0,	nullptr,false,false,true,	MAKE_T("Parent Index"), 100 },
	{ TYPE_INTEGER,	MAKE_T("TABLE_ORDER"),	0,	nullptr,false,true, false,	MAKE_T("Order"),		100 },
	{ TYPE_INTEGER,	MAKE_T("VIDEO_INDEX"),	0,	nullptr,false,false,false,	MAKE_T("Video Index"),	100 },
	{ TYPE_TEXT,	MAKE_T("FILE_NAME"),	256,nullptr,false,false,false,	MAKE_T("File Name"),	100 },
	{ TYPE_TEXT,	MAKE_T("DESCRIPTION"),	256,nullptr,false,false,false,	MAKE_T("Description"),	100 },
};

DECLARE_STATIC_VARIABLES(EditorTagTable, false, EDITOR_TAG_TABLE, -1, 3, 0)
DECLARE_STATIC_TYPESETTINGS(EditorTagTable, 4) =
{
	{ TYPE_INTEGER,	MAKE_T("TABLE_INDEX"),	0,	nullptr,true, false,false, MAKE_T("Table Index"),	100 },
	{ TYPE_TEXT,	MAKE_T("DESCRIPTION"),	128,nullptr,false,false,false, MAKE_T("Tag Name"),		100 },
	{ TYPE_INTEGER,	MAKE_T("VARIABLE"),		0,	nullptr,false,false,false, MAKE_T("Tag Type"),		100 },
	{ TYPE_INTEGER,	MAKE_T("TABLE_ORDER"),	0,	nullptr,false, true,false, MAKE_T("Order"),			100 },
};

DECLARE_STATIC_VARIABLES(OPDataVersion, false, VIDEOFILE_VERSION, -1, -1, 0)
DECLARE_STATIC_TYPESETTINGS(OPDataVersion, 5) =
{
	{ TYPE_INTEGER,	MAKE_T("TABLE_INDEX"),	 0,	 nullptr,true, false,false, MAKE_T("Table Index"),	100 },
	{ TYPE_TEXT,	MAKE_T("VERSION_STRING"),32,nullptr,false,false,false, MAKE_T("Data Version"), 100 },
	{ TYPE_INTEGER,	MAKE_T("VERSION_1"),0,nullptr,false,false,false, MAKE_T("Version1"), 100 },
	{ TYPE_INTEGER,	MAKE_T("VERSION_2"),0,nullptr,false,false,false, MAKE_T("Version2"), 100 },
	{ TYPE_INTEGER,	MAKE_T("VERSION_3"),0,nullptr,false,false,false, MAKE_T("Version3"), 100 },
};