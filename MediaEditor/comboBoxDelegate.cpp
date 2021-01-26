#include "comboBoxDelegate.h"
#include <qcombobox.h>

comboBoxDelegate::comboBoxDelegate(QObject *parent,std::map<int,std::wstring> *pMap, bool bSortByValue)
	: QSqlRelationalDelegate(parent),m_pMapIdxString(pMap)
{
	if (bSortByValue)
	{
		std::vector<std::pair<int, std::wstring>> v(m_pMapIdxString->begin(), m_pMapIdxString->end());
		std::sort(v.begin(), v.end(), compare_pair_second<std::less>());
	
		m_vSortByValue.resize(v.size());
		std::copy(v.begin(), v.end(), m_vSortByValue.begin());
	}
	else
	{
		std::vector<std::pair<int, std::wstring>> v(m_pMapIdxString->begin(), m_pMapIdxString->end());
		m_vSortByValue.resize(v.size());
		std::copy(v.begin(), v.end(), m_vSortByValue.begin());
	}
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
	/*if(m_pMapIdxString!=nullptr)
	{
		nit=m_pMapIdxString->find(nValue);
		if(nit!=m_pMapIdxString->end())
		{
			myOption=option;
			strText=QString::fromStdWString(nit->second);
			myOption.displayAlignment=Qt::AlignCenter;
			drawDisplay(painter,myOption,myOption.rect,strText);
			drawFocus(painter,myOption,myOption.rect);
		}
	}*/

	if (!m_vSortByValue.empty())
	{
		int idx = 0;
		bool found = false;
		for (int i = 0; i < m_vSortByValue.size(); i++)
		{
			if (m_vSortByValue.at(i).first == nValue)
			{
				idx = i;
				found = true;
				break;
			}
		}

		if (found)
		{
			myOption = option;
			strText = QString::fromStdWString(m_vSortByValue.at(idx).second);
			myOption.displayAlignment = Qt::AlignCenter;
			drawDisplay(painter, myOption, myOption.rect, strText);
			drawFocus(painter, myOption, myOption.rect);
		}
	}
}
QWidget* comboBoxDelegate::createEditor(QWidget *aParent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QComboBox *editor;
	editor=new QComboBox(aParent);
	//std::map<int,std::wstring>::iterator nit;

	//if(m_pMapIdxString!=nullptr)
	//{
	//	for(nit=m_pMapIdxString->begin();nit!=m_pMapIdxString->end();nit++)
	//	{
	//		editor->addItem(QString::fromStdWString(nit->second),QVariant(nit->first));
	//	}
	//}

	for (auto a : m_vSortByValue)
	{
		editor->addItem(QString::fromStdWString(a.second), QVariant(a.first));
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

