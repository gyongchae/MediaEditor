#include "ledindicatorIndirectdelegate.h"
#include "SQLData.h"
#include "DataManage.h"
#include <QPixmap>
#if QT_VERSION >= 0x050000
	#include <QtWin>
#endif


LEDIndicatorIndirectDelegate::LEDIndicatorIndirectDelegate(int nWidth,int nHeight,int nBit,int nWidthRow,int nHeightRow,int nPagesRow,int nModeRow,int nBufRow,int nBitRow,std::vector<std::shared_ptr<CSQLData>> *pVector,QObject *parent)
: QStyledItemDelegate(parent),m_nDefWidth(nWidth),m_nDefHeight(nHeight),m_nDefBits(nBit),m_pDDI(pVector),m_nBitRow(nBitRow),m_nWidthRow(nWidthRow),m_nHeightRow(nHeightRow),m_nPagesRow(nPagesRow),m_nModeRow(nModeRow),m_nBufRow(nBufRow)
{

}

LEDIndicatorIndirectDelegate::~LEDIndicatorIndirectDelegate()
{

}

void LEDIndicatorIndirectDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	bool bFocus=option.state&QStyle::State_HasFocus;
	bool bSelected=option.state&QStyle::State_Selected;
	bool bActive=option.state&QStyle::State_Active;
	if((bSelected)&&(bActive))
		painter->fillRect(option.rect,option.palette.highlight());
	if((bSelected)&&(!bActive))
		painter->fillRect(option.rect,option.palette.background());


	int nWidth,nHeight,nPages,nMode,nBits;
	unsigned char *pBufSoc=nullptr;
	unsigned char *pBufDes;
	std::vector<std::shared_ptr<CSQLData>>::iterator nit;
	int nIndex=index.data(Qt::DisplayRole).toInt();
	nit=find_if(m_pDDI->begin(),m_pDDI->end(),findSQLData(nIndex));
	if(nit!=m_pDDI->end())
	{

		/*nWidth=nit->get()->nWidth;
		nHeight=nit->get()->nHeight;
		nPages=nit->get()->nPage;
		nMode=nit->get()->nMode;
		nBits=nit->get()->nBit;
		pBufSoc=(void*)nit->get()->pBuffer;*/

		nit->get()->GetData(m_nWidthRow,&nWidth);
		nit->get()->GetData(m_nHeightRow,&nHeight);
		nit->get()->GetData(m_nPagesRow,&nPages);
		nit->get()->GetData(m_nModeRow,&nMode);
		nit->get()->GetData(m_nBitRow,&nBits);
		nit->get()->GetData(m_nBufRow,(void*)&pBufSoc);
	
	/*	nit->get()->

		nWidth=index.model()->data(index.sibling(index.row(),m_nWidthRow),Qt::DisplayRole).toInt();
		nHeight=index.model()->data(index.sibling(index.row(),m_nHeightRow),Qt::DisplayRole).toInt();
		nPages=index.model()->data(index.sibling(index.row(),m_nPagesRow),Qt::DisplayRole).toInt();
		nMode=index.model()->data(index.sibling(index.row(),m_nModeRow),Qt::DisplayRole).toInt();
		nBits=index.model()->data(index.sibling(index.row(),m_nBitRow),Qt::DisplayRole).toInt();
		pBufSoc=(void*)index.model()->data(index.sibling(index.row(),m_nBufRow),Qt::DisplayRole).toUInt();*/
	}
	else
	{
		nWidth=m_nDefWidth;
		nHeight=m_nDefHeight;
		nPages=1;
		nMode=0;
		nBits=m_nDefBits;
	}
		
	HDC hRefDC=GetDC(nullptr);
	int nTotSize=(nWidth*nHeight*nBits*nPages)/8;
	nTotSize=(((nWidth*nBits)/32)+(((nWidth*nBits)%32)?1:0))*4*nPages*nHeight;
	HBITMAP hBitmap;
	switch(nMode)
	{
	case 0:
		hBitmap=CDataManage::CreateBitmapByCreateDIBSection(hRefDC,nWidth,nHeight*nPages,nBits,(LPVOID*)&pBufDes);
		//비트에 맞게 메모리 다시 복사 한다.
		//다음의 식을 활용한다.(((i*nBits)/32)+(((i*nBits)%32)?1:0))*4;
		if(pBufDes&&pBufSoc)
			memcpy(pBufDes,pBufSoc,nTotSize);
		break;
	case 1:
		hBitmap=CDataManage::CreateBitmapByCreateDIBSection(hRefDC,nWidth*nPages,nHeight,nBits, (LPVOID*)&pBufDes);
		//비트에 맞게 메모리 다시 복사 한다.
		if(pBufDes&&pBufSoc)
			memcpy(pBufDes,pBufSoc,nTotSize);
		break;
	default:
		break;
	}
	ReleaseDC(nullptr,hRefDC);
#if QT_VERSION >= 0x050000
	QPixmap fromBitmap = QtWin::fromHBITMAP(hBitmap);
 #else
	QPixmap fromBitmap = QPixmap::fromWinHBITMAP(hBitmap);
#endif
	int xOffset=(option.rect.width()-fromBitmap.width())/2;
	int yOffset=(option.rect.height()-fromBitmap.height())/2;
	painter->drawPixmap(option.rect.x()+xOffset,option.rect.y()+yOffset,fromBitmap);
	DeleteObject(hBitmap);
}

// void LEDIndicatorIndirectDelegate::updateImage(int nWidth,int nHeight,int nPage,int nMode,uchar *pChar)
// {
// 	if(m_pImage)
// 	{
// 		delete m_pImage;
// 		//m_pImage=nullptr;
// 	}
// 	switch(nMode)	//단색Gdiplus::Bitmap의 경우
// 	{
// 	case 0:	//Paging Mode;
// 		m_pImage=new QImage(nWidth,nHeight*nPage,QImage::Format_Mono);
// 		break;
// 	case 1:	//Scroll Mode;
// 		m_pImage=new QImage(nWidth*nPage,nHeight,QImage::Format_Mono);
// 		break;
// 	}
// 	uchar *pBuffer=pChar;
// 	for(int i=0;i<m_pImage->height();i++)
// 	{
// 		memcpy(m_pImage->scanLine(i),pBuffer,m_pImage->bytesPerLine());
// 		pBuffer+=m_pImage->bytesPerLine();
// 	}
// }