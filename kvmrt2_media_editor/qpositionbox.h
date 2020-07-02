#ifndef QPOSITIONBOX_H
#define QPOSITIONBOX_H

#include <QLineEdit>

class QPositionBox : public QLineEdit
{
	Q_OBJECT
	Q_PROPERTY(unsigned int positionValue READ positionValue WRITE setPositionValue)
public:
	QPositionBox(QWidget *parent);
	~QPositionBox();
	unsigned int positionValue() const;
Q_SIGNALS:
	void positionValueChanged(unsigned int);
private:
	unsigned int m_uPositionValue;
public Q_SLOTS:
	void setPositionValue(unsigned int uPositionValue);
};

#endif // QPOSITIONBOX_H
