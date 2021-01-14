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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_bitmapImagePool
{
public:
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnAddBitmap;
    QPushButton *btnDelBitmap;
    QSpacerItem *horizontalSpacer;
    QTableView *m_tblBitmapImagePool;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_4;
    QWidget *widget;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnColor;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnClose;

    void setupUi(QDialog *bitmapImagePool)
    {
        if (bitmapImagePool->objectName().isEmpty())
            bitmapImagePool->setObjectName(QStringLiteral("bitmapImagePool"));
        bitmapImagePool->resize(898, 531);
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        bitmapImagePool->setFont(font);
        verticalLayout = new QVBoxLayout(bitmapImagePool);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        splitter = new QSplitter(bitmapImagePool);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        groupBox = new QGroupBox(splitter);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        btnAddBitmap = new QPushButton(groupBox);
        btnAddBitmap->setObjectName(QStringLiteral("btnAddBitmap"));

        horizontalLayout_3->addWidget(btnAddBitmap);

        btnDelBitmap = new QPushButton(groupBox);
        btnDelBitmap->setObjectName(QStringLiteral("btnDelBitmap"));

        horizontalLayout_3->addWidget(btnDelBitmap);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_3);

        m_tblBitmapImagePool = new QTableView(groupBox);
        m_tblBitmapImagePool->setObjectName(QStringLiteral("m_tblBitmapImagePool"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_tblBitmapImagePool->sizePolicy().hasHeightForWidth());
        m_tblBitmapImagePool->setSizePolicy(sizePolicy);
        m_tblBitmapImagePool->setSortingEnabled(false);

        verticalLayout_2->addWidget(m_tblBitmapImagePool);

        verticalLayout_2->setStretch(1, 2);

        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);

        splitter->addWidget(groupBox);
        scrollArea = new QScrollArea(splitter);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1017, 1027));
        verticalLayout_4 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        widget = new QWidget(scrollAreaWidgetContents);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(999, 999));

        verticalLayout_4->addWidget(widget);

        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMaximumSize(QSize(16777215, 4));
        label->setStyleSheet(QLatin1String("QLabel {\n"
"background-color: rgba(255, 255, 255, 255);\n"
"}"));

        verticalLayout_4->addWidget(label);

        scrollArea->setWidget(scrollAreaWidgetContents);
        splitter->addWidget(scrollArea);

        verticalLayout->addWidget(splitter);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btnColor = new QPushButton(bitmapImagePool);
        btnColor->setObjectName(QStringLiteral("btnColor"));

        horizontalLayout->addWidget(btnColor);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        btnClose = new QPushButton(bitmapImagePool);
        btnClose->setObjectName(QStringLiteral("btnClose"));

        horizontalLayout->addWidget(btnClose);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(0, 1);

        retranslateUi(bitmapImagePool);

        QMetaObject::connectSlotsByName(bitmapImagePool);
    } // setupUi

    void retranslateUi(QDialog *bitmapImagePool)
    {
        bitmapImagePool->setWindowTitle(QApplication::translate("bitmapImagePool", "Bitmap", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("bitmapImagePool", "Bitmap List", Q_NULLPTR));
        btnAddBitmap->setText(QApplication::translate("bitmapImagePool", "Add", Q_NULLPTR));
        btnDelBitmap->setText(QApplication::translate("bitmapImagePool", "Del", Q_NULLPTR));
        label->setText(QString());
        btnColor->setText(QApplication::translate("bitmapImagePool", "Background Colour", Q_NULLPTR));
        btnClose->setText(QApplication::translate("bitmapImagePool", "Close", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class bitmapImagePool: public Ui_bitmapImagePool {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BITMAPIMAGEPOOL_H
