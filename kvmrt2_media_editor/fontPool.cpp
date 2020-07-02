#include "fontPool.h"
#include "DataManage.h"
#include "dataModel.h"
#include <shlwapi.h>
#include <QtGui>
#include "ini.h"
#include "stringscaler.h"
#include "DefineTables.h"
#include <qdebug.h>
#include "DefineMode.h"

#pragma comment(lib,"shlwapi")


struct findFontFool : public std::unary_function<std::shared_ptr<CSQLData>,bool>
{
	findFontFool(const wchar_t *pszString)
	{
		wcscpy(szFaceName,pszString);
	}
	bool operator ()(std::shared_ptr<CSQLData> pSI)
	{
		FontPool *pFontPool=(FontPool*)pSI.get();
		return !wcscmp(pFontPool->szFontFace,szFaceName);
	}
private:
	wchar_t szFaceName[128];

};

fontPool::fontPool(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	CALL_INIT_FUNCTION(FontPool);

	connect(ui.btnAddFont, SIGNAL(clicked(bool)), this, SLOT(addFontPool(bool)));
	connect(ui.btnDelFont, SIGNAL(clicked()), this, SLOT(deleteFontPool()));
	connect(ui.btnClose, SIGNAL(clicked()), this, SLOT(close()));

	if (RELEASE_MODE == true)
	{
		SET_HIDE_TABLE_COLUMN(FontPool, 0);
		SET_HIDE_TABLE_COLUMN(FontPool, 1);
		SET_HIDE_TABLE_COLUMN(FontPool, 2);
		SET_HIDE_TABLE_COLUMN(FontPool, 5);
	}
}

fontPool::~fontPool()
{
}

IMPLEMENT_INIT_FUNCTION_FOR_CLASS(fontPool,FontPool)
{
	auto *pDM = CDataManage::GetInstance();
	SET_MODEL_FOR_TABLE_VIEW(FontPool,pDM)
	INSTALL_EVENT_FILTER(FontPool)

	SET_SELECTION_BEHAVIOR(FontPool,QAbstractItemView::SelectRows)	
	SET_SELECTION_MODE(FontPool,QAbstractItemView::SingleSelection)

	SET_DRAG_AND_DROP_ENABLED(FontPool);
	SET_EDIT_TRIGGERS(FontPool,QAbstractItemView::NoEditTriggers)


	QHeaderView *header=GET_TABLE(FontPool)->horizontalHeader();
	header->resizeSections(QHeaderView::ResizeToContents);

	return false;
}

void fontPool::addFontPool(bool bInsert)
{
	int nRow;
	auto *pDM = CDataManage::GetInstance();
	auto *pTM=CTableManage::GetInstance();
	std::vector<std::shared_ptr<CSQLData>>::iterator nit;
	std::shared_ptr<dataModel> pVFM=pDM->GET_MODEL_CLASS(FontPool);
	QModelIndex index=GET_TABLE(FontPool)->currentIndex();
	if(index.isValid())
	{
		nRow=index.row();
	}
	else
	{
		nRow=pVFM->rowCount();
	}

	if(!bInsert)
		nRow=pVFM->rowCount();

	QFileInfo fileInfo;
	QString fileName=pDM->fontPath();
	QStringList filePaths = QFileDialog::getOpenFileNames(this, QString::fromStdWString(L"Find font files"),
		pDM->fontPath(),tr("Font File (*.ttf *.TTF *.ttc *.TTC)"));
	if(filePaths.size())
	{
		while(filePaths.size())
		{
			QString filePath=filePaths.takeFirst();
			QString strSoc,strDes;
			strSoc=filePath;
			fileInfo.setFile(filePath);
			fileName=fileInfo.fileName();

			CFontScaler *pSS=CFontScaler::GetInstance();
			int nCount=pSS->GetNumFaces(filePath.toStdString().c_str());
			for(int i=0;i<nCount;i++)
			{
				char chFamily[128];
				char chStyle[128];
				
				pSS->GetFontString(filePath.toStdString().c_str(),i,chFamily,chStyle);
				QString strFace=QString("%1 %2").arg(chFamily).arg(chStyle);
				nit=find_if(pTM->m_vFontPool.begin(),pTM->m_vFontPool.end(),findFontFool(strFace.toStdWString().c_str()));
				if(nit==pTM->m_vFontPool.end())
				{
					pVFM->insertRows(nRow,1);
					index=pVFM->index(nRow,0);
					pVFM->setData(index.sibling(index.row(),2),i,Qt::EditRole);
					pVFM->setData(index.sibling(index.row(),3),fileName,Qt::EditRole);
					pVFM->setData(index.sibling(index.row(),4),strFace,Qt::EditRole);
				}
			}
			strDes=pDM->fontPath()+'/'+fileName;
			QString strDesTmp=QDir::toNativeSeparators(strDes);
			bool bRet=QFile::copy(strSoc,strDesTmp);
			GET_TABLE(FontPool)->setCurrentIndex(index);
		}
	}
}


void fontPool::deleteFontPool()
{
	int nRow;
	auto *pDM = CDataManage::GetInstance();
	std::shared_ptr<dataModel> pVFM=pDM->GET_MODEL_CLASS(FontPool);
	QModelIndex index=GET_TABLE(FontPool)->currentIndex();
	if(index.isValid())
	{
		int nRet=QMessageBox::warning(this,QString::fromStdWString(APPLICATION_NAME),QString::fromStdWString(ARE_YOU_SURE),QMessageBox::Yes|QMessageBox::No);
		if(nRet==QMessageBox::Yes)
		{
			nRow=index.row();
			pVFM->removeRows(nRow,1);
		}
	}
}

bool fontPool::eventFilter(QObject *object, QEvent *event)
{
	auto *pDM = CDataManage::GetInstance();
	QModelIndex index;
	if(event->type()==QEvent::KeyPress)
	{
		QKeyEvent *keyEvent=static_cast<QKeyEvent*>(event);
		qDebug() << Q_FUNC_INFO << keyEvent->key();
		if(keyEvent->key()==Qt::Key_Delete)
		{
			if(object==GET_TABLE(FontPool))
			{	
				deleteFontPool();
			}
			return true;
		}
		else if(keyEvent->key()==Qt::Key_F9)
		{
			if(object==GET_TABLE(FontPool))
			{	
				addFontPool(false);
			}
			return true;
		}
		else if(keyEvent->key()==Qt::Key_Insert)
		{
			if(object==GET_TABLE(FontPool))
			{	
				addFontPool(true);
			}
			return true;
		}
	}
	return false;
}