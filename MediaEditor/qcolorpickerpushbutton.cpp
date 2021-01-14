#include <qdebug.h>
#include "qcolorpickerpushbutton.h"
#include <QColorDialog>
#include <qmessagebox.h>
QColorPickerPushButton::QColorPickerPushButton(QWidget *parent)
	: QPushButton(parent),m_uColorValue(1)
{
	//setColorValue(m_uColorValue);
	connect(this,SIGNAL(clicked()),this,SLOT(clickedToAcceptChangedColor()));
}

QColorPickerPushButton::~QColorPickerPushButton()
{
}



unsigned int QColorPickerPushButton::colorValue() const
{
	return m_uColorValue;
}

void QColorPickerPushButton::setColorValue(unsigned int uValue)
{
	// button text & font color changed, jkc
	m_uColorValue = uValue;

	int r = (m_uColorValue) & 0x000000ff;
	int g = (m_uColorValue >> 8) & 0x000000ff;
	int b = (m_uColorValue >> 16) & 0x000000ff;

	// r,g,b 0,0,0 is only for video play area
	if (r == 0 && g == 0 && b == 0)
	{
		QMessageBox msgBox;
		msgBox.setText("Inform! Your colour is RGB (0,0,0).");
		msgBox.setInformativeText("Do you want to use rgb(0,0,0)? \nIf press cancel button, the colour sets to RGB (1,0,0)");
		msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Ok);
		int ret = msgBox.exec();
		switch (ret)
		{
		case QMessageBox::Ok:
			m_uColorValue = uValue;
			break;
		case QMessageBox::Cancel:
			m_uColorValue = uValue + 1;
			break;
		}
	}
	else
	{
		m_uColorValue = uValue;
	}

	QColor colorVal=QColor((m_uColorValue)&0x000000ff,(m_uColorValue >>8)&0x000000ff,(m_uColorValue >>16)&0x000000ff,(m_uColorValue >>24)&0x000000ff);

	if ((colorVal.red()   > 80 && colorVal.red()   < 150) &&
		(colorVal.green() > 80 && colorVal.green() < 150) &&
		(colorVal.blue()  > 80 && colorVal.blue()  < 150))
	{ // if gray color, text color set aqua
		QString strVal = QString("background-color: rgb(%1, %2, %3); color: rgb(%4,%5,%6)")
			.arg(colorVal.red()).arg(colorVal.green()).arg(colorVal.blue())
			.arg(0).arg(255).arg(255);
		QString strText = QString("RGBA(%1,%2,%3,%4)").arg(colorVal.red()).arg(colorVal.green()).arg(colorVal.blue()).arg(colorVal.alpha());
		setStyleSheet(strVal);
		setText(strText);
	}
	else
	{
		QString strVal = QString("background-color: rgb(%1, %2, %3); color: rgb(%4,%5,%6)").arg(colorVal.red()).arg(colorVal.green()).arg(colorVal.blue())
			.arg(255 - colorVal.red()).arg(255 - colorVal.green()).arg(colorVal.blue());
		QString strText = QString("RGBA(%1,%2,%3,%4)").arg(colorVal.red()).arg(colorVal.green()).arg(colorVal.blue()).arg(colorVal.alpha());
		setStyleSheet(strVal);
		setText(strText);
	}
}

void QColorPickerPushButton::clickedToAcceptChangedColor()
{
	 QColor color;
	 unsigned int uValue;
	 QColor colorVal=QColor((m_uColorValue)&0x000000ff,(m_uColorValue>>8)&0x000000ff,(m_uColorValue>>16)&0x000000ff,(m_uColorValue>>24)&0x000000ff);

	 color = QColorDialog::getColor(colorVal,(QWidget*)parent(), "Select Color", QColorDialog::DontUseNativeDialog|QColorDialog::ShowAlphaChannel);
	 if(color.isValid())
	 {
		uValue=((unsigned int)color.alpha()<<24)|((unsigned int)color.blue()<<16)|((unsigned int)color.green()<<8)|((unsigned int)color.red());
		setColorValue(uValue);
		emit colorValueChanged(m_uColorValue);
	 }
}
