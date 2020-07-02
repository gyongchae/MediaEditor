#include "DefineLEDTables.h"

DECLARE_STATIC_VARIABLES(ETNDIndicator, true, ETND_INDICATOR, -1, 9, 0)
DECLARE_STATIC_TYPESETTINGS(ETNDIndicator, 10) =
{
	{ TYPE_INTEGER,		MAKE_T("TABLE_INDEX"),	0,nullptr,true, false,false, MAKE_T("Table Index"),	100 },
	{ TYPE_INTEGER,		MAKE_T("CODE"),			0,nullptr,false,false,false, MAKE_T("Code"),		100 },
	{ TYPE_DATALENGTH,	MAKE_T("DATALENGTH"),	0,nullptr,false,false,false, MAKE_T("Data Length"),	100 },
	{ TYPE_DATA,		MAKE_T("DATAPOINTER"),	0,nullptr,false,false,false, MAKE_T("LED Preview"),	100 },
	{ TYPE_INTEGER,		MAKE_T("IMG_WIDTH"),	0,nullptr,false,false,false, MAKE_T("Width"),		100 },
	{ TYPE_INTEGER,		MAKE_T("IMG_HEIGHT"),	0,nullptr,false,false,false, MAKE_T("Height"),		100 },
	{ TYPE_INTEGER,		MAKE_T("IMG_BIT"),		0,nullptr,false,false,false, MAKE_T("Bit"),			100 },
	{ TYPE_INTEGER,		MAKE_T("IMG_PAGE"),		0,nullptr,false,false,false, MAKE_T("Page"),		100 },
	{ TYPE_INTEGER,		MAKE_T("IMG_MODE"),		0,nullptr,false,false,false, MAKE_T("Mode"),		100 },
	{ TYPE_INTEGER,		MAKE_T("TABLE_ORDER"),	0,nullptr,false,true, false, MAKE_T("Order"),		100 },
};

DECLARE_STATIC_VARIABLES(EDDIndicator, true, EDD_INDICATOR, -1, 9, 0)
DECLARE_STATIC_TYPESETTINGS(EDDIndicator, 10) =
{
	{ TYPE_INTEGER,		MAKE_T("TABLE_INDEX"),	0,nullptr,true, false,false, MAKE_T("LED Index"),	100 },
	{ TYPE_INTEGER,		MAKE_T("CODE"),			0,nullptr,false,false,false, MAKE_T("Code"),		100 },
	{ TYPE_DATALENGTH,	MAKE_T("DATALENGTH"),	0,nullptr,false,false,false, MAKE_T("Data Length"), 100 },
	{ TYPE_DATA,		MAKE_T("DATAPOINTER"),	0,nullptr,false,false,false, MAKE_T("Preview"),		100 },
	{ TYPE_INTEGER,		MAKE_T("IMG_WIDTH"),	0,nullptr,false,false,false, MAKE_T("Width"),		100 },
	{ TYPE_INTEGER,		MAKE_T("IMG_HEIGHT"),	0,nullptr,false,false,false, MAKE_T("Height"),		100 },
	{ TYPE_INTEGER,		MAKE_T("IMG_BIT"),		0,nullptr,false,false,false, MAKE_T("Bit"),			100 },
	{ TYPE_INTEGER,		MAKE_T("IMG_PAGE"),		0,nullptr,false,false,false, MAKE_T("Page"),		100 },
	{ TYPE_INTEGER,		MAKE_T("IMG_MODE"),		0,nullptr,false,false,false, MAKE_T("Mode"),		100 },
	{ TYPE_INTEGER,		MAKE_T("TABLE_ORDER"),	0,nullptr,false,true, false, MAKE_T("Order"),		100 },
};

DECLARE_STATIC_VARIABLES(EDDIndex, false, EDD_INDEX, -1, 3, 0)
DECLARE_STATIC_TYPESETTINGS(EDDIndex, 4) =
{
	{ TYPE_INTEGER,	MAKE_T("TABLE_INDEX"),	0,	nullptr,true, false,false, MAKE_T("Table Index"),	100 },
	{ TYPE_TEXT,	MAKE_T("DESCRIPTION"),	128,nullptr,false,false,false, MAKE_T("Description"),	100 },
	{ TYPE_INTEGER,	MAKE_T("CODE"),			128,nullptr,false,false,false, MAKE_T("Code"),			100 },
	{ TYPE_INTEGER,	MAKE_T("TABLE_ORDER"),	0,	nullptr,false,true, false, MAKE_T("Order"),			100 },
};

DECLARE_STATIC_VARIABLES(EDDIndexList, false, EDD_INDEXLIST, 1, 2, 0)
DECLARE_STATIC_TYPESETTINGS(EDDIndexList, 4) =
{
	{ TYPE_INTEGER,MAKE_T("TABLE_INDEX"),	0,nullptr,true, false,false, MAKE_T("Table Index"), 100 },
	{ TYPE_INTEGER,MAKE_T("PARENT_INDEX"),	0,nullptr,false,false,true,  MAKE_T("Parent Index"),100 },
	{ TYPE_INTEGER,MAKE_T("TABLE_ORDER"),	0,nullptr,false,true, false, MAKE_T("Order"),		100 },
	{ TYPE_INTEGER,MAKE_T("EDD_INDEX"),		0,nullptr,false,false,false, MAKE_T("LED Index"),	100 },
};

