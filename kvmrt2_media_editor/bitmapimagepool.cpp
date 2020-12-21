#include "bitmapimagepool.h"
#include "DataManage.h"
#include "dataModel.h"
#include <shlwapi.h>
#include <QtGui>
#include "ini.h"
#include "stringscaler.h"
#include "DefineTables.h"
#include "qtextaligner.h"
#include <qcolordialog.h>
#include "TileMapSupport.h"
#include <qdebug.h>
#include <qsplitter.h>
#include "DefineMode.h"

bitmapImagePool::bitmapImagePool(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	CALL_INIT_FUNCTION(BitmapImagePool);
	
	connect(ui.btnAddBitmap, SIGNAL(clicked(bool)), this, SLOT(addBitmapImagePool(bool)));
	connect(ui.btnDelBitmap, SIGNAL(clicked()), this, SLOT(deleteBitmapImagePool()));
	connect(ui.btnClose, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui.btnColor, SIGNAL(clicked()), this, SLOT(changeBackgroundColor()));

	if (OFFICIAL_RELEASE == true)
	{
		SET_HIDE_TABLE_COLUMN(BitmapImagePool, 0);
		SET_HIDE_TABLE_COLUMN(BitmapImagePool, 1);
		SET_HIDE_TABLE_COLUMN(BitmapImagePool, 5);
		SET_HIDE_TABLE_COLUMN(BitmapImagePool, 6);
		SET_HIDE_TABLE_COLUMN(BitmapImagePool, 7);
	}
}

bitmapImagePool::~bitmapImagePool()
{
}

IMPLEMENT_INIT_FUNCTION_FOR_CLASS(bitmapImagePool, BitmapImagePool)
{
	auto *pDM = CDataManage::GetInstance();
	SET_MODEL_FOR_TABLE_VIEW(BitmapImagePool, pDM)
	INSTALL_EVENT_FILTER(BitmapImagePool)

	SET_SELECTION_BEHAVIOR(BitmapImagePool, QAbstractItemView::SelectRows)
	SET_SELECTION_MODE(BitmapImagePool, QAbstractItemView::SingleSelection)

	SET_DRAG_AND_DROP_ENABLED(BitmapImagePool);
	SET_EDIT_TRIGGERS(BitmapImagePool, QAbstractItemView::NoEditTriggers);

	QHeaderView *header = GET_TABLE(BitmapImagePool)->horizontalHeader();
	header->resizeSections(QHeaderView::ResizeToContents);

	CONNECT_ROW_CHAHANGED_SLOT(BitmapImagePool, updateBitmapImage(const QModelIndex &, const QModelIndex &));
	connect(GET_TABLE_MODEL(pDM, BitmapImagePool).get(), SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), this, SLOT(updateBitmapImagePool(const QModelIndex &, const QModelIndex &)));

	m_pSFMLView = new QTextAligner(ui.widget, QPoint(0, 0), QSize(999, 999), QTextAligner::BITMAP);
	m_pSFMLView->setBackgroundColor(pDM->m_bmpPoolBack);
	return false;
}

void bitmapImagePool::addBitmapImagePool(bool bInsert)
{
	int nRow;

	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();
	std::vector<std::shared_ptr<CSQLData>>::iterator nit;
	std::shared_ptr<dataModel> pVFM = pDM->GET_MODEL_CLASS(BitmapImagePool);
	CTileMapSupport *pTMS = CTileMapSupport::GetInstance();
	QModelIndex index = GET_TABLE(BitmapImagePool)->currentIndex();
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

	QStringList filePaths =
		QFileDialog::getOpenFileNames(
			this,
			QString::fromStdWString(L"Find image files"),
			QDir::homePath(),
			tr("File (*.png *.PNG *.bmp *.BMP *.gif *.GIF)"));
	if (filePaths.size())
	{
		while (filePaths.size())
		{
			int nActualWidth, nActualHeight;
			QString filePath = filePaths.takeFirst();
			std::shared_ptr<unsigned char> pByte = pTMS->GetBitmapBuffer((wchar_t*)filePath.toStdWString().c_str(), 0, 0, &nActualWidth, &nActualHeight);
			if (pByte.get())
			{
				QFileInfo fileInfo(filePath);
				if (fileInfo.completeSuffix() == "gif" || fileInfo.completeSuffix() == "GIF")
				{
					QString filename(fileInfo.fileName());
					pVFM->insertRows(nRow, 1);
					BitmapImagePool *pImage = (BitmapImagePool*)pTM->m_vBitmapImagePool[nRow].get();
					wcscpy(pImage->szFileName, filename.toStdWString().c_str());
					pImage->nWidth = nActualWidth;
					pImage->nHeight = nActualHeight;
					pImage->nDataLength = nActualWidth*nActualHeight * 4;
					pImage->pByte = pByte;
					nRow += 1;

					int ans = QMessageBox::question(this, "Add Splitted Png File", QString("%1 is a GIF file. It needs to save not only GIF but splitted PNGs.\n"
													"Do you want to save splitted PNGs?").arg(fileInfo.fileName()));
					if (ans == QMessageBox::Yes)
					{
						qDebug() << "<GIF FILE INFORMATION>"
							<< "[1]" << fileInfo.fileName() << "\n"
							<< "[2]" << fileInfo.baseName() << "\n"
							<< "[3]" << fileInfo.filePath() << "\n"
							<< "[4]" << fileInfo.completeSuffix() << "\n"
							<< "[5]" << fileInfo.absoluteFilePath() << "\n"
							<< "[6]" << fileInfo.absolutePath() << "\n";

						QString fileName(fileInfo.fileName());
						QString originalFileName = fileInfo.baseName();
						QProcess process;
						QStringList args;
						QString splitFileName = QString("%1/%2_%d.png").arg(fileInfo.absolutePath()).arg(fileInfo.baseName());
						args << "-i"
							<< fileInfo.filePath()
							<< "-vsync"
							<< "0"
							<< splitFileName;

						process.start(FFMPEG_FILE_PATH, args);
						process.waitForFinished();
						if (process.exitCode() == 0) // success!
						{
							int fileNums = 0;
							for (int i = 1; i < 100; i++)
							{
								QString splitFile = QString("%1/%2_%3.png").arg(fileInfo.absolutePath()).arg(originalFileName).arg(i);
								QFileInfo fInfo(fileInfo.absoluteDir(), splitFile);
								if (fInfo.exists())
								{
									int nWidth = 0;
									int nHeight = 0;
									std::shared_ptr<unsigned char> splitByte = pTMS->GetBitmapBuffer((wchar_t*)splitFile.toStdWString().c_str(), 0, 0, &nWidth, &nHeight);
									if (splitByte.get())
									{
										pVFM->insertRows(nRow, 1);
										BitmapImagePool *pImage = (BitmapImagePool*)pTM->m_vBitmapImagePool[nRow].get();
										wcscpy(pImage->szFileName, fInfo.fileName().toStdWString().c_str());
										pImage->nWidth = nWidth;
										pImage->nHeight = nHeight;
										pImage->nDataLength = nWidth*nHeight * 4;
										pImage->pByte = splitByte;
										nRow += 1;
									}
								}
								else
								{
									fileNums = i - 1;
									break;
								}
							}
							qDebug() << "total file nums:" << fileNums;
						}
						else
						{
							QString err = QString::fromStdString(process.readAllStandardError().toStdString());
							QMessageBox::warning(this, "Unexpected Error!", QString("%1").arg(err));
						}

						// gif split refer : https://www.reddit.com/r/ffmpeg/comments/cqwlwo/extracting_frames_from_gif/
						//ffmpeg -i input/Clap.gif -vsync 0 temp/temp%d.png
					}
				}
				else
				{
					QString filename(fileInfo.fileName());
					pVFM->insertRows(nRow, 1);
					BitmapImagePool *pImage = (BitmapImagePool*)pTM->m_vBitmapImagePool[nRow].get();
					wcscpy(pImage->szFileName, filename.toStdWString().c_str());
					pImage->nWidth = nActualWidth;
					pImage->nHeight = nActualHeight;
					pImage->nDataLength = nActualWidth*nActualHeight * 4;
					pImage->pByte = pByte;
				}
			}
			GET_TABLE(BitmapImagePool)->setCurrentIndex(index);
		}
	}
}

void bitmapImagePool::deleteBitmapImagePool()
{
	int nRow;
	auto *pDM = CDataManage::GetInstance();
	std::shared_ptr<dataModel> pVFM = pDM->GET_MODEL_CLASS(BitmapImagePool);
	QModelIndex index = GET_TABLE(BitmapImagePool)->currentIndex();
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

bool bitmapImagePool::eventFilter(QObject *object, QEvent *event)
{
	auto *pDM = CDataManage::GetInstance();
	QModelIndex index;
	if (event->type() == QEvent::KeyPress)
	{
		QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
		if (keyEvent->key() == Qt::Key_Delete)
		{
			if (object == GET_TABLE(BitmapImagePool))
			{
				deleteBitmapImagePool();
			}
			return true;
		}
		else if (keyEvent->key() == Qt::Key_F9)
		{
			if (object == GET_TABLE(BitmapImagePool))
			{
				addBitmapImagePool(false);
			}
			return true;
		}
		else if (keyEvent->key() == Qt::Key_Insert)
		{
			if (object == GET_TABLE(BitmapImagePool))
			{
				addBitmapImagePool(true);
			}
			return true;
		}
	}
	return false;
}

void bitmapImagePool::updateBitmapImage(const QModelIndex & current, const QModelIndex & previous)
{
	QModelIndex index = GET_TABLE(BitmapImagePool)->currentIndex();
	auto *pDM = CDataManage::GetInstance();
	auto *pTM = CTableManage::GetInstance();
	if (current.isValid())
	{
		int nRow = current.row();
		if (nRow < pTM->VECTOR_CLASS(BitmapImagePool).size())
		{
			m_pSFMLView->clearAllSprite();
			BitmapImagePool *pImage = (BitmapImagePool*)pTM->m_vBitmapImagePool[nRow].get();
			if (pImage->nWidth&&pImage->nHeight)
			{
				m_pSFMLView->setTexSprite(pImage->GetIndex(), pImage->nWidth, pImage->nHeight, 0, 0, pImage->pByte.get());
			}
		}
		m_pSFMLView->update();
	}
}

void bitmapImagePool::changeBackgroundColor()
{
	auto *pDM = CDataManage::GetInstance();
	
	pDM->m_bmpPoolBack = QColorDialog::getColor(m_pSFMLView->backgroundColor(), this);
	if (pDM->m_bmpPoolBack.isValid())
	{
		m_pSFMLView->setBackgroundColor(pDM->m_bmpPoolBack);
	}
}
