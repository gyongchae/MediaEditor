#ifndef LEDINDICATORINDIRECTDELEGATE_H
#define LEDINDICATORINDIRECTDELEGATE_H

#include <QStyledItemDelegate>
#include <QtGui>
#include <vector>
#include <memory>
#include <QPixmap>

class CSQLData;


class LEDIndicatorIndirectDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	LEDIndicatorIndirectDelegate(int nWidth,int nHeight,int nBit,int nWidthRow,int nHeightRow,int nPagesRow,int nModeRow,int nBufRow,int nBitRow,std::vector<std::shared_ptr<CSQLData>> *pVector,QObject *parent=0);
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	//void updateImage(int nWidth,int nHeight,int nPage,int nMode,uchar *pChar);
	// /void updateImage(int nWidth,int nHeight,int nPage,int nMode,uchar *pChar) const;
	~LEDIndicatorIndirectDelegate();

private:
	std::vector<std::shared_ptr<CSQLData>> *m_pDDI;
	int m_nDefWidth;
	int m_nDefHeight;
	int m_nDefBits;

private:
	int m_nBitRow;
	int m_nWidthRow;
	int m_nHeightRow;
	int m_nPagesRow;
	int m_nModeRow;
	int m_nBufRow;
};

#endif // LEDINDICATORINDIRECTDELEGATE_H
