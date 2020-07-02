#ifndef VECDELEGATE_H
#define VECDELEGATE_H

#include <QItemDelegate>
#include <QObject>
#include <QtSql>
#include <QtGui>
#include "DataManage.h"
#include "SQLData.h"

class VECDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	VECDelegate(QObject *parent,std::vector<std::shared_ptr<CSQLData>> *pvSQL,int nSocCol,int nDesCol,TYPEDEFINE eDesType,bool bCreated=false);
	~VECDelegate();
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

	std::vector<std::shared_ptr<CSQLData>> *m_pvSQL;
	int m_nDesCol;
	int m_nSocCol;
	int m_eDesType;
	bool m_bCreated;
private slots:		
	void commitAndCloseEditor();
	
};

#endif // VECDelegate_H
