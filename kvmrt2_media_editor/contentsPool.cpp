#include "contentsPool.h"
#include "DataManage.h"
#include "dataModel.h"
#include <shlwapi.h>
#include <QtGui>
#include <QFileDialog>
#include "ini.h"
#include "DefineMode.h"
#include <qprogressbar.h>
#include <qmessagebox.h>
#include <qmediacontent.h>

#pragma comment(lib,"shlwapi")

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

	if (OFFICIAL_RELEASE == true)
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

	// audio player init
	m_audioPlayer = new QMediaPlayer();
	m_audioPlayer->setNotifyInterval(100);

	connect(ui.btnPlayAudio, SIGNAL(clicked()), this, SLOT(onAudioPlay()));
	connect(ui.btnPauseAudio, SIGNAL(clicked()), this, SLOT(onAudioPause()));
	connect(ui.btnStopAudio, SIGNAL(clicked()), this, SLOT(onAudioStop()));
	connect(m_audioPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(onAudioPosChanged(qint64)));
	connect(m_audioPlayer, SIGNAL(currentMediaChanged(const QMediaContent&)), this, SLOT(onAudioMediaChanged(const QMediaContent&)));
	connect(m_audioPlayer, &QMediaPlayer::durationChanged, this, &ContentsPool::onDurationChanged);

	connect(ui.btnPlayVideo, SIGNAL(clicked()), this, SLOT(onVideoPlay()));
}

ContentsPool::~ContentsPool()
{

}

void ContentsPool::closeEvent(QCloseEvent *event)
{
	m_audioPlayer->stop();
	event->ignore();
	reject();
}

void ContentsPool::addAudioFilePool(bool bInsert)
{
	int nRow;
	int nFileSize;
	unsigned short uCRC;
	auto *pDM = CDataManage::GetInstance();
	std::shared_ptr<dataModel> pVFM = pDM->GET_MODEL_CLASS(AudioFilePool);
	QModelIndex index = GET_TABLE(AudioFilePool)->currentIndex();
	if (index.isValid())
	{
		nRow = index.row();
	}
	else
	{
		nRow = pVFM->rowCount();
	}

	if (!bInsert)
		nRow = pVFM->rowCount();

	QFileInfo fileInfo;
	QString fileName = pDM->audioPath();
	QStringList filePaths = QFileDialog::getOpenFileNames(this, QString::fromStdWString(L"Find audio files"),
		pDM->audioPath(), tr("Audio File (*.mp3 *.MP3 *.wav *.WAV)"));
	if (filePaths.size())
	{
		while (filePaths.size())
		{
			QString fileNameWithFullPath = filePaths.takeFirst();
			m_audioPlayer->setMedia(QUrl::fromLocalFile(fileNameWithFullPath));
			
			QString strSoc, strDes;
			strSoc = fileNameWithFullPath;
			fileInfo.setFile(fileNameWithFullPath);
			fileName = fileInfo.fileName();
			pVFM->insertRows(nRow, 1);
			index = pVFM->index(nRow, 0);
			uCRC = CDataManage::CheckCRCFile(strSoc, &nFileSize);
			pVFM->setData(index.sibling(index.row(), 3), fileName, Qt::EditRole);
			pVFM->setData(index.sibling(index.row(), 4), uCRC, Qt::EditRole);
			pVFM->setData(index.sibling(index.row(), 5), nFileSize, Qt::EditRole);
			//pVFM->setData(index.sibling(index.row(), 7), audioLen, Qt::DisplayRole);

			strDes = pDM->audioPath() + '/' + fileName;
			bool bRet = QFile::copy(strSoc, strDes);
			GET_TABLE(AudioFilePool)->setCurrentIndex(index);

			m_audioPlayer->play();
			int audioLen = m_audioPlayer->duration();

			//player->();//m_audioPlayer->stop();
			//auto *pDM = CDataManage::GetInstance();
			//QModelIndex index = GET_TABLE(AudioFilePool)->currentIndex();

		}
	}
}

void ContentsPool::deleteAudioFilePool()
{
	int nRow;
	auto *pDM = CDataManage::GetInstance();
	std::shared_ptr<dataModel> pVFM = pDM->GET_MODEL_CLASS(AudioFilePool);
	QModelIndex index = GET_TABLE(AudioFilePool)->currentIndex();
	if (index.isValid())
	{
		int nRet = QMessageBox::warning(this, QString::fromStdWString(APPLICATION_NAME), QString::fromStdWString(ARE_YOU_SURE), QMessageBox::Yes | QMessageBox::No);
		if (nRet == QMessageBox::Yes)
		{
			m_audioPlayer->stop();
			nRow = index.row();
			pVFM->removeRows(nRow, 1);
		}
	}
}

bool ContentsPool::eventFilter(QObject *object, QEvent *event)
{
	auto *pDM = CDataManage::GetInstance();
	QModelIndex index;
	if (event->type() == QEvent::KeyPress)
	{
		QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
		if (keyEvent->key() == Qt::Key_Delete)
		{
			if (object == GET_TABLE(AudioFilePool))
			{
				deleteAudioFilePool();
			}
			if (object == GET_TABLE(VideoFilePool))
			{
				deleteVideoFilePool();
			}
			return true;
		}
		else if (keyEvent->key() == Qt::Key_F9)
		{
			if (object == GET_TABLE(AudioFilePool))
			{
				addAudioFilePool(false);
			}
			if (object == GET_TABLE(VideoFilePool))
			{
				addVideoFilePool(false);
			}
			return true;
		}
		else if (keyEvent->key() == Qt::Key_Insert)
		{
			if (object == GET_TABLE(AudioFilePool))
			{
				addAudioFilePool(true);
			}
			if (object == GET_TABLE(VideoFilePool))
			{
				addVideoFilePool(true);
			}
			return true;
		}
	}
	return false;
}

IMPLEMENT_INIT_FUNCTION_FOR_CLASS(ContentsPool, AudioFilePool)
{
	auto *pDM = CDataManage::GetInstance();
	SET_MODEL_FOR_TABLE_VIEW(AudioFilePool, pDM);
	INSTALL_EVENT_FILTER(AudioFilePool);

	SET_SELECTION_BEHAVIOR(AudioFilePool, QAbstractItemView::SelectRows);
	SET_SELECTION_MODE(AudioFilePool, QAbstractItemView::SingleSelection);

	SET_DRAG_AND_DROP_ENABLED(AudioFilePool);
	SET_EDIT_TRIGGERS(AudioFilePool, QAbstractItemView::NoEditTriggers);


	QHeaderView *header = GET_TABLE(AudioFilePool)->horizontalHeader();
	header->resizeSections(QHeaderView::ResizeToContents);
	//header->setStretchLastSection(true);

	connect(GET_TABLE(AudioFilePool), &QTableView::clicked,
		[this](const QModelIndex &index)
	{
		auto *pDM = CDataManage::GetInstance();
		m_audioFilePath = pDM->audioPath() + "/" + index.sibling(index.row(), 3/*file name col*/).data().toString();
		m_audioPlayer->setMedia(QUrl::fromLocalFile(m_audioFilePath));
	});

	return false;
}


IMPLEMENT_INIT_FUNCTION_FOR_CLASS(ContentsPool, VideoFilePool)
{
	auto *pDM = CDataManage::GetInstance();
	SET_MODEL_FOR_TABLE_VIEW(VideoFilePool, pDM);
	INSTALL_EVENT_FILTER(VideoFilePool);

	SET_SELECTION_BEHAVIOR(VideoFilePool, QAbstractItemView::SelectRows);
	SET_SELECTION_MODE(VideoFilePool, QAbstractItemView::SingleSelection);

	SET_DRAG_AND_DROP_ENABLED(VideoFilePool);
	SET_EDIT_TRIGGERS(VideoFilePool, QAbstractItemView::NoEditTriggers);


	QHeaderView *header = GET_TABLE(VideoFilePool)->horizontalHeader();
	header->resizeSections(QHeaderView::ResizeToContents);

	connect(GET_TABLE(VideoFilePool), &QTableView::clicked,
		[this](const QModelIndex &index)
	{
		auto *pDM = CDataManage::GetInstance();
		m_videoFilePath = pDM->videoPath() + "/" + index.sibling(index.row(), 3/*file name col*/).data().toString();
	});

	return false;
}

void ContentsPool::addVideoFilePool(bool bInsert)
{
	int nRow = 0;
	int nFileSize = 0;
	unsigned short uCRC = 0;
	auto *pDM = CDataManage::GetInstance();
	std::shared_ptr<dataModel> pVFM = pDM->GET_MODEL_CLASS(VideoFilePool);
	QModelIndex index = GET_TABLE(VideoFilePool)->currentIndex();

	bool bAskAgain = true; // for rotation question
	int answer = -1;

	if (index.isValid())
	{
		nRow = index.row();
	}
	else
	{
		nRow = pVFM->rowCount();
	}

	if (!bInsert)
		nRow = pVFM->rowCount();

	QFileInfo fileInfo;
	QString fileName = pDM->videoPath();
	QStringList filePaths = QFileDialog::getOpenFileNames(this, QString::fromStdWString(L"Find video files"),
		pDM->videoPath(), tr("Video File (*.mp4 *.MP4 *.avi *.AVI)"));
	if (!filePaths.isEmpty())
	{
		while (filePaths.size())
		{
			setCursor(Qt::WaitCursor);
			QString filePath = filePaths.takeFirst();
			QString strSoc, strDes;
			strSoc = filePath;
			fileInfo.setFile(filePath);
			fileName = fileInfo.fileName();
			pVFM->insertRows(nRow, 1);
			index = pVFM->index(nRow, 0);
			uCRC = CDataManage::CheckCRCFile(strSoc, &nFileSize);
			pVFM->setData(index.sibling(index.row(), 3), fileName, Qt::EditRole);
			pVFM->setData(index.sibling(index.row(), 4), uCRC, Qt::EditRole);
			pVFM->setData(index.sibling(index.row(), 5), nFileSize, Qt::EditRole);
			strDes = pDM->videoPath() + '/' + fileName;
			bool bRet = QFile::copy(strSoc, strDes);
			setCursor(Qt::ArrowCursor);

			if (bAskAgain)
			{
				answer = QMessageBox::question(this, "Make rotated video", "Do you need a rotated one for PID?", QMessageBox::Yes | QMessageBox::No | QMessageBox::YesToAll | QMessageBox::NoToAll);
			}

			if (answer == QMessageBox::Yes)
			{
				if (!strDes.isEmpty())
				{
					// video rotation
					// refer: https://superuser.com/questions/578321/how-to-rotate-a-video-180-with-ffmpeg
					QProcess process;
					QStringList strList;
					QString rotateName = QString("%1/%2_180_pid_wjis.%3").arg(pDM->videoPath()).arg(fileInfo.baseName()).arg(fileInfo.completeSuffix());
					QFileInfo rotFileInfo(rotateName);
					if (!rotFileInfo.exists())
					{
						setCursor(Qt::WaitCursor);
						strList
							<< "-i"
							<< strDes
							<< "-vf"
							<< "rotate=PI:bilinear=0,format=yuv420p"
							<< "-metadata:s:v"
							<< "rotate=0"
							<< "-codec:v"
							<< "libx264"
							<< "-codec:a"
							<< "copy"
							<< rotateName;
						process.start(FFMPEG_FILE_PATH, strList);
						process.waitForFinished();
						setCursor(Qt::ArrowCursor);

						if (process.exitCode() == 0) // rotate complete
						{
							setCursor(Qt::WaitCursor);
							nFileSize = 0;
							uCRC = 0;
							pVFM->insertRows(nRow + 1, 1);
							index = pVFM->index(nRow + 1, 0);
							uCRC = CDataManage::CheckCRCFile(rotateName, &nFileSize);
							pVFM->setData(index.sibling(index.row(), 3), rotFileInfo.fileName(), Qt::EditRole);
							pVFM->setData(index.sibling(index.row(), 4), uCRC, Qt::EditRole);
							pVFM->setData(index.sibling(index.row(), 5), nFileSize, Qt::EditRole);
							setCursor(Qt::ArrowCursor);
						}
						else
						{
							QString processErrMsg = QString::fromStdString(process.readAllStandardError().toStdString());
							QMessageBox::warning(this, "Unexpected Error!", QString("%1").arg(processErrMsg));
						}
					}
					else
					{
						setCursor(Qt::WaitCursor);
						nFileSize = 0;
						uCRC = 0;
						pVFM->insertRows(nRow + 1, 1);
						index = pVFM->index(nRow + 1, 0);
						uCRC = CDataManage::CheckCRCFile(rotateName, &nFileSize);
						pVFM->setData(index.sibling(index.row(), 3), rotFileInfo.fileName(), Qt::EditRole);
						pVFM->setData(index.sibling(index.row(), 4), uCRC, Qt::EditRole);
						pVFM->setData(index.sibling(index.row(), 5), nFileSize, Qt::EditRole);
						setCursor(Qt::ArrowCursor);
						QMessageBox::information(this, "File already existed", QString("Existing roatated video (%1) added.").arg(rotFileInfo.fileName()));
					}

				}
			}
			 else if (answer == QMessageBox::YesToAll)
			 {
				 if (!strDes.isEmpty())
				 {
					 // video rotation
					 // refer: https://superuser.com/questions/578321/how-to-rotate-a-video-180-with-ffmpeg
					 QProcess process;
					 QStringList strList;
					 QString rotateName = QString("%1/%2_180_pid_wjis.%3").arg(pDM->videoPath()).arg(fileInfo.baseName()).arg(fileInfo.completeSuffix());
					 QFileInfo rotFileInfo(rotateName);
					 if (!rotFileInfo.exists())
					 {
						 setCursor(Qt::WaitCursor);
						 strList
							 << "-i"
							 << strDes
							 << "-vf"
							 << "rotate=PI:bilinear=0,format=yuv420p"
							 << "-metadata:s:v"
							 << "rotate=0"
							 << "-codec:v"
							 << "libx264"
							 << "-codec:a"
							 << "copy"
							 << rotateName;
						 process.start(FFMPEG_FILE_PATH, strList);
						 process.waitForFinished();
						 setCursor(Qt::ArrowCursor);

						 if (process.exitCode() == 0) // rotate complete
						 {
							 setCursor(Qt::WaitCursor);
							 nFileSize = 0;
							 uCRC = 0;
							 pVFM->insertRows(nRow + 1, 1);
							 index = pVFM->index(nRow + 1, 0);
							 uCRC = CDataManage::CheckCRCFile(rotateName, &nFileSize);
							 pVFM->setData(index.sibling(index.row(), 3), rotFileInfo.fileName(), Qt::EditRole);
							 pVFM->setData(index.sibling(index.row(), 4), uCRC, Qt::EditRole);
							 pVFM->setData(index.sibling(index.row(), 5), nFileSize, Qt::EditRole);
							 setCursor(Qt::ArrowCursor);
						 }
						 else
						 {
							 QString processErrMsg = QString::fromStdString(process.readAllStandardError().toStdString());
							 QMessageBox::warning(this, "Unexpected Error!", QString("%1").arg(processErrMsg));
						 }
					 }
					 else
					 {
						 setCursor(Qt::WaitCursor);
						 nFileSize = 0;
						 uCRC = 0;
						 pVFM->insertRows(nRow + 1, 1);
						 index = pVFM->index(nRow + 1, 0);
						 uCRC = CDataManage::CheckCRCFile(rotateName, &nFileSize);
						 pVFM->setData(index.sibling(index.row(), 3), rotFileInfo.fileName(), Qt::EditRole);
						 pVFM->setData(index.sibling(index.row(), 4), uCRC, Qt::EditRole);
						 pVFM->setData(index.sibling(index.row(), 5), nFileSize, Qt::EditRole);
						 setCursor(Qt::ArrowCursor);
						 QMessageBox::information(this, "File already existed", QString("Existing roatated video (%1) added.").arg(rotFileInfo.fileName()));
					 }

				 }
				 bAskAgain = false;
				 answer = QMessageBox::Yes;
			 }
			 else if (answer == QMessageBox::NoToAll)
			 {
				 bAskAgain = false;
				 answer = QMessageBox::No;
			 }
			
			GET_TABLE(VideoFilePool)->setCurrentIndex(index);
		}
	}
}


void ContentsPool::deleteVideoFilePool()
{
	int nRow;
	auto *pDM = CDataManage::GetInstance();
	std::shared_ptr<dataModel> pVFM = pDM->GET_MODEL_CLASS(VideoFilePool);
	QModelIndex index = GET_TABLE(VideoFilePool)->currentIndex();
	if (index.isValid())
	{
		int nRet = QMessageBox::warning(this, QString::fromStdWString(APPLICATION_NAME), QString::fromStdWString(ARE_YOU_SURE), QMessageBox::Yes | QMessageBox::No);
		if (nRet == QMessageBox::Yes)
		{
			nRow = index.row();
			pVFM->removeRows(nRow, 1);
		}
	}
}

void ContentsPool::onAudioPlay()
{
	if (GET_TABLE(AudioFilePool)->currentIndex().isValid())
	{
		m_audioPlayer->play();
	}
	else
	{
		QMessageBox::warning(this, "Select an audio file", "There is no audio file to play.");
	}
}

void ContentsPool::onAudioPause()
{
	m_audioPlayer->pause();
}

void ContentsPool::onAudioStop()
{
	m_audioPlayer->stop();
}

void ContentsPool::onAudioPosChanged(qint64 pos)
{
	ui.progBarAudio->setValue(pos);
}

void ContentsPool::onAudioMediaChanged(const QMediaContent & media)
{
	// 재생할 audio file이 변경된 경우 호출
}

void ContentsPool::onDurationChanged(qint64 dur)
{
	m_audioDuration = dur;
	ui.progBarAudio->setMaximum(m_audioDuration);

	m_audioPlayer->play();

	if (m_audioDuration > 0)
	{
		auto *pDM = CDataManage::GetInstance();
		std::shared_ptr<dataModel> pVFM = pDM->GET_MODEL_CLASS(AudioFilePool);
		QModelIndex index = GET_TABLE(AudioFilePool)->currentIndex();
		pVFM->setData(index.sibling(index.row(), 7), m_audioDuration, Qt::EditRole);
	}
}

void ContentsPool::onVideoPlay()
{
	int nRow;
	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();
	std::shared_ptr<dataModel> pVFM = pDM->GET_MODEL_CLASS(VideoFilePool);
	QModelIndex index = GET_TABLE(VideoFilePool)->currentIndex();
	nRow = index.row();
	if (index.isValid())
	{
		auto *t = (VideoFilePool*)pVFM->m_pEditor->m_pvSQLData->at(nRow).get();
		qDebug() << QString::fromStdWString(t->szFileName);
		QProcess process;
		QStringList args;
		QString fileName = QString("C:/PapisProgram/PapisData/Video/%1").arg(QString::fromStdWString(t->szFileName));
		QFileInfo fInfo(fileName);
		if (fInfo.exists())
		{
			args
				<< "-x"
				<< "640"
				<< "-y"
				<< "480"
				<< fileName;
			process.start(FFPLAY_FILE_PATH, args);
			process.waitForFinished();
			
			if (process.exitCode() != 0)
			{
				QString processErrMsg = QString::fromStdString(process.readAllStandardError().toStdString());
				QMessageBox::warning(this, "Unexpected Error!", QString("%1").arg(processErrMsg));
			}
		}
		else
		{
			QMessageBox::warning(this, "Warning!", QString("The file does not exist.\n(File Path: %1)").arg(fileName));
		}
	}
}
