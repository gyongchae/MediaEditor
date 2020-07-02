#include "LEDIndicator.h"
#include <QLineEdit>
#include <QStylePainter>
#include <QPaintEngine>
#include <QMouseEvent>
#include <QImage>
#include <QWidget>
#include "DataManage.h"
#include <math.h>






void DrawTextNew(HDC dc, LPCWSTR text, int cchText, LPCRECT lprc, UINT format,UINT vAlign)
{
	if(dc==nullptr || lprc==nullptr) return;

	RECT rect = *lprc;
	RECT rectResult = *lprc;
	int marginH=0;
	int marginW=0;
	
	// 글자가 차지하는 사각형 계산
	DrawText(dc, text, cchText, &rect, format | DT_CALCRECT | DT_NOPREFIX);

	// 가로, 세로로 센터
	switch(vAlign)
	{
	case DT_VCENTER:
		marginH = std::max(0, (int)((lprc->bottom-lprc->top) - (rect.bottom-rect.top))/2);
		//marginW=std::max(0, ((lprc->right-lprc->left) - (rect.right-rect.left))/2);
		rectResult.top    += marginH;
		rectResult.bottom -= marginH;
		rectResult.left=rect.left;
		rectResult.right=rect.right;
		//rectResult.left     += marginW;
		//rectResult.right  -= marginW;
		break;
	case DT_TOP:
		marginH = (lprc->bottom-lprc->top) - (rect.bottom-rect.top);
		rectResult.top    = rect.top;
		rectResult.bottom = rect.bottom;
		rectResult.left=rect.left;
		rectResult.right=rect.right;
		break;
	case DT_BOTTOM:
		marginH = (lprc->bottom-lprc->top) - (rect.bottom-rect.top);
		rectResult.top    += marginH;
		rectResult.bottom += marginH;
		rectResult.left=rect.left;
		rectResult.right=rect.right;
		break;
	}

	if((format&0x0000000F)==DT_CENTER)
	{
		marginW=std::max(0, (int)((lprc->right-lprc->left) - (rect.right-rect.left))/2);
		rectResult.left     += marginW;
		rectResult.right  += marginW;
	}
	else if((format&0x0000000F)==DT_LEFT)
	{
		marginW=std::max(0, (int)((lprc->right-lprc->left) - (rect.right-rect.left))/2);
	}
	else if((format&0x0000000F)==DT_RIGHT)
	{
		marginW= ((lprc->right-lprc->left) - (rect.right-rect.left));
		rectResult.left     += marginW;
		rectResult.right  += marginW;

	}

	format|=DT_NOPREFIX;

	// 글자 그리기
	DrawText(dc, text, cchText, &rectResult,format);
}



LEDIndicator::LEDIndicator(QWidget *parent)
: QWidget(parent),m_nBits(1),m_nPages(1),m_nUnitWidth(128),m_nUnitHeight(32),m_nMode(0),m_nRatio(1),m_hBitmap(nullptr)
,m_nCurMode(0),m_bBtnDown(false),m_hBitmapTemp(nullptr),m_bTransparent(false)
{
	setAttribute(Qt::WA_PaintOnScreen,true);
	setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	setFocusPolicy(Qt::StrongFocus);

	memset(&m_tPtBegin,0,sizeof(POINT));
	memset(&m_tPtEnd,0,sizeof(POINT));


	setGeometry(QRect(0, 0, m_nUnitWidth, m_nUnitHeight));
	setMinimumSize(QSize(m_nUnitWidth, m_nUnitHeight));
	setMaximumSize(QSize(m_nUnitWidth, m_nUnitHeight));

}


void LEDIndicator::setProperties(int nBits,int nPages,int nWidth,int nHeight,int nMode,int nRatio)
{
	m_nBits=nBits;
	m_nPages=nPages;
	m_nUnitWidth=nWidth;
	m_nUnitHeight=nHeight;
	m_nMode=nMode;
	m_nRatio=nRatio;
	setGeometry(QRect(0, 0, m_nUnitWidth, m_nUnitHeight));
	setMinimumSize(QSize(m_nUnitWidth, m_nUnitHeight));
	setMaximumSize(QSize(m_nUnitWidth, m_nUnitHeight));
}


LEDIndicator::LEDIndicator(int nMode,int nBits,int nPages,int nUnitWidth,int nUnitHeight,int nRatio,QWidget *parent=nullptr)
: QWidget(parent),m_nBits(nBits),m_nPages(nPages),m_nUnitWidth(nUnitWidth),m_nUnitHeight(nUnitHeight),m_nMode(nMode),m_nRatio(nRatio),m_hBitmap(nullptr)
,m_nCurMode(0),m_bBtnDown(false),m_hBitmapTemp(nullptr),m_bTransparent(false)
{
	setAttribute(Qt::WA_PaintOnScreen,true);
	setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	setFocusPolicy(Qt::StrongFocus);

	memset(&m_tPtBegin,0,sizeof(POINT));
	memset(&m_tPtEnd,0,sizeof(POINT));
}

void LEDIndicator::paintEvent(QPaintEvent *)
{
	RECT tRect;
	HBRUSH hBr;
	HDC hDC = GetDC((HWND)this->winId());
	GetClientRect((HWND)this->winId(),&tRect);
	::FillRect(hDC,&tRect,(HBRUSH)GetStockObject(BLACK_BRUSH));
	if(m_hBitmap)
	{
		BITMAP bm;
		GetObject(m_hBitmap,sizeof(BITMAP),&bm);
		HDC hMemDC=CreateCompatibleDC(hDC);
		HBITMAP hOldBitmap=(HBITMAP)SelectObject(hMemDC,m_hBitmap);
		StretchBlt(hDC,0,0,bm.bmWidth*m_nRatio,bm.bmHeight*m_nRatio,hMemDC,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
		SelectObject(hMemDC,hOldBitmap);
		if(m_hBitmapTemp)
		{
			GetObject(m_hBitmapTemp,sizeof(BITMAP),&bm);
			hOldBitmap=(HBITMAP)SelectObject(hMemDC,m_hBitmapTemp);
			StretchBlt(hDC,m_tSelArea.left*m_nRatio,m_tSelArea.top*m_nRatio,bm.bmWidth*m_nRatio,bm.bmHeight*m_nRatio,hMemDC,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
			SelectObject(hMemDC,hOldBitmap);
		}
		DeleteDC(hMemDC);
	}
	SetRect(&tRect,m_tPtBegin.x*m_nRatio,m_tPtBegin.y*m_nRatio,m_tPtEnd.x*m_nRatio,m_tPtEnd.y*m_nRatio);
	::FrameRect(hDC,&tRect,(HBRUSH)GetStockObject(WHITE_BRUSH));
	
	ReleaseDC((HWND)this->winId(),hDC);
}

void LEDIndicator::resizeEvent(QResizeEvent *)
{
	
}

void LEDIndicator::setMode(int nMode)
{
	m_nCurMode=nMode;
	update();
}

void LEDIndicator::mousePressEvent(QMouseEvent *event)
{
	if(m_nCurMode==2)
	{	
		m_tPtEnd.x=m_tPtBegin.x=event->pos().x()/m_nRatio;
		m_tPtEnd.y=m_tPtBegin.y=event->pos().y()/m_nRatio;	
		m_bBtnDown=true;
		update();
	}
}

void LEDIndicator::mouseMoveEvent(QMouseEvent *event)
{
	if((m_nCurMode==2)||(m_bBtnDown))
	{
		if((m_tPtEnd.x!=event->pos().x()/m_nRatio+1)||
			(m_tPtEnd.y!=event->pos().y()/m_nRatio+1))
		{
			m_tPtEnd.x=event->pos().x()/m_nRatio+1;
			m_tPtEnd.y=event->pos().y()/m_nRatio+1;	
			update();
		}
	}
}

void LEDIndicator::mouseReleaseEvent(QMouseEvent *event)
{
	RECT tRect;
	if(m_nCurMode==2)
	{
		if(m_bBtnDown)
		{
			m_tPtEnd.x=event->pos().x()/m_nRatio+1;
			m_tPtEnd.y=event->pos().y()/m_nRatio+1;	
			
			if(m_hBitmapTemp)
				DeleteObject(m_hBitmapTemp);

			SetRect(&m_tSelArea,std::min(m_tPtBegin.x,m_tPtEnd.x),std::min(m_tPtBegin.y,m_tPtEnd.y),std::max(m_tPtBegin.x,m_tPtEnd.x),std::max(m_tPtBegin.y,m_tPtEnd.y));
			memcpy(&m_tTmpArea,&m_tSelArea,sizeof(RECT));
			OffsetRect(&m_tTmpArea,-m_tSelArea.left,-m_tSelArea.top);

			HDC hRefDC=GetDC((HWND)winId());
			m_hBitmapTemp=CDataManage::CreateBitmapByCreateDIBSection(hRefDC,m_tTmpArea.right-m_tTmpArea.left,m_tTmpArea.bottom-m_tTmpArea.top,m_nBits,&m_pBufferTemp);
			
			BITMAP bm;
			GetObject(m_hBitmapTemp,sizeof(BITMAP),&bm);

			HDC hDCSoc = CreateCompatibleDC(hRefDC);
			HDC hDCDes = CreateCompatibleDC(hRefDC);
			HBITMAP hOldBitmapSoc=(HBITMAP)SelectObject(hDCSoc,m_hBitmap);
			HBITMAP hOldBitmapDes=(HBITMAP)SelectObject(hDCDes,m_hBitmapTemp);
			BitBlt(hDCDes,0,0,m_tTmpArea.right-m_tTmpArea.left,m_tTmpArea.bottom-m_tTmpArea.top,hDCSoc,m_tSelArea.left,m_tSelArea.top,SRCCOPY);
			SelectObject(hDCSoc,hOldBitmapSoc);
			SelectObject(hDCDes,hOldBitmapDes);
			DeleteDC(hDCDes);
			DeleteDC(hDCSoc);





			ReleaseDC((HWND)winId(),hRefDC);

			m_bBtnDown=false;
			update();
		}
	}
}

void LEDIndicator::mouseDoubleClickEvent (QMouseEvent *event)
{
	int xPos=event->pos().x()/m_nRatio;
	int yPos=event->pos().y()/m_nRatio;

// 	RECT tRect;
// 	HDC hDC = GetDC(this->winId());
// 	if(m_hBitmap)
// 	{
// 		BITMAP bm;
// 		GetObject(m_hBitmap,sizeof(BITMAP),&bm);
// 		HDC hMemDC=CreateCompatibleDC(hDC);
// 		HBITMAP hOldBitmap=(HBITMAP)SelectObject(hMemDC,m_hBitmap);
// 		COLORREF uColor=GetPixel(hMemDC,xPos,yPos);
// 		if(uColor)
// 		{
// 			SetPixel(hMemDC,xPos,yPos,0);
// 		}
// 		else
// 		{
// 			SetPixel(hMemDC,xPos,yPos,32255);
// 		}
// 
// 		StretchBlt(hDC,0,0,bm.bmWidth*m_nRatio,bm.bmHeight*m_nRatio,hMemDC,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
// 		SelectObject(hMemDC,hOldBitmap);
// 		DeleteDC(hMemDC);
// 	}
// 	ReleaseDC(this->winId(),hDC);

}

LEDIndicator::~LEDIndicator()
{

}




int LEDIndicator::setRatio(int nRatio)
{
	if(nRatio>0||nRatio<10)
	{
		m_nRatio=nRatio;
	}
	return m_nRatio;
}

void LEDIndicator::selectAllArea()
{
	m_tPtBegin.x=0;
	m_tPtBegin.y=0;
	m_tPtEnd.x=m_nUnitWidth;
	m_tPtEnd.y=m_nUnitHeight;


	if(m_hBitmapTemp)
		DeleteObject(m_hBitmapTemp);

	SetRect(&m_tSelArea,std::min(m_tPtBegin.x,m_tPtEnd.x),std::min(m_tPtBegin.y,m_tPtEnd.y),std::max(m_tPtBegin.x,m_tPtEnd.x),std::max(m_tPtBegin.y,m_tPtEnd.y));
	memcpy(&m_tTmpArea,&m_tSelArea,sizeof(RECT));
	OffsetRect(&m_tTmpArea,-m_tSelArea.left,-m_tSelArea.top);

	HDC hRefDC=GetDC((HWND)winId());
	m_hBitmapTemp=CDataManage::CreateBitmapByCreateDIBSection(hRefDC,m_tTmpArea.right-m_tTmpArea.left,m_tTmpArea.bottom-m_tTmpArea.top,m_nBits,&m_pBufferTemp);

	BITMAP bm;
	GetObject(m_hBitmapTemp,sizeof(BITMAP),&bm);

	HDC hDCSoc = CreateCompatibleDC(hRefDC);
	HDC hDCDes = CreateCompatibleDC(hRefDC);
	HBITMAP hOldBitmapSoc=(HBITMAP)SelectObject(hDCSoc,m_hBitmap);
	HBITMAP hOldBitmapDes=(HBITMAP)SelectObject(hDCDes,m_hBitmapTemp);
	BitBlt(hDCDes,0,0,m_tTmpArea.right-m_tTmpArea.left,m_tTmpArea.bottom-m_tTmpArea.top,hDCSoc,m_tSelArea.left,m_tSelArea.top,SRCCOPY);
	SelectObject(hDCSoc,hOldBitmapSoc);
	SelectObject(hDCDes,hOldBitmapDes);
	DeleteDC(hDCDes);
	DeleteDC(hDCSoc);





	ReleaseDC((HWND)winId(),hRefDC);

	update();
}



BOOL LEDIndicator::setBinaryData(LPBYTE lpBufImages)
{
	if(m_pBuffer)
	{
		int nTotSize=((((m_nUnitWidth*m_nBits)/32)+(((m_nUnitWidth*m_nBits)%32)?1:0))*4)*m_nUnitHeight*m_nPages;
		memcpy(m_pBuffer,lpBufImages,nTotSize);
		//memcpy(m_pBuffer,lpBufImages,m_nUnitHeight*m_nUnitWidth*m_nBits*m_nPages/8);
		return TRUE;
	}
	return FALSE;
}


void LEDIndicator::setBitmap(int nPages,int nMode,LPVOID lpBuffer)
{
	HBITMAP hBitmap;
	byte **pPrev=nullptr;
	byte **pPrevTemp=nullptr;
	byte *pBuf=nullptr;
	int nPrevPages;
	int nMinPages;
	int nTotSize;
	if(m_hBitmap)
	{
		nPrevPages=m_nPages;
		pBuf=(byte*)m_pBuffer;
		switch(m_nMode)
		{
		case 0://Paging Mode
			pPrev=(byte**)malloc(sizeof(byte*)*m_nPages);
			pPrevTemp=(byte**)malloc(sizeof(byte*)*m_nPages);
			nTotSize=((((m_nUnitWidth*m_nBits)/32)+(((m_nUnitWidth*m_nBits)%32)?1:0))*4)*m_nUnitHeight*m_nPages;

			for (int i=0;i<m_nPages;i++) {
				pPrevTemp[i]=pPrev[i]=(byte*)malloc(nTotSize);//페이지 별로 메모리 할당
			}
			for(int i=0;i<m_nPages;i++)
			{
				memcpy(pPrevTemp[i],pBuf,(nTotSize));	//각 페이지에 메모리 복사
				pBuf+=(m_nUnitWidth*m_nUnitHeight*m_nBits/8);
			}

			break;
		case 1://ScrollModel
			pPrev=(byte**)malloc(sizeof(void*)*m_nPages);
			pPrevTemp=(byte**)malloc(sizeof(byte*)*m_nPages);
			nTotSize=((((m_nUnitWidth*m_nBits)/32)+(((m_nUnitWidth*m_nBits)%32)?1:0))*4)*m_nUnitHeight*m_nPages;
			for (int i=0;i<m_nPages;i++) {
				pPrevTemp[i]=pPrev[i]=(byte*)malloc(nTotSize);
			}
			for(int i=0;i<m_nUnitHeight;i++)
			{
				for(int j=0;j<m_nPages;j++)
				{
					memcpy(pPrevTemp[j],pBuf,(m_nUnitWidth*m_nBits/8));
					pPrevTemp[j]+=(m_nUnitWidth*m_nBits/8);
					pBuf+=(m_nUnitWidth*m_nBits/8);
				}
			}
			break;
		}

		DeleteObject(m_hBitmap);
		m_hBitmap=nullptr;
	}
	

	HDC hRefDC;
	switch(nMode)
	{
	case 0://Paging
		hRefDC=GetDC((HWND)winId());

		nTotSize=((((m_nUnitWidth*m_nBits)/32)+(((m_nUnitWidth*m_nBits)%32)?1:0))*4)*m_nUnitHeight*m_nPages;
		
		hBitmap=CDataManage::CreateBitmapByCreateDIBSection(hRefDC,m_nUnitWidth,m_nUnitHeight*nPages,m_nBits,&m_pBuffer);
		if(lpBuffer)
		{
			memcpy(m_pBuffer,lpBuffer,nTotSize);
		}
		ReleaseDC((HWND)this->winId(),hRefDC);
		if(hBitmap)
		{
			m_hBitmap=hBitmap;
		}

		m_nPages=nPages;
		m_nMode=nMode;
		if(!lpBuffer)
		{
			for (int i=0;i<nPrevPages;i++) {
				pPrevTemp[i]=pPrev[i];
			}
			pBuf=(byte*)m_pBuffer;
			nMinPages=std::min(nPrevPages,m_nPages);
			for(int i=0;i<nMinPages;i++)
			{
				memcpy(pBuf,pPrevTemp[i],(m_nUnitWidth*m_nUnitHeight*m_nBits/8));
				pBuf+=(m_nUnitWidth*m_nUnitHeight*m_nBits/8);
			}
		}

		resize(m_nUnitWidth*m_nRatio,m_nUnitHeight*m_nPages*m_nRatio);

		break;
	case 1://Scroll
		hRefDC=GetDC((HWND)winId());
		nTotSize=((((m_nUnitWidth*m_nBits)/32)+(((m_nUnitWidth*m_nBits)%32)?1:0))*4)*m_nUnitHeight*m_nPages;
		hBitmap=CDataManage::CreateBitmapByCreateDIBSection(hRefDC,m_nUnitWidth*nPages,m_nUnitHeight,m_nBits,&m_pBuffer);
		if(lpBuffer)	
		{
			memcpy(m_pBuffer,lpBuffer,nTotSize);
		}
		ReleaseDC((HWND)this->winId(),hRefDC);
		if(hBitmap)
		{
			m_hBitmap=hBitmap;
		}
		m_nPages=nPages;
		m_nMode=nMode;
		if(!lpBuffer)
		{
			for (int i=0;i<nPrevPages;i++) {
				pPrevTemp[i]=pPrev[i];
			}
			pBuf=(byte*)m_pBuffer;
			nMinPages=std::min(nPrevPages,m_nPages);			

			for(int i=0;i<m_nUnitHeight;i++)
			{
				for(int j=0;j<m_nPages;j++)
				{
					if(j<nMinPages)
					{
						memcpy(pBuf,pPrevTemp[j],(m_nUnitWidth*m_nBits/8));
						pPrevTemp[j]+=(m_nUnitWidth*m_nBits/8);
					}
					pBuf+=(m_nUnitWidth*m_nBits/8);
				}
			}
		}

		resize(m_nUnitWidth*nPages*m_nRatio,m_nUnitHeight*m_nRatio);



		break;
	}
	if(pPrev)
	{
		for(int i=0;i<nPrevPages;i++)
		{
			free(pPrev[i]);
		}
	}
	free(pPrev);
	update();
}


void LEDIndicator::setText(LPCWSTR lpStrText,LPCWSTR lpStrFont,int nSize,int nVert,int nHorz,UINT nClrBkGnd,UINT nClrFgGnd,bool bBkTransparent,bool bBold)
{
	int nCount=0;
	int nStart=0;
	int nMaxWidth=0;
	int nCurHeight=0;
	RECT tRect;
	UINT uVertFlg=0,uHorzFlg=0;
	m_bTransparent=bBkTransparent;
	HDC hRefDC=GetDC((HWND)winId());
	HDC hDC = CreateCompatibleDC(hRefDC);
	HFONT hOldFont,hFont=CreateFont(nSize,0,0,0,bBold?FW_HEAVY:FW_NORMAL,0,0,0,DEFAULT_CHARSET,3,2,1,VARIABLE_PITCH | FF_ROMAN,lpStrFont);
	HBITMAP hOldBitmap=(HBITMAP)SelectObject(hDC,m_hBitmapTemp);
	hOldFont=(HFONT)SelectObject(hDC,hFont);
	FillRect(hDC,&m_tTmpArea,(HBRUSH)GetStockObject(BLACK_BRUSH));

	if(bBkTransparent)
	{
		SetBkMode(hDC,TRANSPARENT);
	}
	else
	{
		SetBkMode(hDC,OPAQUE);
		SetBkColor(hDC,nClrBkGnd);
	}

	{
		HDC hSocDC=CreateCompatibleDC(hRefDC);
		HBITMAP hOldBitmapTemp=(HBITMAP)SelectObject(hSocDC,m_hBitmap);
		BitBlt(hDC,0,0,m_tTmpArea.right-m_tTmpArea.left,m_tTmpArea.bottom-m_tTmpArea.top,hSocDC,m_tSelArea.left,m_tSelArea.top,SRCCOPY);
		SelectObject(hSocDC,hOldBitmapTemp);
		DeleteDC(hSocDC);
	}


	SetTextColor(hDC,nClrFgGnd);
	switch(nVert)
	{
	case 0:
		uVertFlg=DT_TOP;break;
	case 1:
		uVertFlg=DT_VCENTER;break;
	case 2:
		uVertFlg=DT_BOTTOM;break;
	}
	switch(nHorz)
	{
	case 0:
		uHorzFlg=DT_LEFT;break;
	case 1:
		uHorzFlg=DT_CENTER;break;
	case 2:
		uHorzFlg=DT_RIGHT;break;
	}
	DrawTextNew(hDC,lpStrText,wcslen(lpStrText),&m_tTmpArea,uHorzFlg,uVertFlg);

	SelectObject(hDC,hOldBitmap);
	SelectObject(hDC,hOldFont);
	DeleteObject(hFont);
	ReleaseDC((HWND)winId(),hRefDC);
	update();
}




void LEDIndicator::setImage(HBITMAP hBitmap)
{
	int nCount=0;
	int nStart=0;
	int nMaxWidth=0;
	int nCurHeight=0;
	RECT tRect;
	UINT uVertFlg=0,uHorzFlg=0;
	HDC hRefDC=GetDC((HWND)winId());
	HDC hDC = CreateCompatibleDC(hRefDC);
	HBITMAP hOldBitmap=(HBITMAP)SelectObject(hDC,m_hBitmapTemp);
	{
		HDC hSocDC=CreateCompatibleDC(hRefDC);
		HBITMAP hOldBitmapTemp=(HBITMAP)SelectObject(hSocDC,hBitmap);
		BitBlt(hDC,0,0,m_tTmpArea.right-m_tTmpArea.left,m_tTmpArea.bottom-m_tTmpArea.top,hSocDC,m_tSelArea.left,m_tSelArea.top,SRCCOPY);
		SelectObject(hSocDC,hOldBitmapTemp);
		DeleteDC(hSocDC);
	}
	SelectObject(hDC,hOldBitmap);
	ReleaseDC((HWND)winId(),hRefDC);
	update();
}


void LEDIndicator::clearImage()
{
	int nCount=0;
	int nStart=0;
	int nMaxWidth=0;
	int nCurHeight=0;
	RECT tRect;
	UINT uVertFlg=0,uHorzFlg=0;
	HDC hRefDC=GetDC((HWND)winId());
	HDC hDC = CreateCompatibleDC(hRefDC);
	HBITMAP hOldBitmap=(HBITMAP)SelectObject(hDC,m_hBitmapTemp);
	{
		//HDC hSocDC=CreateCompatibleDC(hRefDC);
		//HBITMAP hOldBitmapTemp=(HBITMAP)SelectObject(hSocDC,hBitmap);
		//BitBlt(hDC,0,0,m_tTmpArea.right-m_tTmpArea.left,m_tTmpArea.bottom-m_tTmpArea.top,hSocDC,m_tSelArea.left,m_tSelArea.top,SRCCOPY);
		//SelectObject(hSocDC,hOldBitmapTemp);
		//DeleteDC(hSocDC);

		PatBlt(hDC,m_tTmpArea.left,m_tTmpArea.top,m_tTmpArea.right-m_tTmpArea.left,m_tTmpArea.bottom-m_tTmpArea.top,BLACKNESS);
	}
	SelectObject(hDC,hOldBitmap);
	ReleaseDC((HWND)winId(),hRefDC);
	update();
}


QPaintEngine* LEDIndicator::paintEngine(void)  const
{
	return nullptr;
}






void LEDIndicator::setCurrentInputedText()
{
	if(m_hBitmapTemp)
	{
		HDC hRefDC=GetDC((HWND)winId());
		HDC hDCSoc = CreateCompatibleDC(hRefDC);
		HDC hDCDes = CreateCompatibleDC(hRefDC);
		HBITMAP hOldBitmapSoc=(HBITMAP)SelectObject(hDCSoc,m_hBitmapTemp);
		HBITMAP hOldBitmapDes=(HBITMAP)SelectObject(hDCDes,m_hBitmap);
		BitBlt(hDCDes,m_tSelArea.left,m_tSelArea.top,m_tSelArea.right-m_tSelArea.left,m_tSelArea.bottom-m_tSelArea.top,hDCSoc,0,0,SRCCOPY);
		SelectObject(hDCSoc,hOldBitmapSoc);
		SelectObject(hDCDes,hOldBitmapDes);
		DeleteDC(hDCDes);
		DeleteDC(hDCSoc);
		memset(&m_tPtBegin,0,sizeof(POINT));
		memset(&m_tPtEnd,0,sizeof(POINT));
		ReleaseDC((HWND)winId(),hRefDC);
		DeleteObject(m_hBitmapTemp);
		m_hBitmapTemp=nullptr;
		update();
	}
}
