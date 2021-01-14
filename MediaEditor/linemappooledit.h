#ifndef LINEMAPPOOLEDIT_H
#define LINEMAPPOOLEDIT_H

#include <QDialog>
#include "ui_linemappooledit.h"
#include "TableViewHelper.h"


class LineMapPoolEdit : public QDialog
{
	Q_OBJECT

public:
	LineMapPoolEdit(QWidget *parent = 0);
	~LineMapPoolEdit();
public:
	bool eventFilter(QObject *object, QEvent *event);
private:
	Ui::LineMapPoolEdit ui;
	void deleteLineMapPool();
	void addLineMapPool(bool bInsert);
	DECLARE_INIT_FUNCTION_FOR_CLASS(LineMapPool);
private slots:
	void insertmodifyLineMapPool(const QModelIndex &index);
	void deleteAllMap();
};

#endif // LINEMAPPOOLEDIT_H
