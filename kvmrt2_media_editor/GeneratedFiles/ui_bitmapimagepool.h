/********************************************************************************
** Form generated from reading UI file 'bitmapimagepool.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BITMAPIMAGEPOOL_H
#define UI_BITMAPIMAGEPOOL_H

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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_bitmapImagePool
{
public:
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnAddBitmap;
    QPushButton *btnDelBitmap;
    QSpacerItem *horizontalSpacer;
    QTableView *m_tblBitmapImagePool;
    QWidget *widget1;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnColor;
    QSpacerItem *horizontalSpacer_3;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnClose;

    void setupUi(QDialog *bitmapImagePool)
    {
        if (bitmapImagePool->objectName().isEmpty())
            bitmapImagePool->setObjectName(QStringLiteral("bitmapImagePool"));
        bitmapImagePool->resize(577, 393);
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        bitmapImagePool->setFont(font);
        verticalLayout_3 = new QVBoxLayout(bitmapImagePool);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        groupBox = new QGroupBox(bitmapImagePool);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        splitter = new QSplitter(groupBox);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        widget = new QWidget(splitter);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        btnAddBitmap = new QPushButton(widget);
        btnAddBitmap->setObjectName(QStringLiteral("btnAddBitmap"));

        horizontalLayout_3->addWidget(btnAddBitmap);

        btnDelBitmap = new QPushButton(widget);
        btnDelBitmap->setObjectName(QStringLiteral("btnDelBitmap"));

        horizontalLayout_3->addWidget(btnDelBitmap);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_3);

        m_tblBitmapImagePool = new QTableView(widget);
        m_tblBitmapImagePool->setObjectName(QStringLiteral("m_tblBitmapImagePool"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_tblBitmapImagePool->sizePolicy().hasHeightForWidth());
        m_tblBitmapImagePool->setSizePolicy(sizePolicy);
        m_tblBitmapImagePool->setMinimumSize(QSize(360, 0));
        m_tblBitmapImagePool->setSortingEnabled(false);

        verticalLayout_2->addWidget(m_tblBitmapImagePool);

        verticalLayout_2->setStretch(1, 2);
        splitter->addWidget(widget);
        widget1 = new QWidget(splitter);
        widget1->setObjectName(QStringLiteral("widget1"));
        verticalLayout = new QVBoxLayout(widget1);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        btnColor = new QPushButton(widget1);
        btnColor->setObjectName(QStringLiteral("btnColor"));

        horizontalLayout_2->addWidget(btnColor);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_2);

        frame = new QFrame(widget1);
        frame->setObjectName(QStringLiteral("frame"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame);

        verticalLayout->setStretch(1, 2);
        splitter->addWidget(widget1);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);


        verticalLayout_3->addWidget(groupBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        btnClose = new QPushButton(bitmapImagePool);
        btnClose->setObjectName(QStringLiteral("btnClose"));

        horizontalLayout->addWidget(btnClose);


        verticalLayout_3->addLayout(horizontalLayout);

        verticalLayout_3->setStretch(0, 2);

        retranslateUi(bitmapImagePool);

        QMetaObject::connectSlotsByName(bitmapImagePool);
    } // setupUi

    void retranslateUi(QDialog *bitmapImagePool)
    {
        bitmapImagePool->setWindowTitle(QApplication::translate("bitmapImagePool", "bitmapImagePool", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("bitmapImagePool", "Bitmap List", Q_NULLPTR));
        btnAddBitmap->setText(QApplication::translate("bitmapImagePool", "Add", Q_NULLPTR));
        btnDelBitmap->setText(QApplication::translate("bitmapImagePool", "Del", Q_NULLPTR));
        btnColor->setText(QApplication::translate("bitmapImagePool", "Background Colour", Q_NULLPTR));
        btnClose->setText(QApplication::translate("bitmapImagePool", "Close", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class bitmapImagePool: public Ui_bitmapImagePool {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BITMAPIMAGEPOOL_H
