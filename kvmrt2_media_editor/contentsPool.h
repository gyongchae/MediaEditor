#ifndef CONTENTSPOOL_H
#define CONTENTSPOOL_H

#include <QDialog>
#include "ui_contentsPool.h"
#include <QfutureWatcher>
#include "TableViewHelper.h"

class ContentsPool : public QDialog
{
	Q_OBJECT

public:
	ContentsPool(QWidget *parent = 0);
	~ContentsPool();
public:
	bool eventFilter(QObject *object, QEvent *event);
	
	DECLARE_INIT_FUNCTION_FOR_CLASS(AudioFilePool);
	DECLARE_INIT_FUNCTION_FOR_CLASS(VideoFilePool);

protected:
	void closeEvent(QCloseEvent *event);

private slots:
	void addAudioFilePool(bool bInsert);
	void deleteAudioFilePool();

	void addVideoFilePool(bool bInsert);
	void deleteVideoFilePool();
	

private:
	Ui::Dialog ui;
};

#endif // CREATEUPDATE_H
