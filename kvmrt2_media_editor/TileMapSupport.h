#pragma once
#include <QtGui>
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>

class CTileMapSupport
{
public:
	CTileMapSupport(void);
	~CTileMapSupport(void);

	
	static CTileMapSupport *GetInstance();

	std::map<unsigned __int64,QPainterPath> m_mTilePath;
	std::map<unsigned __int64,QPolygonF> m_mPolygon;
	std::map<unsigned __int64,QRect> m_mArcRect;
	
	int GenerateTilePath(int nUnitSize,int nStrokeSize);

	void GetAngles(int nTile,int *pStart,int *pEnd);
	QRect GetArcRect(int nUnitSize,int nStrokeSize,int nTile,int nX,int nY);
	QPainterPath GetPath(int nUnitSize,int nStrokeSize,int nTile,int nX,int nY);
	QPolygonF GetPolygon(int nUnitSize,int nStrokeSize,int nTile,int nX,int nY);
	void setOriginPoint(sf::Sprite &tSprite,int nCenterPos);
	std::vector<QPointF> getPolyLineBuffer(std::vector<QVector2D> &vPolyLine, float fThickness);
	void copyBitmapBuffer(int nDstWidth,int nDstHeight,int nPosX,int nPosY,int nSocWidth,int nSocHeight,unsigned char *pDes,unsigned char *pSoc,int nPixelBytes);

	std::shared_ptr<unsigned char> GenerateTileBitmap(int nTileSize,int nThickness,int *pWidth,int *pHeight);
	std::shared_ptr<unsigned char> GetBitmapBuffer(wchar_t *pszBuffer,int nWidthLimit,int nHeightLimit,int *pWidth,int *pHeight);
	std::shared_ptr<unsigned char> GenerateStationSpot(int nWidth);

	sf::IntRect UnitedRect(sf::IntRect &tRect1,sf::IntRect &tRect2);

private:
	float GetMagnitude(sf::Vector2f v);
	float Dot(sf::Vector2f v0,sf::Vector2f v1);
	sf::Vector2f GetNormal(sf::Vector2f v);
	sf::Vector2f Normalized(sf::Vector2f v);
	void getPointSegment(std::vector<QPointF> &tVa,const QVector2D &p0, const QVector2D &p1, const QVector2D &p2, const QVector2D &p3 ,float fThickness ,bool bLast);
	
};

