#include <QtGui>
#include "tiledelegate.h"
#include "defineTileMap.h"
#include <QDebug>

tileDelegate::tileDelegate(QObject *parent)
	: QAbstractItemDelegate(parent)
{
	m_nTileSize=64;
	//m_ImageTiles=new QImage(1920,1080,QImage::Format_RGB32);

}

tileDelegate::~tileDelegate()
{
}

void tileDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	if(option.state&QStyle::State_Selected)
		painter->fillRect(option.rect,option.palette.highlight());
	TileType tileIndex=(TileType)index.model()->data(index, Qt::DisplayRole).toInt();
	painter->save();
	painter->setRenderHint(QPainter::Antialiasing,true);
	painter->setPen(QPen(Qt::black,10,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
	painter->setClipRect(option.rect);
	int width=option.rect.width();
	int height=option.rect.height();
	QPoint centerPoint;//,centerPoint2;
	QRect boundRect;//,boundRect2;
	centerPoint.setX(option.rect.left()+(option.rect.width()/2));
	centerPoint.setY(option.rect.top()+(option.rect.height()/2));
	switch(tileIndex)
	{
	case TILE_NONE:
		break;
	case TILE_H_U:
		painter->drawLine(centerPoint.x(),option.rect.top(),centerPoint.x(),centerPoint.y());
		//imagePainter->drawLine(centerPoint2.x(),boundRect2.top(),centerPoint2.x(),centerPoint2.y());
		break;
	case TILE_H_D:
		painter->drawLine(centerPoint.x(),centerPoint.y(),centerPoint.x(),option.rect.bottom());
		//imagePainter->drawLine(centerPoint2.x(),centerPoint2.y(),centerPoint2.x(),boundRect2.bottom());
		break;
	case TILE_H_L:
		painter->drawLine(option.rect.left(),centerPoint.y(),centerPoint.x(),centerPoint.y());
		//imagePainter->drawLine(boundRect2.left(),centerPoint2.y(),centerPoint2.x(),centerPoint2.y());
		break;
	case TILE_H_R:
		painter->drawLine(centerPoint.x(),centerPoint.y(),option.rect.right(),centerPoint.y());
		//imagePainter->drawLine(centerPoint2.x(),centerPoint2.y(),boundRect2.right(),centerPoint2.y());
		break;
	case TILE_F_UD:
		painter->drawLine(centerPoint.x(),option.rect.top(),centerPoint.x(),option.rect.bottom());
		//imagePainter->drawLine(centerPoint2.x(),boundRect2.top(),centerPoint2.x(),boundRect2.bottom());
		break;
	case TILE_F_LR:
		painter->drawLine(option.rect.left(),centerPoint.y(),option.rect.right(),centerPoint.y());
		//imagePainter->drawLine(boundRect2.left(),centerPoint2.y(),boundRect2.right(),centerPoint2.y());
		break;
	case TILE_CROSS:
		painter->drawLine(centerPoint.x(),option.rect.top(),centerPoint.x(),option.rect.bottom());
		painter->drawLine(option.rect.left(),centerPoint.y(),option.rect.right(),centerPoint.y());
		//imagePainter->drawLine(centerPoint.x(),boundRect2.top(),centerPoint.x(),boundRect2.bottom());
		//imagePainter->drawLine(boundRect2.left(),centerPoint.y(),boundRect2.right(),centerPoint.y());
		break;

	case TILE_F_UD_H_L:
		painter->drawLine(centerPoint.x(),option.rect.top(),centerPoint.x(),option.rect.bottom());
		painter->drawLine(centerPoint.x(),centerPoint.y(),option.rect.left(),centerPoint.y());
		//imagePainter->drawLine(centerPoint2.x(),boundRect2.top(),centerPoint2.x(),boundRect2.bottom());
		//imagePainter->drawLine(centerPoint2.x(),centerPoint2.y(),boundRect2.left(),centerPoint2.y());
		break;
	case TILE_F_UD_H_R:
		painter->drawLine(centerPoint.x(),option.rect.top(),centerPoint.x(),option.rect.bottom());
		painter->drawLine(centerPoint.x(),centerPoint.y(),option.rect.right(),centerPoint.y());
		//imagePainter->drawLine(centerPoint2.x(),boundRect2.top(),centerPoint2.x(),boundRect2.bottom());
		//imagePainter->drawLine(centerPoint2.x(),centerPoint2.y(),boundRect2.right(),centerPoint2.y());
		break;
	case TILE_F_LR_H_U:
		painter->drawLine(option.rect.left(),centerPoint.y(),option.rect.right(),centerPoint.y());
		painter->drawLine(centerPoint.x(),centerPoint.y(),centerPoint.x(),option.rect.top());
		//imagePainter->drawLine(boundRect2.left(),centerPoint2.y(),boundRect2.right(),centerPoint2.y());
		//imagePainter->drawLine(centerPoint2.x(),centerPoint2.y(),centerPoint2.x(),boundRect2.top());
		break;
	case TILE_F_LR_H_D:
		painter->drawLine(centerPoint.x(),centerPoint.y(),centerPoint.x(),option.rect.bottom());
		painter->drawLine(option.rect.left(),centerPoint.y(),option.rect.right(),centerPoint.y());
		//imagePainter->drawLine(centerPoint2.x(),centerPoint2.y(),centerPoint2.x(),boundRect2.bottom());
		//imagePainter->drawLine(boundRect2.left(),centerPoint2.y(),boundRect2.right(),centerPoint2.y());
		break;
	case TILE_C_LU:
		boundRect=QRect(option.rect.left()-(option.rect.width()/2),
						option.rect.top()-(option.rect.height()/2),
						option.rect.width(),option.rect.height());

		painter->drawArc(boundRect,0,-90*16);
// 		boundRect=QRect(boundRect2.left()-(boundRect2.width()/2),
// 			boundRect2.top()-(boundRect2.height()/2),
// 			boundRect2.width(),boundRect2.height());
// 
// 		imagePainter->drawArc(boundRect,0,-90*16);
		break;
	case TILE_C_LD:
		boundRect=QRect(option.rect.left()-(option.rect.width()/2),
			centerPoint.y(),
			option.rect.width(),option.rect.height());
		painter->drawArc(boundRect,0,90*16);
// 		boundRect=QRect(boundRect2.left()-(boundRect2.width()/2),
// 			centerPoint2.y(),
// 			boundRect2.width(),boundRect2.height());
// 		imagePainter->drawArc(boundRect,0,90*16);
		break;
	case TILE_C_RD:
		boundRect=QRect(centerPoint.x(),centerPoint.y(),
			option.rect.width(),option.rect.height());
		painter->drawArc(boundRect,180*16,-90*16);
// 		boundRect=QRect(centerPoint2.x(),centerPoint2.y(),
// 			boundRect2.width(),boundRect2.height());
// 		imagePainter->drawArc(boundRect,180*16,-90*16);
		break;
	case TILE_C_RU:
		boundRect=QRect(centerPoint.x(),
			option.rect.top()-(option.rect.height()/2),
			option.rect.width(),option.rect.height());
		painter->drawArc(boundRect,180*16,90*16);
// 		boundRect=QRect(centerPoint2.x(),
// 			boundRect2.top()-(boundRect2.height()/2),
// 			boundRect2.width(),boundRect2.height());
// 		imagePainter->drawArc(boundRect,180*16,90*16);
		break;
	default:
		break;
	}
	painter->restore();
}

QSize tileDelegate::sizeHint(const QStyleOptionViewItem &option,
							  const QModelIndex &index) const
{
	return QSize(m_nTileSize,m_nTileSize);
}

void tileDelegate::setTileSize(int size)
{
	m_nTileSize = size;
}

// QImage *tileDelegate::getImage()
// {
// 	//return m_ImageTiles;
// }