#ifndef SQLDELEGATE_H
#define SQLDELEGATE_H

#include <QItemDelegate>
#include <QObject>
#include <QtSql>
#include <QtGui>
#include "DataManage.h"
#include "SQLData.h"

class SQLDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	enum delegatetype {DEFAULT_TYPE, TEXT_IMAGE_TYPE, BITMAP_IMAGE_TYPE, AUDIO_FILE_IDX_TYPE};
	SQLDelegate(QObject *parent, std::vector<std::shared_ptr<CSQLData>> *pvSQL, int nSocCol, int nDesCol, TYPEDEFINE eDesType, bool bCreated = false);
	SQLDelegate(delegatetype type, QObject *parent,std::vector<std::shared_ptr<CSQLData>> *pvSQL,int nSocCol,int nDesCol,TYPEDEFINE eDesType,bool bCreated=false);
	~SQLDelegate();
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	QWidget* createEditor(QWidget *aParent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

	std::vector<std::shared_ptr<CSQLData>> *m_pvSQL;
	int m_nDesCol;
	int m_nSocCol;
	int m_eDesType;
	bool m_bCreated;

private:
	delegatetype m_type{ DEFAULT_TYPE };

private slots:		
	void commitAndCloseEditor();
	
};

#endif // SQLDelegate_H
