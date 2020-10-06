#include "qindexcombobox.h"
#include <qdebug.h>

QIndexComboBox::QIndexComboBox(QWidget *parent)
	: QComboBox(parent)
{
}


void QIndexComboBox::Initialize(std::vector<std::shared_ptr<CSQLData>> *pVector,
	int nSoc,int nDes,TYPEDEFINE eDesType)
{
	int nValue=0;
	QString strText;
	double dValue=0.0;
	wchar_t szBuffer[256];
	std::vector<std::shared_ptr<CSQLData>>::iterator nit;
	if(pVector!=nullptr)
	{
		addItem(QString(""),QVariant(0));
		for(nit=pVector->begin();nit!=pVector->end();nit++)
		{
			switch(eDesType)
			{
			case TYPE_INTEGER:
				nit->get()->GetData(nDes,&nValue);
				strText=QString::number(nValue);
				break;
			case TYPE_TEXT:
				nit->get()->GetData(nDes,szBuffer);
				strText=QString::fromStdWString(szBuffer);
				break;
			case TYPE_DOUBLE:
				nit->get()->GetData(nDes,&dValue);
				strText=QString::number(dValue,'f',6);
				break;
			}
			addItem(strText,QVariant(nit->get()->GetIndex()));
		}
		connect(this,SIGNAL(currentIndexChanged(int)),this,SLOT(currentIndexChangedSlot(int)));
	}
}

QIndexComboBox::~QIndexComboBox()
{
}

void QIndexComboBox::setDataIndex(int nIndex)
{
	int nCurIndex=findData(nIndex);
	if(nCurIndex!=-1)
	{
		m_nDataIndex=nIndex;
		setCurrentIndex(nCurIndex);
	}
	else
		setCurrentIndex(0);
}

int QIndexComboBox::dataIndex() const
{
	return m_nDataIndex;
}

void QIndexComboBox::currentIndexChangedSlot(int index)
{
	QVariant value=itemData(index);
	m_nDataIndex=value.toInt();
	emit dataIndexChanged(m_nDataIndex);
}