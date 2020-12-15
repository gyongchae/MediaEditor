#include "QGLESLineMapCanvas.h"
#include <algorithm>
#include "TableManage.h"
#include "DataManage.h"
#include "dataModel.h"
#include "TextureInformation/CTextureInfo.h"
#include "BinPacked/MaxRectsPixelBuffer.h"
#include "displayItemPropEdit.h"
#include "TexPool.h"
#include <QAction>
#include <QMenu>
#include <QDebug>

QGLESLineMapCanvas::QGLESLineMapCanvas(QWidget * parent)
	: QOpenGLWidget(parent), m_nWidth(0), m_nHeight(0),
	m_eEditMode(EDIT_TILE_MAP), m_nLineWidth(0), m_nCellSize(0), m_pLinkMenu(0), m_nSelectedArrow(-1),
	m_nSelectedNode(-1), m_bNodeAlignPressed(false), m_bPressed(false), m_eCurrentStnState(0), m_nCurTime(0), m_fOffsetX(0), m_fOffsetY(0), m_nSelectedDispItem(0)
{
	memset(m_uVBOsID, 0, sizeof(m_uVBOsID));
	setCurrentStationState(0);
	setAcceptDrops(true);
	setMouseTracking(true);
	setFocusPolicy(Qt::StrongFocus);
}

QGLESLineMapCanvas::QGLESLineMapCanvas(int nRow, QWidget *parent)
	: QOpenGLWidget(parent), m_nWidth(0), m_nHeight(0), m_nRow(nRow),
	m_eEditMode(EDIT_TILE_MAP),m_nLineWidth(0), m_nCellSize(0), m_pLinkMenu(0), m_nSelectedArrow(-1),
	m_nSelectedNode(-1), m_bNodeAlignPressed(false), m_bPressed(false), m_eCurrentStnState(0), m_nCurTime(0),m_fOffsetX(0),m_fOffsetY(0), m_nSelectedDispItem(0)
{
	memset(m_uVBOsID, 0,sizeof(m_uVBOsID));
	setCurrentStationState(0);
	setAcceptDrops(true);
	setMouseTracking(true);
	setFocusPolicy(Qt::StrongFocus);
}


QGLESLineMapCanvas::~QGLESLineMapCanvas()
{
	glDeleteBuffers(3, m_uVBOsID);
}

void QGLESLineMapCanvas::initxxx(int nRow)
{
	m_nRow = nRow;
}


void QGLESLineMapCanvas::dragMoveEvent(QDragMoveEvent *e)
{
	e->accept();
}

void QGLESLineMapCanvas::dragEnterEvent(QDragEnterEvent *e)
{
	if (e->mimeData()->hasFormat("text/plain") && e->mimeData()->hasHtml())
		e->acceptProposedAction();
}

void QGLESLineMapCanvas::dropEvent(QDropEvent * e)
{
	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();
	int nIndex = e->mimeData()->html().toInt();
	std::shared_ptr<CSQLData> pData = pDM->GET_MODEL_CLASS(LineMapDisplayItem).get()->insertRow();
	CSQLData *pSQLData = pData.get();
	if (pSQLData)
	{
		LineMapDisplayItem *pItem = (LineMapDisplayItem*)pSQLData;
		pItem->nRelatedDisplayItem = nIndex;
		pItem->nPosX = e->pos().x();
		pItem->nPosY = e->pos().y();
	}
	update();
}

void QGLESLineMapCanvas::initActions()
{
	auto *pDM = CDataManage::GetInstance();
	m_pActDelItem = new QAction(pDM->m_iconDelMapItem, "&Delete Item", this);
	m_pActEditProp = new QAction(pDM->m_iconEditSpot, "&Edit Property", this);
	m_pActDelItem->setStatusTip(tr("Delete selected item"));
	m_pActEditProp->setStatusTip(tr("Edit properties of selected item"));
	connect(m_pActDelItem, SIGNAL(triggered()), this, SLOT(deleteItem()));
	connect(m_pActEditProp, SIGNAL(triggered()), this, SLOT(editProperties()));

	m_pMenu = new QMenu(this);
	m_pMenu->addAction(m_pActDelItem);
	m_pMenu->addAction(m_pActEditProp);
}

void QGLESLineMapCanvas::deleteItem()
{

}

void QGLESLineMapCanvas::editProperties()
{
	
}

void QGLESLineMapCanvas::getChangedStnAndBound(const int stnOrder, const int bound)
{
	m_unusedLines.clear();
	if (stnOrder != 0)
	{
		auto *pDM = CDataManage::GetInstance();
		auto *pTM = CTableManage::GetInstance();
		auto linkVec = pDM->GET_MODEL_CLASS(LineMapLink)->getVector();

		auto stnVec = pTM->m_vStationInformation;

		int stnCode = 0;

		auto it = find_if(stnVec.begin(), stnVec.end(), findStationNameCodeByTableOrder(stnOrder));
		if (it != stnVec.end())
		{
			auto *a = dynamic_cast<StationInformation*>(it->get());
			stnCode = a->nStationCode;
		}

		qDebug() << "Selected STN CODE:" << stnCode;

		QList<LineMapLink*> unusedLines;
		if (bound == 0) // north
		{
			for (auto it : (*linkVec))
			{
				LineMapLink *pLink = (LineMapLink*)it.get();
				if (pLink->nActiveStation < stnCode)
				{
					unusedLines.append(pLink);
				}
			}
		}
		else if (bound == 1) // south (101 -> 141)
		{
			for (auto it : (*linkVec))
			{
				LineMapLink *pLink = (LineMapLink*)it.get();
				if (pLink->nActiveStation > stnCode)
				{
					unusedLines.append(pLink);
				}
			}
		}
		else
		{

		}
		m_unusedLines = unusedLines;
	}
}

void QGLESLineMapCanvas::setBoundRectangle(DisplayItem *pItem)
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



void QGLESLineMapCanvas::initializeGL()
{
	initializeOpenGLFunctions();
	initShaders();
	initShadersForLine();
	initshadersForArrow();
	initBaseData(m_nRow);
	initDisplayItem();
	initTileMaps();
	initLinkMenu();
	initNodeMenu();
	initArrowMenu();
	initDispItemMenu();
	//reorderAllTimeLine();
}

void QGLESLineMapCanvas::resizeGL(int w, int h)
{
	m_nHeight = h;
	m_nWidth = w;
}

void QGLESLineMapCanvas::paintGL()
{
	prepareArrow(1024,1024);


	CTableManage *pTM = (CTableManage*)CTableManage::GetInstance();
	LineMapPool *pPool = (LineMapPool*)pTM->m_vLineMapPool.at(m_nRow).get();

	//QMatrix4x4 matrix, tempMatrix;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	// Set the viewport
	glViewport(0, 0, m_nWidth, m_nHeight);
	// Clear the color buffer
	
	// Use the program object
	// Bind shader pipeline for use
	if (!scrProgram.bind())
		close();

	glClear(GL_COLOR_BUFFER_BIT);
	GLfloat fBackColor[4] = { 
		(((pPool->uBackColor) & 0xFF)) / 255.0 ,
		(((pPool->uBackColor>>8) & 0xFF)) / 255.0 ,
		(((pPool->uBackColor>>16) & 0xFF)) / 255.0 ,
		(((pPool->uBackColor >> 24) & 0xFF)) / 255.0 };

	glClearColor(
		(((pPool->uBackColor) & 0xFF)) / 255.0f,
		(((pPool->uBackColor >> 8) & 0xFF)) / 255.0f,
		(((pPool->uBackColor >> 16) & 0xFF)) / 255.0f,
		(((pPool->uBackColor >> 24) & 0xFF)) / 255.0f);
	
	glEnableVertexAttribArray(m_aScrPos);
	glEnableVertexAttribArray(m_aScrTexCoord);
	glBindBuffer(GL_ARRAY_BUFFER, m_uVBOsID[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uVBOsID[1]);
	glVertexAttribPointer(m_aScrPos, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glVertexAttribPointer(m_aScrTexCoord, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (const void*)(2 * sizeof(GLfloat)));
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(m_uScrFirstTex, 0);

	auto *pDM = CDataManage::GetInstance();
	auto pVEC = pDM->GET_MODEL_CLASS(LineMapLink)->getVector();

	for (auto it : (*pVEC))
	{
		LineMapLink *pLink = (LineMapLink*)it.get();
		auto findIt = m_mLineMapLink.find(pLink->nItemType);
		if (findIt != m_mLineMapLink.end())
		{
			QMatrix4x4 matrix;
			matrix.ortho(0, m_nWidth, m_nHeight, 0, -1, 1);
			matrix.translate(pLink->nPosX- (m_nCellSize/2),pLink->nPosY- (m_nCellSize/2));
			
			bool bUnused = false;
			if (!m_unusedLines.isEmpty())
			{
				for (auto a : m_unusedLines)
				{
					if (pLink->m_nTableIndex == a->m_nTableIndex)
					{
						bUnused = true;
						break;
					}
				}
				if (!bUnused)
				{
					glUniform4f(m_uScrColor, (((pPool->uLineColor) & 0xFF)) / 255.0f,
						(((pPool->uLineColor >> 8) & 0xFF)) / 255.0f,
						(((pPool->uLineColor >> 16) & 0xFF)) / 255.0f,
						(((pPool->uLineColor >> 24) & 0xFF)) / 255.0f);
				}
				else
				{
					// set Unused line color!!!!!!
					glUniform4f(m_uScrColor, 0.1, 0.1, 0.1, 1.0);
				}
			}
			else
			{
				glUniform4f(m_uScrColor, (((pPool->uLineColor) & 0xFF)) / 255.0f,
					(((pPool->uLineColor >> 8) & 0xFF)) / 255.0f,
					(((pPool->uLineColor >> 16) & 0xFF)) / 255.0f,
					(((pPool->uLineColor >> 24) & 0xFF)) / 255.0f);
			}

			glUniformMatrix4fv(m_uScrMatrix, 1, false, (const GLfloat*)&matrix);
			for (auto subit : findIt->second->vIdxList)
			{
				findIt->second->SetOrigin(5);
				glBindTexture(GL_TEXTURE_2D, subit.nTextureIndex);
				glDrawElements(GL_TRIANGLES, subit.iCount, GL_UNSIGNED_SHORT, (const void*)(subit.iOffset * sizeof(GLushort)));
			}
		}
	}
	
	paintStationRelated();
	paintDisplayItems();
	glDisableVertexAttribArray(m_aScrTexCoord);
	glDisableVertexAttribArray(m_aScrPos);


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
	auto pLMT = pDM->GET_MODEL_CLASS(LineMapArrowTexture)->getVector();
	for (auto it : (*pLMT))
	{
		auto pLMAT = (LineMapArrowTexture *)it.get();
		auto findIt=m_mArrow.find(pLMAT->GetIndex());
		if (findIt != m_mArrow.end())
		{
			QMatrix4x4 matrix;
			matrix.ortho(0, m_nWidth, m_nHeight, 0, -1, 1);
			matrix.translate(findIt->second->m_fOrigin[0] + (GLfloat)pLMAT->nOffsetX, findIt->second->m_fOrigin[1] + (GLfloat)pLMAT->nOffsetY);
			glUniform4f(m_uArrowColor, 1.0, 0.0, 1.0, 1.0);
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

	glDisableVertexAttribArray(m_aArrowTexCoord);
	glDisableVertexAttribArray(m_aArrowPos);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	if (!lineProgram.bind())
		close();
	paintDisplayItemsPoolRect();
}


void QGLESLineMapCanvas::prepareArrow(int nWidth,int nHeight)
{
	GLuint uPreFrameBuffer = 0;
	if (!lineProgram.bind())
		close();
	glEnableVertexAttribArray(m_aLinePos);
	auto *pDM = CDataManage::GetInstance();
	auto pLMT = pDM->GET_MODEL_CLASS(LineMapArrowTexture)->getVector();
	for (auto it : (*pLMT))
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
					glClear(GL_COLOR_BUFFER_BIT);
					// 화살표 설정 완료 후 백그라운드 칼라 변경안되게 주석처리
					//glClearColor(0.0, 0.0, 0.0, 0.0); // 0 0 0 0 original, jkc
					glBindBuffer(GL_ARRAY_BUFFER, m_uVBOsID[2]);
					glVertexAttribPointer(m_aLinePos, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
					QMatrix4x4 matrix;
					matrix.ortho(0, nWidth, nHeight, 0, -1, 1);
					glUniformMatrix4fv(m_uLineMatrix, 1, false, (const GLfloat*)&matrix);
					uPreFrameBuffer = xit.uFrameBufferIdx;
				}
				glUniform4f(m_uLineColor, 0.0, 0.0, 1.0, 1.0);
				glDrawArrays(GL_TRIANGLE_STRIP, xit.iOffsetVtx, xit.iCountVtx);
			}
		}
		else
		{
			setArrowTexture(pLMAT, vVertices, vIndices, vVerticesArrow, 1024, 1024, 4);
			auto findIt = m_mArrow.find(pLMAT->GetIndex());
			if (findIt != m_mArrow.end())
			{
				for (auto xit : findIt->second->vIdxList)
				{
					if (uPreFrameBuffer != xit.uFrameBufferIdx)
					{
						glBindFramebuffer(GL_FRAMEBUFFER, xit.uFrameBufferIdx);
						glViewport(0, 0, nWidth, nHeight);
						glClear(GL_COLOR_BUFFER_BIT);
						glClearColor(0.0, 0.0, 0.0, 0.0);
						glBindBuffer(GL_ARRAY_BUFFER, m_uVBOsID[2]);
						glVertexAttribPointer(m_aLinePos, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
						QMatrix4x4 matrix;
						matrix.ortho(0, nWidth, nHeight, 0, -1, 1);
						glUniformMatrix4fv(m_uLineMatrix, 1, false, (const GLfloat*)&matrix);
						uPreFrameBuffer = xit.uFrameBufferIdx;
					}
					glUniform4f(m_uLineColor, 0.0, 0.0, 1.0, 1.0);
					glDrawArrays(GL_TRIANGLE_STRIP, xit.iOffsetVtx, xit.iCountVtx);
				}
			}
		}
	}
	glDisableVertexAttribArray(m_aLinePos);
}









void QGLESLineMapCanvas::timerEvent(QTimerEvent *e)
{
}



void QGLESLineMapCanvas::initShaders()
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

	if (!scrProgram.addShaderFromSourceCode(QOpenGLShader::Vertex, vShaderStr))
		close();

	if (!scrProgram.addShaderFromSourceCode(QOpenGLShader::Fragment, fShaderStr))
		close();

	if (!scrProgram.link())
		close();

	m_aScrPos = scrProgram.attributeLocation("a_position");
	m_aScrTexCoord = scrProgram.attributeLocation("a_texcoord");
	m_uScrMatrix = scrProgram.uniformLocation("u_matrix");
	m_uScrFirstTex = scrProgram.uniformLocation("firstTex");
	m_uScrColor = scrProgram.uniformLocation("u_color");

}
void QGLESLineMapCanvas::initShadersForLine()
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

	if (!lineProgram.addShaderFromSourceCode(QOpenGLShader::Fragment, fShaderStr))
		close();

	if (!lineProgram.link())
		close();

	m_aLinePos = lineProgram.attributeLocation("a_position");
	m_uLineMatrix = lineProgram.uniformLocation("u_matrix");
	m_uLineColor = lineProgram.uniformLocation("u_color");
}

void QGLESLineMapCanvas::initshadersForArrow()
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

void QGLESLineMapCanvas::setCurrentEditMode(int nMode)
{
	m_eEditMode = nMode;
	m_uArrowNode[0] = m_uArrowNode[1] = 0;
	update();
}


void QGLESLineMapCanvas::initBaseData(int nMapIndex)
{
	auto *pTM = CTableManage::GetInstance();
	auto bitmapCheck = [](unsigned char *pSoc, int nLeftSoc, int nTopSoc, int nRightSoc, int nBottomSoc, int nStrideSoc, int nBytesPerPixel)->bool
	{
		int nHeightSocCnt = nBottomSoc - nTopSoc;
		int nWidthSocCnt = nRightSoc - nLeftSoc;
		bool bEmpty = false;
		std::shared_ptr<unsigned char> pChar = std::shared_ptr<unsigned char>((unsigned char*)calloc(nStrideSoc, 1), free);
		for (int i = 0; i < nHeightSocCnt; i++)
		{
			unsigned char *pSocBase = (unsigned char*)(pSoc + (i*nStrideSoc) + (nLeftSoc * nBytesPerPixel));
			bool bTempEmpty = memcmp(pSocBase, pChar.get(), nWidthSocCnt*nBytesPerPixel);
			if (nBytesPerPixel == 4)
			{
				unsigned int uValue = 0;
				unsigned int *pSocBase4 = (unsigned int*)pSocBase;
				for (int j = 0; j < nWidthSocCnt; j++)
				{
					uValue = pSocBase4[j];
					unsigned char uAlpha = ((uValue & 0xff000000) >> 24);
					if (!uAlpha)
					{
						*(pSocBase4 + j) = 0x00ffffff;
					}
					else
					{
						uValue = (((unsigned int)uAlpha) << 24) | (0x00ffffff);
					}
				}
			}
			bEmpty |= bTempEmpty;
		}
		return bEmpty;
	};

	auto bitmapCopy = [](unsigned char *pSoc, int nLeftSoc, int nTopSoc, int nRightSoc, int nBottomSoc, int nStrideSoc,
		unsigned char *pDes, int nLeftDes, int nTopDes, int nWidthDes, int nHeightDes, int nStrideDes, int nBytesPerPixel)
	{
		int nHeightSocCnt = nBottomSoc - nTopSoc;
		int nHeightDesCnt = nHeightDes - nTopDes;
		int nWidthSocCnt = nRightSoc - nLeftSoc;
		int nWidthDesCnt = nWidthDes - nLeftDes;
		int nHeightLimit = (nHeightSocCnt >= nHeightDesCnt) ? nHeightDesCnt : nHeightSocCnt;
		int nWidthLimit = (nWidthSocCnt >= nWidthDesCnt) ? nWidthDesCnt : nWidthSocCnt;
		int nSocHeightCnt = nTopSoc;
		int nDesHeightCnt = nTopDes;
		for (int i = 0; i < nHeightLimit; i++)
		{
			unsigned char *pSocBase = (unsigned char*)(pSoc + ((nSocHeightCnt++)*nStrideSoc) + (nLeftSoc * nBytesPerPixel));
			unsigned char *pDesBase = (unsigned char*)(pDes + ((nDesHeightCnt++)*nStrideDes) + (nLeftDes * nBytesPerPixel));
			memcpy(pDesBase, pSocBase, nWidthLimit*nBytesPerPixel);
		}
	};


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
			pFloatU[2] = std::max(pFloatL[2], pFloatR[2]);
			pFloatU[3] = std::max(pFloatL[3], pFloatR[3]);
			pFloatU[0] = std::min(pFloatL[0], pFloatR[0]);
			pFloatU[1] = std::min(pFloatL[1], pFloatR[1]);
		}
		else
			bRet = false;
		return bRet;
	};



	typedef struct _tagTEXTURE
	{
		bool bDestIdx;
		GLint nWidth;
		GLint nHeight;
		GLint nStride;
		GLint nParentMap;
		GLint nItemType;
		GLint nRegisterIndex;
		GLubyte *pBuffer;
		GLuint uSocTexIdx;
		GLuint uDesTexIdx;
	}TextureOrig;

	std::vector<TextureOrig> vTexture;

	int nTextureRegisterIndex = 1;
	int nWidthLimit = 1024, nHeightLimit = 1024;
	int nBytesPerPixel = 4;
	int nBytesPerLine = nWidthLimit * nBytesPerPixel;
	std::vector<std::shared_ptr<unsigned char>> vBuffers;
	int nMaxHeight = 0;
	int nCurX = 0;
	int nCurY = 0;
	int nCurMaxHeight = 0;
	int nVertexOrder = 0;


	LineMapPool *pPool = (LineMapPool*)pTM->m_vLineMapPool.at(nMapIndex).get();
	m_nCellSize = pPool->nProp;
	m_nLineWidth = pPool->nWidth;
	TextureOrig tTexture = { false,pPool->nWidth,pPool->nWidth, pPool->nWidth*nBytesPerPixel,pPool->GetIndex(),0,nTextureRegisterIndex++,(GLubyte*)pPool->pByteSpot.get() };
	if (bitmapCheck(tTexture.pBuffer, 0, 0, tTexture.nWidth, tTexture.nHeight, tTexture.nStride, nBytesPerPixel))
		vTexture.push_back(tTexture);

	int nLoopCount = pPool->nSize / (pPool->nProp*pPool->nProp*nBytesPerPixel);
	for (int i = 0; i < nLoopCount; i++)
	{
		unsigned char *pBuf = (unsigned char*)pPool->pByte.get() + pPool->nProp*nBytesPerPixel*i;
		TextureOrig tTexture = { false,pPool->nProp,pPool->nProp, pPool->nProp*nBytesPerPixel*nLoopCount,pPool->GetIndex(),i,nTextureRegisterIndex++,(GLubyte*)(pPool->pByte.get() + pPool->nProp*nBytesPerPixel*i) };
		if (bitmapCheck(tTexture.pBuffer, 0, 0, tTexture.nWidth, tTexture.nHeight, tTexture.nStride, nBytesPerPixel))
			vTexture.push_back(tTexture);
	}


	glGenBuffers(3, m_uVBOsID);	//Creating Vertex Buffer Object
	glBindBuffer(GL_ARRAY_BUFFER, m_uVBOsID[0]);
	glBufferData(GL_ARRAY_BUFFER, 100000 * sizeof(GLfloat), 0, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uVBOsID[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 100000 * sizeof(GLushort), 0, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_uVBOsID[2]);
	glBufferData(GL_ARRAY_BUFFER, 100000 * sizeof(GLfloat), 0, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	std::for_each(pTM->m_vStationImagePool.begin(), pTM->m_vStationImagePool.end(), [bitmapCheck, &vTexture, &nTextureRegisterIndex, &nVertexOrder, &nCurMaxHeight, &nWidthLimit, &nHeightLimit, &nBytesPerLine, &nBytesPerPixel, &nCurX, &nCurY, &nMaxHeight](std::shared_ptr<CSQLData> &pData)
	{
		StationImagePool *pPool = (StationImagePool*)pData.get();
		TextureOrig tTexture = { false, pPool->nWidth,pPool->nHeight,pPool->nWidth*nBytesPerPixel,0,0, pPool->nTextureIndex = nTextureRegisterIndex++,(GLubyte*)pPool->pByte.get() };
		if (bitmapCheck(tTexture.pBuffer, 0, 0, tTexture.nWidth, tTexture.nHeight, tTexture.nStride, nBytesPerPixel))
			vTexture.push_back(tTexture);
	});

	std::for_each(pTM->m_vBitmapImagePool.begin(), pTM->m_vBitmapImagePool.end(), [bitmapCheck, &vTexture, &nTextureRegisterIndex, &nVertexOrder, &nCurMaxHeight, &nWidthLimit, &nHeightLimit, &nBytesPerLine, &nBytesPerPixel, &nCurX, &nCurY, &nMaxHeight](std::shared_ptr<CSQLData> &pData)
	{
		BitmapImagePool *pPool = (BitmapImagePool*)pData.get();
		TextureOrig tTexture = { false, pPool->nWidth,pPool->nHeight,pPool->nWidth*nBytesPerPixel,0,0, pPool->nTextureIndex = nTextureRegisterIndex++,(GLubyte*)pPool->pByte.get() };
		if (bitmapCheck(tTexture.pBuffer, 0, 0, tTexture.nWidth, tTexture.nHeight, tTexture.nStride, nBytesPerPixel))
			vTexture.push_back(tTexture);
	});

	CTextureInfo *pTI = CTextureInfo::GetInstance();
	pTI->ClearTextureInfo();
	vBinPacked.clear();
	vBinPackedDest.clear();

	vBinPacked.push_back(std::shared_ptr<MaxRectsPixelBuffer>(new MaxRectsPixelBuffer(nWidthLimit, nHeightLimit, nBytesPerPixel, false, false)));
	//비트맵 복사 부분
	for (auto tex : vTexture)
	{
		bool bTextureCopied = false;
		CTextureInfo* pTI = CTextureInfo::GetInstance();
		std::vector<std::shared_ptr<MaxRectsPixelBuffer>> *pDestVector = (tex.bDestIdx) ? &vBinPackedDest : &vBinPacked;
		for (auto it = pDestVector->begin(); it != pDestVector->end(); it++)
		{
			rbp::MaxRectsBinPack::FreeRectChoiceHeuristic heuristic = rbp::MaxRectsBinPack::RectBestShortSideFit;
			rbp::Rect packedRect = (*it)->Insert(tex.nWidth, tex.nHeight, heuristic);
			if ((packedRect.height > 0) && (packedRect.width > 0))
			{
				if ((packedRect.width == tex.nWidth) && (packedRect.height == tex.nHeight))
				{
					bTextureCopied = true;

					bitmapCopy(tex.pBuffer, 0, 0, tex.nWidth, tex.nHeight, tex.nStride, (*it)->GetBuffer(), packedRect.x, packedRect.y, nWidthLimit, nHeightLimit, nBytesPerLine, nBytesPerPixel);
					pTI->AddTextureInformation(tex.nParentMap, tex.nItemType, tex.nRegisterIndex, it->get()->Get1StTextureIdx(), tex.nWidth, tex.nHeight
						, ((GLfloat)packedRect.x + (GLfloat)0.5f) / (GLfloat)(nWidthLimit)
						, ((GLfloat)packedRect.y + (GLfloat)0.5f) / (GLfloat)(nHeightLimit)
						, ((GLfloat)(packedRect.x + packedRect.width) - (GLfloat)0.5f) / (GLfloat)(nWidthLimit)
						, ((GLfloat)(packedRect.y + packedRect.height) - (GLfloat)0.5f) / (GLfloat)(nHeightLimit), it->get()->Get2ndTextureIdx(), it->get()->GetFrameBufferIdx(), (GLfloat)packedRect.x, (GLfloat)packedRect.y);
				}
				break;
			}
		}
		if (!bTextureCopied)
		{
			rbp::MaxRectsBinPack::FreeRectChoiceHeuristic heuristic = rbp::MaxRectsBinPack::RectBestShortSideFit;
			pDestVector->push_back(std::shared_ptr<MaxRectsPixelBuffer>(new MaxRectsPixelBuffer(nWidthLimit, nHeightLimit, nBytesPerPixel, tex.bDestIdx, false)));
			rbp::Rect packedRect = pDestVector->rbegin()->get()->Insert(tex.nWidth, tex.nHeight, heuristic);
			if ((packedRect.height > 0) && (packedRect.width > 0))
			{
				if ((packedRect.width == tex.nWidth) && (packedRect.height == tex.nHeight))
				{
					bTextureCopied = true;
					bitmapCopy(tex.pBuffer, 0, 0, tex.nWidth, tex.nHeight, tex.nStride, vBinPacked.rbegin()->get()->GetBuffer(), packedRect.x, packedRect.y, nWidthLimit, nHeightLimit, nBytesPerLine, nBytesPerPixel);
					pTI->AddTextureInformation(tex.nParentMap, tex.nItemType, tex.nRegisterIndex, pDestVector->rbegin()->get()->Get1StTextureIdx(), tex.nWidth, tex.nHeight
						, ((GLfloat)packedRect.x + (GLfloat)0.5f) / (GLfloat)(nWidthLimit)
						, ((GLfloat)packedRect.y + (GLfloat)0.5f) / (GLfloat)(nHeightLimit)
						, ((GLfloat)(packedRect.x + packedRect.width) - (GLfloat)0.5f) / (GLfloat)(nWidthLimit)
						, ((GLfloat)(packedRect.y + packedRect.height) - (GLfloat)0.5f) / (GLfloat)(nHeightLimit), pDestVector->rbegin()->get()->Get2ndTextureIdx(), pDestVector->rbegin()->get()->GetFrameBufferIdx(), (GLfloat)packedRect.x, (GLfloat)packedRect.y);
				}
			}
		}
	}
	m_mImageList.clear();
	for (auto pData : pTM->m_vImageIndexList)
	{
		ImageIndexList *pIIL = (ImageIndexList*)pData.get();
		memset(pIIL->fRect, 0, sizeof(pIIL->fRect));
		std::for_each(pData.get()->m_vChildItem[0].vSQLData.begin(), pData.get()->m_vChildItem[0].vSQLData.end(), [pIIL, unitedRect](std::shared_ptr<CSQLData> &pData)
		{
			int nImageIndex = 0;
			ImageIndex *pII = (ImageIndex*)pData.get();
			auto *pTM = CTableManage::GetInstance();
			switch (pII->nType)
			{
			case 1:
				nImageIndex = pII->nStationNameBitmapIndex;
				{
					auto it = find_if(pTM->m_vStationImagePool.begin(), pTM->m_vStationImagePool.end(), [&nImageIndex](std::shared_ptr<CSQLData> &pData) {return nImageIndex == pData.get()->GetIndex(); });
					if (it != pTM->m_vStationImagePool.end())
					{
						StationImagePool *pSIP = (StationImagePool*)it->get();
						if (pSIP->nDataLength&&pSIP->pByte.get())
						{
							GLfloat fL[4] = { (GLfloat)pII->nXPos,(GLfloat)pII->nYPos,(GLfloat)(pII->nXPos + pSIP->nWidth),(GLfloat)(pII->nYPos + pSIP->nHeight) };
							unitedRect(pIIL->fRect, fL, pIIL->fRect);
						}
					}
				}
				break;
			case 2:
				nImageIndex = pII->nStationBitmapIndex;
				{
					auto it = find_if(pTM->m_vBitmapImagePool.begin(), pTM->m_vBitmapImagePool.end(), [&nImageIndex](std::shared_ptr<CSQLData> &pData) {return nImageIndex == pData.get()->GetIndex(); });
					if (it != pTM->m_vBitmapImagePool.end())
					{
						BitmapImagePool *pSIP = (BitmapImagePool*)it->get();
						if (pSIP->nDataLength&&pSIP->pByte.get())
						{
							GLfloat fL[4] = { (GLfloat)pII->nXPos,(GLfloat)pII->nYPos,(GLfloat)(pII->nXPos + pSIP->nWidth),(GLfloat)(pII->nYPos + pSIP->nHeight) };
							unitedRect(pIIL->fRect, fL, pIIL->fRect);
						}
					}
				}
				break;
			}
		});
	}

	m_mLineMapLink.clear();


	for (GLuint i = 0; i < nLoopCount; i++)
	{
		int nRegisteredIndex = pTI->GetTextureIndex(pPool->GetIndex(), i);
		if (nRegisteredIndex)
		{
			GLsizei nCount, nOffset;
			GLint nTexIndex;
			if (pTI->GetTextureInfo(nRegisteredIndex, vVertices, vIndices, 0, 0, &nCount, &nOffset, &nTexIndex))
			{
				auto itFind = m_mLineMapLink.find(i);
				if (itFind != m_mLineMapLink.end())
				{
					itFind->second.get()->AddIndex(nTexIndex, nCount, nOffset);
				}
				else
				{
					std::shared_ptr<CTexPool> pTP = std::shared_ptr<CTexPool>(new CTexPool((GLfloat)0, (GLfloat)0, (GLfloat)pPool->nProp, (GLfloat)pPool->nProp));
					pTP->AddIndex(nTexIndex, nCount, nOffset);
					m_mLineMapLink[i] = pTP;
				}
			}
		}
	}




	for (auto pData : pTM->m_vImageIndexList)
	{
		ImageIndexList *pIIL = (ImageIndexList*)pData.get();
		for (auto il : pData->m_vChildItem[0].vSQLData)
		{
			ImageIndex *pII = (ImageIndex*)(il.get());
			int nKey = pIIL->GetIndex();
			GLsizei nCount, nOffset;
			GLint nTexIndex;
			switch (pII->nType)
			{
			case 1:
			{
				int nImageIndex = pII->nStationNameBitmapIndex;
				auto it = find_if(pTM->m_vStationImagePool.begin(), pTM->m_vStationImagePool.end(), [&nImageIndex](std::shared_ptr<CSQLData> &pData) {return nImageIndex == pData.get()->GetIndex(); });
				if (it != pTM->m_vStationImagePool.end())
				{
					StationImagePool *pSIP = (StationImagePool*)it->get();
					if (pSIP->nDataLength&&pSIP->pByte.get())
					{
						if (pTI->GetTextureInfo(pSIP->nTextureIndex, vVertices, vIndices, pII->nXPos, pII->nYPos, &nCount, &nOffset, &nTexIndex))
						{
							auto itFind = m_mImageList.find(nKey);
							if (itFind != m_mImageList.end())
							{
								itFind->second.get()->AddIndex(nTexIndex, nCount, nOffset);
							}
							else
							{
								std::shared_ptr<CTexPool> pTP = std::shared_ptr<CTexPool>(new CTexPool((GLfloat)pIIL->fRect[0], (GLfloat)pIIL->fRect[1], (GLfloat)pIIL->fRect[2], (GLfloat)pIIL->fRect[3]));
								pTP->AddIndex(nTexIndex, nCount, nOffset);
								m_mImageList[nKey] = pTP;
							}
						}
					}
				}
			}
			break;
			case 2:
			{
				int nImageIndex = pII->nStationBitmapIndex;
				auto it = find_if(pTM->m_vBitmapImagePool.begin(), pTM->m_vBitmapImagePool.end(), [&nImageIndex](std::shared_ptr<CSQLData> &pData) {return nImageIndex == pData.get()->GetIndex(); });
				if (it != pTM->m_vBitmapImagePool.end())
				{
					BitmapImagePool *pSIP = (BitmapImagePool*)it->get();
					if (pSIP->nDataLength&&pSIP->pByte.get())
					{
						if (pTI->GetTextureInfo(pSIP->nTextureIndex, vVertices, vIndices, pII->nXPos, pII->nYPos, &nCount, &nOffset, &nTexIndex))
						{
							auto itFind = m_mImageList.find(nKey);
							if (itFind != m_mImageList.end())
							{
								itFind->second.get()->AddIndex(nTexIndex, nCount, nOffset);
							}
							else
							{
								std::shared_ptr<CTexPool> pTP = std::shared_ptr<CTexPool>(new CTexPool((GLfloat)pIIL->fRect[0], (GLfloat)pIIL->fRect[1], (GLfloat)pIIL->fRect[2], (GLfloat)pIIL->fRect[3]));
								pTP->AddIndex(nTexIndex, nCount, nOffset);
								m_mImageList[nKey] = pTP;
							}
						}
					}
				}
			}
			break;
			}
		}
	}


	GLsizei nCount, nOffset;
	GLint nTexIndex;
	if (pTI->GetTextureInfo(1, vVertices, vIndices, 0, 0, &nCount, &nOffset, &nTexIndex))
	{
		m_tStationSpot=std::shared_ptr<CTexPool>(new CTexPool((GLfloat)0, (GLfloat)0, (GLfloat)m_nLineWidth, (GLfloat)m_nLineWidth));
		m_tStationSpot->AddIndex(nTexIndex, nCount, nOffset);
	}



	for (auto i : vBinPacked)
	{
		i->Sync1StTextureBuffer();
		//i->Init2ndTextureBuffer();
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_uVBOsID[0]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vVertices.size() * sizeof(GLfloat), &vVertices[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uVBOsID[1]);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, vIndices.size() * sizeof(GLfloat), &vIndices[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	auto pDM = CDataManage::GetInstance();
	for (auto it : (*pDM->GET_MODEL_CLASS(LineMapArrowTexture)->getVector()))
	{
		LineMapArrowTexture *pLMAT = (LineMapArrowTexture*)it.get();
		setArrowTexture(pLMAT,vVertices, vIndices, vVerticesArrow, nWidthLimit, nHeightLimit, nBytesPerPixel);
	}

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
}

void QGLESLineMapCanvas::setArrowTexture(LineMapArrowTexture *pLMAT, std::vector<GLfloat> &vVertex, std::vector<GLushort> &vIndices, std::vector<GLfloat> &vVertexArrow, int nWholeWidth,int nWholeHeight,int nBytesPerPixel)
{
	bool bTextureCopied=false;
	GLsizei iOffset, iCount;
	GLsizei iOffsetVtx, iCountVtx;
	CTextureInfo* pTI = CTextureInfo::GetInstance();
	pTI->SetOpenGLFunctions(this);
	for (auto it : vBinPackedDest )
	{
		rbp::MaxRectsBinPack::FreeRectChoiceHeuristic heuristic = rbp::MaxRectsBinPack::RectBestShortSideFit;
		rbp::Rect packedRect = it->Insert(pLMAT->nTexWidth, pLMAT->nTexHeight, heuristic);
		if ((packedRect.height > 0) && (packedRect.width > 0))
		{
			if ((packedRect.width == pLMAT->nTexWidth) && (packedRect.height == pLMAT->nTexHeight))
			{
				bTextureCopied = true;
				it->SetSubImage(packedRect.x, packedRect.y, packedRect.width, packedRect.height, pLMAT->pByte.get());
				std::shared_ptr<CTexPool> pTP = std::shared_ptr<CTexPool>(new CTexPool((GLfloat)0, (GLfloat)0, (GLfloat)packedRect.width, (GLfloat)packedRect.height));
				pTI->GetTextureInfo(vVertex, vIndices, packedRect.x, packedRect.y, packedRect.width, packedRect.height, (GLfloat)nWholeWidth, (GLfloat)nWholeHeight, 0.5, &iCount, &iOffset, m_uVBOsID[0], m_uVBOsID[1]);
				pTI->GetTextureInfo(vVertexArrow,(GLfloat) packedRect.x, (GLfloat)packedRect.y, (GLfloat*)pLMAT->pByteVertex.get(), pLMAT->nVtxBufSize/4, &iCountVtx, &iOffsetVtx, m_uVBOsID[2]);
				pTP->AddIndex(it->Get1StTextureIdx(), iCount, iOffset,it->Get2ndTextureIdx(), iCountVtx, iOffsetVtx,it->GetFrameBufferIdx());
				pTP->SetOrigin(1);
				m_mArrow[pLMAT->GetIndex()] = pTP;
			}
			break;
		}
	}
	if (!bTextureCopied)
	{
		rbp::MaxRectsBinPack::FreeRectChoiceHeuristic heuristic = rbp::MaxRectsBinPack::RectBestShortSideFit;
		vBinPackedDest.push_back(std::shared_ptr<MaxRectsPixelBuffer>(new MaxRectsPixelBuffer(nWholeWidth, nWholeHeight, nBytesPerPixel,true, false,true)));
		rbp::Rect packedRect = vBinPackedDest.rbegin()->get()->Insert(pLMAT->nTexWidth, pLMAT->nTexHeight, heuristic);
		if ((packedRect.height > 0) && (packedRect.width > 0))
		{
			if ((packedRect.width == pLMAT->nTexWidth) && (packedRect.height == pLMAT->nTexHeight))
			{
				bTextureCopied = true;
				(*vBinPackedDest.rbegin())->SetSubImage(packedRect.x,packedRect.y, packedRect.width, packedRect.height, pLMAT->pByte.get());
				std::shared_ptr<CTexPool> pTP = std::shared_ptr<CTexPool>(new CTexPool((GLfloat)0, (GLfloat)0, (GLfloat)packedRect.width, (GLfloat)packedRect.height));
				pTI->GetTextureInfo(vVertex, vIndices, packedRect.x, packedRect.y, packedRect.width, packedRect.height, (GLfloat)nWholeWidth, (GLfloat)nWholeHeight, 0.5, &iCount, &iOffset, m_uVBOsID[0], m_uVBOsID[1]);
				pTI->GetTextureInfo(vVertexArrow, (GLfloat)packedRect.x, (GLfloat)packedRect.y, (GLfloat*)pLMAT->pByteVertex.get(), pLMAT->nVtxBufSize/4, &iCountVtx, &iOffsetVtx, m_uVBOsID[2]);
				pTP->AddIndex((*vBinPackedDest.rbegin())->Get1StTextureIdx(), iCount, iOffset, (*vBinPackedDest.rbegin())->Get2ndTextureIdx(), iCountVtx, iOffsetVtx, (*vBinPackedDest.rbegin())->GetFrameBufferIdx());
				pTP->SetOrigin(1);
				m_mArrow[pLMAT->GetIndex()] = pTP;
			}
		}
	}
}



