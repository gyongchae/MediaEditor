#ifndef TILEDELEGATE_H
#define TILEDELEGATE_H

#include <QAbstractItemDelegate>
#include <QModelIndex>
#include <QSize>

class QAbstractItemModel;


class tileDelegate : public QAbstractItemDelegate
{
	Q_OBJECT

public:
	tileDelegate(QObject *parent=0);
	~tileDelegate();
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
	//QImage *getImage();
public slots:
	void setTileSize(int size);
private:
	int m_nTileSize;
	//QImage *m_ImageTiles;
};

#endif // TILEDELEGATE_H
