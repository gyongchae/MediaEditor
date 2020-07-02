/********************************************************************************
** Form generated from reading UI file 'StationImagePool.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATIONIMAGEPOOL_H
#define UI_STATIONIMAGEPOOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
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

class Ui_stationImagePool
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnAddText;
    QPushButton *btnDelText;
    QSpacerItem *horizontalSpacer;
    QSplitter *splitter;
    QTableView *m_tblStationImagePool;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnColor;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnClose;

    void setupUi(QDialog *stationImagePool)
    {
        if (stationImagePool->objectName().isEmpty())
            stationImagePool->setObjectName(QStringLiteral("stationImagePool"));
        stationImagePool->resize(528, 524);
        verticalLayout_2 = new QVBoxLayout(stationImagePool);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(stationImagePool);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btnAddText = new QPushButton(groupBox);
        btnAddText->setObjectName(QStringLiteral("btnAddText"));

        horizontalLayout->addWidget(btnAddText);

        btnDelText = new QPushButton(groupBox);
        btnDelText->setObjectName(QStringLiteral("btnDelText"));

        horizontalLayout->addWidget(btnDelText);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        splitter = new QSplitter(groupBox);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        m_tblStationImagePool = new QTableView(splitter);
        m_tblStationImagePool->setObjectName(QStringLiteral("m_tblStationImagePool"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_tblStationImagePool->sizePolicy().hasHeightForWidth());
        m_tblStationImagePool->setSizePolicy(sizePolicy);
        splitter->addWidget(m_tblStationImagePool);
        frame = new QFrame(splitter);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        splitter->addWidget(frame);

        verticalLayout->addWidget(splitter);

        verticalLayout->setStretch(1, 1);

        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        btnColor = new QPushButton(stationImagePool);
        btnColor->setObjectName(QStringLiteral("btnColor"));

        horizontalLayout_2->addWidget(btnColor);

        horizontalSpacer_2 = new QSpacerItem(37, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        btnClose = new QPushButton(stationImagePool);
        btnClose->setObjectName(QStringLiteral("btnClose"));

        horizontalLayout_2->addWidget(btnClose);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalLayout_2->setStretch(0, 1);

        retranslateUi(stationImagePool);

        QMetaObject::connectSlotsByName(stationImagePool);
    } // setupUi

    void retranslateUi(QDialog *stationImagePool)
    {
        stationImagePool->setWindowTitle(QApplication::translate("stationImagePool", "Station Image Pool", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("stationImagePool", "Text List", Q_NULLPTR));
        btnAddText->setText(QApplication::translate("stationImagePool", "Add", Q_NULLPTR));
        btnDelText->setText(QApplication::translate("stationImagePool", "Del", Q_NULLPTR));
        btnColor->setText(QApplication::translate("stationImagePool", "Background Colour", Q_NULLPTR));
        btnClose->setText(QApplication::translate("stationImagePool", "Close", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class stationImagePool: public Ui_stationImagePool {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATIONIMAGEPOOL_H
