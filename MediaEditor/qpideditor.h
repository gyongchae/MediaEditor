#ifndef QPIDEDITOR_H
#define QPIDEDITOR_H

#include <QDialog>
#include "QGLESCanvas.h"
#include "tableViewHelper.h"
#include "ui_qpideditor.h"

class QGridLayout;
class QGLESPIDCanvas;
class QDataWidgetMapper;
class QTimeEvent;
class QTableView;
class QPushButton;
class QLabel;
class QLineEdit;
class QScrollArea;
class QComboBox;

class QPIDEditor : public QDialog
{
	Q_OBJECT

public:
	QPIDEditor(int nRow,int nWidth,int nHeight,int nDuration,QWidget *parent = 0);
	~QPIDEditor();

	void resizeEvent(QResizeEvent *);
	void initTableView();
	void initWidgetMapper(int nRow);
	
protected slots:
	void acceptedChanges();

private:
	Ui::QPIDEditor ui;

private:
	QDataWidgetMapper * m_pDataMapper;
	QGLESPIDCanvas *m_canvas;
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
	QComboBox *m_comboDateTimeDisplay;
};

#endif // QPIDEDITOR_H
