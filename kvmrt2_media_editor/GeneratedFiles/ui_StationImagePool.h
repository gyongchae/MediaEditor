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

class Ui_stationImagePool
{
public:
    QVBoxLayout *verticalLayout_3;
    QSplitter *splitter;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnAddText;
    QPushButton *btnDelText;
    QSpacerItem *horizontalSpacer;
    QTableView *m_tblStationImagePool;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnColor;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnClose;

    void setupUi(QDialog *stationImagePool)
    {
        if (stationImagePool->objectName().isEmpty())
            stationImagePool->setObjectName(QStringLiteral("stationImagePool"));
        stationImagePool->resize(946, 581);
        verticalLayout_3 = new QVBoxLayout(stationImagePool);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        splitter = new QSplitter(stationImagePool);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        groupBox = new QGroupBox(splitter);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
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


        verticalLayout_2->addLayout(horizontalLayout);

        m_tblStationImagePool = new QTableView(groupBox);
        m_tblStationImagePool->setObjectName(QStringLiteral("m_tblStationImagePool"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_tblStationImagePool->sizePolicy().hasHeightForWidth());
        m_tblStationImagePool->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(m_tblStationImagePool);

        verticalLayout_2->setStretch(1, 1);
        splitter->addWidget(groupBox);
        scrollArea = new QScrollArea(splitter);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1017, 1027));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget = new QWidget(scrollAreaWidgetContents);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(999, 999));

        verticalLayout->addWidget(widget);

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

        verticalLayout->addWidget(label);

        scrollArea->setWidget(scrollAreaWidgetContents);
        splitter->addWidget(scrollArea);

        verticalLayout_3->addWidget(splitter);

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


        verticalLayout_3->addLayout(horizontalLayout_2);


        retranslateUi(stationImagePool);

        QMetaObject::connectSlotsByName(stationImagePool);
    } // setupUi

    void retranslateUi(QDialog *stationImagePool)
    {
        stationImagePool->setWindowTitle(QApplication::translate("stationImagePool", "Text", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("stationImagePool", "Text List", Q_NULLPTR));
        btnAddText->setText(QApplication::translate("stationImagePool", "Add", Q_NULLPTR));
        btnDelText->setText(QApplication::translate("stationImagePool", "Del", Q_NULLPTR));
        label->setText(QString());
        btnColor->setText(QApplication::translate("stationImagePool", "Background Colour", Q_NULLPTR));
        btnClose->setText(QApplication::translate("stationImagePool", "Close", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class stationImagePool: public Ui_stationImagePool {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATIONIMAGEPOOL_H
