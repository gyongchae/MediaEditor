#pragma once

#include <QDialog>
#include "ui_newdisplaypool.h"
#include "TableViewHelper.h"

class NewDisplayPool : public QDialog
{
	Q_OBJECT

public:
	NewDisplayPool(QWidget *parent = Q_NULLPTR);
	~NewDisplayPool();

public:
	bool eventFilter(QObject *object, QEvent *event);

protected:
	void closeEvent(QCloseEvent *ev);

private:
	void deleteDisplayItemPool();
	void addDisplayItemPool(bool bInsert);

	DECLARE_INIT_FUNCTION_FOR_CLASS(DisplayItemPool);

	private slots:
	void insertmodifyDisplayItemPool(const QModelIndex &index);

private:
	Ui::NewDisplayPool ui;
};
