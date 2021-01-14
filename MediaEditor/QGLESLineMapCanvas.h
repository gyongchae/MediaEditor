#ifndef QOPENGLLINEMAPCANVAS_H
#define QOPENGLLINEMAPCANVAS_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QRect>
#include <Qmenu>
#include "defineTileMap.h"
#include <vector>
#include <map>
#include <memory>

class MaxRectsPixelBuffer;
class CTexPool;
class DisplayItem;
class DisplayProp;
class QAction;
class QMenu;
class LineMapLink;
class LineMapArrowTexture;
class LineMapDisplayItem;

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

enum
{
	EDIT_TILE_MAP = 1,
	EDIT_NODE,
	EDIT_ARROW,
	EDIT_DISPLAYITEM,
};

enum
{
	STATION_LEFT=1,
	STATION_FOCUSED,
	STATION_PASSED,
	STATION_SKIPPED,
	STATION_UNUSED
};

// new enum
enum
{
	STN_NODE_PASSED = 0,
	STN_NODE_TARGET,
	STN_NODE_REMAIN,
};

enum
{
	DISP_DISPLAY_ITEM = 0,
	DISP_IMAGE_LIST= 1,
};


class QGLESLineMapCanvas : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	explicit QGLESLineMapCanvas(QWidget *parent = nullptr);
	explicit QGLESLineMapCanvas(int nRow, QWidget *parent = 0);
	~QGLESLineMapCanvas();
	
	void initxxx(int nRow);
	
	void initBaseData(int nMapIndex);
	void setBoundRectangle(DisplayItem *pItem);
	void initDisplayItem();
	void initActions();
	bool GetEncCLSID(wchar_t *mime, CLSID *pClsid);
	void saveTextureImage(GLuint nTexture, int nWidth, int nHeight, int nBytePerPixel);
	bool GetTextureInfo(std::vector<GLfloat> &vVertex, std::vector<GLushort> &vIndices, GLfloat fTexPosX, GLfloat fTexPosY, GLfloat fTexWidth, GLfloat fTexHeight, GLfloat fTexWholeWidth, GLfloat fTexWholeHeight, GLfloat fTextureOffset, GLsizei *pCount, GLsizei *pOffset, GLuint uVBOId, GLuint uIBOId);

	void setArrowTexture(LineMapArrowTexture *pLMAT, std::vector<GLfloat> &vVertex, std::vector<GLushort> &vIndices, std::vector<GLfloat> &vVertexArrow, int nWholeWidth, int nWholeHeight, int nBytesPerPixel);

signals:
	void positionChanged(const QString &/*str*/);
	void updateRouteMapLine();

private:
	std::vector<std::shared_ptr<MaxRectsPixelBuffer>> vBinPacked;
	std::vector<std::shared_ptr<MaxRectsPixelBuffer>> vBinPackedDest;
	std::map<GLuint, std::shared_ptr<CTexPool>> m_mImageList;
	std::map<GLuint, std::shared_ptr<CTexPool>> m_mLineMapLink;
	std::map<GLuint, std::shared_ptr<CTexPool>> m_mArrow;
	std::shared_ptr<CTexPool> m_tStationSpot;
	QAction *m_pActDelItem;
	QAction *m_pActEditProp;
	QAction *m_pActDelPropertiesAtCurrentTime;
	QMenu *m_pMenu;

protected:
	void mouseMoveEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
	void timerEvent(QTimerEvent *e) Q_DECL_OVERRIDE;
	void contextMenuEvent(QContextMenuEvent * e) Q_DECL_OVERRIDE;
	void keyPressEvent(QKeyEvent * event) Q_DECL_OVERRIDE;
	void keyReleaseEvent(QKeyEvent * event) Q_DECL_OVERRIDE;
	void dragMoveEvent(QDragMoveEvent * event);
	void dragEnterEvent(QDragEnterEvent * event);
	void dropEvent(QDropEvent * e);

	void initializeGL() Q_DECL_OVERRIDE;
	void resizeGL(int w, int h) Q_DECL_OVERRIDE;
	void paintGL() Q_DECL_OVERRIDE;

	void initShaders();
	void initShadersForLine();
	void initshadersForArrow();
	void paintStationRelated();
	void paintDisplayItems();
	void paintDisplayItemsPoolRect();

public:		//a part that related to edit
	void prepareArrow(int nWidth, int nHeight);
	void initTileMaps();
	void afterSetPos(LineMapLink *pLink);
	unsigned int searchNode(unsigned short wX, unsigned short wY, int *pInt);
	void insertBasicNode(unsigned int nKey);
	void deleteBasicNode(unsigned int nKey);
	bool setNodeActions(int nSelectedNode, int nPosX, int nPosY);
	bool getMinCoordFromBuffer(int nXPosRef, int nYPosRef, int *pXPos, int *pYPos);
	unsigned char m_uConfirmedBuffer[1920][1080];
	unsigned char m_uNodeBuffer[1920][1080];
	unsigned int m_uArrowNode[2];
	int m_nLatestPosX, m_nLatestPosY;
	std::vector<unsigned int> m_vSelNodes;	//Selected Nodes
	std::map<unsigned int, int> m_mNodes;	//Basic Nodes
	std::map<unsigned int, std::map<unsigned int, PATHINFO>> m_mPath;
	//Arrow Related
	std::map<unsigned int, std::map<unsigned int, CONFIRMEDPATH>> m_mConfirmedPath;
	std::map<unsigned int, int> m_mConfirmedNodes;

	void addNode(int nPosX, int nPosY);
	void deleteNode(int nSelectedIndex);
	void editNode(int nSelectedIndex);
	void editSpot(int nSelectedIndex);
	void resetPos(LineMapLink *pLink);
	int m_nSelectedNode;
	int m_nSelectedLink = -1;
	bool m_bNodeAlignPressed;
	bool m_bLinkCtrlPressed = false;
	bool m_bPressed;	//is L button pressed?

	void realignNodes();
	void alignNodes();
	bool CalcShortestPath(unsigned int nBegin, unsigned int nEnd, std::vector<unsigned int> &vString);
	bool CalcShortestPathForConfirmed(unsigned int nBegin, unsigned int nEnd, std::vector<unsigned int> &vString);
	void generateArrowFrom(unsigned short wStX, unsigned short wStY, unsigned short wEnX, unsigned short wEnY, int nBeginTrim, int nEndTrim,float fPenWidth=9.0);

public:
	QMenu * m_pLinkMenu;
	void initLinkMenu();
	void addLink(int nTile, int nX, int nY);
	void addTileBySelection(TileType tAddTile, int nPosX, int nPosY);
	QMenu *m_pNodeMenu;
	void initNodeMenu();
	QMenu *m_pArrowMenu;
	void initArrowMenu();
	int m_nSelectedArrow;
	void deleteArrow(int nSelectedIndex);
	void setBoundRectangle(LineMapDisplayItem *pLMDI);
	bool isPtInItemBound(LineMapDisplayItem *pItem, int nX, int nY, GLfloat *pX, GLfloat *pY);
	GLfloat m_fOffsetX,m_fOffsetY;

	// display item menu
	QMenu *m_pDispItemMenu = nullptr;
	int m_nSelectedDispItem = -1;
	void initDispItemMenu();
	void editDisplayItem(int idx);
	void deleteDisplayItem(int nIdx);

private:
	//VBO Backup
	std::vector<GLfloat> vVertices;
	std::vector<GLfloat> vVerticesArrow;
	std::vector<GLushort> vIndices;

	int m_nRow;
	int m_nWidth;
	int m_nHeight;
	int m_nCellSize;
	int m_nLineWidth;
	GLuint m_uVBOsID[3];

	GLint m_aScrPos;
	GLint m_aScrTexCoord;
	GLint m_uScrMatrix;
	GLint m_uScrColor;
	GLint m_uScrFirstTex;
	QOpenGLShaderProgram scrProgram;


	GLint m_aLinePos;
	GLint m_uLineMatrix;
	GLint m_uLineColor;
	QOpenGLShaderProgram lineProgram;


	GLint m_aArrowPos;
	GLint m_aArrowTexCoord;
	GLint m_uArrowMatrix;
	GLint m_uArrowColor;
	GLint m_uArrowFirstTex;
	GLint m_uArrowSecondTex;
	GLint m_uArrowBlendingRatio;
	QOpenGLShaderProgram arrowProgram;

	int m_nSelIdx;
	bool m_bSelected;
	int m_nCurTime;
	bool m_bMoving;
	int m_nSelectedItem;
	int m_eEditMode;
	int m_eCurrentStnState;
	//void sortToZOrder();

protected slots:
	void setCurrentStationState(int nAction);
	void setCurrentEditMode(int nMode);
	void selectAction(QAction *action);
	void setCurrentTime(int index);
	void deleteItem();
	void editProperties();

	public slots:
	void getNodeIconRadioChangedIdx(const int idx);
	void getChangedStnAndBound(const int stnOrder, const int bound);


private:
	int m_nCurrNodeIconIdx = STN_NODE_PASSED;

	QList<LineMapLink*> m_unusedLines;
};

#endif