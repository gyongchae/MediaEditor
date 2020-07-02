#ifndef QCOLORPICKERPUSHBUTTON_H
#define QCOLORPICKERPUSHBUTTON_H

#include <QPushButton>

class QColorPickerPushButton : public QPushButton
{
	Q_OBJECT
	Q_PROPERTY(unsigned int colorValue READ colorValue WRITE setColorValue NOTIFY colorValueChanged)
public:

public:
	QColorPickerPushButton(QWidget *parent);
	~QColorPickerPushButton();
	unsigned int colorValue() const;
	
Q_SIGNALS:
	void colorValueChanged(unsigned int);
private:
	unsigned int m_uColorValue;
public Q_SLOTS:
	void setColorValue(unsigned int uValue);
private slots:
	void clickedToAcceptChangedColor();
};

#endif // QCOLORPICKERPUSHBUTTON_H
