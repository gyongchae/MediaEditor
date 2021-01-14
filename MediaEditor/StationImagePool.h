#ifndef STATIONIMAGEPOOL_H
#define STATIONIMAGEPOOL_H

#include <QDialog>
#include "ui_stationImagePool.h"
#include "TableViewHelper.h"

//#pragma comment(lib,"libStringScaler_d.lib")

class QTextAligner;

class stationImagePool : public QDialog
{
	Q_OBJECT

public:
	stationImagePool(QWidget *parent = 0);
	~stationImagePool();

public:
	bool eventFilter(QObject *object, QEvent *event);

private:
	Ui::stationImagePool ui;	
	DECLARE_INIT_FUNCTION_FOR_CLASS(StationImagePool);
	QTextAligner* m_pSFMLView;

private slots:
	void addStationImagePool(bool bInsert);
	void deleteStationImagePool();
	void updateStationImage(const QModelIndex & current, const QModelIndex & previous);
	void updateStationImagePool(const QModelIndex & topLeft,const QModelIndex & bottomRight);
	void changeBackgroundColor();
	void deleteAllTxt();
};

#endif // FONTPOOL_H
