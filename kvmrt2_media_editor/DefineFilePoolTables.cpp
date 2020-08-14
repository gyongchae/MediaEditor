#include "DefineFilePoolTables.h"

DECLARE_STATIC_VARIABLES(AudioFilePool, false, AUDIO_FILE_POOL, -1, 6, 0)
DECLARE_STATIC_TYPESETTINGS(AudioFilePool, 7) =
{
	{ TYPE_INTEGER,	MAKE_T("TABLE_INDEX"),	0,	nullptr,true, false,false, MAKE_T("Table Index"),		100 },
	{ TYPE_INTEGER,	MAKE_T("FILE_CODE"),	0,	nullptr,false,false,false, MAKE_T("File Code"),			100 },
	{ TYPE_INTEGER,	MAKE_T("SPARE_CODE"),	0,	nullptr,false,false,false, MAKE_T("Spare Code"),		100 },
	{ TYPE_TEXT,	MAKE_T("FILE_NAME"),	256,nullptr,false,false,false, MAKE_T("Audio File Name"),	100 },
	{ TYPE_INTEGER,	MAKE_T("FILE_CRC"),		0,	nullptr,false,false,false, MAKE_T("CRC"),				100 },
	{ TYPE_INTEGER,	MAKE_T("FILE_SIZE"),	256,nullptr,false,false,false, MAKE_T("Size"),				100 },
	{ TYPE_INTEGER,	MAKE_T("TABLE_ORDER"),	0,	nullptr,false,true, false, MAKE_T("Order"),				100 },
};

DECLARE_STATIC_VARIABLES(VideoFilePool, false, VIDEO_FILE_POOL, -1, 6, 0)
DECLARE_STATIC_TYPESETTINGS(VideoFilePool, 7) =
{
	{ TYPE_INTEGER,	MAKE_T("TABLE_INDEX"),	0,	nullptr,true, false,false, MAKE_T("Table Index"),		100 },
	{ TYPE_INTEGER,	MAKE_T("FILE_CODE"),	0,	nullptr,false,false,false, MAKE_T("File Code"),			100 },
	{ TYPE_INTEGER,	MAKE_T("SPARE_CODE"),	0,	nullptr,false,false,false, MAKE_T("Spare Code"),		100 },
	{ TYPE_TEXT,	MAKE_T("FILE_NAME"),	256,nullptr,false,false,false, MAKE_T("Video File Name"),	100 },
	{ TYPE_INTEGER,	MAKE_T("FILE_CRC"),		0,	nullptr,false,false,false, MAKE_T("CRC"),				100 },
	{ TYPE_INTEGER,	MAKE_T("FILE_SIZE"),	256,nullptr,false,false,false, MAKE_T("Size"),				100 },
	{ TYPE_INTEGER,	MAKE_T("TABLE_ORDER"),	0,	nullptr,false,true, false, MAKE_T("Order"),				100 },

};

DECLARE_STATIC_VARIABLES(FontPool, false, FONT_POOL, -1, 5, 0)
DECLARE_STATIC_TYPESETTINGS(FontPool, 6) =
{
	{ TYPE_INTEGER,	MAKE_T("TABLE_INDEX"),	0,	nullptr,true, false,false, MAKE_T("Table Index"),	100 },
	{ TYPE_INTEGER,	MAKE_T("FILE_CODE"),	0,	nullptr,false,false,false, MAKE_T("File Code"),		100 },
	{ TYPE_INTEGER,	MAKE_T("SPARE_CODE"),	0,	nullptr,false,false,false, MAKE_T("Spare Code"),	100 },
	{ TYPE_TEXT,	MAKE_T("FILE_NAME"),	128,nullptr,false,false,false, MAKE_T("File Name"),		100 },
	{ TYPE_TEXT,	MAKE_T("FONT_FACE"),	128,nullptr,false,false,false, MAKE_T("Font Name"),		100 },
	{ TYPE_INTEGER,	MAKE_T("TABLE_ORDER"),	0,	nullptr,false,true, false, MAKE_T("Order"),			100 },
};

DECLARE_STATIC_VARIABLES(StationImagePool, true, STATION_IMAGE_POOL, -1, 14, 0)
DECLARE_STATIC_TYPESETTINGS(StationImagePool, 16) =
{
	{ TYPE_INTEGER,		MAKE_T("TABLE_INDEX"),	0,	nullptr,true, false,false, MAKE_T("Table Index"),	100 },
	{ TYPE_INTEGER,		MAKE_T("BITMAP_TYPE"),	0,	nullptr,false,false,false, MAKE_T("Bitmap Type"),	100 },
	{ TYPE_TEXT,		MAKE_T("FILE_NAME"),	256,nullptr,false,false,false, MAKE_T("Contents"),		100 },
	{ TYPE_INTEGER,		MAKE_T("FONT_INDEX"),	0,	nullptr,false,false,false, MAKE_T("Font Index"),	100 },
	{ TYPE_INTEGER,		MAKE_T("FONT_SIZE"),	0,	nullptr,false,false,false, MAKE_T("Font Size"),		100 },
	{ TYPE_INTEGER,		MAKE_T("FONT_ATTRIB"),	0,	nullptr,false,false,false, MAKE_T("Font Attrib"),	100 },
	{ TYPE_INTEGER,		MAKE_T("WIDTH_LiMIT"),	0,	nullptr,false,false,false, MAKE_T("Width Limit"),	100 },
	{ TYPE_INTEGER,		MAKE_T("HEIGHT_LIMIT"),	0,	nullptr,false,false,false, MAKE_T("Heigth Limit"),	100 },
	{ TYPE_INTEGER,		MAKE_T("ACTUAL_WIDTH"),	0,	nullptr,false,false,false, MAKE_T("Actual Width"),	100 },
	{ TYPE_INTEGER,		MAKE_T("ACTUAL_HEIGHT"),0,	nullptr,false,false,false, MAKE_T("Actual Heigth"), 100 },
	{ TYPE_INTEGER,		MAKE_T("PROPERTY1"),	0,	nullptr,false,false,false, MAKE_T("Property1"),		100 },
	{ TYPE_INTEGER,		MAKE_T("PROPERTY2"),	0,	nullptr,false,false,false, MAKE_T("Property2"),		100 },
	{ TYPE_DATALENGTH,	MAKE_T("DATALENGTH"),	0,	nullptr,false,false,false, MAKE_T("Data Length"),	100 },
	{ TYPE_DATA,		MAKE_T("DATAPOINTER"),	0,	nullptr,false,false,false, MAKE_T("Data Pointer"),	100 },
	{ TYPE_INTEGER,		MAKE_T("TABLE_ORDER"),	0,	nullptr,false,true, false, MAKE_T("Order"),			100 },
	{ TYPE_TEXT,		MAKE_T("DESCRIPTION"),	256,nullptr,false,false, false,MAKE_T("Description"),	100 },
};

DECLARE_STATIC_VARIABLES(BitmapImagePool, true, BITMAP_IMAGE_POOL, -1, 7, 0)
DECLARE_STATIC_TYPESETTINGS(BitmapImagePool, 8) =
{
	{ TYPE_INTEGER,		MAKE_T("TABLE_INDEX"),	0,	nullptr,true, false,false, MAKE_T("Table Index"),	100 },
	{ TYPE_INTEGER,		MAKE_T("BITMAP_TYPE"),	0,	nullptr,false,false,false, MAKE_T("Bitmap Type"),	100 },
	{ TYPE_TEXT,		MAKE_T("FILE_NAME"),	256,nullptr,false,false,false, MAKE_T("File Name"),		100 },
	{ TYPE_INTEGER,		MAKE_T("ACTUAL_WIDTH"),	0,	nullptr,false,false,false, MAKE_T("Actual Width"),	100 },
	{ TYPE_INTEGER,		MAKE_T("ACTUAL_HEIGHT"),0,	nullptr,false,false,false, MAKE_T("Actual Heigth"), 100 },
	{ TYPE_DATALENGTH,	MAKE_T("DATALENGTH"),	0,	nullptr,false,false,false, MAKE_T("Data Length"),	100 },
	{ TYPE_DATA,		MAKE_T("DATAPOINTER"),	0,	nullptr,false,false,false, MAKE_T("Data Pointer"),	100 },
	{ TYPE_INTEGER,		MAKE_T("TABLE_ORDER"),	0,	nullptr,false,true, false, MAKE_T("Order"),			100 },

};

DECLARE_STATIC_VARIABLES(ImageIndexList, false, IMAGE_INDEX_LIST, -1, 1, 0)
DECLARE_STATIC_TYPESETTINGS(ImageIndexList, 4) =
{
	{ TYPE_INTEGER,	MAKE_T("TABLE_INDEX"),	0,	nullptr,true, false,false, MAKE_T("Table Index"),	100 },
	{ TYPE_INTEGER,	MAKE_T("TABLE_ORDER"),	0,	nullptr,false,true, false, MAKE_T("Order"),			100 },
	{ TYPE_INTEGER,	MAKE_T("DURATION"),		0,	nullptr,false,false,false, MAKE_T("Rotation"),		100 },
	{ TYPE_TEXT,	MAKE_T("DESCRIPTION"),	128,nullptr,false,false,false, MAKE_T("Title"),			100 },
};

DECLARE_STATIC_VARIABLES(ImageIndex, false, IMAGE_INDEX, 1, 2, 0)
DECLARE_STATIC_TYPESETTINGS(ImageIndex, 8) =
{
	{ TYPE_INTEGER,MAKE_T("TABLE_INDEX"),	0,nullptr,true, false,false, MAKE_T("Table Index"),		100 },
	{ TYPE_INTEGER,MAKE_T("PARENT_INDEX"),	0,nullptr,false,false, true, MAKE_T("Parent Index"),	100 },
	{ TYPE_INTEGER,MAKE_T("TABLE_ORDER"),	0,nullptr,false,true, false, MAKE_T("Order"),			100 },
	{ TYPE_INTEGER,MAKE_T("TYPE"),			0,nullptr,false,false,false, MAKE_T("Refer to"),		100 },
	{ TYPE_INTEGER,MAKE_T("TEXT_INDEX"),	0,nullptr,false,false,false, MAKE_T("Text Index"),		100 },
	{ TYPE_INTEGER,MAKE_T("BITMAP_INDEX"),	0,nullptr,false,false,false, MAKE_T("Bitmap Index"),	100 },
	{ TYPE_INTEGER,MAKE_T("XPOS"),			0,nullptr,false,false,false, MAKE_T("Pos X"),			100 },
	{ TYPE_INTEGER,MAKE_T("YPOS"),			0,nullptr,false,false,false, MAKE_T("Pos Y"),			100 },
};