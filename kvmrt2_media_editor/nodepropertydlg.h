#pragma once

#include <QDialog>
#include "ui_nodepropertydlg.h"

class QDataWidgetMapper;
class QIndexComboBox;

struct tagMappingDBColumn
{
	int offsetX;
	int offsetY;
	int pivot;
	int angle; // only for node
	int imgRefType;
	int imgIndex;
	int useDefaultSpotImage; // only for spot, 0: no, 1: yes
};

class NodePropertyDlg : public QDialog
{
	Q_OBJECT

public:
	enum {Pa = 0, Ta = 1, Re = 2}; // passed, target, remain array index
	enum class propertytype {NODE, SPOT};
	NodePropertyDlg(propertytype type, int row, QString title = "Node Property", QWidget *parent = Q_NULLPTR);
	~NodePropertyDlg();

	void initUI(); // initControls()
	void initMappingColumn(propertytype type);
	void initWidgetMapper(int row);
	void initDisplayReferType(); // initItemType()
	void setItemType(int index, int column, QIndexComboBox * comboImgListPool, QIndexComboBox * comboDisplayPool);

private slots:
	void acceptedChanges();
	void rejectedChanges();
	void typeChanged(int index);
	void copyPassedDataToAll();

private:
	Ui::NodePropertyDlg ui;
	propertytype m_propType;
	QString m_title;
	
	// 
private:
	tagMappingDBColumn m_tDBColumn[3]{ 0 };
	QDataWidgetMapper *m_pMapper{ 0 };
	int m_row{ -1 };
	int m_stationIndex{ -1 };
};

// node column
// spot column
// member 변수로 저장하여 사용