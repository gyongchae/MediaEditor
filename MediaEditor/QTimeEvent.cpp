#include "QTimeEvent.h"
#include <QMouseEvent>
#include <QPainter>
#include <qdebug.h>

#define PIXEL_PER_SECONDS		200
#define PIXEL_HEIGHT_PER_ITEM	20
#define PIXEL_PER_50MS			(PIXEL_PER_SECONDS/PIXEL_HEIGHT_PER_ITEM)
#define PIXEL_PER_HALFSECONDS	(PIXEL_PER_50MS*10)

QTimeEvent::QTimeEvent(int nMiliseconds, QWidget *pParent)
	:QWidget(pParent), m_nMiliseconds(nMiliseconds),m_nWidth((((float)m_nMiliseconds / 1000.0f)*((float)PIXEL_PER_SECONDS))),m_nHeight(PIXEL_HEIGHT_PER_ITEM*2),
	m_bPressed(false), m_nCurTime(0), m_pvKeyFrames(0)
{
	m_tSelRect = QRect(0, 0, PIXEL_PER_50MS, m_nHeight);
}


QTimeEvent::~QTimeEvent()
{
}


void QTimeEvent::paintEvent(QPaintEvent * event)
{
	QPainter painter(this);
	//painter.drawRect(0, 0, m_nWidth, m_nHeight);
	int nGridLength;
	for (int i = 0; i < m_nWidth; i += PIXEL_PER_50MS)
	{
		if ((i%PIXEL_PER_HALFSECONDS) == 0)
			nGridLength = 10;
		else
			nGridLength = 5;
		painter.drawLine(i, 0, i, nGridLength);

		if (nGridLength == 10)
		{
			
			painter.drawText(QPoint(i, 25), QString("%1").arg(i*5));
		}

		
	}
	if (m_pvKeyFrames)
	{
		for (auto it : (*m_pvKeyFrames))
		{
			QRect tRect = QRect((((float)it / 1000.0)* PIXEL_PER_SECONDS), 0, PIXEL_PER_50MS, m_nHeight / 2);
			painter.fillRect(tRect, QBrush(QColor(255, 0, 0)));
		}
	}
	if(m_bPressed)
		painter.fillRect(m_tSelRect,QBrush(QColor(255,255,0)));
	else
		painter.fillRect(m_tSelRect, QBrush(QColor(0, 125, 255)));
}

void QTimeEvent::setTimeVector(QVector<int> *pVec)
{
	m_pvKeyFrames = pVec;
}


void QTimeEvent::resizeEvent(QResizeEvent* event)
{
}

void QTimeEvent::mousePressEvent(QMouseEvent * e)
{
	if (m_tSelRect.contains(e->pos()))
	{
		m_bPressed = true;
	}
}

void QTimeEvent::mouseMoveEvent(QMouseEvent *e)
{
	int nLeft = e->pos().x();
	if ((m_nWidth- PIXEL_PER_50MS) < e->pos().x())
		nLeft = (m_nWidth- PIXEL_PER_50MS);
	else if (e->pos().x() < 0)
		nLeft = 0;
	m_nCurTime = ((nLeft / PIXEL_PER_50MS))*PIXEL_PER_50MS;
	
	m_tSelRect.setX(m_nCurTime);
	m_tSelRect.setWidth(PIXEL_PER_50MS);
	if (m_nPrevTime != m_nCurTime)
	{
		m_nPrevTime = m_nCurTime;
		emit timeChanged((int)(((float)m_nCurTime/(float)PIXEL_PER_SECONDS)*1000.f));
	}
	update();
}

void QTimeEvent::mouseReleaseEvent(QMouseEvent *e)
{
	m_bPressed = false;
	update();
}


int QTimeEvent::curTime()
{
	return m_nCurTime;
}

QSize QTimeEvent::sizeHint() const
{
	return QSize(m_nWidth, m_nHeight);
}
