#include "CTextureInfo.h"
#include <qdebug>

#define M_PI 3.1415926535897932384626433832795f

int CTextureInfo::m_nRectCount = 0;
QOpenGLFunctions *CTextureInfo::m_pFunctions = NULL;

CTextureInfo::CTextureInfo()
{
	m_uVBOsID[0] = -1;
	m_uVBOsID[1] = -1;
	m_uVBOsID[2] = -1;
}


CTextureInfo::~CTextureInfo()
{
}

CTextureInfo* CTextureInfo::GetInstance()
{
	static CTextureInfo tInst;
	return &tInst;
}

bool CTextureInfo::SetOpenGLFunctions(QOpenGLFunctions *pFunctions)
{
	m_pFunctions = pFunctions;
	return true;
}


//텍스쳐 정보 저장


unsigned int CTextureInfo::AddTextureInformation(int nParent, int nItemType, int nRegisterIndex, GLuint uSocTexIdx, GLfloat fSocWidth, GLfloat fSocHeight, GLfloat fSocLeft, GLfloat fSocTop, GLfloat fSocRight, GLfloat fSocBottom
	, GLuint uDesTexIdx, GLuint uDesFB,GLfloat uTexCoordX,GLfloat uTexCoordY)
{
	m_vTextureInfo.push_back({ nParent,nItemType,nRegisterIndex,uSocTexIdx,fSocWidth ,fSocHeight ,
		fSocLeft ,fSocTop ,fSocRight ,fSocTop,fSocLeft,fSocBottom,fSocRight ,fSocBottom ,0,1,2,2,1,3 ,
		uDesTexIdx,uDesFB ,uTexCoordX ,uTexCoordY });

	return m_vTextureInfo.size();
}
bool CTextureInfo::ReplaceSocTextureID(GLuint uOldId, GLuint uNewId)
{
	/*std::for_each(m_vTextureInfo.begin(), m_vTextureInfo.end(), [uOldId, uNewId](TextureInfo &info)
	{
		if (info.pDesTexIdx)
			info.nDesTexIdx = (*info.pDesTexIdx);
		else
			info.nDesTexIdx = 0;
		if (info.pSocTexIdx)
			info.nSocTexIdx = (*info.pSocTexIdx);
		else
			info.nSocTexIdx = 0;
	});

	for (auto info = m_mFinalRectInfo.begin(); info != m_mFinalRectInfo.end(); info++)
	{
		if (info->second.pDesTexIdx)
			info->second.nDesTexIdx = (*info->second.pDesTexIdx);
		else
			info->second.nDesTexIdx = 0;
		if (info->second.pSocTexIdx)
			info->second.nSocTexIdx = (*info->second.pSocTexIdx);
		else
			info->second.nSocTexIdx = 0;
	}

	for (auto info = m_mInterRectInfo.begin(); info != m_mInterRectInfo.end(); info++)
	{
		if (info->second.pDesTexIdx)
			info->second.nDesTexIdx = (*info->second.pDesTexIdx);
		else
			info->second.nDesTexIdx = 0;
		if (info->second.pSocTexIdx)
			info->second.nSocTexIdx = (*info->second.pSocTexIdx);
		else
			info->second.nSocTexIdx = 0;
	}*/

	/*for (auto info = m_mFrameBuf.begin(); info != m_mFrameBuf.end(); info++)
	{
		
	}*/
	return false;
}




int CTextureInfo::GetTextureIndex(int nParent,int nItemType)
{
	auto it=std::find_if(m_vTextureInfo.begin(), m_vTextureInfo.end(), [&nParent, &nItemType](TextureInfo &tex)
	{
		return (tex.nItemType == nItemType) && (tex.nParent == nParent);
	});

	if (it != m_vTextureInfo.end())
		return it->nRegisterIndex;
	return 0;
}

int CTextureInfo::GetTransformed(int nRegisteredIndex, std::vector<GLfloat> &vVertex, std::vector<GLushort> &vIndices, GLfloat fXPos, GLfloat fYPos, GLfloat fXOffset, GLfloat fYOffset, GLfloat fAngle, int nCenterPoint,GLfloat fRed, GLfloat fGreen, GLfloat fBlue, GLfloat fAlpha)
{
	//Create contents for Vertex Buffer Object 
	//Create contents for Index Buffer Object 
	auto it = std::find_if(m_vTextureInfo.begin(), m_vTextureInfo.end(), [&nRegisteredIndex](TextureInfo &tex)
	{
		return (tex.nRegisterIndex == nRegisteredIndex);
	});
	if (it != m_vTextureInfo.end())
	{
		GLfloat fCoord[32];
		GLfloat fCoordTemp[16];
		GLfloat fCoordCenter[2];
		GLfloat fSinAngle, fCosAngle;
		GLfloat fLeft, fTop;
		GLushort uShort[6];
		fCoordCenter[0] = fXPos + fXOffset;
		fCoordCenter[1] = fYPos + fYOffset;
		int nVertexIndex = vVertex.size() / 8;
		// float 2 for position
		// float 2 for texture coodinate
		// float 4 for vertex color
		// rectangle -> 4 vertices
		// (2+2+4)*4 = 32 float array per object

		switch (nCenterPoint)
		{
		case 0:
		case 1:
			fCoord[0] = fCoordCenter[0];
			fCoord[1] = fCoordCenter[1];
			break;
		case 2:
			fCoord[0] = fCoordCenter[0] - (it->fCoord[0] / 2.f);
			fCoord[1] = fCoordCenter[1];
			break;
		case 3:
			fCoord[0] = fCoordCenter[0] - it->fCoord[0];
			fCoord[1] = fCoordCenter[1];
			break;
		case 4:
			fCoord[0] = fCoordCenter[0];
			fCoord[1] = fCoordCenter[1] - (it->fCoord[1] / 2.f);
			break;
		case 5:
			fCoord[0] = fCoordCenter[0] - (it->fCoord[0] / 2.f);
			fCoord[1] = fCoordCenter[1] - (it->fCoord[1] / 2.f);
			break;
		case 6:
			fCoord[0] = fCoordCenter[0] - it->fCoord[0];
			fCoord[1] = fCoordCenter[1] - (it->fCoord[1] / 2.f);
			break;
		case 7:
			fCoord[0] = fCoordCenter[0];
			fCoord[1] = fCoordCenter[1] - it->fCoord[1];
			break;
		case 8:
			fCoord[0] = fCoordCenter[0] - (it->fCoord[0] / 2.f);
			fCoord[1] = fCoordCenter[1] - it->fCoord[1];
			break;
		case 9:
			fCoord[0] = fCoordCenter[0] - it->fCoord[0];
			fCoord[1] = fCoordCenter[1] - it->fCoord[1];
			break;
		}


		fSinAngle = sinf(fAngle * M_PI / 180.0f);
		fCosAngle = cosf(fAngle * M_PI / 180.0f);


		fCoord[4] = ((long)(fCoord[0] + it->fCoord[0]));
		fCoord[5] = ((long)(fCoord[1]));

		fCoord[8] = ((long)(fCoord[0]));
		fCoord[9] = ((long)(fCoord[1] + it->fCoord[1]));

		fCoord[12] = ((long)(fCoord[0] + it->fCoord[0]));
		fCoord[13] = ((long)(fCoord[1] + it->fCoord[1]));




		fCoordTemp[0] = ((fCoord[0] - fCoordCenter[0])*fCosAngle) - ((fCoord[1] - fCoordCenter[1])*fSinAngle) + fCoordCenter[0];
		fCoordTemp[1] = ((fCoord[0] - fCoordCenter[0])*fSinAngle) + ((fCoord[1] - fCoordCenter[1])*fCosAngle) + fCoordCenter[1];

		fCoordTemp[4] = ((fCoord[4] - fCoordCenter[0])*fCosAngle) - ((fCoord[5] - fCoordCenter[1])*fSinAngle) + fCoordCenter[0];
		fCoordTemp[5] = ((fCoord[4] - fCoordCenter[0])*fSinAngle) + ((fCoord[5] - fCoordCenter[1])*fCosAngle) + fCoordCenter[1];

		fCoordTemp[8] = ((fCoord[8] - fCoordCenter[0])*fCosAngle) - ((fCoord[9] - fCoordCenter[1])*fSinAngle) + fCoordCenter[0];
		fCoordTemp[9] = ((fCoord[8] - fCoordCenter[0])*fSinAngle) + ((fCoord[9] - fCoordCenter[1])*fCosAngle) + fCoordCenter[1];

		fCoordTemp[12] = ((fCoord[12] - fCoordCenter[0])*fCosAngle) - ((fCoord[13] - fCoordCenter[1])*fSinAngle) + fCoordCenter[0];
		fCoordTemp[13] = ((fCoord[12] - fCoordCenter[0])*fSinAngle) + ((fCoord[13] - fCoordCenter[1])*fCosAngle) + fCoordCenter[1];


		fCoord[0] = fCoordTemp[0];
		fCoord[1] = fCoordTemp[1];

		fCoord[8] = fCoordTemp[4];
		fCoord[9] = fCoordTemp[5];

		fCoord[16] = fCoordTemp[8];
		fCoord[17] = fCoordTemp[9];

		fCoord[24] = fCoordTemp[12];
		fCoord[25] = fCoordTemp[13];

		fCoord[2] = it->fTexCoord[0];
		fCoord[3] = it->fTexCoord[1];

		fCoord[10] = it->fTexCoord[2];
		fCoord[11] = it->fTexCoord[3];

		fCoord[18] = it->fTexCoord[4];
		fCoord[19] = it->fTexCoord[5];

		fCoord[26] = it->fTexCoord[6];
		fCoord[27] = it->fTexCoord[7];



		fCoord[4] = fRed;
		fCoord[5] = fGreen;
		fCoord[6] = fBlue;
		fCoord[7] = fAlpha;

		fCoord[12] = fRed;
		fCoord[13] = fGreen;
		fCoord[14] = fBlue;
		fCoord[15] = fAlpha;

		fCoord[20] = fRed;
		fCoord[21] = fGreen;
		fCoord[22] = fBlue;
		fCoord[23] = fAlpha;

		fCoord[28] = fRed;
		fCoord[29] = fGreen;
		fCoord[30] = fBlue;
		fCoord[31] = fAlpha;


		vVertex.insert(vVertex.end(), &fCoord[0], &fCoord[32]);

		uShort[0] = it->uIndex[0] + nVertexIndex;
		uShort[1] = it->uIndex[1] + nVertexIndex;
		uShort[2] = it->uIndex[2] + nVertexIndex;
		uShort[3] = it->uIndex[3] + nVertexIndex;
		uShort[4] = it->uIndex[4] + nVertexIndex;
		uShort[5] = it->uIndex[5] + nVertexIndex;

		FinalRectInfo tRectInfo;
		tRectInfo.bDest = false;
		tRectInfo.nOffset = vIndices.size();
		tRectInfo.nSize = 6;
		tRectInfo.nRegisterIndex = m_nRectCount++;
		tRectInfo.uDesTexIdx= it->uDesTexIdx;
		tRectInfo.uSocTexIdx = it->uSocTexIdx;
		tRectInfo.uFrameBufferIdx = it->uFrameBufferIdx;
		vIndices.insert(vIndices.end(), &uShort[0], &uShort[6]);

		m_mFinalRectInfo[tRectInfo.nRegisterIndex] = tRectInfo;
		return tRectInfo.nRegisterIndex;
	}
	return 0;
}



int CTextureInfo::GetTransformed8(int nRegisteredIndex, std::vector<GLfloat> &vVertex, std::vector<GLushort> &vIndices,GLfloat *pWholeRect,GLfloat fXPos, GLfloat fYPos, GLfloat fXOffset, GLfloat fYOffset, GLfloat fAngle, int nCenterPoint,GLfloat fRed, GLfloat fGreen, GLfloat fBlue, GLfloat fAlpha)
{
	auto it = std::find_if(m_vTextureInfo.begin(), m_vTextureInfo.end(), [&nRegisteredIndex](TextureInfo &tex)
	{
		return (tex.nRegisterIndex == nRegisteredIndex);
	});
	if (it != m_vTextureInfo.end())
	{
		GLfloat fCoord[32];
		GLfloat fCoordTemp[16];
		GLfloat fCoordCenter[2];
		GLfloat fSinAngle, fCosAngle;
		GLfloat fLeft, fTop;
		GLushort uShort[6];
		int nVertexIndex;



		fCoordCenter[0] = fXPos;
		fCoordCenter[1] = fYPos;




		nVertexIndex = vVertex.size() / 8;
		// float 2 for position
		// float 2 for texture coodinate
		// float 4 for vertex color
		// rectangle -> 4 vertices
		// (2+2+4)*4 = 32 float array per object



		switch (nCenterPoint)
		{
		case 0:
		case 1:
			fCoord[0] = fCoordCenter[0];
			fCoord[1] = fCoordCenter[1];
			break;
		case 2:
			fCoord[0] = fCoordCenter[0] - (pWholeRect[2] / 2.f);
			fCoord[1] = fCoordCenter[1];
			break;
		case 3:
			fCoord[0] = fCoordCenter[0] - pWholeRect[2];
			fCoord[1] = fCoordCenter[1];
			break;
		case 4:
			fCoord[0] = fCoordCenter[0];
			fCoord[1] = fCoordCenter[1] - (pWholeRect[3] / 2.f);
			break;
		case 5:
			fCoord[0] = fCoordCenter[0] - (pWholeRect[2] / 2.f);
			fCoord[1] = fCoordCenter[1] - (pWholeRect[3] / 2.f);
			break;
		case 6:
			fCoord[0] = fCoordCenter[0] - pWholeRect[2];
			fCoord[1] = fCoordCenter[1] - (pWholeRect[3] / 2.f);
			break;
		case 7:
			fCoord[0] = fCoordCenter[0];
			fCoord[1] = fCoordCenter[1] - pWholeRect[3];
			break;
		case 8:
			fCoord[0] = fCoordCenter[0] - (pWholeRect[2] / 2.f);
			fCoord[1] = fCoordCenter[1] - pWholeRect[3];
			break;
		case 9:
			fCoord[0] = fCoordCenter[0] - pWholeRect[2];
			fCoord[1] = fCoordCenter[1] - pWholeRect[3];
			break;
		}


		fSinAngle = sinf(fAngle * M_PI / 180.0f);
		fCosAngle = cosf(fAngle * M_PI / 180.0f);

		fCoord[0] += fXOffset;
		fCoord[1] += fYOffset;

		fCoord[4] = ((long)(fCoord[0] + it->fCoord[0]));		//너비 
		fCoord[5] = ((long)(fCoord[1]));

		fCoord[8] = ((long)(fCoord[0]));
		fCoord[9] = ((long)(fCoord[1] + it->fCoord[1]));		//높이

		fCoord[12] = ((long)(fCoord[0] + it->fCoord[0]));		//너비
		fCoord[13] = ((long)(fCoord[1] + it->fCoord[1]));		//높이






		fCoordTemp[0] = ((fCoord[0] - fCoordCenter[0])*fCosAngle) - ((fCoord[1] - fCoordCenter[1])*fSinAngle) + fCoordCenter[0];		//회전
		fCoordTemp[1] = ((fCoord[0] - fCoordCenter[0])*fSinAngle) + ((fCoord[1] - fCoordCenter[1])*fCosAngle) + fCoordCenter[1];		//회전

		fCoordTemp[4] = ((fCoord[4] - fCoordCenter[0])*fCosAngle) - ((fCoord[5] - fCoordCenter[1])*fSinAngle) + fCoordCenter[0];		//회전
		fCoordTemp[5] = ((fCoord[4] - fCoordCenter[0])*fSinAngle) + ((fCoord[5] - fCoordCenter[1])*fCosAngle) + fCoordCenter[1];

		fCoordTemp[8] = ((fCoord[8] - fCoordCenter[0])*fCosAngle) - ((fCoord[9] - fCoordCenter[1])*fSinAngle) + fCoordCenter[0];
		fCoordTemp[9] = ((fCoord[8] - fCoordCenter[0])*fSinAngle) + ((fCoord[9] - fCoordCenter[1])*fCosAngle) + fCoordCenter[1];

		fCoordTemp[12] = ((fCoord[12] - fCoordCenter[0])*fCosAngle) - ((fCoord[13] - fCoordCenter[1])*fSinAngle) + fCoordCenter[0];
		fCoordTemp[13] = ((fCoord[12] - fCoordCenter[0])*fSinAngle) + ((fCoord[13] - fCoordCenter[1])*fCosAngle) + fCoordCenter[1];



		fCoord[0] = fCoordTemp[0];
		fCoord[1] = fCoordTemp[1];

		fCoord[8] = fCoordTemp[4];
		fCoord[9] = fCoordTemp[5];

		fCoord[16] = fCoordTemp[8];
		fCoord[17] = fCoordTemp[9];

		fCoord[24] = fCoordTemp[12];
		fCoord[25] = fCoordTemp[13];





		fCoord[2] = it->fTexCoord[0];
		fCoord[3] = it->fTexCoord[1];

		fCoord[10] = it->fTexCoord[2];
		fCoord[11] = it->fTexCoord[3];

		fCoord[18] = it->fTexCoord[4];
		fCoord[19] = it->fTexCoord[5];

		fCoord[26] = it->fTexCoord[6];
		fCoord[27] = it->fTexCoord[7];



		fCoord[4] = fRed;
		fCoord[5] = fGreen;
		fCoord[6] = fBlue;
		fCoord[7] = fAlpha;

		fCoord[12] = fRed;
		fCoord[13] = fGreen;
		fCoord[14] = fBlue;
		fCoord[15] = fAlpha;

		fCoord[20] = fRed;
		fCoord[21] = fGreen;
		fCoord[22] = fBlue;
		fCoord[23] = fAlpha;

		fCoord[28] = fRed;
		fCoord[29] = fGreen;
		fCoord[30] = fBlue;
		fCoord[31] = fAlpha;



		vVertex.insert(vVertex.end(), &fCoord[0], &fCoord[32]);

		uShort[0] = it->uIndex[0] + nVertexIndex;
		uShort[1] = it->uIndex[1] + nVertexIndex;
		uShort[2] = it->uIndex[2] + nVertexIndex;
		uShort[3] = it->uIndex[3] + nVertexIndex;
		uShort[4] = it->uIndex[4] + nVertexIndex;
		uShort[5] = it->uIndex[5] + nVertexIndex;


		FinalRectInfo tRectInfo;
		tRectInfo.bDest = false;
		tRectInfo.nOffset = vIndices.size();
		tRectInfo.nSize = 6;
		tRectInfo.nRegisterIndex = m_nRectCount++;
		tRectInfo.uDesTexIdx = it->uDesTexIdx;
		tRectInfo.uSocTexIdx = it->uSocTexIdx;
		tRectInfo.uFrameBufferIdx = it->uFrameBufferIdx;


		vIndices.insert(vIndices.end(), &uShort[0], &uShort[6]);


		m_mFinalRectInfo[tRectInfo.nRegisterIndex ] = tRectInfo;
		return tRectInfo.nRegisterIndex;
	}
	return 0;
}






bool CTextureInfo::GetTextureInfo(int nRegisteredIndex, std::vector<GLfloat> &vVertex, std::vector<GLushort> &vIndices, GLfloat fXPos, GLfloat fYPos,GLsizei *pCount,GLsizei *pOffset,GLint *pTexIdx)
{
	auto it = std::find_if(m_vTextureInfo.begin(), m_vTextureInfo.end(), [&nRegisteredIndex](TextureInfo &tex)
	{
		return (tex.nRegisterIndex == nRegisteredIndex);
	});
	if (it != m_vTextureInfo.end())
	{
		GLfloat fCoord[32];
		GLfloat fCoordTemp[16];
		GLfloat fCoordCenter[2];
		GLfloat fSinAngle, fCosAngle;
		GLfloat fLeft, fTop;
		GLushort uShort[6];
		int nVertexIndex = vVertex.size() / 4;

		fCoordCenter[0] = fXPos;
		fCoordCenter[1] = fYPos;
		// float 2 for position
		// float 2 for texture coodinate
		// rectangle -> 4 vertices
		// (2+2)*4 = 16 float array per object

		fCoord[0] = fCoordCenter[0];
		fCoord[1] = fCoordCenter[1];

		fCoord[4] = ((long)(fCoord[0] + it->fCoord[0]));		//너비 
		fCoord[5] = ((long)(fCoord[1]));

		fCoord[8] = ((long)(fCoord[0]));
		fCoord[9] = ((long)(fCoord[1] + it->fCoord[1]));		//높이

		fCoord[12] = ((long)(fCoord[0] + it->fCoord[0]));		//너비
		fCoord[13] = ((long)(fCoord[1] + it->fCoord[1]));		//높이

		fCoord[2] = it->fTexCoord[0];
		fCoord[3] = it->fTexCoord[1];

		fCoord[6] = it->fTexCoord[2];
		fCoord[7] = it->fTexCoord[3];

		fCoord[10] = it->fTexCoord[4];
		fCoord[11] = it->fTexCoord[5];

		fCoord[14] = it->fTexCoord[6];
		fCoord[15] = it->fTexCoord[7];

		vVertex.insert(vVertex.end(), &fCoord[0], &fCoord[16]);

		(*pOffset) = vIndices.size();

		uShort[0] = it->uIndex[0] + nVertexIndex;
		uShort[1] = it->uIndex[1] + nVertexIndex;
		uShort[2] = it->uIndex[2] + nVertexIndex;
		uShort[3] = it->uIndex[3] + nVertexIndex;
		uShort[4] = it->uIndex[4] + nVertexIndex;
		uShort[5] = it->uIndex[5] + nVertexIndex;

		vIndices.insert(vIndices.end(), &uShort[0], &uShort[6]);

		(*pTexIdx) = it->uSocTexIdx;
		(*pCount) = 6;
		return true;
	}
	return false;
}



bool CTextureInfo::GetTextureInfo(std::vector<GLfloat> &vVertex, std::vector<GLushort> &vIndices, 
	GLfloat fTexPosX, GLfloat fTexPosY,GLfloat fTexWidth,GLfloat fTexHeight,GLfloat fTexWholeWidth,GLfloat fTexWholeHeight,GLfloat fTextureOffset,GLsizei *pCount, GLsizei *pOffset,GLuint uVBOId, GLuint uIBOId, GLfloat fPosX, GLfloat fPosY)
{
	
		GLfloat fCoord[32];
		GLfloat fCoordTemp[16];
		GLfloat fCoordCenter[2];
		GLfloat fSinAngle, fCosAngle;
		GLfloat fLeft, fTop;
		GLushort uShort[6];
		int nVertexIndex = vVertex.size() / 4;

		fCoord[0] = fPosX;
		fCoord[1] = fPosY;

		fCoord[4] = fPosX+fTexWidth;
		fCoord[5] = fPosY;

		fCoord[8] = fPosX;
		fCoord[9] = fPosY+fTexHeight;		//높이

		fCoord[12] = fPosX+fTexWidth;		//너비
		fCoord[13] = fPosY+fTexHeight;		//높이

		fCoord[2] = (fTexPosX+ fTextureOffset)/ fTexWholeWidth;
		fCoord[3] = (fTexPosY+ fTextureOffset) / fTexWholeHeight;

		fCoord[6] = (fTexPosX+ fTexWidth- fTextureOffset) / fTexWholeWidth;
		fCoord[7] = (fTexPosY+ fTextureOffset) / fTexWholeHeight;

		fCoord[10] = (fTexPosX+ fTextureOffset) / fTexWholeWidth;
		fCoord[11] = (fTexPosY + fTexHeight- fTextureOffset) / fTexWholeHeight;

		fCoord[14] = (fTexPosX + fTexWidth- fTextureOffset) / fTexWholeWidth;
		fCoord[15] = (fTexPosY + fTexHeight- fTextureOffset) / fTexWholeHeight;

		
		m_pFunctions->glBindBuffer(GL_ARRAY_BUFFER, uVBOId);
		m_pFunctions->glBufferSubData(GL_ARRAY_BUFFER, vVertex.size() * sizeof(GLfloat), 16 * sizeof(GLfloat), &fCoord[0]);
		m_pFunctions->glBindBuffer(GL_ARRAY_BUFFER, 0);
		

		vVertex.insert(vVertex.end(), &fCoord[0], &fCoord[16]);

		(*pOffset) = vIndices.size();

		uShort[0] = 0 + nVertexIndex;
		uShort[1] = 1 + nVertexIndex;
		uShort[2] = 2 + nVertexIndex;
		uShort[3] = 2 + nVertexIndex;
		uShort[4] = 1 + nVertexIndex;
		uShort[5] = 3 + nVertexIndex;

		m_pFunctions->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uIBOId);
		m_pFunctions->glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, vIndices.size() * sizeof(GLushort), 6 * sizeof(GLushort), &uShort[0]);
		m_pFunctions->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



		vIndices.insert(vIndices.end(), &uShort[0], &uShort[6]);

		(*pCount) = 6;
		return true;
}

bool CTextureInfo::GetTextureInfo(std::vector<GLfloat> &vVertex, GLfloat fX, GLfloat fY,GLfloat *pFloat,int nSize, GLsizei *pCount, GLsizei *pOffset,GLuint uVBOId)
{
	int nTempSize = vVertex.size();


	for (int i = 0; i < nSize; i += 2)
	{
		vVertex.push_back(pFloat[i] + fX);
		vVertex.push_back(1024-(pFloat[i + 1] + fY));
	}
	m_pFunctions->glBindBuffer(GL_ARRAY_BUFFER, uVBOId);
	m_pFunctions->glBufferSubData(GL_ARRAY_BUFFER, nTempSize *sizeof(GLfloat), nSize * sizeof(GLfloat),&vVertex[nTempSize]);
	m_pFunctions->glBindBuffer(GL_ARRAY_BUFFER, 0);
	(*pOffset) = (nTempSize / 2);
	(*pCount) = nSize/2;
	return true;
}




bool CTextureInfo::GetTextureInfo(std::vector<GLfloat> &vVertex, std::vector<GLushort> &vIndices,
	GLfloat fTexPosX, GLfloat fTexPosY, GLfloat fTexWidth, GLfloat fTexHeight, GLsizei iOffset, GLsizei iCount, GLsizei *pCount, GLsizei *pOffset, GLuint uVBOId, GLuint uIBOId, GLfloat fPosX, GLfloat fPosY)
{

	GLfloat fCoord[32];
	GLfloat fCoordTemp[16];
	GLfloat fCoordCenter[2];
	GLfloat fSinAngle, fCosAngle;
	GLfloat fLeft, fTop;
	GLushort uShort[6];
	int nVertexIndex = vVertex.size() / 4;

	fCoord[0] = fPosX;
	fCoord[1] = fPosY;

	fCoord[4] = fPosX + fTexWidth;
	fCoord[5] = fPosY;

	fCoord[8] = fPosX;
	fCoord[9] = fPosY + fTexHeight;		//높이

	fCoord[12] = fPosX + fTexWidth;		//너비
	fCoord[13] = fPosY + fTexHeight;		//높이



	int nTempIndex = vIndices[iOffset];

	fCoord[2] = vVertex[((nTempIndex ) * 4) + 2];
	fCoord[3] = vVertex[((nTempIndex) * 4) + 3];

	fCoord[6] = vVertex[((nTempIndex + 1) * 4) + 2];
	fCoord[7] = vVertex[((nTempIndex + 1) * 4) + 3];

	fCoord[10] = vVertex[((nTempIndex + 2) * 4) + 2];
	fCoord[11] = vVertex[((nTempIndex + 2) * 4) + 3];

	fCoord[14] = vVertex[((nTempIndex + 3) * 4) + 2];
	fCoord[15] = vVertex[((nTempIndex + 3) * 4) + 3];


	m_pFunctions->glBindBuffer(GL_ARRAY_BUFFER, uVBOId);
	m_pFunctions->glBufferSubData(GL_ARRAY_BUFFER, vVertex.size() * sizeof(GLfloat), 16 * sizeof(GLfloat), &fCoord[0]);
	m_pFunctions->glBindBuffer(GL_ARRAY_BUFFER, 0);





	vVertex.insert(vVertex.end(), &fCoord[0], &fCoord[16]);

	(*pOffset) = vIndices.size();

	uShort[0] = 0 + nVertexIndex;
	uShort[1] = 1 + nVertexIndex;
	uShort[2] = 2 + nVertexIndex;
	uShort[3] = 2 + nVertexIndex;
	uShort[4] = 1 + nVertexIndex;
	uShort[5] = 3 + nVertexIndex;

	m_pFunctions->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uIBOId);
	m_pFunctions->glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, vIndices.size() * sizeof(GLushort), 6 * sizeof(GLushort), &uShort[0]);
	m_pFunctions->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



	vIndices.insert(vIndices.end(), &uShort[0], &uShort[6]);

	(*pCount) = 6;
	return true;
}



void CTextureInfo::ClearTextureInfo()
{
	m_vTextureInfo.clear();
}







int CTextureInfo::GetTransformed9(int nRegisteredIndex, std::vector<GLfloat> &vVertexArrow, std::vector<GLfloat> &vVertex, std::vector<GLushort> &vIndices, GLfloat *pFloat, int nSize, GLfloat fXPos, GLfloat fYPos, GLfloat fXOffset, GLfloat fYOffset, GLfloat fRed, GLfloat fGreen, GLfloat fBlue, GLfloat fAlpha)
{
	//Create contents for Vertex Buffer Object 
	//Create contents for Index Buffer Object 
	auto it = std::find_if(m_vTextureInfo.begin(), m_vTextureInfo.end(), [&nRegisteredIndex](TextureInfo &tex)
	{
		return (tex.nRegisterIndex == nRegisteredIndex);
	});
	if (it != m_vTextureInfo.end())
	{
		GLfloat fCoord[32];
		GLfloat fCoordTemp[16];
		GLfloat fCoordCenter[2];
		GLfloat fSinAngle, fCosAngle;
		GLfloat fLeft, fTop;
		GLushort uShort[6];
		fCoordCenter[0] = fXPos + fXOffset;
		fCoordCenter[1] = fYPos + fYOffset;
		int nVertexIndex = vVertex.size() / 8;
		// float 2 for position
		// float 2 for texture coodinate
		// float 4 for vertex color
		// rectangle -> 4 vertices
		// (2+2+4)*4 = 32 float array per object

		
		fCoord[0] = fCoordCenter[0];
		fCoord[1] = fCoordCenter[1];
			
		fSinAngle = sinf(0.0f * M_PI / 180.0f);
		fCosAngle = cosf(0.0f * M_PI / 180.0f);

		fCoord[4] = ((long)(fCoord[0] + it->fCoord[0]));
		fCoord[5] = ((long)(fCoord[1]));

		fCoord[8] = ((long)(fCoord[0]));
		fCoord[9] = ((long)(fCoord[1] + it->fCoord[1]));

		fCoord[12] = ((long)(fCoord[0] + it->fCoord[0]));
		fCoord[13] = ((long)(fCoord[1] + it->fCoord[1]));

		fCoordTemp[0] = ((fCoord[0] - fCoordCenter[0])*fCosAngle) - ((fCoord[1] - fCoordCenter[1])*fSinAngle) + fCoordCenter[0];
		fCoordTemp[1] = ((fCoord[0] - fCoordCenter[0])*fSinAngle) + ((fCoord[1] - fCoordCenter[1])*fCosAngle) + fCoordCenter[1];

		fCoordTemp[4] = ((fCoord[4] - fCoordCenter[0])*fCosAngle) - ((fCoord[5] - fCoordCenter[1])*fSinAngle) + fCoordCenter[0];
		fCoordTemp[5] = ((fCoord[4] - fCoordCenter[0])*fSinAngle) + ((fCoord[5] - fCoordCenter[1])*fCosAngle) + fCoordCenter[1];

		fCoordTemp[8] = ((fCoord[8] - fCoordCenter[0])*fCosAngle) - ((fCoord[9] - fCoordCenter[1])*fSinAngle) + fCoordCenter[0];
		fCoordTemp[9] = ((fCoord[8] - fCoordCenter[0])*fSinAngle) + ((fCoord[9] - fCoordCenter[1])*fCosAngle) + fCoordCenter[1];

		fCoordTemp[12] = ((fCoord[12] - fCoordCenter[0])*fCosAngle) - ((fCoord[13] - fCoordCenter[1])*fSinAngle) + fCoordCenter[0];
		fCoordTemp[13] = ((fCoord[12] - fCoordCenter[0])*fSinAngle) + ((fCoord[13] - fCoordCenter[1])*fCosAngle) + fCoordCenter[1];

		fCoord[0] = fCoordTemp[0];
		fCoord[1] = fCoordTemp[1];

		fCoord[8] = fCoordTemp[4];
		fCoord[9] = fCoordTemp[5];

		fCoord[16] = fCoordTemp[8];
		fCoord[17] = fCoordTemp[9];

		fCoord[24] = fCoordTemp[12];
		fCoord[25] = fCoordTemp[13];

		fCoord[2] = it->fTexCoord[0];
		fCoord[3] = it->fTexCoord[1];

		fCoord[10] = it->fTexCoord[2];
		fCoord[11] = it->fTexCoord[3];

		fCoord[18] = it->fTexCoord[4];
		fCoord[19] = it->fTexCoord[5];

		fCoord[26] = it->fTexCoord[6];
		fCoord[27] = it->fTexCoord[7];



		fCoord[4] = fRed;
		fCoord[5] = fGreen;
		fCoord[6] = fBlue;
		fCoord[7] = fAlpha;

		fCoord[12] = fRed;
		fCoord[13] = fGreen;
		fCoord[14] = fBlue;
		fCoord[15] = fAlpha;

		fCoord[20] = fRed;
		fCoord[21] = fGreen;
		fCoord[22] = fBlue;
		fCoord[23] = fAlpha;

		fCoord[28] = fRed;
		fCoord[29] = fGreen;
		fCoord[30] = fBlue;
		fCoord[31] = fAlpha;


		vVertex.insert(vVertex.end(), &fCoord[0], &fCoord[32]);

		uShort[0] = it->uIndex[0] + nVertexIndex;
		uShort[1] = it->uIndex[1] + nVertexIndex;
		uShort[2] = it->uIndex[2] + nVertexIndex;
		uShort[3] = it->uIndex[3] + nVertexIndex;
		uShort[4] = it->uIndex[4] + nVertexIndex;
		uShort[5] = it->uIndex[5] + nVertexIndex;

		FinalRectInfo tRectInfo;
		tRectInfo.bDest = false;
		tRectInfo.nOffset = vIndices.size();
		tRectInfo.nSize = 6;
		tRectInfo.nRegisterIndex = m_nRectCount++;
		tRectInfo.uDesTexIdx = it->uDesTexIdx;
		tRectInfo.uSocTexIdx = it->uSocTexIdx;
		tRectInfo.uFrameBufferIdx = it->uFrameBufferIdx;
		vIndices.insert(vIndices.end(), &uShort[0], &uShort[6]);

		m_mFinalRectInfo[tRectInfo.nRegisterIndex] = tRectInfo;
		

		nVertexIndex = vVertexArrow.size() / 6;
		std::vector<GLfloat> vVertexTemp;
		std::vector<GLushort> vIndicesTemp;
		vVertexTemp.reserve(nSize * 8);


		tRectInfo.bDest = false;
		tRectInfo.nOffset = 0;
	
		static int nValue = 0;
		for (int i = 0; i < nSize; i += 2)
		{
			nValue++;
			vVertexTemp.push_back(pFloat[i] + it->fDesTexCoord[0]);
			vVertexTemp.push_back(1024-(pFloat[i + 1] + it->fDesTexCoord[1]));

			//TextureCoordinate!
			/*GLfloat fScaleFactorX = (GLfloat)(it->fCoord[0] + (it->fDesCoord[0] * 2)) / ((GLfloat)it->fCoord[0]);	//스케일 비율X
			GLfloat fScaleFactorY = (GLfloat)(it->fCoord[1] + (it->fDesCoord[1] * 2)) / ((GLfloat)it->fCoord[1]);	//스케일 비율Y

			GLfloat fPivotPointX = (GLfloat)(it->fDesTexCoord[0] + ((it->fDesTexCoord[2] - it->fDesTexCoord[0]) / 2.0f));		//피벗포인트
			GLfloat fPivotPointY = (GLfloat)(it->fDesTexCoord[1] + ((it->fDesTexCoord[5] - it->fDesTexCoord[1]) / 2.0f));		//피벗포인트


			GLfloat fTranslatedPointX = (it->fDesTexCoord[0] + pFloat[i]) - fPivotPointX;
			GLfloat fTranslatedPointY = (it->fDesTexCoord[1] + pFloat[i + 1]) - fPivotPointY;

			GLfloat fScaledPointX = fTranslatedPointX * fScaleFactorX;
			GLfloat fScaledPointY = fTranslatedPointY * fScaleFactorY;

			fTranslatedPointX = fScaledPointX + fPivotPointX;
			fTranslatedPointY = fScaledPointY + fPivotPointY;

			vVertexTemp.push_back(fTranslatedPointX / fWidthLimit);
			vVertexTemp.push_back(fTranslatedPointY / fHeightLimit);*/		
			
			vVertexTemp.push_back(1.0);
			vVertexTemp.push_back(0.0);
			vVertexTemp.push_back(0.0);
			
			vVertexTemp.push_back((GLfloat)fAlpha);
		}

		tRectInfo.nOffset = nVertexIndex;
		tRectInfo.nSize = vVertexTemp.size()/6;
		tRectInfo.nRegisterIndex;
		tRectInfo.uDesTexIdx = it->uDesTexIdx;
		tRectInfo.uFrameBufferIdx = it->uFrameBufferIdx;
		m_mArrowRectInfo[tRectInfo.nRegisterIndex] = tRectInfo;
		vVertexArrow.insert(vVertexArrow.end(), vVertexTemp.begin(), vVertexTemp.end());

		return tRectInfo.nRegisterIndex;
	}
	return 0;
}

bool CTextureInfo::PrepareShaderForScreen()
{
	GLbyte vShaderStr[] =
		"attribute vec4 a_position;\n"
		"attribute vec2 a_texcoord;\n"
		"attribute vec4 a_color;\n"
		"varying vec2 v_texcoord;\n"
		"uniform mat4 u_matrix;\n"
		"varying vec4 v_color;\n"
		"void main()\n"
		"{\n"
		"gl_Position = u_matrix * a_position;\n"
		"v_texcoord = a_texcoord;\n"
		"v_color = a_color;\n"
		"}\n";



	GLbyte fShaderStr[] =
		"precision mediump float;\n"
		"uniform float blendingRatio;\n"
		"varying vec2 v_texcoord;\n"
		"varying vec4 v_color;\n"
		"uniform sampler2D firstTex;                   \n"
		"uniform sampler2D secondTex;                  \n"
		"void main()\n"
		"{\n"
		"vec4 firstTexColor = texture2D( firstTex, v_texcoord );\n"
		"vec4 secondTexColor = texture2D( secondTex, v_texcoord );\n"
		"vec4 thirdTexColor =  texture2D(firstTex, v_texcoord)*v_color;\n"
		"vec4 fourthTexColor=  vec4(secondTexColor.rgb,firstTexColor.a);\n"
		"gl_FragColor = mix(fourthTexColor,thirdTexColor,blendingRatio);\n"
		"}\n";




	/*m_uScreenProgram = esLoadProgram((const char*)vShaderStr, (const char*)fShaderStr);
	if (m_uScreenProgram)
	{
		m_uPosScrLoc = glGetAttribLocation(m_uScreenProgram, "a_position");
		m_uTexCoordScrLoc = glGetAttribLocation(m_uScreenProgram, "a_texcoord");
		m_uColorScrLoc = glGetAttribLocation(m_uScreenProgram, "a_color");
		m_nMatrixScrLoc = glGetUniformLocation(m_uScreenProgram, "u_matrix");
		if (m_nMatrixScrLoc < 0)
		{
			glDeleteProgram(m_uScreenProgram);
			return false;
		}
		m_nFirstTex = glGetUniformLocation(m_uScreenProgram, "firstTex");
		if (m_nFirstTex < 0)
		{
			glDeleteProgram(m_uScreenProgram);
			return false;
		}
		m_nSecondTex = glGetUniformLocation(m_uScreenProgram, "secondTex");
		if (m_nSecondTex < 0)
		{
			glDeleteProgram(m_uScreenProgram);
			return false;
		}
		m_nSecondTexIndex = glGetUniformLocation(m_uScreenProgram, "blendingRatio");
		if (m_nSecondTexIndex < 0)
		{
			glDeleteProgram(m_uScreenProgram);
			return false;
		}
		return true;
	}*/
	return false;
}


bool CTextureInfo::PrepareShaderForFBO()
{
	GLbyte vShaderStr[] =
		"attribute vec4 a_position;				\n"
		"attribute vec4 a_color;				\n"
		"uniform mat4 u_matrix;					\n"
		"varying vec4 v_color;					\n"
		"void main()							\n"
		"{										\n"
		"gl_Position = u_matrix * a_position;	\n"
		"v_color = a_color;						\n"
		"}										\n";

	GLbyte fShaderStr[] =
		"precision mediump float;			\n"
		"varying vec4 v_color;				\n"
		"void main()						\n"
		"{									\n"
		"  gl_FragColor = v_color;			\n"
		"}									\n";

	/*m_uFBOProgram = esLoadProgram((const char*)vShaderStr, (const char*)fShaderStr);
	if (m_uFBOProgram)
	{
		m_uPosFBOLoc = glGetAttribLocation(m_uFBOProgram, "a_position");
		m_uColorFBOLoc = glGetAttribLocation(m_uFBOProgram, "a_color");
		m_nMatrixFBOLoc = glGetUniformLocation(m_uFBOProgram, "u_matrix");
		if (m_nMatrixFBOLoc < 0)
		{
			glDeleteProgram(m_uFBOProgram);
			return false;
		}
		return true;
	}*/
	return false;


}

bool CTextureInfo::PrepareVBO(std::vector<GLfloat> &vVertex, std::vector<GLushort> &vIndices)
{
	m_pFunctions->glGenBuffers(2, m_uVBOsID);	//Creating Vertex Buffer Object
	m_pFunctions->glBindBuffer(GL_ARRAY_BUFFER, m_uVBOsID[0]);
	m_pFunctions->glBufferData(GL_ARRAY_BUFFER, vVertex.size() * sizeof(GLfloat), &vVertex[0], GL_STATIC_DRAW);
	m_pFunctions->glBindBuffer(GL_ARRAY_BUFFER, 0);
	m_pFunctions->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uVBOsID[1]);
	m_pFunctions->glBufferData(GL_ELEMENT_ARRAY_BUFFER, vIndices.size() * sizeof(GLushort), &vIndices[0], GL_STATIC_DRAW);
	m_pFunctions->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	return true;
}

bool CTextureInfo::PrepareArrowVBO(std::vector<GLfloat> &vVertex)
{

	m_pFunctions->glGenBuffers(1, &m_uVBOsID[2]);	//Creating Vertex Buffer Object
	m_pFunctions->glBindBuffer(GL_ARRAY_BUFFER, m_uVBOsID[2]);
	m_pFunctions->glBufferData(GL_ARRAY_BUFFER, vVertex.size() * sizeof(GLfloat), &vVertex[0], GL_STATIC_DRAW);
	m_pFunctions->glBindBuffer(GL_ARRAY_BUFFER, 0);
	return true;
}


void CTextureInfo::SetVBOForScreen()
{
	m_pFunctions->glEnableVertexAttribArray(m_uPosScrLoc);
	m_pFunctions->glEnableVertexAttribArray(m_uTexCoordScrLoc);
	m_pFunctions->glEnableVertexAttribArray(m_uColorScrLoc);
	m_pFunctions->glBindBuffer(GL_ARRAY_BUFFER, m_uVBOsID[0]);
	m_pFunctions->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uVBOsID[1]);
	m_pFunctions->glVertexAttribPointer(m_uPosScrLoc, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	m_pFunctions->glVertexAttribPointer(m_uTexCoordScrLoc, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (const void*)(2 * sizeof(GLfloat)));
	m_pFunctions->glVertexAttribPointer(m_uColorScrLoc, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (const void*)(4 * sizeof(GLfloat)));
}

void CTextureInfo::SetVBOforFBO()
{
	m_pFunctions->glEnableVertexAttribArray(m_uPosFBOLoc);
	m_pFunctions->glEnableVertexAttribArray(m_uColorFBOLoc);
	m_pFunctions->glBindBuffer(GL_ARRAY_BUFFER, m_uVBOsID[2]);
	m_pFunctions->glVertexAttribPointer(m_uPosFBOLoc, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	m_pFunctions->glVertexAttribPointer(m_uColorFBOLoc, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (const void*)(2 * sizeof(GLfloat)));
}

void CTextureInfo::ResetVBOForScreen()
{
	m_pFunctions->glDisableVertexAttribArray(m_uPosScrLoc);
	m_pFunctions->glDisableVertexAttribArray(m_uTexCoordScrLoc);
	m_pFunctions->glDisableVertexAttribArray(m_uColorScrLoc);
}
void CTextureInfo::ResetVBOforFBO()
{
	m_pFunctions->glDisableVertexAttribArray(m_uPosFBOLoc);
	m_pFunctions->glDisableVertexAttribArray(m_uColorFBOLoc);
}

void CTextureInfo::DrawCurrentMap(int nWidth, int nHeight)
{
	m_pFunctions->glBindFramebuffer(GL_FRAMEBUFFER, 0);
	// Set the viewport
	m_pFunctions->glViewport(0, 0, nWidth, nHeight);
	// Clear the color buffer
	m_pFunctions->glClear(GL_COLOR_BUFFER_BIT);
	// Use the program object
	m_pFunctions->glClearColor(0.0, 0.0, 0.0, 0.0);
	m_pFunctions->glUseProgram(m_uScreenProgram);
	// Load the vertex position

	SetVBOForScreen();

	/*ESMatrix mat = { 0 };
	esMatrixLoadIdentity(&mat);
	static float fXOffset = 1.0f;
	fXOffset += 1.0f;
	esOrtho(&mat, fXOffset, nWidth+ fXOffset, nHeight, .0f, -1, 1);
	glUniformMatrix4fv(m_nMatrixScrLoc, 1, false, (const GLfloat*)&mat);

	for (const auto it : m_mFinalRectInfo)
	{
		//if (it.second.uDesTexIdx)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, it.second.uSocTexIdx);
			glUniform1i(m_nFirstTex, 0);
			if (it.second.uDesTexIdx)
			{
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, it.second.uDesTexIdx);
				glUniform1i(m_nSecondTex, 1);
			}
			glUniform1f(m_nSecondTexIndex, it.second.uDesTexIdx ?0.0 : 1.0);
			glDrawElements(GL_TRIANGLES, it.second.nSize, GL_UNSIGNED_SHORT, (const void*)(it.second.nOffset * sizeof(GLushort)));
		}
	}*/
	ResetVBOForScreen();
}


void CTextureInfo::DrawArrowFBO(int nWidth,int nHeight)
{
	/*GLuint uPreFrameBuffer = 0;
	for (const auto it : m_mArrowRectInfo)
	{
		if (uPreFrameBuffer != it.second.uFrameBufferIdx)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, it.second.uFrameBufferIdx);
			glViewport(0, 0, nWidth, nHeight);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glUseProgram(m_uFBOProgram);
			SetVBOforFBO();

			ESMatrix mat = { 0 };
			esMatrixLoadIdentity(&mat);
			esOrtho(&mat, .0f, nWidth, nHeight, .0f, -1, 1);
			glUniformMatrix4fv(m_nMatrixFBOLoc, 1, false, (const GLfloat*)&mat);
			uPreFrameBuffer = it.second.uFrameBufferIdx;
		}
		glDrawArrays(GL_TRIANGLE_STRIP, it.second.nOffset, it.second.nSize);
	}
	ResetVBOforFBO();*/
}


int CTextureInfo::PtInPolygon(int nvert, float *vertx, float *verty, float testx, float testy)
{
	int i, j, c = 0;
	for (i = 0, j = nvert - 1; i < nvert; j = i++) {
		if (((verty[i]>testy) != (verty[j]>testy)) &&
			(testx < (vertx[j] - vertx[i]) * (testy - verty[i]) / (verty[j] - verty[i]) + vertx[i]))
			c = !c;
	}
	return c;
}


bool CTextureInfo::PtInPolygon(GLfloat *pRectFloat,GLfloat fX,GLfloat fY)
{
	GLfloat fXPos[7] = { 0 };
	GLfloat fYPos[7] = { 0 };
	for (int i = 0; i < 5; i++)
	{
		fXPos[i ] = pRectFloat[i * 2];
		fYPos[i ] = pRectFloat[i * 2 + 1];
	}
	return PtInPolygon(5, fXPos, fYPos, fX, fY) ? true : false;
}

