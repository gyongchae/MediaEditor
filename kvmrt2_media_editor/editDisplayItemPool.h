#pragma once

#include <QDialog>
#include "ui_editDisplayItemPool.h"
#include "TableViewHelper.h"

class editDisplayItemPool : public QDialog
{
	Q_OBJECT

public:
	editDisplayItemPool(QWidget *parent = Q_NULLPTR);
	~editDisplayItemPool();
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
	Ui::editDisplayItemPool ui;
};
