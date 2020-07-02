#ifndef QTIMEEVENT_H
#define QTIMEEVENT_H
#include <QWidget>

class QTimeEvent
	:public QWidget
{
	Q_OBJECT
public:
	QTimeEvent(int nMiliseconds,QWidget *pParent);
	~QTimeEvent();

	QSize sizeHint() const;
	int curTime();
protected:
	void paintEvent(QPaintEvent * event);
	void resizeEvent(QResizeEvent* event);
	void mousePressEvent(QMouseEvent * e);
	void mouseMoveEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
public:
	int m_nMiliseconds;
	int m_nWidth;
	int m_nHeight;
	QRect m_tSelRect;
	bool m_bPressed;
	int m_nCurTime;
	int m_nPrevTime;
	void setTimeVector(QVector<int> *pVec);
private:
	QVector<int> *m_pvKeyFrames;
signals:
	void timeChanged(int /*nTimeEvent*/);

};

#endif