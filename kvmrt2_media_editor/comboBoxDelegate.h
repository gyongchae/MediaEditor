#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include <QObject>
#include <QtSql>
#include <QtGui>
#include <qsqlrelationaldelegate.h>

class QStyleOptionViewItem;

class comboBoxDelegate : public QSqlRelationalDelegate
{
	Q_OBJECT

public:
	comboBoxDelegate(QObject *parent,std::map<int,std::wstring> *pMap);
	~comboBoxDelegate();
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	QWidget* createEditor(QWidget *aParent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
	void setSpeakerSettings(bool bSpk);
	std::map<int,std::wstring> *m_pindexString;
private slots:		
	void commitAndCloseEditor();
	
};

#endif // comboBoxDelegate_H
