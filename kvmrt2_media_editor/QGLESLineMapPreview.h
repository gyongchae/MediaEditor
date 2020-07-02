#ifndef QLINEMAPPREVIEW_H
#define QLINEMAPPREVIEW_H


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

class LineMapPool;
class LineMapArrowTexture;
class StationImagePool;
class BitmapImagePool;
class CValueMonitor;
class CSQLData;


enum
{
	DISP_DISPLAY_ITEM = 0,
	DISP_IMAGE_LIST = 1,
};

class QGLESLineMapPreview : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT
public:
	QGLESLineMapPreview(QWidget *parent = 0);
	~QGLESLineMapPreview();
	void initVBO();

	void mapStopPtnIdx(int *pStopPtnIdx);
	void mapDistIdx(int *pDistIdx);
	void mapProgress(int *pProgress);
	void mapLineMapIdx(int *pLineMapIdx);
	void mapRoutesIdx(int *pRoutesIdx);

	//void initBaseData();

	std::vector<std::shared_ptr<MaxRectsPixelBuffer>> vBinPacked;
	std::vector<std::shared_ptr<MaxRectsPixelBuffer>> vBinPackedDest;

	std::map<GLuint, std::map<GLuint, std::shared_ptr<CTexPool>>> m_mLineMapLink;
	std::map<GLuint, std::shared_ptr<CTexPool>> *m_pCurLineMapLink;
	std::map<GLuint, std::shared_ptr<CTexPool>> m_mArrow;
	std::map<GLuint, std::shared_ptr<CTexPool>> m_mStation;
	std::map<GLuint, std::shared_ptr<CTexPool>> m_mBitmap;
	std::map<GLuint, std::shared_ptr<CTexPool>> m_mImageList;
	void setLineMapLinkTexture(LineMapPool *pLMP, std::vector<GLfloat> &vVertex, std::vector<GLushort> &vIndices, int nWholeWidth, int nWholeHeight, int nBytesPerPixel);
	void setArrowTexture(LineMapArrowTexture *pLMAT, std::vector<GLfloat> &vVertex, std::vector<GLushort> &vIndices, std::vector<GLfloat> &vVertexArrow, int nWholeWidth, int nWholeHeight, int nBytesPerPixel);
	void setStationImageTexture(StationImagePool *pSIM, std::vector<GLfloat> &vVertex, std::vector<GLushort> &vIndices, int nWholeWidth, int nWholeHeight, int nBytesPerPixel);
	void setBitmapImageTexture(BitmapImagePool *pBIM, std::vector<GLfloat> &vVertex, std::vector<GLushort> &vIndices, int nWholeWidth, int nWholeHeight, int nBytesPerPixel);
private:
	GLuint m_aPosScrLoc;
	GLuint m_aTexCoordScrLoc;
	GLuint m_uMatrixScrLoc;
	GLuint m_uColorScrLoc;
	GLint m_nFirstScrTex;
	QOpenGLShaderProgram program;


	GLuint m_uPosLineLoc;
	GLuint m_uMatrixLineLoc;
	GLuint m_uColorLineLoc;
	QOpenGLShaderProgram lineProgram;



	GLint m_aArrowPos;
	GLint m_aArrowTexCoord;
	GLint m_uArrowMatrix;
	GLint m_uArrowColor;
	GLint m_uArrowFirstTex;
	GLint m_uArrowSecondTex;
	GLint m_uArrowBlendingRatio;
	QOpenGLShaderProgram arrowProgram;


	int m_nHeight;
	int m_nWidth;


protected:
	/*void timerEvent(QTimerEvent *e) Q_DECL_OVERRIDE;*/
	void initializeGL() Q_DECL_OVERRIDE;
	void resizeGL(int w, int h) Q_DECL_OVERRIDE;
	void paintGL() Q_DECL_OVERRIDE;

	void initShaders();
	void initShadersForLine();
	void initshadersForArrow();

	void initBaseData();
	void initImageListBoundRect();
	void prepareArrow(std::vector<std::shared_ptr<CSQLData>> *m_pLineMapArrowTextures, int nWidth, int nHeight,float fR, float fG, float fB);
	void setArrowProgress(std::vector<std::shared_ptr<CSQLData>> *m_pLineMapArrowTextures, int nWidth, int nHeight,int nPerMil, float fR, float fG, float fB, float fPR, float fPG, float fPB);

	GLuint m_uVBOsID[3];
	GLfloat m_fColorState[5][4];
private:
	void PushTextureInfo(std::vector<std::shared_ptr<MaxRectsPixelBuffer>> &vBinPacked, std::vector<GLfloat> &vVertex, std::vector<GLushort> &vIndices,
		std::map<GLuint, std::shared_ptr<CTexPool>> &mTexPool, unsigned char *pSoc, int nWidth, int nHeight, int nWholeHeight, int nWholeWidth, int nBytesPerPixel, int nIndex);
	void PushDoubleTextureInfo(std::vector<std::shared_ptr<MaxRectsPixelBuffer>> &vBinPacked, std::vector<GLfloat> &vVertex, std::vector<GLushort> &vIndices, std::vector<GLfloat> &v2ndVertex,
		std::map<GLuint, std::shared_ptr<CTexPool>> &mTexPool, unsigned char *pSoc, int nWidth, int nHeight, int nWholeHeight, int nWholeWidth, int nBytesPerPixel, unsigned char *pVertexBuf, int nVtxSize, int nIndex);
	void saveTextureImage(GLuint nTexture, int nWidth, int nHeight, int nBytePerPixel);
	bool GetEncCLSID(wchar_t *mime, CLSID *pClsid);
	std::vector<GLfloat> vVertices;
	std::vector<GLfloat> vVerticesArrow;
	std::vector<GLushort> vIndices;


	std::shared_ptr<CValueMonitor> m_pMonStopPtnIdx;
	std::shared_ptr<CValueMonitor> m_pMonDistIdx;
	std::shared_ptr<CValueMonitor> m_pMonProgIdx;
	std::shared_ptr<CValueMonitor> m_pMonLineMapIdx;
	std::shared_ptr<CValueMonitor> m_pMonRoutesIdx;

	void initDisplayItem();
	void initMetaDisplayItem();
	void initStationRelated();
	void setBoundRectangle(DisplayItem *pItem);
	void setBoundRectangle(DisplayMetaItem *pItem);
	void setMetaItemOrientation(DisplayMetaItem *pItem);
	void paintStationRelated(std::vector<std::shared_ptr<CSQLData>> &tVECStn, int nState,int nWidth, int nHeight);
	void paintDisplayItems(std::vector<std::shared_ptr<CSQLData>> *pvLMDP,int nWidth,int nHeight);
private:
	LineMapPool * m_pCurLineMapPool;
	std::vector<std::shared_ptr<CSQLData>> *m_pLineMapLinkProps;
	std::vector<std::shared_ptr<CSQLData>> *m_pLineMapNode;
	std::vector<std::shared_ptr<CSQLData>> *m_pLineMapArrowTextures;
	std::vector<std::shared_ptr<CSQLData>> *m_pLineMapDisplayItem;
	std::vector<std::shared_ptr<CSQLData>> *m_pRoutes;

	std::vector<std::shared_ptr<CSQLData>> m_vArrowsInUse[3];
	std::vector<std::shared_ptr<CSQLData>> m_vNodesInUse[3];
	void fillArrowsAndNodes(int nCurRouteIdx, int nFocusedStnIdx);

	int m_nCurTime;
protected slots:
	/*void setCurrentStationState(int nAction);
	void setCurrentEditMode(int nMode);
	void selectAction(QAction *action);*/
	void setCurrentTime(int index);

};


#endif
