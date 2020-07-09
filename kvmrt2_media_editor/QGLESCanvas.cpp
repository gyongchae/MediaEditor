#include "QGLESCanvas.h"
#include <QMouseEvent>
#include <algorithm>
#include "TableManage.h"
#include "DataManage.h"
#include "dataModel.h"
#include "TextureInformation/CTextureInfo.h"
#include "BinPacked/MaxRectsPixelBuffer.h"
#include "displayItemPropEdit.h"
#include "editDisplayMetaItem.h"
#include "TexPool.h"
#include <QAction>
#include <QMenu>
#include <qdebug.h>

QGLESPIDCanvas::QGLESPIDCanvas(QWidget *parent)
	: QOpenGLWidget(parent), m_fOffsetX(.0f), m_fOffsetY(.0f), m_nWidth(0), m_nHeight(0), m_nSelIdx(0), m_bSelected(false), m_nCurTime(0), 
	m_bMoving(false), m_pActDelItem(0), m_pActEditProp(0), m_pActDelProp(0), m_nLatestSelected(0), m_nLatestSelectedType(0),
	m_pMetaItemMenu(0),m_pMenu(0), m_bMousePressed(false), m_bMouseMovedWhilePressed(false)
{
	qDebug() << Q_FUNC_INFO;
	setAcceptDrops(true);
	initActions();
	setMouseTracking(true);
}

QGLESPIDCanvas::~QGLESPIDCanvas()
{
	glDeleteBuffers(2, m_uVBOsID);
}

void QGLESPIDCanvas::initializeGL()
{
	qDebug() << Q_FUNC_INFO;
	//m_bMoving = true;
	initializeOpenGLFunctions();
	glClearColor(0, 0, 0, 1);
	initShaders();
	initShadersForLine();
	initBaseData();
	initDisplayItem();
	initMetaDisplayItem();
	reorderAllTimeLine();
	//m_bMoving = false;
}

void QGLESPIDCanvas::initShaders()
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
		"varying vec2 v_texcoord;\n"
		"uniform vec4 u_color;\n"
		"uniform sampler2D firstTex;\n"
		"void main()\n"
		"{\n"
		"gl_FragColor =  texture2D(firstTex, v_texcoord)*u_color;\n"
		"}\n";

	if (!program.addShaderFromSourceCode(QOpenGLShader::Vertex, vShaderStr))
	{
		qDebug() << Q_FUNC_INFO << "vertex error";
		//close();
	}

	// Compile fragment shader
	if (!program.addShaderFromSourceCode(QOpenGLShader::Fragment, fShaderStr))
	{
		qDebug() << Q_FUNC_INFO << "frag error!";
		//close();
	}

	// Link shader pipeline
	if (!program.link())
	{
		qDebug() << Q_FUNC_INFO << "link error!";
		//close();
	}

	m_uPosScrLoc = program.attributeLocation("a_position");
	m_uTexCoordScrLoc = program.attributeLocation("a_texcoord");
	m_uMatrixLoc = program.uniformLocation("u_matrix");
	m_nFirstTex = program.uniformLocation("firstTex");
	m_uColorLoc = program.uniformLocation("u_color");
}

void QGLESPIDCanvas::initShadersForLine()
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
	{
		qDebug() << Q_FUNC_INFO << "vertex error";
		//close();
	}

	// Compile fragment shader
	if (!lineProgram.addShaderFromSourceCode(QOpenGLShader::Fragment, fShaderStr))
	{
		qDebug() << Q_FUNC_INFO << "frag error";
		//close();
	}

	// Link shader pipeline
	if (!lineProgram.link())
	{
		qDebug() << Q_FUNC_INFO << "link error";
		//close();
	}

	m_uPosLineLoc = lineProgram.attributeLocation("a_position");
	m_uMatrixLineLoc = lineProgram.uniformLocation("u_matrix");
	m_uColorLineLoc = lineProgram.uniformLocation("u_color");
}

void QGLESPIDCanvas::initDisplayItem()
{
	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();
	auto pVEC = pDM->GET_MODEL_CLASS(DisplayItem).get()->getVector();
	for (auto it : (*pVEC))
	{
		DisplayItem *pItem = (DisplayItem*)it.get();
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
}


void QGLESPIDCanvas::initMetaDisplayItem()
{
	auto *pDM = CDataManage::GetInstance();
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
	}
}

void QGLESPIDCanvas::paintGL()
{
	qDebug() << Q_FUNC_INFO;
	//QMatrix4x4 matrix, tempMatrix;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	// Set the viewport
	glViewport(0, 0, m_nWidth, m_nHeight);
	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Use the program object

	glClearColor(0.8f, 0.8f, 0.8f, 0.0f);

	// Bind shader pipeline for use
	if (!program.bind())
		close();

	glEnableVertexAttribArray(m_uPosScrLoc);
	glEnableVertexAttribArray(m_uTexCoordScrLoc);
	glBindBuffer(GL_ARRAY_BUFFER, m_uVBOsID[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uVBOsID[1]);
	glVertexAttribPointer(m_uPosScrLoc, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glVertexAttribPointer(m_uTexCoordScrLoc, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (const void*)(2 * sizeof(GLfloat)));
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(m_nFirstTex, 0);

	auto *pDM = CDataManage::GetInstance();
	auto pVEC = pDM->GET_MODEL_CLASS(DisplayItem).get()->getVector();
	auto pMVEC = pDM->GET_MODEL_CLASS(DisplayMetaItem).get()->getVector();

	for (auto it : (*pVEC))
	{
		DisplayItem *pItem = (DisplayItem*)it.get();
		pItem->SetOrigin(pItem->nOrigin);
		if (!m_bMoving)
		{
			pItem->tLine.jumpTo(m_nCurTime);
		}
		if (pItem->m_nVisible)
		{
			auto findIt = m_mImageList.find(pItem->nRelatedBufferIndex);
			if (findIt != m_mImageList.end())
			{

				QMatrix4x4 matrix;
				findIt->second->SetOrigin(pItem->nOrigin, true);
				matrix.ortho(0, m_nWidth, m_nHeight, 0, -1, 1);
				matrix.translate(pItem->m_fTrans[0], pItem->m_fTrans[1]);
				matrix.rotate(pItem->m_fRotation, 0, 0, 1.0f);
				matrix.scale(pItem->m_fScale[0], pItem->m_fScale[1]);
				matrix.translate(pItem->fOrigX, pItem->fOrigY);
				glUniform4f(m_uColorLoc, pItem->m_fColor[3], pItem->m_fColor[2], pItem->m_fColor[1], pItem->m_fColor[0]);
				glUniformMatrix4fv(m_uMatrixLoc, 1, false, (const GLfloat*)&matrix);
				for (auto subit : findIt->second->vIdxList)
				{

					glBindTexture(GL_TEXTURE_2D, subit.nTextureIndex);
					glDrawElements(GL_TRIANGLES, subit.iCount, GL_UNSIGNED_SHORT, (const void*)(subit.iOffset * sizeof(GLushort)));
				}
			}
		}
	}


	for (auto it : (*pMVEC))
	{
		DisplayMetaItem *pItem = (DisplayMetaItem*)it.get();
		pItem->SetOrigin(pItem->nOrigin);
		if (!m_bMoving)
		{
			pItem->tLine.jumpTo(m_nCurTime);
		}
		auto findIt = m_mImageList.find(pItem->nRelatedIndex);
		if (findIt != m_mImageList.end())
		{
			QMatrix4x4 matrix;
			matrix.ortho(0, m_nWidth, m_nHeight, 0, -1, 1);
			matrix.translate(pItem->m_fTrans[0], pItem->m_fTrans[1]);
			matrix.rotate(pItem->m_fRotation, 0, 0, 1.0f);
			matrix.scale(pItem->m_fScale[0], pItem->m_fScale[1]);
			matrix.translate(pItem->fOrigX, pItem->fOrigY);

			matrix.translate(pItem->fOffsetX, pItem->fOffsetY);
			matrix.scale(pItem->fRatioX, pItem->fRatioY);

			glUniform4f(m_uColorLoc, pItem->m_fColor[3], pItem->m_fColor[2], pItem->m_fColor[1], pItem->m_fColor[0]);
			glUniformMatrix4fv(m_uMatrixLoc, 1, false, (const GLfloat*)&matrix);
			for (auto subit : findIt->second->vIdxList)
			{
				glBindTexture(GL_TEXTURE_2D, subit.nTextureIndex);
				glDrawElements(GL_TRIANGLES, subit.iCount, GL_UNSIGNED_SHORT, (const void*)(subit.iOffset * sizeof(GLushort)));
			}
		}
	}

	glDisableVertexAttribArray(m_uTexCoordScrLoc);
	glDisableVertexAttribArray(m_uPosScrLoc);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	if (!lineProgram.bind())
		close();
	glEnableVertexAttribArray(m_uPosLineLoc);

	//Boundary Rectangles

	for (auto it : (*pVEC))
	{
		DisplayItem *pItem = (DisplayItem*)it.get();
		if ((m_nLatestSelected == pItem->GetIndex()) && (m_nLatestSelectedType == 1))
			glUniform4f(m_uColorLineLoc, 1.0, 0.0, 0.0, 1.0);
		else
			glUniform4f(m_uColorLineLoc, 1.0, 1.0, 1.0, 1.0);

		QMatrix4x4 matrix;
		matrix.ortho(0, m_nWidth, m_nHeight, 0, -1, 1);
		matrix.translate(pItem->m_fTrans[0], pItem->m_fTrans[1], 0.1f);
		matrix.rotate(pItem->m_fRotation, 0, 0, 1.0f);
		matrix.scale(pItem->m_fScale[0], pItem->m_fScale[1]);
		matrix.translate(pItem->fOrigX, pItem->fOrigY);


		//matrix.translate(pItem->m_fOrigin[0], pItem->m_fOrigin[1]);
		glUniformMatrix4fv(m_uMatrixLoc, 1, false, (const GLfloat*)&matrix);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), pItem->m_fTempRect);
		glDrawArrays(GL_LINE_STRIP, 0, 5);
	}

	for (auto it : (*pMVEC))
	{
		DisplayMetaItem *pItem = (DisplayMetaItem*)it.get();
		pItem->SetOrigin(pItem->nOrigin);
		if (!m_bMoving)
		{
			pItem->tLine.jumpTo(m_nCurTime);
		}
		if ((m_nLatestSelected == pItem->GetIndex()) && (m_nLatestSelectedType == 2))
			glUniform4f(m_uColorLineLoc, 1.0, 0.0, 0.0, 1.0);
		else
			glUniform4f(m_uColorLineLoc, 1.0, 1.0, 1.0, 1.0);

		QMatrix4x4 matrix;
		matrix.ortho(0, m_nWidth, m_nHeight, 0, -1, 1);
		matrix.translate(pItem->m_fTrans[0], pItem->m_fTrans[1], 0.1f);
		matrix.rotate(pItem->m_fRotation, 0, 0, 1.0f);
		matrix.scale(pItem->m_fScale[0], pItem->m_fScale[1]);
		matrix.translate(pItem->fOrigX, pItem->fOrigY);
		//matrix.translate(pItem->m_fOrigin[0], pItem->m_fOrigin[1]);
		glUniformMatrix4fv(m_uMatrixLoc, 1, false, (const GLfloat*)&matrix);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), pItem->m_fTempRect);
		glDrawArrays(GL_LINE_STRIP, 0, 5);
	}
	
	glDisableVertexAttribArray(m_uPosLineLoc);
}

void QGLESPIDCanvas::initActions()
{
	auto *pDM = CDataManage::GetInstance();
	m_pActDelItem = new QAction(pDM->m_iconDelDispItem, "&Delete", this);
	m_pActEditProp = new QAction(pDM->m_iconEditProp, "&Property", this);
	m_pActDelProp = new QAction(pDM->m_iconRemoveProp, "&Remove Current Property",this);

	m_pMenu = new QMenu(this);
	m_pMenu->addAction(m_pActDelItem);
	m_pMenu->addAction(m_pActEditProp);
	m_pMenu->addAction(m_pActDelProp);
	

	connect(m_pActDelItem, SIGNAL(triggered()), this, SLOT(deleteItem()));
	connect(m_pActEditProp, SIGNAL(triggered()), this, SLOT(editProperties()));
	connect(m_pActDelProp, SIGNAL(triggered()), this, SLOT(delPropAtCurTime()));

	m_pAddMetaItem = new QAction(pDM->m_iconAddMeta, "&Add Meta Item", this);
	m_pDeleteMetaItem = new QAction(pDM->m_iconDelDispItem, "&Delete", this);
	m_pEditMetaItem = new QAction(pDM->m_iconEditProp, "&Property", this);
	m_pDelMetaProp = new QAction(pDM->m_iconRemoveProp, "&Remove Current Property", this);
	m_pAddMetaItem->setData(1);
	m_pDeleteMetaItem->setData(2);
	m_pEditMetaItem->setData(3);
	m_pDelMetaProp->setData(4);

	m_pMetaItemMenu = new QMenu(this);
	m_pMetaItemMenu->addAction(m_pAddMetaItem);
	m_pMetaItemMenu->addAction(m_pDeleteMetaItem);
	m_pMetaItemMenu->addAction(m_pEditMetaItem);
	m_pMetaItemMenu->addAction(m_pDelMetaProp);

	connect(m_pMetaItemMenu, SIGNAL(triggered(QAction*)), this, SLOT(selectMetaItemAction(QAction*)));
}


void QGLESPIDCanvas::setMetaItemOrientation(DisplayMetaItem *pItem)
{
	float fRatioX, fRatioY, fOffsetX, fOffsetY;
	auto findIt = m_mImageList.find(pItem->nRelatedIndex);
	if (findIt != m_mImageList.end())
	{
		if((!pItem->nLimit)||((float)pItem->nWidth > findIt->second->m_fRect[2]))
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
			pItem->fRatioY = (GLfloat)pItem->nHeight/(GLfloat)findIt->second->m_fRect[3];
		}
	}
}
void QGLESPIDCanvas::selectMetaItemAction(QAction *action)
{
	auto *pDM = CDataManage::GetInstance();
	int nValue = action->data().toInt();
	switch (nValue)
	{
	case 1:	//Add MetaItem
		{
			auto pInserted=pDM->GET_MODEL_CLASS(DisplayMetaItem)->insertRow();
			int nSubRow,nRow=pDM->GET_MODEL_CLASS(DisplayMetaItem)->rowCount()-1;
			auto pMI = (DisplayMetaItem*)pInserted.get();
			getMetaItemProperties((DisplayMetaItem*)pInserted.get(), &nSubRow, m_nMetaItemPosX, m_nMetaItemPosY);
			auto pProp = (DisplayMetaItemProp*)pMI->m_vChildItem[0].vSQLData.at(nSubRow).get();
			editDisplayMetaItem dialog(nRow, nSubRow,this);
			if (dialog.exec() != QDialog::Accepted)
			{
				pDM->GET_MODEL_CLASS(DisplayMetaItem)->removeRows(nRow, 1);
			}
			else
			{
				setSelectedItemVectors(pMI, 1);

				pMI->m_fRect[0] = 0;
				pMI->m_fRect[1] = 0;
				pMI->m_fRect[2] = (GLfloat)pMI->nWidth;
				pMI->m_fRect[3] = (GLfloat)pMI->nHeight;
				pMI->SetOrigin(pMI->nOrigin,true);
				pMI->m_fRotation= pProp->fAngle;
				setBoundRectangle(pMI);
				pMI->m_fRotation= pProp->fAngle;
				pProp->fScalingX = pMI->m_fScale[0];
				pProp->fScalingY = pMI->m_fScale[1];
				pProp->nVisible = pMI->m_nVisible;
				setMetaItemOrientation(pMI);
				CDataManage::reorderTimeLine(pMI);
				m_nSelIdx = 0;
				m_nSelMetaIdx = 0;
			}
		}
		break;
	case 2:	//Delete MetaItem
		pDM->GET_MODEL_CLASS(DisplayMetaItem)->removeRow(m_nSelMetaIdx);
		setSelectedItemVectors(0, 2);
		break;
	case 3:	//Edit MetaItem
		editMetaItemProperties();
		break;
	case 4:	//Edit Properties
		delMetaPropAtCurTime();
	}
	update();
}


int QGLESPIDCanvas::isPropExist()
{
	auto *pDM = CDataManage::GetInstance();
	auto pVEC = pDM->GET_MODEL_CLASS(DisplayItem).get()->getVector();
	int nSelectedItem = m_nSelIdx;
	auto it = find_if(pVEC->begin(), pVEC->end(), [&nSelectedItem](std::shared_ptr<CSQLData> &pData)
	{
		DisplayItem *pItem = (DisplayItem*)pData.get();
		return pItem->GetIndex() == nSelectedItem;
	});
	int nCurTime = m_nCurTime;
	if (it != pVEC->end())
	{
		pDM->GET_MODEL_CLASS(DisplayProp)->setVectors(&it->get()->m_vChildItem[0].vSQLData, &it->get()->m_vChildItem[0].vSQLDataDelItems, it->get()->GetIndex());
		auto subit = find_if(it->get()->m_vChildItem[0].vSQLData.begin(), it->get()->m_vChildItem[0].vSQLData.end(), [&nCurTime](std::shared_ptr<CSQLData> &pData)
		{
			DisplayProp *pProp = (DisplayProp*)pData.get();
			return (pProp->nAtMiliseconds == nCurTime);
		});
		if (subit != it->get()->m_vChildItem[0].vSQLData.end())
		{
			return subit->get()->GetIndex();
		}
	}
	return 0;
}

int QGLESPIDCanvas::isMetaPropExist()
{
	auto *pDM = CDataManage::GetInstance();
	auto pVEC = pDM->GET_MODEL_CLASS(DisplayMetaItem).get()->getVector();
	int nSelectedItem = m_nSelMetaIdx;
	auto it = find_if(pVEC->begin(), pVEC->end(), [&nSelectedItem](std::shared_ptr<CSQLData> &pData)
	{
		DisplayMetaItem *pItem = (DisplayMetaItem*)pData.get();
		return pItem->GetIndex() == nSelectedItem;
	});
	int nCurTime = m_nCurTime;
	if (it != pVEC->end())
	{
		pDM->GET_MODEL_CLASS(DisplayMetaItemProp)->setVectors(&it->get()->m_vChildItem[0].vSQLData, &it->get()->m_vChildItem[0].vSQLDataDelItems, it->get()->GetIndex());
		auto subit = find_if(it->get()->m_vChildItem[0].vSQLData.begin(), it->get()->m_vChildItem[0].vSQLData.end(), [&nCurTime](std::shared_ptr<CSQLData> &pData)
		{
			DisplayMetaItemProp *pProp = (DisplayMetaItemProp*)pData.get();
			return (pProp->nAtMiliseconds == nCurTime);
		});
		if (subit != it->get()->m_vChildItem[0].vSQLData.end())
		{
			return subit->get()->GetIndex();
		}
	}
	return 0;
}

void QGLESPIDCanvas::delPropAtCurTime()
{
	auto *pDM = CDataManage::GetInstance();
	int nIndex = isPropExist();
	pDM->GET_MODEL_CLASS(DisplayProp)->removeRow(nIndex);
	auto pVEC = pDM->GET_MODEL_CLASS(DisplayItem).get()->getVector();
	auto findIt=find_if(pVEC->begin(), pVEC->end(), findSQLData(m_nSelIdx));
	if (findIt != pVEC->end())
	{
		setSelectedItemVectors((void *)findIt->get(), 0);
		CDataManage::reorderTimeLine((DisplayItem*)findIt->get());
	}
}


void QGLESPIDCanvas::delMetaPropAtCurTime()
{
	auto *pDM = CDataManage::GetInstance();
	int nIndex = isMetaPropExist();
	pDM->GET_MODEL_CLASS(DisplayMetaItemProp)->removeRow(nIndex);
	auto pVEC = pDM->GET_MODEL_CLASS(DisplayMetaItem).get()->getVector();
	auto findIt = find_if(pVEC->begin(), pVEC->end(), findSQLData(m_nSelMetaIdx));
	if (findIt != pVEC->end())
	{
		setSelectedItemVectors((void *)findIt->get(), 1);
		CDataManage::reorderTimeLine((DisplayMetaItem*)findIt->get());
	}
}


void QGLESPIDCanvas::getMetaItemProperties(DisplayMetaItem *pInserted,int *pPropertiesRow, int nX, int nY)
{
	int nCurTime = m_nCurTime;
	auto *pDM = CDataManage::GetInstance();
	auto subit = find_if(pInserted->m_vChildItem[0].vSQLData.begin(), pInserted->m_vChildItem[0].vSQLData.end(), [&nCurTime](std::shared_ptr<CSQLData> &pData)
	{
		DisplayMetaItemProp *pProp = (DisplayMetaItemProp*)pData.get();
		return (pProp->nAtMiliseconds == nCurTime);
	});
	if (subit != pInserted->m_vChildItem[0].vSQLData.end())
	{
		(*pPropertiesRow) = std::distance(pInserted->m_vChildItem[0].vSQLData.begin(), subit);
	}
	else
	{
		pDM->GET_MODEL_CLASS(DisplayMetaItemProp)->setVectors(&pInserted->m_vChildItem[0].vSQLData, &pInserted->m_vChildItem[0].vSQLDataDelItems, pInserted->GetIndex());
		auto pVEC = pDM->GET_MODEL_CLASS(DisplayMetaItemProp)->insertRow();
		DisplayMetaItemProp *pDMIP = (DisplayMetaItemProp*)pVEC.get();
		(*pPropertiesRow) = (pDM->GET_MODEL_CLASS(DisplayMetaItemProp)->rowCount()-1);
		pDMIP->nAtMiliseconds = nCurTime;
		setPropertiesFromMetaItem(pInserted, pDMIP, nX,nY);
	}
}

void QGLESPIDCanvas::addMetaItem()
{
	auto *pDM = CDataManage::GetInstance();
	update();
}

void QGLESPIDCanvas::deleteItem()
{
	auto *pDM = CDataManage::GetInstance();
	pDM->GET_MODEL_CLASS(DisplayItem)->removeRow(m_nSelIdx);
	setSelectedItemVectors(0, 2);
	update();
}

void QGLESPIDCanvas::editProperties()
{
	auto *pDM = CDataManage::GetInstance();
	auto pVEC = pDM->GET_MODEL_CLASS(DisplayItem).get()->getVector();
	int nSelectedItem = m_nSelIdx;
	int nRowItem=-1,nSubRowItem=-1;
	auto it = find_if(pVEC->begin(), pVEC->end(), [&nSelectedItem](std::shared_ptr<CSQLData> &pData)
	{
		DisplayItem *pItem = (DisplayItem*)pData.get();
		return pItem->GetIndex() == nSelectedItem;
	});
	int nCurTime = m_nCurTime;
	if (it != pVEC->end())
	{
		bool bNewlyAdded = false;
		nRowItem = std::distance(pVEC->begin(), it);
		pDM->GET_MODEL_CLASS(DisplayProp)->setVectors(&it->get()->m_vChildItem[0].vSQLData, &it->get()->m_vChildItem[0].vSQLDataDelItems, it->get()->GetIndex());
		auto subit = find_if(it->get()->m_vChildItem[0].vSQLData.begin(), it->get()->m_vChildItem[0].vSQLData.end(), [&nCurTime](std::shared_ptr<CSQLData> &pData)
		{
			DisplayProp *pProp = (DisplayProp*)pData.get();
			return (pProp->nAtMiliseconds == nCurTime);
		});
		if (subit != it->get()->m_vChildItem[0].vSQLData.end())
		{
			nSubRowItem = std::distance(it->get()->m_vChildItem[0].vSQLData.begin(), subit);
		}
		else
		{
			bNewlyAdded = true;
			nSubRowItem = 0;
			auto tProp = pDM->GET_MODEL_CLASS(DisplayProp)->insertRows(0, 1);
		}
		auto pSubVEC=pDM->GET_MODEL_CLASS(DisplayProp)->getVector();
		DisplayItem *pItem = (DisplayItem*)it->get();
		DisplayProp *pProp=(DisplayProp*)pSubVEC->at(nSubRowItem).get();
		pProp->nAtMiliseconds = nCurTime;

		setPropertiesFromItem(pItem, pProp, pItem->m_fTrans[0], pItem->m_fTrans[1]);
	

		displayItemPropEdit tEdit(nRowItem, nSubRowItem, this);
		if ((tEdit.exec() != QDialog::Accepted))
		{
			if(bNewlyAdded)
				pDM->GET_MODEL_CLASS(DisplayProp)->removeRows(nSubRowItem, 1);
		}
		else
		{
			setSelectedItemVectors(pItem, 0);
			syncBounds(pItem, pProp);
			setBoundRectangle(pItem);
			pProp->nAtMiliseconds = m_nCurTime;
			(CDataManage::reorderTimeLine(pItem));
			setSelectedItemVectors(pItem, 0);
		}
		sortToZOrder();
	}
	m_nSelIdx = 0;
	m_nSelMetaIdx = 0;
}

void QGLESPIDCanvas::syncBounds(DisplayItem *pItem,DisplayProp *pProp)
{
	if (pItem->SetOrigin(pItem->nOrigin))
	{
		auto findIt = m_mImageList.find(pItem->nRelatedBufferIndex);
		if (findIt != m_mImageList.end())
		{
			GLfloat fPrevOriginX = findIt->second->m_fOrigin[0];
			GLfloat fPrevOriginY = findIt->second->m_fOrigin[1];
			if (findIt->second->SetOrigin(pItem->nOrigin,true))
			{
				pItem->fOrigX = findIt->second->m_fOrigin[0];
				pItem->fOrigY = findIt->second->m_fOrigin[1];
			}
			fPrevOriginX -= findIt->second->m_fOrigin[0];
			fPrevOriginY -= findIt->second->m_fOrigin[1];
			//Rotation and scaling
			QMatrix4x4 mat2;
			mat2.rotate(pItem->m_fRotation, 0, 0, 1.0f);
			mat2.scale(pItem->m_fScale[0], pItem->m_fScale[1]);
			QPointF tFloat2 = mat2.map(QPointF(fPrevOriginX, fPrevOriginY));	
			pProp->fX += tFloat2.x();
			pProp->fY += tFloat2.y();
		}
	}
}

void QGLESPIDCanvas::syncMetaItemBounds(DisplayMetaItem *pItem, DisplayMetaItemProp *pProp)
{
	GLfloat fPrevOriginX = pItem->fOrigX;
	GLfloat fPrevOriginY = pItem->fOrigY;
	if (pItem->SetOrigin(pItem->nOrigin, true))
	{
		fPrevOriginX -= pItem->fOrigX;
		fPrevOriginY -= pItem->fOrigY;
		//Rotation and scaling
		QMatrix4x4 mat2;
		mat2.rotate(pItem->m_fRotation, 0, 0, 1.0f);
		mat2.scale(pItem->m_fScale[0], pItem->m_fScale[1]);
		QPointF tFloat2 = mat2.map(QPointF(fPrevOriginX, fPrevOriginY));
		pProp->fX += tFloat2.x();
		pProp->fY += tFloat2.y();
	}
}



void QGLESPIDCanvas::editMetaItemProperties()
{
	auto *pDM = CDataManage::GetInstance();
	auto pVEC = pDM->GET_MODEL_CLASS(DisplayMetaItem).get()->getVector();
	int nSelectedItem = m_nSelMetaIdx;
	int nRowItem = -1, nSubRowItem = -1;
	auto it = find_if(pVEC->begin(), pVEC->end(), [&nSelectedItem](std::shared_ptr<CSQLData> &pData)
	{
		DisplayMetaItem *pItem = (DisplayMetaItem*)pData.get();
		return pItem->GetIndex() == nSelectedItem;
	});
	int nCurTime = m_nCurTime;
	if (it != pVEC->end())
	{
		bool bNewlyAdded = false;
		nRowItem = std::distance(pVEC->begin(), it);
		pDM->GET_MODEL_CLASS(DisplayMetaItemProp)->setVectors(&it->get()->m_vChildItem[0].vSQLData, &it->get()->m_vChildItem[0].vSQLDataDelItems, it->get()->GetIndex());
		auto subit = find_if(it->get()->m_vChildItem[0].vSQLData.begin(), it->get()->m_vChildItem[0].vSQLData.end(), [&nCurTime](std::shared_ptr<CSQLData> &pData)
		{
			DisplayMetaItemProp *pProp = (DisplayMetaItemProp*)pData.get();
			return (pProp->nAtMiliseconds == nCurTime);
		});
		if (subit != it->get()->m_vChildItem[0].vSQLData.end())
		{
			nSubRowItem = std::distance(it->get()->m_vChildItem[0].vSQLData.begin(), subit);
		}
		else
		{
			bNewlyAdded = true;
			nSubRowItem = 0;
			auto tProp = pDM->GET_MODEL_CLASS(DisplayMetaItemProp)->insertRows(0, 1);
		}
		auto pSubVEC = pDM->GET_MODEL_CLASS(DisplayMetaItemProp)->getVector();
		DisplayMetaItem *pItem = (DisplayMetaItem*)it->get();
		DisplayMetaItemProp *pProp = (DisplayMetaItemProp*)pSubVEC->at(nSubRowItem).get();
		pProp->nAtMiliseconds = nCurTime;

		setPropertiesFromMetaItem(pItem, pProp, pItem->m_fTrans[0], pItem->m_fTrans[1]);


		editDisplayMetaItem tEdit(nRowItem, nSubRowItem, this);
		if ((tEdit.exec() != QDialog::Accepted))
		{
			if (bNewlyAdded)
				pDM->GET_MODEL_CLASS(DisplayProp)->removeRows(nSubRowItem, 1);
		}
		else
		{
			pItem->m_fRect[0] = 0;
			pItem->m_fRect[1] = 0;
			pItem->m_fRect[2] = (GLfloat)pItem->nWidth;
			pItem->m_fRect[3] = (GLfloat)pItem->nHeight;
			syncMetaItemBounds(pItem, pProp);
			setBoundRectangle(pItem);
			pItem->m_fRotation = pProp->fAngle;
			pProp->fScalingX = pItem->m_fScale[0];
			pProp->fScalingY = pItem->m_fScale[1];
			pProp->nVisible = pItem->m_nVisible;
			setMetaItemOrientation(pItem);
			CDataManage::reorderTimeLine(pItem);
			setSelectedItemVectors(pItem, 1);
		}
		sortToZOrder();
	}
}



void QGLESPIDCanvas::dragMoveEvent(QDragMoveEvent *e)
{
	e->accept();
}

void QGLESPIDCanvas::dragEnterEvent(QDragEnterEvent *e)
{
	if (e->mimeData()->hasFormat("text/plain") && e->mimeData()->hasHtml())
		e->acceptProposedAction();
}

void QGLESPIDCanvas::contextMenuEvent(QContextMenuEvent * e)
{
	auto *pDM = CDataManage::GetInstance();
	auto pVEC = pDM->GET_MODEL_CLASS(DisplayItem).get()->getVector();
	m_bMouseMovedWhilePressed = false;
	for (auto it : (*pVEC))
	{
		DisplayItem *pItem = (DisplayItem*)it.get();
		if (isPtInItemBound(pItem, e->pos().x(), e->pos().y()))
		{
			m_nSelIdx = pItem->GetIndex();

			if (isPropExist())
				m_pActDelProp->setEnabled(true);
			else
				m_pActDelProp->setEnabled(false);

			setSelectedItemVectors(pItem, 0);

			m_nSelMetaIdx = 0;
			m_pMenu->exec(e->globalPos());
			return;
		}
	}

	auto pDMI = pDM->GET_MODEL_CLASS(DisplayMetaItem).get()->getVector();
	for (auto it : (*pDMI))
	{
		DisplayMetaItem *pItem = (DisplayMetaItem*)it.get();
		if (isPtInMetaItemBound(pItem, e->pos().x(), e->pos().y()))
		{
			m_nMetaItemPosX= e->pos().x();
			m_nMetaItemPosY= e->pos().y();
			m_pAddMetaItem->setEnabled(false);
			m_pDeleteMetaItem->setEnabled(true);
			m_pEditMetaItem->setEnabled(true);
		
			m_nSelMetaIdx = pItem->GetIndex();
			m_nSelIdx = 0;

			if (isMetaPropExist())
				m_pDelMetaProp->setEnabled(true);
			else
				m_pDelMetaProp->setEnabled(false);
			setSelectedItemVectors(pItem, 1);

			
			m_pMetaItemMenu->exec(e->globalPos());
			return;
		}
	}
	
	m_nMetaItemPosX = e->pos().x();
	m_nMetaItemPosY = e->pos().y();

	m_pAddMetaItem->setEnabled(true);
	m_pDeleteMetaItem->setEnabled(false);
	m_pEditMetaItem->setEnabled(false);
	m_pDelMetaProp->setEnabled(false);
	m_pMetaItemMenu->exec(e->globalPos());

}

void QGLESPIDCanvas::setCurrentTime(int nCurTime)
{
	m_nCurTime = nCurTime;
	update();
}







void QGLESPIDCanvas::dropEvent(QDropEvent * e)
{
	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();
	int nIndex=e->mimeData()->html().toInt();
	std::shared_ptr<CSQLData> pData=pDM->GET_MODEL_CLASS(DisplayItem).get()->insertRow();
	CSQLData *pSQLData = pData.get();
	if (pSQLData)
	{
		DisplayItem *pItem = (DisplayItem*)pSQLData;
		pItem->nRelatedItemListIndex = nIndex;
		pDM->GET_MODEL_CLASS(DisplayProp)->setVectors(&pItem->m_vChildItem[0].vSQLData, &pItem->m_vChildItem[0].vSQLDataDelItems,pItem->GetIndex());
		std::shared_ptr<CSQLData> pSubData = pDM->GET_MODEL_CLASS(DisplayProp).get()->insertRow();
		DisplayProp *pProp = (DisplayProp*)pSubData.get();
		pItem->bSelected = false;
		auto it = m_mImageList.find(nIndex);
		if (it != m_mImageList.end())
		{
			pItem->nRelatedItemListIndex = nIndex;
			it->second->SetOrigin(pItem->nOrigin, true);
			pItem->SetBufferIndex(it->first, it->second.get());
			pItem->m_fTrans[0]=(GLfloat)e->pos().x();
			pItem->m_fTrans[1]=(GLfloat)e->pos().y();
			setBoundRectangle(pItem);
			pProp->nAtMiliseconds = m_nCurTime;
			setPropertiesFromItem(pItem, pProp, e->pos().x(), e->pos().y());
			syncBounds(pItem, pProp);
			m_nSelIdx = pItem->GetIndex();
			m_nSelMetaIdx = 0;
			setSelectedItemVectors(pItem, 0);
		}
		CDataManage::reorderTimeLine(pItem);
	}
	update();
}




void QGLESPIDCanvas::setBoundRectangle(DisplayItem *pItem)
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

void QGLESPIDCanvas::setBoundRectangle(DisplayMetaItem *pItem)
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


bool QGLESPIDCanvas::isPtInItemBound(DisplayItem *pItem,int nX,int nY,GLfloat *pX,GLfloat *pY)
{
	QMatrix4x4 mat;
	QPointF tFloat, tFloat2;;
	mat.translate(pItem->m_fTrans[0], pItem->m_fTrans[1]);
	mat.rotate(pItem->m_fRotation, 0, 0, 1.0f);
	mat.scale(pItem->m_fScale[0], pItem->m_fScale[1]);
	mat.translate(pItem->fOrigX, pItem->fOrigY);
	bool bInvertable;
	QMatrix4x4 matInv=mat.inverted(&bInvertable);
	if (bInvertable)
	{
		CTextureInfo *pTI = CTextureInfo::GetInstance();
		tFloat = matInv.map(QPointF((float)nX, (GLfloat)nY));
		float fX = tFloat.x();
		float fY = tFloat.y();

		if (pX&&pY)
		{
			float fOffsetX = pItem->fOrigX + fX;
			float fOffsetY = pItem->fOrigY + fY;
			QMatrix4x4 mat2;
			mat2.rotate(pItem->m_fRotation, 0, 0, 1.0f);
			mat2.scale(pItem->m_fScale[0], pItem->m_fScale[1]);
			tFloat2 = mat2.map(QPointF(fOffsetX, fOffsetY));
			(*pX) = tFloat2.x();
			(*pY) = tFloat2.y();
		}
		return pTI->PtInPolygon(pItem->m_fTempRect,(GLfloat)fX,(GLfloat)fY);
	}
	return false;
}


bool QGLESPIDCanvas::isPtInMetaItemBound(DisplayMetaItem *pItem, int nX, int nY, GLfloat *pX, GLfloat *pY)
{
	QMatrix4x4 mat;
	QPointF tFloat, tFloat2;
	mat.translate(pItem->m_fTrans[0], pItem->m_fTrans[1]);
	mat.rotate(pItem->m_fRotation, 0, 0, 1.0f);
	mat.scale(pItem->m_fScale[0], pItem->m_fScale[1]);
	mat.translate(pItem->fOrigX, pItem->fOrigY);
	bool bInvertable;
	QMatrix4x4 matInv = mat.inverted(&bInvertable);
	if (bInvertable)
	{
		CTextureInfo *pTI = CTextureInfo::GetInstance();
		tFloat = matInv.map(QPointF((float)nX, (GLfloat)nY));
		float fX = tFloat.x();
		float fY = tFloat.y();
		if (pX&&pY)
		{
			float fOffsetX = pItem->fOrigX + fX;
			float fOffsetY = pItem->fOrigY + fY;
			QMatrix4x4 mat2;
			mat2.rotate(pItem->m_fRotation, 0, 0, 1.0f);
			mat2.scale(pItem->m_fScale[0], pItem->m_fScale[1]);
			tFloat2 = mat2.map(QPointF(fOffsetX, fOffsetY));
			(*pX) = tFloat2.x();
			(*pY) = tFloat2.y();
		}
		return pTI->PtInPolygon(pItem->m_fTempRect, (GLfloat)tFloat.x(), (GLfloat)tFloat.y());
	}
	return false;
}


void QGLESPIDCanvas::setSelectedItemVectors(void *pItem,int nType)
{
	switch (nType)
	{
	case 0:
		{
			DisplayItem *pPropItem = (DisplayItem*)pItem;
			m_nLatestSelected = pPropItem->GetIndex();
			m_nLatestSelectedType = 1;
			vKeyFrames.clear();
			for (auto it : pPropItem->m_vChildItem[0].vSQLData)
			{
				DisplayProp *pProp = (DisplayProp*)it.get();
				vKeyFrames.push_back(pProp->nAtMiliseconds);
			}
			emit selectionChanged();
		}
		break;
	case 1:
		{
			DisplayMetaItem *pPropItem = (DisplayMetaItem*)pItem;
			m_nLatestSelected = pPropItem->GetIndex();
			m_nLatestSelectedType = 2;
			vKeyFrames.clear();
			for (auto it : pPropItem->m_vChildItem[0].vSQLData)
			{
				DisplayMetaItemProp *pProp = (DisplayMetaItemProp*)it.get();
				vKeyFrames.push_back(pProp->nAtMiliseconds);
			}
			emit selectionChanged();
		}
		break;
	case 2:
		m_nLatestSelected=0;
		m_nLatestSelectedType=0;
		vKeyFrames.clear();
		emit selectionChanged();
		break;
	default:
		return;
	}
	

}


void QGLESPIDCanvas::mousePressEvent(QMouseEvent *e)
{
	auto *pDM = CDataManage::GetInstance();
	CTextureInfo *pTI = CTextureInfo::GetInstance();
	if (e->button() == Qt::LeftButton)
	{
		m_bMousePressed = true;
		auto pVEC = pDM->GET_MODEL_CLASS(DisplayItem).get()->getVector();
		auto pVECM = pDM->GET_MODEL_CLASS(DisplayMetaItem).get()->getVector();
		for (auto it : (*pVEC))
		{
			DisplayItem *pItem = (DisplayItem*)it.get();
			if (isPtInItemBound(pItem, e->pos().x(), e->pos().y(),&m_fOffsetX,&m_fOffsetY))
			{
				m_bMoving = false;
				pItem->bSelected = true;
				m_nSelIdx = pItem->GetIndex();
				setSelectedItemVectors( pItem, 0);
				m_nSelMetaIdx = 0;
				update();
				return;
			}
		}

		for (auto it : (*pVEC))
		{
			DisplayItem *pItem = (DisplayItem*)it.get();
			pItem->bSelected = false;
		}

		for (auto it : (*pVECM))
		{
			DisplayMetaItem *pItem = (DisplayMetaItem*)it.get();
			if (isPtInMetaItemBound(pItem, e->pos().x(), e->pos().y(), &m_fOffsetX, &m_fOffsetY))
			{
				m_bMoving = false;
				pItem->bSelected = true;
				m_nSelMetaIdx = pItem->GetIndex();

				setSelectedItemVectors(pItem, 1);

				m_nSelIdx = 0;
				update();
				return;
			}
		}

		for (auto it : (*pVECM))
		{
			DisplayMetaItem *pItem = (DisplayMetaItem*)it.get();
			pItem->bSelected = false;
		}
		m_nSelIdx = 0;
		m_nSelMetaIdx = 0;
		update();
		return;
	}
}


void QGLESPIDCanvas::mouseMoveEvent(QMouseEvent *e)
{
	int nSelIdx = m_nSelIdx;
	auto *pDM = CDataManage::GetInstance();
	CTextureInfo *pTI = CTextureInfo::GetInstance();
	emit positionChanged(QString("x : %1 y : %2").arg(e->pos().x()).arg(e->pos().y()));
	if (m_bMousePressed)
	{
		m_bMouseMovedWhilePressed = true;
		auto pVEC = pDM->GET_MODEL_CLASS(DisplayItem).get()->getVector();
		if (nSelIdx)
		{
			auto fIt = find_if(pVEC->begin(), pVEC->end(), [&nSelIdx](std::shared_ptr<CSQLData> &pData) {return (pData->GetIndex() == nSelIdx); });
			if (fIt != pVEC->end())
			{
				m_bMoving = true;
				DisplayItem *pItem = (DisplayItem*)fIt->get();
				pItem->m_fTrans[0] = (GLfloat)e->pos().x() - m_fOffsetX;
				pItem->m_fTrans[1] = (GLfloat)e->pos().y() - m_fOffsetY;
				update();
				return;
			}
		}

		int nMetaSelIdx = m_nSelMetaIdx;
		auto pVECM = pDM->GET_MODEL_CLASS(DisplayMetaItem).get()->getVector();
		if (nMetaSelIdx)
		{
			auto fIt = find_if(pVECM->begin(), pVECM->end(), [&nMetaSelIdx](std::shared_ptr<CSQLData> &pData) {return (pData->GetIndex() == nMetaSelIdx); });
			if (fIt != pVECM->end())
			{
				m_bMoving = true;
				DisplayMetaItem *pItem = (DisplayMetaItem*)fIt->get();
				pItem->m_fTrans[0] = (GLfloat)e->pos().x() - m_fOffsetX;
				pItem->m_fTrans[1] = (GLfloat)e->pos().y() - m_fOffsetY;
				update();
				return;
			}
		}
	}
}

void QGLESPIDCanvas::reorderAllTimeLine()
{
	auto *pDM = CDataManage::GetInstance();
	auto pVEC = pDM->GET_MODEL_CLASS(DisplayItem).get()->getVector();
	for (auto it : (*pVEC))
	{
		DisplayItem *pItem = (DisplayItem*)it.get();
		CDataManage::reorderTimeLine(pItem);
	}

	auto pMVEC = pDM->GET_MODEL_CLASS(DisplayMetaItem).get()->getVector();
	for (auto it : (*pMVEC))
	{
		DisplayMetaItem *pItem = (DisplayMetaItem*)it.get();
		CDataManage::reorderTimeLine(pItem);
	}

}



void QGLESPIDCanvas::mouseReleaseEvent(QMouseEvent *e)
{
	m_bMoving = false;
	int nSelIdx = m_nSelIdx;
	int nSelMetaIdx = m_nSelMetaIdx;
	m_bMousePressed = false;
	auto *pDM = CDataManage::GetInstance();
	CTextureInfo *pTI = CTextureInfo::GetInstance();
	auto pVEC = pDM->GET_MODEL_CLASS(DisplayItem).get()->getVector();
	auto pVECM = pDM->GET_MODEL_CLASS(DisplayMetaItem).get()->getVector();
	if (m_bMouseMovedWhilePressed)
	{
		if (nSelIdx)
		{
			auto fIt = find_if(pVEC->begin(), pVEC->end(), [&nSelIdx](std::shared_ptr<CSQLData> &pData) {return (pData->GetIndex() == nSelIdx); });
			if (fIt != pVEC->end())
			{
				int nCurTime = m_nCurTime;
				DisplayItem *pItem = (DisplayItem*)fIt->get();
				//해당되는 시간을 찾는다.
				auto iit = find_if(pItem->m_vChildItem[0].vSQLData.begin(), pItem->m_vChildItem[0].vSQLData.end(), [&nCurTime](std::shared_ptr<CSQLData> &pData)
				{
					DisplayProp *pProp = (DisplayProp*)pData.get();
					return (pProp->nAtMiliseconds == nCurTime);
				});
				if (iit != pItem->m_vChildItem[0].vSQLData.end())
				{
					DisplayProp *pProp = (DisplayProp*)iit->get();
					setPropertiesFromItem(pItem, pProp, e->pos().x() - m_fOffsetX, e->pos().y() - m_fOffsetY);
					m_fOffsetX = 0;
					m_fOffsetY = 0;
				}
				else
				{
					//해당되는 시간에 대한 프로퍼티가 없다면 새로 입력하여 설정한다.
					pDM->GET_MODEL_CLASS(DisplayProp)->setVectors(&pItem->m_vChildItem[0].vSQLData, &pItem->m_vChildItem[0].vSQLDataDelItems, pItem->GetIndex());
					std::shared_ptr<CSQLData> pSubData = pDM->GET_MODEL_CLASS(DisplayProp).get()->insertRow();
					DisplayProp *pProp = (DisplayProp*)pSubData.get();
					pProp->nAtMiliseconds = m_nCurTime;
					setPropertiesFromItem(pItem, pProp, e->pos().x() - m_fOffsetX, e->pos().y() - m_fOffsetY);
					m_fOffsetX = 0;
					m_fOffsetY = 0;
				}
				CDataManage::reorderTimeLine(pItem);
				pItem->tLine.jumpTo((GLfloat)m_nCurTime);
				setSelectedItemVectors(pItem, 0);
			}
		}
		for (auto it : (*pVEC))
		{
			DisplayItem *pItem = (DisplayItem*)it.get();
			pItem->bSelected = false;
		}

		if (nSelMetaIdx)
		{
			auto fIt = find_if(pVECM->begin(), pVECM->end(), findSQLData(nSelMetaIdx));
			if (fIt != pVECM->end())
			{
				int nCurTime = m_nCurTime;
				DisplayMetaItem *pItem = (DisplayMetaItem*)fIt->get();
				//해당되는 시간을 찾는다.
				auto iit = find_if(pItem->m_vChildItem[0].vSQLData.begin(), pItem->m_vChildItem[0].vSQLData.end(), [&nCurTime](std::shared_ptr<CSQLData> &pData)
				{
					DisplayMetaItemProp *pProp = (DisplayMetaItemProp*)pData.get();
					return (pProp->nAtMiliseconds == nCurTime);
				});
				if (iit != pItem->m_vChildItem[0].vSQLData.end())
				{
					DisplayMetaItemProp *pProp = (DisplayMetaItemProp*)iit->get();
					setPropertiesFromMetaItem(pItem, pProp, e->pos().x() - m_fOffsetX, e->pos().y() - m_fOffsetY);
					m_fOffsetX = 0;
					m_fOffsetY = 0;
				}
				else
				{
					//해당되는 시간에 대한 프로퍼티가 없다면 새로 입력하여 설정한다.
					pDM->GET_MODEL_CLASS(DisplayMetaItemProp)->setVectors(&pItem->m_vChildItem[0].vSQLData, &pItem->m_vChildItem[0].vSQLDataDelItems, pItem->GetIndex());
					std::shared_ptr<CSQLData> pSubData = pDM->GET_MODEL_CLASS(DisplayMetaItemProp).get()->insertRow();
					DisplayMetaItemProp *pProp = (DisplayMetaItemProp*)pSubData.get();
					pProp->nAtMiliseconds = m_nCurTime;
					setPropertiesFromMetaItem(pItem, pProp, e->pos().x() - m_fOffsetX, e->pos().y() - m_fOffsetY);
					m_fOffsetX = 0;
					m_fOffsetY = 0;
				}
				CDataManage::reorderTimeLine(pItem);
				pItem->tLine.jumpTo((GLfloat)m_nCurTime);
				setSelectedItemVectors(pItem, 1);
			}
		}
		for (auto it : (*pVECM))
		{
			DisplayMetaItem *pItem = (DisplayMetaItem*)it.get();
			pItem->bSelected = false;
		}
	}


	sortToZOrder();
	m_nSelIdx = 0;
	m_nSelMetaIdx = 0;
	m_bMouseMovedWhilePressed = false;
	update();
	return;
}

void QGLESPIDCanvas::setPropertiesFromItem(DisplayItem* pItem, DisplayProp *pProp,GLfloat nX, GLfloat nY)
{
	pProp->fX = (GLfloat)nX;
	pProp->fY = (GLfloat)nY;
	pProp->fScalingX = pItem->m_fScale[0];
	pProp->fScalingY = pItem->m_fScale[1];
	pProp->fAngle = pItem->m_fRotation;
	pProp->nVisible = pItem->m_nVisible;
	unsigned int uRed = (unsigned char)(GLfloat)((pItem->m_fColor[0] / 1.0f) * 255.0f);
	unsigned int uGreen = (unsigned char)(GLfloat)((pItem->m_fColor[1] / 1.0f) * 255.0f);
	unsigned int uBlue = (unsigned char)(GLfloat)((pItem->m_fColor[2] / 1.0f) * 255.0f);
	unsigned int uAlpha = (unsigned char)(GLfloat)((pItem->m_fColor[3] / 1.0f) * 255.0f);
	pProp->uColor = (uRed << 24) | (uGreen << 16) | (uBlue << 8) | (uAlpha);

	if (pProp->GetRecordState() != EDIT_INSERTED)
	{
		pProp->SetRecordState(EDIT_UPDATED);
	}
}

void QGLESPIDCanvas::setPropertiesFromMetaItem(DisplayMetaItem* pItem, DisplayMetaItemProp *pProp, GLfloat nX, GLfloat nY)
{
	pProp->fX = (GLfloat)nX;
	pProp->fY = (GLfloat)nY;
	pProp->fScalingX = pItem->m_fScale[0];
	pProp->fScalingY = pItem->m_fScale[1];
	pProp->fAngle = pItem->m_fRotation;
	pProp->nVisible = pItem->m_nVisible;
	/*unsigned int uRed = (unsigned char)(GLfloat)((pItem->m_fColor[0] / 1.0f) * 255.0f);
	unsigned int uGreen = (unsigned char)(GLfloat)((pItem->m_fColor[1] / 1.0f) * 255.0f);
	unsigned int uBlue = (unsigned char)(GLfloat)((pItem->m_fColor[2] / 1.0f) * 255.0f);
	unsigned int uAlpha = (unsigned char)(GLfloat)((pItem->m_fColor[3] / 1.0f) * 255.0f);
	pProp->uColor = (uRed << 24) | (uGreen << 16) | (uBlue << 8) | (uAlpha);*/
	if (pProp->GetRecordState() != EDIT_INSERTED)
	{
		pProp->SetRecordState(EDIT_UPDATED);
	}
}

void QGLESPIDCanvas::timerEvent(QTimerEvent *e)
{
}

void QGLESPIDCanvas::resizeGL(int w, int h)
{
	qDebug() << Q_FUNC_INFO;
	m_nHeight = h;
	m_nWidth = w;
}


void QGLESPIDCanvas::sortToZOrder()
{
	auto *pDM = CDataManage::GetInstance();
	auto pVEC = pDM->GET_MODEL_CLASS(DisplayItem).get()->getVector();
	std::sort(pVEC->begin(), pVEC->end(), [](std::shared_ptr<CSQLData> &pL, std::shared_ptr<CSQLData> &pR)
	{
		DisplayItem *pDPL = (DisplayItem*)pL.get();
		DisplayItem *pDPR = (DisplayItem*)pR.get();
		return pDPL->nZOrder < pDPR->nZOrder;
	});

	auto pVECM = pDM->GET_MODEL_CLASS(DisplayMetaItem).get()->getVector();
	std::sort(pVECM->begin(), pVECM->end(), [](std::shared_ptr<CSQLData> &pL, std::shared_ptr<CSQLData> &pR)
	{
		DisplayMetaItem *pDPL = (DisplayMetaItem*)pL.get();
		DisplayMetaItem *pDPR = (DisplayMetaItem*)pR.get();
		return pDPL->nZOrder < pDPR->nZOrder;
	});


}

void QGLESPIDCanvas::initBaseData()
{

	auto *pTM = CTableManage::GetInstance();
	// text image, picture image file pool에 있는 데이터 check
	auto bitmapCheck = [](unsigned char *pSoc, int nLeftSoc, int nTopSoc, int nRightSoc, int nBottomSoc, int nStrideSoc, int nBytesPerPixel)->bool
	{
		qDebug() << QString("bmpcheck left:%1 top:%2 right:%3 bot:%4 stride:%5 bpp:%6")
			.arg(nLeftSoc).arg(nTopSoc).arg(nRightSoc).arg(nBottomSoc).arg(nStrideSoc).arg(nBytesPerPixel);

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
		qDebug() << QString("bmpcopy[soc]left:%1 top:%2 right:%3 bot:%4 stride:%5 bpp:%6")
			.arg(nLeftSoc).arg(nTopSoc).arg(nRightSoc).arg(nBottomSoc).arg(nStrideSoc).arg(nBytesPerPixel);
		qDebug() << QString("bmpcopy[des]left:%1 top:%2 width:%3 height:%4 stride:%5")
			.arg(nLeftDes).arg(nTopDes).arg(nWidthDes).arg(nHeightDes).arg(nStrideDes);

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
			qDebug() << "[before]L:" << pFloatL[0] << pFloatL[1] << pFloatL[2] << pFloatL[3];
			qDebug() << "[before]R:" << pFloatR[0] << pFloatR[1] << pFloatR[2] << pFloatR[3];

			if (pFloatL[0] == 0.0f&&pFloatL[1] == 0.0f&&pFloatL[2] == 0.0f&&pFloatL[3] == 0.0f)
			{
				memcpy(pFloatL, pFloatR, sizeof(GLfloat) * 4);
			}
			else if (pFloatR[0] == 0.0f&&pFloatR[1] == 0.0f&&pFloatR[2] == 0.0f&&pFloatR[3] == 0.0f)
			{
				memcpy(pFloatR, pFloatL, sizeof(GLfloat) * 4);
			}

			pFloatU[0] = std::min(pFloatL[0], pFloatR[0]);
			pFloatU[1] = std::min(pFloatL[1], pFloatR[1]);
			pFloatU[2] = std::max(pFloatL[2], pFloatR[2]);
			pFloatU[3] = std::max(pFloatL[3], pFloatR[3]);

			qDebug() << "[Result]L:" << pFloatL[0] << pFloatL[1] << pFloatL[2] << pFloatL[3];
			qDebug() << "[Result]R:" << pFloatR[0] << pFloatR[1] << pFloatR[2] << pFloatR[3];
			qDebug() << "[Result]U:" << pFloatU[0] << pFloatU[1] << pFloatU[2] << pFloatU[3];
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
	int nWidthLimit = WIDTH_LIMIT;
	int nHeightLimit = HEIGHT_LIMIT;
	int nBytesPerPixel = 4;
	int nBytesPerLine = nWidthLimit * nBytesPerPixel;
	std::vector<std::shared_ptr<unsigned char>> vBuffers;
	int nMaxHeight = 0;
	int nCurX = 0;
	int nCurY = 0;
	int nCurMaxHeight = 0;
	int nVertexOrder = 0;
	

	std::for_each(pTM->m_vStationImagePool.begin(), pTM->m_vStationImagePool.end(), 
		[bitmapCheck, &vTexture, &nTextureRegisterIndex, &nVertexOrder, &nCurMaxHeight, 
		&nWidthLimit, &nHeightLimit, &nBytesPerLine, &nBytesPerPixel, &nCurX, &nCurY, &nMaxHeight] (std::shared_ptr<CSQLData> &pData)
	{
		StationImagePool *pPool = (StationImagePool*)pData.get();
		TextureOrig tTexture = { 
			false, 
			pPool->nWidth,
			pPool->nHeight,
			pPool->nWidth*nBytesPerPixel,
			0,
			0, 
			pPool->nTextureIndex = nTextureRegisterIndex++,
			(GLubyte*)pPool->pByte.get()
		};

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
	vBinPackedDest.push_back(std::shared_ptr<MaxRectsPixelBuffer>(new MaxRectsPixelBuffer(nWidthLimit, nHeightLimit, nBytesPerPixel, true, false)));

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
	
	std::vector<GLfloat> vVertices;
	std::vector<GLushort> vIndices;

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
				qDebug() << Q_FUNC_INFO << "unitedRect type:" << pII->nType << "index:" << nImageIndex;
				{
					auto it = find_if(pTM->m_vStationImagePool.begin(), pTM->m_vStationImagePool.end(), [&nImageIndex](std::shared_ptr<CSQLData> &pData) {return nImageIndex == pData.get()->GetIndex(); });
					if (it != pTM->m_vStationImagePool.end())
					{
						StationImagePool *pSIP = (StationImagePool*)it->get();
						if (pSIP->nDataLength&&pSIP->pByte.get())
						{
							GLfloat fL[4] = { (GLfloat)pII->nXPos,(GLfloat)pII->nYPos,(GLfloat)(pII->nXPos+pSIP->nWidth),(GLfloat)(pII->nYPos+pSIP->nHeight) };
							unitedRect(pIIL->fRect, fL, pIIL->fRect);
						}
					}
				}
				break;
			case 2:
				nImageIndex = pII->nStationBitmapIndex;
				qDebug() << Q_FUNC_INFO << "unitedRect type:" << pII->nType << "index:" << nImageIndex;
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

	for (auto pData : pTM->m_vImageIndexList)
	{
		ImageIndexList *pIIL = (ImageIndexList*)pData.get();	
		for (auto il : pData->m_vChildItem[0].vSQLData)
		{
			ImageIndex *pII = (ImageIndex*)(il.get());
			int nKey = pIIL->GetIndex();
			GLsizei nCount, nOffset;
			GLint nTexIndex;
			switch(pII->nType)
			{
			case 1:
				{
					int nImageIndex = pII->nStationNameBitmapIndex;
					qDebug() << Q_FUNC_INFO << "GetTextureInfo type:" << pII->nType << "index:" << nImageIndex;
					auto it = find_if(pTM->m_vStationImagePool.begin(), pTM->m_vStationImagePool.end(), [&nImageIndex](std::shared_ptr<CSQLData> &pData) {return nImageIndex == pData.get()->GetIndex(); });
					if (it != pTM->m_vStationImagePool.end())
					{
						StationImagePool *pSIP = (StationImagePool*)it->get();
						if (pSIP->nDataLength&&pSIP->pByte.get())
						{
							if (pTI->GetTextureInfo(pSIP->nTextureIndex, vVertices, vIndices,  pII->nXPos, pII->nYPos,&nCount,&nOffset,&nTexIndex))
							{
								auto itFind = m_mImageList.find(nKey);
								if (itFind != m_mImageList.end())
								{
									itFind->second.get()->AddIndex(nTexIndex,nCount,nOffset);
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
					qDebug() << Q_FUNC_INFO << "GetTextureInfo type:" << pII->nType << "index:" << nImageIndex;
					auto it = find_if(pTM->m_vBitmapImagePool.begin(), pTM->m_vBitmapImagePool.end(), [&nImageIndex](std::shared_ptr<CSQLData> &pData) {return nImageIndex == pData.get()->GetIndex(); });
					if (it != pTM->m_vBitmapImagePool.end())
					{
						BitmapImagePool *pSIP = (BitmapImagePool*)it->get();
						if (pSIP->nDataLength&&pSIP->pByte.get())
						{
							if (pTI->GetTextureInfo(pSIP->nTextureIndex, vVertices, vIndices, pII->nXPos, pII->nYPos,&nCount, &nOffset, &nTexIndex))
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

	for (auto i : vBinPacked)
	{
		i->Sync1StTextureBuffer();
		i->Init2ndTextureBuffer();
	}


	glGenBuffers(2, m_uVBOsID);	//Creating Vertex Buffer Object
	glBindBuffer(GL_ARRAY_BUFFER, m_uVBOsID[0]);
	glBufferData(GL_ARRAY_BUFFER, vVertices.size() * sizeof(GLfloat), &vVertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uVBOsID[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vIndices.size() * sizeof(GLushort), &vIndices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

}