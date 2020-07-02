#pragma once

#include "SQLData.h"
#include "choreograph/Choreograph.h"
#include "ValueMonitor.h"
#ifdef PAC_EDITOR
	#include <QtGui>
	#include <qopenglfunctions.h>
#else if
	#include <GLES2/gl2.h>
#endif

// LineMapLink
BEGIN_CLASS_FROM_SQLDATA(LineMapLink, , );
COMMON_VAL_FOR_SQLDATA;
DECLARE_TYPESETTINGS(7);
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC;
BEGIN_MAPPING_MEMBERS
	m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
	m_tSettings[1].POINTER = (void*)(&nParent);
	m_tSettings[2].POINTER = (void*)(&nItemType); // tile type
	m_tSettings[3].POINTER = (void*)(&nPosX);
	m_tSettings[4].POINTER = (void*)(&nPosY);
	m_tSettings[5].POINTER = (void*)(&nProp);
	m_tSettings[6].POINTER = (void*)(&nOrder); // no use
END_MAPPING_MEMBERS
	// fields
	int nParent{ 0 };
	int nItemType{ 0 };
	int nPosX{ 0 };
	int nPosY{ 0 };
	int nProp{ 0 };
	// !fields
	int nAngleSt{ 0 };
	int nAngleEn{ 0 };
	bool bSelected{ false };
	bool bContains{ false };
	int nSelCount{ 0 };
	int nOrder{ 0 };
#ifdef PAC_EDITOR
	QPainterPath m_tPath;
	QPainterPath m_tRevPath;
	QPolygonF m_tPolygon;
	QRect m_tArcRect;
	int nTextureIndex;

	//Start Point - End Point
	unsigned int nLinkIndex[2];
	float fAngle[2];
	std::vector<QPoint> vPoint;
	std::vector<qreal> vAngle;
	std::vector<QPoint> vPointRev;
	std::vector<qreal> vAngleRev;

	int setMinumumDistance(QPoint tRefVal,QPoint &tRetVal)
	{
		int nMin=99999999;
		int nValue;
		std::vector<QPoint>::iterator nit;
		for(nit=vPoint.begin();nit!=vPoint.end();nit++)
		{
			QPoint point=(*nit)-tRefVal;
			nValue=point.manhattanLength();
			nMin=qMin(nValue,nMin);
			if(nValue==nMin)
			{
				tRetVal=(*nit);
			}
		}
		return nMin;
	};
#endif
END_CLASS_FROM_SQLDATA
DECLARE_EDITOR_CLASS(LineMapLink);
// !LineMapLink

// LineMapDisplayItem
BEGIN_CLASS_FROM_SQLDATA(LineMapDisplayItem, , );
COMMON_VAL_FOR_SQLDATA;
DECLARE_TYPESETTINGS(5);
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC;
BEGIN_MAPPING_MEMBERS
	m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
	m_tSettings[1].POINTER = (void*)(&nParentIndex);
	m_tSettings[2].POINTER = (void*)(&nPosX);
	m_tSettings[3].POINTER = (void*)(&nPosY);
	m_tSettings[4].POINTER = (void*)(&nRelatedDisplayItem);
END_MAPPING_MEMBERS
	// fields
	int nParentIndex{ 0 };
	int nPosX{ 0 };
	int nPosY{ 0 };
	int nRelatedDisplayItem{ 0 };
	// !fields
	GLfloat m_fRect[4]{ 0.0f };
	GLfloat m_fOrigin[2]{ 0.0f };
	GLfloat m_fTempRect[10]{ 0.0f };			//Whole Rectangle
	int nPrevCenterSpot{ 0 };
	int nCenterSpot{ 0 };

void SetOrigin(int nCenterSpot, bool bForce)
{
	if ((nPrevCenterSpot != nCenterSpot) || bForce)
	{
		float fHeight = m_fRect[3] - m_fRect[1];
		float fWidth = m_fRect[2] - m_fRect[0];
		switch (nCenterSpot)
		{
		case 0:
		case 1:
			//LeftTop
			m_fOrigin[0] = m_fRect[0];
			m_fOrigin[1] = m_fRect[1];
			break;
		case 2:
			//MidTop
			m_fOrigin[0] = m_fRect[0] + (fWidth / 2.f);
			m_fOrigin[1] = m_fRect[1];
			break;
		case 3:
			//RightTop
			m_fOrigin[0] = m_fRect[0] + fWidth;
			m_fOrigin[1] = m_fRect[1];
			break;
		case 4:
			//LeftMid
			m_fOrigin[0] = m_fRect[0];
			m_fOrigin[1] = m_fRect[1] + (fHeight / 2.f);
			break;
		case 5:
			//Center
			m_fOrigin[0] = m_fRect[0] + (fWidth / 2.f);
			m_fOrigin[1] = m_fRect[1] + (fHeight / 2.f);
			break;
		case 6:
			//RightMid
			m_fOrigin[0] = m_fRect[0] + fWidth;
			m_fOrigin[1] = m_fRect[1] + (fHeight / 2.f);
			break;
		case 7:
			//LeftBottom
			m_fOrigin[0] = m_fRect[0];
			m_fOrigin[1] = m_fRect[1] + fHeight;
			break;
		case 8:
			//MidBottom
			m_fOrigin[0] = m_fRect[0] + (fWidth / 2.f);
			m_fOrigin[1] = m_fRect[1] + fHeight;
			break;
		case 9:
			//RightBottom
			m_fOrigin[0] = m_fRect[0] + fWidth;
			m_fOrigin[1] = m_fRect[1] + fHeight;
			break;
		}
		m_fOrigin[0] *= -1.0f;
		m_fOrigin[1] *= -1.0f;
		nPrevCenterSpot = nCenterSpot;
	}
}
END_CLASS_FROM_SQLDATA
DECLARE_EDITOR_CLASS(LineMapDisplayItem);
// !LineMapDisplayItem

// LineMapNode
BEGIN_CLASS_FROM_SQLDATA(LineMapNode, memset(nSUseDefault, 0xFF, sizeof(nSUseDefault));, );
COMMON_VAL_FOR_SQLDATA;
DECLARE_TYPESETTINGS(47);
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC;
BEGIN_MAPPING_MEMBERS
	m_tSettings[0].POINTER=(void*)(&m_nTableIndex);
	m_tSettings[1].POINTER=(void*)(&nParent);
	m_tSettings[2].POINTER=(void*)(&nItemType);
	m_tSettings[3].POINTER=(void*)(&nPosX);
	m_tSettings[4].POINTER=(void*)(&nPosY);
	m_tSettings[5].POINTER=(void*)(&nProp);
	m_tSettings[6].POINTER=(void*)(&nStationIndex);

	// [0]: passed, [1]: focused, [2]: remain

	// node-related
	m_tSettings[7].POINTER = (void*)(&nOffsetX[0]);
	m_tSettings[8].POINTER = (void*)(&nOffsetY[0]);
	m_tSettings[9].POINTER = (void*)(&nCenterSpot[0]);
	m_tSettings[10].POINTER = (void*)(&nRotAngle[0]);
	m_tSettings[11].POINTER = (void*)(&nType[0]); // indicates node image refer to display pool or image list pool
	m_tSettings[12].POINTER = (void*)(&nColored[0]);
	m_tSettings[13].POINTER = (void*)(&nRelatedIndex[0]);

	m_tSettings[14].POINTER = (void*)(&nOffsetX[1]);
	m_tSettings[15].POINTER = (void*)(&nOffsetY[1]);
	m_tSettings[16].POINTER = (void*)(&nCenterSpot[1]);
	m_tSettings[17].POINTER = (void*)(&nRotAngle[1]);
	m_tSettings[18].POINTER = (void*)(&nType[1]); // indicates node image refer to display pool or image list pool
	m_tSettings[19].POINTER = (void*)(&nColored[1]);
	m_tSettings[20].POINTER = (void*)(&nRelatedIndex[1]);

	m_tSettings[21].POINTER = (void*)(&nOffsetX[2]);
	m_tSettings[22].POINTER = (void*)(&nOffsetY[2]);
	m_tSettings[23].POINTER = (void*)(&nCenterSpot[2]);
	m_tSettings[24].POINTER = (void*)(&nRotAngle[2]);
	m_tSettings[25].POINTER = (void*)(&nType[2]); // indicates node image refer to display pool or image list pool
	m_tSettings[26].POINTER = (void*)(&nColored[2]);
	m_tSettings[27].POINTER = (void*)(&nRelatedIndex[2]);

	// spot-related
	m_tSettings[28].POINTER = (void*)(&nSOffsetX[0]);
	m_tSettings[29].POINTER = (void*)(&nSOffsetY[0]);
	m_tSettings[30].POINTER = (void*)(&nSCenterSpot[0]);
	m_tSettings[31].POINTER = (void*)(&nSUseDefault[0]);
	m_tSettings[32].POINTER = (void*)(&nSRelatedIndex[0]);

	m_tSettings[33].POINTER = (void*)(&nSOffsetX[1]);
	m_tSettings[34].POINTER = (void*)(&nSOffsetY[1]);
	m_tSettings[35].POINTER = (void*)(&nSCenterSpot[1]);
	m_tSettings[36].POINTER = (void*)(&nSUseDefault[1]);
	m_tSettings[37].POINTER = (void*)(&nSRelatedIndex[1]);

	m_tSettings[38].POINTER = (void*)(&nSOffsetX[2]);
	m_tSettings[39].POINTER = (void*)(&nSOffsetY[2]);
	m_tSettings[40].POINTER = (void*)(&nSCenterSpot[2]);
	m_tSettings[41].POINTER = (void*)(&nSUseDefault[2]);
	m_tSettings[42].POINTER = (void*)(&nSRelatedIndex[2]);

	m_tSettings[43].POINTER = (void*)(&nSType[0]); // indicates spot image refer display pool or image list pool
	m_tSettings[44].POINTER = (void*)(&nSType[1]); // indicates spot image refer display pool or image list pool
	m_tSettings[45].POINTER = (void*)(&nSType[2]); // indicates spot image refer display pool or image list pool

	m_tSettings[46].POINTER = (void*)(&nOrder);
END_MAPPING_MEMBERS
// fields
	int nParent{ 0 };
	int nItemType{ 0 };
	int nPosX{ 0 };
	int nPosY{ 0 };
	int nProp{ 0 };
	int nStationIndex{ 0 };

	// node-related
	int nOffsetX[3]{ 0 };
	int nOffsetY[3]{ 0 };
	int nCenterSpot[3]{ 0 };
	int nRotAngle[3]{ 0 };
	int nType[3]{ 0 }; // display pool or image list pool
	int nColored[3]{ 0 }; // always 0 (unchecked)
	int nRelatedIndex[3]{ 0 };

	// spot-related
	int nSOffsetX[3]{ 0 };
	int nSOffsetY[3]{ 0 };
	int nSCenterSpot[3]{ 0 };
	int nSUseDefault[3]; // init node image red circle
	int nSRelatedIndex[3]{ 0 };
	int nSType[3]{ 0 };

	int nOrder{ 1 };
// !fields
	bool bSelected{ false };
	bool bContains{ false };
	GLfloat m_fRect[3][4]{ 0.5f };
	GLfloat m_fOrigin[3][2]{ 0.5f };
	int nPrevCenterSpot[3]{ 0 };
	GLfloat m_fSRect[3][4]{ 0.5f };
	GLfloat m_fSOrigin[3][2]{ 0.5f };
	int nSPrevCenterSpot[3]{ 0 };

void SetOrigin(int nState,int nOrigin)
{
	if (nPrevCenterSpot[nState] != nCenterSpot[nState])
	{
		float fHeight = m_fRect[nState][3] - m_fRect[nState][1];
		float fWidth = m_fRect[nState][2] - m_fRect[nState][0];
		switch (nCenterSpot[nState])
		{
		case 0:
		case 1:
			//LeftTop
			m_fOrigin[nState][0] = m_fRect[nState][0];
			m_fOrigin[nState][1] = m_fRect[nState][1];
			break;
		case 2:
			//MidTop
			m_fOrigin[nState][0] = m_fRect[nState][0] + (fWidth / 2.f);
			m_fOrigin[nState][1] = m_fRect[nState][1];
			break;
		case 3:
			//RightTop
			m_fOrigin[nState][0] = m_fRect[nState][0] + fWidth;
			m_fOrigin[nState][1] = m_fRect[nState][1];
			break;
		case 4:
			//LeftMid
			m_fOrigin[nState][0] = m_fRect[nState][0];
			m_fOrigin[nState][1] = m_fRect[nState][1] + (fHeight / 2.f);
			break;
		case 5:
			//Center
			m_fOrigin[nState][0] = m_fRect[nState][0] + (fWidth / 2.f);
			m_fOrigin[nState][1] = m_fRect[nState][1] + (fHeight / 2.f);
			break;
		case 6:
			//RightMid
			m_fOrigin[nState][0] = m_fRect[nState][0] + fWidth;
			m_fOrigin[nState][1] = m_fRect[nState][1] + (fHeight / 2.f);
			break;
		case 7:
			//LeftBottom
			m_fOrigin[nState][0] = m_fRect[nState][0];
			m_fOrigin[nState][1] = m_fRect[nState][1] + fHeight;
			break;
		case 8:
			//MidBottom
			m_fOrigin[nState][0] = m_fRect[nState][0] + (fWidth / 2.f);
			m_fOrigin[nState][1] = m_fRect[nState][1] + fHeight;
			break;
		case 9:
			//RightBottom
			m_fOrigin[nState][0] = m_fRect[nState][0] + fWidth;
			m_fOrigin[nState][1] = m_fRect[nState][1] + fHeight;
			break;
		}
		m_fOrigin[nState][0] *= -1.0f;
		m_fOrigin[nState][1] *= -1.0f;
		nPrevCenterSpot[nState] = nCenterSpot[nState];
	}
}


void SetSpotOrigin(int nState, int nOrigin)
{
	if (nSPrevCenterSpot[nState] != nSCenterSpot[nState])
	{
		float fHeight = m_fSRect[nState][3] - m_fSRect[nState][1];
		float fWidth = m_fSRect[nState][2] - m_fSRect[nState][0];
		switch (nSCenterSpot[nState])
		{
		case 0:
		case 1:
			//LeftTop
			m_fSOrigin[nState][0] = m_fSRect[nState][0];
			m_fSOrigin[nState][1] = m_fSRect[nState][1];
			break;
		case 2:
			//MidTop
			m_fSOrigin[nState][0] = m_fSRect[nState][0] + (fWidth / 2.f);
			m_fSOrigin[nState][1] = m_fSRect[nState][1];
			break;
		case 3:
			//RightTop
			m_fSOrigin[nState][0] = m_fSRect[nState][0] + fWidth;
			m_fSOrigin[nState][1] = m_fSRect[nState][1];
			break;
		case 4:
			//LeftMid
			m_fSOrigin[nState][0] = m_fSRect[nState][0];
			m_fSOrigin[nState][1] = m_fSRect[nState][1] + (fHeight / 2.f);
			break;
		case 5:
			//Center
			m_fSOrigin[nState][0] = m_fSRect[nState][0] + (fWidth / 2.f);
			m_fSOrigin[nState][1] = m_fSRect[nState][1] + (fHeight / 2.f);
			break;
		case 6:
			//RightMid
			m_fSOrigin[nState][0] = m_fSRect[nState][0] + fWidth;
			m_fSOrigin[nState][1] = m_fSRect[nState][1] + (fHeight / 2.f);
			break;
		case 7:
			//LeftBottom
			m_fSOrigin[nState][0] = m_fSRect[nState][0];
			m_fSOrigin[nState][1] = m_fSRect[nState][1] + fHeight;
			break;
		case 8:
			//MidBottom
			m_fSOrigin[nState][0] = m_fSRect[nState][0] + (fWidth / 2.f);
			m_fSOrigin[nState][1] = m_fSRect[nState][1] + fHeight;
			break;
		case 9:
			//RightBottom
			m_fSOrigin[nState][0] = m_fSRect[nState][0] + fWidth;
			m_fSOrigin[nState][1] = m_fSRect[nState][1] + fHeight;
			break;
		}
		m_fSOrigin[nState][0] *= -1.0f;
		m_fSOrigin[nState][1] *= -1.0f;
		nSPrevCenterSpot[nState] = nSCenterSpot[nState];
	}
}
END_CLASS_FROM_SQLDATA
DECLARE_EDITOR_CLASS(LineMapNode);
// !LineMapNode

// LineMapArrowTexture
BEGIN_CLASS_FROM_SQLDATA(LineMapArrowTexture, , );
COMMON_VAL_FOR_SQLDATA;
DECLARE_TYPESETTINGS(13);
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC;
BEGIN_MAPPING_MEMBERS
	m_tSettings[0].POINTER=(void*)(&m_nTableIndex);
	m_tSettings[1].POINTER=(void*)(&nParent);
	m_tSettings[2].POINTER=(void*)(&uStart);
	m_tSettings[3].POINTER=(void*)(&uEnd);
	m_tSettings[4].POINTER=(void*)(&nSize);
	m_tSettings[5].POINTER=(void*)(&pByte);
	m_tSettings[6].POINTER=(void*)(&nOffsetX);
	m_tSettings[7].POINTER=(void*)(&nOffsetY);
	m_tSettings[8].POINTER=(void*)(&nTexWidth);
	m_tSettings[9].POINTER=(void*)(&nTexHeight);
	m_tSettings[10].POINTER=(void*)(&nVtxBufSize);
	m_tSettings[11].POINTER=(void*)(&pByteVertex);
	m_tSettings[12].POINTER=(void*)(&bVisible);
END_MAPPING_MEMBERS
	// fields
	int nParent{ 0 };
	unsigned int uStart;
	unsigned int uEnd;
	int nSize{ 0 };
	std::shared_ptr<unsigned char> pByte{ 0 };
	int nOffsetX{ 0 };
	int nOffsetY{ 0 };
	int nTexWidth{ 0 };
	int nTexHeight{ 0 };
	int nVtxBufSize{ 0 };
	std::shared_ptr<unsigned char> pByteVertex{ 0 };
	unsigned int bVisible{ 1 };
	// !fields
	int nTextureIndex{ 0 };
END_CLASS_FROM_SQLDATA
DECLARE_EDITOR_CLASS(LineMapArrowTexture);
// !LineMapArrowTexture

// LineMapPool
BEGIN_CLASS_FROM_SQLDATA_WITH_CHILDS(LineMapPool, , , 5);
COMMON_VAL_FOR_SQLDATA;
DECLARE_TYPESETTINGS(24);
DECLARE_COMMON_FUNCTIONS;/* OVERRIDE_DUMMY_EDITOR_FUNC*/
BEGIN_MAPPING_MEMBERS
	m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
	m_tSettings[1].POINTER = (void*)szDesc;
	m_tSettings[2].POINTER = (void*)(&nProp); // tile size
	m_tSettings[3].POINTER = (void*)(&nWidth); // line width
	m_tSettings[4].POINTER = (void*)(&nSize);		// data length
	m_tSettings[5].POINTER = (void*)(&pByte);		// buffer
	m_tSettings[6].POINTER = (void*)(&nWholeWidth);		// map width
	m_tSettings[7].POINTER = (void*)(&nWholeHeight);		// mape height
	m_tSettings[8].POINTER = (void*)(&nSizeSpot);
	m_tSettings[9].POINTER = (void*)(&pByteSpot);
	m_tSettings[10].POINTER = (void*)(&uBackColor);
	m_tSettings[11].POINTER = (void*)(&uLineColor);
	m_tSettings[12].POINTER = (void*)(&uPassedColor);
	m_tSettings[13].POINTER = (void*)(&uFocusedColor);
	m_tSettings[14].POINTER = (void*)(&uLeftColor);
	m_tSettings[15].POINTER = (void*)(&uFocusedColor1);
	m_tSettings[16].POINTER = (void*)(&uForArrowOffset);
	m_tSettings[17].POINTER = (void*)(&uBackArrowOffset);
	m_tSettings[18].POINTER = (void*)(&fPenWidth);
	m_tSettings[19].POINTER = (void*)(&uArrowPassedColor);
	m_tSettings[20].POINTER = (void*)(&uArrowFocusedColor);
	m_tSettings[21].POINTER = (void*)(&uArrowFocusedColor1);
	m_tSettings[22].POINTER = (void*)(&uArrowLeftColor);
	m_tSettings[23].POINTER = (void*)(&nOrder);
END_MAPPING_MEMBERS
	// fields
	TYC szDesc[256]{ 0 };
	int nProp{ 0 }; // tile size
	int nWidth{ 0 }; // line width
	int nSize{ 0 };
	std::shared_ptr<unsigned char> pByte{ 0 };
	int nWholeWidth{ 0 };
	int nWholeHeight{ 0 };
	int nSizeSpot{ 0 };
	std::shared_ptr<unsigned char> pByteSpot{ 0 };
	unsigned int uBackColor{ 0xffffffff };
	unsigned int uLineColor{ 0xffff0000 };
	unsigned int uPassedColor{ 0xffffffff };
	unsigned int uFocusedColor{ 0xffffffff };
	unsigned int uLeftColor{ 0xffffffff }; // remain
	unsigned int uFocusedColor1{ 0xffffffff };
	unsigned int uForArrowOffset{ 0xffffffff };
	unsigned int uBackArrowOffset{ 0xffffffff };
	float fPenWidth{ 10.0f };
	unsigned int uArrowPassedColor{ 0xffffffff };
	unsigned int uArrowFocusedColor{ 0xffffffff };
	unsigned int uArrowFocusedColor1{ 0xffffffff };
	unsigned int uArrowLeftColor{ 0xffffffff };
	int nOrder{ 1 };
	// !fields

virtual CEditSQLData* GetEditor(int nRow)
{
	switch (nRow)
	{
	case 0:		return new LineMapLinkEditor();			break;
	case 1:		return nullptr;							break;
	case 2:		return new LineMapNodeEditor();			break;
	case 3:		return new LineMapArrowTextureEditor(); break;
	case 4:		return new LineMapDisplayItemEditor();	break;
	default:	return nullptr;							break;
	}
	return nullptr;
}
END_CLASS_FROM_SQLDATA
DECLARE_EDITOR_CLASS(LineMapPool);
// !LineMapPool




