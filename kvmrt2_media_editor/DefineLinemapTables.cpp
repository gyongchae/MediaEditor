#include "defineLinemapTables.h"
#include "DefineTables.h"

// LineMapPool
DECLARE_STATIC_VARIABLES(LineMapPool, true, LINEMAP_POOL, -1, 23, 0)
DECLARE_STATIC_TYPESETTINGS(LineMapPool, 25) =
{
	{ TYPE_INTEGER,		MAKE_T("TABLE_INDEX"),			0,	nullptr,true, false,false, MAKE_T("Table Index"),			100 },
	{ TYPE_TEXT,		MAKE_T("MAP_NAME"),				256,nullptr,false,false,false, MAKE_T("Route Map Name"),		100 },
	{ TYPE_INTEGER,		MAKE_T("TILE_SIZE"),			0,	nullptr,false,false,false, MAKE_T("Tile Size"),				100 },
	{ TYPE_INTEGER,		MAKE_T("LINE_THICKNESS"),		0,	nullptr,false,false,false, MAKE_T("Line Thickness"),		100 },
	{ TYPE_DATALENGTH,	MAKE_T("DATALENGTH"),			0,	nullptr,false,false,false, MAKE_T("Data Length"),			100 },
	{ TYPE_DATA,		MAKE_T("DATAPOINTER"),			0,	nullptr,false,false,false, MAKE_T("Data Pointer"),			100 },
	{ TYPE_INTEGER,		MAKE_T("WIDTH"),				0,	nullptr,false,false,false, MAKE_T("Map Width"),				100 },
	{ TYPE_INTEGER,		MAKE_T("HEIGHT"),				0,	nullptr,false,false,false, MAKE_T("Map Height"),			100 },
	{ TYPE_DATALENGTH,	MAKE_T("DATALENGTHSPOT"),		0,	nullptr,false,false,false, MAKE_T("Data Length Spot"),		100 },
	{ TYPE_DATA,		MAKE_T("DATAPOINTERSPOT"),		0,	nullptr,false,false,false, MAKE_T("Data Pointer Spot"),		100 },
	{ TYPE_INTEGER,		MAKE_T("BACK_COLOR"),			0,	nullptr,false,false,false, MAKE_T("Background Color"),		100 },
	{ TYPE_INTEGER,		MAKE_T("LINE_COLOR"),			0,	nullptr,false,false,false, MAKE_T("Line Color"),			100 },
	{ TYPE_INTEGER,		MAKE_T("PASSED_COLOR"),			0,	nullptr,false,false,false, MAKE_T("Passed Color"),			100 },
	{ TYPE_INTEGER,		MAKE_T("FOCUSED_COLOR"),		0,	nullptr,false,false,false, MAKE_T("Focused Color"),			100 },
	{ TYPE_INTEGER,		MAKE_T("REMAIN_COLOR"),			0,	nullptr,false,false,false, MAKE_T("Left Color"),			100 },
	{ TYPE_INTEGER,		MAKE_T("FOCUSED_COLOR1"),		0,	nullptr,false,false,false, MAKE_T("Focused Color"),			100 },
	{ TYPE_INTEGER,		MAKE_T("FORWARD_ARROW_OFFSET"),	0,	nullptr,false,false,false, MAKE_T("Arrow Offset(Forward)"),	100 },
	{ TYPE_INTEGER,		MAKE_T("BACKWARD_ARROW_OFFSET"),0,	nullptr,false,false,false, MAKE_T("Arrow Offset(Backward)"),100 },
	{ TYPE_FLOAT,		MAKE_T("ARROW_THICKNESS"),		0,	nullptr,false,false,false, MAKE_T("Arrow Thickness"),		100 },
	{ TYPE_INTEGER,		MAKE_T("ARROW_PASSED_COLOR"),	0,	nullptr,false,false,false, MAKE_T("Passed Arrow Color"),	100 },
	{ TYPE_INTEGER,		MAKE_T("ARROW_FOCUSED_COLOR"),	0,	nullptr,false,false,false, MAKE_T("Focused Arrow Color"),	100 },
	{ TYPE_INTEGER,		MAKE_T("ARROW_LEFT_COLOR"),		0,	nullptr,false,false,false, MAKE_T("Remain Arrow Color"),	100 },
	{ TYPE_INTEGER,		MAKE_T("ARROW_FOCUSED_COLOR1"),	0,	nullptr,false,false,false, MAKE_T("Focused Color"),			100 },
	{ TYPE_INTEGER,		MAKE_T("TABLE_ORDER"),			0,	nullptr,false,true, false, MAKE_T("Order"),					100 },
	{ TYPE_INTEGER,		MAKE_T("ROUTE_BOUND"),			0,	nullptr,false,false,false, MAKE_T("Bound"),					100 },
};
// !LineMapPool

// LineMapLink
DECLARE_STATIC_VARIABLES(LineMapLink,false,LINEMAP_LINK,1,6,0)
DECLARE_STATIC_TYPESETTINGS(LineMapLink,9)=
{
    {TYPE_INTEGER,MAKE_T("TABLE_INDEX"),	 0,nullptr,true, false,false, MAKE_T("Table Index"),	100},
    {TYPE_INTEGER,MAKE_T("PARENT_INDEX"),	 0,nullptr,false,false,true,  MAKE_T("Parent Index"),	100},
    {TYPE_INTEGER,MAKE_T("ITEM_TYPE"),		 0,nullptr,false,false,false, MAKE_T("Item Type"),		100},
    {TYPE_INTEGER,MAKE_T("POSX"),			 0,nullptr,false,false,false, MAKE_T("Pos X"),			100},
    {TYPE_INTEGER,MAKE_T("POSY"),			 0,nullptr,false,false,false, MAKE_T("Pos Y"),			100},
	{TYPE_INTEGER,MAKE_T("PROP"),			 0,nullptr,false,false,false, MAKE_T("Prop"),			100 },
	{TYPE_INTEGER,MAKE_T("TABLE_ORDER"),	 0,nullptr,false,true, false, MAKE_T("Order"),			100 },
	{TYPE_INTEGER,MAKE_T("ACTIVE_STATION"),	 0,nullptr,false,false,false, MAKE_T("Active Station"),	100},
	{TYPE_TEXT,	  MAKE_T("ACT_STATION_NAME"),128,nullptr,false,false,false,	MAKE_T("Station Name"),	100 },
};
// !LineMapLink

// LineMapNode
DECLARE_STATIC_VARIABLES(LineMapNode, false, LINEMAP_NODE, 1, 46, 0)
DECLARE_STATIC_TYPESETTINGS(LineMapNode, 47) =
{
	{ TYPE_INTEGER,MAKE_T("TABLE_INDEX"),	0,nullptr,true, false,false, MAKE_T("Table Index"),		100 },
	{ TYPE_INTEGER,MAKE_T("PARENT_INDEX"),	0,nullptr,false,false, true, MAKE_T("Parent Index"),	100 },
	{ TYPE_INTEGER,MAKE_T("ITEM_TYPE"),		0,nullptr,false,false,false, MAKE_T("Spare"),			100 },
	{ TYPE_INTEGER,MAKE_T("POS_X"),			0,nullptr,false,false,false, MAKE_T("Pos X"),			100 },
	{ TYPE_INTEGER,MAKE_T("POS_Y"),			0,nullptr,false,false,false, MAKE_T("Pos Y"),			100 },
	{ TYPE_INTEGER,MAKE_T("PROP"),			0,nullptr,false,false,false, MAKE_T("Spare"),			100 },
	{ TYPE_INTEGER,MAKE_T("STATION_INDEX"), 0,nullptr,false,false,false, MAKE_T("Station Index"),	100 },

	{ TYPE_INTEGER,MAKE_T("NODE_OFFSET1_X"),	 0,nullptr,false,false,false, MAKE_T("Offset X(1)"),	100 },
	{ TYPE_INTEGER,MAKE_T("NODE_OFFSET1_Y"),	 0,nullptr,false,false,false, MAKE_T("Offset Y(1)"),	100 },
	{ TYPE_INTEGER,MAKE_T("NODE_CENTERSPOT1"),	 0,nullptr,false,false,false, MAKE_T("Pivot Type(1)"),	100 },
	{ TYPE_INTEGER,MAKE_T("NODE_ROTANGLE1"),	 0,nullptr,false,false,false, MAKE_T("Angle(1)"),		100 },
	{ TYPE_INTEGER,MAKE_T("NODE_TYPE1"),		 0,nullptr,false,false,false, MAKE_T("Display Type(1)"),100 },
	{ TYPE_INTEGER,MAKE_T("NODE_COLORED1"),		 0,nullptr,false,false,false, MAKE_T("Color(1)"),		100 },
	{ TYPE_INTEGER,MAKE_T("NODE_RELATED_INDEX1"),0,nullptr,false,false,false, MAKE_T("Item Index(1)"),	100 },
	{ TYPE_INTEGER,MAKE_T("NODE_OFFSET2_X"),	 0,nullptr,false,false,false, MAKE_T("Offset X(2)"),	100 },
	{ TYPE_INTEGER,MAKE_T("NODE_OFFSET2_Y"),	 0,nullptr,false,false,false, MAKE_T("Offset Y(2)"),	100 },
	{ TYPE_INTEGER,MAKE_T("NODE_CENTERSPOT2"),	 0,nullptr,false,false,false, MAKE_T("Pivot Type(2)"),	100 },
	{ TYPE_INTEGER,MAKE_T("NODE_ROTANGLE2"),	 0,nullptr,false,false,false, MAKE_T("Angle(2)"),		100 },
	{ TYPE_INTEGER,MAKE_T("NODE_TYPE2"),		 0,nullptr,false,false,false, MAKE_T("Display Type(2)"),100 },
	{ TYPE_INTEGER,MAKE_T("NODE_COLORED2"),		 0,nullptr,false,false,false, MAKE_T("Color(2)"),		100 },
	{ TYPE_INTEGER,MAKE_T("NODE_RELATED_INDEX2"),0,nullptr,false,false,false, MAKE_T("Item Index(2)"),	100 },
	{ TYPE_INTEGER,MAKE_T("NODE_OFFSET3_X"),	 0,nullptr,false,false,false, MAKE_T("Offset X(3)"),	100 },
	{ TYPE_INTEGER,MAKE_T("NODE_OFFSET3_Y"),	 0,nullptr,false,false,false, MAKE_T("Offset Y(3)"),	100 },
	{ TYPE_INTEGER,MAKE_T("NODE_CENTERSPOT3"),	 0,nullptr,false,false,false, MAKE_T("Pivot Type(3)"),	100 },
	{ TYPE_INTEGER,MAKE_T("NODE_ROTANGLE3"),	 0,nullptr,false,false,false, MAKE_T("Angle(3)"),		100 },
	{ TYPE_INTEGER,MAKE_T("NODE_TYPE3"),		 0,nullptr,false,false,false, MAKE_T("Display Type(3)"),100 },
	{ TYPE_INTEGER,MAKE_T("NODE_COLORED3"),		 0,nullptr,false,false,false, MAKE_T("Color(3)"),		100 },
	{ TYPE_INTEGER,MAKE_T("NODE_RELATED_INDEX3"),0,nullptr,false,false,false, MAKE_T("Item Index(3)"),	100 },

	{ TYPE_INTEGER,MAKE_T("SPOT_OFFSET1_X"),	 0,nullptr,false,false,false, MAKE_T("Offset X(1)"),		100 },
	{ TYPE_INTEGER,MAKE_T("SPOT_OFFSET1_Y"),	 0,nullptr,false,false,false, MAKE_T("Offset Y(1)"),		100 },
	{ TYPE_INTEGER,MAKE_T("SPOT_CENTERSPOT1"),	 0,nullptr,false,false,false, MAKE_T("Pivot Type(1)"),		100 },
	{ TYPE_INTEGER,MAKE_T("SPOT_USE_DEFAULT1"),	 0,nullptr,false,false,false, MAKE_T("Default(1)"),			100 },
	{ TYPE_INTEGER,MAKE_T("SPOT_RELATED_INDEX1"),0,nullptr,false,false,false, MAKE_T("Item Index(1)"),		100 },
	{ TYPE_INTEGER,MAKE_T("SPOT_OFFSET2_X"),	 0,nullptr,false,false,false, MAKE_T("Offset X(2)"),		100 },
	{ TYPE_INTEGER,MAKE_T("SPOT_OFFSET2_Y"),	 0,nullptr,false,false,false, MAKE_T("Offset Y(2)"),		100 },
	{ TYPE_INTEGER,MAKE_T("SPOT_CENTERSPOT2"),	 0,nullptr,false,false,false, MAKE_T("Pivot Type(2)"),		100 },
	{ TYPE_INTEGER,MAKE_T("SPOT_USE_DEFAULT2"),	 0,nullptr,false,false,false, MAKE_T("Default(2)"),			100 },
	{ TYPE_INTEGER,MAKE_T("SPOT_RELATED_INDEX2"),0,nullptr,false,false,false, MAKE_T("Item Index(2)"),		100 },
	{ TYPE_INTEGER,MAKE_T("SPOT_OFFSET3_X"),	 0,nullptr,false,false,false, MAKE_T("Offset X(3)"),		100 },
	{ TYPE_INTEGER,MAKE_T("SPOT_OFFSET3_Y"),	 0,nullptr,false,false,false, MAKE_T("Offset Y(3)"),		100 },
	{ TYPE_INTEGER,MAKE_T("SPOT_CENTERSPOT3"),	 0,nullptr,false,false,false, MAKE_T("Pivot Type(3)"),		100 },
	{ TYPE_INTEGER,MAKE_T("SPOT_USE_DEFAULT3"),	 0,nullptr,false,false,false, MAKE_T("Default(3)"),			100 },
	{ TYPE_INTEGER,MAKE_T("SPOT_RELATED_INDEX3"),0,nullptr,false,false,false, MAKE_T("Item Index(3)"),		100 },
	{ TYPE_INTEGER,MAKE_T("SPOT_ITEM_TYPE1"),	 0,nullptr,false,false,false, MAKE_T("Spot Display Type 1"),100 },
	{ TYPE_INTEGER,MAKE_T("SPOT_ITEM_TYPE2"),	 0,nullptr,false,false,false, MAKE_T("Spot Display Type 2"),100 },
	{ TYPE_INTEGER,MAKE_T("SPOT_ITEM_TYPE3"),	 0,nullptr,false,false,false, MAKE_T("Spot Display Type 3"),100 },
	
	{ TYPE_INTEGER,MAKE_T("TABLE_ORDER"), 0, nullptr,false,true,false, MAKE_T("Order"), 100 },
};
// !LineMapNode

// LineMapDisplayItem
DECLARE_STATIC_VARIABLES(LineMapDisplayItem, false, LINEMAP_DISPLAY_ITEM, 1, -1, 0)
DECLARE_STATIC_TYPESETTINGS(LineMapDisplayItem, 5) =
{
    { TYPE_INTEGER,MAKE_T("TABLE_INDEX"),	0,nullptr,true, false,false, MAKE_T("Table Index"), 100 },
    { TYPE_INTEGER,MAKE_T("PARENT_INDEX"),	0,nullptr,false,false, true, MAKE_T("Parent Index"),100 },
    { TYPE_INTEGER,MAKE_T("POS_X"),			0,nullptr,false,false,false, MAKE_T("PosX"),		100 },
    { TYPE_INTEGER,MAKE_T("POS_Y"),			0,nullptr,false,false,false, MAKE_T("PosY"),		100 },
    { TYPE_INTEGER,MAKE_T("RELATED_ITEM"),	0,nullptr,false,false,false, MAKE_T("Related Item"),100 },
};
// !LineMapDisplayItem

// LineMapArrowTexture
DECLARE_STATIC_VARIABLES(LineMapArrowTexture,true,LINEMAP_ARROW_TEXTURE,1,-1,0)
DECLARE_STATIC_TYPESETTINGS(LineMapArrowTexture,13)=
{
    {TYPE_INTEGER,		MAKE_T("TABLE_INDEX"),		0,nullptr,true, false,false, MAKE_T("Table Index"),			100},
    {TYPE_INTEGER,		MAKE_T("PARENT_INDEX"),		0,nullptr,false,false, true, MAKE_T("Parent Index"),		100},
    {TYPE_INTEGER,		MAKE_T("STARTINDEX"),		0,nullptr,false,false,false, MAKE_T("Start Index"),			100},
    {TYPE_INTEGER,		MAKE_T("ENDINDEX"),			0,nullptr,false,false,false, MAKE_T("End Index"),			100},
    {TYPE_DATALENGTH,	MAKE_T("DATALENGTH"),		0,nullptr,false,false,false, MAKE_T("Data Length"),			100},
    {TYPE_DATA,			MAKE_T("DATAPOINTER"),		0,nullptr,false,false,false, MAKE_T("Data Pointer"),		100},
    {TYPE_INTEGER,		MAKE_T("OFFSET_X"),			0,nullptr,false,false,false, MAKE_T("Offset X"),			100},
    {TYPE_INTEGER,		MAKE_T("OFFSET_Y"),			0,nullptr,false,false,false, MAKE_T("Offset Y"),			100},
    {TYPE_INTEGER,		MAKE_T("TEXTURE_WIDTH"),	0,nullptr,false,false,false, MAKE_T("Texture Width"),		100},
    {TYPE_INTEGER,		MAKE_T("TEXTURE_HEIGHT"),	0,nullptr,false,false,false, MAKE_T("Texture Height"),		100},
    {TYPE_DATALENGTH,	MAKE_T("VERTEXDATALENGTH"),	0,nullptr,false,false,false, MAKE_T("Vertex Data Length"),	100},
    {TYPE_DATA,			MAKE_T("VERTEXDATAPOINTER"),0,nullptr,false,false,false, MAKE_T("Vertex Data Pointer"), 100},
    {TYPE_INTEGER,		MAKE_T("VISIBLE"),			0,nullptr,false,false,false, MAKE_T("Visible"),				100},
};
// !LineMapArrowTexture









