#ifndef QLINEMAPEDITOR_H
#define QLINEMAPEDITOR_H

#include <QDialog>
#include "tableViewHelper.h"
#include "ui_QLineMapEdit.h"
#include "SQLData.h"

class QButtonGroup;
class QDataWidgetMapper;

struct tagNodeProperty
{
	// node-related
	int nOffsetX[3];
	int nOffsetY[3];
	int nCenterSpot[3];
	int nRotAngle[3];
	int nType[3]; // display pool or image list pool
	int nColored[3]; // always 0 (unchecked)
	int nRelatedIndex[3];
};

struct tagSpotProperty
{
	// spot-related
	int nSOffsetX[3];
	int nSOffsetY[3];
	int nSCenterSpot[3];
	int nSUseDefault[3]; // init node image red circle
	int nSRelatedIndex[3];
	int nSType[3];
};

class QLineMapEdit : public QDialog
{
	Q_OBJECT

public:
	QLineMapEdit(int nIndexRow, QWidget *parent = Q_NULLPTR);
	~QLineMapEdit();
	void resizeEvent(QResizeEvent *);
	void initModels(int nRow);
	void initWidgets();
	void initLineMapNodeTable();
	void initMapper();
	void initApplyArrowOffset();

	DECLARE_INIT_FUNCTION_FOR_CLASS(LineMapLink);
	DECLARE_INIT_FUNCTION_FOR_CLASS(LineMapNode);
	DECLARE_INIT_FUNCTION_FOR_CLASS(DisplayItemPool);

	std::shared_ptr<CSQLData> m_pCopyLineMapNode;

protected slots:
	void colorApply();
	void arrowOffsetApply();
	void acceptedChanges();
	void copyNodeProperty();
	void pasteNodeProperty();
	void pasteSpotProperty();
	void clickedSetSpotButton(int id);

private:
	QDataWidgetMapper * m_pLineMapMapper{ 0 };
	QButtonGroup *m_editGroup{ 0 };
	QButtonGroup *m_showSpotGroup{ 0 };
	QSize m_ScreenSize{ 0, 0 };
	int m_nRow{ 0 };
	int m_nTileSize{ 0 };
	int m_nLineThick{ 0 };

	// for copy data
private:
	tagNodeProperty m_tNode{0};
	tagSpotProperty m_tSpot{0};
	int m_selectedRow{ -1 }; // no copy target

private:
	Ui::QLineMapEdit ui;
};

#endif
