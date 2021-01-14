#include "SQLDelegate.h"

SQLDelegate::SQLDelegate(QObject *parent, std::vector<std::shared_ptr<CSQLData>> *pvSQL, int nSocCol, int nDesCol, TYPEDEFINE eDesType, bool bCreated)
	: QItemDelegate(parent), m_pvSQL(nullptr), m_eDesType(eDesType)
	, m_nDesCol(nDesCol), m_nSocCol(nSocCol), m_bCreated(bCreated)
{
	if (pvSQL)
		m_pvSQL = pvSQL;

	installEventFilter(this);
}

SQLDelegate::SQLDelegate(delegatetype type, QObject * parent, std::vector<std::shared_ptr<CSQLData>>* pvSQL, int nSocCol, int nDesCol, TYPEDEFINE eDesType, bool bCreated)
	: QItemDelegate(parent), m_pvSQL(nullptr), m_eDesType(eDesType)
	, m_nDesCol(nDesCol), m_nSocCol(nSocCol), m_bCreated(bCreated)
{
	if (pvSQL)
		m_pvSQL = pvSQL;

	m_type = type;

	installEventFilter(this);
}

SQLDelegate::~SQLDelegate()
{
}

void SQLDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QString strText;
	int nRetType;
	double dValue;
	wchar_t szBuffer[128];
	int nValue;
	int nStnCode = index.model()->data(index, Qt::DisplayRole).toInt();
	std::vector<std::shared_ptr<CSQLData>>::iterator nit;
	QStyleOptionViewItem myOption;
	if (m_pvSQL != nullptr)
	{
		void *pValue;
		nit = find_if(m_pvSQL->begin(), m_pvSQL->end(), findSQLData(nStnCode));
		if (nit != m_pvSQL->end())
		{
			switch (m_eDesType)
			{
			case TYPE_INTEGER:
				nit->get()->GetData(m_nDesCol, &nValue);
				strText = QString::number(nValue);
				break;
			case TYPE_TEXT:
				nit->get()->GetData(m_nDesCol, szBuffer);
				strText = QString::fromStdWString(szBuffer);

				break;
			case TYPE_DOUBLE:
				nit->get()->GetData(m_nDesCol, &dValue);
				strText = QString::number(dValue, 'f', 6);
				break;
			}
		}
		else
		{
			strText = QString(" ");
		}
		myOption = option;
		myOption.displayAlignment = Qt::AlignCenter | Qt::AlignVCenter;
		drawDisplay(painter, myOption, myOption.rect, strText);
		drawFocus(painter, myOption, myOption.rect);
	}
}


QWidget* SQLDelegate::createEditor(QWidget *aParent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	if (!m_bCreated)
	{
		int nValue = 0;
		QComboBox *editor;
		QString strText;
		double dValue = 0.0;
		wchar_t szBuffer[256];
		editor = new QComboBox(aParent);
		std::vector<std::shared_ptr<CSQLData>>::iterator nit;

		if (m_pvSQL != nullptr)
		{
			editor->addItem(QString(""), QVariant(0));
			for (nit = m_pvSQL->begin(); nit != m_pvSQL->end(); nit++)
			{
				switch (m_eDesType)
				{
				case TYPE_INTEGER:
					nit->get()->GetData(m_nDesCol, &nValue);
					strText = QString::number(nValue);
					break;
				case TYPE_TEXT:
					nit->get()->GetData(m_nDesCol, szBuffer);
					strText = QString::fromStdWString(szBuffer);
					if (m_type == SQLDelegate::BITMAP_IMAGE_TYPE)
					{
						int w = -1;
						int h = -1;
						nit->get()->GetData(3, &w);
						nit->get()->GetData(4, &h);
						strText += QString(" (%1,%2)").arg(QString::number(w)).arg(QString::number(h));
					}
					else if (m_type == SQLDelegate::TEXT_IMAGE_TYPE)
					{
						wchar_t szDesc[256];
						nit->get()->GetData(15, szDesc);
						strText += QString(" (%1)").arg(QString::fromStdWString(szDesc));
					}
					break;
				case TYPE_DOUBLE:
					nit->get()->GetData(m_nDesCol, &dValue);
					strText = QString::number(dValue, 'f', 6);
					break;
				}
				editor->addItem(strText, QVariant(nit->get()->GetIndex()));
			}
		}
		connect(editor, SIGNAL(currentIndexChanged(int)), this, SLOT(commitAndCloseEditor()));
		return editor;
	}
	else
		return QItemDelegate::createEditor(aParent, option, index);
}

void SQLDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	wchar_t szBuffer[64];
	int nSQLIndex = index.model()->data(index, Qt::EditRole).toInt();

	QComboBox *comboBox = qobject_cast<QComboBox*>(editor);
	if (m_pvSQL)
	{
		std::vector<std::shared_ptr<CSQLData>>::iterator nit;
		nit = find_if(m_pvSQL->begin(), m_pvSQL->end(), findSQLData(nSQLIndex));
		if (nit != m_pvSQL->end())
		{
			int nIndex;
			nIndex = comboBox->findData(nSQLIndex);
			comboBox->setCurrentIndex(nIndex);
		}
	}
}

void SQLDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	QComboBox *comboBox;

	unsigned int  nValue;
	nValue = index.model()->data(index, Qt::DisplayRole).toUInt();
	comboBox = qobject_cast<QComboBox*>(editor);
	nValue = comboBox->currentIndex();
	nValue = comboBox->itemData(nValue).toInt();
	model->setData(index, nValue);

}

void SQLDelegate::commitAndCloseEditor()
{
	QComboBox *comboBox = qobject_cast<QComboBox*>(sender());
	emit commitData(comboBox);
	emit closeEditor(comboBox);
}
