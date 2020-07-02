#ifndef TEXPOOL
#define TEXPOOL

#include <vector>
#ifdef PAC_EDITOR
#include <QtGui>
#include <qopenglfunctions.h>
#else if
#include <GLES2/gl2.h>
#endif

typedef struct _TEXTUREINDEX
{
	int nTextureIndex;
	GLsizei iCount;
	GLsizei iOffset;
	int nSecTextureIndex;
	GLsizei iCountVtx;
	GLsizei iOffsetVtx;
	GLuint uFrameBufferIdx;
}TEXTUREINDEX;

class CTexPool
{
public:
	CTexPool( GLfloat fLeft, GLfloat fTop, GLfloat fRight, GLfloat fBottom)
	{
		m_nPrevOrigin = 0;
		m_fRect[0] = fLeft;
		m_fRect[1] = fTop;
		m_fRect[2] = fRight;
		m_fRect[3] = fBottom;

		m_fColor[0] = 1.0f;
		m_fColor[1] = 1.0f;
		m_fColor[2] = 1.0f;
		m_fColor[3] = 1.0f;

		m_fTrans[0] = 0.0f;
		m_fTrans[1] = 0.0f;

		m_fRotation = 0.0f;
		
		m_fScale[0] = 1.0f;
		m_fScale[1] = 1.0f;
		
		m_fOrigin[0] = 0.0f;
		m_fOrigin[1] = 0.0f;
		
		SetOrigin(5);//Default
	}

	virtual ~CTexPool()
	{

	}

	int SetOrigin(int nOrigin,bool bForce=false)
	{
		if (((m_nPrevOrigin != nOrigin)&& nOrigin)||bForce)
		{
			float fHeight = m_fRect[3] - m_fRect[1];
			float fWidth = m_fRect[2] - m_fRect[0];
			switch (nOrigin)
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
			m_nPrevOrigin = nOrigin;
			return m_nPrevOrigin;
		}
		return 0;
	}

	void AddIndex(int nPrimTextureIndex, GLsizei iCount, GLsizei iOffset, int nSecTextureIndex = 0, GLsizei iCountVtx=0, GLsizei iOffsetVtx=0,GLuint uFrameBufferIdx=0)
	{
		vIdxList.push_back({ nPrimTextureIndex,iCount,iOffset,nSecTextureIndex,iCountVtx,iOffsetVtx ,uFrameBufferIdx });
    }

public:
	int m_nPrevOrigin;
	GLfloat m_fRect[4];			//Whole Rectangle
	GLfloat m_fTrans[2];		//Translation x,y
	GLfloat m_fRotation;		//Rotation
	GLfloat m_fScale[2];		//Scaling x,y
	GLfloat m_fOrigin[2];		//Origin Coordinate
	GLfloat m_fColor[4];		//Color
	std::vector<TEXTUREINDEX> vIdxList;
};

#endif
