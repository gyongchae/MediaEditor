/********************************************************************************
** Form generated from reading UI file 'ledindicatorpool.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEDINDICATORPOOL_H
#define UI_LEDINDICATORPOOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_LEDIndicatorPool
{
public:
    QGridLayout *gridLayout_5;
    QSplitter *splitter_3;
    QSplitter *splitter;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QTableView *m_tblEDDIndicator;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_4;
    QTableView *m_tblETNDIndicator;
    QSplitter *splitter_2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QTableView *m_tblEDDIndex;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QTableView *m_tblEDDIndexList;

    void setupUi(QDialog *LEDIndicatorPool)
    {
        if (LEDIndicatorPool->objectName().isEmpty())
            LEDIndicatorPool->setObjectName(QStringLiteral("LEDIndicatorPool"));
        LEDIndicatorPool->resize(670, 474);
        gridLayout_5 = new QGridLayout(LEDIndicatorPool);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        splitter_3 = new QSplitter(LEDIndicatorPool);
        splitter_3->setObjectName(QStringLiteral("splitter_3"));
        splitter_3->setOrientation(Qt::Vertical);
        splitter = new QSplitter(splitter_3);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        groupBox = new QGroupBox(splitter);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        m_tblEDDIndicator = new QTableView(groupBox);
        m_tblEDDIndicator->setObjectName(QStringLiteral("m_tblEDDIndicator"));

        gridLayout->addWidget(m_tblEDDIndicator, 0, 0, 1, 1);

        splitter->addWidget(groupBox);
        groupBox_4 = new QGroupBox(splitter);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        gridLayout_4 = new QGridLayout(groupBox_4);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        m_tblETNDIndicator = new QTableView(groupBox_4);
        m_tblETNDIndicator->setObjectName(QStringLiteral("m_tblETNDIndicator"));

        gridLayout_4->addWidget(m_tblETNDIndicator, 0, 0, 1, 1);

        splitter->addWidget(groupBox_4);
        splitter_3->addWidget(splitter);
        splitter_2 = new QSplitter(splitter_3);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        groupBox_2 = new QGroupBox(splitter_2);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        m_tblEDDIndex = new QTableView(groupBox_2);
        m_tblEDDIndex->setObjectName(QStringLiteral("m_tblEDDIndex"));

        gridLayout_2->addWidget(m_tblEDDIndex, 0, 0, 1, 1);

        splitter_2->addWidget(groupBox_2);
        groupBox_3 = new QGroupBox(splitter_2);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        m_tblEDDIndexList = new QTableView(groupBox_3);
        m_tblEDDIndexList->setObjectName(QStringLiteral("m_tblEDDIndexList"));

        gridLayout_3->addWidget(m_tblEDDIndexList, 0, 0, 1, 1);

        splitter_2->addWidget(groupBox_3);
        splitter_3->addWidget(splitter_2);

        gridLayout_5->addWidget(splitter_3, 0, 0, 1, 1);


        retranslateUi(LEDIndicatorPool);

        QMetaObject::connectSlotsByName(LEDIndicatorPool);
    } // setupUi

    void retranslateUi(QDialog *LEDIndicatorPool)
    {
        LEDIndicatorPool->setWindowTitle(QApplication::translate("LEDIndicatorPool", "LEDIndicatorPool", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("LEDIndicatorPool", "LED Raw Data", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("LEDIndicatorPool", "LED Raw Data (Number)", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("LEDIndicatorPool", "LED List Name", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("LEDIndicatorPool", "LED Item List", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LEDIndicatorPool: public Ui_LEDIndicatorPool {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEDINDICATORPOOL_H
