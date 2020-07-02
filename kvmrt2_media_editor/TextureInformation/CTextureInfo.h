#pragma once
//#include "esUtil.h"
#include <map>
#include <vector>
#include <algorithm>
#include <QOpenGLFunctions>

typedef struct tagTextureInfo
{	
	int nParent;
	int nItemType;
	int nRegisterIndex;
	GLuint uSocTexIdx;
	GLfloat fCoord[2];
	GLfloat fTexCoord[8];
	GLushort uIndex[6];
	GLuint uDesTexIdx;
	GLuint uFrameBufferIdx;
	GLfloat fDesTexCoord[2];
}TextureInfo;


typedef struct tagFinalRectInfo
{
	bool bDest;
	int nRegisterIndex;
	int nSize;
	int nOffset;
	GLuint uSocTexIdx;

	int nDesSize;
	int nDesOffset;
	GLuint uDesTexIdx;
	GLuint uFrameBufferIdx;
}FinalRectInfo;


class QOpenGLFunctions;

class CTextureInfo
{
public:
	CTextureInfo();
	~CTextureInfo();

	static CTextureInfo* GetInstance();
	static int m_nRectCount;
	static int PtInPolygon(int nvert, float *vertx, float *verty, float testx, float testy);
	static bool PtInPolygon(GLfloat *pRectFloat, GLfloat fX, GLfloat fY);
	static bool SetOpenGLFunctions(QOpenGLFunctions *pFunctions);
	static QOpenGLFunctions *m_pFunctions;
	bool ReplaceSocTextureID(GLuint uOldId, GLuint uNewId);
	unsigned int AddTextureInformation(int nParent, int nItemType, int nRegisterIndex, GLuint uSocTexIdx, GLfloat fWidth, GLfloat fHeight, GLfloat fLeft, GLfloat fTop, GLfloat fRight, GLfloat fBottom, GLuint uDesTexIdx = 0, GLuint uDesFB = 0, GLfloat uTexCoordX = 0.0f, GLfloat uTexCoordY = 0.0f);
	int GetTextureIndex(int nParent, int nItemType);
	int GetTransformed(int nRegisteredIndex, std::vector<GLfloat> &vVertex, std::vector<GLushort> &vIndices, GLfloat fXPos, GLfloat fYPos, GLfloat fXOffset, GLfloat fYOffset, GLfloat fAngle, int nCenterPoint = 0 , GLfloat fRed=1.0f,GLfloat fGreen=1.0f,GLfloat fBlue=1.0f,GLfloat fAlpha=1.0f);
	int GetTransformed8(int nRegisteredIndex, std::vector<GLfloat> &vVertex, std::vector<GLushort> &vIndices, GLfloat *pWholeRect, GLfloat fXPos, GLfloat fYPos, GLfloat fXOffset, GLfloat fYOffset, GLfloat fAngle, int nCenterPoint=0, GLfloat fRed = 1.0f, GLfloat fGreen = 1.0f, GLfloat fBlue = 1.0f, GLfloat fAlpha = 1.0f);
	int GetTransformed9(int nRegisteredIndex, std::vector<GLfloat> &vVertexArrow, std::vector<GLfloat> &vVertex, std::vector<GLushort> &vIndices, GLfloat *pFloat, int nSize, GLfloat fXPos, GLfloat fYPos, GLfloat fXOffset, GLfloat fYOffset, GLfloat fRed, GLfloat fGreen, GLfloat fBlue, GLfloat fAlpha);
	bool GetTextureInfo(int nRegisteredIndex, std::vector<GLfloat> &vVertex, std::vector<GLushort> &vIndices, GLfloat fXPos, GLfloat fYPos, GLsizei *pCount, GLsizei *pOffset,GLint *pTexIdx);

	bool GetTextureInfo(std::vector<GLfloat> &vVertex, std::vector<GLushort> &vIndices,
		GLfloat fTexPosX, GLfloat fTexPosY, GLfloat fTexWidth, GLfloat fTexHeight, GLfloat fTexWholeWidth, GLfloat fTexWholeHeight, GLfloat fTextureOffset, GLsizei *pCount, GLsizei *pOffset, GLuint nVBO, GLuint nIBO, GLfloat fPosX=0.f, GLfloat fPosY=0.f);
	bool GetTextureInfo(std::vector<GLfloat> &vVertex, GLfloat fX, GLfloat fY, GLfloat *pFloat, int nSize, GLsizei *pCount, GLsizei *pOffset,GLuint nVBO);
	bool GetTextureInfo(std::vector<GLfloat> &vVertex, std::vector<GLushort> &vIndices,
		GLfloat fTexPosX, GLfloat fTexPosY, GLfloat fTexWidth, GLfloat fTexHeight, GLsizei iOffset, GLsizei iCount, GLsizei *pCount, GLsizei *pOffset, GLuint uVBOId, GLuint uIBOId, GLfloat fPosX = 0.f, GLfloat fPosY = 0.f);

	void DrawCurrentMap(int nWidth, int nHeight);
	void DrawArrowFBO(int nWidth, int nHeight);
	void ClearTextureInfo();
	bool PrepareShaderForScreen();
	bool PrepareShaderForFBO();
	bool PrepareVBO(std::vector<GLfloat> &vVertex, std::vector<GLushort> &vIndices);
	bool PrepareArrowVBO(std::vector<GLfloat> &vVertex);
	void SetVBOForScreen();
	void SetVBOforFBO();
	void ResetVBOForScreen();
	void ResetVBOforFBO();
private:
	GLuint m_uScreenProgram;
	GLuint m_uFBOProgram;
	GLuint m_uPosScrLoc;
	GLuint m_uTexCoordScrLoc;
	GLuint m_uColorScrLoc;

	GLint m_nMatrixScrLoc;
	GLint m_nFirstTex;
	GLint m_nSecondTex;
	GLint m_nSecondTexIndex;

	GLuint m_uPosFBOLoc;
	GLuint m_uColorFBOLoc;
	GLint m_nMatrixFBOLoc;


	GLuint m_uVBOsID[3];
	//std::map<GLuint,GLuint> m_mFrameBuf;
	std::vector<TextureInfo> m_vTextureInfo;

	std::map<int, FinalRectInfo> m_mFinalRectInfo;
	std::map<int, FinalRectInfo> m_mArrowRectInfo;
};

