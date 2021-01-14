#pragma once
#include "qsfmlcanvas.h"
#include <QMouseEvent>
#include <QModelIndex>
#include <memory>
#include <QMutex>
#include "defineTileMap.h"

class CSQLData;
class LineMapLink;
class LineMapNode;
class CTreeInfo;
class CSQLTreeModel;
class QMenu;
class QWidget;



typedef struct _PATHINFO
{
	LineMapLink *pLink;
	std::vector<QPoint> *vPoint;
	std::vector<qreal> *vAngle;
}PATHINFO;


typedef struct _CONFIRMEDPATH
{
	QRect tRect;
	int nItemType;
	std::vector<QPoint> vPoint;
	std::vector<qreal> vAngle;
}CONFIRMEDPATH;


class QLineMap :
	public QSFMLCanvas
{
	 Q_OBJECT

public:
	QLineMap(QWidget* parent);
	QLineMap(QWidget* Parent,int nBlockSize,int nThickness,int nWholeWidth,int nWholeHeight,unsigned char *pBufTileMap,const QPoint& Position, const QSize& Size);
	~QLineMap(void);
private :
	void OnInit();
    void OnUpdate();
	void OnResize(int x,int y);
	void mouseMoveEvent ( QMouseEvent * event );
	void mousePressEvent ( QMouseEvent * event );
	void mouseReleaseEvent ( QMouseEvent * event );
	void keyPressEvent (QKeyEvent * event);
	void keyReleaseEvent (QKeyEvent * event);
	void focusOutEvent ( QFocusEvent * event );
	void focusInEvent ( QFocusEvent * event );
	void mouseDoubleClickEvent( QMouseEvent * event );
public:
	void setCurrentIndex(const QModelIndex &index)
	{
		m_index=index;
	}
	void setModel(CSQLTreeModel *pModel)
	{
		m_pModel=(CSQLTreeModel*)pModel;
	}
	QModelIndex m_tmpIndex;
	QModelIndex m_index;
	CSQLTreeModel *m_pModel;
	int m_nLatestPosX;
	int m_nLatestPosY;
public:
	bool m_bCtrlKeyPressed;
	bool m_bPressed;
public:
	//LineMapLink;
	std::vector<std::shared_ptr<CSQLData>> *m_pvLink;
	std::vector<std::shared_ptr<CSQLData>> m_vLink;
	std::shared_ptr<CTreeInfo> m_pTreeInfoLink;
	void initTileMaps(std::shared_ptr<CTreeInfo> &pTreeInfo);
	void addTileBySelection(TileType tAddTile,int nPosX,int nPosY);

public:
	//Node Information
	std::vector<std::shared_ptr<CSQLData>> *m_pvNode;
	std::vector<std::shared_ptr<CSQLData>> m_vNode;
	std::shared_ptr<CTreeInfo> m_pTreeInfoNode;
	void initNodeInformation(std::shared_ptr<CTreeInfo> &pTreeInfo);

public:
	std::vector<std::shared_ptr<CSQLData>> *m_pvArrow;
	std::vector<std::shared_ptr<CSQLData>> m_vArrow;
	std::shared_ptr<CTreeInfo> m_pTreeInfoArrow;
	void initArrowInformation(std::shared_ptr<CTreeInfo> &pTreeInfo);

public:
	QSize m_tScreenSize;

public:
	void QLineMap::initialize(int nBlockSize,int nThickness,int nWholeWidth,int nWholeHeight,unsigned char *pBufTileMap,const QPoint& position, const QSize& size);
	void setTileMap(int nWholeWidth,int nWholeHeight,int nUnitSize,unsigned char *pByte);
	void updateNodePropertyGUI();
	void clearAllSprite();
	void setTexSprite(int nIndex,int nWidth,int nHeight,int nXPos,int nYPos,void* pVoid);
	void removeIndex(int nIndex);
	void GenerateTileBitmap(int nTileSize,int nThickness);
	void GenerateSpotBitmap(int nSpotSize);
	void setTimeMap(int nWholeWidth,int nWholeHeight,int nUnitSize,unsigned char *pByte);
	void scroll(int dx,int dy)
	{
		nInitPosX+=dx;
		nInitPosY+=dy;
		m_standard.move((float)dx,(float)dy);
		update();
	}
	
	sf::View m_fixed;
	sf::View m_standard;

	sf::Texture m_texTile;
	sf::Sprite m_sprTile[16];
	sf::Texture m_texSpot;
	sf::Sprite m_sprSpot[16];

	sf::IntRect m_rctFocus;


	std::vector<std::shared_ptr<sf::Texture>> m_vTexture;
	std::vector<std::shared_ptr<sf::Sprite>> m_vSprite;

	std::map<unsigned __int64,unsigned int> m_mTileMap;

	std::vector<unsigned int> m_vNodes;
	std::vector<unsigned int> m_vSelNodes;
	std::map<unsigned int,int> m_mNodes;
	std::map<unsigned int,std::map<unsigned int,PATHINFO>> m_mPath;


	std::map<unsigned int,std::map<unsigned int,CONFIRMEDPATH>> m_mConfirmedPath;
	std::map<unsigned int,int> m_mConfirmedNodes;
	//std::map<unsigned __int64,PATHINFO> m_mPath;


	std::vector<unsigned int> m_vNodesTemp;


	



	std::map<int,std::shared_ptr<CSQLData>> m_mBasicNode;
	std::map<int,std::shared_ptr<CSQLData>> m_mNode;


	
	std::vector<std::shared_ptr<CSQLData>> *m_pvBasicNode;
	std::vector<std::shared_ptr<CSQLData>> *m_pvArrowTexture;
	std::vector<std::shared_ptr<CSQLData>> *m_pvArrowVertex;



	std::map<unsigned int,std::map<unsigned int,std::shared_ptr<CSQLData>>> m_mConfirmedArrow;



	unsigned char m_uConfirmedBuffer[1920][1080];
	unsigned char m_uNodeBuffer[1920][1080];


	bool m_bSelected;
	int nIndexed;
	int nInitPosX;
	int nInitPosY;

	int m_nBlockSize;
	int m_nThickness;
	int m_nSelectedNode;
	unsigned int m_uArrowNode[2];
	TileType m_tCurTile;
	int m_tMapMode;

	unsigned int searchNode(unsigned short wX,unsigned short wY,int *pInt);
	void addLink(int nTile,int nX,int nY);

	void afterSetPos(LineMapLink *pLink);
	void resetPos(LineMapLink *pLink);
	void insertBasicNode(unsigned int nKey);
	void deleteBasicNode(unsigned int nKey);
	bool moveNodeTo(int dir,LineMapNode *pNode);
	bool CalcShortestPath(unsigned int nBegin,unsigned int nEnd,std::vector<unsigned int> &vString);

	bool CalcShortestPathForConfirmed(unsigned int nBegin,unsigned int nEnd,std::vector<unsigned int> &vString);

	void alignNodes();
	void realignNodes();

	void generateArrow();
	void generateArrowFrom(unsigned short wStX,unsigned short wStY,unsigned short wEnX,unsigned short wEnY,int nBeginTrim,int nEndTrim);

public:
	bool getMinCoordFromBuffer(int nXPosRef,int nYPosRef,int *pXPos,int *pYPos);
public:
	QMenu *m_pAlignMenu;
	void InitAlignMenu();
public:
	QMenu *m_pLinkMenu;
	void InitLinkMenu();
public:
	QMenu *m_pNodeMenu;
	void InitNodeMenu();
	void addNode(int nPosX,int nPosY);
	void deleteNode(int nSelectedIndex);
	bool setNodeActions(int nSelectedNode,int nPosX,int nPosY);
	void syncData();
public slots:
    void setMode(int nMode);
    void setItemType(TileType type);
	void contextMenu(const QPoint &pos);
	void selectAction(QAction *action);
signals:
	void posChanged(int nIndex,int x,int y);
	void setCurrentModelIndex(const QModelIndex & index);
	void makeItemExpended(const QModelIndex & index, bool expanded);

};