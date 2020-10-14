#ifndef QOPENGLCANVAS_H
#define QOPENGLCANVAS_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <vector>
#include <map>
#include <memory>

class MaxRectsPixelBuffer;
class CTexPool;
class DisplayMetaItem;
class DisplayMetaItemProp;
class DisplayItem;
class DisplayProp;
class QAction;
class QMenu;

// 해당 해상도를 넘어가는 이미지는 화면 표출이 안 된다.
// MAL PID에서 1000넘으면 표출이 안됨
const int WIDTH_LIMIT = 4092;
const int HEIGHT_LIMIT = 4092;

class QGLESPIDCanvas : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	explicit QGLESPIDCanvas(QWidget *parent = 0);
	virtual ~QGLESPIDCanvas();

public:
	void initBaseData();
	void reorderAllTimeLine();

	void setBoundRectangle(DisplayItem *pItem);
	void setBoundRectangle(DisplayMetaItem *pItem);

	bool isPtInItemBound(DisplayItem *pItem, int nX, int nY,GLfloat *pX=0,GLfloat *pY=0);
	bool isPtInMetaItemBound(DisplayMetaItem *pItem, int nX, int nY, GLfloat *pX = 0, GLfloat *pY = 0);

	void setPropertiesFromItem(DisplayItem* pItem, DisplayProp *pProp, GLfloat nX, GLfloat nY);
	void setPropertiesFromMetaItem(DisplayMetaItem* pItem, DisplayMetaItemProp *pProp, GLfloat nX, GLfloat nY);

	void setMetaItemOrientation(DisplayMetaItem *pItem);
	void initMetaDisplayItem();
	void initDisplayItem();

	void initActions();
	void syncBounds(DisplayItem *pItem, DisplayProp *pProp);
	void syncMetaItemBounds(DisplayMetaItem *pItem, DisplayMetaItemProp *pProp);

	void setSelectedItemVectors(void *pItem, int nType);
	QVector<int> vKeyFrames;

	// new func for displaying meta item init image
	int getInitMetaItemIndex(const int & tagIdx);

//////////////////////////////// QOpenGLWidget override func ///////////////////////////////
protected:
	void initializeGL() Q_DECL_OVERRIDE;
	void resizeGL(int w, int h) Q_DECL_OVERRIDE;
	void paintGL() Q_DECL_OVERRIDE;
//////////////////////////////// QOpenGLWidget override func ///////////////////////////////

	void mouseMoveEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
	void dragMoveEvent(QDragMoveEvent * event) Q_DECL_OVERRIDE;
	void dragEnterEvent(QDragEnterEvent * event) Q_DECL_OVERRIDE;
	void contextMenuEvent(QContextMenuEvent * event) Q_DECL_OVERRIDE;
	void dropEvent(QDropEvent * e) Q_DECL_OVERRIDE;

	void initShaders();
	void initShadersForLine();

	GLfloat m_fOffsetX;
	GLfloat m_fOffsetY;

private:
	std::vector<std::shared_ptr<MaxRectsPixelBuffer>> vBinPacked;
	std::vector<std::shared_ptr<MaxRectsPixelBuffer>> vBinPackedDest;
	std::map<GLuint, std::shared_ptr<CTexPool>> m_mImageList;

	QAction *m_pAddMetaItem;
	QAction *m_pDeleteMetaItem;
	QAction *m_pEditMetaItem;
	QAction *m_pRemoveMetaProp;

	QAction *m_pActDelItem;
	QAction *m_pActEditProp;
	QAction *m_pActDelProp;

	QMenu *m_pMenu;
	QMenu *m_pMetaItemMenu;

private:
	int m_nWidth;
	int m_nHeight;
	GLuint m_uVBOsID[2];
	GLuint m_uPosScrLoc;
	GLuint m_uTexCoordScrLoc;
	GLuint m_uMatrixLoc;
	GLuint m_uColorLoc;
	GLint m_nFirstTex;
	QOpenGLShaderProgram program;

	GLuint m_uPosLineLoc;
	GLuint m_uMatrixLineLoc;
	GLuint m_uColorLineLoc;
	QOpenGLShaderProgram lineProgram;

	int m_nSelMetaIdx;
	int m_nSelIdx;

	int m_nLatestSelected;
	int m_nLatestSelectedType;

	bool m_bMousePressed;
	bool m_bMouseMovedWhilePressed;
	bool m_bSelected;
	int m_nCurTime;
	bool m_bMoving;

	int m_nMetaItemPosX;
	int m_nMetaItemPosY;
	
	int isPropExist();
	int isMetaPropExist();
	void sortToZOrder();
	void getMetaItemProperties(DisplayMetaItem *pInserted, int *pPropertiesRow,int nX,int nY);

signals:
	void positionChanged(const QString &/*str*/);
	void selectionChanged();

private slots:
	void selectMetaItemAction(QAction *action);
	void setCurrentTime(int index);

	void deleteItem();
	void addMetaItem();

	void editProperties();
	void editMetaItemProperties();

	void removeMetaPropAtCurTime();
	void removePropAtCurTime();
};

#endif
