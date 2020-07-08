#ifndef CONTENTSPOOL_H
#define CONTENTSPOOL_H

#include <QDialog>
#include "ui_contentsPool.h"
#include <QfutureWatcher>
#include "TableViewHelper.h"

#include <qmediaplayer.h>
#include <qmediaplaylist.h>

class QVideoWidget;

class ContentsPool : public QDialog
{
	Q_OBJECT

public:
	ContentsPool(QWidget *parent = 0);
	~ContentsPool();
public:
	bool eventFilter(QObject *object, QEvent *event);
	
	DECLARE_INIT_FUNCTION_FOR_CLASS(AudioFilePool);
	DECLARE_INIT_FUNCTION_FOR_CLASS(VideoFilePool);

protected:
	void closeEvent(QCloseEvent *event);

private slots:
	void addAudioFilePool(bool bInsert);
	void deleteAudioFilePool();

	void addVideoFilePool(bool bInsert);
	void deleteVideoFilePool();
	
	// audio related func
	void onAudioPlay();
	void onAudioPause();
	void onAudioStop();
	void onAudioPosChanged(qint64 pos);
	void onAudioMediaChanged(const QMediaContent &media);

	// video related func
	void onVideoPlay();
	void onVideoPause();
	void onVideoStop();
	void onVideoPosChanged(qint64 pos);
	void onVideoMediaChanged(const QMediaContent &media);

private:
	Ui::Dialog ui;

	// audio related var
	QMediaPlayer *m_audioPlayer{ 0 };
	QString m_audioFilePath{""};
	qint64 m_audioDuration{ 0 };

	// video related var
	QMediaPlayer *m_videoPlayer{ 0 };
	QString m_videoFilePath{ "" };
	qint64 m_videoDuration{ 0 };
	QVideoWidget *m_videoWidget;
};

#endif // CREATEUPDATE_H
