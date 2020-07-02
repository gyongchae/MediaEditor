/********************************************************************************
** Form generated from reading UI file 'editDisplayItemPool.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITDISPLAYITEMPOOL_H
#define UI_EDITDISPLAYITEMPOOL_H

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

class Ui_editDisplayItemPool
{
public:
    QVBoxLayout *verticalLayout_2;
    QSplitter *splitter;
    QGroupBox *gbDispItemList;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnAddDisplayPool;
    QPushButton *btnDelDisplayPool;
    QSpacerItem *horizontalSpacer;
    QTableView *m_tblDisplayItemPool;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnClose;

    void setupUi(QDialog *editDisplayItemPool)
    {
        if (editDisplayItemPool->objectName().isEmpty())
            editDisplayItemPool->setObjectName(QStringLiteral("editDisplayItemPool"));
        editDisplayItemPool->resize(418, 463);
        verticalLayout_2 = new QVBoxLayout(editDisplayItemPool);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        splitter = new QSplitter(editDisplayItemPool);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        gbDispItemList = new QGroupBox(splitter);
        gbDispItemList->setObjectName(QStringLiteral("gbDispItemList"));
        gridLayout_2 = new QGridLayout(gbDispItemList);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        btnAddDisplayPool = new QPushButton(gbDispItemList);
        btnAddDisplayPool->setObjectName(QStringLiteral("btnAddDisplayPool"));

        horizontalLayout_2->addWidget(btnAddDisplayPool);

        btnDelDisplayPool = new QPushButton(gbDispItemList);
        btnDelDisplayPool->setObjectName(QStringLiteral("btnDelDisplayPool"));

        horizontalLayout_2->addWidget(btnDelDisplayPool);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        m_tblDisplayItemPool = new QTableView(gbDispItemList);
        m_tblDisplayItemPool->setObjectName(QStringLiteral("m_tblDisplayItemPool"));

        verticalLayout->addWidget(m_tblDisplayItemPool);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);

        splitter->addWidget(gbDispItemList);

        verticalLayout_2->addWidget(splitter);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        btnClose = new QPushButton(editDisplayItemPool);
        btnClose->setObjectName(QStringLiteral("btnClose"));

        horizontalLayout->addWidget(btnClose);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout_2->setStretch(0, 1);

        retranslateUi(editDisplayItemPool);

        QMetaObject::connectSlotsByName(editDisplayItemPool);
    } // setupUi

    void retranslateUi(QDialog *editDisplayItemPool)
    {
        editDisplayItemPool->setWindowTitle(QApplication::translate("editDisplayItemPool", "DRMD & PID", Q_NULLPTR));
        gbDispItemList->setTitle(QApplication::translate("editDisplayItemPool", "Display Item List", Q_NULLPTR));
        btnAddDisplayPool->setText(QApplication::translate("editDisplayItemPool", "Add", Q_NULLPTR));
        btnDelDisplayPool->setText(QApplication::translate("editDisplayItemPool", "Del", Q_NULLPTR));
        btnClose->setText(QApplication::translate("editDisplayItemPool", "Close", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class editDisplayItemPool: public Ui_editDisplayItemPool {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITDISPLAYITEMPOOL_H
