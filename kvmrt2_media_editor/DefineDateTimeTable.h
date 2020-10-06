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


BEGIN_CLASS_FROM_SQLDATA_WITH_CHILDS(DisplayDateTimeItem, 
	uBackColor = 0xffffffff; nPrevOrigin = -1; nRelatedItemListIndex = nInitPosX = nInitPosY = nParentIndex = nAppearFrom = nAppearTo = nZOrder = 0; nOrigin = 1; fOrigX = fOrigY = 0.0f; , , 1)
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
DECLARE_EDITOR_CLASS(DisplayDateTimeItem);



BEGIN_CLASS_FROM_SQLDATA(DisplayDateTimeProp, nParentIndex = nAtMiliseconds = nTransistionType = 0; nTransType[0] = nTransType[1] = nTransType[2] = nTransType[3] = nTransType[4] = 1; nVisible = 1; uColor = 0xFFFFFFFF; fX = fY = fAngle = fScalingX = fScalingY = fZorder = 0.0f;, )

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

DECLARE_EDITOR_CLASS(DisplayDateTimeProp);

