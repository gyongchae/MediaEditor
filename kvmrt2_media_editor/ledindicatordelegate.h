#ifndef LEDINDICATORDELEGATE_H
#define LEDINDICATORDELEGATE_H

#include <QStyledItemDelegate>
#include <QtGui>


class LEDIndicatorDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	LEDIndicatorDelegate(int nWidthRow,int nHeightRow,int nPagesRow,int nModeRow,int nBufRow,int nBitRow,QObject *parent=0);

	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	~LEDIndicatorDelegate();

private:
	int m_nBitRow;
	int m_nWidthRow;
	int m_nHeightRow;
	int m_nPagesRow;
	int m_nModeRow;
	int m_nBufRow;	
};

#endif // LEDINDICATORDELEGATE_H
