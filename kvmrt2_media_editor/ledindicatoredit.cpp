#include "ledindicatoredit.h"
#include <QScrollArea>
#include <qdebug.h>
#include <QtGui>
#include <QDataWidgetMapper>
#include "LEDIndicator.h"
#include "DataManage.h"
#include "MapManage.h"

#if QT_VERSION >= 0x050000
#include <QtWin>
#endif


LEDIndicatorEdit::LEDIndicatorEdit(const QModelIndex &index,int nWidthCol,int nHeightCol,int nPageCol,int nModeCol,int nDataCol,int nBitCol,QWidget *parent)
	: QDialog(parent),m_pDataMapper(nullptr),m_pLEDIndicator(nullptr),m_nWidthCol(nWidthCol),m_nHeightCol(nHeightCol),m_nPageCol(nPageCol),m_nModeCol(nModeCol),m_nDataCol(nDataCol),m_nBitCol(nBitCol)
{
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	ui.setupUi(this);
	initWidget();
	initWidgetMapper(index);
	initLEDIndicator();
	m_pIndex=&index;
	m_dwFrColor=0x000080FF;
	m_dwBkColor=0xFFFFFFFF;
	toggleFrColor();
	toggleBkColor();
}

LEDIndicatorEdit::~LEDIndicatorEdit()
{

}


void LEDIndicatorEdit::initLEDIndicator()
{
	if(!m_pLEDIndicator)
	{
 		m_pLEDIndicator=new LEDIndicator(ui.m_cbPagingMode->currentIndex(),4,ui.m_spPages->value(),ui.m_spUnitWidth->value(),ui.m_spUnitHeight->value(),6,this);
 		m_pScrLEDIMS=new QScrollArea;
		m_pScrLEDIMS->setBackgroundRole(QPalette::Dark);
		m_pScrLEDIMS->setWidget(m_pLEDIndicator);
		ui.m_layoutLED->removeItem(ui.horizontalLayout_2);
		ui.m_layoutLED->addWidget(m_pScrLEDIMS,1,0);
		ui.m_layoutLED->addLayout(ui.horizontalLayout_2,2,0);
		m_pLEDIndicator->setBitmap(ui.m_spPages->value(),ui.m_cbPagingMode->currentIndex(),m_pLEDBuf);
		connect(ui.m_spPages,SIGNAL(valueChanged(int)),this,SLOT(redrawLED()));
		connect(ui.m_cbPagingMode,SIGNAL(currentIndexChanged(int)),this,SLOT(redrawLED()));
		connect(ui.m_teVMIMS,SIGNAL(textChanged()),this,SLOT(updateLEDDisplay()));
		connect(ui.m_cbFontIMS,SIGNAL(currentFontChanged(const QFont &)),this,SLOT(updateLEDDisplay()));
		connect(ui.m_spFontSizeIMS,SIGNAL(valueChanged(int)),this,SLOT(updateLEDDisplay()));
		connect(ui.m_cbVAIMS,SIGNAL(currentIndexChanged(int)),this,SLOT(updateLEDDisplay()));
		connect(ui.m_cbHAIMS,SIGNAL(currentIndexChanged(int)),this,SLOT(updateLEDDisplay()));
		connect(m_pLEDIndicator,SIGNAL(selectAreaChanged(RECT)),this,SLOT(selectAreaChanged(RECT)));

	}
}

void LEDIndicatorEdit::selectAreaChanged(RECT tRect)
{
	ui.m_tlSelectArea->setText(QString("L:%1 T:%2 R:%3 B:%4").arg(tRect.left).arg(tRect.top).arg(tRect.right).arg(tRect.bottom));
}

void LEDIndicatorEdit::updateLEDDisplay()
{
	int nVAValue=ui.m_cbVAIMS->currentIndex();
	int nHAValue=ui.m_cbHAIMS->currentIndex();
	m_pLEDIndicator->setText(ui.m_teVMIMS->toPlainText().toStdWString().c_str(),ui.m_cbFontIMS->currentText().toStdWString().c_str(),ui.m_spFontSizeIMS->value(),nVAValue,nHAValue,m_dwBkColor,m_dwFrColor,(m_dwBkColor==0xFFFFFFFF)?true:false);
}

void LEDIndicatorEdit::redrawLED()
{
	m_pLEDIndicator->setBitmap(ui.m_spPages->value(),ui.m_cbPagingMode->currentIndex(),nullptr);
}

void LEDIndicatorEdit::initWidget()
{
	QButtonGroup* group = new QButtonGroup(this);
	group->addButton(ui.m_rbPreview);
	group->addButton(ui.m_rbSelectArea);
	group->addButton(ui.m_rbEdit);
	group->setId(ui.m_rbPreview,1);
	group->setId(ui.m_rbSelectArea,2);
	group->setId(ui.m_rbEdit,3);

	connect(group,SIGNAL(buttonClicked(int)),this,SLOT(selectMode(int)));
	ui.m_rbPreview->setChecked(true);	//Select the first one
	group->setExclusive(true);
	selectMode(1);	
	CMapManage *pDM=CMapManage::GetInstance();
	std::map<int,tstring>::iterator nit;
	for(nit=pDM->m_mVerticalAlign.begin();nit!=pDM->m_mVerticalAlign.end();nit++)
	{
		ui.m_cbVAIMS->addItem(QString::fromStdWString(nit->second.c_str()),nit->first);
	}
	for(nit=pDM->m_mHorizontalAlign.begin();nit!=pDM->m_mHorizontalAlign.end();nit++)
	{
		ui.m_cbHAIMS->addItem(QString::fromStdWString(nit->second.c_str()),nit->first);
	}
	for(nit=pDM->m_mDisplayMode.begin();nit!=pDM->m_mDisplayMode.end();nit++)
	{
		ui.m_cbPagingMode->addItem(QString::fromStdWString(nit->second.c_str()),nit->first);
	}

	connect(ui.m_pbClrBkGnd,SIGNAL(clicked()),this,SLOT(toggleBkColor()));
	connect(ui.m_pbClrFrGnd,SIGNAL(clicked()),this,SLOT(toggleFrColor()));

	connect(ui.m_pbSetImage,SIGNAL(clicked()),this,SLOT(setImage()));
	connect(ui.m_pbLoadBitmap,SIGNAL(clicked()),this,SLOT(loadImage()));

	connect(ui.m_pbAccept,SIGNAL(clicked()),this,SLOT(acceptedChanges()));
	connect(ui.m_pbCancel,SIGNAL(clicked()),this,SLOT(rejectedChanges()));

}

void LEDIndicatorEdit::setImage()
{
	m_pLEDIndicator->setCurrentInputedText();
}


void LEDIndicatorEdit::toggleFrColor()
{
	switch(m_dwFrColor)
	{
	case 0x00000000:
		m_dwFrColor=0x000000FF;
		ui.m_pbClrFrGnd->setText("Red");
		break;
	case 0x000000FF:
		m_dwFrColor=0x0000FFC3;
		ui.m_pbClrFrGnd->setText("Green");
		break;
	case 0x0000FFC3:
		m_dwFrColor=0x000080FF;
		ui.m_pbClrFrGnd->setText("Amber");
		break;
	case 0x000080FF:
		m_dwFrColor=0x00000000;
		ui.m_pbClrFrGnd->setText("Black");
		break;
	}
	setPBColor(m_dwFrColor,ui.m_pbClrFrGnd);
	updateLEDDisplay();
}

void LEDIndicatorEdit::toggleBkColor()
{
	switch(m_dwBkColor)
	{
	case 0x00000000:
		m_dwBkColor=0x000000FF;
		ui.m_pbClrBkGnd->setText("Red");
		break;
	case 0x000000FF:
		m_dwBkColor=0x0000FFC3;
		ui.m_pbClrBkGnd->setText("Green");
		break;
	case 0x0000FFC3:
		m_dwBkColor=0x000080FF;
		ui.m_pbClrBkGnd->setText("Amber");
		break;
	case 0x000080FF:
		m_dwBkColor=0xFFFFFFFF;
		ui.m_pbClrBkGnd->setText("Transparent");
		break;
	case 0xFFFFFFFF:
		m_dwBkColor=0x00000000;
		ui.m_pbClrBkGnd->setText("Black");
		break;
	}
	setPBColor(m_dwBkColor,ui.m_pbClrBkGnd);
	updateLEDDisplay();
}


void LEDIndicatorEdit::selectMode(int id)
{
	switch(id)
	{
	case 1:
		ui.m_spPages->setEnabled(false);
		ui.m_cbPagingMode->setEnabled(false);
		
		ui.m_teVMIMS->setEnabled(false);
		ui.m_cbHAIMS->setEnabled(false);
		ui.m_cbVAIMS->setEnabled(false);
		ui.m_cbFontIMS->setEnabled(false);
		ui.m_spFontSizeIMS->setEnabled(false);
		if(m_pLEDIndicator)
			m_pLEDIndicator->setMode(1);
	
		break;
	case 2:
		ui.m_spPages->setEnabled(true);
		ui.m_cbPagingMode->setEnabled(true);

		ui.m_teVMIMS->setEnabled(false);
		ui.m_cbHAIMS->setEnabled(false);
		ui.m_cbVAIMS->setEnabled(false);
		ui.m_cbFontIMS->setEnabled(false);
		ui.m_spFontSizeIMS->setEnabled(false);
		if(m_pLEDIndicator)
			m_pLEDIndicator->setMode(2);
		break;
	case 3:
		ui.m_spPages->setEnabled(false);
		ui.m_cbPagingMode->setEnabled(false);

		ui.m_teVMIMS->setEnabled(true);
		ui.m_cbHAIMS->setEnabled(true);
		ui.m_cbVAIMS->setEnabled(true);
		ui.m_cbFontIMS->setEnabled(true);
		ui.m_spFontSizeIMS->setEnabled(true);
		if(m_pLEDIndicator)
			m_pLEDIndicator->setMode(3);
		break;
	default:
		break;
	}
}


void LEDIndicatorEdit::initWidgetMapper(const QModelIndex &index)
{
	CDataManage *pManage=CDataManage::GetInstance();
	
	m_pDataMapper = new QDataWidgetMapper(this);
	m_pDataMapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
	m_pDataMapper->setModel((QAbstractItemModel *)index.model());
	
	ui.m_spPages->setMaximum(3);
	ui.m_spPages->setMinimum(1);

	ui.m_spUnitWidth->setMaximum(65535);
	ui.m_spUnitWidth->setMinimum(0);
	ui.m_spUnitHeight->setMaximum(65535);
	ui.m_spUnitHeight->setMinimum(0);
	ui.m_spUnitWidth->setEnabled(false);
	ui.m_spUnitHeight->setEnabled(false);

	m_pDataMapper->addMapping(ui.m_spUnitWidth,m_nWidthCol,"value");
	m_pDataMapper->addMapping(ui.m_spUnitHeight,m_nHeightCol,"value");
	m_pDataMapper->addMapping(ui.m_spPages,m_nPageCol,"value");
	m_pDataMapper->addMapping(ui.m_cbPagingMode,m_nModeCol,"currentIndex");
	m_pLEDBuf=(void*)index.sibling(index.row(),m_nDataCol).data(Qt::EditRole).toUInt();
	m_pDataMapper->setCurrentModelIndex(index);

}




void LEDIndicatorEdit::setPBColor(unsigned int nValue,QPushButton *pButton)
{
	QColor colorVal=QColor((nValue)&0x000000ff,(nValue>>8)&0x000000ff,(nValue>>16)&0x000000ff);
	QString strVal=QString("background-color: rgb(%1, %2, %3);").arg(colorVal.red()).arg(colorVal.green()).arg(colorVal.blue());
	pButton->setStyleSheet(strVal);
}


void LEDIndicatorEdit::acceptedChanges()
{
	m_pDataMapper->submit();
	int nWidth=m_pIndex->sibling(m_pIndex->row(),m_nWidthCol).data().toInt();
	int nHeight=m_pIndex->sibling(m_pIndex->row(),m_nHeightCol).data().toInt();
	int nPage=m_pIndex->sibling(m_pIndex->row(),m_nPageCol).data().toInt();
	int nMode=m_pIndex->sibling(m_pIndex->row(),m_nModeCol).data().toInt();
	int nBit=m_pIndex->sibling(m_pIndex->row(),m_nBitCol).data().toInt();

	int nDataLength=(nWidth*nHeight*nBit*nPage)/8;



	m_pDataMapper->model()->setData(m_pIndex->sibling(m_pIndex->row(),m_nDataCol-1),nDataLength);
	m_pDataMapper->model()->setData(m_pIndex->sibling(m_pIndex->row(),m_nDataCol),(unsigned int)m_pLEDIndicator->m_pBuffer);
	accept();
}

void LEDIndicatorEdit::rejectedChanges()
{
	reject();
}


void LEDIndicatorEdit::loadImage()
{
	QString filePath = QFileDialog::getOpenFileName(this, tr("Select image file"),"",tr("Images (*.bmp *.jpg)"));
	if(filePath.length())
	{
		QPixmap image(filePath);
		if (!image.isNull())
		{
#if QT_VERSION >= 0x050000
			m_pLEDIndicator->setImage(QtWin::toHBITMAP(image));
#else
			m_pLEDIndicator->setImage(image.toWinHBITMAP());
#endif
		}
	}
}