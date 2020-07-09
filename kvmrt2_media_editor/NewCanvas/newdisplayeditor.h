#pragma once

#include <QDialog>
#include "ui_newdisplayeditor.h"
#include "tableViewHelper.h"
#include "qgleslcdcanvas.h"

class QGridLayout;
class QDataWidgetMapper;
class QTimeEvent;
class QTableView;
class QPushButton;
class QLabel;
class QLineEdit;
class QScrollArea;
class QComboBox;

class NewDisplayEditor : public QDialog
{
	Q_OBJECT

public:
	NewDisplayEditor(int nRow, int nWidth, int nHeight, int nDuration, QWidget *parent = Q_NULLPTR);
	~NewDisplayEditor();

	void resizeEvent(QResizeEvent *);
	void initTableView();
	void initWidgetMapper(int nRow);

protected slots:
	void acceptedChanges();

private:
	QDataWidgetMapper * m_pDataMapper;
	QGLESLCDCanvas *m_canvas;
	QTimeEvent *m_timeEvent;
	QSize m_ScreenSize;
	QScrollArea *scrollAreaView;
	QScrollArea *scrollAreaTime;
	QGridLayout *m_loMain;
	QTableView *m_tblItemList;
	QPushButton *m_btnAccept;
	QLabel *m_labelCoordXY;
	QLineEdit *m_editTitle;
	QLineEdit *m_editWidth;
	QLineEdit *m_editHeight;
	QLineEdit *m_editDuration;
	QComboBox *m_comboDisplayType;

private:
	Ui::NewDisplayEditor ui;
};
