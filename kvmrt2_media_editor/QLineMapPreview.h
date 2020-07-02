#pragma once

#include <QDialog>
#include "ui_QLineMapPreview.h"

class QGridLayout;
class QGLESLineMapPreview;
class QTimeEvent;
class QTableView;
class QPushButton;
class QLabel;


class QLineMapPreview : public QDialog
{
	Q_OBJECT

public:
	QLineMapPreview(QWidget *parent = Q_NULLPTR);
	~QLineMapPreview();
public:
	void resizeEvent(QResizeEvent *);
	void initTableView();
private:
	QGridLayout * m_layout;
	QGLESLineMapPreview *m_canvas;
	QTimeEvent *m_timeEvent;
	QPushButton *m_btnAccept;
	QPushButton *m_btnEditMode;
	QSize m_ScreenSize;
	QLabel *m_lbLocation;
	int m_nSelectedIndexRow;
protected slots:
	void acceptedChanges();
	void setTrainNumber();
	void setCurProgress(int nProg);
	void updateEventLists(const QModelIndex &, const QModelIndex &);
private:
	Ui::QLineMapPreview ui;
	wchar_t m_szTrainNum[16];
private:
	int m_nStopPtnIdx;
	int m_nProgress;
	int m_nLineMapIdx;
	int m_nRoutesIdx;
	int m_nDistIdx;

	void initStopPtnRoutes();
};
