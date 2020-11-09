#include "QGLESLineMapPreview.h"
#include <algorithm>
#include "TableManage.h"
#include "DataManage.h"
#include "dataModel.h"
#include "TextureInformation/CTextureInfo.h"
#include "BinPacked/MaxRectsPixelBuffer.h"
#include "displayItemPropEdit.h"
#include "editDisplayMetaItem.h"
#include "TexPool.h"
#include "ValueMonitor.h"
#include "CMappedValue.h"

#include <minmax.h>
#include <windows.h>
#include <Gdiplus.h>
#include <algorithm>

enum
{
	STATE_PASSED = 0,
	STATE_FOCUSED,
	STATE_REMAINED,
};

enum
{
	COLOR_LINE = 0,
	COLOR_PASSED=1,
	COLOR_FOCUSED1=2,
	COLOR_FOCUSED2=3,
	COLOR_REMAINED=4,
};


#define SET_COLOR_A(A) (GLfloat)((A>>24)&0xFF)/(255.0f)
#define SET_COLOR_R(A) (GLfloat)((A>>16)&0xFF)/(255.0f)
#define SET_COLOR_G(A) (GLfloat)((A>>8)&0xFF)/(255.0f)
#define SET_COLOR_B(A) (GLfloat)((A)&0xFF)/(255.0f)



QGLESLineMapPreview::QGLESLineMapPreview(QWidget *parent)
	:m_nHeight(0), m_nWidth(0), QOpenGLWidget(parent), 
	m_pCurLineMapPool(0), m_pCurLineMapLink(0), m_pLineMapLinkProps(0), m_pLineMapNode(0), m_pLineMapArrowTextures(0), m_pLineMapDisplayItem(0), m_pRoutes(0), m_nCurTime(0)
{
}


QGLESLineMapPreview::~QGLESLineMapPreview()
{
}


void QGLESLineMapPreview::mapStopPtnIdx(int *pStopPtnIdx)
{
	m_pMonStopPtnIdx = std::shared_ptr<CValueMonitor>(new CIntValueMonitor());
	m_pMonStopPtnIdx->setValue(pStopPtnIdx);
}

void QGLESLineMapPreview::mapDistIdx(int *pDistIdx)
{
	m_pMonDistIdx = std::shared_ptr<CValueMonitor>(new CIntValueMonitor());
	m_pMonDistIdx->setValue(pDistIdx);
}

void QGLESLineMapPreview::mapProgress(int *pProgress)
{
	m_pMonProgIdx = std::shared_ptr<CValueMonitor>(new CIntValueMonitor());
	m_pMonProgIdx->setValue(pProgress);
}

void QGLESLineMapPreview::mapLineMapIdx(int *pLineMapIdx)
{
	m_pMonLineMapIdx = std::shared_ptr<CValueMonitor>(new CIntValueMonitor());
	m_pMonLineMapIdx->setValue(pLineMapIdx);
}

void QGLESLineMapPreview::mapRoutesIdx(int *pRoutesIdx)
{
	m_pMonRoutesIdx = std::shared_ptr<CValueMonitor>(new CIntValueMonitor());
	m_pMonRoutesIdx->setValue(pRoutesIdx);
}


void QGLESLineMapPreview::initShaders()
{
	const char vShaderStr[] =
		"attribute vec4 a_position;\n"
		"attribute vec2 a_texcoord;\n"
		"varying vec2 v_texcoord;\n"
		"uniform mat4 u_matrix;\n"
		"void main()\n"
		"{\n"
		"gl_Position = u_matrix * a_position;\n"
		"v_texcoord = a_texcoord;\n"
		"}\n";

	const char fShaderStr[] =
		//"precision mediump float;\n"
		"varying vec2 v_texcoord;\n"
		"uniform vec4 u_color;\n"
		"uniform sampler2D firstTex;\n"
		"void main()\n"
		"{\n"
		"gl_FragColor =  texture2D(firstTex, v_texcoord)*u_color;\n"
		"}\n";

	if (!program.addShaderFromSourceCode(QOpenGLShader::Vertex, vShaderStr))
		close();

	// Compile fragment shader
	if (!program.addShaderFromSourceCode(QOpenGLShader::Fragment, fShaderStr))
		close();

	// Link shader pipeline
	if (!program.link())
		close();

	m_aPosScrLoc = program.attributeLocation("a_position");
	m_aTexCoordScrLoc = program.attributeLocation("a_texcoord");
	m_uMatrixScrLoc = program.uniformLocation("u_matrix");
	m_nFirstScrTex = program.uniformLocation("firstTex");
	m_uColorScrLoc = program.uniformLocation("u_color");
}


void QGLESLineMapPreview::initShadersForLine()
{
	const char vShaderStr[] =
		"attribute vec4 a_position;\n"
		"uniform vec4 u_color;\n"
		"uniform mat4 u_matrix;\n"
		"varying vec4 v_color;\n"
		"void main()\n"
		"{\n"
		"gl_Position = u_matrix * a_position;\n"
		"v_color = u_color;\n"
		"}\n";

	const char fShaderStr[] =
		//"precision mediump float;\n"
		"varying vec4 v_color;\n"
		"void main()\n"
		"{\n"
		"gl_FragColor = v_color;\n"
		"}\n";

	if (!lineProgram.addShaderFromSourceCode(QOpenGLShader::Vertex, vShaderStr))
		close();

	// Compile fragment shader
	if (!lineProgram.addShaderFromSourceCode(QOpenGLShader::Fragment, fShaderStr))
		close();

	// Link shader pipeline
	if (!lineProgram.link())
		close();

	m_uPosLineLoc = lineProgram.attributeLocation("a_position");
	m_uMatrixLineLoc = lineProgram.uniformLocation("u_matrix");
	m_uColorLineLoc = lineProgram.uniformLocation("u_color");
}

void QGLESLineMapPreview::initshadersForArrow()
{
	const char vShaderStr[] =
		"attribute vec4 a_position;\n"
		"attribute vec2 a_texcoord;\n"
		"varying vec2 v_texcoord;\n"
		"uniform mat4 u_matrix;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = u_matrix * a_position;\n"
		"	v_texcoord = a_texcoord;\n"
		"}\n";



	const char fShaderStr[] =
		//"precision mediump float;\n"
		"varying vec2 v_texcoord;\n"
		"uniform sampler2D firstTex;                   \n"
		"uniform sampler2D secondTex;                  \n"
		"void main()\n"
		"{\n"
		"	vec4 firstTexColor = texture2D( firstTex, v_texcoord );\n"
		"	vec4 secondTexColor = texture2D( secondTex, v_texcoord );\n"
		"	gl_FragColor =vec4(secondTexColor.rgb,firstTexColor.a);\n"
		"}\n";

	if (!arrowProgram.addShaderFromSourceCode(QOpenGLShader::Vertex, vShaderStr))
		close();

	if (!arrowProgram.addShaderFromSourceCode(QOpenGLShader::Fragment, fShaderStr))
		close();

	if (!arrowProgram.link())
		close();

	m_aArrowPos = arrowProgram.attributeLocation("a_position");
	m_aArrowTexCoord = arrowProgram.attributeLocation("a_texcoord");
	m_uArrowMatrix = arrowProgram.uniformLocation("u_matrix");
	m_uArrowFirstTex = arrowProgram.uniformLocation("firstTex");
	m_uArrowSecondTex = arrowProgram.uniformLocation("secondTex");

}




void QGLESLineMapPreview::initVBO()
{
	glGenBuffers(3, m_uVBOsID);	//Creating Vertex Buffer Object
	glBindBuffer(GL_ARRAY_BUFFER, m_uVBOsID[0]);
	glBufferData(GL_ARRAY_BUFFER, 200000* sizeof(GLfloat), 0, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uVBOsID[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 200000 * sizeof(GLushort), 0, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_uVBOsID[2]);
	glBufferData(GL_ARRAY_BUFFER, 200000 * sizeof(GLfloat), 0, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}


void QGLESLineMapPreview::initializeGL()
{
	initializeOpenGLFunctions();
	initShaders();
	initShadersForLine();
	initshadersForArrow();
	initBaseData();
	initStationRelated();
	initDisplayItem();
	initMetaDisplayItem();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	//initDisplayItem();
	//initMetaDisplayItem();
	//reorderAllTimeLine();
}

void QGLESLineMapPreview::resizeGL(int w, int h)
{
	m_nHeight = h;
	m_nWidth = w;
}

#define MAKECOORDKEY(A,B)	MAKELONG(B,A)

void QGLESLineMapPreview::paintGL()
{
	auto *pTM = CTableManage::GetInstance();
	if (m_pMonLineMapIdx->isChanged())
	{
		unsigned int uIdx;
		m_pMonLineMapIdx->getValue(&uIdx);
		auto it=m_mLineMapLink.find(uIdx);
		if (it != m_mLineMapLink.end())
		{
			m_pCurLineMapLink = &it->second;
		}
		auto itn = find_if(pTM->m_vLineMapPool.begin(), pTM->m_vLineMapPool.end(), findSQLData(uIdx));
		if (itn != pTM->m_vLineMapPool.end())
		{
			m_pCurLineMapPool = (LineMapPool*)itn->get();

			m_fColorState[COLOR_LINE][0] = SET_COLOR_A(m_pCurLineMapPool->uLineColor);
			m_fColorState[COLOR_LINE][1] = SET_COLOR_R(m_pCurLineMapPool->uLineColor);
			m_fColorState[COLOR_LINE][2] = SET_COLOR_G(m_pCurLineMapPool->uLineColor);
			m_fColorState[COLOR_LINE][3] = SET_COLOR_B(m_pCurLineMapPool->uLineColor);

			m_fColorState[COLOR_PASSED][0] = SET_COLOR_A(m_pCurLineMapPool->uPassedColor);
			m_fColorState[COLOR_PASSED][1] = SET_COLOR_R(m_pCurLineMapPool->uPassedColor);
			m_fColorState[COLOR_PASSED][2] = SET_COLOR_G(m_pCurLineMapPool->uPassedColor);
			m_fColorState[COLOR_PASSED][3] = SET_COLOR_B(m_pCurLineMapPool->uPassedColor);

			m_fColorState[COLOR_FOCUSED1][0] = SET_COLOR_A(m_pCurLineMapPool->uFocusedColor);
			m_fColorState[COLOR_FOCUSED1][1] = SET_COLOR_R(m_pCurLineMapPool->uFocusedColor);
			m_fColorState[COLOR_FOCUSED1][2] = SET_COLOR_G(m_pCurLineMapPool->uFocusedColor);
			m_fColorState[COLOR_FOCUSED1][3] = SET_COLOR_B(m_pCurLineMapPool->uFocusedColor);

			m_fColorState[COLOR_FOCUSED2][0] = SET_COLOR_A(m_pCurLineMapPool->uFocusedColor);
			m_fColorState[COLOR_FOCUSED2][1] = SET_COLOR_R(m_pCurLineMapPool->uFocusedColor);
			m_fColorState[COLOR_FOCUSED2][2] = SET_COLOR_G(m_pCurLineMapPool->uFocusedColor);
			m_fColorState[COLOR_FOCUSED2][3] = SET_COLOR_B(m_pCurLineMapPool->uFocusedColor);

			m_fColorState[COLOR_REMAINED][0] = SET_COLOR_A(m_pCurLineMapPool->uLeftColor);
			m_fColorState[COLOR_REMAINED][1] = SET_COLOR_R(m_pCurLineMapPool->uLeftColor);
			m_fColorState[COLOR_REMAINED][2] = SET_COLOR_G(m_pCurLineMapPool->uLeftColor);
			m_fColorState[COLOR_REMAINED][3] = SET_COLOR_B(m_pCurLineMapPool->uLeftColor);


			m_pLineMapLinkProps = &(m_pCurLineMapPool->m_vChildItem[0].vSQLData);
			m_pLineMapNode = &(m_pCurLineMapPool->m_vChildItem[2].vSQLData);
			m_pLineMapArrowTextures = &(m_pCurLineMapPool->m_vChildItem[3].vSQLData);
			m_pLineMapDisplayItem=&(m_pCurLineMapPool->m_vChildItem[4].vSQLData);
		}
		m_pMonLineMapIdx->saveLatest();
	}

	if (m_pMonStopPtnIdx->isChanged())
	{
		unsigned int uIdx;
		m_pMonStopPtnIdx->getValue(&uIdx);
		auto itn = find_if(pTM->m_vStopPtnHeader.begin(), pTM->m_vStopPtnHeader.end(), findSQLData(uIdx));
		if (itn != pTM->m_vStopPtnHeader.end())
		{
			m_pRoutes = &(itn->get()->m_vChildItem[0].vSQLData);
			fillArrowsAndNodes(0,0);
		}

		// prepareArrow - arrow color?, jkc
		m_pMonStopPtnIdx->saveLatest();
		prepareArrow(&m_vArrowsInUse[STATE_PASSED], 1024, 1024, 0.4f, 0.4f, 0.4f);
		prepareArrow(&m_vArrowsInUse[STATE_REMAINED], 1024, 1024, 0.0f, 1.0f, 0.0f);
		prepareArrow(&m_vArrowsInUse[STATE_FOCUSED], 1024, 1024, 0.0f, 0.0f, 0.0f);
	}

	if (m_pMonRoutesIdx->isChanged())
	{
		unsigned int uIdx;
		bool bPassedIdx = false;
		m_pMonRoutesIdx->getValue(&uIdx);
		fillArrowsAndNodes(uIdx, 0);
		
		// prepareArrow - arrow color?, jkc
		prepareArrow(&m_vArrowsInUse[STATE_PASSED], 1024, 1024, 0.4f, 0.4f, 0.4f);
		prepareArrow(&m_vArrowsInUse[STATE_REMAINED], 1024, 1024, 0.0f, 1.0f, 0.0f);
		prepareArrow(&m_vArrowsInUse[STATE_FOCUSED], 1024, 1024, 0.0f, 0.0f, 0.0f);
		m_pMonRoutesIdx->saveLatest();
	}

	if (m_pMonProgIdx->isChanged())
	{
		unsigned int uIdx;
		bool bPassedIdx = false;
		m_pMonProgIdx->getValue(&uIdx);
		setArrowProgress(&m_vArrowsInUse[STATE_FOCUSED], 1024, 1024, uIdx, 0.0f, 0.0f, 1.0f, 0.4f, 0.4f, 0.4f);
		m_pMonProgIdx->saveLatest();
	}


	

	if (m_pLineMapLinkProps&&m_pLineMapNode&&m_pLineMapArrowTextures&&m_pLineMapDisplayItem)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		// 배경?, jkc
		glClearColor(255.0f,255.0f,255.0f, 0.0f);

		if (!program.bind())
			close();

		glEnableVertexAttribArray(m_aPosScrLoc);
		glEnableVertexAttribArray(m_aTexCoordScrLoc);
		glBindBuffer(GL_ARRAY_BUFFER, m_uVBOsID[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uVBOsID[1]);
		glVertexAttribPointer(m_aPosScrLoc, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
		glVertexAttribPointer(m_aTexCoordScrLoc, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (const void*)(2 * sizeof(GLfloat)));
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(m_nFirstScrTex, 0);
		glViewport(0, 0, m_pCurLineMapPool->nWholeWidth, m_pCurLineMapPool->nWholeHeight);

		// Drawing Tile Map
		for (auto it : (*m_pLineMapLinkProps))
		{
			LineMapLink *pLink = (LineMapLink*)it.get();
			if (pLink->nItemType)
			{
				auto findIt = m_pCurLineMapLink->find(pLink->nItemType);
				if (findIt != m_pCurLineMapLink->end())
				{
					QMatrix4x4 matrix;
					matrix.ortho(0, m_pCurLineMapPool->nWholeWidth, m_pCurLineMapPool->nWholeHeight, 0, -1, 1);
					matrix.translate(pLink->nPosX - (m_pCurLineMapPool->nProp / 2), pLink->nPosY - (m_pCurLineMapPool->nProp / 2));

					glUniform4f(m_uColorScrLoc, m_fColorState[COLOR_LINE][3],
						m_fColorState[COLOR_LINE][2],
						m_fColorState[COLOR_LINE][1],
						m_fColorState[COLOR_LINE][0]);
					glUniformMatrix4fv(m_uMatrixScrLoc, 1, false, (const GLfloat*)&matrix);
					for (auto subit : findIt->second->vIdxList)
					{
						findIt->second->SetOrigin(5);
						glBindTexture(GL_TEXTURE_2D, subit.nTextureIndex);
						glDrawElements(GL_TRIANGLES, subit.iCount, GL_UNSIGNED_SHORT, (const void*)(subit.iOffset * sizeof(GLushort)));
					}
				}
			}
		}
		
		paintStationRelated(m_vNodesInUse[STATE_PASSED],STATE_PASSED,m_pCurLineMapPool->nWholeWidth, m_pCurLineMapPool->nWholeHeight);
		paintStationRelated(m_vNodesInUse[STATE_FOCUSED], STATE_FOCUSED, m_pCurLineMapPool->nWholeWidth, m_pCurLineMapPool->nWholeHeight);
		paintStationRelated(m_vNodesInUse[STATE_REMAINED], STATE_REMAINED, m_pCurLineMapPool->nWholeWidth, m_pCurLineMapPool->nWholeHeight);


		paintDisplayItems(m_pLineMapDisplayItem, m_pCurLineMapPool->nWholeWidth, m_pCurLineMapPool->nWholeHeight);


		glDisableVertexAttribArray(m_aPosScrLoc);
		glDisableVertexAttribArray(m_aTexCoordScrLoc);

		if (!arrowProgram.bind())
			close();

		glEnableVertexAttribArray(m_aArrowPos);
		glEnableVertexAttribArray(m_aArrowTexCoord);
		glBindBuffer(GL_ARRAY_BUFFER, m_uVBOsID[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uVBOsID[1]);
		glVertexAttribPointer(m_aArrowPos, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
		glVertexAttribPointer(m_aArrowTexCoord, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (const void*)(2 * sizeof(GLfloat)));
		glUniform1i(m_uArrowFirstTex, 0);
		glUniform1i(m_uArrowSecondTex, 1);
		for (int nStateCnt = STATE_PASSED; nStateCnt < (STATE_REMAINED + 1); nStateCnt++)
		{
			for (auto it : m_vArrowsInUse[nStateCnt])
			{
				LineMapArrowTexture *pLMAT = (LineMapArrowTexture*)it.get();
				auto findIt = m_mArrow.find(pLMAT->GetIndex());
				if (findIt != m_mArrow.end())
				{
					QMatrix4x4 matrix;
					matrix.ortho(0, m_pCurLineMapPool->nWholeWidth, m_pCurLineMapPool->nWholeHeight, 0, -1, 1);
					matrix.translate(findIt->second->m_fOrigin[0] + (GLfloat)pLMAT->nOffsetX, findIt->second->m_fOrigin[1] + (GLfloat)pLMAT->nOffsetY);
					glUniform4f(m_uArrowColor, 1.0, 0.0, 0.0, 1.0);
					glUniformMatrix4fv(m_uArrowMatrix, 1, false, (const GLfloat*)&matrix);
					for (auto subit : findIt->second->vIdxList)
					{
						glActiveTexture(GL_TEXTURE0);
						glBindTexture(GL_TEXTURE_2D, subit.nTextureIndex);
						if (subit.nSecTextureIndex)
						{
							glActiveTexture(GL_TEXTURE1);
							glBindTexture(GL_TEXTURE_2D, subit.nSecTextureIndex);
						}
						glDrawElements(GL_TRIANGLES, subit.iCount, GL_UNSIGNED_SHORT, (const void*)(subit.iOffset * sizeof(GLushort)));
					}
				}
			}
		}
	}
}

void QGLESLineMapPreview::initStationRelated()
{
	auto *pTM = CTableManage::GetInstance();
	for (auto it : pTM->m_vLineMapPool)
	{
		LineMapPool *pLMP=(LineMapPool*)it.get();
		for (auto subit : pLMP->m_vChildItem[2].vSQLData)
		{
			LineMapNode *pNode = (LineMapNode*)subit.get();
			if (!pNode->nRelatedIndex[1])
			{
				pNode->nRelatedIndex[1] = pNode->nRelatedIndex[0];
				pNode->nOffsetX[1] = pNode->nOffsetX[0];
				pNode->nOffsetY[1] = pNode->nOffsetY[0];
				pNode->nCenterSpot[1] = pNode->nCenterSpot[0];
				pNode->nRotAngle[1] = pNode->nRotAngle[0];
				pNode->nType[1]= pNode->nType[0];
				pNode->nColored[1] = pNode->nColored[0];
			}

			if (!pNode->nRelatedIndex[2])
			{
				pNode->nRelatedIndex[2] = pNode->nRelatedIndex[0];
				pNode->nOffsetX[2] = pNode->nOffsetX[0];
				pNode->nOffsetY[2] = pNode->nOffsetY[0];
				pNode->nCenterSpot[2] = pNode->nCenterSpot[0];
				pNode->nRotAngle[2] = pNode->nRotAngle[0];
				pNode->nType[2] = pNode->nType[0];
				pNode->nColored[2] = pNode->nColored[0];
			}

			if (!pNode->nSRelatedIndex[1])
			{
				pNode->nSRelatedIndex[1] = pNode->nSRelatedIndex[0];
				pNode->nSOffsetX[1] = pNode->nSOffsetX[0];
				pNode->nSOffsetY[1] = pNode->nSOffsetY[0];
				pNode->nSCenterSpot[1] = pNode->nSCenterSpot[0];
				pNode->nSUseDefault[1] = pNode->nSUseDefault[0];
			}

			if (!pNode->nSRelatedIndex[2])
			{
				pNode->nSRelatedIndex[2] = pNode->nSRelatedIndex[0];
				pNode->nSOffsetX[2] = pNode->nSOffsetX[0];
				pNode->nSOffsetY[2] = pNode->nSOffsetY[0];
				pNode->nSCenterSpot[2] = pNode->nSCenterSpot[0];
				pNode->nSUseDefault[2] = pNode->nSUseDefault[0];
			}
		}
	}	
}


void QGLESLineMapPreview::paintStationRelated(std::vector<std::shared_ptr<CSQLData>> &tVECStn,int nState,int nWidth,int nHeight)
{
	auto *pTM = CTableManage::GetInstance();
	CTexPool  *pTexPool = nullptr;
	auto it = m_pCurLineMapLink->find(0);
	if (it != m_pCurLineMapLink->end())
	{
		pTexPool = (CTexPool*)it->second.get();
	}
	for (auto it : tVECStn)
	{
		LineMapNode *pNode = (LineMapNode*)it.get();
		switch(pNode->nType[nState])
		{
		case DISP_DISPLAY_ITEM:
			{
				auto findIt = find_if(pTM->m_vDisplayItemPool.begin(), pTM->m_vDisplayItemPool.end(), findSQLData(pNode->nRelatedIndex[nState]));
				if (findIt != pTM->m_vDisplayItemPool.end())
				{
					DisplayItemPool *pDIP = (DisplayItemPool*)findIt->get();
					pNode->m_fRect[nState][0] = (GLfloat)0.0f;
					pNode->m_fRect[nState][1] = (GLfloat)0.0f;
					pNode->m_fRect[nState][2] = (GLfloat)pDIP->nWidth;
					pNode->m_fRect[nState][3] = (GLfloat)pDIP->nHeight;
					pNode->SetOrigin(nState, pNode->nCenterSpot[nState]);
					for (auto vit : findIt->get()->m_vChildItem[0].vSQLData)
					{
						DisplayItem *pItem = (DisplayItem*)vit.get();
						pItem->tLine.jumpTo(m_nCurTime);
						auto findIt = m_mImageList.find(pItem->nRelatedBufferIndex);
						if (findIt != m_mImageList.end())
						{
							QMatrix4x4 matrix;
							findIt->second->SetOrigin(pItem->nOrigin, true);
							matrix.ortho(0, nWidth, nHeight, 0, -1, 1);
							matrix.translate(pNode->nPosX + pNode->nOffsetX[nState], pNode->nPosY + pNode->nOffsetY[nState]);
							matrix.rotate(pNode->nRotAngle[nState], 0, 0, 1.0f);
							matrix.translate(pNode->m_fOrigin[nState][0], pNode->m_fOrigin[nState][1]);
							matrix.translate(pItem->m_fTrans[0], pItem->m_fTrans[1]);
							matrix.rotate(pItem->m_fRotation, 0, 0, 1.0f);
							matrix.scale(pItem->m_fScale[0], pItem->m_fScale[1]);
							matrix.translate(pItem->fOrigX, pItem->fOrigY);

							glUniform4f(m_uColorScrLoc, pItem->m_fColor[3], pItem->m_fColor[2], pItem->m_fColor[1], pItem->m_fColor[0]);
							glUniformMatrix4fv(m_uMatrixScrLoc, 1, false, (const GLfloat*)&matrix);
							for (auto subit : findIt->second->vIdxList)
							{
								glBindTexture(GL_TEXTURE_2D, subit.nTextureIndex);
								glDrawElements(GL_TRIANGLES, subit.iCount, GL_UNSIGNED_SHORT, (const void*)(subit.iOffset * sizeof(GLushort)));
							}
						}
					}
				}
			}
			break;
		case DISP_IMAGE_LIST:
			{
				auto findIt = m_mImageList.find(pNode->nRelatedIndex[nState]);
				if (findIt != m_mImageList.end())
				{
					QMatrix4x4 mat;
					mat.ortho(0, nWidth, nHeight, 0, -1, 1);
					findIt->second->SetOrigin(pNode->nCenterSpot[nState]);
					mat.translate(pNode->nPosX + (GLfloat)pNode->nOffsetX[nState], pNode->nPosY + (GLfloat)pNode->nOffsetY[nState]);
					mat.rotate(pNode->nRotAngle[nState], 0, 0, 1.0f);
					mat.translate(findIt->second->m_fOrigin[0], findIt->second->m_fOrigin[1]);
					glUniformMatrix4fv(m_uMatrixScrLoc, 1, false, (const GLfloat*)&mat);
					if (pNode->nColored[nState])
					{
						switch (nState)
						{
						case STATE_PASSED:
							glUniform4f(m_uColorScrLoc, m_fColorState[COLOR_PASSED][3],
								m_fColorState[COLOR_PASSED][2],
								m_fColorState[COLOR_PASSED][1],
								m_fColorState[COLOR_PASSED][0]);
							break;
						case STATE_FOCUSED:
							glUniform4f(m_uColorScrLoc, m_fColorState[COLOR_FOCUSED1][3],
								m_fColorState[COLOR_FOCUSED1][2],
								m_fColorState[COLOR_FOCUSED1][1],
								m_fColorState[COLOR_FOCUSED1][0]);
							break;
						case STATE_REMAINED:
							glUniform4f(m_uColorScrLoc, m_fColorState[COLOR_REMAINED][3],
								m_fColorState[COLOR_REMAINED][2],
								m_fColorState[COLOR_REMAINED][1],
								m_fColorState[COLOR_REMAINED][0]);
							break;
						}
					}	
					else
						glUniform4f(m_uColorScrLoc, 1.0f, 1.0f, 1.0f, 1.0f);
					
					for (auto subit : findIt->second->vIdxList)
					{
						glBindTexture(GL_TEXTURE_2D, subit.nTextureIndex);
						glDrawElements(GL_TRIANGLES, subit.iCount, GL_UNSIGNED_SHORT, (const void*)(subit.iOffset * sizeof(GLushort)));
					}
				}
			}
			break;
		default:
			break;
		}


		 if (!pNode->nSUseDefault[nState])
		{
			switch (pNode->nSType[nState])
			{
			case DISP_DISPLAY_ITEM:
			{
				auto findIt = find_if(pTM->m_vDisplayItemPool.begin(), pTM->m_vDisplayItemPool.end(), findSQLData(pNode->nSRelatedIndex[nState]));
				if (findIt != pTM->m_vDisplayItemPool.end())
				{
					DisplayItemPool *pDIP = (DisplayItemPool*)findIt->get();
					pNode->m_fRect[nState][0] = (GLfloat)0.0f;
					pNode->m_fRect[nState][1] = (GLfloat)0.0f;
					pNode->m_fRect[nState][2] = (GLfloat)pDIP->nWidth;
					pNode->m_fRect[nState][3] = (GLfloat)pDIP->nHeight;
					pNode->SetOrigin(nState, pNode->nSCenterSpot[nState]);
					for (auto vit : findIt->get()->m_vChildItem[0].vSQLData)
					{
						DisplayItem *pItem = (DisplayItem*)vit.get();
						pItem->tLine.jumpTo(m_nCurTime);
						auto findIt = m_mImageList.find(pItem->nRelatedBufferIndex);
						if (findIt != m_mImageList.end())
						{
							QMatrix4x4 matrix;
							findIt->second->SetOrigin(pItem->nOrigin, true);
							matrix.ortho(0, nWidth, nHeight, 0, -1, 1);
							matrix.translate(pNode->nPosX + pNode->nSOffsetX[nState], pNode->nPosY + pNode->nSOffsetY[nState]);
							matrix.translate(pNode->m_fOrigin[nState][0], pNode->m_fOrigin[nState][1]);


							matrix.translate(pItem->m_fTrans[0], pItem->m_fTrans[1]);
							matrix.rotate(pItem->m_fRotation, 0, 0, 1.0f);
							matrix.scale(pItem->m_fScale[0], pItem->m_fScale[1]);
							matrix.translate(pItem->fOrigX, pItem->fOrigY);

							//QMatrix4x4 matrix2;
							//matrix2.ortho(0, m_nWidth, m_nHeight, 0, -1, 1);

							//	QMatrix4x4 matrix3 = matrix * matrix2;
							/*matrix.translate(pNode->nPosX, pNode->nPosY);
							matrix.rotate(pNode->nRotAngle[nState], 0, 0, 1.0f);
							matrix.translate((GLfloat)pNode->m_fOrigin[nState][0], (GLfloat)pNode->m_fOrigin[nState][1]);*/

							glUniform4f(m_uColorScrLoc, pItem->m_fColor[3], pItem->m_fColor[2], pItem->m_fColor[1], pItem->m_fColor[0]);
							glUniformMatrix4fv(m_uMatrixScrLoc, 1, false, (const GLfloat*)&matrix);
							for (auto subit : findIt->second->vIdxList)
							{
								glBindTexture(GL_TEXTURE_2D, subit.nTextureIndex);
								glDrawElements(GL_TRIANGLES, subit.iCount, GL_UNSIGNED_SHORT, (const void*)(subit.iOffset * sizeof(GLushort)));
							}
						}
					}
				}
			}
			break;
			case DISP_IMAGE_LIST:
			{
				auto findIt = m_mImageList.find(pNode->nSRelatedIndex[nState]);
				if (findIt != m_mImageList.end())
				{
					findIt->second->SetOrigin(pNode->nSCenterSpot[nState]);
					QMatrix4x4 matrix;
					matrix.ortho(0, nWidth, nHeight, 0, -1, 1);
					//matrix.ortho(0, m_nWidth, m_nHeight, 0, -1, 1);
					matrix.translate(pNode->nPosX + (GLfloat)pNode->nSOffsetX[nState], pNode->nPosY + (GLfloat)pNode->nSOffsetY[nState]);
					matrix.translate(findIt->second->m_fOrigin[0], findIt->second->m_fOrigin[1]);
					glUniformMatrix4fv(m_uMatrixScrLoc, 1, false, (const GLfloat*)&matrix);
					if (pNode->nColored[nState])
					{
						switch (nState)
						{
						case STATE_PASSED:
							glUniform4f(m_uColorScrLoc, m_fColorState[COLOR_PASSED][3],
								m_fColorState[COLOR_PASSED][2],
								m_fColorState[COLOR_PASSED][1],
								m_fColorState[COLOR_PASSED][0]);
							break;
						case STATE_FOCUSED:
							glUniform4f(m_uColorScrLoc, m_fColorState[COLOR_FOCUSED1][3],
								m_fColorState[COLOR_FOCUSED1][2],
								m_fColorState[COLOR_FOCUSED1][1],
								m_fColorState[COLOR_FOCUSED1][0]);
							break;
						case STATE_REMAINED:
							glUniform4f(m_uColorScrLoc, m_fColorState[COLOR_REMAINED][3],
								m_fColorState[COLOR_REMAINED][2],
								m_fColorState[COLOR_REMAINED][1],
								m_fColorState[COLOR_REMAINED][0]);
							break;
						}
					}
					else
						glUniform4f(m_uColorScrLoc, 1.0f, 1.0f, 1.0f, 1.0f);
					for (auto subit : findIt->second->vIdxList)
					{
						glBindTexture(GL_TEXTURE_2D, subit.nTextureIndex);
						glDrawElements(GL_TRIANGLES, subit.iCount, GL_UNSIGNED_SHORT, (const void*)(subit.iOffset * sizeof(GLushort)));
					}
				}
			}
			break;
			}
		}
		else
		{
			QMatrix4x4 matrix;
			if (pTexPool)
			{
				pTexPool->SetOrigin(5);
				matrix.ortho(0, m_pCurLineMapPool->nWholeWidth, m_pCurLineMapPool->nWholeHeight, 0, -1, 1);
				matrix.translate(pTexPool->m_fOrigin[0] + (GLfloat)pNode->nPosX, pTexPool->m_fOrigin[1] + (GLfloat)pNode->nPosY);
				glUniform4f(m_uColorScrLoc, (GLfloat)1.0f, (GLfloat)0.0f, (GLfloat)0.0f, (GLfloat)1.0f);
				glUniformMatrix4fv(m_uMatrixScrLoc, 1, false, (const GLfloat*)&matrix);
				for (auto spotit : pTexPool->vIdxList)
				{
					glBindTexture(GL_TEXTURE_2D, spotit.nTextureIndex);
					glDrawElements(GL_TRIANGLES, spotit.iCount, GL_UNSIGNED_SHORT, (const void*)(spotit.iOffset * sizeof(GLushort)));
				}
			}
		}
	}
}




void QGLESLineMapPreview::paintDisplayItems(std::vector<std::shared_ptr<CSQLData>> *pvLMDP,int nWidth,int nHeight)
{
	auto *pTM = CTableManage::GetInstance();
	for (auto it : (*pvLMDP))
	{
		LineMapDisplayItem *pLMDI = (LineMapDisplayItem*)it.get();
		auto findIt = find_if(pTM->m_vDisplayItemPool.begin(), pTM->m_vDisplayItemPool.end(), findSQLData(pLMDI->nRelatedDisplayItem));
		if (findIt != pTM->m_vDisplayItemPool.end())
		{
			DisplayItemPool *pDIP = (DisplayItemPool*)findIt->get();
			pLMDI->m_fRect[0] = (GLfloat)0.0f;
			pLMDI->m_fRect[1] = (GLfloat)0.0f;
			pLMDI->m_fRect[2] = (GLfloat)pDIP->nWidth;
			pLMDI->m_fRect[3] = (GLfloat)pDIP->nHeight;
			pLMDI->SetOrigin(pLMDI->nCenterSpot,true);
			for (auto vit : findIt->get()->m_vChildItem[0].vSQLData)
			{
				DisplayItem *pItem = (DisplayItem*)vit.get();
				pItem->tLine.jumpTo(m_nCurTime);
				auto findIt = m_mImageList.find(pItem->nRelatedBufferIndex);
				if (findIt != m_mImageList.end())
				{
					QMatrix4x4 matrix;
					findIt->second->SetOrigin(pItem->nOrigin, true);
					matrix.ortho(0, nWidth, nHeight, 0, -1, 1);
					matrix.translate(pLMDI->nPosX, pLMDI->nPosY);
					matrix.translate(pLMDI->m_fOrigin[0], pLMDI->m_fOrigin[1]);

					matrix.translate(pItem->m_fTrans[0], pItem->m_fTrans[1]);
					matrix.rotate(pItem->m_fRotation, 0, 0, 1.0f);
					matrix.scale(pItem->m_fScale[0], pItem->m_fScale[1]);
					matrix.translate(pItem->fOrigX, pItem->fOrigY);

					glUniform4f(m_uColorScrLoc, pItem->m_fColor[3], pItem->m_fColor[2], pItem->m_fColor[1], pItem->m_fColor[0]);
					glUniformMatrix4fv(m_uMatrixScrLoc, 1, false, (const GLfloat*)&matrix);
					for (auto subit : findIt->second->vIdxList)
					{
						glBindTexture(GL_TEXTURE_2D, subit.nTextureIndex);
						glDrawElements(GL_TRIANGLES, subit.iCount, GL_UNSIGNED_SHORT, (const void*)(subit.iOffset * sizeof(GLushort)));
					}
				}
			}


			for (auto vit : findIt->get()->m_vChildItem[1].vSQLData)
			{
				DisplayMetaItem *pItem = (DisplayMetaItem*)vit.get();
				pItem->SetOrigin(pItem->nOrigin);
				if (pItem->m_pValueMonitor->isChanged())
				{
					int nValue;
					wchar_t szBuffer[64];
					pItem->m_pValueMonitor->getValue(&nValue);
					swprintf_s(szBuffer, 64, L"[%s:%d]", pItem->szTagItem, nValue);
					auto tagIt = find_if(pTM->m_vImageIndexList.begin(), pTM->m_vImageIndexList.end(), [&szBuffer](std::shared_ptr<CSQLData> &pValue)
					{
						ImageIndexList *pIIL=(ImageIndexList*)pValue.get();
						return !STRCMP(pIIL->szDesc, szBuffer);
					});
					if (tagIt != pTM->m_vImageIndexList.end())
					{
						pItem->nRelatedIndex=(*tagIt)->GetIndex();
						pItem->m_fRect[0] = 0;
						pItem->m_fRect[1] = 0;
						pItem->m_fRect[2] = (GLfloat)pItem->nWidth;
						pItem->m_fRect[3] = (GLfloat)pItem->nHeight;
						setMetaItemOrientation(pItem);
					}
					pItem->m_pValueMonitor->saveLatest();
				}
				pItem->tLine.jumpTo(m_nCurTime);
				auto findIt = m_mImageList.find(pItem->nRelatedIndex);
				if (findIt != m_mImageList.end())
				{
					QMatrix4x4 matrix;
					matrix.ortho(0,nWidth, nHeight, 0, -1, 1);

					matrix.translate(pLMDI->nPosX, pLMDI->nPosY);
					matrix.translate(pLMDI->m_fOrigin[0], pLMDI->m_fOrigin[1]);
					
					matrix.translate(pItem->m_fTrans[0], pItem->m_fTrans[1]);
					
					matrix.rotate(pItem->m_fRotation, 0, 0, 1.0f);
					matrix.scale(pItem->m_fScale[0], pItem->m_fScale[1]);
					matrix.translate(pItem->fOrigX, pItem->fOrigY);

					matrix.translate(pItem->fOffsetX, pItem->fOffsetY);
					matrix.scale(pItem->fRatioX, pItem->fRatioY);

					glUniform4f(m_uColorScrLoc, pItem->m_fColor[3], pItem->m_fColor[2], pItem->m_fColor[1], pItem->m_fColor[0]);
					glUniformMatrix4fv(m_uMatrixScrLoc, 1, false, (const GLfloat*)&matrix);
					for (auto subit : findIt->second->vIdxList)
					{
						glBindTexture(GL_TEXTURE_2D, subit.nTextureIndex);
						glDrawElements(GL_TRIANGLES, subit.iCount, GL_UNSIGNED_SHORT, (const void*)(subit.iOffset * sizeof(GLushort)));
					}
				}
			}
		}
	}
}





void QGLESLineMapPreview::fillArrowsAndNodes(int nCurRouteIdx,int nFocusedStnIdx)
{
	bool bArrowPassed = false,bNodePassed=false;
	bool bFirst = true;

	m_vArrowsInUse[STATE_PASSED].clear();
	m_vArrowsInUse[STATE_FOCUSED].clear();
	m_vArrowsInUse[STATE_REMAINED].clear();
	m_vNodesInUse[STATE_PASSED].clear();
	m_vNodesInUse[STATE_FOCUSED].clear();
	m_vNodesInUse[STATE_REMAINED].clear();

	if (m_pRoutes)
	{
		auto *pTM=CTableManage::GetInstance();
		for (auto it : (*m_pRoutes))
		{
			StopPtnRoutes *pSPR = (StopPtnRoutes *)it.get();
			auto diit = find_if(pTM->m_vStationInformation.begin(), pTM->m_vStationInformation.end(), findSQLData(pSPR->nDestIndexLCD));
			if (diit != pTM->m_vStationInformation.end())
			{
				auto *pDI = (StationInformation*)diit->get();
				CMappedValue::setDestinationCode(pDI->nStationCode);
			}
			auto subit = find_if(pTM->m_vStationDistance.begin(), pTM->m_vStationDistance.end(), findSQLData(pSPR->nDistIndex));
			if (subit != pTM->m_vStationDistance.end())
			{
				StationDistance *pSD = (StationDistance*)subit->get();
				if (m_pLineMapNode)
				{
					unsigned int uDepart = 0, uArrival = 0;
					auto dit = find_if(pTM->m_vStationInformation.begin(), pTM->m_vStationInformation.end(), findSQLData(pSD->nDepartStn));
					auto ait = find_if(pTM->m_vStationInformation.begin(), pTM->m_vStationInformation.end(), findSQLData(pSD->nArrivalStn));
					if ((dit != pTM->m_vStationInformation.end()) && (ait != pTM->m_vStationInformation.end()))
					{
						uDepart = pSD->nDepartStn;
						uArrival = pSD->nArrivalStn;
						auto dit = find_if(m_pLineMapNode->begin(), m_pLineMapNode->end(), [&uDepart](std::shared_ptr<CSQLData> &pData)
						{
							LineMapNode *pLMN = (LineMapNode*)pData.get();
							return (pLMN->nStationIndex == uDepart);
						});
						if (dit != m_pLineMapNode->end())
						{
							LineMapNode *pLMN = (LineMapNode*)dit->get();
							uDepart = MAKECOORDKEY(pLMN->nPosX, pLMN->nPosY);
						}
						else
							uDepart = 0;
						auto ait = find_if(m_pLineMapNode->begin(), m_pLineMapNode->end(), [&uArrival](std::shared_ptr<CSQLData> &pData)
						{
							LineMapNode *pLMN = (LineMapNode*)pData.get();
							return (pLMN->nStationIndex == uArrival);
						});
						if (ait != m_pLineMapNode->end())
						{
							LineMapNode *pLMN = (LineMapNode*)ait->get();
							uArrival = MAKECOORDKEY(pLMN->nPosX, pLMN->nPosY);
						}
						else
							uArrival = 0;

						auto setNodeState = [this](bool *bNodePassed,int nIndex, int nFocused,std::shared_ptr<CSQLData> &pData)->bool
						{
							if ((*bNodePassed) || (!nFocused))
								m_vNodesInUse[STATE_REMAINED].push_back(pData);
							else
							{
								if ((nIndex == nFocused)&&nFocused)
								{
									m_vNodesInUse[STATE_FOCUSED].push_back(pData);
									auto *pTM = CTableManage::GetInstance();
									auto it = find_if(pTM->m_vStationInformation.begin(), pTM->m_vStationInformation.end(), findSQLData(nFocused));
									if (it != pTM->m_vStationInformation.end())
									{
										StationInformation *pSI = (StationInformation*)it->get();
										CMappedValue::setStationCode(pSI->nStationCode);
									}
									(*bNodePassed) = true;
									return true;
								}
								else
									m_vNodesInUse[STATE_PASSED].push_back(pData);
							}
							return false;
						};

						auto setArrowState = [this](bool *bArrowPassed,int nIndex,int nFocused,std::shared_ptr<CSQLData> &pData)->bool
						{
							if ((*bArrowPassed) || (!nFocused))
								m_vArrowsInUse[STATE_REMAINED].push_back(pData);
							else
							{
								if ((nIndex == nFocused) && nFocused)
								{
									m_vArrowsInUse[STATE_FOCUSED].push_back(pData);
									(*bArrowPassed) = true;
									return true;
								}
								else
								{
									m_vArrowsInUse[STATE_PASSED].push_back(pData);
								}
							}
							return false;
						};
						if (uDepart&&uArrival)
						{
							bool bRetVal = false;
							auto arit = find_if(m_pLineMapArrowTextures->begin(), m_pLineMapArrowTextures->end(), [&uDepart, &uArrival](std::shared_ptr<CSQLData> &pData)
							{
								LineMapArrowTexture *pLMAT = (LineMapArrowTexture*)pData.get();
								return (pLMAT->uStart == uDepart) && (pLMAT->uEnd == uArrival);
							});
							if (arit != m_pLineMapArrowTextures->end())
								bRetVal=setArrowState(&bArrowPassed, pSPR->GetIndex(), nCurRouteIdx, *arit);

							if (nFocusedStnIdx)
							{
								if (bFirst)
								{

									setNodeState(&bNodePassed, pSD->nDepartStn, nFocusedStnIdx, *dit);
									setNodeState(&bNodePassed, pSD->nArrivalStn, nFocusedStnIdx, *ait);
									bFirst = false;
								}
								else
									setNodeState(&bNodePassed, pSD->nArrivalStn, nFocusedStnIdx, *ait);
							}
							else
							{
								if (bFirst)
								{

									setNodeState(&bNodePassed, pSD->nDepartStn, 0, *dit);
									setNodeState(&bNodePassed, pSD->nArrivalStn, bRetVal? pSD->nArrivalStn:0, *ait);
									bFirst = false;
								}
								else
									setNodeState(&bNodePassed, pSD->nArrivalStn, bRetVal ? pSD->nArrivalStn : 0, *ait);
							}

						}
					}
				}
			}
		}
	}
}



void QGLESLineMapPreview::prepareArrow(std::vector<std::shared_ptr<CSQLData>> *m_pLineMapArrowTextures,int nWidth, int nHeight,float fR, float fG, float fB)
{
	GLuint uPreFrameBuffer = 0;
	if (!lineProgram.bind())
		close();
	glEnableVertexAttribArray(m_uPosLineLoc);
	auto *pDM = CDataManage::GetInstance();
	if (m_pLineMapArrowTextures)
	{
		for (auto it : (*m_pLineMapArrowTextures))
		{
			auto pLMAT = (LineMapArrowTexture *)it.get();
			auto findIt = m_mArrow.find(pLMAT->GetIndex());
			if (findIt != m_mArrow.end())
			{
				for (auto xit : findIt->second->vIdxList)
				{
					if (uPreFrameBuffer != xit.uFrameBufferIdx)
					{
						glBindFramebuffer(GL_FRAMEBUFFER, xit.uFrameBufferIdx);
						glViewport(0, 0, nWidth, nHeight);
						//glClear(GL_COLOR_BUFFER_BIT);
						//glClearColor(1.0, 0.0, 0.0, 1.0);
						glBindBuffer(GL_ARRAY_BUFFER, m_uVBOsID[2]);
						glVertexAttribPointer(m_uPosLineLoc, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
						QMatrix4x4 matrix;
						matrix.ortho(0, nWidth, nHeight, 0, -1, 1);
						glUniformMatrix4fv(m_uMatrixLineLoc, 1, false, (const GLfloat*)&matrix);
						uPreFrameBuffer = xit.uFrameBufferIdx;
					}
					glUniform4f(m_uColorLineLoc, fR, fG, fB, 1.0);
					glDrawArrays(GL_TRIANGLE_STRIP, xit.iOffsetVtx, xit.iCountVtx);
				}
			}
		}
	}
	glDisableVertexAttribArray(m_uPosLineLoc);
}


void QGLESLineMapPreview::setArrowProgress(std::vector<std::shared_ptr<CSQLData>> *m_pLineMapArrowTextures, int nWidth, int nHeight,int nPerMil,float fR, float fG, float fB, float fPR, float fPG, float fPB)
{
	GLuint uPreFrameBuffer = 0;
	if (!lineProgram.bind())
		close();
	int nTotalVtxCount=0;
	glEnableVertexAttribArray(m_uPosLineLoc);
	auto *pDM = CDataManage::GetInstance();
	if (m_pLineMapArrowTextures)
	{
		for (auto it : (*m_pLineMapArrowTextures))
		{
			auto pLMAT = (LineMapArrowTexture *)it.get();
			auto findIt = m_mArrow.find(pLMAT->GetIndex());
			if (findIt != m_mArrow.end())
			{
				for (auto xit : findIt->second->vIdxList)
				{
					nTotalVtxCount+=xit.iCountVtx;
				}
			}
		}
		bool bPassed = false;
		int nPassed=(int)(((float)nPerMil/1000.f)*((float)nTotalVtxCount));
		int nLeft = nTotalVtxCount - nPassed;
		for (auto it : (*m_pLineMapArrowTextures))
		{
			auto pLMAT = (LineMapArrowTexture *)it.get();
			auto findIt = m_mArrow.find(pLMAT->GetIndex());
			if (findIt != m_mArrow.end())
			{
				for (auto xit : findIt->second->vIdxList)
				{
					if (uPreFrameBuffer != xit.uFrameBufferIdx)
					{
						glBindFramebuffer(GL_FRAMEBUFFER, xit.uFrameBufferIdx);
						glViewport(0, 0, nWidth, nHeight);
						//glClear(GL_COLOR_BUFFER_BIT);
						//glClearColor(0.0, 0.0, 0.0, 0.0);
						glBindBuffer(GL_ARRAY_BUFFER, m_uVBOsID[2]);
						glVertexAttribPointer(m_uPosLineLoc, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
						QMatrix4x4 matrix;
						matrix.ortho(0, nWidth, nHeight, 0, -1, 1);
						glUniformMatrix4fv(m_uMatrixLineLoc, 1, false, (const GLfloat*)&matrix);
						uPreFrameBuffer = xit.uFrameBufferIdx;
					}
					if(!bPassed)
					{
						if (nPassed > xit.iCountVtx)
						{
							glUniform4f(m_uColorLineLoc, fPR, fPG, fPB, 1.0);
							glDrawArrays(GL_TRIANGLE_STRIP, xit.iOffsetVtx, xit.iCountVtx);
							nPassed -= xit.iCountVtx;
						}
						else
						{
							int nTmpLeft = xit.iCountVtx - nPassed;
							if (nPassed)
							{
								glUniform4f(m_uColorLineLoc, fPR, fPG, fPB, 1.0);
								glDrawArrays(GL_TRIANGLE_STRIP, xit.iOffsetVtx, nPassed);
							
							}
							glUniform4f(m_uColorLineLoc, fR, fG, fB, 1.0);
							glDrawArrays(GL_TRIANGLE_STRIP, xit.iOffsetVtx + nPassed, nTmpLeft);
							nPassed = 0;
							bPassed = true;
							nLeft = nTmpLeft;
						}
					}
					else
					{
						glUniform4f(m_uColorLineLoc, fR, fG, fB, 1.0);
						glDrawArrays(GL_TRIANGLE_STRIP, xit.iOffsetVtx, xit.iCountVtx);
					}
				}
			}
		}
		glDisableVertexAttribArray(m_uPosLineLoc);
	}
}




void QGLESLineMapPreview::initBaseData()
{
	vBinPacked.clear();
	vBinPackedDest.clear();

	initVBO();
	auto *pTM = CTableManage::GetInstance();
	CTextureInfo *pTI = CTextureInfo::GetInstance();
	pTI->SetOpenGLFunctions(this);
	int m_nTextureWidth = 1024;;
	int m_nTextureHeight = 1024;
	int m_nBytesPerPixel = 4;

	for (auto it : pTM->m_vStationImagePool)
	{
		StationImagePool *pPool = (StationImagePool*)it.get();
		setStationImageTexture(pPool,vVertices,vIndices, m_nTextureWidth, m_nTextureHeight, m_nBytesPerPixel);
	}

	for (auto it : pTM->m_vBitmapImagePool)
	{
		BitmapImagePool *pPool = (BitmapImagePool*)it.get();
		setBitmapImageTexture(pPool, vVertices, vIndices, m_nTextureWidth, m_nTextureHeight, m_nBytesPerPixel);
	}
	initImageListBoundRect();
	auto setImageListTexInfo = [this, &m_nTextureWidth, &m_nTextureHeight](std::vector<GLfloat> &vVert, std::vector<GLushort> &Indices, GLfloat fLeft, 
		GLfloat fTop, GLfloat fRight, GLfloat fBottom, GLfloat fXPos, GLfloat fYPos, int nTextureIndex, int nIndex,int iOffset,int iCount)
	{
		GLsizei xCount = 0, xOffset = 0;
		CTextureInfo *pTI = CTextureInfo::GetInstance();
		pTI->GetTextureInfo(vVertices, vIndices, fLeft, fTop, fRight, fBottom,
			iOffset, iCount, &xCount, &xOffset, m_uVBOsID[0], m_uVBOsID[1], (GLfloat)fXPos, (GLfloat)fYPos);
		auto subFindIt = m_mImageList.find(nIndex);
		if (subFindIt != m_mImageList.end())
		{
			subFindIt->second.get()->AddIndex(nTextureIndex, xCount, xOffset);
		}
		else
		{
			std::shared_ptr<CTexPool> pTP = std::shared_ptr<CTexPool>(new CTexPool((GLfloat)fLeft, (GLfloat)fTop, (GLfloat)fRight, (GLfloat)fBottom));
			pTP->AddIndex(nTextureIndex, xCount, xOffset);
			m_mImageList[nIndex] = pTP;
		}
	};


	for (auto it : pTM->m_vImageIndexList)
	{
		ImageIndexList *pIIL = (ImageIndexList*)it.get();
		if (pIIL->GetIndex() == 29)
		{
			int nIndex = 9;
			nIndex = 20;
		}
		for (auto subit : pIIL->m_vChildItem[0].vSQLData)
		{
			ImageIndex *pII = (ImageIndex*)(subit.get());
			GLsizei nCount, nOffset;
			GLint nTexIndex;
			switch (pII->nType)
			{
			case 1:
				{	
					auto findIt=m_mStation.find(pII->nStationNameBitmapIndex);
					if (findIt != m_mStation.end())
					{
						setImageListTexInfo(vVertices, vIndices, findIt->second->m_fRect[0], findIt->second->m_fRect[1], findIt->second->m_fRect[2],
							findIt->second->m_fRect[3], (GLfloat)pII->nXPos, (GLfloat)pII->nYPos, findIt->second->vIdxList.begin()->nTextureIndex, pIIL->GetIndex(), findIt->second->vIdxList.begin()->iOffset, findIt->second->vIdxList.begin()->iCount);
					}
				}
				break;
			case 2:
				{
					auto findIt = m_mBitmap.find(pII->nStationBitmapIndex);
					if (findIt != m_mBitmap.end())
					{
						setImageListTexInfo(vVertices, vIndices, findIt->second->m_fRect[0], findIt->second->m_fRect[1], findIt->second->m_fRect[2],
							findIt->second->m_fRect[3], (GLfloat)pII->nXPos, (GLfloat)pII->nYPos, findIt->second->vIdxList.begin()->nTextureIndex, pIIL->GetIndex(), findIt->second->vIdxList.begin()->iOffset, findIt->second->vIdxList.begin()->iCount);
					}
				}
			break;
			}
		}
		auto iilit = m_mImageList.find(pIIL->GetIndex());
		if (iilit != m_mImageList.end())
		{
			memcpy(iilit->second->m_fRect,pIIL->fRect,sizeof(pIIL->fRect));
		}
	}


	for (auto it : pTM->m_vLineMapPool)
	{
		LineMapPool *pPool = (LineMapPool*)it.get();
		setLineMapLinkTexture(pPool, vVertices, vIndices, m_nTextureWidth, m_nTextureHeight, m_nBytesPerPixel);
		for (auto subit : pPool->m_vChildItem[3].vSQLData)
		{
			LineMapArrowTexture *pLMAT = (LineMapArrowTexture*)subit.get();
			setArrowTexture(pLMAT, vVertices, vIndices, vVerticesArrow, m_nTextureWidth, m_nTextureHeight, m_nBytesPerPixel);
		}
	}
}

void QGLESLineMapPreview::setLineMapLinkTexture(LineMapPool *pLMP, std::vector<GLfloat> &vVertex, std::vector<GLushort> &vIndices, int nWholeWidth, int nWholeHeight, int nBytesPerPixel)
{
	int nIsFilled;
	bool bIsFilled;
	PushTextureInfo(vBinPacked, vVertex, vIndices, m_mLineMapLink[pLMP->GetIndex()], pLMP->pByteSpot.get(), pLMP->nWidth, pLMP->nWidth, nWholeWidth, nWholeHeight, nBytesPerPixel, 0);

	std::shared_ptr<unsigned char> pDstChk = std::shared_ptr<unsigned char>((unsigned char*)calloc(pLMP->nProp*nBytesPerPixel, 1), free);
	memset(pDstChk.get(), 0, pLMP->nProp*nBytesPerPixel);

	int nLoopCount = pLMP->nSize / (pLMP->nProp*pLMP->nProp*nBytesPerPixel);
	for (int i = 0; i < nLoopCount; i++)
	{
		bIsFilled = false;
		unsigned char *pDstBuf,*pSocBuf = (unsigned char*)pLMP->pByte.get() + pLMP->nProp*nBytesPerPixel*i;
		std::shared_ptr<unsigned char> pDst = std::shared_ptr<unsigned char>((unsigned char*)calloc(pLMP->nProp*pLMP->nProp*nBytesPerPixel, 1), free);
		pDstBuf = pDst.get();
		for (int j = 0; j < pLMP->nProp; j++)
		{
			memcpy(pDstBuf, pSocBuf, pLMP->nProp*nBytesPerPixel);
			
			//nIsFilled |= memcmp(pDstChk.get(), pSocBuf, pLMP->nProp*nBytesPerPixel);
			if (nBytesPerPixel == 4)
			{
				unsigned int *pTmp = (unsigned int*)pDstBuf;
				for (int k = 0; k < pLMP->nProp; k++)
				{
					unsigned int uValue = pTmp[k];
					unsigned char uAlpha = ((uValue & 0xff000000) >> 24);
					if (!uAlpha)
					{
						pTmp[k] = 0x00FFFFFF;
					}
					else
						bIsFilled = true;
				}
			}
			pSocBuf += (pLMP->nProp*nBytesPerPixel*nLoopCount);
			pDstBuf += (pLMP->nProp*nBytesPerPixel);
		}
		//비트맵 체크 필요함
		if(bIsFilled)
			PushTextureInfo(vBinPacked, vVertex, vIndices, m_mLineMapLink[pLMP->GetIndex()], pDst.get(), pLMP->nProp, pLMP->nProp, nWholeWidth, nWholeHeight, nBytesPerPixel, i);
	}
}

void QGLESLineMapPreview::setBitmapImageTexture(BitmapImagePool *pBIP, std::vector<GLfloat> &vVertex, std::vector<GLushort> &vIndices, int nWholeWidth, int nWholeHeight, int nBytesPerPixel)
{
	PushTextureInfo(vBinPacked, vVertex, vIndices, m_mBitmap, pBIP->pByte.get(), pBIP->nWidth, pBIP->nHeight, nWholeWidth, nWholeHeight, nBytesPerPixel, pBIP->GetIndex());
}

void QGLESLineMapPreview::setStationImageTexture(StationImagePool *SIP, std::vector<GLfloat> &vVertex, std::vector<GLushort> &vIndices, int nWholeWidth, int nWholeHeight, int nBytesPerPixel)
{
	PushTextureInfo(vBinPacked, vVertex, vIndices, m_mStation, SIP->pByte.get(), SIP->nWidth, SIP->nHeight, nWholeWidth, nWholeHeight, nBytesPerPixel, SIP->GetIndex());
}

void QGLESLineMapPreview::setArrowTexture(LineMapArrowTexture *pLMAT, std::vector<GLfloat> &vVertex, std::vector<GLushort> &vIndices, std::vector<GLfloat> &vVertexArrow, int nWholeWidth, int nWholeHeight, int nBytesPerPixel)
{
	PushDoubleTextureInfo(vBinPackedDest, vVertex, vIndices, vVertexArrow, m_mArrow, pLMAT->pByte.get(), pLMAT->nTexWidth, pLMAT->nTexHeight, nWholeWidth, nWholeHeight, nBytesPerPixel, pLMAT->pByteVertex.get(), pLMAT->nVtxBufSize, pLMAT->GetIndex());
}




void QGLESLineMapPreview::PushTextureInfo(std::vector<std::shared_ptr<MaxRectsPixelBuffer>> &vBinPacked, std::vector<GLfloat> &vVertex, std::vector<GLushort> &vIndices,
	std::map<GLuint, std::shared_ptr<CTexPool>> &mTexPool,unsigned char *pSoc,int nWidth,int nHeight,int nWholeWidth,int nWholeHeight,int nBytesPerPixel,int nIndex)
{
	bool bTextureCopied = false;
	GLsizei iOffset, iCount;
	GLsizei iOffsetVtx, iCountVtx;
	CTextureInfo* pTI = CTextureInfo::GetInstance();
	pTI->SetOpenGLFunctions(this);
	auto fillTextureMap = [&nWidth, &nHeight,&bTextureCopied,&mTexPool,&pSoc,&vVertex,&vIndices,&nWholeWidth,&nWholeHeight,&nIndex](MaxRectsPixelBuffer *pPixBuf,GLuint uVtx,GLuint uIdx)->bool
	{
		GLsizei iOffset, iCount;
		CTextureInfo* pTI = CTextureInfo::GetInstance();
		rbp::MaxRectsBinPack::FreeRectChoiceHeuristic heuristic = rbp::MaxRectsBinPack::RectBestShortSideFit;
		rbp::Rect packedRect = pPixBuf->Insert(nWidth, nHeight, heuristic);
		if ((packedRect.height > 0) && (packedRect.width > 0))
		{
			if ((packedRect.width == nWidth) && (packedRect.height == nHeight))
			{
				bTextureCopied = true;
				pPixBuf->SetSubImage(packedRect.x, packedRect.y, packedRect.width, packedRect.height, pSoc);
				std::shared_ptr<CTexPool> pTP = std::shared_ptr<CTexPool>(new CTexPool((GLfloat)0, (GLfloat)0, (GLfloat)packedRect.width, (GLfloat)packedRect.height));
				pTI->GetTextureInfo(vVertex, vIndices, packedRect.x, packedRect.y, packedRect.width, packedRect.height, (GLfloat)nWholeWidth, (GLfloat)nWholeHeight, 0.5, &iCount, &iOffset, uVtx, uIdx);
				pTP->AddIndex(pPixBuf->Get1StTextureIdx(), iCount, iOffset);
				pTP->SetOrigin(1);
				mTexPool[nIndex] = pTP;
				return true;
			}
		}
		return false;
	};
	for (auto it : vBinPacked)
	{
		fillTextureMap(it.get(), m_uVBOsID[0], m_uVBOsID[1]);
	}
	if (!bTextureCopied)
	{
		vBinPacked.push_back(std::shared_ptr<MaxRectsPixelBuffer>(new MaxRectsPixelBuffer(nWholeWidth, nWholeHeight, nBytesPerPixel, true, false, true)));
		fillTextureMap(vBinPacked.rbegin()->get(), m_uVBOsID[0], m_uVBOsID[1]);
	}
}


void QGLESLineMapPreview::PushDoubleTextureInfo(std::vector<std::shared_ptr<MaxRectsPixelBuffer>> &vBinPacked, std::vector<GLfloat> &vVertex, std::vector<GLushort> &vIndices, std::vector<GLfloat> &v2ndVertex,
	std::map<GLuint, std::shared_ptr<CTexPool>> &mTexPool, unsigned char *pSoc,int nWidth, int nHeight, int nWholeWidth, int nWholeHeight, int nBytesPerPixel, unsigned char *pVertexBuf,int nVtxSize,int nIndex)
{
	bool bTextureCopied = false;
	GLsizei iOffset, iCount;
	GLsizei iOffsetVtx, iCountVtx;
	CTextureInfo* pTI = CTextureInfo::GetInstance();
	pTI->SetOpenGLFunctions(this);
	auto fillTextureMap = [&nWidth, &nHeight, &bTextureCopied, &mTexPool, &pSoc, &vVertex, &vIndices,&v2ndVertex, &nWholeWidth, &nWholeHeight, &nIndex,&pVertexBuf,&nVtxSize](MaxRectsPixelBuffer *pPixBuf, GLuint uVtx, GLuint uIdx,GLuint u2ndVtx)->bool
	{
		GLsizei iOffset, iCount, iCountVtx, iOffsetVtx;
		CTextureInfo* pTI = CTextureInfo::GetInstance();
		rbp::MaxRectsBinPack::FreeRectChoiceHeuristic heuristic = rbp::MaxRectsBinPack::RectBestShortSideFit;
		rbp::Rect packedRect = pPixBuf->Insert(nWidth, nHeight, heuristic);
		if ((packedRect.height > 0) && (packedRect.width > 0))
		{
			if ((packedRect.width == nWidth) && (packedRect.height == nHeight))
			{
				bTextureCopied = true;
				pPixBuf->SetSubImage(packedRect.x, packedRect.y, packedRect.width, packedRect.height, pSoc);
				std::shared_ptr<CTexPool> pTP = std::shared_ptr<CTexPool>(new CTexPool((GLfloat)0, (GLfloat)0, (GLfloat)packedRect.width, (GLfloat)packedRect.height));
				pTI->GetTextureInfo(vVertex, vIndices, packedRect.x, packedRect.y, packedRect.width, packedRect.height, (GLfloat)nWholeWidth, (GLfloat)nWholeHeight, 0.5, &iCount, &iOffset, uVtx, uIdx);
				pTI->GetTextureInfo(v2ndVertex, (GLfloat)packedRect.x, (GLfloat)packedRect.y, (GLfloat*)pVertexBuf, nVtxSize / sizeof(float), &iCountVtx, &iOffsetVtx, u2ndVtx);
				pTP->AddIndex(pPixBuf->Get1StTextureIdx(), iCount, iOffset, pPixBuf->Get2ndTextureIdx(), iCountVtx, iOffsetVtx, pPixBuf->GetFrameBufferIdx());
				pTP->SetOrigin(1);
				mTexPool[nIndex] = pTP;
				return true;
			}
		}
		return false;
	};
	for (auto it : vBinPacked)
	{
		fillTextureMap(it.get(), m_uVBOsID[0], m_uVBOsID[1], m_uVBOsID[2]);
	}
	if (!bTextureCopied)
	{
		vBinPacked.push_back(std::shared_ptr<MaxRectsPixelBuffer>(new MaxRectsPixelBuffer(nWholeWidth, nWholeHeight, nBytesPerPixel, true, false, true)));
		fillTextureMap(vBinPacked.rbegin()->get(), m_uVBOsID[0], m_uVBOsID[1], m_uVBOsID[2]);
	}
}


void QGLESLineMapPreview::initImageListBoundRect()
{
	auto *pTM = CTableManage::GetInstance();
	auto unitedRect = [](GLfloat *pFloatL, GLfloat *pFloatR, GLfloat *pFloatU)->bool
	{
		bool bRet = true;
		if (pFloatL&&pFloatR&&pFloatU)
		{
			if (pFloatL[0] == 0.0f&&pFloatL[1] == 0.0f&&pFloatL[2] == 0.0f&&pFloatL[3] == 0.0f)
			{
				memcpy(pFloatL, pFloatR, sizeof(GLfloat) * 4);
			}
			else if (pFloatR[0] == 0.0f&&pFloatR[1] == 0.0f&&pFloatR[2] == 0.0f&&pFloatR[3] == 0.0f)
			{
				memcpy(pFloatR, pFloatL, sizeof(GLfloat) * 4);
			}
			pFloatU[2] = max(pFloatL[2], pFloatR[2]);
			pFloatU[3] = max(pFloatL[3], pFloatR[3]);
			pFloatU[0] = min(pFloatL[0], pFloatR[0]);
			pFloatU[1] = min(pFloatL[1], pFloatR[1]);
		}
		else
			bRet = false;
		return bRet;
	};

	for (auto it : pTM->m_vImageIndexList)
	{
		ImageIndexList *pIIL = (ImageIndexList*)it.get();
		if (pIIL->GetIndex() == 29)
		{
			int nValue = 0;
			nValue = 0;
		}
		memset(pIIL->fRect, 0, sizeof(pIIL->fRect));
		for (auto subit : it->m_vChildItem[0].vSQLData)
		{
			int nImageIndex = 0;
			ImageIndex *pII = (ImageIndex*)subit.get();
			switch (pII->nType)
			{
				case 1:
				{
					auto tmpit = find_if(pTM->m_vStationImagePool.begin(), pTM->m_vStationImagePool.end(), findSQLData(pII->nStationNameBitmapIndex));
					if (tmpit != pTM->m_vStationImagePool.end())
					{
						StationImagePool *pSIP = (StationImagePool*)tmpit->get();
						if (pSIP->nDataLength&&pSIP->pByte.get())
						{
							GLfloat fL[4] = { (GLfloat)pII->nXPos,(GLfloat)pII->nYPos,(GLfloat)(pII->nXPos + pSIP->nWidth),(GLfloat)(pII->nYPos + pSIP->nHeight) };
							unitedRect(pIIL->fRect, fL, pIIL->fRect);
						}
					}
				}
				break;
			case 2:
				{
					auto tmpit = find_if(pTM->m_vBitmapImagePool.begin(), pTM->m_vBitmapImagePool.end(), findSQLData(pII->nStationBitmapIndex));
					if (tmpit != pTM->m_vBitmapImagePool.end())
					{
						BitmapImagePool *pSIP = (BitmapImagePool*)tmpit->get();
						if (pSIP->nDataLength&&pSIP->pByte.get())
						{
							GLfloat fL[4] = { (GLfloat)pII->nXPos,(GLfloat)pII->nYPos,(GLfloat)(pII->nXPos + pSIP->nWidth),(GLfloat)(pII->nYPos + pSIP->nHeight) };
							unitedRect(pIIL->fRect, fL, pIIL->fRect);
						}
					}
				}
				break;
			}
		};
	}
}

void QGLESLineMapPreview::setCurrentTime(int nCurTime)
{
	m_nCurTime = nCurTime;
	update();
}

void QGLESLineMapPreview::saveTextureImage(GLuint nTexture, int nWidth, int nHeight, int nBytePerPixel)
{
	std::shared_ptr<unsigned char> pByte = std::shared_ptr<unsigned char>((unsigned char*)malloc(nWidth*nHeight*nBytePerPixel), free);
	memset(pByte.get(), 0, nWidth*nHeight*nBytePerPixel);
	glBindTexture(GL_TEXTURE_2D, nTexture);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pByte.get());
	glBindTexture(GL_TEXTURE_2D, 0);
	Gdiplus::Bitmap *pBitmap = new Gdiplus::Bitmap(nWidth, nHeight, PixelFormat32bppARGB);
	Gdiplus::BitmapData* bitmapData = new Gdiplus::BitmapData;
	Gdiplus::Rect tRect(0, 0, nWidth, nHeight);
	pBitmap->LockBits(&tRect, Gdiplus::ImageLockModeWrite, PixelFormat32bppARGB, bitmapData);
	UINT *pixels = (UINT*)bitmapData->Scan0;
	UINT *sourcePixels = (UINT*)pByte.get();
	bitmapData->Stride;

	for (UINT row = 0; row<nHeight; row++)
	{
		memcpy(pixels, sourcePixels, nWidth*nBytePerPixel);
		pixels += (bitmapData->Stride / 4);
		sourcePixels += nWidth;
	}
	pBitmap->UnlockBits(bitmapData);

	CLSID clsid;
	GetEncCLSID(L"image/png", &clsid);
	wchar_t szBuffer[256];
	swprintf_s(szBuffer, dim(szBuffer), L"C:\\Intel\\Texture%d.PNG", nTexture);
	pBitmap->Save(szBuffer, &clsid);

}

bool QGLESLineMapPreview::GetEncCLSID(wchar_t *mime, CLSID *pClsid)
{
	UINT num, size, i;
	Gdiplus::ImageCodecInfo *arCod;
	BOOL bFound = FALSE;
	Gdiplus::GetImageEncodersSize(&num, &size);
	arCod = (Gdiplus::ImageCodecInfo *)malloc(size);
	GetImageEncoders(num, size, arCod);
	for (i = 0; i<num; i++) {
		if (wcscmp(arCod[i].MimeType, mime) == 0) {
			*pClsid = arCod[i].Clsid;
			bFound = TRUE;
			break;
		}
	}
	free(arCod);
	return bFound;
}


void QGLESLineMapPreview::initDisplayItem()
{
	auto *pTM = CTableManage::GetInstance();
	CMappedValue *pMV = CMappedValue::GetInstance();
	for (auto it : pTM->m_vDisplayItemPool)		//DisplayItemPool
	{
		for (auto subit : it.get()->m_vChildItem[0].vSQLData)
		{
			DisplayItem *pItem = (DisplayItem*)subit.get();
			CDataManage::reorderTimeLine(pItem);
			auto it = m_mImageList.find(pItem->nRelatedItemListIndex);
			if (it != m_mImageList.end())
			{
				pItem->SetOrigin(pItem->nOrigin);
				it->second->SetOrigin(pItem->nOrigin, true);
				pItem->fOrigX = it->second->m_fOrigin[0];
				pItem->fOrigY = it->second->m_fOrigin[1];
				pItem->SetBufferIndex(it->first, it->second.get());
				setBoundRectangle(pItem);
			}
		}

		for (auto subit : it.get()->m_vChildItem[1].vSQLData)
		{
			DisplayMetaItem *pItem = (DisplayMetaItem*)subit.get();
			CDataManage::reorderTimeLine(pItem);
			pItem->m_fRect[0] = 0;
			pItem->m_fRect[1] = 0;
			pItem->m_fRect[2] = (GLfloat)pItem->nWidth;
			pItem->m_fRect[3] = (GLfloat)pItem->nHeight;
			pItem->SetOrigin(pItem->nOrigin, true);
			pMV->getMappedValue(pItem->szTagItem, &pItem->m_pValueMonitor);
			setBoundRectangle(pItem);
			setMetaItemOrientation(pItem);
		}
	}
}


void QGLESLineMapPreview::initMetaDisplayItem()
{
	/*auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();
	auto pVEC = pDM->GET_MODEL_CLASS(DisplayMetaItem).get()->getVector();
	for (auto it : (*pVEC))
	{
		DisplayMetaItem *pItem = (DisplayMetaItem*)it.get();
		pItem->m_fRect[0] = 0;
		pItem->m_fRect[1] = 0;
		pItem->m_fRect[2] = (GLfloat)pItem->nWidth;
		pItem->m_fRect[3] = (GLfloat)pItem->nHeight;
		pItem->SetOrigin(pItem->nOrigin, true);
		setBoundRectangle(pItem);
		setMetaItemOrientation(pItem);
	}*/
}


void QGLESLineMapPreview::setBoundRectangle(DisplayMetaItem *pItem)
{
	pItem->m_fTempRect[0] = pItem->m_fTempRect[8] = (GLfloat)pItem->m_fRect[0];
	pItem->m_fTempRect[1] = pItem->m_fTempRect[9] = (GLfloat)pItem->m_fRect[1];
	pItem->m_fTempRect[2] = (GLfloat)pItem->m_fRect[2];
	pItem->m_fTempRect[3] = (GLfloat)pItem->m_fRect[1];
	pItem->m_fTempRect[4] = (GLfloat)pItem->m_fRect[2];
	pItem->m_fTempRect[5] = (GLfloat)pItem->m_fRect[3];
	pItem->m_fTempRect[6] = (GLfloat)pItem->m_fRect[0];
	pItem->m_fTempRect[7] = (GLfloat)pItem->m_fRect[3];
}



void QGLESLineMapPreview::setBoundRectangle(DisplayItem *pItem)
{
	pItem->m_fTempRect[0] = pItem->m_fTempRect[8] = (GLfloat)pItem->m_fRect[0];
	pItem->m_fTempRect[1] = pItem->m_fTempRect[9] = (GLfloat)pItem->m_fRect[1];
	pItem->m_fTempRect[2] = (GLfloat)pItem->m_fRect[2];
	pItem->m_fTempRect[3] = (GLfloat)pItem->m_fRect[1];
	pItem->m_fTempRect[4] = (GLfloat)pItem->m_fRect[2];
	pItem->m_fTempRect[5] = (GLfloat)pItem->m_fRect[3];
	pItem->m_fTempRect[6] = (GLfloat)pItem->m_fRect[0];
	pItem->m_fTempRect[7] = (GLfloat)pItem->m_fRect[3];
}

void QGLESLineMapPreview::setMetaItemOrientation(DisplayMetaItem *pItem)
{
	float fRatioX, fRatioY, fOffsetX, fOffsetY;
	auto findIt = m_mImageList.find(pItem->nRelatedIndex);
	if (findIt != m_mImageList.end())
	{
		if ((!pItem->nLimit) || ((float)pItem->nWidth > findIt->second->m_fRect[2]))
		{
			switch (pItem->nHAlignMode)
			{
			case 0:
				pItem->fOffsetX = 0;
				break;
			case 1:
				pItem->fOffsetX = ((float)pItem->nWidth - findIt->second->m_fRect[2]) / 2.0f;
				break;
			case 2:
				pItem->fOffsetX = ((float)pItem->nWidth - findIt->second->m_fRect[2]);
				break;
			}
			pItem->fRatioX = 1.0f;
		}
		else
		{
			pItem->fOffsetX = 0.0f;
			pItem->fRatioX = (GLfloat)pItem->nWidth / (GLfloat)findIt->second->m_fRect[2];
		}

		if ((!pItem->nLimit) || ((float)pItem->nHeight > findIt->second->m_fRect[3]))
		{
			switch (pItem->nVAlignMode)
			{
			case 0:
				pItem->fOffsetY = 0;
				break;
			case 1:
				pItem->fOffsetY = ((float)pItem->nHeight - findIt->second->m_fRect[3]) / 2.0f;
				break;
			case 2:
				pItem->fOffsetY = ((float)pItem->nHeight - findIt->second->m_fRect[3]);
				break;
			}
			pItem->fRatioY = 1.0f;
		}
		else
		{
			pItem->fOffsetY = 0.0f;
			pItem->fRatioY = (GLfloat)pItem->nHeight / (GLfloat)findIt->second->m_fRect[3];
		}
	}
}





