#ifndef LEDINDICATORPOOL_H
#define LEDINDICATORPOOL_H

#include <QDialog>
#include "ui_ledindicatorpool.h"
#include <map>
#include <memory>

class dataModel;

class LEDIndicatorPool : public QDialog
{
	Q_OBJECT

public:
	LEDIndicatorPool(QWidget *parent = 0);
	~LEDIndicatorPool();


	
	void initETNDTable();
	void initEDDTable();
	
	bool initEDDIndexTable();
	bool initEDDIndexListTable();


	void addETND(bool bInsert);
	void deleteETND();
	
	void addEDD(bool bInsert);
	void deleteEDD();

public:
	bool eventFilter(QObject *object, QEvent *event);
	std::map<QTableView*,std::shared_ptr<dataModel>> m_mEventTable;

public:
	void addRowToTable(bool bInsert,QTableView *pView,dataModel *pModel);
	void deleteRowFromTable(QTableView *pView,dataModel *pModel);
private slots:
	void updateEDDIndexList();
	void doubleClickedETND(const QModelIndex& index);
	void doubleClickedEDD(const QModelIndex& index);



private:
	Ui::LEDIndicatorPool ui;
};

#endif // LEDINDICATORPOOL_H
