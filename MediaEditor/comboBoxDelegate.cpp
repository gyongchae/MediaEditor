#include "comboBoxDelegate.h"
#include <qcombobox.h>

comboBoxDelegate::comboBoxDelegate(QObject *parent,std::map<int,std::wstring> *pMap)
	: QSqlRelationalDelegate(parent),m_pindexString(pMap)
{
	
}

comboBoxDelegate::~comboBoxDelegate()
{

}


void comboBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	int nValueExt;
	QString strText;
	unsigned int nValue=index.model()->data(index,Qt::DisplayRole).toUInt();
	std::map<int,std::wstring>::iterator nit;
	QStyleOptionViewItem myOption;
	if(m_pindexString!=nullptr)
	{
		nit=m_pindexString->find(nValue);
		if(nit!=m_pindexString->end())
		{
			myOption=option;
			strText=QString::fromStdWString(nit->second);
			myOption.displayAlignment=Qt::AlignCenter|Qt::AlignVCenter;
			drawDisplay(painter,myOption,myOption.rect,strText);
			drawFocus(painter,myOption,myOption.rect);
		}
	}
}
QWidget* comboBoxDelegate::createEditor(QWidget *aParent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QComboBox *editor;
	editor=new QComboBox(aParent);
	std::map<int,std::wstring>::iterator nit;
	if(m_pindexString!=nullptr)
	{
		for(nit=m_pindexString->begin();nit!=m_pindexString->end();nit++)
		{
			editor->addItem(QString::fromStdWString(nit->second),QVariant(nit->first));
		}
	}
	connect(editor,SIGNAL(currentIndexChanged(int)),this,SLOT(commitAndCloseEditor()));
	return editor;
}

void comboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QComboBox *comboBox=qobject_cast<QComboBox*>(editor);
	int nCurIndex=comboBox->findData(index.data());
	if(nCurIndex!=-1)
		comboBox->setCurrentIndex(nCurIndex);
	
}
void comboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	QComboBox *comboBox;
	unsigned int  nValue,nCurValue;
	//nValue = index.model()->data(index, Qt::DisplayRole).toUInt();
	nValue=index.model()->data(index).toInt();
	comboBox=qobject_cast<QComboBox*>(editor);
	nValue = comboBox->currentData().toInt();
	//nValue=comboBox->currentIndex();
	model->setData(index,nValue);
		
}

void comboBoxDelegate::commitAndCloseEditor()
{
	QComboBox *comboBox=qobject_cast<QComboBox*>(sender());
	emit commitData(comboBox);
	emit closeEditor(comboBox);
}