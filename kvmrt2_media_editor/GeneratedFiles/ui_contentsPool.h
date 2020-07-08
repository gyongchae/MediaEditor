/********************************************************************************
** Form generated from reading UI file 'contentsPool.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTENTSPOOL_H
#define UI_CONTENTSPOOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_3;
    QSplitter *splitter;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnAddAudio;
    QPushButton *btnDelAudio;
    QPushButton *btnDelAllAudio;
    QSpacerItem *horizontalSpacer;
    QTableView *m_tblAudioFilePool;
    QHBoxLayout *horizontalLayout_4;
    QToolButton *btnPlayAudio;
    QToolButton *btnPauseAudio;
    QToolButton *btnStopAudio;
    QProgressBar *progBarAudio;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnAddVideo;
    QPushButton *btnDelVideo;
    QPushButton *btnDelAllVideo;
    QSpacerItem *horizontalSpacer_2;
    QTableView *m_tblVideoFilePool;
    QHBoxLayout *horizontalLayout_5;
    QToolButton *btnPlayVideo;
    QToolButton *btnPauseVideo;
    QToolButton *btnStopVideo;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnClose;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(883, 615);
        gridLayout_3 = new QGridLayout(Dialog);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        splitter = new QSplitter(Dialog);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        groupBox = new QGroupBox(splitter);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btnAddAudio = new QPushButton(groupBox);
        btnAddAudio->setObjectName(QStringLiteral("btnAddAudio"));

        horizontalLayout->addWidget(btnAddAudio);

        btnDelAudio = new QPushButton(groupBox);
        btnDelAudio->setObjectName(QStringLiteral("btnDelAudio"));

        horizontalLayout->addWidget(btnDelAudio);

        btnDelAllAudio = new QPushButton(groupBox);
        btnDelAllAudio->setObjectName(QStringLiteral("btnDelAllAudio"));

        horizontalLayout->addWidget(btnDelAllAudio);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout);

        m_tblAudioFilePool = new QTableView(groupBox);
        m_tblAudioFilePool->setObjectName(QStringLiteral("m_tblAudioFilePool"));

        verticalLayout_2->addWidget(m_tblAudioFilePool);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        btnPlayAudio = new QToolButton(groupBox);
        btnPlayAudio->setObjectName(QStringLiteral("btnPlayAudio"));

        horizontalLayout_4->addWidget(btnPlayAudio);

        btnPauseAudio = new QToolButton(groupBox);
        btnPauseAudio->setObjectName(QStringLiteral("btnPauseAudio"));

        horizontalLayout_4->addWidget(btnPauseAudio);

        btnStopAudio = new QToolButton(groupBox);
        btnStopAudio->setObjectName(QStringLiteral("btnStopAudio"));

        horizontalLayout_4->addWidget(btnStopAudio);

        progBarAudio = new QProgressBar(groupBox);
        progBarAudio->setObjectName(QStringLiteral("progBarAudio"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(progBarAudio->sizePolicy().hasHeightForWidth());
        progBarAudio->setSizePolicy(sizePolicy);
        progBarAudio->setMaximum(100);
        progBarAudio->setValue(0);
        progBarAudio->setTextVisible(true);
        progBarAudio->setOrientation(Qt::Horizontal);
        progBarAudio->setInvertedAppearance(false);
        progBarAudio->setTextDirection(QProgressBar::TopToBottom);

        horizontalLayout_4->addWidget(progBarAudio);


        verticalLayout_2->addLayout(horizontalLayout_4);

        verticalLayout_2->setStretch(1, 1);
        splitter->addWidget(groupBox);
        groupBox_2 = new QGroupBox(splitter);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        btnAddVideo = new QPushButton(groupBox_2);
        btnAddVideo->setObjectName(QStringLiteral("btnAddVideo"));

        horizontalLayout_2->addWidget(btnAddVideo);

        btnDelVideo = new QPushButton(groupBox_2);
        btnDelVideo->setObjectName(QStringLiteral("btnDelVideo"));

        horizontalLayout_2->addWidget(btnDelVideo);

        btnDelAllVideo = new QPushButton(groupBox_2);
        btnDelAllVideo->setObjectName(QStringLiteral("btnDelAllVideo"));

        horizontalLayout_2->addWidget(btnDelAllVideo);

        horizontalSpacer_2 = new QSpacerItem(37, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        m_tblVideoFilePool = new QTableView(groupBox_2);
        m_tblVideoFilePool->setObjectName(QStringLiteral("m_tblVideoFilePool"));

        verticalLayout->addWidget(m_tblVideoFilePool);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        btnPlayVideo = new QToolButton(groupBox_2);
        btnPlayVideo->setObjectName(QStringLiteral("btnPlayVideo"));

        horizontalLayout_5->addWidget(btnPlayVideo);

        btnPauseVideo = new QToolButton(groupBox_2);
        btnPauseVideo->setObjectName(QStringLiteral("btnPauseVideo"));

        horizontalLayout_5->addWidget(btnPauseVideo);

        btnStopVideo = new QToolButton(groupBox_2);
        btnStopVideo->setObjectName(QStringLiteral("btnStopVideo"));

        horizontalLayout_5->addWidget(btnStopVideo);

        horizontalSpacer_4 = new QSpacerItem(34, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_5);

        verticalLayout->setStretch(1, 1);
        splitter->addWidget(groupBox_2);

        verticalLayout_3->addWidget(splitter);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        btnClose = new QPushButton(Dialog);
        btnClose->setObjectName(QStringLiteral("btnClose"));

        horizontalLayout_3->addWidget(btnClose);


        verticalLayout_3->addLayout(horizontalLayout_3);

        verticalLayout_3->setStretch(0, 1);

        gridLayout_3->addLayout(verticalLayout_3, 0, 0, 1, 1);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Audio & Video", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("Dialog", "Audio File List", Q_NULLPTR));
        btnAddAudio->setText(QApplication::translate("Dialog", "Add", Q_NULLPTR));
        btnDelAudio->setText(QApplication::translate("Dialog", "Del", Q_NULLPTR));
        btnDelAllAudio->setText(QApplication::translate("Dialog", "Delete All", Q_NULLPTR));
        btnPlayAudio->setText(QApplication::translate("Dialog", "Play", Q_NULLPTR));
        btnPauseAudio->setText(QApplication::translate("Dialog", "Pause", Q_NULLPTR));
        btnStopAudio->setText(QApplication::translate("Dialog", "Stop", Q_NULLPTR));
        progBarAudio->setFormat(QApplication::translate("Dialog", "%v ms", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("Dialog", "Video File List", Q_NULLPTR));
        btnAddVideo->setText(QApplication::translate("Dialog", "Add", Q_NULLPTR));
        btnDelVideo->setText(QApplication::translate("Dialog", "Del", Q_NULLPTR));
        btnDelAllVideo->setText(QApplication::translate("Dialog", "Delete All", Q_NULLPTR));
        btnPlayVideo->setText(QApplication::translate("Dialog", "Play", Q_NULLPTR));
        btnPauseVideo->setText(QApplication::translate("Dialog", "Pause", Q_NULLPTR));
        btnStopVideo->setText(QApplication::translate("Dialog", "Stop", Q_NULLPTR));
        btnClose->setText(QApplication::translate("Dialog", "Close", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTENTSPOOL_H
