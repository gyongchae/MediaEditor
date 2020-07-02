/********************************************************************************
** Form generated from reading UI file 'imagelistpool.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGELISTPOOL_H
#define UI_IMAGELISTPOOL_H

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

class Ui_imageListPool
{
public:
    QVBoxLayout *verticalLayout_3;
    QSplitter *splitter_2;
    QSplitter *splitter;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnAddImgListPool;
    QPushButton *btnDelImgListPool;
    QSpacerItem *horizontalSpacer_2;
    QTableView *m_tblImageIndexList;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnAddImgIndex;
    QPushButton *btnDelImgIndex;
    QSpacerItem *horizontalSpacer_3;
    QTableView *m_tblImageIndex;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnColor;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnClose;

    void setupUi(QDialog *imageListPool)
    {
        if (imageListPool->objectName().isEmpty())
            imageListPool->setObjectName(QStringLiteral("imageListPool"));
        imageListPool->resize(639, 594);
        verticalLayout_3 = new QVBoxLayout(imageListPool);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        splitter_2 = new QSplitter(imageListPool);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        groupBox = new QGroupBox(splitter);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        btnAddImgListPool = new QPushButton(groupBox);
        btnAddImgListPool->setObjectName(QStringLiteral("btnAddImgListPool"));

        horizontalLayout_2->addWidget(btnAddImgListPool);

        btnDelImgListPool = new QPushButton(groupBox);
        btnDelImgListPool->setObjectName(QStringLiteral("btnDelImgListPool"));

        horizontalLayout_2->addWidget(btnDelImgListPool);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        m_tblImageIndexList = new QTableView(groupBox);
        m_tblImageIndexList->setObjectName(QStringLiteral("m_tblImageIndexList"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_tblImageIndexList->sizePolicy().hasHeightForWidth());
        m_tblImageIndexList->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(m_tblImageIndexList);

        verticalLayout->setStretch(1, 1);

        gridLayout->addLayout(verticalLayout, 1, 0, 1, 1);

        splitter->addWidget(groupBox);
        groupBox_2 = new QGroupBox(splitter);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        btnAddImgIndex = new QPushButton(groupBox_2);
        btnAddImgIndex->setObjectName(QStringLiteral("btnAddImgIndex"));

        horizontalLayout_3->addWidget(btnAddImgIndex);

        btnDelImgIndex = new QPushButton(groupBox_2);
        btnDelImgIndex->setObjectName(QStringLiteral("btnDelImgIndex"));

        horizontalLayout_3->addWidget(btnDelImgIndex);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_3);

        m_tblImageIndex = new QTableView(groupBox_2);
        m_tblImageIndex->setObjectName(QStringLiteral("m_tblImageIndex"));
        sizePolicy.setHeightForWidth(m_tblImageIndex->sizePolicy().hasHeightForWidth());
        m_tblImageIndex->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(m_tblImageIndex);

        verticalLayout_2->setStretch(1, 1);

        gridLayout_2->addLayout(verticalLayout_2, 1, 0, 1, 1);

        splitter->addWidget(groupBox_2);
        splitter_2->addWidget(splitter);
        frame = new QFrame(splitter_2);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        splitter_2->addWidget(frame);

        verticalLayout_3->addWidget(splitter_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btnColor = new QPushButton(imageListPool);
        btnColor->setObjectName(QStringLiteral("btnColor"));

        horizontalLayout->addWidget(btnColor);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnClose = new QPushButton(imageListPool);
        btnClose->setObjectName(QStringLiteral("btnClose"));

        horizontalLayout->addWidget(btnClose);


        verticalLayout_3->addLayout(horizontalLayout);

        verticalLayout_3->setStretch(0, 1);

        retranslateUi(imageListPool);

        QMetaObject::connectSlotsByName(imageListPool);
    } // setupUi

    void retranslateUi(QDialog *imageListPool)
    {
        imageListPool->setWindowTitle(QApplication::translate("imageListPool", "imageListPool", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("imageListPool", "Image List Pool", Q_NULLPTR));
        btnAddImgListPool->setText(QApplication::translate("imageListPool", "Add", Q_NULLPTR));
        btnDelImgListPool->setText(QApplication::translate("imageListPool", "Del", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("imageListPool", "Image List Index", Q_NULLPTR));
        btnAddImgIndex->setText(QApplication::translate("imageListPool", "Add", Q_NULLPTR));
        btnDelImgIndex->setText(QApplication::translate("imageListPool", "Del", Q_NULLPTR));
        btnColor->setText(QApplication::translate("imageListPool", "Background Colour", Q_NULLPTR));
        btnClose->setText(QApplication::translate("imageListPool", "Close", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class imageListPool: public Ui_imageListPool {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGELISTPOOL_H
