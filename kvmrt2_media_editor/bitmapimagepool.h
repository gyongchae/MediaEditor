#ifndef BITMAPIMAGEPOOL_H
#define BITMAPIMAGEPOOL_H

#include <QDialog>
#include "ui_bitmapimagepool.h"
#include "TableViewHelper.h"

class QTextAligner;

class bitmapImagePool : public QDialog
{
	Q_OBJECT

public:
	bitmapImagePool(QWidget *parent = 0);
	~bitmapImagePool();
		
public:
	bool eventFilter(QObject *object, QEvent *event);
	//void findSplittedPng(const QString d);

private:
	Ui::bitmapImagePool ui;
	DECLARE_INIT_FUNCTION_FOR_CLASS(BitmapImagePool);
	QTextAligner* m_pSFMLView;

private slots:
	void addBitmapImagePool(bool bInsert);
	void deleteBitmapImagePool();
	void updateBitmapImage(const QModelIndex & current, const QModelIndex & previous);
	void changeBackgroundColor();
};

#endif // BITMAPIMAGEPOOL_H
