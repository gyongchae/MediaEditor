/********************************************************************************
** Form generated from reading UI file 'fontpool.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FONTPOOL_H
#define UI_FONTPOOL_H

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
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_fontPool
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QToolButton *btnAddFont;
    QToolButton *btnDelFont;
    QSpacerItem *horizontalSpacer;
    QTableView *m_tblFontPool;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnClose;

    void setupUi(QDialog *fontPool)
    {
        if (fontPool->objectName().isEmpty())
            fontPool->setObjectName(QStringLiteral("fontPool"));
        fontPool->resize(319, 527);
        verticalLayout_2 = new QVBoxLayout(fontPool);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(fontPool);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btnAddFont = new QToolButton(groupBox);
        btnAddFont->setObjectName(QStringLiteral("btnAddFont"));

        horizontalLayout->addWidget(btnAddFont);

        btnDelFont = new QToolButton(groupBox);
        btnDelFont->setObjectName(QStringLiteral("btnDelFont"));

        horizontalLayout->addWidget(btnDelFont);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        horizontalLayout->setStretch(2, 1);

        verticalLayout->addLayout(horizontalLayout);

        m_tblFontPool = new QTableView(groupBox);
        m_tblFontPool->setObjectName(QStringLiteral("m_tblFontPool"));

        verticalLayout->addWidget(m_tblFontPool);

        verticalLayout->setStretch(1, 1);

        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(118, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        btnClose = new QPushButton(fontPool);
        btnClose->setObjectName(QStringLiteral("btnClose"));

        horizontalLayout_2->addWidget(btnClose);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalLayout_2->setStretch(0, 1);

        retranslateUi(fontPool);

        QMetaObject::connectSlotsByName(fontPool);
    } // setupUi

    void retranslateUi(QDialog *fontPool)
    {
        fontPool->setWindowTitle(QApplication::translate("fontPool", "Font", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("fontPool", "Font List", Q_NULLPTR));
        btnAddFont->setText(QApplication::translate("fontPool", "Add", Q_NULLPTR));
        btnDelFont->setText(QApplication::translate("fontPool", "Del", Q_NULLPTR));
        btnClose->setText(QApplication::translate("fontPool", "Close", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class fontPool: public Ui_fontPool {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FONTPOOL_H
