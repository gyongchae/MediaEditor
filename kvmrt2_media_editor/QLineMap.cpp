#include "QLineMap.h"
#include "defineTileMap.h"
#include "SQLData.h"
#include "DefineTables.h"
#include "DataManage.h"
#include "DataModel.h"
#include "TileMapSupport.h"
#include "editableSQLTreeModel.h"
#include "QMenu.h"


#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif


#define MAKECOORDKEY(A,B)	MAKELONG(B,A)
#include <windows.h>
#include <math.h>
#include <Gdiplus.h>

QLineMap::QLineMap(QWidget* parent)
	:QSFMLCanvas(parent,QPoint(0,0),QSize(1920,1080))
{

}


QLineMap::QLineMap(QWidget* parent,int nBlockSize,int nThickness,int nWholeWidth,int nWholeHeight,unsigned char *pBufTileMap,const QPoint& position, const QSize& size)
	:QSFMLCanvas(parent, position, size),m_nBlockSize(nBlockSize),m_nThickness(nThickness),m_tCurTile(TILE_NONE),m_nSelectedNode(-1),m_tMapMode(-1),nInitPosX(0),nInitPosY(0),m_bPressed(false),m_pLinkMenu(0),m_bCtrlKeyPressed(false),m_tScreenSize(size)

{

	m_fixed = getView(); // The 'fixed' view will never change
	m_standard = m_fixed; // The 'standard' view will be the one that gets always displayed

	InitLinkMenu();
	InitNodeMenu();
	InitAlignMenu();
	setTileMap(nWholeWidth,nWholeHeight,nBlockSize,pBufTileMap);
	GenerateTileBitmap(nBlockSize,nThickness);
	GenerateSpotBitmap(nBlockSize);
	setMouseTracking(true);
	ZeroMemory(m_uConfirmedBuffer,sizeof(m_uConfirmedBuffer));
	ZeroMemory(m_uNodeBuffer,sizeof(m_uNodeBuffer));
	ZeroMemory(m_uArrowNode,sizeof(m_uArrowNode));
	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(contextMenu(const QPoint&)));
}


void QLineMap::initTileMaps(std::shared_ptr<CTreeInfo> &pTreeInfo)
{
	CTileMapSupport *pTMS=CTileMapSupport::GetInstance();
	m_pTreeInfoLink=pTreeInfo;
	std::vector<std::shared_ptr<CSQLData>>::iterator vit;
	int nCount=m_pTreeInfoLink->GetChildCount();
	LPCHILDITEM lpInfo=(LPCHILDITEM)pTreeInfo->GetPointer();
	m_pvLink=&lpInfo->vSQLData;
	m_vLink=lpInfo->vSQLData;
	for(vit=m_vLink.begin();vit!=m_vLink.end();vit++)
	{
		LineMapLink *pItem=(LineMapLink*)vit->get();
		pItem->m_tPath=pTMS->GetPath(m_nBlockSize,m_nThickness,pItem->nItemType,pItem->nPosX,pItem->nPosY);
		pItem->m_tPolygon=pTMS->GetPolygon(m_nBlockSize,m_nThickness,pItem->nItemType,pItem->nPosX,pItem->nPosY);
		pItem->m_tArcRect=pTMS->GetArcRect(m_nBlockSize,m_nThickness,pItem->nItemType,pItem->nPosX,pItem->nPosY);
		afterSetPos(pItem);

#ifdef SAVEPIC
		CSQLData *pParent=(CSQLData*)pTreeInfo->GetParent()->GetPointer();
		QString str=QString("C:/Intel2/TILE_MAP-%1.TXT").arg(pParent->GetIndex());
		QFile tFile(str);
		tFile.open(QIODevice::WriteOnly|QIODevice::Append|QIODevice::Text);
		QTextStream out(&tFile);
		out<<"Parent "<<pParent->GetIndex()<<"-"<<pItem->GetIndex()<<"\tX "<<pItem->nPosX<<"\tY "<<pItem->nPosY<<"\tProp : "<<pItem->nProp<<"\tItemType: "<<pItem->nItemType<<"\n";
		tFile.close();



#endif



	}
}


void QLineMap::initNodeInformation(std::shared_ptr<CTreeInfo> &pTreeInfo)
{
	m_pTreeInfoNode=pTreeInfo;
	LPCHILDITEM lpInfo=(LPCHILDITEM)pTreeInfo->GetPointer();
	m_pvNode=&lpInfo->vSQLData;
	m_vNode=lpInfo->vSQLData;


#ifdef SAVEPIC
	CTableManage *pTM=CTableManage::GetInstance();
	std::vector<std::shared_ptr<CSQLData>>::iterator vit;
	std::vector<std::shared_ptr<CSQLData>>::iterator vnit;
	std::vector<std::shared_ptr<CSQLData>>::iterator vnnit;
	std::vector<std::shared_ptr<CSQLData>>::iterator vnnnit;

	for(vit=m_vNode.begin();vit!=m_vNode.end();vit++)
	{
		LineMapNode *pNode=(LineMapNode*)vit->get();
		for(vnit=vit->get()->m_vChildItem[0].vSQLData.begin();vnit!=vit->get()->m_vChildItem[0].vSQLData.end();vnit++)
		{
			NodeImageList *pList=(NodeImageList*)vnit->get();
			for(vnnit=vnit->get()->m_vChildItem[0].vSQLData.begin();vnnit!=vnit->get()->m_vChildItem[0].vSQLData.end();vnnit++)
			{
				NodeImageItem *pItem=(NodeImageItem*)vnnit->get();
				vnnnit=find_if(pTM->m_vImageIndexList.begin(),pTM->m_vImageIndexList.end(),findSQLData(pItem->nRelatedIdnex));
				if(vnnnit!=pTM->m_vImageIndexList.end())
				{
					ImageIndexList *pIL=(ImageIndexList*)vnnnit->get();

					QString str=QString("C:/Intel2/NODEIMAGE%1-%2-%3.TXT").arg(pList->GetIndex()).arg(pItem->GetIndex()).arg(pIL->GetIndex());
					QFile tFile(str);
					tFile.open(QIODevice::WriteOnly|QIODevice::Text);
					CSQLData *pParent=(CSQLData*)pTreeInfo->GetParent()->GetPointer();
					QTextStream out(&tFile);
					out<<"PIC Index :"<<pItem->nRelatedIdnex<<"\t X: "<<pNode->nPosX+pItem->nOffsetX<<"\t Y: "<<pNode->nPosY+pItem->nOffsetY<<"\t Rotation "<<pItem->nRotAngle<<"\t Origin Point :"<<(pItem->nCenterSpot?pItem->nCenterSpot:1)<<"\t Color: "<<hex<<(unsigned long)pItem->nColoring<<"\tDuration: "<<pItem->nDuration<<"\n";
					tFile.close();
				}
			}
		}
	}
#endif



}

void QLineMap::initArrowInformation(std::shared_ptr<CTreeInfo> &pTreeInfo)
{
	m_pTreeInfoArrow=pTreeInfo;
	LPCHILDITEM lpInfo=(LPCHILDITEM)pTreeInfo->GetPointer();
	m_pvArrow=&lpInfo->vSQLData;
	m_vArrow=lpInfo->vSQLData;

	CSQLData *pParentData=(CSQLData*)pTreeInfo->GetParent()->GetPointer();

	std::vector<std::shared_ptr<CSQLData>>::iterator nit;
	for(nit=m_vArrow.begin();nit!=m_vArrow.end();nit++)		//화살표 텍스쳐
	{
		LineMapArrowTexture *pLT=(LineMapArrowTexture*)nit->get();
		pLT->tex.create(pLT->nTexWidth,pLT->nTexHeight);
		pLT->tex.update((sf::Uint8*)pLT->pByte.get());
		pLT->offTex.create(pLT->nTexWidth,pLT->nTexHeight);
		pLT->progTex.create(pLT->nTexWidth,pLT->nTexHeight);



#ifdef SAVEPIC
		QImage *pImage=new QImage(pLT->pByte.get(),pLT->nTexWidth,pLT->nTexHeight,QImage::Format_ARGB32);
		QString str=QString("C:/Intel2/ARROW%1-%2.PNG").arg(pParentData->GetIndex()).arg(pLT->GetIndex());
		pImage->save(str);
		delete pImage;
		
		str=QString("C:/Intel2/ARROW%1-%2.TXT").arg(pParentData->GetIndex()).arg(pLT->GetIndex());
		QFile tFile(str);
		tFile.open(QIODevice::WriteOnly|QIODevice::Text);
		CSQLData *pParent=(CSQLData*)pTreeInfo->GetParent()->GetPointer();
		QTextStream out(&tFile);
		out<<"Parent "<<pParentData->GetIndex()<<"-"<<pLT->GetIndex()<<"\tX "<<pLT->nOffsetX<<"\tY "<<pLT->nOffsetY<<"\tWidth : "<<pLT->nTexWidth<<"\tHeight: "<<pLT->nTexHeight<<"\n";
		tFile.close();



#endif


		pLT->tex.setSmooth(true);
		pLT->spr.setColor(sf::Color::White);
		pLT->spr.setTexture(pLT->tex);

		int nBufValue=(pLT->nVtxBufSize/4);
		int nVertexCount=(nBufValue/2);
		pLT->va.clear();
		float *pfVa=(float*)pLT->pByteVertex.get();
		for(int i=0;i<nVertexCount;i++)
		{
			pLT->va.append(sf::Vertex(sf::Vector2f(pfVa[0],pfVa[1])));
			pfVa+=2;
		}
		pLT->va.setPrimitiveType(sf::TrianglesStrip);
		pLT->finalSpr.setPosition(pLT->nOffsetX-1,pLT->nOffsetY-1);
		pLT->SetProgress(sf::Color::Red,sf::Color::Blue,100.f);
	}
}



QLineMap::~QLineMap(void)
{
	
}




void QLineMap::OnInit()
{
	
}
   

void QLineMap::OnUpdate()
{
	clear(sf::Color(0, 0, 0));
	setView(m_standard);
	CTableManage *pTM=CTableManage::GetInstance();
	CTileMapSupport *pTMS=CTileMapSupport::GetInstance();

	std::vector<std::shared_ptr<CSQLData>>::iterator vit;
	std::vector<std::shared_ptr<CSQLData>>::iterator vnit;
	std::vector<std::shared_ptr<CSQLData>>::iterator vnnit;
	std::vector<std::shared_ptr<CSQLData>>::iterator vnnnit;
	for(vit=m_vLink.begin();vit!=m_vLink.end();vit++)
	{
		LineMapLink *pItem=(LineMapLink*)vit->get();
		m_sprTile[pItem->nItemType].setPosition((float)pItem->nPosX,(float)pItem->nPosY);
		draw(m_sprTile[pItem->nItemType]);
	}

	
	sf::CircleShape circle(10,360);
	circle.setOrigin(circle.getRadius(), circle.getRadius());

	if(!m_bCtrlKeyPressed)	//Key Release 된 경우
	{
		for(vit=m_vNode.begin();vit!=m_vNode.end();vit++)
		{
			LineMapNode *pNode=(LineMapNode*)vit->get();
			circle.setPosition(pNode->nPosX,pNode->nPosY);
			if(pNode->GetIndex()==m_nSelectedNode)
				circle.setFillColor(sf::Color::Yellow);
			else
				circle.setFillColor(sf::Color::Blue);
			draw(circle);
			for(vnit=vit->get()->m_vChildItem[0].vSQLData.begin();vnit!=vit->get()->m_vChildItem[0].vSQLData.end();vnit++)
			{
				NodeImageList *pList=(NodeImageList*)vnit->get();
				for(vnnit=vnit->get()->m_vChildItem[0].vSQLData.begin();vnnit!=vnit->get()->m_vChildItem[0].vSQLData.end();vnnit++)
				{
					NodeImageItem *pItem=(NodeImageItem*)vnnit->get();
					vnnnit=find_if(pTM->m_vImageIndexList.begin(),pTM->m_vImageIndexList.end(),findSQLData(pItem->nRelatedIdnex));
					if(vnnnit!=pTM->m_vImageIndexList.end())
					{
						ImageIndexList *pIL=(ImageIndexList*)vnnnit->get();
						if(pItem->bVisible)
						{
							pTMS->setOriginPoint(pIL->spr,pItem->nCenterSpot?pItem->nCenterSpot:1);
							pIL->spr.setRotation(pItem->nRotAngle);
							pIL->spr.setPosition(pNode->nPosX+pItem->nOffsetX,pNode->nPosY+pItem->nOffsetY);
							unsigned char uColor=(unsigned char)(pItem->nColoring>>24);
							pIL->spr.setColor(sf::Color(pItem->nColoring,pItem->nColoring>>8,pItem->nColoring>>16,pItem->nColoring>>24));
							draw(pIL->spr);
						}
					}
				}
			}
		}
		for(vit=m_vArrow.begin();vit!=m_vArrow.end();vit++)
		{
			LineMapArrowTexture *pLMAT=(LineMapArrowTexture*)vit->get();
			if(pLMAT->bVisible)
				draw(pLMAT->finalSpr);
		}
	}
	else
	{
		std::map<unsigned int,int>::iterator mit;
		std::vector<unsigned int>::iterator vit;
		for(mit=m_mNodes.begin();mit!=m_mNodes.end();mit++)
		{
			WORD wX=(mit->first>>16);
			WORD wY=(mit->first);
			vit=std::find(m_vSelNodes.begin(),m_vSelNodes.end(),mit->first);
			if(vit!=m_vSelNodes.end())
				circle.setFillColor(sf::Color::Red);
			else
				circle.setFillColor(sf::Color::Green);

			circle.setPosition(wX,wY);
			draw(circle);
		}
	}
}

void QLineMap::OnResize(int x,int y)
{
	setSize(sf::Vector2u(x,y));
	m_standard.setSize(x,y);
	m_standard.setCenter((float)x/2.f,(float)y/2.f);
	m_standard.move((float)nInitPosX,(float)nInitPosY);
	setView(m_standard);
}

void QLineMap::mouseMoveEvent ( QMouseEvent * event )
{
	int nOriginPosX=event->pos().x()+nInitPosX;
	int nOriginPosY=event->pos().y()+nInitPosY;	
	CDataManage *pDM=CDataManage::GetInstance();
	std::vector<std::shared_ptr<CSQLData>>::iterator vit;
	int nMinXPos,nMinYPos;
	switch(m_tMapMode)
	{
	case 3:
		if(m_bPressed&&(m_nSelectedNode!=-1)&&getMinCoordFromBuffer(nOriginPosX,nOriginPosY,&nMinXPos,&nMinYPos))
		{
			vit=find_if(m_vNode.begin(),m_vNode.end(),findSQLData(m_nSelectedNode));
			if(vit!=m_vNode.end())
			{
				LineMapNode *pLN=(LineMapNode*)vit->get();
				pLN->nPosX=nMinXPos;
				pLN->nPosY=nMinYPos;
				if(pLN->GetRecordState()==EDIT_NOT_MODIFIED)
					pLN->SetRecordState(EDIT_UPDATED);
			}
		}
		break;
	default:
		break;
	}
	update();



}	

void QLineMap::mousePressEvent(QMouseEvent * event)
{
	int nIndex;
	bool bDeleted=false;
	CDataManage *pDM=CDataManage::GetInstance();
	int nOriginPosX=event->pos().x()+nInitPosX;
	int nOriginPosY=event->pos().y()+nInitPosY;
	int nCurX=(int)(nOriginPosX/m_nBlockSize)*m_nBlockSize+(m_nBlockSize/2);
	int nCurY=(int)(nOriginPosY/m_nBlockSize)*m_nBlockSize+(m_nBlockSize/2);
	if(event->button()==Qt::LeftButton)
	{
		switch(m_tMapMode)
		{
		case 3:
			{
				if(!m_bCtrlKeyPressed)
				{
					std::vector<std::shared_ptr<CSQLData>>::iterator vit;
					for(vit=m_vNode.begin();vit!=m_vNode.end();vit++)
					{
						LineMapNode *pNode=(LineMapNode*)vit->get();
						sf::IntRect tRect(pNode->nPosX-15,pNode->nPosY-15,30,30);
						if(tRect.contains(nOriginPosX,nOriginPosY))
						{
							m_nSelectedNode=vit->get()->GetIndex();
						}
					}
					m_bPressed=true;
				}
				else
				{
					m_bPressed=false;
					m_nSelectedNode=-1;

					std::map<unsigned int,int>::iterator mit;
					for(mit=m_mNodes.begin();mit!=m_mNodes.end();mit++)
					{
						WORD wX=(mit->first>>16);
						WORD wY=(mit->first);
						sf::IntRect tRect(wX-15,wY-15,30,30);
						if(tRect.contains(nOriginPosX,nOriginPosY))
						{
							m_vSelNodes.push_back(mit->first);
						}
					}
				}
			}
			break;
		case 2:
			{
				bool bSelected=false;
				std::vector<std::shared_ptr<CSQLData>>::iterator vit;
				for(vit=m_vNode.begin();vit!=m_vNode.end();vit++)
				{
					LineMapNode *pNode=(LineMapNode*)vit->get();
					sf::IntRect tRect(pNode->nPosX-15,pNode->nPosY-15,30,30);
					if(tRect.contains(nOriginPosX,nOriginPosY))
					{
						bSelected=true;
						if(!m_uArrowNode[0])
						{
							m_uArrowNode[0]=MAKECOORDKEY((WORD)pNode->nPosX,(WORD)pNode->nPosY);
						}
						else if(!m_uArrowNode[1])
						{
							m_uArrowNode[1]=MAKECOORDKEY((WORD)pNode->nPosX,(WORD)pNode->nPosY);
							if(m_uArrowNode[0]==m_uArrowNode[1])
							{
								m_uArrowNode[1]=0;
							}
							else
							{
								WORD wStX=(WORD)(m_uArrowNode[0]>>16);
								WORD wStY=(WORD)(m_uArrowNode[0]);
								WORD wEnX=(WORD)(m_uArrowNode[1]>>16);
								WORD wEnY=(WORD)(m_uArrowNode[1]);
								realignNodes();
								generateArrowFrom(wStX,wStY,wEnX,wEnY,15,15);
								m_uArrowNode[0]=m_uArrowNode[1]=0;
							}
						}
					}
				}
				if(!bSelected)
				{
					m_uArrowNode[0]=m_uArrowNode[1]=0;
				}
			}
			break;
		default:
			break;
		}
	}
	update();
}

void QLineMap::addLink(int nTile,int nX,int nY)
{
	CDataManage *pDM=CDataManage::GetInstance();
	CTileMapSupport *pTMS=CTileMapSupport::GetInstance();
	CTreeInfo *pInfo=m_pModel->getItem(m_tmpIndex);
	std::shared_ptr<CSQLData> pLML=m_pModel->insertRow(m_tmpIndex);
	LineMapLink *pLM=(LineMapLink*)pLML.get();
	pLM->m_tPath=pTMS->GetPath(m_nBlockSize,m_nThickness,nTile,nX,nY);
	pLM->m_tPolygon=pTMS->GetPolygon(m_nBlockSize,m_nThickness,nTile,nX,nY);
	pLM->m_tArcRect=pTMS->GetArcRect(m_nBlockSize,m_nThickness,nTile,nX,nY);
	pTMS->GetAngles(nTile,&pLM->nAngleSt,&pLM->nAngleEn);
	pLM->nItemType=nTile;
	pLM->nPosX=nX;
	pLM->nPosY=nY;
	afterSetPos(pLM);	
	m_vLink=(*m_pvLink);
}




void QLineMap::keyPressEvent (QKeyEvent * event)
{
	CDataManage *pDM=CDataManage::GetInstance();
	switch(m_tMapMode)
	{
	case 3:
		switch(event->key())
		{
		case Qt::Key_Control:
			m_bCtrlKeyPressed=true;
			break;
		case Qt::Key_A:
			if(m_bCtrlKeyPressed)
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

void QLineMap::keyReleaseEvent (QKeyEvent * event)
{
	switch(event->key())
	{
	case Qt::Key_Control:
		m_bCtrlKeyPressed=false;
		break;
	case Qt::Key_A:
		break;
	}
	update();
	CDataManage *pDM=CDataManage::GetInstance();
	switch(m_tMapMode)
	{
	case 3:
		break;
	}
}

void QLineMap::focusOutEvent ( QFocusEvent * event )
{
	static int nCount=0;
	m_bCtrlKeyPressed=false;
	m_vSelNodes.clear();
	update();
	bool bFocusLost=event->lostFocus();
	qDebug("focusOutEvent %d %d\n",bFocusLost,nCount++);
}

void QLineMap::focusInEvent ( QFocusEvent * event )
{
	static int nCount=0;
	m_vSelNodes.clear();
	bool bFocused=event->gotFocus();
	qDebug("focusInEvent %d %d\n",bFocused,nCount++);
}





void QLineMap::mouseReleaseEvent ( QMouseEvent * event )
{
	m_bPressed=false;
	m_nSelectedNode=-1;
	update();
}

void QLineMap::clearAllSprite()
{
	
}

void QLineMap::setTexSprite(int nIndex,int nWidth,int nHeight,int nXPos,int nYPos,void* pVoid)
{
}

void QLineMap::removeIndex(int nIndex)
{

}


void QLineMap::setItemType(TileType type)
{
    m_tCurTile = type;
}

void QLineMap::setMode(int nMode)
{
	m_bCtrlKeyPressed=false;
	m_tMapMode = nMode;
	update();
}

void QLineMap::setTileMap(int nWholeWidth,int nWholeHeight,int nUnitSize,unsigned char *pByte)
{
	int nHalfSize=(nUnitSize/2);
	if(pByte)
	{
		m_texTile.create(nWholeWidth,nWholeHeight);
		m_texTile.update((sf::Uint8*)pByte);
		m_texTile.setSmooth(true);
		sf::IntRect tRect(0,0,nUnitSize,nUnitSize);
		for(int i=0;i<16;i++)
		{
			m_sprTile[i].setTexture(m_texTile);
			m_sprTile[i].setTextureRect(tRect);
			m_sprTile[i].setOrigin((float)nHalfSize,(float)nHalfSize);
			tRect.left+=nUnitSize;
		}
	}
}


void QLineMap::GenerateTileBitmap(int nTileSize,int nThickness)
{
	int nWholeSize=nTileSize;
	int nHalfSize=(nTileSize/2);
	using namespace Gdiplus;
	Pen pen(Color(255,255,255,255),nThickness);
	Bitmap *pBitmap=new Bitmap(nWholeSize*16,nWholeSize,PixelFormat32bppARGB);
	Graphics G(pBitmap);
	G.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
	G.SetClip(Rect(0,0,nWholeSize,nWholeSize));
	G.TranslateTransform(nHalfSize,nHalfSize);
	for(int i=0;i<16;i++)
	{
		switch(i)
		{
		case TILE_H_U:
			G.DrawLine(&pen,0,1,0,-nHalfSize-1);
			break;
		case TILE_H_D:
			G.DrawLine(&pen,0,-1,0,nHalfSize+1);
			break;
		case TILE_H_L:
			G.DrawLine(&pen,1,0,-nHalfSize-1,0);
			break;
		case TILE_H_R:
			G.DrawLine(&pen,-1,0,nHalfSize+1,0);
			break;
		case TILE_C_LU:
			G.DrawArc(&pen,-nWholeSize,-nWholeSize,nWholeSize,nWholeSize,92,-93);
			break;
		case TILE_C_LD:
			G.DrawArc(&pen,-nWholeSize,0,nWholeSize,nWholeSize,-92,92);
			break;
		case TILE_C_RD:
			G.DrawArc(&pen,0,0,nWholeSize,nWholeSize,-88,-92);
			break;
		case TILE_C_RU:
			G.DrawArc(&pen,0,-nWholeSize,nWholeSize,nWholeSize,88,93);
			break;
		default:
			break;
		}
		G.TranslateTransform(nWholeSize,0);
		G.TranslateClip(nWholeSize,0);
	}

	Rect rctClip=Rect(0,0,pBitmap->GetWidth(),pBitmap->GetHeight());
	UINT uBuffer;
	BitmapData* bitmapData = new BitmapData;
	pBitmap->LockBits(&rctClip,ImageLockModeRead,PixelFormat32bppARGB,bitmapData);
	UINT *pDst32=(UINT*)malloc(rctClip.Width*rctClip.Height*4);
	UINT *pSrc32=(UINT*)bitmapData->Scan0;	
	for(int i=rctClip.GetTop();i<rctClip.GetBottom();i++)
	{
		UINT *pSrcTmp32=pSrc32+((i-rctClip.GetTop())*(bitmapData->Stride/4));
		UINT *pDstTmp32=pDst32+(i*pBitmap->GetWidth())+(UINT)rctClip.GetLeft();
		UINT *pSrcTmp32Pixel=pSrcTmp32;
		UINT *pDstTmp32Pixel=pDstTmp32;
		int nRepeatCount=rctClip.GetRight()-rctClip.GetLeft();
		for(int j=0;j<nRepeatCount;j++)
		{
			UINT uPixelSrc=(*pSrcTmp32Pixel);
			UINT uPixelDst=(*pDstTmp32Pixel)=(((uPixelSrc&0x000000FF)<<24)|0x00FFFFFF);
			pSrcTmp32Pixel++;
			pDstTmp32Pixel++;
		}
		memcpy(pDstTmp32,pSrcTmp32,rctClip.Width*sizeof(DWORD));	
	}
	pBitmap->UnlockBits(bitmapData);
	m_texTile.create(rctClip.Width,rctClip.Height);
	m_texTile.update((sf::Uint8*)pDst32);
	m_texTile.setSmooth(true);
	sf::IntRect tRect(0,0,nTileSize,nTileSize);
	for(int i=0;i<16;i++)
	{
		m_sprTile[i].setTexture(m_texTile);
		m_sprTile[i].setTextureRect(tRect);
		m_sprTile[i].setOrigin((float)nHalfSize,(float)nHalfSize);
		tRect.left+=nTileSize;
	}
	delete bitmapData;
	delete pBitmap;
	free(pDst32);
}

void QLineMap::GenerateSpotBitmap(int nSpotSize)
{
	int nWholeSize=nSpotSize;
	int nHalfSize=(nSpotSize/2);
	using namespace Gdiplus;
	SolidBrush SB(Color(255,255,255,255));
	Bitmap *pBitmap=new Bitmap(nWholeSize*16,nWholeSize,PixelFormat32bppARGB);
	Graphics G(pBitmap);
	G.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
	G.SetClip(Rect(0,0,nWholeSize,nWholeSize));
	G.TranslateTransform(nHalfSize,nHalfSize);
	for(int i=0;i<16;i++)
	{
		G.FillEllipse(&SB,-10,-10,23,23);
		G.TranslateTransform(nWholeSize,0);
		G.TranslateClip(nWholeSize,0);
	}

	Rect rctClip=Rect(0,0,pBitmap->GetWidth(),pBitmap->GetHeight());
	UINT uBuffer;
	BitmapData* bitmapData = new BitmapData;
	pBitmap->LockBits(&rctClip,ImageLockModeRead,PixelFormat32bppARGB,bitmapData);
	UINT *pDst32=(UINT*)malloc(rctClip.Width*rctClip.Height*4);
	UINT *pSrc32=(UINT*)bitmapData->Scan0;	
	for(int i=rctClip.GetTop();i<rctClip.GetBottom();i++)
	{
		UINT *pSrcTmp32=pSrc32+((i-rctClip.GetTop())*(bitmapData->Stride/4));
		UINT *pDstTmp32=pDst32+(i*pBitmap->GetWidth())+(UINT)rctClip.GetLeft();
		UINT *pSrcTmp32Pixel=pSrcTmp32;
		UINT *pDstTmp32Pixel=pDstTmp32;
		int nRepeatCount=rctClip.GetRight()-rctClip.GetLeft();
		for(int j=0;j<nRepeatCount;j++)
		{
			UINT uPixelSrc=(*pSrcTmp32Pixel);
			UINT uPixelDst=(*pDstTmp32Pixel)=(((uPixelSrc&0x000000FF)<<24)|0x00FFFFFF);
			pSrcTmp32Pixel++;
			pDstTmp32Pixel++;
		}
		memcpy(pDstTmp32,pSrcTmp32,rctClip.Width*sizeof(DWORD));	
	}
	pBitmap->UnlockBits(bitmapData);
	m_texSpot.create(rctClip.Width,rctClip.Height);
	m_texSpot.update((sf::Uint8*)pDst32);
	m_texSpot.setSmooth(true);
	sf::IntRect tRect(0,0,nSpotSize,nSpotSize);
	for(int i=0;i<16;i++)
	{
		m_sprSpot[i].setTexture(m_texSpot);
		m_sprSpot[i].setTextureRect(tRect);
		m_sprSpot[i].setOrigin((float)nHalfSize,(float)nHalfSize);
		tRect.left+=nSpotSize;
	}
	delete bitmapData;
	delete pBitmap;
	free(pDst32);
}




void QLineMap::afterSetPos(LineMapLink *pLink)
{
	
	qreal angle;
	QPoint tPrev;
	int len=(qreal)pLink->m_tPath.length();
	pLink->nAngleSt;
	pLink->nAngleEn;
	pLink->m_tArcRect;

	pLink->vAngle.clear();
	pLink->vPoint.clear();

	
	
	for(int i=0;i<len+1;i++)
	{
		QPoint tP;
		qreal perCent=pLink->m_tPath.percentAtLength(i);
		QPointF tempVal=pLink->m_tPath.pointAtPercent(perCent);
		angle=(qreal)pLink->nAngleSt;
		angle=pLink->m_tPath.angleAtPercent(perCent)-90.0f;//*(-1.0);

		tP.setX(qCeil(tempVal.x()+0.5));
		tP.setY(qCeil(tempVal.y()+0.5));
		
		if(tP!=tPrev)
		{
			pLink->vPoint.push_back(tP);
			m_uConfirmedBuffer[tP.x()][tP.y()]++;
			pLink->vAngle.push_back(angle);
		}
		tPrev=tP;
	}

	int nNodeExists=0;
	UINT uX,uY;
	unsigned int uValue=searchNode(pLink->vPoint.begin()->x(),pLink->vPoint.begin()->y(),&nNodeExists);
	if((uValue!=0)&&(nNodeExists!=0))
	{
		switch(nNodeExists)
		{
		case 1:
		case 2:
		case 3:
		case 4:
			uX=((uValue>>16)&0xFFFF);
			uY=((uValue)&0xFFFF);
			pLink->vPoint.insert(pLink->vPoint.begin(),QPoint(uX,uY));
			pLink->vAngle.insert(pLink->vAngle.begin(),pLink->vAngle.front());
			break;
		}
	}
	uValue=searchNode(pLink->vPoint.rbegin()->x(),pLink->vPoint.rbegin()->y(),&nNodeExists);
	if((uValue!=0)&&(nNodeExists!=0))
	{
		switch(nNodeExists)
		{
		case 1:
		case 2:
		case 3:
		case 4:
			uX=((uValue>>16)&0xFFFF);
			uY=((uValue)&0xFFFF);
			pLink->vPoint.push_back(QPoint(uX,uY));
			pLink->vAngle.push_back(pLink->vAngle.back());
			break;
		}
	}




	pLink->vAngleRev=pLink->vAngle;
	pLink->vPointRev=pLink->vPoint;
	reverse(pLink->vPointRev.begin(),pLink->vPointRev.end());
	reverse(pLink->vAngleRev.begin(),pLink->vAngleRev.end());


	PATHINFO tInfo;
	tInfo.pLink=pLink;
	tInfo.vPoint=&pLink->vPoint;
	tInfo.vAngle=&pLink->vAngle;


	pLink->nLinkIndex[0]=((pLink->vPoint.begin()->x()&0x0000FFFF)<<16)|(pLink->vPoint.begin()->y()&0x0000FFFF);
	pLink->nLinkIndex[1]=((pLink->vPoint.rbegin()->x()&0x0000FFFF)<<16)|(pLink->vPoint.rbegin()->y()&0x0000FFFF);
	m_mPath[pLink->nLinkIndex[0]][pLink->nLinkIndex[1]]=tInfo;

	tInfo.pLink=pLink;
	tInfo.vPoint=&pLink->vPointRev;
	tInfo.vAngle=&pLink->vAngleRev;

	m_mPath[pLink->nLinkIndex[1]][pLink->nLinkIndex[0]]=tInfo;

	insertBasicNode(pLink->nLinkIndex[0]);
	insertBasicNode(pLink->nLinkIndex[1]);
}

unsigned int QLineMap::searchNode(WORD wX,WORD wY,int *pInt)
{
	bool bRet=false;
	unsigned int uKey=0;
	for(int i=0;i<5;i++)
	{
		switch(i)
		{
		case 0:
			uKey=(((DWORD)wX&0x0000FFFF)<<16)|(((DWORD)wY)&0x0000FFFF);
			break;
		case 1:
			uKey=((((DWORD)(wX+1))&0x0000FFFF)<<16)|(((DWORD)wY&0x0000FFFF));
			break;
		case 2:
			uKey=(((DWORD)wX&0x0000FFFF)<<16)|((((DWORD)wY+1)&0x0000FFFF));
			break;
		case 3:
			uKey=((((DWORD)(wX-1))&0x0000FFFF)<<16)|(((DWORD)wY&0x0000FFFF));
			break;
		case 4:
			uKey=(((DWORD)wX&0x0000FFFF)<<16)|((((DWORD)(wY-1))&0x0000FFFF));
			break;
		}
		(*pInt)=i;
		std::map<unsigned int,int>::iterator nit=m_mNodes.find(uKey);
		if(nit!=m_mNodes.end())
		{
			return nit->first;
		}
	}
	return 0;
}



void QLineMap::resetPos(LineMapLink *pLink)
{
	unsigned __int64 uKey;
	std::vector<QPoint>::iterator nit;
	for(nit=pLink->vPoint.begin();nit!=pLink->vPoint.end();nit++)
	{
		if(m_uConfirmedBuffer[nit->x()][nit->y()])
			m_uConfirmedBuffer[nit->x()][nit->y()]--;
	}
	std::map<unsigned int,std::map<unsigned int,PATHINFO>>::iterator mit;
	std::map<unsigned int,PATHINFO>::iterator sit;
	mit=m_mPath.find(pLink->nLinkIndex[0]);
	if(mit!=m_mPath.end())
	{
		sit=mit->second.find(pLink->nLinkIndex[1]);
		if(sit!=mit->second.end())
		{
			mit->second.erase(sit);
		}
	}


	mit=m_mPath.find(pLink->nLinkIndex[1]);
	if(mit!=m_mPath.end())
	{
		sit=mit->second.find(pLink->nLinkIndex[0]);
		if(sit!=mit->second.end())
		{
			mit->second.erase(sit);
		}
	}
	deleteBasicNode(pLink->nLinkIndex[0]);
	deleteBasicNode(pLink->nLinkIndex[1]);
}



void QLineMap::insertBasicNode(unsigned int nKey)
{
	bool bRet=false;
	std::map<unsigned int,int>::iterator nit=m_mNodes.find(nKey);
	if(nit==m_mNodes.end())
	{
		
	}
	m_mNodes[nKey]++;
}

void QLineMap::deleteBasicNode(unsigned int nKey)
{
	std::map<unsigned int,int>::iterator nit=m_mNodes.find(nKey);
	if(nit!=m_mNodes.end())
	{
		if(nit->second==1)
		{
			//반복자 복사후 지우기 최종
			m_mNodes.erase(nit);
		}
		else
			m_mNodes[nKey]--;
	}
}


void QLineMap::mouseDoubleClickEvent( QMouseEvent * event )
{
	QPoint tPoint;
	int nValue,nMin=9999999;
	LineMapLink *tmpItem=NULL;
	CDataManage *pDM=CDataManage::GetInstance();
	std::map<int,std::shared_ptr<CSQLData>>::iterator mit;
	switch(m_tMapMode)
	{
	case InsertItem:
		break;
	case InsertNode:
		{
		}
		break;
	case SelectPath:
		break;
	default:
		break;
	}
	update();
}



bool QLineMap::moveNodeTo(int dir,LineMapNode *pNode)
{
	switch(dir)
	{
	case Qt::Key_Left:
		if(m_uConfirmedBuffer[pNode->nPosX-1][pNode->nPosY])
		{
			pNode->nPosX--;
			pNode->nPosY;
			return true;
		}
		if(m_uConfirmedBuffer[pNode->nPosX-1][pNode->nPosY-1])
		{
			pNode->nPosX--;
			pNode->nPosY--;
			return true;
		}
		if(m_uConfirmedBuffer[pNode->nPosX-1][pNode->nPosY+1])
		{
			pNode->nPosX--;
			pNode->nPosY++;
			return true;
		}
		break;
	case Qt::Key_Right:
		if(m_uConfirmedBuffer[pNode->nPosX+1][pNode->nPosY])
		{
			pNode->nPosX++;
			pNode->nPosY;
			return true;
		}
		if(m_uConfirmedBuffer[pNode->nPosX+1][pNode->nPosY-1])
		{
			pNode->nPosX++;
			pNode->nPosY--;
			return true;
		}
		if(m_uConfirmedBuffer[pNode->nPosX+1][pNode->nPosY+1])
		{
			pNode->nPosX++;
			pNode->nPosY++;
			return true;
		}
		break;
	case Qt::Key_Up:
		if(m_uConfirmedBuffer[pNode->nPosX][pNode->nPosY-1])
		{
			pNode->nPosX;
			pNode->nPosY--;
			return true;
		}
		if(m_uConfirmedBuffer[pNode->nPosX-1][pNode->nPosY-1])
		{
			pNode->nPosX--;
			pNode->nPosY--;
			return true;
		}
		if(m_uConfirmedBuffer[pNode->nPosX+1][pNode->nPosY-1])
		{
			pNode->nPosX++;
			pNode->nPosY--;
			return true;
		}
		break;
	case Qt::Key_Down:
		if(m_uConfirmedBuffer[pNode->nPosX][pNode->nPosY+1])
		{
			pNode->nPosX;
			pNode->nPosY++;
			return true;
		}
		if(m_uConfirmedBuffer[pNode->nPosX-1][pNode->nPosY+1])
		{
			pNode->nPosX--;
			pNode->nPosY++;
			return true;
		}
		if(m_uConfirmedBuffer[pNode->nPosX+1][pNode->nPosY+1])
		{
			pNode->nPosX++;
			pNode->nPosY++;
			return true;
		}
		break;
	default:
		break;
	}
	return false;
}




bool QLineMap::CalcShortestPath(unsigned int nBegin,unsigned int nEnd,std::vector<unsigned int> &vString)
{
	bool bVisit=false;int min;
	unsigned strNow=nBegin,strMin;
	std::map<unsigned int,std::map<unsigned int,PATHINFO>>::iterator wnit;
	std::map<unsigned int,PATHINFO>::iterator vnit;
	std::map<unsigned int,int>::iterator vvit;

	std::map<unsigned int,int> mValue;
	std::map<unsigned int,int> mVisited;

	std::map<unsigned int,int>::iterator stit;
	std::map<unsigned int,int>::iterator nit;
	std::map<unsigned int,unsigned int> mIndex;

	for(stit=m_mNodes.begin();stit!=m_mNodes.end();stit++)	//초기화
	{
		mVisited[stit->first]=0;
		mValue[stit->first]=99999;
		mIndex[stit->first]=0;
	}

	mValue[nBegin]=0;	//가중치가 가장 작은 경로




	for(stit=m_mNodes.begin();stit!=m_mNodes.end();stit++)
	{
		min=99999;
		for(vvit=mValue.begin();vvit!=mValue.end();vvit++)
		{
			if((vvit->second<min)&&(!mVisited[vvit->first]))
			{
				min=vvit->second;

				strNow=vvit->first;
			}
		}
		mVisited[strNow]=1;

		wnit=m_mPath.find(strNow);
		if(wnit!=m_mPath.end())
		{
			for(vnit=wnit->second.begin();vnit!=wnit->second.end();vnit++)
			{
				if(mValue[vnit->first]>(mValue[strNow]+vnit->second.vAngle->size()))
				{
					mValue[vnit->first]=mValue[strNow]+vnit->second.vAngle->size();
					mIndex[vnit->first]=strNow;
				}
			}
		}
	}
	
	std::vector<unsigned int> tmpString;
	nit=mValue.find(nEnd);
	if((nit!=mValue.end())&&(nit->second<99999))
	{
		strNow=nit->first;
		tmpString.push_back(strNow);
		while((mIndex.find(strNow)!=mIndex.end())&&(mIndex.find(strNow)->second))
		{
			strNow=mIndex[strNow];
			tmpString.push_back(strNow);
		}
		reverse(tmpString.begin(),tmpString.end());

		if(vString.size()&&((*vString.rbegin())==(*tmpString.begin())))
		{
			tmpString.erase(tmpString.begin());
		}
		vString.insert(vString.end(),tmpString.begin(),tmpString.end());
		return true;
	}
	return false;
}


bool QLineMap::CalcShortestPathForConfirmed(unsigned int nBegin,unsigned int nEnd,std::vector<unsigned int> &vString)
{
	bool bVisit=false;int min;
	unsigned strNow=nBegin,strMin;
	std::map<unsigned int,std::map<unsigned int,CONFIRMEDPATH>>::iterator wnit;
	std::map<unsigned int,CONFIRMEDPATH>::iterator vnit;
	std::map<unsigned int,int>::iterator vvit;

	std::map<unsigned int,int> mValue;
	std::map<unsigned int,int> mVisited;

	std::map<unsigned int,int>::iterator stit;
	std::map<unsigned int,int>::iterator nit;
	std::map<unsigned int,unsigned int> mIndex;

	for(stit=m_mConfirmedNodes.begin();stit!=m_mConfirmedNodes.end();stit++)	//초기화
	{
		mVisited[stit->first]=0;
		mValue[stit->first]=99999;
		mIndex[stit->first]=0;
	}

	mValue[nBegin]=0;	//가중치가 가장 작은 경로




	for(stit=m_mConfirmedNodes.begin();stit!=m_mConfirmedNodes.end();stit++)
	{
		min=99999;
		for(vvit=mValue.begin();vvit!=mValue.end();vvit++)
		{
			if((vvit->second<min)&&(!mVisited[vvit->first]))
			{
				min=vvit->second;

				strNow=vvit->first;
			}
		}
		mVisited[strNow]=1;

		wnit=m_mConfirmedPath.find(strNow);
		if(wnit!=m_mConfirmedPath.end())
		{
			for(vnit=wnit->second.begin();vnit!=wnit->second.end();vnit++)
			{
				if(mValue[vnit->first]>(mValue[strNow]+vnit->second.vAngle.size()))
				{
					mValue[vnit->first]=mValue[strNow]+vnit->second.vAngle.size();
					mIndex[vnit->first]=strNow;
				}
			}
		}
	}
	
	std::vector<unsigned int> tmpString;
	nit=mValue.find(nEnd);
	if((nit!=mValue.end())&&(nit->second<99999))
	{
		strNow=nit->first;
		tmpString.push_back(strNow);
		while((mIndex.find(strNow)!=mIndex.end())&&(mIndex.find(strNow)->second))
		{
			strNow=mIndex[strNow];
			tmpString.push_back(strNow);
		}
		reverse(tmpString.begin(),tmpString.end());

		if(vString.size()&&((*vString.rbegin())==(*tmpString.begin())))
		{
			tmpString.erase(tmpString.begin());
		}
		vString.insert(vString.end(),tmpString.begin(),tmpString.end());
		return true;
	}
	return false;
}

void QLineMap::generateArrow()
{
	//realignNodes();
}



BOOL GetEncCLSID(WCHAR *mime, CLSID *pClsid)
{
	UINT num,size,i;
	Gdiplus::ImageCodecInfo *arCod;
	 BOOL bFound=FALSE;
	 Gdiplus::GetImageEncodersSize(&num,&size);
	 arCod=(Gdiplus::ImageCodecInfo *)malloc(size);
	 Gdiplus::GetImageEncoders(num,size,arCod);
	 for (i=0;i<num;i++)
		  {
			  if(wcscmp(arCod[i].MimeType,mime)==0)
			  {
				  *pClsid=arCod[i].Clsid;
			   bFound=TRUE;
			   break;
		  }
	 }
	 free(arCod);
	 return bFound;
}




struct findStartEnd : public std::unary_function<std::shared_ptr<CSQLData>,bool>
{
	findStartEnd(unsigned int uStart,unsigned int uEnd)
		:m_uStart(uStart),m_uEnd(uEnd)
	{

	}
	bool operator ()(std::shared_ptr<CSQLData> pSI)
	{
		LineMapArrowTexture *pLMAT=(LineMapArrowTexture*)pSI.get();
		return ((pLMAT->uStart==m_uStart)&&(pLMAT->uEnd==m_uEnd));
	}
private:
	unsigned int m_uStart,m_uEnd;
};



void QLineMap::generateArrowFrom(unsigned short wStX,unsigned short wStY,unsigned short wEnX,unsigned short wEnY,int nBeginTrim,int nEndTrim)
{
	wchar_t szBuffer[256];
	std::vector<unsigned int> vSelNodes;
	std::vector<unsigned int>::iterator sit,pit;
	std::vector<unsigned int>::reverse_iterator rsit,rpit;
	unsigned int uStart=MAKECOORDKEY(wStX,wStY);
	unsigned int uEnd=MAKECOORDKEY(wEnX,wEnY);
	CalcShortestPathForConfirmed(uStart,uEnd,vSelNodes);
	
	bool bBegin=false;
	Gdiplus::Point tPtLineSt,tPtLineEn,tPtLinkSt,tPtLinkEn;
	Gdiplus::GraphicsPath tPath,tLinePath,tArcPath;
	Gdiplus::REAL fStartAngle;
	Gdiplus::REAL fSweepAngle;
	Gdiplus::Rect tArcRect;
	int nPrevItem=TILE_NONE;


	int nTotalBufferCount=0;
	for(sit=vSelNodes.begin();sit!=vSelNodes.end();sit++)
	{
		if(bBegin)
		{
			nTotalBufferCount+=m_mConfirmedPath[(*pit)][(*sit)].vPoint.size();
		}
		bBegin=true;
		pit=sit;
	}
	if(nTotalBufferCount>(nBeginTrim+nEndTrim))
	{
		int nTrimCount=nBeginTrim,nDiff,nBeginOffset,nEndOffset;
		bBegin=false;	
		sit=vSelNodes.begin();
		while(nTrimCount)
		{
			if(bBegin)
			{
				nDiff=nTrimCount-m_mConfirmedPath[(*pit)][(*sit)].vPoint.size();
				if(nDiff<0)
				{
					nBeginOffset=nTrimCount;
					nTrimCount=0;
				}	
				else
				{	
					sit=vSelNodes.erase(pit);
					nBeginOffset=nTrimCount=nDiff;
				}
			}
			bBegin=true;
			pit=sit++;
		}

		nTrimCount=nEndTrim;
		bBegin=false;

		rsit=vSelNodes.rbegin();
		while(nTrimCount)
		{
			if(bBegin)
			{
				nDiff=nTrimCount-m_mConfirmedPath[(*rsit)][(*rpit)].vPoint.size();
				if(nDiff<0)
				{
					nEndOffset=nTrimCount;
					nTrimCount=0;
				}	
				else
				{	vSelNodes.erase(vSelNodes.begin()+vSelNodes.size()-1);
					rsit=vSelNodes.rbegin();
					nEndOffset=nTrimCount=nDiff;
				}
			}
			bBegin=true;
			rpit=rsit++;
		}

		bBegin=false;


		std::vector<QPoint> vTmpPoint;
		std::vector<QPoint>::iterator stit,enit;
		rsit=vSelNodes.rbegin();


		Gdiplus::Pen P2(Gdiplus::Color::White,9.0f);
		P2.SetLineJoin(Gdiplus::LineJoin::LineJoinRound);


		Gdiplus::Pen P3(Gdiplus::Color::White,9.0f);
		P3.SetLineJoin(Gdiplus::LineJoin::LineJoinRound);
		P3.SetEndCap(Gdiplus::LineCap::LineCapArrowAnchor);
		
		tPath.SetFillMode(Gdiplus::FillModeWinding);


		for(sit=vSelNodes.begin();sit!=vSelNodes.end();sit++)
		{
			if(bBegin)
			{

				switch(m_mConfirmedPath[(*pit)][(*sit)].nItemType)
				{
				case TILE_H_U:
				case TILE_H_D:
					if((nPrevItem==TILE_NONE)||(nPrevItem==TILE_C_LU)||(nPrevItem==TILE_C_LD)||(nPrevItem==TILE_C_RD)||(nPrevItem==TILE_C_RU))
					{
						if(sit==(vSelNodes.begin()+1))
						{
							stit=m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()+nBeginOffset;
							tPtLineSt.X=(m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()+nBeginOffset)->x();
							tPtLineSt.Y=(m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()+nBeginOffset)->y();
						}
						else
						{
							if((nPrevItem==TILE_C_LU)||(nPrevItem==TILE_C_LD)||(nPrevItem==TILE_C_RD)||(nPrevItem==TILE_C_RU))
							{
								tArcPath.Widen(&P2);
								tArcPath.Outline();
								tPath.AddPath(&tArcPath,true);
								tArcPath.Reset();
							}
							stit=m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin();
							tPtLineSt.X=m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()->x();
							tPtLineSt.Y=m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()->y();
						}
						if((*sit)==(*vSelNodes.rbegin()))
						{
							enit=m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()+(m_mConfirmedPath[(*pit)][(*sit)].vPoint.size()-nEndOffset-1);
							tPtLineEn.X=(m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()+nEndOffset)->x();
							tPtLineEn.Y=(m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()+nEndOffset)->y();
						}
						else
						{
							enit=m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()+m_mConfirmedPath[(*pit)][(*sit)].vPoint.size()-1;
							tPtLineEn.X=m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()->x();
							tPtLineEn.Y=m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()->y();
						}
					}
					else if((nPrevItem==TILE_H_D)||(nPrevItem==TILE_H_U))
					{
						stit=m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin();
						if((*sit)==(*vSelNodes.rbegin()))
						{
							enit=m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()+(m_mConfirmedPath[(*pit)][(*sit)].vPoint.size()-nEndOffset-1);
							tPtLineEn.X=(m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()+nEndOffset)->x();
							tPtLineEn.Y=(m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()+nEndOffset)->y();
						}
						else
						{
							enit=m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()+m_mConfirmedPath[(*pit)][(*sit)].vPoint.size()-1;
							tPtLineEn.X=m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()->x();
							tPtLineEn.Y=m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()->y();
						}
					}
					else
					{
						tLinePath.AddLine(tPtLineSt,tPtLineEn);
						stit=m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin();
						tPtLineSt.X=m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()->x();
						tPtLineSt.Y=m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()->y();
						if((*sit)==(*vSelNodes.rbegin()))
						{
							enit=m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()+(m_mConfirmedPath[(*pit)][(*sit)].vPoint.size()-nEndOffset-1);
							tPtLineEn.X=(m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()+nEndOffset)->x();
							tPtLineEn.Y=(m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()+nEndOffset)->y();
						}
						else
						{
							enit=m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()+m_mConfirmedPath[(*pit)][(*sit)].vPoint.size()-1;
							tPtLineEn.X=m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()->x();
							tPtLineEn.Y=m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()->y();
						}
					}
					vTmpPoint.insert(vTmpPoint.end(),stit,enit);
					break;
				case TILE_H_L:
				case TILE_H_R:
					if((nPrevItem==TILE_NONE)||(nPrevItem==TILE_C_LU)||(nPrevItem==TILE_C_LD)||(nPrevItem==TILE_C_RD)||(nPrevItem==TILE_C_RU))
					{	
						if(sit==(vSelNodes.begin()+1))
						{
							stit=m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()+nBeginOffset;
							tPtLineSt.X=(m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()+nBeginOffset)->x();
							tPtLineSt.Y=(m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()+nBeginOffset)->y();
						}
						else
						{
							if((nPrevItem==TILE_C_LU)||(nPrevItem==TILE_C_LD)||(nPrevItem==TILE_C_RD)||(nPrevItem==TILE_C_RU))
							{
								tArcPath.Widen(&P2);
								tArcPath.Outline();
								tPath.AddPath(&tArcPath,true);
								tArcPath.Reset();
							}
							stit=m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin();
							tPtLineSt.X=m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()->x();
							tPtLineSt.Y=m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()->y();
						}
						if((*sit)==(*vSelNodes.rbegin()))
						{
							enit=m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()+(m_mConfirmedPath[(*pit)][(*sit)].vPoint.size()-nEndOffset-1);
							tPtLineEn.X=(m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()+nEndOffset)->x();
							tPtLineEn.Y=(m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()+nEndOffset)->y();
						}
						else
						{
							enit=m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()+m_mConfirmedPath[(*pit)][(*sit)].vPoint.size()-1;
							tPtLineEn.X=m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()->x();
							tPtLineEn.Y=m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()->y();
						}
					}
					else if((nPrevItem==TILE_H_L)||(nPrevItem==TILE_H_R))
					{
						stit=m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin();
						if((*sit)==(*vSelNodes.rbegin()))
						{
							enit=m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()+(m_mConfirmedPath[(*pit)][(*sit)].vPoint.size()-nEndOffset-1);
							tPtLineEn.X=(m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()+nEndOffset)->x();
							tPtLineEn.Y=(m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()+nEndOffset)->y();
						}
						else
						{
							enit=m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()+m_mConfirmedPath[(*pit)][(*sit)].vPoint.size()-1;
							tPtLineEn.X=m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()->x();
							tPtLineEn.Y=m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()->y();
						}
					}
					else
					{
						tLinePath.AddLine(tPtLineSt,tPtLineEn);
	
						stit=m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin();
						tPtLineSt.X=m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()->x();
						tPtLineSt.Y=m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()->y();
						if((*sit)==(*vSelNodes.rbegin()))
						{
							enit=m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()+(m_mConfirmedPath[(*pit)][(*sit)].vPoint.size()-nEndOffset-1);
							tPtLineEn.X=(m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()+nEndOffset)->x();
							tPtLineEn.Y=(m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()+nEndOffset)->y();
						}
						else
						{
							enit=m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()+m_mConfirmedPath[(*pit)][(*sit)].vPoint.size()-1;
							tPtLineEn.X=m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()->x();
							tPtLineEn.Y=m_mConfirmedPath[(*pit)][(*sit)].vPoint.rbegin()->y();
						}
					}
					vTmpPoint.insert(vTmpPoint.end(),stit,enit);
					break;
				case TILE_C_LU:
				case TILE_C_LD:
				case TILE_C_RD:
				case TILE_C_RU:

					if((nPrevItem==TILE_H_U)||(nPrevItem==TILE_H_D)||(nPrevItem==TILE_H_L)||(nPrevItem==TILE_H_R))
					{
						Gdiplus::GraphicsPath *pTmpPath;
						tLinePath.AddLine(tPtLineSt,tPtLineEn);
						pTmpPath=tLinePath.Clone();
						pTmpPath->Widen(&P2);
						pTmpPath->Outline();
						tPath.AddPath(pTmpPath,true);
						tLinePath.Reset();
					}

					tArcRect=Gdiplus::Rect(m_mConfirmedPath[(*pit)][(*sit)].tRect.x(),m_mConfirmedPath[(*pit)][(*sit)].tRect.y(),m_mConfirmedPath[(*pit)][(*sit)].tRect.width(),m_mConfirmedPath[(*pit)][(*sit)].tRect.height());
					tArcRect.Offset(1,1);
					if(sit==(vSelNodes.begin()+1))
					{
						stit=m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()+nBeginOffset;
						fStartAngle=(*(m_mConfirmedPath[(*pit)][(*sit)].vAngle.begin()+nBeginOffset));
						tPtLinkEn=Gdiplus::Point(stit->x(),stit->y());
					}
					else
					{
						stit=m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin();
						fStartAngle=(*m_mConfirmedPath[(*pit)][(*sit)].vAngle.begin());
						tPtLinkEn=Gdiplus::Point(stit->x(),stit->y());
					}
					tPtLineSt=tPtLineEn;
					if((*sit)==(*vSelNodes.rbegin()))
					{
						
						enit=m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()+(m_mConfirmedPath[(*pit)][(*sit)].vPoint.size()-nEndOffset-1);
						fSweepAngle=((*(m_mConfirmedPath[(*pit)][(*sit)].vAngle.rbegin()+nEndOffset))-fStartAngle);
					}
					else
					{
						enit=m_mConfirmedPath[(*pit)][(*sit)].vPoint.begin()+m_mConfirmedPath[(*pit)][(*sit)].vPoint.size()-1;
						fSweepAngle=(*m_mConfirmedPath[(*pit)][(*sit)].vAngle.rbegin())-fStartAngle;
					}


					
					tArcPath.AddArc(tArcRect,-fStartAngle,-fSweepAngle);
					if((*sit)==(*vSelNodes.rbegin()))
					{
						tArcPath.Widen(&P3);
						tArcPath.Outline();
						tPath.AddPath(&tArcPath,true);
						tArcPath.Reset();
					}
					vTmpPoint.insert(vTmpPoint.end(),stit,enit);
					break;
				default:
					break;
				}
				nPrevItem=m_mConfirmedPath[(*pit)][(*sit)].nItemType;
			}
			bBegin=true;
			pit=sit;
		}

		if((nPrevItem==TILE_H_U)||(nPrevItem==TILE_H_D)||(nPrevItem==TILE_H_L)||(nPrevItem==TILE_H_R))
		{
			Gdiplus::GraphicsPath *pTmpPath;
			tLinePath.AddLine(tPtLineSt,tPtLineEn);
			pTmpPath=tLinePath.Clone();;
			pTmpPath->Widen(&P3);
			pTmpPath->Outline();
			tPath.AddPath(pTmpPath,true);
		}



		Gdiplus::Rect tRect;
		

		tPath.GetBounds(&tRect);
		tRect.Inflate(10.f,10.f);

		Gdiplus::Pen P(Gdiplus::Color::White,1.0f);
		Gdiplus::Bitmap *pBitmap=new Gdiplus::Bitmap(tRect.X+tRect.Width,tRect.Y+tRect.Height,PixelFormat32bppARGB);
		Gdiplus::Graphics G(pBitmap);
		G.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
		G.DrawPath(&P,&tPath);
		G.FillPath(&Gdiplus::SolidBrush(Gdiplus::Color::White),&tPath);
		Gdiplus::BitmapData* bitmapData = new Gdiplus::BitmapData;
		std::shared_ptr<unsigned char> pByte=std::shared_ptr<unsigned char>((unsigned char*)malloc(((UINT)tRect.Width*(UINT)tRect.Height*4)),free);
		UINT *pDst=(UINT*)pByte.get();
		tRect.Inflate(-5.f,-5.f);
		pBitmap->LockBits(&tRect,Gdiplus::ImageLockModeRead,PixelFormat32bppARGB,bitmapData);
		UINT *pixels=(UINT*)bitmapData->Scan0;
		for(UINT row=0;row<tRect.Height;row++)
		{
			memcpy(pDst,pixels+(row*bitmapData->Stride/4),(UINT)(tRect.Width*sizeof(UINT)));
			pDst+=(UINT)tRect.Width;
		}

		
		delete pBitmap;
		delete bitmapData;



		QPoint tCur,tPrev;
		std::vector<QPoint>::iterator rit;
		rit=vTmpPoint.begin();
		while(rit!=vTmpPoint.end())
		{
			tCur=(*rit);
			if(tCur==tPrev)
			{
				rit=vTmpPoint.erase(rit);
			}
			else
				rit++;
			tPrev=tCur;
		}

		std::vector<sf::Vector2f> vConverted;
		rit=vTmpPoint.begin();
		while(rit!=vTmpPoint.end())
		{
			sf::Vector2f vV=sf::Vector2f((float)rit->x()-tRect.X,(float)rit->y()-tRect.Y);
			vConverted.push_back(vV);
			rit++;
		}


		CTileMapSupport *pTS=CTileMapSupport::GetInstance();
		sf::VertexArray tVA;
		//pTS->getPolyLineBuffer(vConverted, 11.f, tVA);
		tVA.setPrimitiveType(sf::TrianglesStrip);
		




		CDataManage *pDM=CDataManage::GetInstance();
		std::map<unsigned int,std::map<unsigned int,std::shared_ptr<CSQLData>>>::iterator fit;
		std::map<unsigned int,std::shared_ptr<CSQLData>>::iterator bit;
		bool bFind=false;

		std::vector<std::shared_ptr<CSQLData>>::iterator xit;

		xit=find_if(m_vArrow.begin(),m_vArrow.end(),findStartEnd(uStart,uEnd));
		if(xit!=m_vArrow.end())
		{
			LineMapArrowTexture *pLT=(LineMapArrowTexture*)xit->get();
			pLT->pByte=pByte;
			pLT->nSize=(UINT)tRect.Width*(UINT)tRect.Height*4;
			pLT->nOffsetX=tRect.X;
			pLT->nOffsetY=tRect.Y;
			pLT->nTexWidth=tRect.Width;
			pLT->nTexHeight=tRect.Height;
			pLT->uStart=uStart;
			pLT->uEnd=uEnd;
			pLT->tex.create(tRect.Width,tRect.Height);
			pLT->tex.update((sf::Uint8*)pByte.get());
			pLT->tex.setSmooth(true);
			pLT->spr.setColor(sf::Color::White);
			pLT->spr.setTexture(pLT->tex);
			pLT->finalSpr.setPosition(pLT->nOffsetX-1,pLT->nOffsetY-1);
			pLT->offTex.create(tRect.Width,tRect.Height);
			pLT->progTex.create(tRect.Width,tRect.Height);
			pLT->va=tVA;
			int nCount=pLT->va.getVertexCount();
			pLT->nVtxBufSize=nCount*2*sizeof(float);
			std::shared_ptr<unsigned char> pTmpByte=std::shared_ptr<unsigned char>((unsigned char*)malloc(pLT->nVtxBufSize),free);
			float *pf=(float*)pTmpByte.get();
			for(int i=0;i<nCount;i++)
			{
				pf[i*2]=pLT->va[i].position.x;
				pf[i*2+1]=pLT->va[i].position.y;
			}
			pLT->pByteVertex=pTmpByte;


			pLT->SetProgress(sf::Color::Red,sf::Color::Blue,100.f);


			bFind=true;
		}
		
		if(!bFind)
		{
			std::shared_ptr<CSQLData> pLML=m_pModel->insertRow(m_index);
			LineMapArrowTexture *pLT=(LineMapArrowTexture*)pLML.get();
			pLT->pByte=pByte;
			pLT->nSize=(UINT)tRect.Width*(UINT)tRect.Height*4;
			pLT->nOffsetX=tRect.X;
			pLT->nOffsetY=tRect.Y;
			pLT->nTexWidth=tRect.Width;
			pLT->nTexHeight=tRect.Height;
			pLT->uStart=uStart;
			pLT->uEnd=uEnd;
			pLT->tex.create(tRect.Width,tRect.Height);
			pLT->tex.update((sf::Uint8*)pByte.get());
			pLT->tex.setSmooth(true);
			pLT->spr.setColor(sf::Color::White);
			pLT->spr.setTexture(pLT->tex);
			pLT->finalSpr.setPosition(pLT->nOffsetX-1,pLT->nOffsetY-1);
			pLT->offTex.create(tRect.Width,tRect.Height);
			pLT->progTex.create(tRect.Width,tRect.Height);
			pLT->va=tVA;
			int nCount=pLT->va.getVertexCount();
			pLT->nVtxBufSize=nCount*2*sizeof(float);
			std::shared_ptr<unsigned char> pTmpByte=std::shared_ptr<unsigned char>((unsigned char*)malloc(pLT->nVtxBufSize),free);
			float *pf=(float*)pTmpByte.get();
			for(int i=0;i<nCount;i++)
			{
				pf[i*2]=pLT->va[i].position.x;
				pf[i*2+1]=pLT->va[i].position.y;
			}
			pLT->pByteVertex=pTmpByte;
			pLT->SetProgress(sf::Color::Red,sf::Color::Blue,100.f);
			m_vArrow=(*m_pvArrow);



			const QModelIndex index=m_index;
			emit makeItemExpended(index,true);
			nCount=m_pModel->rowCount(m_index);
			const QModelIndex index2=m_pModel->index(nCount-1,0,m_index);
			emit setCurrentModelIndex(index2);
		}
	}
}


void QLineMap::alignNodes()
{
	syncData();
	QPoint ptPrev;
	bool bBegin=false;
	int nOffset,nCount=0;
	unsigned int uStart,uEnd;
	std::vector<QPoint> vTempPoint;	
	std::vector<unsigned int>::iterator tmit;
	std::vector<unsigned int> vTempBuffer;
	std::vector<unsigned int>::iterator vit;
	std::vector<QPoint>::iterator kit;
	std::vector<std::shared_ptr<CSQLData>>::iterator pit;

	std::map<unsigned int,std::vector<int>> mMap;
	std::map<unsigned int,std::vector<int>>::iterator mit;
	std::vector<int>::iterator xit;




	std::vector<std::shared_ptr<CSQLData>> vTempNode;
	if(m_vSelNodes.size())
	{
		uStart=m_vSelNodes.at(0);
		tmit=++m_vSelNodes.begin();

		for(;tmit!=m_vSelNodes.end();tmit++)
		{
			uEnd=(*tmit);
			CalcShortestPath(uStart,uEnd,vTempBuffer);
			uStart=(*tmit);
		}

		m_vNodesTemp=vTempBuffer;
	
		uStart=m_vSelNodes.at(0);
		vit=++vTempBuffer.begin();
		for(;vit!=vTempBuffer.end();vit++)
		{
			uEnd=(*vit);
			if(m_mPath[uStart][uEnd].vPoint->size())
			{
				nOffset=(ptPrev==m_mPath[uStart][uEnd].vPoint->at(0))?1:0;
				vTempPoint.insert(vTempPoint.end(),m_mPath[uStart][uEnd].vPoint->begin()+nOffset,m_mPath[uStart][uEnd].vPoint->end());
				ptPrev=(*vTempPoint.rbegin());
			}
			uStart=uEnd;
		}

		//Initialize Node Buffer;
		std::vector<std::shared_ptr<CSQLData>>::iterator nit;
		for(nit=m_vNode.begin();nit!=m_vNode.end();nit++)
		{
			LineMapNode *pItem=(LineMapNode*)nit->get();

			unsigned long nKey=MAKECOORDKEY((WORD)pItem->nPosX,(WORD)pItem->nPosY);
			mMap[nKey].push_back(pItem->GetIndex());
		}

		int nOffsetFront=0;
		int nOffsetRear=0;
		bool bFindFront=false;
		for(kit=vTempPoint.begin();kit!=vTempPoint.end();kit++)
		{
			unsigned long nKey=MAKECOORDKEY((WORD)kit->x(),(WORD)kit->y());
			mit=mMap.find(nKey);
			if(mit!=mMap.end())
			{
				for(xit=mit->second.begin();xit!=mit->second.end();xit++)
				{
					pit=find_if(m_vNode.begin(),m_vNode.end(),findSQLData((*xit)));
					if(pit!=m_vNode.end())
					{
						nOffsetRear=distance(vTempPoint.begin(),kit);
						if(!bFindFront)
						{
							nOffsetFront=nOffsetRear;
							bFindFront=true;
						}
						vTempNode.push_back((*pit));
					}
				}
			}
		}
		
		nOffsetFront--;
		nOffsetRear++;

		//Trimming from both tail.
		if(nOffsetRear<=vTempPoint.size())
			vTempPoint.erase(vTempPoint.begin()+nOffsetRear,vTempPoint.end());

		if(nOffsetFront>=0)
			vTempPoint.erase(vTempPoint.begin(),vTempPoint.begin()+nOffsetFront);

		float fOffset=(float)(vTempPoint.size()-vTempNode.size())/(float)(vTempNode.size()-1);
		fOffset+=1.0f;
		float fCurPos=0;

		// 
		for(pit=vTempNode.begin();pit!=vTempNode.end();pit++)
		{
			LineMapNode *pItem=(LineMapNode*)pit->get();
			int nPos=(int)fCurPos;
			pItem->nPosX=vTempPoint.at(nPos).x();
			pItem->nPosY=vTempPoint.at(nPos).y();
			fCurPos+=fOffset;

			if(pItem->GetRecordState()==EDIT_NOT_MODIFIED)
				pItem->SetRecordState(EDIT_UPDATED);
		}
	}
	update();
}


void QLineMap::realignNodes()
{
	std::vector<QPoint> vTmpPoint;
	std::vector<qreal> vTmpAngle;
	std::vector<QPoint>::iterator itp;
	std::vector<qreal>::iterator itr;
	ZeroMemory(m_uNodeBuffer,sizeof(m_uNodeBuffer));
	std::vector<std::shared_ptr<CSQLData>>::iterator vit;
	for(vit=m_vNode.begin();vit!=m_vNode.end();vit++)
	{
		LineMapNode *pItem=(LineMapNode*)vit->get();
		m_uNodeBuffer[pItem->nPosX][pItem->nPosY]=10;
	}


	std::map<unsigned int,std::map<unsigned int,PATHINFO>>::iterator tit;
	std::map<unsigned int,PATHINFO>::iterator sit;
	std::map<int,std::shared_ptr<CSQLData>>::iterator xit;
	std::vector<PATHINFO> vPathInfo;

	m_mConfirmedPath.clear();
	m_mConfirmedNodes.clear();


	CONFIRMEDPATH tPath;
	unsigned int uStIndex,uEnIndex,uFinalIndex;
	for(tit=m_mPath.begin();tit!=m_mPath.end();tit++)
	{
		for(sit=tit->second.begin();sit!=tit->second.end();sit++)
		{
			itp=sit->second.vPoint->begin();
			itr=sit->second.vAngle->begin();
			

			vTmpPoint.clear();
			vTmpAngle.clear();
	
			tPath.nItemType=sit->second.pLink->nItemType;
			tPath.tRect=sit->second.pLink->m_tArcRect;
			
			uStIndex=((itp->x()&0x0000FFFF)<<16)|(itp->y()&0x0000FFFF);
			while((itp!=sit->second.vPoint->end())&&(itr!=sit->second.vAngle->end()))
			{
				vTmpPoint.push_back(*itp);
				vTmpAngle.push_back(*itr);
				if((itp!=sit->second.vPoint->begin())&&(itp!=(sit->second.vPoint->begin()+sit->second.vPoint->size())))
				{
					if(m_uNodeBuffer[itp->x()][itp->y()]==10)
					{
						tPath.vPoint=vTmpPoint;
						tPath.vAngle=vTmpAngle;
						uEnIndex=((itp->x()&0x0000FFFF)<<16)|(itp->y()&0x0000FFFF);
						
						m_mConfirmedPath[uStIndex][uEnIndex]=tPath;
			
						vTmpPoint.erase(vTmpPoint.begin(),vTmpPoint.begin()+vTmpPoint.size()-1);
						vTmpAngle.erase(vTmpAngle.begin(),vTmpAngle.begin()+vTmpAngle.size()-1);
						uStIndex=uEnIndex;
					}
				}
				uFinalIndex=((itp->x()&0x0000FFFF)<<16)|(itp->y()&0x0000FFFF);
				itp++;
				itr++;
			}
			
			tPath.vPoint=vTmpPoint;
			tPath.vAngle=vTmpAngle;



			m_mConfirmedPath[uStIndex][uFinalIndex]=tPath;


		}
	}



	wchar_t szBuffer[256];

	std::map<unsigned int,std::map<unsigned int,CONFIRMEDPATH>>::iterator ait;
	std::map<unsigned int,CONFIRMEDPATH>::iterator bit;
	
	int nCount=0;
	
	for(ait=m_mConfirmedPath.begin();ait!=m_mConfirmedPath.end();ait++)
	{
		m_mConfirmedNodes[ait->first]++;
		for(bit=ait->second.begin();bit!=ait->second.end();bit++)
		{
			m_mConfirmedNodes[bit->first]++;
			nCount++;
			/*swprintf_s(szBuffer,_countof(szBuffer),L"%d: (%u,%u),(%u,%u),%d\n",nCount,(ait->first>>16)&0x0000FFFF,(ait->first)&0x0000FFFF,(bit->first>>16)&0x0000FFFF,(bit->first)&0x0000FFFF,bit->second.vPoint.size());
			OutputDebugString(szBuffer);*/
		}
	}
	for(tit=m_mPath.begin();tit!=m_mPath.end();tit++)
	{
		for(sit=tit->second.begin();sit!=tit->second.end();sit++)
		{
			nCount++;
			/*swprintf_s(szBuffer,_countof(szBuffer),L"%d: (%u,%u),(%u,%u),%d\n",nCount,(tit->first>>16)&0x0000FFFF,(tit->first)&0x0000FFFF,(sit->first>>16)&0x0000FFFF,(sit->first)&0x0000FFFF,sit->second.vPoint->size());
			OutputDebugString(szBuffer);*/
		}
	}
}


void QLineMap::contextMenu(const QPoint &pos)
{
	int nOriginPosX=m_nLatestPosX=pos.x()+nInitPosX;
	int nOriginPosY=m_nLatestPosY=pos.y()+nInitPosY;
	switch(m_tMapMode)
	{
	case 0:
		m_pLinkMenu->popup(mapToGlobal(pos));
		break;
	case 3:
		if(!m_bCtrlKeyPressed)
		{
			m_nSelectedNode=-1;
			std::vector<std::shared_ptr<CSQLData>>::iterator vit;
			for(vit=m_vNode.begin();vit!=m_vNode.end();vit++)
			{
				LineMapNode *pNode=(LineMapNode*)vit->get();
				sf::IntRect tRect(pNode->nPosX-15,pNode->nPosY-15,30,30);
				if(tRect.contains(nOriginPosX,nOriginPosY))
				{
					m_nSelectedNode=vit->get()->GetIndex();
				}
			}
			if(setNodeActions(m_nSelectedNode,nOriginPosX,nOriginPosY))
				m_pNodeMenu->popup(mapToGlobal(pos));
		}
		else
		{
			if(m_vSelNodes.size())
				m_pAlignMenu->popup(mapToGlobal(pos));
		}
		break;
	}
}

void QLineMap::InitAlignMenu()
{
	QAction *pAction;
	m_pAlignMenu=new QMenu("Align nodes in selected basic nodes",this);

	pAction=new QAction(QIcon(":/PACEditor4/Resources/TILE_NONE.bmp"),"Align",this);
	pAction->setData(1);
	m_pAlignMenu->addAction(pAction);



	connect(m_pAlignMenu, SIGNAL(triggered(QAction*)), this, SLOT(selectAction(QAction*)));

}

void QLineMap::InitNodeMenu()
{	
	QAction *pAction;
	m_pNodeMenu=new QMenu("Edit Node",this);

	pAction=new QAction(QIcon(":/PACEditor4/Resources/TILE_NONE.bmp"),"Add Node",this);
	pAction->setData(1);
	m_pNodeMenu->addAction(pAction);

	pAction=new QAction(QIcon(":/PACEditor4/Resources/TILE_NONE.bmp"),"Delete Node",this);
	pAction->setData(2);
	m_pNodeMenu->addAction(pAction);


	connect(m_pNodeMenu, SIGNAL(triggered(QAction*)), this, SLOT(selectAction(QAction*)));
}

void QLineMap::InitLinkMenu()
{	
	QAction *pAction;
	m_pLinkMenu=new QMenu("Select tile",this);
	for(int i=TILE_NONE;i<TILE_C_RU+1;i++)
	{
		switch(i)
		{
		case TILE_NONE:
			pAction=new QAction(QIcon(":/PACEditor4/Resources/TILE_NONE.bmp"),"TILE_NONE",this);
			pAction->setData(i);
			m_pLinkMenu->addAction(pAction);
			break;
		case TILE_H_U:
			pAction=new QAction(QIcon(":/PACEditor4/Resources/TILE_H_U.bmp"),"TILE_H_U",this);
			pAction->setData(i);
			m_pLinkMenu->addAction(pAction);
			break;
		case TILE_H_D:
			pAction=new QAction(QIcon(":/PACEditor4/Resources/TILE_H_D.bmp"),"TILE_H_D",this);
			pAction->setData(i);
			m_pLinkMenu->addAction(pAction);
			break;
		case TILE_H_L:
			pAction=new QAction(QIcon(":/PACEditor4/Resources/TILE_H_L.bmp"),"TILE_H_L",this);
			pAction->setData(i);
			m_pLinkMenu->addAction(pAction);
			break;
		case TILE_H_R:
			pAction=new QAction(QIcon(":/PACEditor4/Resources/TILE_H_R.bmp"),"TILE_H_R",this);
			pAction->setData(i);
			m_pLinkMenu->addAction(pAction);
			break;
		case TILE_F_UD:
			pAction=new QAction(QIcon(":/PACEditor4/Resources/TILE_F_UD.bmp"),"TILE_F_UD",this);
			pAction->setData(i);
			m_pLinkMenu->addAction(pAction);
			break;
		case TILE_F_LR:
			pAction=new QAction(QIcon(":/PACEditor4/Resources/TILE_F_LR.bmp"),"TILE_F_LR",this);
			pAction->setData(i);
			m_pLinkMenu->addAction(pAction);
			break;
		case TILE_CROSS:
			pAction=new QAction(QIcon(":/PACEditor4/Resources/TILE_CROSS.bmp"),"TILE_CROSS",this);
			pAction->setData(i);
			m_pLinkMenu->addAction(pAction);
			break;
		case TILE_F_UD_H_L:
			pAction=new QAction(QIcon(":/PACEditor4/Resources/TILE_F_UD_H_L.bmp"),"TILE_F_UD_H_L",this);
			pAction->setData(i);
			m_pLinkMenu->addAction(pAction);
			break;
		case TILE_F_UD_H_R:
			pAction=new QAction(QIcon(":/PACEditor4/Resources/TILE_F_UD_H_R.bmp"),"TILE_F_UD_H_R",this);
			pAction->setData(i);
			m_pLinkMenu->addAction(pAction);
			break;
		case TILE_F_LR_H_U:
			pAction=new QAction(QIcon(":/PACEditor4/Resources/TILE_F_LR_H_U.bmp"),"TILE_F_LR_H_U",this);
			pAction->setData(i);
			m_pLinkMenu->addAction(pAction);
			break;
		case TILE_F_LR_H_D:
			pAction=new QAction(QIcon(":/PACEditor4/Resources/TILE_F_LR_H_D.bmp"),"TILE_F_LR_H_D",this);
			pAction->setData(i);
			m_pLinkMenu->addAction(pAction);
			break;
		case TILE_C_LU:
			pAction=new QAction(QIcon(":/PACEditor4/Resources/TILE_C_LU.bmp"),"TILE_C_LU",this);
			pAction->setData(i);
			m_pLinkMenu->addAction(pAction);
			break;
		case TILE_C_LD:
			pAction=new QAction(QIcon(":/PACEditor4/Resources/TILE_C_LD.bmp"),"TILE_C_LD",this);
			pAction->setData(i);
			m_pLinkMenu->addAction(pAction);
			break;
		case TILE_C_RD:
			pAction=new QAction(QIcon(":/PACEditor4/Resources/TILE_C_RD.bmp"),"TILE_C_RD",this);
			pAction->setData(i);
			m_pLinkMenu->addAction(pAction);
			break;
		case TILE_C_RU:
			pAction=new QAction(QIcon(":/PACEditor4/Resources/TILE_C_RU.bmp"),"TILE_C_RU",this);
			pAction->setData(i);
			m_pLinkMenu->addAction(pAction);
			break;
		default:
			break;
		}
	}
	connect(m_pLinkMenu, SIGNAL(triggered(QAction*)), this, SLOT(selectAction(QAction*)));
}


void QLineMap::selectAction(QAction *action)
{
	int nValue = action->data().toInt();
	switch(m_tMapMode)
	{
	case 0:
		addTileBySelection((TileType)nValue,m_nLatestPosX,m_nLatestPosY);
		break;
	case 3:
		if(!m_bCtrlKeyPressed)
		{
			switch(nValue)
			{
			case 1:
				addNode(m_nLatestPosX,m_nLatestPosY);
				break;
			case 2:
				deleteNode(m_nSelectedNode);
				break;
			}
		}
		else
		{
			switch(nValue)
			{
			case 1:
				break;
			default:
				break;
			}
		}
		break;
	default:
		break;
	}
}

void QLineMap::addNode(int nPosX,int nPosY)
{
	int nMinXPos,nMinYPos;
	if(getMinCoordFromBuffer(nPosX,nPosY,&nMinXPos,&nMinYPos))
	{
		std::shared_ptr<CSQLData> pLM=m_pModel->insertRow(m_index);
		LineMapNode *pLMN=(LineMapNode*)pLM.get();
		pLMN->nPosX=nMinXPos;
		pLMN->nPosY=nMinYPos;
		m_vNode=(*m_pvNode);

			const QModelIndex index=m_index;
		emit makeItemExpended(index,true);
		int nCount=m_pModel->rowCount(m_index);
		const QModelIndex index2=m_pModel->index(nCount-1,0,m_index);
		emit setCurrentModelIndex(index2);
	}
}

void QLineMap::deleteNode(int nSelectedIndex)
{
	m_pModel->removeRowByIndex(nSelectedIndex,m_index);
	m_vNode=(*m_pvNode);

	const QModelIndex index=m_index;
	emit makeItemExpended(index,true);
	int nCount=m_pModel->rowCount(m_index);
	const QModelIndex index2=m_pModel->index(nCount-1,0,m_index);
	emit setCurrentModelIndex(index2);
}


void QLineMap::addTileBySelection(TileType tAddTile,int nPosX,int nPosY)
{
	int nIndex;
	bool bDeleted=false;
	CDataManage *pDM=CDataManage::GetInstance();
	int nCurX=(int)(nPosX/m_nBlockSize)*m_nBlockSize+(m_nBlockSize/2);
	int nCurY=(int)(nPosY/m_nBlockSize)*m_nBlockSize+(m_nBlockSize/2);
	std::vector<std::shared_ptr<CSQLData>>::iterator vit;
	m_tmpIndex=m_index;
	for(vit=m_vLink.begin();vit!=m_vLink.end();)
	{
		LineMapLink *pItem=(LineMapLink*)vit->get();
		if((nCurX==pItem->nPosX)&&(nCurY==pItem->nPosY)&&(tAddTile!=pItem->nItemType))
		{
			switch(tAddTile)
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
				nIndex=vit->get()->GetIndex();
				resetPos(pItem);
				vit=m_vLink.erase(vit);
				m_pModel->removeRowByIndex(nIndex,m_tmpIndex);
				bDeleted=true;
				break;
			default:
				break;
			}
			if(!bDeleted)
			{
				switch(pItem->nItemType)
				{	
				case TILE_H_U:
				case TILE_H_D:
				case TILE_H_L:
				case TILE_H_R:
					vit++;
					break;
				default:
					nIndex=vit->get()->GetIndex();
					resetPos(pItem);
					vit=m_vLink.erase(vit);
					m_pModel->removeRowByIndex(nIndex,m_tmpIndex);
					break;
				}
			}
		}
		else
			vit++;
	}



	if(TILE_NONE!=tAddTile)
	{
		switch(tAddTile)
		{
		case TILE_F_UD:
			addLink(TILE_H_U,nCurX,nCurY);
			addLink(TILE_H_D,nCurX,nCurY);
			break;
		case TILE_F_LR:
			addLink(TILE_H_L,nCurX,nCurY);
			addLink(TILE_H_R,nCurX,nCurY);
			break;
		case TILE_CROSS:
			addLink(TILE_H_U,nCurX,nCurY);
			addLink(TILE_H_D,nCurX,nCurY);
			addLink(TILE_H_L,nCurX,nCurY);
			addLink(TILE_H_R,nCurX,nCurY);
			break;
		case TILE_F_UD_H_L:
			addLink(TILE_H_U,nCurX,nCurY);
			addLink(TILE_H_D,nCurX,nCurY);
			addLink(TILE_H_L,nCurX,nCurY);
			break;
		case TILE_F_UD_H_R:
			addLink(TILE_H_U,nCurX,nCurY);
			addLink(TILE_H_D,nCurX,nCurY);
			addLink(TILE_H_R,nCurX,nCurY);
			break;
		case TILE_F_LR_H_U:
			addLink(TILE_H_L,nCurX,nCurY);
			addLink(TILE_H_R,nCurX,nCurY);
			addLink(TILE_H_U,nCurX,nCurY);
			break;
		case TILE_F_LR_H_D:
			addLink(TILE_H_L,nCurX,nCurY);
			addLink(TILE_H_R,nCurX,nCurY);
			addLink(TILE_H_D,nCurX,nCurY);
			break;
		default:
			addLink(tAddTile,nCurX,nCurY);
			break;
		}
	}
	const QModelIndex index=m_index;
	emit makeItemExpended(index,true);
	int nCount=m_pModel->rowCount(m_index);
	const QModelIndex index2=m_pModel->index(nCount-1,0,m_index);
	emit setCurrentModelIndex(index2);
}

bool QLineMap::setNodeActions(int nSelectedNode,int nPosX,int nPosY)
{
	int nMinXPos,nMinYPos;
	QList<QAction*> lAction=m_pNodeMenu->actions();
	QList<QAction*>::iterator vit;
	if(nSelectedNode!=-1)
	{
		for(vit=lAction.begin();vit!=lAction.end();vit++)
		{
			switch((*vit)->data().toInt())
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
		if(getMinCoordFromBuffer(nPosX,nPosY,&nMinXPos,&nMinYPos))
		{
			for(vit=lAction.begin();vit!=lAction.end();vit++)
			{
				switch((*vit)->data().toInt())
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

bool QLineMap::getMinCoordFromBuffer(int nXPosRef,int nYPosRef,int *pXPos,int *pYPos)
{
	CDataManage *pDM=CDataManage::GetInstance();
	int nLeftBound=nXPosRef-20;
	int nTopBound=nYPosRef-20;
	//하한 설정
	nLeftBound=(nLeftBound<0)?0:nLeftBound;
	nTopBound=(nTopBound<0)?0:nTopBound;
	//상한 설정
	//nLeftBound=(nLeftBound<0)?0:nLeftBound;
	//nTopBound=(nTopBound<0)?0:nTopBound;
	(*pYPos)=(*pXPos)=0;
	double dMin=9999999.0;
	bool bFound=false;	
	for(int j=nTopBound;j<(nTopBound+40);j++)
	{
		for(int i=nLeftBound;i<(nLeftBound+40);i++)
		{	
			if(m_uConfirmedBuffer[i][j])
			{
				double dX=pow((double)nXPosRef-(double)i,(double)2);
				double dY=pow((double)nYPosRef-(double)j,(double)2);
				double dDistance=sqrt(dX+dY);
				dMin=min(dDistance,dMin);
				if(dMin==dDistance)
				{
					bFound=true;
					(*pXPos)=i;
					(*pYPos)=j;
				}
			}
		}
	}
	return bFound;
}



void QLineMap::syncData()
{
	m_vLink=(*m_pvLink);
	m_vNode=(*m_pvNode);
	m_vArrow=(*m_pvArrow);
}