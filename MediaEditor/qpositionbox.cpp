#include "qpositionbox.h"
#include <qdebug.h>
QPositionBox::QPositionBox(QWidget *parent)
	: QLineEdit(parent),m_uPositionValue(0)
{
}

QPositionBox::~QPositionBox()
{
}


unsigned int QPositionBox::positionValue() const
{
	return m_uPositionValue;
}

void QPositionBox::setPositionValue(unsigned int uPositionValue)
{
	QString strText=QString("(%1,%2)").arg((uPositionValue>>16)&0x0000FFFF).arg((uPositionValue)&0x0000FFFF);
	m_uPositionValue=uPositionValue;
	setText(strText);
}
