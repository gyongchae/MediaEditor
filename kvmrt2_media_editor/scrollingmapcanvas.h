#ifndef SCROLLINGMAPCANVAS_H
#define SCROLLINGMAPCANVAS_H

#include <QScrollArea>

class QLineMap;

class ScrollingMapCanvas : public QScrollArea
{
	Q_OBJECT

public:
	ScrollingMapCanvas(QWidget* parent);
	~ScrollingMapCanvas();
	
	void setLineMap(QLineMap *lineMap);
	QLineMap* lineMap() const;

protected:
	void resizeEvent(QResizeEvent* event);
	void scrollContentsBy(int dx,int dy);
private:
	QLineMap* m_LineMap;
};

#endif // SCROLLINGMAPCANVAS_H
