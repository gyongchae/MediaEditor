#include "qintCheckbox.h"
#include <qdebug.h>

QIntCheckBox::QIntCheckBox(QWidget *parent)
	: QCheckBox(parent),m_uCheckedValue(0)
{
	connect(this,SIGNAL(clicked(bool)),this,SLOT(checkedValueAccepted(bool)));
}

QIntCheckBox::~QIntCheckBox()
{
}

unsigned int QIntCheckBox::checkedValue() const
{
	return m_uCheckedValue;
}

void QIntCheckBox::setCheckedValue(unsigned int uCheckedValue)
{
	m_uCheckedValue=uCheckedValue;
	setChecked(uCheckedValue?true:false);
}


void QIntCheckBox::checkedValueAccepted(bool checked)
{
	m_uCheckedValue=checked?1:0;
	emit checkedValueChanged(m_uCheckedValue);
}