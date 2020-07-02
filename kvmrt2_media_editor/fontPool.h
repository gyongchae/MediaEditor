#ifndef FONTPOOL_H
#define FONTPOOL_H

#include <QDialog>
#include "ui_fontPool.h"
#include "TableViewHelper.h"

//#pragma comment(lib,"libStringScaler_d.lib")

class fontPool : public QDialog
{
	Q_OBJECT

public:
	fontPool(QWidget *parent = 0);
	~fontPool();

public:
	bool eventFilter(QObject *object, QEvent *event);

private:
	Ui::fontPool ui;

	DECLARE_INIT_FUNCTION_FOR_CLASS(FontPool);

public slots:
	void addFontPool(bool bInsert);
	void deleteFontPool();
	
};

#endif // FONTPOOL_H
