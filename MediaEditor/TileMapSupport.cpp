#include <minmax.h>
#include <windows.h>
#include <Gdiplus.h>
#include "TileMapSupport.h"
#include "defineTileMap.h"
#include <QtGui>
#include <QDebug>

CTileMapSupport::CTileMapSupport(void)
{
}

CTileMapSupport::~CTileMapSupport(void)
{
}


CTileMapSupport *CTileMapSupport::GetInstance()
{
	static CTileMapSupport tDataManage;
	return &tDataManage;
}

int CTileMapSupport::GenerateTilePath(int nUnitSize,int nStrokeSize)
{
	QPainterPath path;
	int nHalfSize=(nUnitSize/2);
	unsigned __int64 uKey=(((nUnitSize&0x0000FFFF)<<16)|(nStrokeSize&0x0000FFFF));
	unsigned __int64 uValue;


	

	int nBeginAngle=0;
	int nEndAngle=90;
	for(int i=TILE_NONE;i<(TILE_C_RU+1);i++)
	{
		switch(i)
		{
		case TILE_H_U:
			{
				uValue=(((unsigned __int64)uKey<<32)|((unsigned __int64)i));
				QPainterPath curvePath,curveRevPath;
				curvePath.moveTo(QPoint(0,0));
				curvePath.lineTo(QPoint(0,-nHalfSize));
				qreal length=curvePath.length();
				QPainterPathStroker tStroker;
				tStroker.setCapStyle(Qt::FlatCap);
				tStroker.setWidth(nStrokeSize);
				QPainterPath outline=tStroker.createStroke(curvePath);
				qreal outlinelength=outline.length();


				m_mTilePath[uValue]=curvePath;
				m_mPolygon[uValue]=outline.toFillPolygon();
			}
			 break;
		case TILE_H_D:
			{
				uValue=(((unsigned __int64)uKey<<32)|((unsigned __int64)i));
				QPainterPath curvePath,curveRevPath;
				curvePath.moveTo(QPoint(0,0));
				curvePath.lineTo(QPoint(0,nHalfSize));
				qreal length=curvePath.length();

				QPainterPathStroker tStroker;
				tStroker.setCapStyle(Qt::FlatCap);
				tStroker.setWidth(nStrokeSize);
				QPainterPath outline=tStroker.createStroke(curvePath);
				qreal outlinelength=outline.length();


				m_mTilePath[uValue]=curvePath;
				m_mPolygon[uValue]=outline.toFillPolygon();
			}
			 break;
		case TILE_H_L:
			 {
				uValue=(((unsigned __int64)uKey<<32)|((unsigned __int64)i));
				QPainterPath curvePath,curveRevPath;
				curvePath.moveTo(QPoint(0,0));
				curvePath.lineTo(QPoint(-nHalfSize,0));
				qreal length=curvePath.length();

				QPainterPathStroker tStroker;
				tStroker.setCapStyle(Qt::FlatCap);
				tStroker.setWidth(nStrokeSize);
				QPainterPath outline=tStroker.createStroke(curvePath);
				qreal outlinelength=outline.length();



				m_mTilePath[uValue]=curvePath;
				m_mPolygon[uValue]=outline.toFillPolygon();
			 }
			 break;
		case TILE_H_R:
			{
				uValue=(((unsigned __int64)uKey<<32)|((unsigned __int64)i));
				QPainterPath curvePath,curveRevPath;
				curvePath.moveTo(QPoint(0,0));
				curvePath.lineTo(QPoint(nHalfSize,0));
				qreal length=curvePath.length();

				QPainterPathStroker tStroker;
				tStroker.setCapStyle(Qt::FlatCap);
				tStroker.setWidth(nStrokeSize);
				QPainterPath outline=tStroker.createStroke(curvePath);
				qreal outlinelength=outline.length();

	

				m_mTilePath[uValue]=curvePath;
				m_mPolygon[uValue]=outline.toFillPolygon();
			 }
			 break;
		case TILE_C_LU:
			{
				uValue=(((unsigned __int64)uKey<<32)|((unsigned __int64)i));
				QRect arcRect=QRect(-nUnitSize,-nUnitSize,nUnitSize,nUnitSize);
				QPainterPath curvePath,curveRevPath;
				curvePath.arcMoveTo(arcRect,270);
				curvePath.arcTo(arcRect,270,90);
				qreal length=curvePath.length();

				QPainterPathStroker tStroker;
				tStroker.setCapStyle(Qt::FlatCap);
				tStroker.setWidth(nStrokeSize);
				QPainterPath outline=tStroker.createStroke(curvePath);
				qreal outlinelength=outline.length();

				m_mTilePath[uValue]=curvePath;
				m_mPolygon[uValue]=outline.toFillPolygon();
				m_mArcRect[uValue]=arcRect;
				
			}


			
			break;
		case TILE_C_LD:
			{
				uValue=(((unsigned __int64)uKey<<32)|((unsigned __int64)i));
				QRect arcRect=QRect(-nUnitSize,0,nUnitSize,nUnitSize);
				QPainterPath curvePath,curveRevPath;
				curvePath.arcMoveTo(arcRect,0);
				curvePath.arcTo(arcRect,0,90);

				qreal qlen=curvePath.length();
				QPainterPathStroker tStroker;
				tStroker.setCapStyle(Qt::FlatCap);
				tStroker.setWidth(nStrokeSize);
				QPainterPath outline=tStroker.createStroke(curvePath);
				qreal outlinelength=outline.length();

				m_mTilePath[uValue]=curvePath;
				m_mPolygon[uValue]=outline.toFillPolygon();
				m_mArcRect[uValue]=arcRect;

		
			}
            break;
		case TILE_C_RD:
			{
				uValue=(((unsigned __int64)uKey<<32)|((unsigned __int64)i));
				QRect arcRect=QRect(0,0,nUnitSize,nUnitSize);
				QPainterPath curvePath,curveRevPath;
				curvePath.arcMoveTo(arcRect,90);
				curvePath.arcTo(arcRect,90,90);
				qreal qlen=curvePath.length();
				QPainterPathStroker tStroker;
				tStroker.setCapStyle(Qt::FlatCap);
				tStroker.setWidth(nStrokeSize);
				QPainterPath outline=tStroker.createStroke(curvePath);
				qreal outlinelength=outline.length();


				m_mTilePath[uValue]=curvePath;
				m_mPolygon[uValue]=outline.toFillPolygon();
				m_mArcRect[uValue]=arcRect;
			}

			 break;
		case TILE_C_RU:
			{
				uValue=(((unsigned __int64)uKey<<32)|((unsigned __int64)i));
				QRect arcRect=QRect(0,-nUnitSize,nUnitSize,nUnitSize);
				QPainterPath curvePath,curveRevPath;
				curvePath.arcMoveTo(arcRect,180);
				curvePath.arcTo(arcRect,180,90);



				//m_tPath=curvePath;
				QPainterPathStroker tStroker;
				tStroker.setCapStyle(Qt::FlatCap);
				tStroker.setWidth(nStrokeSize);
				QPainterPath outline=tStroker.createStroke(curvePath);
				qreal outlinelength=outline.length();


				m_mTilePath[uValue]=curvePath;
				m_mPolygon[uValue]=outline.toFillPolygon();
				m_mArcRect[uValue]=arcRect;
			}
            break;
        default:
            break;
		}
	}
	return true;
}




QPainterPath CTileMapSupport::GetPath(int nUnitSize,int nStrokeSize,int nTile,int nX,int nY)
{
	QPainterPath tmpPath;
	unsigned __int64 uKey=(((nUnitSize&0x0000FFFF)<<16)|(nStrokeSize&0x0000FFFF));
	unsigned __int64 uValue=uValue=(((unsigned __int64)uKey<<32)|((unsigned __int64)nTile));
	std::map<unsigned __int64,QPainterPath>::iterator nit;
	nit=m_mTilePath.find(uValue);
	if(nit!=m_mTilePath.end())
	{
		tmpPath=nit->second;
		tmpPath.translate(nX,nY);
	}
	return tmpPath;
}

QPolygonF CTileMapSupport::GetPolygon(int nUnitSize,int nStrokeSize,int nTile,int nX,int nY)
{
	QPolygonF tmpPolygon;
	unsigned __int64 uKey=(((nUnitSize&0x0000FFFF)<<16)|(nStrokeSize&0x0000FFFF));
	unsigned __int64 uValue=uValue=(((unsigned __int64)uKey<<32)|((unsigned __int64)nTile));
	std::map<unsigned __int64,QPolygonF>::iterator nit;
	nit=m_mPolygon.find(uValue);
	if(nit!=m_mPolygon.end())
	{
		tmpPolygon=nit->second;
		tmpPolygon.translate(nX,nY);
	}
	return tmpPolygon;
}


void CTileMapSupport::GetAngles(int nTile,int *pStart,int *pEnd)
{
	switch(nTile)
	{
	case TILE_C_LU:
		{
			(*pStart)=270;
			(*pEnd)=360;
		}
		break;
	case TILE_C_LD:
		{
			(*pStart)=0;
			(*pEnd)=90;
		}
        break;
	case TILE_C_RD:
		{
			(*pStart)=90;
			(*pEnd)=180;
		}
		 break;
	case TILE_C_RU:
		{
			(*pStart)=180;
			(*pEnd)=270;
		}
        break;
    default:
		(*pStart)=0;
		(*pEnd)=0;
        break;
	}
}

QRect CTileMapSupport::GetArcRect(int nUnitSize,int nStrokeSize,int nTile,int nX,int nY)
{
	QRect tRect;
	unsigned __int64 uKey=(((nUnitSize&0x0000FFFF)<<16)|(nStrokeSize&0x0000FFFF));
	unsigned __int64 uValue=uValue=(((unsigned __int64)uKey<<32)|((unsigned __int64)nTile));
	std::map<unsigned __int64,QRect>::iterator nit;
	nit=m_mArcRect.find(uValue);
	if(nit!=m_mArcRect.end())
	{
		tRect=nit->second;
		tRect.translate(nX,nY);
	}
	return tRect;
}

float CTileMapSupport::GetMagnitude(sf::Vector2f v)
{
	return (float)sqrt(v.x * v.x + v.y * v.y);
}

float CTileMapSupport::Dot(sf::Vector2f v0,sf::Vector2f v1)
{
	return v0.x * v1.x + v0.y * v1.y;
}


sf::Vector2f CTileMapSupport::Normalized(sf::Vector2f v)
{
	return v / GetMagnitude(v);
}

void CTileMapSupport::getPointSegment(std::vector<QPointF> &tVa,const QVector2D &p0, const QVector2D &p1, const QVector2D &p2, const QVector2D &p3 ,float fThickness ,bool bLast)
{
	// skip if zero length
	if(p1 == p2) return;
	
	// 1) define the line between the two points
	QVector2D line = (p2 - p1).normalized();

	// 2) find the normal vector of this line
	QVector2D normal = QVector2D(-line.y(), line.x()).normalized();
	// 3) find the tangent vector at both the end points:
	//		-if there are no segments before or after this one, use the line itself
	//		-otherwise, add the two normalized lines and average them by normalizing again
	QVector2D tangent1 = (p0 == p1) ? line : ((p1 - p0).normalized() + line).normalized();
	QVector2D tangent2 = (p2 == p3) ? line : ((p3 - p2).normalized() + line).normalized();

	
	// 4) find the miter line, which is the normal of the tangent
	QVector2D miter1 = QVector2D(-tangent1.y(), tangent1.x());
	QVector2D miter2 = QVector2D(-tangent2.y(), tangent2.x());
	// find length of miter by projecting the miter onto the normal,
	// take the length of the projection, invert it and multiply it by the thickness:
	//		length = thickness * ( 1 / |normal|.|miter| )
	float length1 = fThickness / QVector2D::dotProduct(normal,miter1);
	float length2 = fThickness / QVector2D::dotProduct(normal, miter2);


	QVector2D tVec[2];
	tVec[0] = (p1 - length1 * miter1);
	tVec[1] = (p1 + length1 * miter1);
	tVa.push_back(QPointF(tVec[0].x(), tVec[0].y()));
	tVa.push_back(QPointF(tVec[1].x(), tVec[1].y()));
	if(bLast)
	{
		tVec[0] = (p2 - length2 * miter2);
		tVec[1] = (p2 + length2 * miter2);
		tVa.push_back(QPointF(tVec[0].x(), tVec[0].y()));
		tVa.push_back(QPointF(tVec[1].x(), tVec[1].y()));
	}
}
std::vector<QPointF> CTileMapSupport::getPolyLineBuffer(std::vector<QVector2D> &vPolyLine,float fThickness)
{
	bool bLast=false;
	std::vector<QPointF> tVa;
	int nPolyLineSize=vPolyLine.size();
	for(int i=0;i<nPolyLineSize;++i) {
		int a = ((i-1) < 0) ? 0 : (i-1);
		int b = i;
		int c = ((i+1) >= vPolyLine.size()) ? vPolyLine.size()-1 : (i+1);
		int d = ((i+2) >= vPolyLine.size()) ? vPolyLine.size()-1 : (i+2);
		
		getPointSegment(tVa, vPolyLine[a], vPolyLine[b], vPolyLine[c], vPolyLine[d] ,fThickness,((nPolyLineSize-2)==i)?true:false);
	}
	return tVa;
}


void CTileMapSupport::copyBitmapBuffer(int nDstWidth,int nDstHeight,int nPosX,int nPosY,int nSocWidth,int nSocHeight,unsigned char *pDes,unsigned char *pSoc,int nPixelBytes)
{
	unsigned char	*p1=(unsigned char*)pDes;
	unsigned short	*p2=(unsigned short *)pDes;
	unsigned int	*p4=(unsigned int *)pDes;

	unsigned char	*p1s=(unsigned char*)pSoc;
	unsigned short	*p2s=(unsigned short *)pSoc;
	unsigned int	*p4s=(unsigned int *)pSoc;

	switch(nPixelBytes)
	{
	case 1:
		for(int i=nPosY;i<(nSocHeight+nPosY);i++)
		{
			unsigned char *pTmp=(p1+(nDstWidth*i)+nPosX);
			memcpy(pTmp,p1s,nSocWidth);
			p1s+=nSocWidth;
		}
		break;
	case 2:
		for(int i=nPosY;i<(nSocHeight+nPosY);i++)
		{
			unsigned short *pTmp=(p2+(nDstWidth*i)+nPosX);
			memcpy(pTmp,p2s,(nSocWidth*2));
			p2s+=nSocWidth;
		}
		break;
	case 4:
		for(int i=nPosY;i<(nSocHeight+nPosY);i++)
		{
			unsigned int *pTmp=(p4+(nDstWidth*i)+nPosX);
			memcpy(pTmp,p4s,(nSocWidth*4));
			p4s+=nSocWidth;
		}
		break;
	}
}

void CTileMapSupport::setOriginPoint(sf::Sprite &tSprite,int nCenterPos)
{
	sf::FloatRect boundRect=tSprite.getLocalBounds();

	switch(nCenterPos)
	{
	case 1:
		tSprite.setOrigin(0.f,0.f);
		break;
	case 2:
		tSprite.setOrigin(boundRect.width/2.f,0);
		break;
	case 3:
		tSprite.setOrigin(boundRect.width,0);
		break;
	case 4:
		tSprite.setOrigin(0.f,boundRect.height/2.f);
		break;
	case 5:
		tSprite.setOrigin(boundRect.width/2.f,boundRect.height/2.f);
		break;
	case 6:
		tSprite.setOrigin(boundRect.width,boundRect.height/2.f);
		break;
	case 7:
		tSprite.setOrigin(0.f,boundRect.height);
		break;
	case 8:
		tSprite.setOrigin(boundRect.width/2.f,boundRect.height);
		break;
	case 9:
		tSprite.setOrigin(boundRect.width,boundRect.height);
		break;
	}
}



std::shared_ptr<unsigned char> CTileMapSupport::GenerateTileBitmap(int nTileSize,int nThickness,int *pWidth,int *pHeight)
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


	std::shared_ptr<unsigned char> pByte=std::shared_ptr<unsigned char>((unsigned char*)malloc(((UINT)rctClip.Width*(UINT)rctClip.Height*4)),free);


	UINT *pDst32=(UINT*)pByte.get();
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
	(*pWidth)=rctClip.Width;
	(*pHeight)=rctClip.Height;
	pBitmap->UnlockBits(bitmapData);
	delete bitmapData;
	delete pBitmap;
	return pByte;
}




std::shared_ptr<unsigned char> CTileMapSupport::GenerateStationSpot(int nWidth)
{
	using namespace Gdiplus;
	Bitmap *pBitmap = new Bitmap(nWidth , nWidth, PixelFormat32bppARGB);
	Graphics G(pBitmap);
	G.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
	G.FillEllipse(&SolidBrush(Color(255, 255, 255, 255)), Rect(1, 1, nWidth - 3, nWidth - 3));
	Rect rctClip = Rect(0, 0, pBitmap->GetWidth(), pBitmap->GetHeight());
	UINT uBuffer;
	BitmapData* bitmapData = new BitmapData;
	pBitmap->LockBits(&rctClip, ImageLockModeRead, PixelFormat32bppARGB, bitmapData);
	std::shared_ptr<unsigned char> pByte = std::shared_ptr<unsigned char>((unsigned char*)malloc(((UINT)rctClip.Width*(UINT)rctClip.Height * 4)), free);
	UINT *pDst32 = (UINT*)pByte.get();
	UINT *pSrc32 = (UINT*)bitmapData->Scan0;
	for (int i = rctClip.GetTop(); i<rctClip.GetBottom(); i++)
	{
		UINT *pSrcTmp32 = pSrc32 + ((i - rctClip.GetTop())*(bitmapData->Stride / 4));
		UINT *pDstTmp32 = pDst32 + (i*pBitmap->GetWidth()) + (UINT)rctClip.GetLeft();
		UINT *pSrcTmp32Pixel = pSrcTmp32;
		UINT *pDstTmp32Pixel = pDstTmp32;
		int nRepeatCount = rctClip.GetRight() - rctClip.GetLeft();
		for (int j = 0; j<nRepeatCount; j++)
		{
			UINT uPixelSrc = (*pSrcTmp32Pixel);
			UINT uPixelDst = (*pDstTmp32Pixel) = (((uPixelSrc & 0x000000FF) << 24) | 0x00FFFFFF);
			pSrcTmp32Pixel++;
			pDstTmp32Pixel++;
		}
		memcpy(pDstTmp32, pSrcTmp32, rctClip.Width * sizeof(DWORD));
	}
	pBitmap->UnlockBits(bitmapData);
	delete bitmapData;
	delete pBitmap;
	return pByte;
}


std::shared_ptr<unsigned char> CTileMapSupport::GetBitmapBuffer(wchar_t *pszFile,int nWidthLimit,int nHeightLimit,int *pWidth,int *pHeight)
{
	//using namespace Gdiplus;
	//Bitmap *pBitmap=new Bitmap(pszFile);
	//Rect rctClip=Rect(0,0,pBitmap->GetWidth(),pBitmap->GetHeight());
	//BitmapData* bitmapData = new BitmapData;
	//pBitmap->LockBits(&rctClip,ImageLockModeRead,PixelFormat32bppARGB,bitmapData);
	//std::shared_ptr<unsigned char> pByte=std::shared_ptr<unsigned char>((unsigned char*)malloc(((UINT)rctClip.Width*(UINT)rctClip.Height*4)),free);
	//UINT *pDst32=(UINT*)pByte.get();
	//UINT *pSrc32=(UINT*)bitmapData->Scan0;	
	//for(int i=rctClip.GetTop();i<rctClip.GetBottom();i++)
	//{
	//	UINT *pSrcTmp32=pSrc32+((i-rctClip.GetTop())*(bitmapData->Stride/4));
	//	UINT *pDstTmp32=pDst32+(i*pBitmap->GetWidth())+(UINT)rctClip.GetLeft();
	//	UINT *pSrcTmp32Pixel=pSrcTmp32;
	//	UINT *pDstTmp32Pixel=pDstTmp32;
	//	int nRepeatCount=rctClip.GetRight()-rctClip.GetLeft();
	//	for(int j=0;j<nRepeatCount;j++)
	//	{
	//		UINT uPixelSrc=(*pSrcTmp32Pixel);
	//		if(uPixelSrc)
	//		{
	//			int nValue=0;
	//		}
	//		UINT uPixelDst=(*pDstTmp32Pixel)=((uPixelSrc&0xFF000000)|((uPixelSrc>>16)&0x000000FF)|((uPixelSrc<<16)&0x00FF0000)|((uPixelSrc)&0x0000FF00));
	//		pSrcTmp32Pixel++;
	//		pDstTmp32Pixel++;
	//	}
	//}
	//(*pWidth)=rctClip.Width;
	//(*pHeight)=rctClip.Height;
	//pBitmap->UnlockBits(bitmapData);
	//delete bitmapData;
	//delete pBitmap;

	//return pByte;

	using namespace Gdiplus;
	Bitmap *pBitmap=new Bitmap(pszFile);
	Rect rctClip=Rect(0,0,pBitmap->GetWidth(),pBitmap->GetHeight());
	BitmapData* bitmapData = new BitmapData;
	pBitmap->LockBits(&rctClip,ImageLockModeRead,PixelFormat32bppARGB,bitmapData);
	std::shared_ptr<unsigned char> pByte=std::shared_ptr<unsigned char>((unsigned char*)malloc(((UINT)rctClip.Width*(UINT)rctClip.Height*4)),free);
	UINT *pDst32=(UINT*)pByte.get();
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
			//if(uPixelSrc)
			//{
			//	int nValue=0;
			//}
			(*pDstTmp32Pixel)=((uPixelSrc&0xFF000000)|((uPixelSrc>>16)&0x000000FF)|((uPixelSrc<<16)&0x00FF0000)|((uPixelSrc)&0x0000FF00));
			pSrcTmp32Pixel++;
			pDstTmp32Pixel++;
		}
	}
	(*pWidth)=rctClip.Width;
	(*pHeight)=rctClip.Height;
	pBitmap->UnlockBits(bitmapData);
	delete bitmapData;
	delete pBitmap;

	return pByte;
}


sf::IntRect CTileMapSupport::UnitedRect(sf::IntRect &tRect1,sf::IntRect &tRect2)
{
	int l1 = tRect1.left;
    int r1 = tRect1.left;
    if (tRect1.left+tRect1.width - tRect1.left + 1 < 0)
        l1 = tRect1.left+tRect1.width;
    else
        r1 = tRect1.left+tRect1.width;

    int l2 = tRect2.left;
    int r2 = tRect2.left;
    if (tRect2.left+tRect2.width - tRect2.left + 1 < 0)
        l2 = tRect2.left+tRect2.width;
    else
        r2 = tRect2.left+tRect2.width;

    int t1 = tRect1.top;
    int b1 = tRect1.top;
    if (tRect1.top+tRect1.height - tRect1.top + 1 < 0)
        t1 = tRect1.top+tRect1.height;
    else
        b1 = tRect1.top+tRect1.height; 

    int t2 = tRect2.top;
    int b2 = tRect2.top;
    if (tRect2.top+tRect2.height - tRect2.top + 1 < 0)
        t2 = tRect2.top+tRect2.height;
    else
        b2 = tRect2.top+tRect2.height;

	sf::IntRect tTmpRect;
	tTmpRect.left=(std::min)(l1,l2);
	tTmpRect.width=(std::max)(r1,r2)-tTmpRect.left;
	tTmpRect.top=(std::min)(t1, t2);
	tTmpRect.height=(std::max)(b1,b2)-tTmpRect.top;

    return tTmpRect;
}