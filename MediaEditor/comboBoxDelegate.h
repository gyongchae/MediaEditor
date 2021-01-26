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
	comboBoxDelegate(QObject *parent,std::map<int,std::wstring> *pMap, bool bSortByValue=false);
	~comboBoxDelegate();
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	QWidget* createEditor(QWidget *aParent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
	void setSpeakerSettings(bool bSpk);
	std::map<int,std::wstring> *m_pMapIdxString;

	std::vector<std::pair<int, std::wstring>> m_vSortByValue;

private slots:		
	void commitAndCloseEditor();
	
public:
	// https://juggernaut.tistory.com/entry/STL-map-%EA%B0%92%EC%9C%BC%EB%A1%9C-%EC%A0%95%EB%A0%ACsort-by-value
	template<template <typename> class P = std::less>
	struct compare_pair_second
	{
		template<class T1, class T2> bool operator()(const std::pair<T1, T2>&left,
			const std::pair<T1, T2>&right)
		{
			return P<T2>()(left.second, right.second);
		}
	};
};

#endif // comboBoxDelegate_H
