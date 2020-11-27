#ifndef LEDINDICATOR_H
#define LEDINDICATOR_H

#include <QWidget>


#include <windows.h>


#ifdef UNICODE
	#define tstring std::wstring
	#define tstream std::wofstream
#else if
	#define tstring std::string
	#define tstream std::ofstream
#endif

class QImage;
class QByteArray;
class QPaintEngine;

class LEDIndicator : public QWidget
{
	Q_OBJECT

public:
	LEDIndicator(QWidget *parent=NULL);
	LEDIndicator(int nMode,int nLEDType,int nPages,int nUnitWidth,int nUnitHeight,int nRatio,QWidget *parent);
	~LEDIndicator();
protected:
	void paintEvent(QPaintEvent *);
	void resizeEvent(QResizeEvent *);
	void mousePressEvent(QMouseEvent *);
	void mouseMoveEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);
	void mouseDoubleClickEvent(QMouseEvent *);
public:
	void setMode(int nMode);
	void setImage(HBITMAP hBitmap);
	void clearImage();
	BOOL setBinaryData(LPBYTE lpBufImages);
	void setCurrentInputedText();
	HBITMAP CreateBitmapByCreateDIBSection(HDC hdc, int cx, int cy, int bpp,LPVOID *pBuf);
	void setText(LPCWSTR lpStrText,LPCWSTR lpStrFont,int nSize,int nVert,int nHorz,UINT nClrBkGnd,UINT nClrFgGnd,bool bBkTransparent,bool bBold=false);
	//BOOL setBinaryData(int nWidth,int nHeight,int nBits,int nMode,int nPages,LPBYTE lpBufImages);
	//HBITMAP MakeDIBSection(int nWidth,int nHeight,int nBits,int nMode,int nPages,LPVOID *lpBuf);
	//void setText(LPCWSTR lpStrText,LPCWSTR lpStrFont,int nSize,int nVert,int nHorz,UINT nClrBkGnd,UINT nClrFgGnd,int nUnitHeight,int nUnitWidth);
	void setBitmap(int nPages,int nMode,LPVOID lpBuffer);
	void setProperties(int nBits,int nPages,int nWidth,int nHeight,int nMode,int nRatio);
	//BOOL setBitmapImage(QString strPath);
	//BOOL LoadBitmapFromBMPFile( LPCTSTR szFileName1, HBITMAP *phBitmap,HPALETTE *phPalette );
	//QByteArray binaryData();

	void selectAllArea();
	
	int setRatio(int nRatio);
	QPaintEngine *paintEngine(void) const;
public:
	void *m_pBuffer;
private:
	HBITMAP m_hBitmap;
	HBITMAP m_hBitmapTemp;
	void *m_pBufferTemp;
	bool m_bBtnDown;
	bool m_bTransparent;
	int m_nCurMode;
	int m_nBits;
	int m_nMode;
	int m_nPages;
	int m_nRatio;
	int m_nUnitWidth;
	int m_nUnitHeight;
	POINT m_tPtBegin;
	POINT m_tPtEnd;
	RECT m_tSelArea;
	RECT m_tTmpArea;
	
};

#endif // LEDINDICATOR_H
