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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_3;
    QSplitter *splitter;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnPlayAudio;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnAddAudio;
    QPushButton *btnDelAudio;
    QTableView *m_tblAudioFilePool;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnPlayVideo;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnAddVideo;
    QPushButton *btnDelVideo;
    QTableView *m_tblVideoFilePool;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnClose;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(631, 308);
        gridLayout_3 = new QGridLayout(Dialog);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        splitter = new QSplitter(Dialog);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        groupBox = new QGroupBox(splitter);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btnPlayAudio = new QPushButton(groupBox);
        btnPlayAudio->setObjectName(QStringLiteral("btnPlayAudio"));

        horizontalLayout->addWidget(btnPlayAudio);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnAddAudio = new QPushButton(groupBox);
        btnAddAudio->setObjectName(QStringLiteral("btnAddAudio"));

        horizontalLayout->addWidget(btnAddAudio);

        btnDelAudio = new QPushButton(groupBox);
        btnDelAudio->setObjectName(QStringLiteral("btnDelAudio"));

        horizontalLayout->addWidget(btnDelAudio);


        verticalLayout_2->addLayout(horizontalLayout);

        m_tblAudioFilePool = new QTableView(groupBox);
        m_tblAudioFilePool->setObjectName(QStringLiteral("m_tblAudioFilePool"));

        verticalLayout_2->addWidget(m_tblAudioFilePool);

        verticalLayout_2->setStretch(1, 1);

        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);

        splitter->addWidget(groupBox);
        groupBox_2 = new QGroupBox(splitter);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        btnPlayVideo = new QPushButton(groupBox_2);
        btnPlayVideo->setObjectName(QStringLiteral("btnPlayVideo"));

        horizontalLayout_2->addWidget(btnPlayVideo);

        horizontalSpacer_2 = new QSpacerItem(37, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        btnAddVideo = new QPushButton(groupBox_2);
        btnAddVideo->setObjectName(QStringLiteral("btnAddVideo"));

        horizontalLayout_2->addWidget(btnAddVideo);

        btnDelVideo = new QPushButton(groupBox_2);
        btnDelVideo->setObjectName(QStringLiteral("btnDelVideo"));

        horizontalLayout_2->addWidget(btnDelVideo);


        verticalLayout->addLayout(horizontalLayout_2);

        m_tblVideoFilePool = new QTableView(groupBox_2);
        m_tblVideoFilePool->setObjectName(QStringLiteral("m_tblVideoFilePool"));

        verticalLayout->addWidget(m_tblVideoFilePool);

        verticalLayout->setStretch(1, 1);

        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);

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
        btnPlayAudio->setText(QApplication::translate("Dialog", "Play", Q_NULLPTR));
        btnAddAudio->setText(QApplication::translate("Dialog", "Add", Q_NULLPTR));
        btnDelAudio->setText(QApplication::translate("Dialog", "Del", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("Dialog", "Video File List", Q_NULLPTR));
        btnPlayVideo->setText(QApplication::translate("Dialog", "Play", Q_NULLPTR));
        btnAddVideo->setText(QApplication::translate("Dialog", "Add", Q_NULLPTR));
        btnDelVideo->setText(QApplication::translate("Dialog", "Del", Q_NULLPTR));
        btnClose->setText(QApplication::translate("Dialog", "Close", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTENTSPOOL_H
