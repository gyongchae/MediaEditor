#include "contentsPool.h"
#include "DataManage.h"
#include "dataModel.h"
#include <shlwapi.h>
#include <QtGui>
#include <QFileDialog>
#include "ini.h"
#pragma comment(lib,"shlwapi")
#include "DefineMode.h"

ContentsPool::ContentsPool(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	
	CALL_INIT_FUNCTION(AudioFilePool);
	CALL_INIT_FUNCTION(VideoFilePool);

	connect(ui.btnAddAudio, SIGNAL(clicked(bool)), this, SLOT(addAudioFilePool(bool)));
	connect(ui.btnAddVideo, SIGNAL(clicked(bool)), this, SLOT(addVideoFilePool(bool)));

	connect(ui.btnDelAudio, SIGNAL(clicked()), this, SLOT(deleteAudioFilePool()));
	connect(ui.btnDelVideo, SIGNAL(clicked()), this, SLOT(deleteVideoFilePool()));
	
	connect(ui.btnClose, SIGNAL(clicked()), this, SLOT(close()));

	if (RELEASE_MODE == true)
	{
		SET_HIDE_TABLE_COLUMN(AudioFilePool, 0);
		SET_HIDE_TABLE_COLUMN(AudioFilePool, 1);
		SET_HIDE_TABLE_COLUMN(AudioFilePool, 2);
		SET_HIDE_TABLE_COLUMN(AudioFilePool, 6);
		SET_HIDE_TABLE_COLUMN(VideoFilePool, 0);
		SET_HIDE_TABLE_COLUMN(VideoFilePool, 1);
		SET_HIDE_TABLE_COLUMN(VideoFilePool, 2);
		SET_HIDE_TABLE_COLUMN(VideoFilePool, 6);
	}
}

ContentsPool::~ContentsPool()
{

}

void ContentsPool::closeEvent(QCloseEvent *event)
{
	event->ignore();
	reject();
}

void ContentsPool::addAudioFilePool(bool bInsert)
{
	int nRow;
	int nFileSize;
	unsigned short uCRC;
	auto *pDM = CDataManage::GetInstance();
	std::shared_ptr<dataModel> pVFM=pDM->GET_MODEL_CLASS(AudioFilePool);
	QModelIndex index=GET_TABLE(AudioFilePool)->currentIndex();
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
	QString fileName=pDM->audioPath();
	QStringList filePaths = QFileDialog::getOpenFileNames(this, QString::fromStdWString(L"Find audio files"),
		pDM->audioPath(),tr("Audio File (*.mp3 *.MP3 *.wav *.WAV)"));
	if(filePaths.size())
	{
		while(filePaths.size())
		{
			QString filePath=filePaths.takeFirst();
			QString strSoc,strDes;
			strSoc=filePath;
			fileInfo.setFile(filePath);
			fileName=fileInfo.fileName();
			pVFM->insertRows(nRow,1);
			index=pVFM->index(nRow,0);
			uCRC=CDataManage::CheckCRCFile(strSoc,&nFileSize);
			pVFM->setData(index.sibling(index.row(),3),fileName,Qt::EditRole);
			pVFM->setData(index.sibling(index.row(),4),uCRC,Qt::EditRole);
			pVFM->setData(index.sibling(index.row(),5),nFileSize,Qt::EditRole);


			strDes=pDM->audioPath()+'/'+fileName;
			bool bRet=QFile::copy(strSoc,strDes);
			GET_TABLE(AudioFilePool)->setCurrentIndex(index);
		}
	}
}

void ContentsPool::deleteAudioFilePool()
{
	int nRow;
	auto *pDM = CDataManage::GetInstance();
	std::shared_ptr<dataModel> pVFM=pDM->GET_MODEL_CLASS(AudioFilePool);
	QModelIndex index=GET_TABLE(AudioFilePool)->currentIndex();
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

bool ContentsPool::eventFilter(QObject *object, QEvent *event)
{
	auto *pDM = CDataManage::GetInstance();
	QModelIndex index;
	if(event->type()==QEvent::KeyPress)
	{
		QKeyEvent *keyEvent=static_cast<QKeyEvent*>(event);
		qDebug() << Q_FUNC_INFO << keyEvent->key();
		if(keyEvent->key()==Qt::Key_Delete)
		{
			if(object==GET_TABLE(AudioFilePool))
			{	
				deleteAudioFilePool();
			}
			if(object==GET_TABLE(VideoFilePool))
			{	
				deleteVideoFilePool();
			}
			return true;
		}
		else if(keyEvent->key()==Qt::Key_F9)
		{
			if(object==GET_TABLE(AudioFilePool))
			{	
				addAudioFilePool(false);
			}
			if(object==GET_TABLE(VideoFilePool))
			{	
				addVideoFilePool(false);
			}
			return true;
		}
		else if(keyEvent->key()==Qt::Key_Insert)
		{
			if(object==GET_TABLE(AudioFilePool))
			{	
				addAudioFilePool(true);
			}
			if(object==GET_TABLE(VideoFilePool))
			{	
				addVideoFilePool(true);
			}
			return true;
		}
	}
	return false;
}

IMPLEMENT_INIT_FUNCTION_FOR_CLASS(ContentsPool,AudioFilePool)
{
	auto *pDM = CDataManage::GetInstance();
	SET_MODEL_FOR_TABLE_VIEW(AudioFilePool,pDM)
	INSTALL_EVENT_FILTER(AudioFilePool)

	SET_SELECTION_BEHAVIOR(AudioFilePool,QAbstractItemView::SelectRows)	
	SET_SELECTION_MODE(AudioFilePool,QAbstractItemView::SingleSelection)

	SET_DRAG_AND_DROP_ENABLED(AudioFilePool);
	SET_EDIT_TRIGGERS(AudioFilePool,QAbstractItemView::NoEditTriggers)


	QHeaderView *header=GET_TABLE(AudioFilePool)->horizontalHeader();
	header->resizeSections(QHeaderView::ResizeToContents);

	return false;
}


IMPLEMENT_INIT_FUNCTION_FOR_CLASS(ContentsPool,VideoFilePool)
{
	auto *pDM = CDataManage::GetInstance();
	SET_MODEL_FOR_TABLE_VIEW(VideoFilePool,pDM)
	INSTALL_EVENT_FILTER(VideoFilePool)

	SET_SELECTION_BEHAVIOR(VideoFilePool,QAbstractItemView::SelectRows)	
	SET_SELECTION_MODE(VideoFilePool,QAbstractItemView::SingleSelection)

	SET_DRAG_AND_DROP_ENABLED(VideoFilePool);
	SET_EDIT_TRIGGERS(VideoFilePool,QAbstractItemView::NoEditTriggers)


	QHeaderView *header=GET_TABLE(VideoFilePool)->horizontalHeader();
	header->resizeSections(QHeaderView::ResizeToContents);

	return false;
}

void ContentsPool::addVideoFilePool(bool bInsert)
{
	int nRow;
	int nFileSize;
	unsigned short uCRC;
	auto *pDM = CDataManage::GetInstance();
	std::shared_ptr<dataModel> pVFM=pDM->GET_MODEL_CLASS(VideoFilePool);
	QModelIndex index=GET_TABLE(VideoFilePool)->currentIndex();
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
	QString fileName=pDM->videoPath();
	QStringList filePaths = QFileDialog::getOpenFileNames(this, QString::fromStdWString(L"Find video files"),
		pDM->videoPath(),tr("Video File (*.mp4 *.MP4 *.avi *.AVI *.mpg *.MPG)"));
	if(filePaths.size())
	{
		while(filePaths.size())
		{
			QString filePath=filePaths.takeFirst();
			QString strSoc,strDes;
			strSoc=filePath;
			fileInfo.setFile(filePath);
			fileName=fileInfo.fileName();
			pVFM->insertRows(nRow,1);
			index=pVFM->index(nRow,0);
			uCRC=CDataManage::CheckCRCFile(strSoc,&nFileSize);
			pVFM->setData(index.sibling(index.row(),3),fileName,Qt::EditRole);
			pVFM->setData(index.sibling(index.row(),4),uCRC,Qt::EditRole);
			pVFM->setData(index.sibling(index.row(),5),nFileSize,Qt::EditRole);
			strDes=pDM->videoPath()+'/'+fileName;
			bool bRet=QFile::copy(strSoc,strDes);
			GET_TABLE(VideoFilePool)->setCurrentIndex(index);
		}
	}
}


void ContentsPool::deleteVideoFilePool()
{
	int nRow;
	auto *pDM = CDataManage::GetInstance();
	std::shared_ptr<dataModel> pVFM=pDM->GET_MODEL_CLASS(VideoFilePool);
	QModelIndex index=GET_TABLE(VideoFilePool)->currentIndex();
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