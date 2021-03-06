#include "scrollingmapcanvas.h"
#include "QLineMap.h"
#include <QScrollBar>
#include <qdebug.h>

ScrollingMapCanvas::ScrollingMapCanvas(QWidget* parent)
	:QScrollArea(parent),m_LineMap(nullptr)
{
	//m_LineMap=lineMap;
	//m_LineMap->setParent(viewport());
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}
ScrollingMapCanvas::~ScrollingMapCanvas()
{
}

void ScrollingMapCanvas::resizeEvent(QResizeEvent* /*event*/)
{
	QSize areaSize = viewport()->size();
	if(m_LineMap)
		m_LineMap->resize(areaSize);
	int width = 1920;
	int height = 1080;
	QSize mapSize=QSize(width,height);
	horizontalScrollBar()->setPageStep(areaSize.width());
	verticalScrollBar()->setPageStep(areaSize.height());
	horizontalScrollBar()->setRange(0,mapSize.width() - areaSize.width());
	verticalScrollBar()->setRange(0,mapSize.height() - areaSize.height());
}

void ScrollingMapCanvas::scrollContentsBy(int dx, int dy)
{
	if(m_LineMap)
		m_LineMap->scroll(-dx,-dy);
}

QLineMap* ScrollingMapCanvas::lineMap() const
{
 	return m_LineMap;
}

void ScrollingMapCanvas::setLineMap(QLineMap *lineMap)
{
	if(!m_LineMap)
	{
		m_LineMap=lineMap;
		m_LineMap->setParent(viewport());
	}
}