/********************************************************************************
** Form generated from reading UI file 'linemappooledit.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LINEMAPPOOLEDIT_H
#define UI_LINEMAPPOOLEDIT_H

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
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LineMapPoolEdit
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnAddMap;
    QPushButton *btnDelMap;
    QSpacerItem *horizontalSpacer;
    QTableView *m_tblLineMapPool;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnClose;

    void setupUi(QDialog *LineMapPoolEdit)
    {
        if (LineMapPoolEdit->objectName().isEmpty())
            LineMapPoolEdit->setObjectName(QStringLiteral("LineMapPoolEdit"));
        LineMapPoolEdit->resize(599, 542);
        verticalLayout_2 = new QVBoxLayout(LineMapPoolEdit);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(LineMapPoolEdit);
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
        btnAddMap = new QPushButton(groupBox);
        btnAddMap->setObjectName(QStringLiteral("btnAddMap"));

        horizontalLayout_2->addWidget(btnAddMap);

        btnDelMap = new QPushButton(groupBox);
        btnDelMap->setObjectName(QStringLiteral("btnDelMap"));

        horizontalLayout_2->addWidget(btnDelMap);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        m_tblLineMapPool = new QTableView(groupBox);
        m_tblLineMapPool->setObjectName(QStringLiteral("m_tblLineMapPool"));

        verticalLayout->addWidget(m_tblLineMapPool);

        verticalLayout->setStretch(1, 1);

        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        btnClose = new QPushButton(LineMapPoolEdit);
        btnClose->setObjectName(QStringLiteral("btnClose"));

        horizontalLayout->addWidget(btnClose);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout_2->setStretch(0, 1);

        retranslateUi(LineMapPoolEdit);

        QMetaObject::connectSlotsByName(LineMapPoolEdit);
    } // setupUi

    void retranslateUi(QDialog *LineMapPoolEdit)
    {
        LineMapPoolEdit->setWindowTitle(QApplication::translate("LineMapPoolEdit", "Route Map", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("LineMapPoolEdit", "Route Map List", Q_NULLPTR));
        btnAddMap->setText(QApplication::translate("LineMapPoolEdit", "Add", Q_NULLPTR));
        btnDelMap->setText(QApplication::translate("LineMapPoolEdit", "Del", Q_NULLPTR));
        btnClose->setText(QApplication::translate("LineMapPoolEdit", "Close", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LineMapPoolEdit: public Ui_LineMapPoolEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LINEMAPPOOLEDIT_H
