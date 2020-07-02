#ifndef LEDINDICATOREDIT_H
#define LEDINDICATOREDIT_H

#include <QDialog>
#include "ui_ledindicatoredit.h"
#include <windows.h>
#include <memory>


class dataModel;
class LEDIndicator;
class QScrollArea;
class QDataWidgetMapper;

class LEDIndicatorEdit : public QDialog
{
	Q_OBJECT

public:
	LEDIndicatorEdit(const QModelIndex &index,int nWidthCol,int nHeightCol,int nPageCol,int nModeCol,int nDataCol,int nBitCol,QWidget *parent = 0);
	~LEDIndicatorEdit();

private:
	Ui::LEDIndicatorEdit ui;
public:
	void initLEDIndicator();
	void initWidget();
	void setPBColor(unsigned int nValue,QPushButton *pButton);
	LEDIndicator *m_pLEDIndicator;
	QScrollArea *m_pScrLEDIMS;

	std::shared_ptr<dataModel> m_pLEDDataModel;

	QDataWidgetMapper *m_pDataMapper;
	const QModelIndex *m_pIndex;
	void *m_pLEDBuf;
	unsigned long m_dwFrColor;
	unsigned long  m_dwBkColor;

	int m_nWidthCol;
	int m_nHeightCol;
	int m_nPageCol;
	int m_nModeCol;
	int m_nDataCol;
	int m_nBitCol;
	
private slots:
	void loadImage();
	void setImage();
	void selectMode(int id);
	void initWidgetMapper(const QModelIndex &index);
	void redrawLED();
	void updateLEDDisplay();
	void toggleFrColor();
	void toggleBkColor();
	void acceptedChanges();
	void rejectedChanges();
	void selectAreaChanged(RECT tRect);
};

#endif // LEDINDICATOREDIT_H
