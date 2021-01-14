#include "VECDelegate.h"
#include <QDebug>


VECDelegate::VECDelegate(QObject *parent,std::vector<std::shared_ptr<CSQLData>> *pvSQL,int nSocCol,int nDesCol,TYPEDEFINE eDesType,bool bCreated)
: QItemDelegate(parent),m_pvSQL(NULL),m_eDesType(eDesType),m_nDesCol(nDesCol),m_nSocCol(nSocCol),m_bCreated(bCreated)
{
	if(pvSQL)
		m_pvSQL=pvSQL;

	installEventFilter(this);

}

VECDelegate::~VECDelegate()
{
}


void VECDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QString strText;
	int nRetType;
	double dValue;
	wchar_t szBuffer[128];
	int nValue;
	int nStnCode=index.model()->data(index,Qt::DisplayRole).toInt();
	std::vector<std::shared_ptr<CSQLData>>::iterator nit;
	QStyleOptionViewItem myOption;
	if(m_pvSQL!=NULL)
	{
		void *pValue;
		nit=find_if(m_pvSQL->begin(),m_pvSQL->end(),findSQLData(nStnCode));
		if(nit!=m_pvSQL->end())
		{
			switch(m_eDesType)
			{
			case TYPE_INTEGER:
				nit->get()->GetData(m_nDesCol,&nValue);
				strText=QString::number(nValue);
				break;
			case TYPE_TEXT:
				nit->get()->GetData(m_nDesCol,szBuffer);
				strText=QString::fromStdWString(szBuffer);
				break;
			case TYPE_DOUBLE:
				nit->get()->GetData(m_nDesCol,&dValue);
				strText=QString::number(dValue,'f',6);
				break;
			}
		}
		else
		{
			strText=QString(" ");
		}
		myOption=option;
		myOption.displayAlignment=Qt::AlignCenter|Qt::AlignVCenter;
		drawDisplay(painter,myOption,myOption.rect,strText);
		drawFocus(painter,myOption,myOption.rect);
	}
}


void VECDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	wchar_t szBuffer[64];
	int nSQLIndex=index.model()->data(index,Qt::EditRole).toInt();
	QComboBox *comboBox=qobject_cast<QComboBox*>(editor);
	if(m_pvSQL)
	{
		std::vector<std::shared_ptr<CSQLData>>::iterator nit;
		nit=find_if(m_pvSQL->begin(),m_pvSQL->end(),findSQLData(nSQLIndex));
		if(nit!=m_pvSQL->end())
		{
			int nIndex;
			nIndex=comboBox->findData(nSQLIndex);
			comboBox->setCurrentIndex(nIndex);
		}
	}
}
void VECDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	QComboBox *comboBox;
	unsigned int  nValue,nCurValue;
	nValue=index.model()->data(index,Qt::DisplayRole).toUInt();
	comboBox=qobject_cast<QComboBox*>(editor);
	nValue=comboBox->currentIndex();
	nValue=comboBox->itemData(nValue).toInt();
	model->setData(index,nValue);

}

void VECDelegate::commitAndCloseEditor()
{
	QComboBox *comboBox=qobject_cast<QComboBox*>(sender());
	emit commitData(comboBox);
	emit closeEditor(comboBox);
}
