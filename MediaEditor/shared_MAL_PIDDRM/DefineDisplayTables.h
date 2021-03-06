#pragma once
#include "DefineTables.h"
#include "choreograph/Choreograph.h"
#include "TexPool.h"
#include "ValueMonitor.h"
#ifdef PAC_EDITOR
#include <QtGui>
#include <qopenglfunctions.h>
#else
#include <GLES2/gl2.h>
#endif
using namespace choreograph;

BEGIN_CLASS_FROM_SQLDATA_WITH_CHILDS(DisplayItem, uBackColor = 0xffffffff; nPrevOrigin = -1; nRelatedItemListIndex = nInitPosX = nInitPosY = nParentIndex = nAppearFrom = nAppearTo = nZOrder = 0; nOrigin = 1; fOrigX = fOrigY = 0.0f; , , 1)
COMMON_VAL_FOR_SQLDATA
DECLARE_TYPESETTINGS(9)
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC
BEGIN_MAPPING_MEMBERS
m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
m_tSettings[1].POINTER = (void*)(&nParentIndex);
m_tSettings[2].POINTER = (void*)(&nRelatedItemListIndex);
m_tSettings[3].POINTER = (void*)(&nInitPosX);
m_tSettings[4].POINTER = (void*)(&nInitPosY);
m_tSettings[5].POINTER = (void*)(&nAppearFrom);
m_tSettings[6].POINTER = (void*)(&nAppearTo);
m_tSettings[7].POINTER = (void*)(&nZOrder);
m_tSettings[8].POINTER = (void*)(&nOrigin);
END_MAPPING_MEMBERS

int nRelatedItemListIndex;
int nInitPosX;
int nInitPosY;
int nAppearFrom;
int nAppearTo;
int nParentIndex;
int nZOrder;
int nOrigin;
int nPrevOrigin;
unsigned int uBackColor;
GLfloat fOrigX, fOrigY;

int SetOrigin(int nCurOrigin)
{
	if (nPrevOrigin != nCurOrigin)
	{
		int nPrev = nPrevOrigin;
		nPrevOrigin = nCurOrigin;
		return nPrev;
	}
	return 0;
}
/*Editing purposes only*/
void SetBufferIndex(int nIndex, CTexPool *pPool);


choreograph::Timeline tLine;

int m_nPrevOrigin;

GLfloat m_fRect[4];			//Whole Rectangle
GLfloat m_fTempRect[10];			//Whole Rectangle

choreograph::Output<GLfloat> m_fTrans[2];		//Translation x,y
choreograph::Output<GLfloat> m_fRotation;		//Rotation
choreograph::Output<GLfloat> m_fScale[2];		//Scaling x,y
												//choreograph::Output<GLfloat> m_fOrigin[2];		//Origin Coordinate
choreograph::Output<GLfloat> m_fColor[4];		//Color
choreograph::Output<GLfloat> m_fZorder;			//Zorder
choreograph::Output<int>	m_nVisible;

int nRelatedBufferIndex;			//Index
bool bSelected;
/*Editing purposes only*/
END_CLASS_FROM_SQLDATA
DECLARE_EDITOR_CLASS(DisplayItem);



BEGIN_CLASS_FROM_SQLDATA_WITH_CHILDS(
	DisplayItemPool, 
	nOrder = 1; memset(szDesc, 0, sizeof(szDesc));,
	, 
	2) /*child count*/

COMMON_VAL_FOR_SQLDATA
DECLARE_TYPESETTINGS(8)
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC

BEGIN_MAPPING_MEMBERS
m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
m_tSettings[1].POINTER = (void*)(szDesc);
m_tSettings[2].POINTER = (void*)(&nWidth);
m_tSettings[3].POINTER = (void*)(&nHeight);
m_tSettings[4].POINTER = (void*)(&nDuration);
m_tSettings[5].POINTER = (void*)(&uBackColor);
m_tSettings[6].POINTER = (void*)(&nOrder);
m_tSettings[7].POINTER = (void*)(&nDisplayType);
END_MAPPING_MEMBERS

TYC szDesc[256];
int nWidth;
int nHeight;
int nDuration;
unsigned int uBackColor;
int nOrder;
int nDisplayType{ 0 };
GLfloat m_fTempRect[10];			//Whole Rectangle

END_CLASS_FROM_SQLDATA

DECLARE_EDITOR_CLASS(DisplayItemPool);



BEGIN_CLASS_FROM_SQLDATA(DisplayProp, nParentIndex = nAtMiliseconds = nTransistionType = 0; nTransType[0] = nTransType[1] = nTransType[2] = nTransType[3] = nTransType[4] = 1; nVisible = 1; uColor = 0xFFFFFFFF; fX = fY = fAngle = fScalingX = fScalingY = fZorder = 0.0f;, )

COMMON_VAL_FOR_SQLDATA
DECLARE_TYPESETTINGS(16)
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC

BEGIN_MAPPING_MEMBERS
m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
m_tSettings[1].POINTER = (void*)(&nParentIndex);
m_tSettings[2].POINTER = (void*)(&fX);
m_tSettings[3].POINTER = (void*)(&fY);
m_tSettings[4].POINTER = (void*)(&fAngle);
m_tSettings[5].POINTER = (void*)(&fScalingX);
m_tSettings[6].POINTER = (void*)(&fScalingY);
m_tSettings[7].POINTER = (void*)(&fZorder);
m_tSettings[8].POINTER = (void*)(&nAtMiliseconds);
m_tSettings[9].POINTER = (void*)(&nVisible);
m_tSettings[10].POINTER = (void*)(&uColor);

m_tSettings[11].POINTER = (void*)(&nTransType[0]);
m_tSettings[12].POINTER = (void*)(&nTransType[1]);
m_tSettings[13].POINTER = (void*)(&nTransType[2]);
m_tSettings[14].POINTER = (void*)(&nTransType[3]);
m_tSettings[15].POINTER = (void*)(&nTransType[4]);

END_MAPPING_MEMBERS

int nParentIndex;
GLfloat fX, fY;
GLfloat fAngle;
GLfloat fScalingX, fScalingY;
GLfloat fZorder;
unsigned int uColor;
int nAtMiliseconds;
int nTransistionType;
int nVisible;
int nTransType[5];

END_CLASS_FROM_SQLDATA

DECLARE_EDITOR_CLASS(DisplayProp);

BEGIN_CLASS_FROM_SQLDATA_WITH_CHILDS(DisplayMetaItem, \
	nTagIndex = 0; m_pValueMonitor = NULL; m_fRotation = 0.0f; m_fScale[0] = 1.0f; m_fScale[1] = 1.0f; \
	memset(szTagItem, 0, sizeof(szTagItem)); nRelatedIndex = 1; \
	nOrigin = nInitPosX = nInitPosY = nParentIndex = nAppearFrom = nAppearTo = nHAlignMode = nVAlignMode = nLimit = nZOrder = 0; \
	fRatioX = fRatioY = fOffsetX = fOffsetY = fOrigX = fOrigY = 0.0f; nWidth = nHeight = 128;, , 1)

	COMMON_VAL_FOR_SQLDATA
	DECLARE_TYPESETTINGS(16)
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC

BEGIN_MAPPING_MEMBERS
m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
m_tSettings[1].POINTER = (void*)(&nParentIndex);
m_tSettings[2].POINTER = (void*)(szTagItem);
m_tSettings[3].POINTER = (void*)(&nInitPosX);
m_tSettings[4].POINTER = (void*)(&nInitPosY);
m_tSettings[5].POINTER = (void*)(&nWidth);
m_tSettings[6].POINTER = (void*)(&nHeight);
m_tSettings[7].POINTER = (void*)(&nHAlignMode);
m_tSettings[8].POINTER = (void*)(&nVAlignMode);
m_tSettings[9].POINTER = (void*)(&nLimit);
m_tSettings[10].POINTER = (void*)(&nAppearFrom);
m_tSettings[11].POINTER = (void*)(&nAppearTo);
m_tSettings[12].POINTER = (void*)(&nZOrder);
m_tSettings[13].POINTER = (void*)(&nOrigin);
m_tSettings[14].POINTER = (void*)(&nTagIndex);
m_tSettings[15].POINTER = (void*)(&nTagVarValue);
\
END_MAPPING_MEMBERS

int nParentIndex;
int nInitPosX;
int nInitPosY;
int nAppearFrom;
int nAppearTo;
int nHAlignMode;
int nVAlignMode;
int nLimit;
int nZOrder;
int nOrigin;
int nWidth;
int nHeight;
int nRelatedIndex;
int nTagIndex;
int nTagVarValue{ 0 };
GLfloat fOrigX, fOrigY;

GLfloat fRatioX, fRatioY, fOffsetX, fOffsetY;
TYC szTagItem[256];


std::shared_ptr<CValueMonitor> m_pValueMonitor;


void SetBufferIndex(int nIndex, CTexPool *pPool);


choreograph::Timeline tLine;

int m_nPrevOrigin;

GLfloat m_fRect[4];			//Whole Rectangle
GLfloat m_fTempRect[10];			//Whole Rectangle

choreograph::Output<GLfloat> m_fTrans[2];		//Translation x,y
choreograph::Output<GLfloat> m_fRotation;		//Rotation
choreograph::Output<GLfloat> m_fScale[2];		//Scaling x,y
choreograph::Output<GLfloat> m_fColor[4];		//Color
choreograph::Output<GLfloat> m_fZorder;			//Zorder
choreograph::Output<int>	m_nVisible;

int nRelatedBufferIndex;			//Index
bool bSelected;



int SetOrigin(int nOrigin, bool bForce = false)
{
	if ((m_nPrevOrigin != nOrigin) || bForce)
	{
		float fHeight = m_fRect[3] - m_fRect[1];
		float fWidth = m_fRect[2] - m_fRect[0];
		switch (nOrigin)
		{
		case 0:
		case 1:
			//LeftTop
			fOrigX = m_fRect[0];
			fOrigY = m_fRect[1];
			break;
		case 2:
			//MidTop
			fOrigX = m_fRect[0] + (fWidth / 2.f);
			fOrigY = m_fRect[1];
			break;
		case 3:
			//RightTop
			fOrigX = m_fRect[0] + fWidth;
			fOrigY = m_fRect[1];
			break;
		case 4:
			//LeftMid
			fOrigX = m_fRect[0];
			fOrigY = m_fRect[1] + (fHeight / 2.f);
			break;
		case 5:
			//Center
			fOrigX = m_fRect[0] + (fWidth / 2.f);
			fOrigY = m_fRect[1] + (fHeight / 2.f);
			break;
		case 6:
			//RightMid
			fOrigX = m_fRect[0] + fWidth;
			fOrigY = m_fRect[1] + (fHeight / 2.f);
			break;
		case 7:
			//LeftBottom
			fOrigX = m_fRect[0];
			fOrigY = m_fRect[1] + fHeight;
			break;
		case 8:
			//MidBottom
			fOrigX = m_fRect[0] + (fWidth / 2.f);
			fOrigY = m_fRect[1] + fHeight;
			break;
		case 9:
			//RightBottom
			fOrigX = m_fRect[0] + fWidth;
			fOrigY = m_fRect[1] + fHeight;
			break;
		}
		fOrigX = fOrigX *(-1.0f);
		fOrigY = fOrigY *(-1.0f);
		return m_nPrevOrigin = nOrigin;
	}
	return 0;
}






END_CLASS_FROM_SQLDATA

DECLARE_EDITOR_CLASS(DisplayMetaItem);



BEGIN_CLASS_FROM_SQLDATA(DisplayMetaItemProp, memset(&nTransType, 0, sizeof(nTransType)); nRelatedIndex = nParentIndex = nAtMiliseconds = nTransistionType = 0; nVisible = 1; uColor = 0xFFFFFFFF; fX = fY = fAngle = fScalingX = fScalingY = fZorder = 0.0f; , )

COMMON_VAL_FOR_SQLDATA
DECLARE_TYPESETTINGS(16)
DECLARE_COMMON_FUNCTIONS OVERRIDE_DUMMY_EDITOR_FUNC

BEGIN_MAPPING_MEMBERS
m_tSettings[0].POINTER = (void*)(&m_nTableIndex);
m_tSettings[1].POINTER = (void*)(&nParentIndex);
m_tSettings[2].POINTER = (void*)(&fX);
m_tSettings[3].POINTER = (void*)(&fY);
m_tSettings[4].POINTER = (void*)(&fAngle);
m_tSettings[5].POINTER = (void*)(&fScalingX);
m_tSettings[6].POINTER = (void*)(&fScalingY);
m_tSettings[7].POINTER = (void*)(&fZorder);
m_tSettings[8].POINTER = (void*)(&nAtMiliseconds);
m_tSettings[9].POINTER = (void*)(&nVisible);
m_tSettings[10].POINTER = (void*)(&uColor);

m_tSettings[11].POINTER = (void*)(&nTransType[0]); // pos easing
m_tSettings[12].POINTER = (void*)(&nTransType[1]); // angle easing
m_tSettings[13].POINTER = (void*)(&nTransType[2]);
m_tSettings[14].POINTER = (void*)(&nTransType[3]);
m_tSettings[15].POINTER = (void*)(&nTransType[4]); // color easing

END_MAPPING_MEMBERS

int nParentIndex;
GLfloat fX, fY;
GLfloat fAngle;
GLfloat fScalingX, fScalingY;
GLfloat fZorder;
unsigned int uColor;
int nAtMiliseconds;
int nTransistionType;
int nVisible;
int nRelatedIndex;
int nTransType[5];

END_CLASS_FROM_SQLDATA

DECLARE_EDITOR_CLASS(DisplayMetaItemProp);

struct findDisplayItemByRelatedItem : public std::unary_function<SHARED_PTRC(CSQLData), bool>
{
	findDisplayItemByRelatedItem(int idx) : m_idx(idx)
	{

	}
	bool operator()(SHARED_PTRC(CSQLData) &p)
	{
		auto *c = dynamic_cast<DisplayItemPool*>(p.get());
		return(c->m_nTableIndex == m_idx);
	}
private:
	int m_idx;
};

struct findDisplayItemByDisplayType : public std::unary_function<SHARED_PTRC(CSQLData), bool>
{
	findDisplayItemByDisplayType(int idx) : m_idx(idx)
	{

	}
	bool operator()(SHARED_PTRC(CSQLData) &p)
	{
		auto *c = dynamic_cast<DisplayItemPool*>(p.get());
		return(c->nDisplayType == m_idx);
	}
private:
	int m_idx;
};