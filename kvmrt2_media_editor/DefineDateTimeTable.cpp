#include "DefineDateTimeTable.h"

DECLARE_STATIC_VARIABLES(DisplayDateTimeItem, false, DISPLAY_DATE_TIME_ITEM, 1, -1, 0)

DECLARE_STATIC_TYPESETTINGS(DisplayDateTimeItem, 9) =
{
	{ TYPE_INTEGER,MAKE_T("TABLE_INDEX"),0,nullptr,true,false,false, MAKE_T("Table Index"), 100 },
	{ TYPE_INTEGER,MAKE_T("PARENT_INDEX"),0,nullptr,false,false,true, MAKE_T("ParentIndex"), 100 },
	{ TYPE_INTEGER,MAKE_T("RELATED_ITEM_INDEX"),0,nullptr,false,false,false, MAKE_T("ImageList"), 100 },
	{ TYPE_INTEGER,MAKE_T("INITPOS_X"),0,nullptr,false,false,false, MAKE_T("X"), 100 },
	{ TYPE_INTEGER,MAKE_T("INITPOS_Y"),0,nullptr,false,false,false, MAKE_T("Y"), 100 },
	{ TYPE_INTEGER,MAKE_T("APPEAR_FROM"),0,nullptr,false,false,false, MAKE_T("From"), 100 },
	{ TYPE_INTEGER,MAKE_T("APPEAR_TO"),0,nullptr,false,false,false, MAKE_T("To"), 100 },
	{ TYPE_INTEGER,MAKE_T("Z_ORDER"),0,nullptr,false,false,false, MAKE_T("Z Order"), 100 },
	{ TYPE_INTEGER,MAKE_T("ORIGIN"),0,nullptr,false,false,false, MAKE_T("Origin"), 100 },
};

void DisplayDateTimeItem::SetBufferIndex(int nIndex, CTexPool *pPool)
{
	m_nPrevOrigin = pPool->m_nPrevOrigin;
	m_fRotation = pPool->m_fRotation;

	m_fRect[0] = pPool->m_fRect[0];
	m_fRect[1] = pPool->m_fRect[1];
	m_fRect[2] = pPool->m_fRect[2];
	m_fRect[3] = pPool->m_fRect[3];

	fOrigX = pPool->m_fOrigin[0];
	fOrigY = pPool->m_fOrigin[1];

	m_fTrans[0] = pPool->m_fTrans[0];
	m_fTrans[1] = pPool->m_fTrans[1];

	m_fScale[0] = pPool->m_fScale[0];
	m_fScale[1] = pPool->m_fScale[1];

	m_fColor[0] = pPool->m_fColor[0];
	m_fColor[1] = pPool->m_fColor[1];
	m_fColor[2] = pPool->m_fColor[2];
	m_fColor[3] = pPool->m_fColor[3];

	nRelatedBufferIndex = nIndex;
}

DECLARE_STATIC_VARIABLES(DisplayDateTimeProp, false, DISPLAY_DATE_TIME_PROP, 1, -1, 0)

DECLARE_STATIC_TYPESETTINGS(DisplayDateTimeProp, 16) =
{
	{ TYPE_INTEGER,MAKE_T("TABLE_INDEX"),0,nullptr,true,false,false, MAKE_T("Table Index"), 100 },
	{ TYPE_INTEGER,MAKE_T("PARENT_INDEX"),0,nullptr,false,false,true, MAKE_T("Parent Index"), 100 },
	{ TYPE_FLOAT,MAKE_T("POSX"),0,nullptr,false,false,false, MAKE_T("XPos"), 100 },
	{ TYPE_FLOAT,MAKE_T("POSY"),0,nullptr,false,false,false, MAKE_T("YPos"), 100 },
	{ TYPE_FLOAT,MAKE_T("ANGLE"),0,nullptr,false,false,false, MAKE_T("Angle"), 100 },
	{ TYPE_FLOAT,MAKE_T("SCALEX"),0,nullptr,false,false,false, MAKE_T("XScale"), 100 },
	{ TYPE_FLOAT,MAKE_T("SCALEY"),0,nullptr,false,false,false, MAKE_T("YScale"), 100 },
	{ TYPE_FLOAT,MAKE_T("ZORDER"),0,nullptr,false,false,false, MAKE_T("Z"), 100 },
	{ TYPE_INTEGER,MAKE_T("EVENTS_AT"),0,nullptr,false,false,false, MAKE_T("EventsAt"), 100 },
	{ TYPE_INTEGER,MAKE_T("VISIBLE"),0,nullptr,false,false,false, MAKE_T("Visible"), 100 },
	{ TYPE_INTEGER,MAKE_T("COLOR"),0,nullptr,false,false,false, MAKE_T("Color"), 100 },

	{ TYPE_INTEGER,MAKE_T("TRANSTYPE_POS"),0,nullptr,false,false,false, MAKE_T("TransType"), 100 },
	{ TYPE_INTEGER,MAKE_T("TRANSTYPE_ANGLE"),0,nullptr,false,false,false, MAKE_T("TransAngle"), 100 },
	{ TYPE_INTEGER,MAKE_T("TRANSTYPE_SCALE"),0,nullptr,false,false,false, MAKE_T("TransScale"), 100 },
	{ TYPE_INTEGER,MAKE_T("TRANSTYPE_ZORDER"),0,nullptr,false,false,false, MAKE_T("TransZOrder"), 100 },
	{ TYPE_INTEGER,MAKE_T("TRANSTYPE_COLOR"),0,nullptr,false,false,false, MAKE_T("TransColor"), 100 },
};