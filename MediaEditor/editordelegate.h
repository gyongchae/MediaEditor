#ifndef editorDelegate_H
#define editorDelegate_H

#include <QSqlRelationalDelegate>
#include <QObject>
#include <QtSql>
#include <QtGui>

class editorDelegate : public QSqlRelationalDelegate
{
	Q_OBJECT

public:
	editorDelegate(QObject *parent);
	~editorDelegate();
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	QWidget* createEditor(QWidget *aParent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
	void setSpeakerSettings(bool bSpk);
private:
	bool bSpeakerSettings;
	int m_nIntExt;
private slots:		
	void commitAndCloseEditor();
	
};

#endif // editorDelegate_H
