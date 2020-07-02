#include "ledindicatordelegate.h"
#include "DataManage.h"
#include <Qpixmap>

#if QT_VERSION >= 0x050000
#include <QtWin>
#endif



LEDIndicatorDelegate::LEDIndicatorDelegate(int nWidthRow,int nHeightRow,int nPagesRow,int nModeRow,int nBufRow,int nBitRow,QObject *parent)
: QStyledItemDelegate(parent),m_nBitRow(nBitRow),m_nWidthRow(nWidthRow),m_nHeightRow(nHeightRow),m_nPagesRow(nPagesRow),m_nModeRow(nModeRow),m_nBufRow(nBufRow)
{
	
}

LEDIndicatorDelegate::~LEDIndicatorDelegate()
{

}

void LEDIndicatorDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	bool bFocus=option.state&QStyle::State_HasFocus;
	bool bSelected=option.state&QStyle::State_Selected;
	bool bActive=option.state&QStyle::State_Active;
	if((bSelected)&&(bActive))
		painter->fillRect(option.rect,option.palette.highlight());
	if((bSelected)&&(!bActive))
		painter->fillRect(option.rect,option.palette.background());

	int nWidth=index.model()->data(index.sibling(index.row(),m_nWidthRow),Qt::DisplayRole).toInt();
	int nHeight=index.model()->data(index.sibling(index.row(),m_nHeightRow),Qt::DisplayRole).toInt();
	int nPages=index.model()->data(index.sibling(index.row(),m_nPagesRow),Qt::DisplayRole).toInt();
	int nMode=index.model()->data(index.sibling(index.row(),m_nModeRow),Qt::DisplayRole).toInt();
	int nBits=index.model()->data(index.sibling(index.row(),m_nBitRow),Qt::DisplayRole).toInt();
	void *pBufSoc=(void*)index.model()->data(index.sibling(index.row(),m_nBufRow),Qt::DisplayRole).toUInt();
	void *pBufDes;
	HDC hRefDC=GetDC(nullptr);
	int nTotSize=(nWidth*nHeight*nBits*nPages)/8;
	HBITMAP hBitmap;
	switch(nMode)
	{
	case 0:
		hBitmap=CDataManage::CreateBitmapByCreateDIBSection(hRefDC,nWidth,nHeight*nPages,nBits,&pBufDes);
		memcpy(pBufDes,pBufSoc,nTotSize);break;
	case 1:
		hBitmap=CDataManage::CreateBitmapByCreateDIBSection(hRefDC,nWidth*nPages,nHeight,nBits,&pBufDes);
		memcpy(pBufDes,pBufSoc,nTotSize);break;
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