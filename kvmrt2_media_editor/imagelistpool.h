#ifndef IMAGELISTPOOL_H
#define IMAGELISTPOOL_H

#include <QDialog>
#include <memory>
#include "ui_imagelistpool.h"
#include "tableViewHelper.h"

// 특정 이미지 리스트만 띄우게 구분할 순 없을까

class QTextAligner;
class dataModel;

class imageListPool : public QDialog
{
	Q_OBJECT

public:
	imageListPool(QWidget *parent = 0);
	~imageListPool();

	bool eventFilter(QObject *object, QEvent *event);
	QMap<QTableView*,std::shared_ptr<dataModel>> m_mEventTable;
	DECLARE_INIT_FUNCTION_FOR_CLASS(ImageIndexList);
	DECLARE_INIT_FUNCTION_FOR_CLASS(ImageIndex);
	void addRowToTable(bool bInsert,QTableView *pView,dataModel *pModel);
	bool deleteRowFromTable(QTableView *pView,dataModel *pModel);
	
private:
	Ui::imageListPool ui;
	QTextAligner* m_pSFMLView;

private slots:
	void itemPositionChanged(int nIndex,int x,int y);
	void updateImageIndexList(const QModelIndex & current, const QModelIndex & previous);
	void onAddImageListPool();
	void onDelImageListPool();
	void onAddImageIndex();
	void onDelImageIndex();
	void changeBackgroundColor();
};

#endif // IMAGELISTPOOL_H
