#include "QGLESLineMapCanvas.h"
#include "TableManage.h"
#include "DataManage.h"
#include "dataModel.h"
#include <minmax.h>
#include <windows.h>
#include <Gdiplus.h>
#include "TileMapSupport.h"
#include "TexPool.h"
#include <algorithm>
#include "TextureInformation/CTextureInfo.h"
#include <qdebug.h>
#include <qformlayout.h>
#include <qlineedit.h>
#include <qspinbox.h>

#include "nodepropertydlg.h"

#define MAKECOORDKEY(A,B)	MAKELONG(B,A)


void QGLESLineMapCanvas::mousePressEvent(QMouseEvent *e)
{
	int nIndex;
	bool bDeleted = false;
	auto *pDM = CDataManage::GetInstance();
	int nOriginPosX = e->pos().x();
	int nOriginPosY = e->pos().y();
	int nCurX = (int)(nOriginPosX / m_nCellSize)*m_nCellSize + (m_nCellSize / 2);
	int nCurY = (int)(nOriginPosY / m_nCellSize)*m_nCellSize + (m_nCellSize / 2);
	if (e->button() == Qt::LeftButton)
	{
		switch (m_eEditMode)
		{
		case EDIT_NODE:
			if (!m_bCtrlKeyPressed)
			{
				for (auto it : (*pDM->GET_MODEL_CLASS(LineMapNode)->getVector()))
				{
					LineMapNode *pNode = (LineMapNode*)it.get();
					QRect tRect(pNode->nPosX - 15, pNode->nPosY - 15, 30, 30);
					if (tRect.contains(nOriginPosX, nOriginPosY))
					{
						m_nSelectedNode = it.get()->GetIndex();
					}
				}
				m_bPressed = true;
			}
			else
			{
				m_bPressed = false;
				m_nSelectedNode = -1;

				std::map<unsigned int, int>::iterator mit;
				for (auto mit : m_mNodes)
				{
					unsigned short wX = (mit.first >> 16);
					unsigned short wY = (mit.first);
					QRect tRect(wX - 15, wY - 15, 30, 30);
					if (tRect.contains(nOriginPosX, nOriginPosY))
					{
						m_vSelNodes.push_back(mit.first);
					}
				}
			}
			break;
		case EDIT_ARROW:
		{
			bool bSelected = false;
			CTableManage *pTM = (CTableManage*)CTableManage::GetInstance();
			LineMapPool *pPool = (LineMapPool*)pTM->m_vLineMapPool.at(m_nRow).get();
			for (auto vit : (*pDM->GET_MODEL_CLASS(LineMapNode)->getVector()))
			{
				LineMapNode *pNode = (LineMapNode*)vit.get();
				QRect tRect(pNode->nPosX - 15, pNode->nPosY - 15, 30, 30);
				if (tRect.contains(nOriginPosX, nOriginPosY))
				{
					bSelected = true;
					if (!m_uArrowNode[0])
					{
						m_uArrowNode[0] = MAKECOORDKEY((WORD)pNode->nPosX, (WORD)pNode->nPosY);
					}
					else if (!m_uArrowNode[1])
					{
						m_uArrowNode[1] = MAKECOORDKEY((WORD)pNode->nPosX, (WORD)pNode->nPosY);
						if (m_uArrowNode[0] == m_uArrowNode[1])
						{
							m_uArrowNode[1] = 0;
						}
						else
						{
							unsigned short wStX = (unsigned short)(m_uArrowNode[0] >> 16);
							unsigned short wStY = (unsigned short)(m_uArrowNode[0]);
							unsigned short wEnX = (unsigned short)(m_uArrowNode[1] >> 16);
							unsigned short wEnY = (unsigned short)(m_uArrowNode[1]);
							realignNodes();
							generateArrowFrom(wStX, wStY, wEnX, wEnY, pPool->uForArrowOffset, pPool->uBackArrowOffset, pPool->fPenWidth);
							m_uArrowNode[0] = m_uArrowNode[1] = 0;
						}
					}
				}
			}
			if (!bSelected)
			{
				m_uArrowNode[0] = m_uArrowNode[1] = 0;
			}
		}
		break;
		case EDIT_DISPLAYITEM:
		{
			auto pVEC = pDM->GET_MODEL_CLASS(LineMapDisplayItem)->getVector();
			for (auto it : (*pVEC))
			{
				LineMapDisplayItem *pItem = (LineMapDisplayItem*)it.get();
				if (isPtInItemBound(pItem, e->pos().x(), e->pos().y(), &m_fOffsetX, &m_fOffsetY))
				{
					m_bMoving = false;
					m_nSelectedDispItem = pItem->GetIndex();
					//pItem->bSelected = true;
					update();
					return;
				}
			}
		}
		break;
		default:
			break;
		}
	}
	update();
}

void QGLESLineMapCanvas::mouseReleaseEvent(QMouseEvent *e)
{
	m_bPressed = false;
	m_nSelectedNode = -1;
	m_nSelectedDispItem = 0;
	update();
}

void QGLESLineMapCanvas::mouseMoveEvent(QMouseEvent *e)
{
	auto *pDM = CDataManage::GetInstance();
	int nMinXPos, nMinYPos;
	switch (m_eEditMode)
	{
	case EDIT_NODE:
		if (m_bPressed && (m_nSelectedNode != -1) && getMinCoordFromBuffer(e->pos().x(), e->pos().y(), &nMinXPos, &nMinYPos))
		{
			auto pVEC = pDM->GET_MODEL_CLASS(LineMapNode)->getVector();
			auto vit = find_if(pVEC->begin(), pVEC->end(), findSQLData(m_nSelectedNode));
			if (vit != pVEC->end())
			{
				LineMapNode *pLN = (LineMapNode*)vit->get();
				pLN->nPosX = nMinXPos;
				pLN->nPosY = nMinYPos;
				if (pLN->GetRecordState() == EDIT_NOT_MODIFIED)
					pLN->SetRecordState(EDIT_UPDATED);
			}
		}
		break;
	case EDIT_DISPLAYITEM:
		if (m_nSelectedDispItem)
		{
			int nSelIdx = m_nSelectedDispItem;
			auto pVEC = pDM->GET_MODEL_CLASS(LineMapDisplayItem).get()->getVector();
			auto fIt = find_if(pVEC->begin(), pVEC->end(), [&nSelIdx](std::shared_ptr<CSQLData> &pData) {return (pData->GetIndex() == nSelIdx); });
			if (fIt != pVEC->end())
			{
				m_bMoving = true;
				LineMapDisplayItem *pItem = (LineMapDisplayItem*)fIt->get();
				pItem->nPosX = (int)((GLfloat)e->pos().x() - m_fOffsetX);
				pItem->nPosY = (int)((GLfloat)e->pos().y() - m_fOffsetY);
				if (pItem->GetRecordState() == EDIT_NOT_MODIFIED)
					pItem->SetRecordState(EDIT_UPDATED);
				update();
				return;
			}
		}
		break;
	default:
		break;
	}
	update();
}

void QGLESLineMapCanvas::initLinkMenu()
{
	QAction *pAction;
	auto *pDM = CDataManage::GetInstance();
	m_pLinkMenu = new QMenu("Select tile", this);
	for (int i = TILE_NONE; i < TILE_C_RU + 1; i++)
	{
		switch (i)
		{
		case TILE_NONE:
			pAction = new QAction(pDM->m_iconTile01, "NONE (&0)", this);
			pAction->setData(i);
			m_pLinkMenu->addAction(pAction);
			break;
		case TILE_H_U:
			pAction = new QAction(pDM->m_iconTile02, "H_U (&1)", this);
			pAction->setData(i);
			m_pLinkMenu->addAction(pAction);
			break;
		case TILE_H_D:
			pAction = new QAction(pDM->m_iconTile03, "H_D (&2)", this);
			pAction->setData(i);
			m_pLinkMenu->addAction(pAction);
			break;
		case TILE_H_L:
			pAction = new QAction(pDM->m_iconTile04, "H_L (&3)", this);
			pAction->setData(i);
			m_pLinkMenu->addAction(pAction);
			break;
		case TILE_H_R:
			pAction = new QAction(pDM->m_iconTile05, "H_R (&4)", this);
			pAction->setData(i);
			m_pLinkMenu->addAction(pAction);
			break;
		case TILE_F_UD:
			pAction = new QAction(pDM->m_iconTile06, "F_UD (&5)", this);
			pAction->setData(i);
			m_pLinkMenu->addAction(pAction);
			break;
		case TILE_F_LR:
			pAction = new QAction(pDM->m_iconTile07, "F_LR (&6)", this);
			pAction->setData(i);
			m_pLinkMenu->addAction(pAction);
			break;
		case TILE_CROSS:
			pAction = new QAction(pDM->m_iconTile08, "CROSS (&7)", this);
			pAction->setData(i);
			m_pLinkMenu->addAction(pAction);

			break;
		case TILE_F_UD_H_L:
			pAction = new QAction(pDM->m_iconTile09, "F_UD_H_L (&8)", this);
			pAction->setData(i);
			m_pLinkMenu->addAction(pAction);
			break;
		case TILE_F_UD_H_R:
			pAction = new QAction(pDM->m_iconTile10, "F_UD_H_R (&9)", this);
			pAction->setData(i);
			m_pLinkMenu->addAction(pAction);
			break;
		case TILE_F_LR_H_U:
			pAction = new QAction(pDM->m_iconTile11, "F_LR_H_U (&Q)", this);
			pAction->setData(i);
			m_pLinkMenu->addAction(pAction);
			break;
		case TILE_F_LR_H_D:
			pAction = new QAction(pDM->m_iconTile12, "F_LR_H_D (&W)", this);
			pAction->setData(i);
			m_pLinkMenu->addAction(pAction);
			break;
		case TILE_C_LU:
			pAction = new QAction(pDM->m_iconTile13, "C_LU (&E)", this);
			pAction->setData(i);
			m_pLinkMenu->addAction(pAction);
			break;
		case TILE_C_LD:
			pAction = new QAction(pDM->m_iconTile14, "C_LD (&R)", this);
			pAction->setData(i);
			m_pLinkMenu->addAction(pAction);
			break;
		case TILE_C_RD:
			pAction = new QAction(pDM->m_iconTile15, "C_RD (&T)", this);
			pAction->setData(i);
			m_pLinkMenu->addAction(pAction);
			break;
		case TILE_C_RU:
			pAction = new QAction(pDM->m_iconTile16, "C_RU (&Y)", this);
			pAction->setData(i);

			m_pLinkMenu->addAction(pAction);
			break;
		default:
			break;
		}
	}
	connect(m_pLinkMenu, SIGNAL(triggered(QAction*)), this, SLOT(selectAction(QAction*)));
}


void QGLESLineMapCanvas::initNodeMenu()
{
	QAction *pAction;
	auto *pDM = CDataManage::GetInstance();

	m_pNodeMenu = new QMenu("Edit Node", this);

	pAction = new QAction(pDM->m_iconAddNode, "Add Node", this);
	pAction->setData(1);
	m_pNodeMenu->addAction(pAction);

	pAction = new QAction(pDM->m_iconDelMapItem, "Delete Node", this);
	pAction->setData(2);
	m_pNodeMenu->addAction(pAction);

	pAction = new QAction(pDM->m_iconEditNode, "Edit Node Name", this);
	pAction->setData(3);
	m_pNodeMenu->addAction(pAction);

	pAction = new QAction(pDM->m_iconEditSpot, "Edit Node Icon", this);
	pAction->setData(4);
	m_pNodeMenu->addAction(pAction);

	connect(m_pNodeMenu, SIGNAL(triggered(QAction*)), this, SLOT(selectAction(QAction*)));
}


void QGLESLineMapCanvas::initArrowMenu()
{
	QAction *pAction;
	auto *pDM = CDataManage::GetInstance();
	m_pArrowMenu = new QMenu("Edit Arrow", this);

	pAction = new QAction(pDM->m_iconDelMapItem, "Delete arrow", this);
	pAction->setData(1);
	m_pArrowMenu->addAction(pAction);

	connect(m_pArrowMenu, SIGNAL(triggered(QAction*)), this, SLOT(selectAction(QAction*)));
}


void QGLESLineMapCanvas::initDispItemMenu()
{
	auto *pDM = CDataManage::GetInstance();
	m_pDispItemMenu = new QMenu("Edit Display Item", this);
	QAction *pAction;

	pAction = new QAction(pDM->m_iconEditNode, "Edit pos", this);
	pAction->setData(1);
	m_pDispItemMenu->addAction(pAction);

	pAction = new QAction(pDM->m_iconDelDispItem, "Delete", this);
	pAction->setData(2);
	m_pDispItemMenu->addAction(pAction);

	connect(m_pDispItemMenu, SIGNAL(triggered(QAction*)), this, SLOT(selectAction(QAction*)));
}


void QGLESLineMapCanvas::initTileMaps()
{
	CTileMapSupport *pTMS = CTileMapSupport::GetInstance();
	auto *pDM = CDataManage::GetInstance();
	memset(m_uConfirmedBuffer, 0, sizeof(m_uConfirmedBuffer));
	memset(m_uNodeBuffer, 0, sizeof(m_uNodeBuffer));
	auto pVEC = pDM->GET_MODEL_CLASS(LineMapLink)->getVector();
	for (auto it : (*pVEC))
	{
		LineMapLink *pItem = (LineMapLink*)it.get();
		pItem->m_tPath = pTMS->GetPath(m_nCellSize, m_nLineWidth, pItem->nItemType, pItem->nPosX, pItem->nPosY);
		pItem->m_tPolygon = pTMS->GetPolygon(m_nCellSize, m_nLineWidth, pItem->nItemType, pItem->nPosX, pItem->nPosY);
		pItem->m_tArcRect = pTMS->GetArcRect(m_nCellSize, m_nLineWidth, pItem->nItemType, pItem->nPosX, pItem->nPosY);
		afterSetPos(pItem);
	}
}


void QGLESLineMapCanvas::afterSetPos(LineMapLink *pLink)
{
	qreal angle;
	QPoint tPrev;
	int len = (qreal)pLink->m_tPath.length();
	pLink->nAngleSt;
	pLink->nAngleEn;
	pLink->m_tArcRect;
	pLink->vAngle.clear();
	pLink->vPoint.clear();
	for (int i = 0; i < len + 1; i++)
	{
		QPoint tP;
		qreal perCent = pLink->m_tPath.percentAtLength(i);
		QPointF tempVal = pLink->m_tPath.pointAtPercent(perCent);
		angle = (qreal)pLink->nAngleSt;
		angle = pLink->m_tPath.angleAtPercent(perCent) - 90.0f;//*(-1.0);

		tP.setX(qCeil(tempVal.x() + 0.5));
		tP.setY(qCeil(tempVal.y() + 0.5));

		if (tP != tPrev)
		{
			pLink->vPoint.push_back(tP);
			m_uConfirmedBuffer[tP.x()][tP.y()]++;
			pLink->vAngle.push_back(angle);
		}
		tPrev = tP;
	}

	int nNodeExists = 0;
	UINT uX, uY;
	unsigned int uValue = searchNode(pLink->vPoint.begin()->x(), pLink->vPoint.begin()->y(), &nNodeExists);
	if ((uValue != 0) && (nNodeExists != 0))
	{
		switch (nNodeExists)
		{
		case 1:
		case 2:
		case 3:
		case 4:
			uX = ((uValue >> 16) & 0xFFFF);
			uY = ((uValue) & 0xFFFF);
			pLink->vPoint.insert(pLink->vPoint.begin(), QPoint(uX, uY));
			pLink->vAngle.insert(pLink->vAngle.begin(), pLink->vAngle.front());
			break;
		}
	}
	uValue = searchNode(pLink->vPoint.rbegin()->x(), pLink->vPoint.rbegin()->y(), &nNodeExists);
	if ((uValue != 0) && (nNodeExists != 0))
	{
		switch (nNodeExists)
		{
		case 1:
		case 2:
		case 3:
		case 4:
			uX = ((uValue >> 16) & 0xFFFF);
			uY = ((uValue) & 0xFFFF);
			pLink->vPoint.push_back(QPoint(uX, uY));
			pLink->vAngle.push_back(pLink->vAngle.back());
			break;
		}
	}




	pLink->vAngleRev = pLink->vAngle;
	pLink->vPointRev = pLink->vPoint;
	reverse(pLink->vPointRev.begin(), pLink->vPointRev.end());
	reverse(pLink->vAngleRev.begin(), pLink->vAngleRev.end());


	PATHINFO tInfo;
	tInfo.pLink = pLink;
	tInfo.vPoint = &pLink->vPoint;
	tInfo.vAngle = &pLink->vAngle;


	pLink->nLinkIndex[0] = ((pLink->vPoint.begin()->x() & 0x0000FFFF) << 16) | (pLink->vPoint.begin()->y() & 0x0000FFFF);
	pLink->nLinkIndex[1] = ((pLink->vPoint.rbegin()->x() & 0x0000FFFF) << 16) | (pLink->vPoint.rbegin()->y() & 0x0000FFFF);
	m_mPath[pLink->nLinkIndex[0]][pLink->nLinkIndex[1]] = tInfo;

	tInfo.pLink = pLink;
	tInfo.vPoint = &pLink->vPointRev;
	tInfo.vAngle = &pLink->vAngleRev;

	m_mPath[pLink->nLinkIndex[1]][pLink->nLinkIndex[0]] = tInfo;


	unsigned short uStX = pLink->nLinkIndex[0] >> 16;
	unsigned short uStY = pLink->nLinkIndex[0];
	unsigned short uEnX = pLink->nLinkIndex[1] >> 16;
	unsigned short uEnY = pLink->nLinkIndex[1];

	insertBasicNode(pLink->nLinkIndex[0]);
	insertBasicNode(pLink->nLinkIndex[1]);
}

unsigned int QGLESLineMapCanvas::searchNode(unsigned short wX, unsigned short wY, int *pInt)
{
	bool bRet = false;
	unsigned int uKey = 0;
	for (int i = 0; i < 5; i++)
	{
		switch (i)
		{
		case 0:
			uKey = (((DWORD)wX & 0x0000FFFF) << 16) | (((DWORD)wY) & 0x0000FFFF);
			break;
		case 1:
			uKey = ((((DWORD)(wX + 1)) & 0x0000FFFF) << 16) | (((DWORD)wY & 0x0000FFFF));
			break;
		case 2:
			uKey = (((DWORD)wX & 0x0000FFFF) << 16) | ((((DWORD)wY + 1) & 0x0000FFFF));
			break;
		case 3:
			uKey = ((((DWORD)(wX - 1)) & 0x0000FFFF) << 16) | (((DWORD)wY & 0x0000FFFF));
			break;
		case 4:
			uKey = (((DWORD)wX & 0x0000FFFF) << 16) | ((((DWORD)(wY - 1)) & 0x0000FFFF));
			break;
		}
		(*pInt) = i;
		std::map<unsigned int, int>::iterator nit = m_mNodes.find(uKey);
		if (nit != m_mNodes.end())
		{
			return nit->first;
		}
	}
	return 0;
}


void QGLESLineMapCanvas::insertBasicNode(unsigned int nKey)
{
	bool bRet = false;
	std::map<unsigned int, int>::iterator nit = m_mNodes.find(nKey);
	if (nit == m_mNodes.end())
	{

	}
	m_mNodes[nKey]++;
}

void QGLESLineMapCanvas::deleteBasicNode(unsigned int nKey)
{
	std::map<unsigned int, int>::iterator nit = m_mNodes.find(nKey);
	if (nit != m_mNodes.end())
	{
		if (nit->second == 1)
		{
			//반복자 복사후 지우기 최종
			m_mNodes.erase(nit);
		}
		else
			m_mNodes[nKey]--;
	}
}

void QGLESLineMapCanvas::contextMenuEvent(QContextMenuEvent * e)
{
	int nOriginPosX = m_nLatestPosX = e->pos().x();
	int nOriginPosY = m_nLatestPosY = e->pos().y();

	switch (m_eEditMode)
	{
	case EDIT_TILE_MAP:
		m_pLinkMenu->popup(e->globalPos());
		break;
	case EDIT_NODE:
		if (!m_bCtrlKeyPressed)
		{
			m_nSelectedNode = -1;
			auto *pDM = CDataManage::GetInstance();
			auto pVEC = pDM->GET_MODEL_CLASS(LineMapNode)->getVector();
			for (auto it : (*pVEC))
			{
				LineMapNode *pNode = (LineMapNode*)it.get();
				QRect tRect(pNode->nPosX - 15, pNode->nPosY - 15, 30, 30);
				if (tRect.contains(nOriginPosX, nOriginPosY))
				{
					m_nSelectedNode = it.get()->GetIndex();
				}
			}
			if (setNodeActions(m_nSelectedNode, nOriginPosX, nOriginPosY))
				m_pNodeMenu->popup(e->globalPos());
		}
		break;
	case EDIT_ARROW:
	{
		m_nSelectedArrow = -1;
		auto *pDM = CDataManage::GetInstance();
		auto pVEC = pDM->GET_MODEL_CLASS(LineMapArrowTexture)->getVector();
		for (auto it : (*pVEC))
		{
			LineMapArrowTexture *pNode = (LineMapArrowTexture*)it.get();
			QRect tRect(pNode->nOffsetX, pNode->nOffsetY, pNode->nTexWidth, pNode->nTexHeight);
			if (tRect.contains(nOriginPosX, nOriginPosY))
			{
				m_nSelectedArrow = pNode->GetIndex();
				m_pArrowMenu->popup(e->globalPos());
			}
		}
	}
	break;
	case EDIT_DISPLAYITEM:
	{
		m_nSelectedDispItem = -1;
		auto *pDM = CDataManage::GetInstance();
		auto *pTM = CTableManage::GetInstance();
		auto pVEC = pDM->GET_MODEL_CLASS(LineMapDisplayItem)->getVector();

		for (auto it : (*pVEC))
		{
			auto *pItem = (LineMapDisplayItem*)it.get();
			qDebug() << "pItem->nRelatedDisplayItem:" << pItem->nRelatedDisplayItem;
			auto nit = find_if(pTM->m_vDisplayItemPool.begin(), pTM->m_vDisplayItemPool.end(),
				findDisplayItemByRelatedItem(pItem->nRelatedDisplayItem));

			if (nit != pTM->m_vDisplayItemPool.end())
			{
				auto dip = (DisplayItemPool*)nit->get();
				qDebug() << "pItem->nPosX, pItem->nPosY, dip->nWidth, dip->nHeight" << pItem->nPosX << pItem->nPosY << dip->nWidth << dip->nHeight;
				QRect tRect(pItem->nPosX, pItem->nPosY, dip->nWidth, dip->nHeight);
				qDebug() << "nOriginPosX, nOriginPosY" << nOriginPosX << nOriginPosY;
				if (tRect.contains(nOriginPosX, nOriginPosY))
				{
					m_nSelectedDispItem = pItem->GetIndex();
					qDebug() << "m_nDispItemSelected" << m_nSelectedDispItem;
					m_pDispItemMenu->popup(e->globalPos());
				}
			}

		}
	}
	}

}

void QGLESLineMapCanvas::setCurrentStationState(int nAction)
{
	if (nAction < STATION_LEFT)
		m_eCurrentStnState = STATION_LEFT;
	else if ((nAction > STATION_PASSED))
		m_eCurrentStnState = STATION_PASSED;
	else
		m_eCurrentStnState = nAction;
}

void QGLESLineMapCanvas::selectAction(QAction *action)
{
	int nValue = action->data().toInt();
	switch (m_eEditMode)
	{
	case EDIT_TILE_MAP:
		addTileBySelection((TileType)nValue, m_nLatestPosX, m_nLatestPosY);
		break;
	case EDIT_NODE:
		if (!m_bCtrlKeyPressed)
		{
			switch (nValue)
			{
			case 1:
				addNode(m_nLatestPosX, m_nLatestPosY);
				break;
			case 2:
				deleteNode(m_nSelectedNode);
				break;
			case 3:
				editNode(m_nSelectedNode);
				break;
			case 4:
				editSpot(m_nSelectedNode);
			}
		}
		break;
	case EDIT_ARROW:
		switch (nValue)
		{
		case 1:
			deleteArrow(m_nSelectedArrow);
			break;;
		}
		break;
	case EDIT_DISPLAYITEM:
		switch (nValue)
		{
		case 1:
			qDebug() << Q_FUNC_INFO << "edit" << nValue;
			editDisplayItem(m_nSelectedDispItem);
			break;
		case 2:
			qDebug() << Q_FUNC_INFO << "delete" << nValue;
			deleteDisplayItem(m_nSelectedDispItem);
		default:
			break;
		}
	default:
		break;
	}
	update();
}

void QGLESLineMapCanvas::addNode(int nPosX, int nPosY)
{
	int nMinXPos, nMinYPos;
	auto *pDM = CDataManage::GetInstance();
	if (getMinCoordFromBuffer(nPosX, nPosY, &nMinXPos, &nMinYPos))
	{
		auto pLMN = pDM->GET_MODEL_CLASS(LineMapNode)->insertRow();
		LineMapNode *p = (LineMapNode*)pLMN.get();
		p->nPosX = nMinXPos;
		p->nPosY = nMinYPos;
	}
	update();
}

void QGLESLineMapCanvas::deleteNode(int nSelectedIndex)
{
	auto *pDM = CDataManage::GetInstance();
	pDM->GET_MODEL_CLASS(LineMapNode)->removeRow(nSelectedIndex);
	update();
}

void QGLESLineMapCanvas::editSpot(int nSelectedIndex)
{
	auto *pDM = CDataManage::GetInstance();
	auto pVEC = pDM->GET_MODEL_CLASS(LineMapNode)->getVector();
	auto pit = find_if(pVEC->begin(), pVEC->end(), findSQLData(nSelectedIndex));
	if (pit != pVEC->end())
	{
		int nRow = std::distance(pVEC->begin(), pit);
		NodePropertyDlg tEdit(NodePropertyDlg::propertytype::SPOT, nRow, "Node Icon Property", this);
		if (tEdit.exec() != QDialog::Accepted)
		{

		}
	}
	update();
}

void QGLESLineMapCanvas::editNode(int nSelectedIndex)
{
	auto *pDM = CDataManage::GetInstance();
	auto pVEC = pDM->GET_MODEL_CLASS(LineMapNode)->getVector();
	auto pit = find_if(pVEC->begin(), pVEC->end(), findSQLData(nSelectedIndex));
	if (pit != pVEC->end())
	{
		int nRow = std::distance(pVEC->begin(), pit);
		NodePropertyDlg tEdit(NodePropertyDlg::propertytype::NODE, nRow, "Node Name Property", this);
		if (tEdit.exec() != QDialog::Accepted)
		{

		}
	}
	update();
}

void QGLESLineMapCanvas::editDisplayItem(int idx)
{
	/*
	참고링크
	https://stackoverflow.com/questions/17512542/getting-multiple-inputs-from-qinputdialog-in-qtcreator
	*/

	auto *pDM = CDataManage::GetInstance();
	auto pVEC = pDM->GET_MODEL_CLASS(LineMapDisplayItem)->getVector();
	auto pit = find_if(pVEC->begin(), pVEC->end(), findSQLData(idx));
	if (pit != pVEC->end())
	{
		auto *pItem = (LineMapDisplayItem*)pit->get();


		int nRow = std::distance(pVEC->begin(), pit);
		qDebug() << nRow;

		QDialog dialog(this);
		dialog.setWindowTitle("Edit Display Item Position");

		// Use a layout allowing to have a label next to each field
		QFormLayout form(&dialog);

		auto spinX = new QSpinBox(&dialog);
		auto spinY = new QSpinBox(&dialog);

		spinX->setRange(-10000, 10000);
		spinY->setRange(-10000, 10000);

		spinX->setValue(pItem->nPosX);
		spinY->setValue(pItem->nPosY);

		form.addRow("X :", spinX);
		form.addRow("Y :", spinY);

		// Add some standard buttons (Cancel/Ok) at the bottom of the dialog
		QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
			Qt::Horizontal, &dialog);

		form.addRow(&buttonBox);

		QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
		QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

		// Show the dialog as modal
		if (dialog.exec() == QDialog::Accepted)
		{
			// If the user didn't dismiss the dialog, do something with the fields
			qDebug() << spinX->value() << "---" << spinY->value();
			pItem->nPosX = spinX->value();
			pItem->nPosY = spinY->value();
		}
		m_bPressed = false;
		m_nSelectedDispItem = -1;
	}
	update();
}

void QGLESLineMapCanvas::deleteArrow(int nSelectedIndex)
{
	auto *pDM = CDataManage::GetInstance();
	pDM->GET_MODEL_CLASS(LineMapArrowTexture)->removeRow(nSelectedIndex);
	update();
}

void QGLESLineMapCanvas::deleteDisplayItem(int nIdx)
{
	auto *pDM = CDataManage::GetInstance();
	pDM->GET_MODEL_CLASS(LineMapDisplayItem)->removeRow(nIdx);
	update();
}

void QGLESLineMapCanvas::resetPos(LineMapLink *pLink)
{
	unsigned __int64 uKey;
	std::vector<QPoint>::iterator nit;
	for (nit = pLink->vPoint.begin(); nit != pLink->vPoint.end(); nit++)
	{
		if (m_uConfirmedBuffer[nit->x()][nit->y()])
			m_uConfirmedBuffer[nit->x()][nit->y()]--;
	}
	std::map<unsigned int, std::map<unsigned int, PATHINFO>>::iterator mit;
	std::map<unsigned int, PATHINFO>::iterator sit;
	mit = m_mPath.find(pLink->nLinkIndex[0]);
	if (mit != m_mPath.end())
	{
		sit = mit->second.find(pLink->nLinkIndex[1]);
		if (sit != mit->second.end())
		{
			mit->second.erase(sit);
		}
	}


	mit = m_mPath.find(pLink->nLinkIndex[1]);
	if (mit != m_mPath.end())
	{
		sit = mit->second.find(pLink->nLinkIndex[0]);
		if (sit != mit->second.end())
		{
			mit->second.erase(sit);
		}
	}
	deleteBasicNode(pLink->nLinkIndex[0]);
	deleteBasicNode(pLink->nLinkIndex[1]);
}


bool QGLESLineMapCanvas::getMinCoordFromBuffer(int nXPosRef, int nYPosRef, int *pXPos, int *pYPos)
{
	auto *pDM = CDataManage::GetInstance();
	int nLeftBound = nXPosRef - 20;
	int nTopBound = nYPosRef - 20;
	//하한 설정
	nLeftBound = (nLeftBound < 0) ? 0 : nLeftBound;
	nTopBound = (nTopBound < 0) ? 0 : nTopBound;
	//상한 설정
	//nLeftBound=(nLeftBound<0)?0:nLeftBound;
	//nTopBound=(nTopBound<0)?0:nTopBound;
	(*pYPos) = (*pXPos) = 0;
	double dMin = 9999999.0;
	bool bFound = false;
	for (int j = nTopBound; j < (nTopBound + 40); j++)
	{
		for (int i = nLeftBound; i < (nLeftBound + 40); i++)
		{
			if (m_uConfirmedBuffer[i][j])
			{
				double dX = pow((double)nXPosRef - (double)i, (double)2);
				double dY = pow((double)nYPosRef - (double)j, (double)2);
				double dDistance = sqrt(dX + dY);
				dMin = min(dDistance, dMin);
				if (dMin == dDistance)
				{
					bFound = true;
					(*pXPos) = i;
					(*pYPos) = j;
				}
			}
		}
	}
	return bFound;
}




void QGLESLineMapCanvas::addTileBySelection(TileType tAddTile, int nPosX, int nPosY)
{
	int nIndex;
	bool bDeleted = false;
	auto *pDM = CDataManage::GetInstance();
	int nCurX = (int)(nPosX / m_nCellSize)*m_nCellSize + (m_nCellSize / 2);
	int nCurY = (int)(nPosY / m_nCellSize)*m_nCellSize + (m_nCellSize / 2);
	auto pVEC = pDM->GET_MODEL_CLASS(LineMapLink)->getVector();
	std::vector<int> vListDeleted;
	for (auto it : (*pVEC))
	{
		LineMapLink *pItem = (LineMapLink*)it.get();
		if ((nCurX == pItem->nPosX) && (nCurY == pItem->nPosY) && (tAddTile != pItem->nItemType))
		{
			switch (tAddTile)
			{
			case TILE_NONE:
			case TILE_C_LU:
			case TILE_C_LD:
			case TILE_C_RD:
			case TILE_C_RU:
			case TILE_F_UD:
			case TILE_F_LR:
			case TILE_CROSS:
			case TILE_F_UD_H_L:
			case TILE_F_UD_H_R:
			case TILE_F_LR_H_U:
			case TILE_F_LR_H_D:
				vListDeleted.push_back(it.get()->GetIndex());
				resetPos(pItem);
				bDeleted = true;
				break;
			default:
				break;
			}
			if (!bDeleted)
			{
				switch (pItem->nItemType)
				{
				case TILE_H_U:
				case TILE_H_D:
				case TILE_H_L:
				case TILE_H_R:
					break;
				default:
					vListDeleted.push_back(it.get()->GetIndex());
					resetPos(pItem);
					break;
				}
			}
		}
	}

	for (auto it : vListDeleted)
	{
		pDM->GET_MODEL_CLASS(LineMapLink)->removeRow(it);
	}

	if (TILE_NONE != tAddTile)
	{
		switch (tAddTile)
		{
		case TILE_F_UD:
			addLink(TILE_H_U, nCurX, nCurY);
			addLink(TILE_H_D, nCurX, nCurY);
			break;
		case TILE_F_LR:
			addLink(TILE_H_L, nCurX, nCurY);
			addLink(TILE_H_R, nCurX, nCurY);
			break;
		case TILE_CROSS:
			addLink(TILE_H_U, nCurX, nCurY);
			addLink(TILE_H_D, nCurX, nCurY);
			addLink(TILE_H_L, nCurX, nCurY);
			addLink(TILE_H_R, nCurX, nCurY);
			break;
		case TILE_F_UD_H_L:
			addLink(TILE_H_U, nCurX, nCurY);
			addLink(TILE_H_D, nCurX, nCurY);
			addLink(TILE_H_L, nCurX, nCurY);
			break;
		case TILE_F_UD_H_R:
			addLink(TILE_H_U, nCurX, nCurY);
			addLink(TILE_H_D, nCurX, nCurY);
			addLink(TILE_H_R, nCurX, nCurY);
			break;
		case TILE_F_LR_H_U:
			addLink(TILE_H_L, nCurX, nCurY);
			addLink(TILE_H_R, nCurX, nCurY);
			addLink(TILE_H_U, nCurX, nCurY);
			break;
		case TILE_F_LR_H_D:
			addLink(TILE_H_L, nCurX, nCurY);
			addLink(TILE_H_R, nCurX, nCurY);
			addLink(TILE_H_D, nCurX, nCurY);
			break;
		default:
			addLink(tAddTile, nCurX, nCurY);
			break;
		}
	}
	update();
}


void QGLESLineMapCanvas::addLink(int nTile, int nX, int nY)
{
	auto *pDM = CDataManage::GetInstance();
	CTileMapSupport *pTMS = CTileMapSupport::GetInstance();
	int nRowCount = pDM->GET_MODEL_CLASS(LineMapLink)->rowCount();
	auto pLML = pDM->GET_MODEL_CLASS(LineMapLink)->insertRow();
	LineMapLink *pLM = (LineMapLink*)pLML.get();
	pLM->m_tPath = pTMS->GetPath(m_nCellSize, m_nLineWidth, nTile, nX, nY);
	pLM->m_tPolygon = pTMS->GetPolygon(m_nCellSize, m_nLineWidth, nTile, nX, nY);
	pLM->m_tArcRect = pTMS->GetArcRect(m_nCellSize, m_nLineWidth, nTile, nX, nY);
	pTMS->GetAngles(nTile, &pLM->nAngleSt, &pLM->nAngleEn);
	pLM->nItemType = nTile;
	pLM->nPosX = nX;
	pLM->nPosY = nY;
	afterSetPos(pLM);
}

void QGLESLineMapCanvas::keyPressEvent(QKeyEvent * event)
{
	auto *pDM = CDataManage::GetInstance();
	switch (m_eEditMode)
	{
	case EDIT_NODE:
		switch (event->key())
		{
		case Qt::Key_Control:
			m_bCtrlKeyPressed = true;
			break;
		case Qt::Key_A:
			if (m_bCtrlKeyPressed)
			{
				//Aligning code here;
				alignNodes();
				m_vSelNodes.clear();
			}
			break;
		}
		update();
		break;
	}
}

void QGLESLineMapCanvas::keyReleaseEvent(QKeyEvent * event)
{
	auto *pDM = CDataManage::GetInstance();
	switch (m_eEditMode)
	{
	case EDIT_NODE:
		switch (event->key())
		{
		case Qt::Key_Control:
			m_bCtrlKeyPressed = false;
			break;
		case Qt::Key_A:
			if (m_bCtrlKeyPressed)
			{
				//Aligning code here;
				//alignNodes();
				//m_vSelNodes.clear();
			}
			break;
		}
		update();
		break;
	case EDIT_DISPLAYITEM:
		break;
	}
}

bool QGLESLineMapCanvas::setNodeActions(int nSelectedNode, int nPosX, int nPosY)
{
	int nMinXPos, nMinYPos;
	QList<QAction*> lAction = m_pNodeMenu->actions();
	QList<QAction*>::iterator vit;
	if (nSelectedNode != -1)
	{
		for (vit = lAction.begin(); vit != lAction.end(); vit++)
		{
			switch ((*vit)->data().toInt())
			{
			case 1:
				(*vit)->setEnabled(false);
				break;
			case 2:
				(*vit)->setEnabled(true);
				break;
			default:
				break;
			}
		}
		return true;
	}
	else
	{
		if (getMinCoordFromBuffer(nPosX, nPosY, &nMinXPos, &nMinYPos))
		{
			for (vit = lAction.begin(); vit != lAction.end(); vit++)
			{
				switch ((*vit)->data().toInt())
				{
				case 1:
					(*vit)->setEnabled(true);
					break;
				case 2:
					(*vit)->setEnabled(false);
					break;
				default:
					break;
				}
			}
			return true;
		}
	}
	return false;
}

void QGLESLineMapCanvas::realignNodes()
{
	std::vector<QPoint> vTmpPoint;
	std::vector<qreal> vTmpAngle;
	auto *pDM = CDataManage::GetInstance();
	ZeroMemory(m_uNodeBuffer, sizeof(m_uNodeBuffer));
	for (auto it : (*(pDM->GET_MODEL_CLASS(LineMapNode)->getVector())))
	{
		LineMapNode *pItem = (LineMapNode*)it.get();
		m_uNodeBuffer[pItem->nPosX][pItem->nPosY] = 10;
	}
	std::vector<PATHINFO> vPathInfo;
	m_mConfirmedPath.clear();
	m_mConfirmedNodes.clear();
	CONFIRMEDPATH tPath;
	unsigned int uStIndex, uEnIndex, uFinalIndex;

	for (auto tit : m_mPath)
	{
		for (auto sit : tit.second)
		{
			auto itp = sit.second.vPoint->begin();
			auto itr = sit.second.vAngle->begin();
			vTmpPoint.clear();
			vTmpAngle.clear();

			tPath.nItemType = sit.second.pLink->nItemType;
			tPath.tRect = sit.second.pLink->m_tArcRect;

			uStIndex = ((itp->x() & 0x0000FFFF) << 16) | (itp->y() & 0x0000FFFF);
			while ((itp != sit.second.vPoint->end()) && (itr != sit.second.vAngle->end()))
			{
				vTmpPoint.push_back(*itp);
				vTmpAngle.push_back(*itr);
				if ((itp != sit.second.vPoint->begin()) && (itp != (sit.second.vPoint->begin() + sit.second.vPoint->size())))
				{
					if (m_uNodeBuffer[itp->x()][itp->y()] == 10)
					{
						tPath.vPoint = vTmpPoint;
						tPath.vAngle = vTmpAngle;
						uEnIndex = ((itp->x() & 0x0000FFFF) << 16) | (itp->y() & 0x0000FFFF);
						m_mConfirmedPath[uStIndex][uEnIndex] = tPath;
						vTmpPoint.erase(vTmpPoint.begin(), vTmpPoint.begin() + vTmpPoint.size() - 1);
						vTmpAngle.erase(vTmpAngle.begin(), vTmpAngle.begin() + vTmpAngle.size() - 1);
						uStIndex = uEnIndex;
					}
				}
				uFinalIndex = ((itp->x() & 0x0000FFFF) << 16) | (itp->y() & 0x0000FFFF);
				itp++;
				itr++;
			}
			tPath.vPoint = vTmpPoint;
			tPath.vAngle = vTmpAngle;
			m_mConfirmedPath[uStIndex][uFinalIndex] = tPath;
		}
	}

	for (auto it : m_mConfirmedPath)
	{
		m_mConfirmedNodes[it.first]++;
		for (auto subit : it.second)
		{
			m_mConfirmedNodes[subit.first]++;
		}
	}
}


void QGLESLineMapCanvas::alignNodes()
{
	QPoint ptPrev;
	bool bBegin = false;
	int nOffset, nCount = 0;
	unsigned int uStart, uEnd;
	std::vector<QPoint> vTempPoint;
	std::vector<unsigned int> vTempBuffer;
	std::map<unsigned int, std::vector<int>> mMap;
	std::vector<std::shared_ptr<CSQLData>> vTempNode;

	if (m_vSelNodes.size())
	{
		uStart = m_vSelNodes.at(0);
		auto tmit = ++m_vSelNodes.begin();

		for (; tmit != m_vSelNodes.end(); tmit++)
		{
			uEnd = (*tmit);
			CalcShortestPath(uStart, uEnd, vTempBuffer);
			uStart = (*tmit);
		}

		uStart = m_vSelNodes.at(0);

		for (auto mit : m_mPath)
		{
			mit.first;
			mit.second;
			unsigned short uStX = uStart >> 16;
			unsigned short uStY = uStart;
			unsigned short uEnX = uEnd >> 16;
			unsigned short uEnY = uEnd;
		}
		auto vit = ++vTempBuffer.begin();
		for (; vit != vTempBuffer.end(); vit++)
		{
			uEnd = (*vit);
			unsigned short uStX = uStart >> 16;
			unsigned short uStY = uStart;
			unsigned short uEnX = uEnd >> 16;
			unsigned short uEnY = uEnd;
			if (m_mPath[uStart][uEnd].vPoint->size())
			{
				nOffset = (ptPrev == m_mPath[uStart][uEnd].vPoint->at(0)) ? 1 : 0;
				vTempPoint.insert(vTempPoint.end(), m_mPath[uStart][uEnd].vPoint->begin() + nOffset, m_mPath[uStart][uEnd].vPoint->end());
				ptPrev = (*vTempPoint.rbegin());
			}
			uStart = uEnd;
		}

		//Initialize Node Buffer;
		auto *pDM = CDataManage::GetInstance();
		auto pvNode = pDM->GET_MODEL_CLASS(LineMapNode)->getVector();
		for (auto nit : (*pvNode))
		{
			LineMapNode *pItem = (LineMapNode*)nit.get();
			unsigned long nKey = MAKECOORDKEY((WORD)pItem->nPosX, (WORD)pItem->nPosY);
			mMap[nKey].push_back(pItem->GetIndex());
		}

		int nOffsetFront = 0;
		int nOffsetRear = 0;
		bool bFindFront = false;
		for (auto kit = vTempPoint.begin(); kit != vTempPoint.end(); kit++)
		{
			unsigned long nKey = MAKECOORDKEY((WORD)kit->x(), (WORD)kit->y());
			auto mit = mMap.find(nKey);
			if (mit != mMap.end())
			{
				for (auto xit : mit->second)
				{
					auto pit = find_if(pvNode->begin(), pvNode->end(), findSQLData(xit));
					if (pit != pvNode->end())
					{
						nOffsetRear = std::distance(vTempPoint.begin(), kit);
						if (!bFindFront)
						{
							nOffsetFront = nOffsetRear;
							bFindFront = true;
						}
						vTempNode.push_back((*pit));
					}
				}
			}
		}

		nOffsetFront--;
		nOffsetRear++;

		//Trimming from both tail.
		if (nOffsetRear <= vTempPoint.size())
			vTempPoint.erase(vTempPoint.begin() + nOffsetRear, vTempPoint.end());

		if (nOffsetFront >= 0)
			vTempPoint.erase(vTempPoint.begin(), vTempPoint.begin() + nOffsetFront);

		float fOffset = (float)(vTempPoint.size() - vTempNode.size()) / (float)(vTempNode.size() - 1);
		fOffset += 1.0f;
		float fCurPos = 0;

		for (auto pit : vTempNode)
		{
			LineMapNode *pItem = (LineMapNode*)pit.get();
			int nPos = (int)fCurPos;
			pItem->nPosX = vTempPoint.at(nPos).x();
			pItem->nPosY = vTempPoint.at(nPos).y();
			fCurPos += fOffset;

			if (pItem->GetRecordState() == EDIT_NOT_MODIFIED)
				pItem->SetRecordState(EDIT_UPDATED);
		}
	}
	update();
}



bool QGLESLineMapCanvas::CalcShortestPath(unsigned int nBegin, unsigned int nEnd, std::vector<unsigned int> &vString)
{
	bool bVisit = false; int min;
	unsigned strNow = nBegin, strMin;

	std::map<unsigned int, int> mValue;
	std::map<unsigned int, int> mVisited;
	std::map<unsigned int, unsigned int> mIndex;

	for (auto stit : m_mNodes)	//초기화
	{
		mVisited[stit.first] = 0;
		mValue[stit.first] = 99999;
		mIndex[stit.first] = 0;
	}

	mValue[nBegin] = 0;	//가중치가 가장 작은 경로

	for (auto stit : m_mNodes)
	{
		min = 99999;
		for (auto vvit : mValue)
		{
			if ((vvit.second < min) && (!mVisited[vvit.first]))
			{
				min = vvit.second;
				strNow = vvit.first;
			}
		}
		mVisited[strNow] = 1;
		auto wnit = m_mPath.find(strNow);
		if (wnit != m_mPath.end())
		{
			for (auto vnit : wnit->second)
			{
				if (mValue[vnit.first] > (mValue[strNow] + vnit.second.vAngle->size()))
				{
					mValue[vnit.first] = mValue[strNow] + vnit.second.vAngle->size();
					mIndex[vnit.first] = strNow;
				}
			}
		}
	}



	std::vector<unsigned int> tmpString;
	auto nit = mValue.find(nEnd);
	if ((nit != mValue.end()) && (nit->second < 99999))
	{
		strNow = nit->first;
		tmpString.push_back(strNow);
		while ((mIndex.find(strNow) != mIndex.end()) && (mIndex.find(strNow)->second))
		{
			strNow = mIndex[strNow];
			tmpString.push_back(strNow);
		}
		reverse(tmpString.begin(), tmpString.end());

		if (vString.size() && ((*vString.rbegin()) == (*tmpString.begin())))
		{
			tmpString.erase(tmpString.begin());
		}
		vString.insert(vString.end(), tmpString.begin(), tmpString.end());
		return true;
	}
	return false;
}


bool QGLESLineMapCanvas::CalcShortestPathForConfirmed(unsigned int nBegin, unsigned int nEnd, std::vector<unsigned int> &vString)
{
	bool bVisit = false; int min;
	unsigned strNow = nBegin, strMin;
	std::map<unsigned int, std::map<unsigned int, CONFIRMEDPATH>>::iterator wnit;
	std::map<unsigned int, CONFIRMEDPATH>::iterator vnit;
	std::map<unsigned int, int>::iterator vvit;

	std::map<unsigned int, int> mValue;
	std::map<unsigned int, int> mVisited;

	std::map<unsigned int, int>::iterator stit;
	std::map<unsigned int, int>::iterator nit;
	std::map<unsigned int, unsigned int> mIndex;

	for (auto stit : m_mConfirmedNodes)	//초기화
	{
		mVisited[stit.first] = 0;
		mValue[stit.first] = 99999;
		mIndex[stit.first] = 0;
	}

	mValue[nBegin] = 0;	//가중치가 가장 작은 경로




	for (auto stit : m_mConfirmedNodes)
	{
		min = 99999;
		for (auto vvit : mValue)
		{
			if ((vvit.second < min) && (!mVisited[vvit.first]))
			{
				min = vvit.second;
				strNow = vvit.first;
			}
		}
		mVisited[strNow] = 1;
		wnit = m_mConfirmedPath.find(strNow);
		if (wnit != m_mConfirmedPath.end())
		{
			for (auto vnit : wnit->second)
			{
				if (mValue[vnit.first] > (mValue[strNow] + vnit.second.vAngle.size()))
				{
					mValue[vnit.first] = mValue[strNow] + vnit.second.vAngle.size();
					mIndex[vnit.first] = strNow;
				}
			}
		}
	}

	std::vector<unsigned int> tmpString;
	nit = mValue.find(nEnd);
	if ((nit != mValue.end()) && (nit->second < 99999))
	{
		strNow = nit->first;
		tmpString.push_back(strNow);
		while ((mIndex.find(strNow) != mIndex.end()) && (mIndex.find(strNow)->second))
		{
			strNow = mIndex[strNow];
			tmpString.push_back(strNow);
		}
		reverse(tmpString.begin(), tmpString.end());

		if (vString.size() && ((*vString.rbegin()) == (*tmpString.begin())))
		{
			tmpString.erase(tmpString.begin());
		}
		vString.insert(vString.end(), tmpString.begin(), tmpString.end());
		return true;
	}
	return false;
}



void QGLESLineMapCanvas::generateArrowFrom(unsigned short wStX, unsigned short wStY, unsigned short wEnX, unsigned short wEnY, int nBeginTrim, int nEndTrim, float fPenWidth)
{
	wchar_t szBuffer[256];
	std::vector<unsigned int> vSelNodes;
	std::vector<unsigned int>::reverse_iterator rsit, rpit;
	unsigned int uStart = MAKECOORDKEY(wStX, wStY);
	unsigned int uEnd = MAKECOORDKEY(wEnX, wEnY);
	CalcShortestPathForConfirmed(uStart, uEnd, vSelNodes);
	using namespace Gdiplus;
	bool bBegin = false;
	Gdiplus::Point tPtLineSt, tPtLineEn, tPtLinkSt, tPtLinkEn;
	Gdiplus::GraphicsPath tPath, tLinePath, tArcPath;
	Gdiplus::REAL fStartAngle;
	Gdiplus::REAL fSweepAngle;
	Gdiplus::Rect tArcRect;
	Gdiplus::Matrix tMat;
	int nPrevItem = TILE_NONE;

	int nPrev;
	int nTotalBufferCount = 0;
	for (auto nCur : vSelNodes)
	{
		if (bBegin)
		{
			nTotalBufferCount += m_mConfirmedPath[nPrev][nCur].vPoint.size();
		}
		bBegin = true;
		nPrev = nCur;
	}
	if (nTotalBufferCount > (nBeginTrim + nEndTrim))
	{
		int nTrimCount = nBeginTrim, nDiff = 0, nBeginOffset = 0, nEndOffset = 0;
		bBegin = false;
		auto sit = vSelNodes.begin();
		auto pit = sit;
		while (nTrimCount)
		{
			if (bBegin)
			{
				nDiff = nTrimCount - m_mConfirmedPath[(*pit)][(*sit)].vPoint.size();
				if (nDiff < 0)
				{
					nBeginOffset = nTrimCount;
					nTrimCount = 0;
				}
				else
				{
					sit = vSelNodes.erase(pit);
					nBeginOffset = nTrimCount = nDiff;
				}
			}
			bBegin = true;
			pit = sit++;
		}

		nTrimCount = nEndTrim;
		bBegin = false;

		rsit = vSelNodes.rbegin();
		while (nTrimCount)
		{
			if (bBegin)
			{
				nDiff = nTrimCount - m_mConfirmedPath[(*rsit)][(*rpit)].vPoint.size();
				if (nDiff < 0)
				{
					nEndOffset = nTrimCount;
					nTrimCount = 0;
				}
				else
				{
					vSelNodes.erase(vSelNodes.begin() + vSelNodes.size() - 1);
					rsit = vSelNodes.rbegin();
					nEndOffset = nTrimCount = nDiff;
				}
			}
			bBegin = true;
			rpit = rsit++;
		}

		bBegin = false;


		std::vector<QPoint> vTmpPoint;
		std::vector<QPoint>::iterator stit, enit;
		rsit = vSelNodes.rbegin();


		Gdiplus::Pen P2(Gdiplus::Color::White, fPenWidth);
		P2.SetLineJoin(Gdiplus::LineJoin::LineJoinRound);

		Gdiplus::Pen P3(Color(255, 204, 0), fPenWidth);
		P3.SetLineJoin(Gdiplus::LineJoin::LineJoinRound);
		P3.SetStartCap(Gdiplus::LineCap::LineCapDiamondAnchor);
		P3.SetEndCap(Gdiplus::LineCap::LineCapArrowAnchor); // arrow shape, jkc

		// original
		//Gdiplus::Pen P3(Gdiplus::Color::White, fPenWidth);
		//P3.SetLineJoin(Gdiplus::LineJoin::LineJoinRound);
		//P3.SetEndCap(Gdiplus::LineCap::LineCapArrowAnchor); // arrow shape, jkc

		tPath.SetFillMode(Gdiplus::FillModeWinding);


		for (sit = vSelNodes.begin(); sit != vSelNodes.end(); sit++)
		{
			if (bBegin)
			{

				switch (m_mConfirmedPath[(*pit)][(*sit)].nItemType)
				{
				case TILE_H_U:
				case TILE_H_D:
					if ((nPrevItem == TILE_NONE) || (nPrevItem == TILE_C_LU) || (nPrevItem == TILE_C_LD) || (nPrevItem == TILE_C_RD) || (nPrevItem == TILE_C_RU))
					{
						if (sit == (vSelNodes.begin() + 1))
						{
							stit = m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin() + nBeginOffset;
							tPtLineSt.X = (m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin() + nBeginOffset)->x();
							tPtLineSt.Y = (m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin() + nBeginOffset)->y();
						}
						else
						{
							if ((nPrevItem == TILE_C_LU) || (nPrevItem == TILE_C_LD) || (nPrevItem == TILE_C_RD) || (nPrevItem == TILE_C_RU))
							{
								tArcPath.Widen(&P2);
								tArcPath.Outline();
								tPath.AddPath(&tArcPath, true);
								tArcPath.Reset();
							}
							stit = m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin();
							tPtLineSt.X = m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()->x();
							tPtLineSt.Y = m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()->y();
						}
						if ((*sit) == (*vSelNodes.rbegin()))
						{
							enit = m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin() + (m_mConfirmedPath[(*pit)][(*sit)].vPoint.size() - nEndOffset - 1);
							tPtLineEn.X = (m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin() + nEndOffset)->x();
							tPtLineEn.Y = (m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin() + nEndOffset)->y();
						}
						else
						{
							enit = m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin() + m_mConfirmedPath[(*pit)][(*sit)].vPoint.size() - 1;
							tPtLineEn.X = m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()->x();
							tPtLineEn.Y = m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()->y();
						}
					}
					else if ((nPrevItem == TILE_H_D) || (nPrevItem == TILE_H_U))
					{
						stit = m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin();
						if ((*sit) == (*vSelNodes.rbegin()))
						{
							enit = m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin() + (m_mConfirmedPath[(*pit)][(*sit)].vPoint.size() - nEndOffset - 1);
							tPtLineEn.X = (m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin() + nEndOffset)->x();
							tPtLineEn.Y = (m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin() + nEndOffset)->y();
						}
						else
						{
							enit = m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin() + m_mConfirmedPath[(*pit)][(*sit)].vPoint.size() - 1;
							tPtLineEn.X = m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()->x();
							tPtLineEn.Y = m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()->y();
						}
					}
					else
					{
						tLinePath.AddLine(tPtLineSt, tPtLineEn);
						stit = m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin();
						tPtLineSt.X = m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()->x();
						tPtLineSt.Y = m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()->y();
						if ((*sit) == (*vSelNodes.rbegin()))
						{
							enit = m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin() + (m_mConfirmedPath[(*pit)][(*sit)].vPoint.size() - nEndOffset - 1);
							tPtLineEn.X = (m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin() + nEndOffset)->x();
							tPtLineEn.Y = (m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin() + nEndOffset)->y();
						}
						else
						{
							enit = m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin() + m_mConfirmedPath[(*pit)][(*sit)].vPoint.size() - 1;
							tPtLineEn.X = m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()->x();
							tPtLineEn.Y = m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()->y();
						}
					}
					vTmpPoint.insert(vTmpPoint.end(), stit, enit);
					break;
				case TILE_H_L:
				case TILE_H_R:
					if ((nPrevItem == TILE_NONE) || (nPrevItem == TILE_C_LU) || (nPrevItem == TILE_C_LD) || (nPrevItem == TILE_C_RD) || (nPrevItem == TILE_C_RU))
					{
						if (sit == (vSelNodes.begin() + 1))
						{
							stit = m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin() + nBeginOffset;
							tPtLineSt.X = (m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin() + nBeginOffset)->x();
							tPtLineSt.Y = (m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin() + nBeginOffset)->y();
						}
						else
						{
							if ((nPrevItem == TILE_C_LU) || (nPrevItem == TILE_C_LD) || (nPrevItem == TILE_C_RD) || (nPrevItem == TILE_C_RU))
							{
								tArcPath.Widen(&P2);
								tArcPath.Outline();
								tPath.AddPath(&tArcPath, true);
								tArcPath.Reset();
							}
							stit = m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin();
							tPtLineSt.X = m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()->x();
							tPtLineSt.Y = m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()->y();
						}
						if ((*sit) == (*vSelNodes.rbegin()))
						{
							enit = m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin() + (m_mConfirmedPath[(*pit)][(*sit)].vPoint.size() - nEndOffset - 1);
							tPtLineEn.X = (m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin() + nEndOffset)->x();
							tPtLineEn.Y = (m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin() + nEndOffset)->y();
						}
						else
						{
							enit = m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin() + m_mConfirmedPath[(*pit)][(*sit)].vPoint.size() - 1;
							tPtLineEn.X = m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()->x();
							tPtLineEn.Y = m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()->y();
						}
					}
					else if ((nPrevItem == TILE_H_L) || (nPrevItem == TILE_H_R))
					{
						stit = m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin();
						if ((*sit) == (*vSelNodes.rbegin()))
						{
							enit = m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin() + (m_mConfirmedPath[(*pit)][(*sit)].vPoint.size() - nEndOffset - 1);
							tPtLineEn.X = (m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin() + nEndOffset)->x();
							tPtLineEn.Y = (m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin() + nEndOffset)->y();
						}
						else
						{
							enit = m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin() + m_mConfirmedPath[(*pit)][(*sit)].vPoint.size() - 1;
							tPtLineEn.X = m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()->x();
							tPtLineEn.Y = m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()->y();
						}
					}
					else
					{
						tLinePath.AddLine(tPtLineSt, tPtLineEn);

						stit = m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin();
						tPtLineSt.X = m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()->x();
						tPtLineSt.Y = m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()->y();
						if ((*sit) == (*vSelNodes.rbegin()))
						{
							enit = m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin() + (m_mConfirmedPath[(*pit)][(*sit)].vPoint.size() - nEndOffset - 1);
							tPtLineEn.X = (m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin() + nEndOffset)->x();
							tPtLineEn.Y = (m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin() + nEndOffset)->y();
						}
						else
						{
							enit = m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin() + m_mConfirmedPath[(*pit)][(*sit)].vPoint.size() - 1;
							tPtLineEn.X = m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()->x();
							tPtLineEn.Y = m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()->y();
						}
					}
					vTmpPoint.insert(vTmpPoint.end(), stit, enit);
					break;
				case TILE_C_LU:
				case TILE_C_LD:
				case TILE_C_RD:
				case TILE_C_RU:

					if ((nPrevItem == TILE_H_U) || (nPrevItem == TILE_H_D) || (nPrevItem == TILE_H_L) || (nPrevItem == TILE_H_R))
					{
						Gdiplus::GraphicsPath *pTmpPath;
						tLinePath.AddLine(tPtLineSt, tPtLineEn);
						pTmpPath = tLinePath.Clone();;
						pTmpPath->Widen(&P2);
						pTmpPath->Outline();
						tPath.AddPath(pTmpPath, true);
						tLinePath.Reset();
					}

					tArcRect = Gdiplus::Rect(m_mConfirmedPath[(*pit)][(*sit)].tRect.x(), m_mConfirmedPath[(*pit)][(*sit)].tRect.y(), m_mConfirmedPath[(*pit)][(*sit)].tRect.width(), m_mConfirmedPath[(*pit)][(*sit)].tRect.height());
					tArcRect.Offset(1, 1);
					if (sit == (vSelNodes.begin() + 1))
					{
						stit = m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin() + nBeginOffset;
						fStartAngle = (*(m_mConfirmedPath[(*pit)][(*sit)].vAngle.begin() + nBeginOffset));
						tPtLinkEn = Gdiplus::Point(stit->x(), stit->y());
					}
					else
					{
						stit = m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin();
						fStartAngle = (*m_mConfirmedPath[(*pit)][(*sit)].vAngle.begin());
						tPtLinkEn = Gdiplus::Point(stit->x(), stit->y());
					}
					tPtLineSt = tPtLineEn;
					if ((*sit) == (*vSelNodes.rbegin()))
					{

						enit = m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin() + (m_mConfirmedPath[(*pit)][(*sit)].vPoint.size() - nEndOffset - 1);
						fSweepAngle = ((*(m_mConfirmedPath[(*pit)][(*sit)].vAngle.rbegin() + nEndOffset)) - fStartAngle);
					}
					else
					{
						enit = m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin() + m_mConfirmedPath[(*pit)][(*sit)].vPoint.size() - 1;
						fSweepAngle = (*m_mConfirmedPath[(*pit)][(*sit)].vAngle.rbegin()) - fStartAngle;
					}



					tArcPath.AddArc(tArcRect, -fStartAngle, -fSweepAngle);
					if ((*sit) == (*vSelNodes.rbegin()))
					{
						tArcPath.Widen(&P3);
						tArcPath.Outline();
						tPath.AddPath(&tArcPath, true);
						tArcPath.Reset();
					}
					vTmpPoint.insert(vTmpPoint.end(), stit, enit);
					break;
				default:
					break;
				}
				nPrevItem = m_mConfirmedPath[(*pit)][(*sit)].nItemType;
			}
			bBegin = true;
			pit = sit;
		}

		if ((nPrevItem == TILE_H_U) || (nPrevItem == TILE_H_D) || (nPrevItem == TILE_H_L) || (nPrevItem == TILE_H_R))
		{
			Gdiplus::GraphicsPath *pTmpPath;
			tLinePath.AddLine(tPtLineSt, tPtLineEn);
			pTmpPath = tLinePath.Clone();;
			pTmpPath->Widen(&P3);
			pTmpPath->Outline();
			tPath.AddPath(pTmpPath, true);
		}



		Gdiplus::Rect tRect;


		tPath.GetBounds(&tRect);
		tRect.Inflate(10.f, 10.f);

		Gdiplus::Pen P(Gdiplus::Color::White, 1.0f);
		Gdiplus::Bitmap *pBitmap = new Gdiplus::Bitmap(tRect.X + tRect.Width, tRect.Y + tRect.Height, PixelFormat32bppARGB);
		Gdiplus::Graphics G(pBitmap);
		G.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
		//G.FillRectangle(&SolidBrush(Color(0, 255, 255, 255)), Gdiplus::Rect(0,0,tRect.X + tRect.Width,tRect.Y + tRect.Height));
		G.DrawPath(&P, &tPath);
		G.FillPath(&Gdiplus::SolidBrush(Gdiplus::Color::White), &tPath);
		Gdiplus::BitmapData* bitmapData = new Gdiplus::BitmapData;
		auto pByte = std::shared_ptr<unsigned char>((unsigned char*)malloc(((UINT)tRect.Width*(UINT)tRect.Height * 4)), free);
		UINT *pDst = (UINT*)pByte.get();
		tRect.Inflate(-5.f, -5.f);
		pBitmap->LockBits(&tRect, Gdiplus::ImageLockModeRead, PixelFormat32bppARGB, bitmapData);
		UINT *pixels = (UINT*)bitmapData->Scan0;
		for (UINT row = 0; row < tRect.Height; row++)
		{
			memcpy(pDst, pixels + (row*bitmapData->Stride / 4), (UINT)(tRect.Width * sizeof(UINT)));
			pDst += (UINT)tRect.Width;
		}


		delete pBitmap;
		delete bitmapData;



		QPoint tCur, tPrev;
		auto rit = vTmpPoint.begin();
		while (rit != vTmpPoint.end())
		{
			tCur = (*rit);
			if (tCur == tPrev)
			{
				rit = vTmpPoint.erase(rit);
			}
			else
				rit++;
			tPrev = tCur;
		}
		std::vector<QVector2D> vConverted;
		rit = vTmpPoint.begin();
		while (rit != vTmpPoint.end())
		{
			QVector2D vV = QVector2D((float)rit->x() - tRect.X, (float)rit->y() - tRect.Y);
			vConverted.push_back(vV);
			rit++;
		}

		CTileMapSupport *pTS = CTileMapSupport::GetInstance();
		std::vector<QPointF> tVA = pTS->getPolyLineBuffer(vConverted, 11.f);

		auto *pDM = CDataManage::GetInstance();
		bool bFind = false;
		auto pVEC = pDM->GET_MODEL_CLASS(LineMapArrowTexture)->getVector();
		auto xit = find_if(pVEC->begin(), pVEC->end(), [&uStart, &uEnd](std::shared_ptr<CSQLData> &pData)
		{
			LineMapArrowTexture *pLT = (LineMapArrowTexture*)pData.get();
			return ((pLT->uStart == uStart) && (pLT->uEnd == uEnd));
		});
		if (xit != pVEC->end())
		{
			LineMapArrowTexture *pLT = (LineMapArrowTexture*)xit->get();
			pLT->pByte = pByte;
			pLT->nSize = (UINT)tRect.Width*(UINT)tRect.Height * 4;
			pLT->nOffsetX = tRect.X;
			pLT->nOffsetY = tRect.Y;
			pLT->nTexWidth = tRect.Width;
			pLT->nTexHeight = tRect.Height;
			pLT->uStart = uStart;
			pLT->uEnd = uEnd;
			pLT->nVtxBufSize = tVA.size() * 2 * sizeof(float);
			std::shared_ptr<unsigned char> pTmpByte = std::shared_ptr<unsigned char>((unsigned char*)malloc(pLT->nVtxBufSize), free);
			float *pf = (float*)pTmpByte.get();
			for (int i = 0; i < tVA.size(); i++)
			{
				pf[i * 2] = tVA[i].x();
				pf[i * 2 + 1] = tVA[i].y();
			}
			pLT->pByteVertex = pTmpByte;
			bFind = true;
		}
		if (!bFind)
		{
			auto pLML = pDM->GET_MODEL_CLASS(LineMapArrowTexture)->insertRow();
			LineMapArrowTexture *pLT = (LineMapArrowTexture*)pLML.get();
			pLT->pByte = pByte;
			pLT->nSize = (UINT)tRect.Width*(UINT)tRect.Height * 4;
			pLT->nOffsetX = tRect.X;
			pLT->nOffsetY = tRect.Y;
			pLT->nTexWidth = tRect.Width;
			pLT->nTexHeight = tRect.Height;
			pLT->uStart = uStart;
			pLT->uEnd = uEnd;
			pLT->nVtxBufSize = tVA.size() * 2 * sizeof(float);
			std::shared_ptr<unsigned char> pTmpByte = std::shared_ptr<unsigned char>((unsigned char*)malloc(pLT->nVtxBufSize), free);
			float *pf = (float*)pTmpByte.get();
			for (int i = 0; i < tVA.size(); i++)
			{
				pf[i * 2] = (GLfloat)tVA[i].x();
				pf[i * 2 + 1] = (GLfloat)tVA[i].y();
			}
			pLT->pByteVertex = pTmpByte;
		}
	}
}


bool QGLESLineMapCanvas::GetEncCLSID(wchar_t *mime, CLSID *pClsid)
{
	UINT num, size, i;
	Gdiplus::ImageCodecInfo *arCod;
	BOOL bFound = FALSE;
	Gdiplus::GetImageEncodersSize(&num, &size);
	arCod = (Gdiplus::ImageCodecInfo *)malloc(size);
	GetImageEncoders(num, size, arCod);
	for (i = 0; i < num; i++) {
		if (wcscmp(arCod[i].MimeType, mime) == 0) {
			*pClsid = arCod[i].Clsid;
			bFound = TRUE;
			break;
		}
	}
	free(arCod);
	return bFound;
}

void QGLESLineMapCanvas::saveTextureImage(GLuint nTexture, int nWidth, int nHeight, int nBytePerPixel)
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

	for (UINT row = 0; row < nHeight; row++)
	{
		memcpy(pixels, sourcePixels, nWidth*nBytePerPixel);
		pixels += (bitmapData->Stride / 4);
		sourcePixels += nWidth;
	}
	pBitmap->UnlockBits(bitmapData);

	CLSID clsid;
	GetEncCLSID(L"image/png", &clsid);
	wchar_t szBuffer[256];
	swprintf_s(szBuffer, _countof(szBuffer), L"C:\\Intel\\Texture%d.PNG", nTexture);
	pBitmap->Save(szBuffer, &clsid);

}

void QGLESLineMapCanvas::paintDisplayItems()
{
	auto *pDM = CDataManage::GetInstance();
	auto pLMDI = pDM->GET_MODEL_CLASS(LineMapDisplayItem)->getVector();
	auto pDIP = pDM->GET_MODEL_CLASS(DisplayItemPool)->getVector();
	for (auto it : (*pLMDI))
	{
		LineMapDisplayItem *pLMDI = (LineMapDisplayItem*)it.get();
		auto findIt = find_if(pDIP->begin(), pDIP->end(), findSQLData(pLMDI->nRelatedDisplayItem));
		if (findIt != pDIP->end())
		{
			DisplayItemPool *pDIP = (DisplayItemPool*)findIt->get();
			pLMDI->m_fRect[0] = (GLfloat)0.0f;
			pLMDI->m_fRect[1] = (GLfloat)0.0f;
			pLMDI->m_fRect[2] = (GLfloat)pDIP->nWidth;
			pLMDI->m_fRect[3] = (GLfloat)pDIP->nHeight;
			pLMDI->SetOrigin(pLMDI->nCenterSpot, true);
			for (auto vit : findIt->get()->m_vChildItem[0].vSQLData)
			{
				DisplayItem *pItem = (DisplayItem*)vit.get();
				pItem->tLine.jumpTo(m_nCurTime);
				auto findIt = m_mImageList.find(pItem->nRelatedBufferIndex);
				if (findIt != m_mImageList.end())
				{
					QMatrix4x4 matrix;
					findIt->second->SetOrigin(pItem->nOrigin, true);
					matrix.ortho(0, m_nWidth/*pDIP->nWidth*/, m_nHeight/*pDIP->nHeight*/, 0, -1, 1);
					matrix.translate(pLMDI->nPosX, pLMDI->nPosY);
					matrix.translate(pLMDI->m_fOrigin[0], pLMDI->m_fOrigin[1]);

					matrix.translate(pItem->m_fTrans[0], pItem->m_fTrans[1]);
					matrix.rotate(pItem->m_fRotation, 0, 0, 1.0f);
					matrix.scale(pItem->m_fScale[0], pItem->m_fScale[1]);
					matrix.translate(pItem->fOrigX, pItem->fOrigY);

					glUniform4f(m_uScrColor, pItem->m_fColor[3], pItem->m_fColor[2], pItem->m_fColor[1], pItem->m_fColor[0]);
					glUniformMatrix4fv(m_uScrMatrix, 1, false, (const GLfloat*)&matrix);
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



bool QGLESLineMapCanvas::isPtInItemBound(LineMapDisplayItem *pItem, int nX, int nY, GLfloat *pX, GLfloat *pY)
{
	QMatrix4x4 mat;
	QPointF tFloat, tFloat2;;
	mat.translate(pItem->nPosX, pItem->nPosY);
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
			float fOffsetX = fX;
			float fOffsetY = fY;
			QMatrix4x4 mat2;
			tFloat2 = mat2.map(QPointF(fOffsetX, fOffsetY));
			(*pX) = tFloat2.x();
			(*pY) = tFloat2.y();
		}
		return pTI->PtInPolygon(pItem->m_fTempRect, (GLfloat)fX, (GLfloat)fY);
	}
	return false;
}




void QGLESLineMapCanvas::setBoundRectangle(LineMapDisplayItem *pLMDI)
{
	pLMDI->m_fTempRect[0] = pLMDI->m_fTempRect[8] = (GLfloat)pLMDI->m_fRect[0];
	pLMDI->m_fTempRect[1] = pLMDI->m_fTempRect[9] = (GLfloat)pLMDI->m_fRect[1];
	pLMDI->m_fTempRect[2] = (GLfloat)pLMDI->m_fRect[2];
	pLMDI->m_fTempRect[3] = (GLfloat)pLMDI->m_fRect[1];
	pLMDI->m_fTempRect[4] = (GLfloat)pLMDI->m_fRect[2];
	pLMDI->m_fTempRect[5] = (GLfloat)pLMDI->m_fRect[3];
	pLMDI->m_fTempRect[6] = (GLfloat)pLMDI->m_fRect[0];
	pLMDI->m_fTempRect[7] = (GLfloat)pLMDI->m_fRect[3];
}


void QGLESLineMapCanvas::paintDisplayItemsPoolRect()
{
	glEnableVertexAttribArray(m_aLinePos);
	auto *pDM = CDataManage::GetInstance();
	auto pLMDI = pDM->GET_MODEL_CLASS(LineMapDisplayItem)->getVector();
	auto pDIP = pDM->GET_MODEL_CLASS(DisplayItemPool)->getVector();
	for (auto it : (*pLMDI))
	{
		LineMapDisplayItem *pLMDI = (LineMapDisplayItem*)it.get();
		auto findIt = find_if(pDIP->begin(), pDIP->end(), findSQLData(pLMDI->nRelatedDisplayItem));
		if (findIt != pDIP->end())
		{
			DisplayItemPool *pDIP = (DisplayItemPool*)findIt->get();
			pLMDI->m_fRect[0] = 0.f;
			pLMDI->m_fRect[1] = 0.f;
			pLMDI->m_fRect[2] = (GLfloat)pDIP->nWidth + pLMDI->m_fRect[0];
			pLMDI->m_fRect[3] = (GLfloat)pDIP->nHeight + pLMDI->m_fRect[1];
			setBoundRectangle(pLMDI);
			QMatrix4x4 matrix;
			matrix.ortho(0, m_nWidth, m_nHeight, 0, -1, 1);
			matrix.translate((GLfloat)pLMDI->nPosX, (GLfloat)pLMDI->nPosY, 0.1f);
			glUniform4f(m_uLineColor, 1.0, 1.0, 1.0, 1.0);
			glUniformMatrix4fv(m_uLineMatrix, 1, false, (const GLfloat*)&matrix);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), pLMDI->m_fTempRect);
			glDrawArrays(GL_LINE_STRIP, 0, 5);
		}
	}
	glDisableVertexAttribArray(m_aLinePos);
}


void QGLESLineMapCanvas::paintStationRelated()
{
	auto *pDM = CDataManage::GetInstance();
	auto pVE = pDM->GET_MODEL_CLASS(LineMapNode)->getVector();
	auto pDIP = pDM->GET_MODEL_CLASS(DisplayItemPool)->getVector();


	for (auto it : (*pVE))
	{
		// num of nodes
		LineMapNode *pNode = (LineMapNode*)it.get();


		switch (pNode->nType[m_eCurrentStnState - 1])
		{
		case DISP_DISPLAY_ITEM:
		{
			auto findIt = find_if(pDIP->begin(), pDIP->end(), findSQLData(pNode->nRelatedIndex[m_eCurrentStnState - 1]));

			if (findIt != pDIP->end())
			{
				DisplayItemPool *pDIP = (DisplayItemPool*)findIt->get();
				pNode->m_fRect[m_eCurrentStnState - 1][0] = (GLfloat)0.0f;
				pNode->m_fRect[m_eCurrentStnState - 1][1] = (GLfloat)0.0f;
				pNode->m_fRect[m_eCurrentStnState - 1][2] = (GLfloat)pDIP->nWidth;
				pNode->m_fRect[m_eCurrentStnState - 1][3] = (GLfloat)pDIP->nHeight;
				pNode->SetOrigin(m_eCurrentStnState - 1, pNode->nCenterSpot[m_eCurrentStnState - 1]);
				for (auto vit : findIt->get()->m_vChildItem[0].vSQLData)
				{
					DisplayItem *pItem = (DisplayItem*)vit.get();
					pItem->tLine.jumpTo(m_nCurTime);
					auto findIt = m_mImageList.find(pItem->nRelatedBufferIndex);
					if (findIt != m_mImageList.end())
					{
						QMatrix4x4 matrix;
						findIt->second->SetOrigin(pItem->nOrigin, true);
						matrix.ortho(0, m_nWidth/*pDIP->nWidth*/, m_nHeight/*pDIP->nHeight*/, 0, -1, 1);
						matrix.translate(pNode->nPosX + pNode->nOffsetX[m_eCurrentStnState - 1], pNode->nPosY + pNode->nOffsetY[m_eCurrentStnState - 1]);
						matrix.rotate(pNode->nRotAngle[m_eCurrentStnState - 1], 0, 0, 1.0f);
						matrix.translate(pNode->m_fOrigin[m_eCurrentStnState - 1][0], pNode->m_fOrigin[m_eCurrentStnState - 1][1]);


						matrix.translate(pItem->m_fTrans[0], pItem->m_fTrans[1]);
						matrix.rotate(pItem->m_fRotation, 0, 0, 1.0f);
						matrix.scale(pItem->m_fScale[0], pItem->m_fScale[1]);
						matrix.translate(pItem->fOrigX, pItem->fOrigY);

						//QMatrix4x4 matrix2;
						//matrix2.ortho(0, m_nWidth, m_nHeight, 0, -1, 1);

					//	QMatrix4x4 matrix3 = matrix * matrix2;
						/*matrix.translate(pNode->nPosX, pNode->nPosY);
						matrix.rotate(pNode->nRotAngle[m_eCurrentStnState - 1], 0, 0, 1.0f);
						matrix.translate((GLfloat)pNode->m_fOrigin[m_eCurrentStnState - 1][0], (GLfloat)pNode->m_fOrigin[m_eCurrentStnState - 1][1]);*/

						glUniform4f(m_uScrColor, pItem->m_fColor[3], pItem->m_fColor[2], pItem->m_fColor[1], pItem->m_fColor[0]);
						glUniformMatrix4fv(m_uScrMatrix, 1, false, (const GLfloat*)&matrix);
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
			auto findIt = m_mImageList.find(pNode->nRelatedIndex[m_eCurrentStnState - 1]);
			if (findIt != m_mImageList.end())
			{
				findIt->second->SetOrigin(pNode->nCenterSpot[m_eCurrentStnState - 1]);
				QMatrix4x4 matrix;
				matrix.ortho(0, m_nWidth, m_nHeight, 0, -1, 1);
				matrix.translate(pNode->nPosX + (GLfloat)pNode->nOffsetX[m_eCurrentStnState - 1], pNode->nPosY + (GLfloat)pNode->nOffsetY[m_eCurrentStnState - 1]);
				matrix.rotate(pNode->nRotAngle[m_eCurrentStnState - 1], 0, 0, 1.0f);
				matrix.translate(findIt->second->m_fOrigin[0], findIt->second->m_fOrigin[1]);
				glUniform4f(m_uScrColor, 1.0f, 1.0f, 1.0f, 1.0f);
				/*glUniform4f(m_uScrColor,
					(GLfloat)((pItem->nColoring >> 24) & 0xFF) / 255.0f,
					(GLfloat)((pItem->nColoring >> 16) & 0xFF) / 255.0f,
					(GLfloat)((pItem->nColoring >> 8) & 0xFF) / 255.0f,
					(GLfloat)((pItem->nColoring) & 0xFF) / 255.0f);*/
				glUniform4f(m_uScrColor, 1.0f, 1.0f, 1.0f, 1.0f);
				glUniformMatrix4fv(m_uScrMatrix, 1, false, (const GLfloat*)&matrix);

				for (auto subit : findIt->second->vIdxList)
				{
					glBindTexture(GL_TEXTURE_2D, subit.nTextureIndex);
					glDrawElements(GL_TRIANGLES, subit.iCount, GL_UNSIGNED_SHORT, (const void*)(subit.iOffset * sizeof(GLushort)));
				}
			}
		}
		break;
		}
		if (m_bCtrlKeyPressed && (m_eEditMode == EDIT_NODE))
		{
			for (auto mit : m_mNodes)
			{
				unsigned short wX = (mit.first >> 16);
				unsigned short wY = (mit.first);
				QMatrix4x4 mat;
				m_tStationSpot->SetOrigin(5);
				mat.ortho(0, m_nWidth, m_nHeight, 0, -1, 1);
				mat.translate(m_tStationSpot->m_fOrigin[0] + (GLfloat)wX, m_tStationSpot->m_fOrigin[1] + (GLfloat)wY);
				auto vit = std::find(m_vSelNodes.begin(), m_vSelNodes.end(), mit.first);
				if (vit != m_vSelNodes.end())
					glUniform4f(m_uScrColor, (GLfloat)1.0f, (GLfloat)0.0f, (GLfloat)0.0f, (GLfloat)1.0f);
				else
					glUniform4f(m_uScrColor, (GLfloat)0.0f, (GLfloat)1.0f, (GLfloat)0.0f, (GLfloat)1.0f);

				glUniformMatrix4fv(m_uScrMatrix, 1, false, (const GLfloat*)&mat);
				for (auto spotit : m_tStationSpot->vIdxList)
				{
					glBindTexture(GL_TEXTURE_2D, spotit.nTextureIndex);
					glDrawElements(GL_TRIANGLES, spotit.iCount, GL_UNSIGNED_SHORT, (const void*)(spotit.iOffset * sizeof(GLushort)));
				}
			}
		}
		else
		{

			if (!pNode->nSUseDefault[m_eCurrentStnState - 1])
			{
				switch (pNode->nSType[m_eCurrentStnState - 1])
				{
				case DISP_DISPLAY_ITEM:
				{
					auto findIt = find_if(pDIP->begin(), pDIP->end(), findSQLData(pNode->nSRelatedIndex[m_eCurrentStnState - 1]));

					if (findIt != pDIP->end())
					{
						DisplayItemPool *pDIP = (DisplayItemPool*)findIt->get();
						pNode->m_fRect[m_eCurrentStnState - 1][0] = (GLfloat)0.0f;
						pNode->m_fRect[m_eCurrentStnState - 1][1] = (GLfloat)0.0f;
						pNode->m_fRect[m_eCurrentStnState - 1][2] = (GLfloat)pDIP->nWidth;
						pNode->m_fRect[m_eCurrentStnState - 1][3] = (GLfloat)pDIP->nHeight;
						pNode->SetOrigin(m_eCurrentStnState - 1, pNode->nSCenterSpot[m_eCurrentStnState - 1]);
						for (auto vit : findIt->get()->m_vChildItem[0].vSQLData)
						{
							DisplayItem *pItem = (DisplayItem*)vit.get();
							pItem->tLine.jumpTo(m_nCurTime);
							auto findIt = m_mImageList.find(pItem->nRelatedBufferIndex);
							if (findIt != m_mImageList.end())
							{
								QMatrix4x4 matrix;
								findIt->second->SetOrigin(pItem->nOrigin, true);
								matrix.ortho(0, m_nWidth/*pDIP->nWidth*/, m_nHeight /*pDIP->nHeight*/, 0, -1, 1);
								matrix.translate(pNode->nPosX + pNode->nSOffsetX[m_eCurrentStnState - 1], pNode->nPosY + pNode->nSOffsetY[m_eCurrentStnState - 1]);
								//matrix.rotate(pNode->nRotAngle[m_eCurrentStnState - 1], 0, 0, 1.0f);
								matrix.translate(pNode->m_fOrigin[m_eCurrentStnState - 1][0], pNode->m_fOrigin[m_eCurrentStnState - 1][1]);


								matrix.translate(pItem->m_fTrans[0], pItem->m_fTrans[1]);
								matrix.rotate(pItem->m_fRotation, 0, 0, 1.0f);
								matrix.scale(pItem->m_fScale[0], pItem->m_fScale[1]);
								matrix.translate(pItem->fOrigX, pItem->fOrigY);

								//QMatrix4x4 matrix2;
								//matrix2.ortho(0, m_nWidth, m_nHeight, 0, -1, 1);

								//	QMatrix4x4 matrix3 = matrix * matrix2;
								/*matrix.translate(pNode->nPosX, pNode->nPosY);
								matrix.rotate(pNode->nRotAngle[m_eCurrentStnState - 1], 0, 0, 1.0f);
								matrix.translate((GLfloat)pNode->m_fOrigin[m_eCurrentStnState - 1][0], (GLfloat)pNode->m_fOrigin[m_eCurrentStnState - 1][1]);*/

								glUniform4f(m_uScrColor, pItem->m_fColor[3], pItem->m_fColor[2], pItem->m_fColor[1], pItem->m_fColor[0]);
								glUniformMatrix4fv(m_uScrMatrix, 1, false, (const GLfloat*)&matrix);
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
					auto findIt = m_mImageList.find(pNode->nSRelatedIndex[m_eCurrentStnState - 1]);
					if (findIt != m_mImageList.end())
					{
						findIt->second->SetOrigin(pNode->nSCenterSpot[m_eCurrentStnState - 1]);
						QMatrix4x4 matrix;
						matrix.ortho(0, m_nWidth, m_nHeight, 0, -1, 1);
						matrix.translate(pNode->nPosX + (GLfloat)pNode->nSOffsetX[m_eCurrentStnState - 1], pNode->nPosY + (GLfloat)pNode->nSOffsetY[m_eCurrentStnState - 1]);
						//matrix.rotate(pNode->nRotAngle[m_eCurrentStnState - 1], 0, 0, 1.0f);
						matrix.translate(findIt->second->m_fOrigin[0], findIt->second->m_fOrigin[1]);
						glUniform4f(m_uScrColor, 1.0f, 1.0f, 1.0f, 1.0f);
						/*glUniform4f(m_uScrColor,
						(GLfloat)((pItem->nColoring >> 24) & 0xFF) / 255.0f,
						(GLfloat)((pItem->nColoring >> 16) & 0xFF) / 255.0f,
						(GLfloat)((pItem->nColoring >> 8) & 0xFF) / 255.0f,
						(GLfloat)((pItem->nColoring) & 0xFF) / 255.0f);*/
						glUniform4f(m_uScrColor, 1.0f, 1.0f, 1.0f, 1.0f);
						glUniformMatrix4fv(m_uScrMatrix, 1, false, (const GLfloat*)&matrix);

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
				QMatrix4x4 mat;
				mat.ortho(0, m_nWidth, m_nHeight, 0, -1, 1);
				mat.translate(m_tStationSpot->m_fOrigin[0] + (GLfloat)pNode->nPosX, m_tStationSpot->m_fOrigin[1] + (GLfloat)pNode->nPosY);
				glUniform4f(m_uScrColor, (GLfloat)1.0f, (GLfloat)0.0f, (GLfloat)0.0f, (GLfloat)1.0f);
				glUniformMatrix4fv(m_uScrMatrix, 1, false, (const GLfloat*)&mat);
				for (auto spotit : m_tStationSpot->vIdxList)
				{
					m_tStationSpot->SetOrigin(5);
					glBindTexture(GL_TEXTURE_2D, spotit.nTextureIndex);
					glDrawElements(GL_TRIANGLES, spotit.iCount, GL_UNSIGNED_SHORT, (const void*)(spotit.iOffset * sizeof(GLushort)));
				}

			}
		}

	}
}

void QGLESLineMapCanvas::initDisplayItem()
{
	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();
	auto pVECMain = pDM->GET_MODEL_CLASS(DisplayItemPool).get()->getVector();
	for (auto it : (*pVECMain))		//DisplayItemPool
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
	}
}

void QGLESLineMapCanvas::setCurrentTime(int nCurTime)
{
	m_nCurTime = nCurTime;
	update();
}