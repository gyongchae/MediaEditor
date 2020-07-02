/********************************************************************************
** Form generated from reading UI file 'nodePropEdit.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NODEPROPEDIT_H
#define UI_NODEPROPEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include "qindexcombobox.h"

QT_BEGIN_NAMESPACE

class Ui_nodePropEdit
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QDoubleSpinBox *m_ctlX;
    QLabel *label_2;
    QDoubleSpinBox *m_ctlY;
    QLabel *label_3;
    QDoubleSpinBox *m_ctlAngle;
    QLabel *label_5;
    QComboBox *m_cboCenter;
    QLabel *label_4;
    QComboBox *m_cboType;
    QLabel *label_6;
    QIndexComboBox *m_cboIndex;
    QLabel *label_22;
    QIndexComboBox *m_cboImageListIndex;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_4;
    QLabel *label_7;
    QDoubleSpinBox *m_ctlX_2;
    QLabel *label_8;
    QDoubleSpinBox *m_ctlY_2;
    QLabel *label_9;
    QDoubleSpinBox *m_ctlAngle_2;
    QLabel *label_10;
    QComboBox *m_cboCenter_2;
    QLabel *label_11;
    QComboBox *m_cboType_2;
    QLabel *label_12;
    QIndexComboBox *m_cboIndex_2;
    QLabel *label_23;
    QIndexComboBox *m_cboImageListIndex_2;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_6;
    QLabel *label_13;
    QDoubleSpinBox *m_ctlX_3;
    QLabel *label_14;
    QDoubleSpinBox *m_ctlY_3;
    QLabel *label_15;
    QDoubleSpinBox *m_ctlAngle_3;
    QLabel *label_16;
    QComboBox *m_cboCenter_3;
    QLabel *label_17;
    QComboBox *m_cboType_3;
    QLabel *label_18;
    QIndexComboBox *m_cboIndex_3;
    QLabel *label_24;
    QIndexComboBox *m_cboImageListIndex_3;
    QHBoxLayout *horizontalLayout_21;
    QPushButton *btnCopyAll;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_25;
    QIndexComboBox *m_cboStationInformation;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_14;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *nodePropEdit)
    {
        if (nodePropEdit->objectName().isEmpty())
            nodePropEdit->setObjectName(QStringLiteral("nodePropEdit"));
        nodePropEdit->resize(813, 263);
        verticalLayout = new QVBoxLayout(nodePropEdit);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        groupBox = new QGroupBox(nodePropEdit);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        m_ctlX = new QDoubleSpinBox(groupBox);
        m_ctlX->setObjectName(QStringLiteral("m_ctlX"));
        m_ctlX->setDecimals(1);
        m_ctlX->setMinimum(-9999);
        m_ctlX->setMaximum(9999);

        gridLayout->addWidget(m_ctlX, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        m_ctlY = new QDoubleSpinBox(groupBox);
        m_ctlY->setObjectName(QStringLiteral("m_ctlY"));
        m_ctlY->setDecimals(1);
        m_ctlY->setMinimum(-9999);
        m_ctlY->setMaximum(9999);

        gridLayout->addWidget(m_ctlY, 1, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        m_ctlAngle = new QDoubleSpinBox(groupBox);
        m_ctlAngle->setObjectName(QStringLiteral("m_ctlAngle"));
        m_ctlAngle->setDecimals(0);
        m_ctlAngle->setMaximum(360);

        gridLayout->addWidget(m_ctlAngle, 2, 1, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        m_cboCenter = new QComboBox(groupBox);
        m_cboCenter->setObjectName(QStringLiteral("m_cboCenter"));

        gridLayout->addWidget(m_cboCenter, 3, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 4, 0, 1, 1);

        m_cboType = new QComboBox(groupBox);
        m_cboType->setObjectName(QStringLiteral("m_cboType"));

        gridLayout->addWidget(m_cboType, 4, 1, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        m_cboIndex = new QIndexComboBox(groupBox);
        m_cboIndex->setObjectName(QStringLiteral("m_cboIndex"));

        gridLayout->addWidget(m_cboIndex, 5, 1, 1, 1);

        label_22 = new QLabel(groupBox);
        label_22->setObjectName(QStringLiteral("label_22"));

        gridLayout->addWidget(label_22, 6, 0, 1, 1);

        m_cboImageListIndex = new QIndexComboBox(groupBox);
        m_cboImageListIndex->setObjectName(QStringLiteral("m_cboImageListIndex"));

        gridLayout->addWidget(m_cboImageListIndex, 6, 1, 1, 1);

        gridLayout->setColumnStretch(1, 1);

        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        horizontalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(nodePropEdit);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_4->addWidget(label_7, 0, 0, 1, 1);

        m_ctlX_2 = new QDoubleSpinBox(groupBox_2);
        m_ctlX_2->setObjectName(QStringLiteral("m_ctlX_2"));
        m_ctlX_2->setDecimals(1);
        m_ctlX_2->setMinimum(-9999);
        m_ctlX_2->setMaximum(9999);

        gridLayout_4->addWidget(m_ctlX_2, 0, 1, 1, 1);

        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_4->addWidget(label_8, 1, 0, 1, 1);

        m_ctlY_2 = new QDoubleSpinBox(groupBox_2);
        m_ctlY_2->setObjectName(QStringLiteral("m_ctlY_2"));
        m_ctlY_2->setDecimals(1);
        m_ctlY_2->setMinimum(-9999);
        m_ctlY_2->setMaximum(9999);

        gridLayout_4->addWidget(m_ctlY_2, 1, 1, 1, 1);

        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_4->addWidget(label_9, 2, 0, 1, 1);

        m_ctlAngle_2 = new QDoubleSpinBox(groupBox_2);
        m_ctlAngle_2->setObjectName(QStringLiteral("m_ctlAngle_2"));
        m_ctlAngle_2->setDecimals(0);
        m_ctlAngle_2->setMaximum(360);

        gridLayout_4->addWidget(m_ctlAngle_2, 2, 1, 1, 1);

        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_4->addWidget(label_10, 3, 0, 1, 1);

        m_cboCenter_2 = new QComboBox(groupBox_2);
        m_cboCenter_2->setObjectName(QStringLiteral("m_cboCenter_2"));

        gridLayout_4->addWidget(m_cboCenter_2, 3, 1, 1, 1);

        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_4->addWidget(label_11, 4, 0, 1, 1);

        m_cboType_2 = new QComboBox(groupBox_2);
        m_cboType_2->setObjectName(QStringLiteral("m_cboType_2"));

        gridLayout_4->addWidget(m_cboType_2, 4, 1, 1, 1);

        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_4->addWidget(label_12, 5, 0, 1, 1);

        m_cboIndex_2 = new QIndexComboBox(groupBox_2);
        m_cboIndex_2->setObjectName(QStringLiteral("m_cboIndex_2"));

        gridLayout_4->addWidget(m_cboIndex_2, 5, 1, 1, 1);

        label_23 = new QLabel(groupBox_2);
        label_23->setObjectName(QStringLiteral("label_23"));

        gridLayout_4->addWidget(label_23, 6, 0, 1, 1);

        m_cboImageListIndex_2 = new QIndexComboBox(groupBox_2);
        m_cboImageListIndex_2->setObjectName(QStringLiteral("m_cboImageListIndex_2"));

        gridLayout_4->addWidget(m_cboImageListIndex_2, 6, 1, 1, 1);

        gridLayout_4->setColumnStretch(1, 1);

        gridLayout_3->addLayout(gridLayout_4, 0, 0, 1, 1);


        horizontalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(nodePropEdit);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_5 = new QGridLayout(groupBox_3);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setSpacing(6);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        label_13 = new QLabel(groupBox_3);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_6->addWidget(label_13, 0, 0, 1, 1);

        m_ctlX_3 = new QDoubleSpinBox(groupBox_3);
        m_ctlX_3->setObjectName(QStringLiteral("m_ctlX_3"));
        m_ctlX_3->setDecimals(1);
        m_ctlX_3->setMinimum(-9999);
        m_ctlX_3->setMaximum(9999);

        gridLayout_6->addWidget(m_ctlX_3, 0, 1, 1, 1);

        label_14 = new QLabel(groupBox_3);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout_6->addWidget(label_14, 1, 0, 1, 1);

        m_ctlY_3 = new QDoubleSpinBox(groupBox_3);
        m_ctlY_3->setObjectName(QStringLiteral("m_ctlY_3"));
        m_ctlY_3->setDecimals(1);
        m_ctlY_3->setMinimum(-9999);
        m_ctlY_3->setMaximum(9999);

        gridLayout_6->addWidget(m_ctlY_3, 1, 1, 1, 1);

        label_15 = new QLabel(groupBox_3);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout_6->addWidget(label_15, 2, 0, 1, 1);

        m_ctlAngle_3 = new QDoubleSpinBox(groupBox_3);
        m_ctlAngle_3->setObjectName(QStringLiteral("m_ctlAngle_3"));
        m_ctlAngle_3->setDecimals(0);
        m_ctlAngle_3->setMaximum(360);

        gridLayout_6->addWidget(m_ctlAngle_3, 2, 1, 1, 1);

        label_16 = new QLabel(groupBox_3);
        label_16->setObjectName(QStringLiteral("label_16"));

        gridLayout_6->addWidget(label_16, 3, 0, 1, 1);

        m_cboCenter_3 = new QComboBox(groupBox_3);
        m_cboCenter_3->setObjectName(QStringLiteral("m_cboCenter_3"));

        gridLayout_6->addWidget(m_cboCenter_3, 3, 1, 1, 1);

        label_17 = new QLabel(groupBox_3);
        label_17->setObjectName(QStringLiteral("label_17"));

        gridLayout_6->addWidget(label_17, 4, 0, 1, 1);

        m_cboType_3 = new QComboBox(groupBox_3);
        m_cboType_3->setObjectName(QStringLiteral("m_cboType_3"));

        gridLayout_6->addWidget(m_cboType_3, 4, 1, 1, 1);

        label_18 = new QLabel(groupBox_3);
        label_18->setObjectName(QStringLiteral("label_18"));

        gridLayout_6->addWidget(label_18, 5, 0, 1, 1);

        m_cboIndex_3 = new QIndexComboBox(groupBox_3);
        m_cboIndex_3->setObjectName(QStringLiteral("m_cboIndex_3"));

        gridLayout_6->addWidget(m_cboIndex_3, 5, 1, 1, 1);

        label_24 = new QLabel(groupBox_3);
        label_24->setObjectName(QStringLiteral("label_24"));

        gridLayout_6->addWidget(label_24, 6, 0, 1, 1);

        m_cboImageListIndex_3 = new QIndexComboBox(groupBox_3);
        m_cboImageListIndex_3->setObjectName(QStringLiteral("m_cboImageListIndex_3"));

        gridLayout_6->addWidget(m_cboImageListIndex_3, 6, 1, 1, 1);

        gridLayout_6->setColumnStretch(1, 1);

        gridLayout_5->addLayout(gridLayout_6, 0, 0, 1, 1);


        horizontalLayout->addWidget(groupBox_3);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setObjectName(QStringLiteral("horizontalLayout_21"));
        btnCopyAll = new QPushButton(nodePropEdit);
        btnCopyAll->setObjectName(QStringLiteral("btnCopyAll"));

        horizontalLayout_21->addWidget(btnCopyAll);

        horizontalSpacer_3 = new QSpacerItem(37, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_21->addItem(horizontalSpacer_3);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_25 = new QLabel(nodePropEdit);
        label_25->setObjectName(QStringLiteral("label_25"));

        horizontalLayout_7->addWidget(label_25);

        m_cboStationInformation = new QIndexComboBox(nodePropEdit);
        m_cboStationInformation->setObjectName(QStringLiteral("m_cboStationInformation"));

        horizontalLayout_7->addWidget(m_cboStationInformation);

        pushButton = new QPushButton(nodePropEdit);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_7->addWidget(pushButton);

        horizontalLayout_7->setStretch(1, 1);

        horizontalLayout_21->addLayout(horizontalLayout_7);

        horizontalSpacer_2 = new QSpacerItem(37, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_21->addItem(horizontalSpacer_2);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer);

        buttonBox = new QDialogButtonBox(nodePropEdit);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_14->addWidget(buttonBox);


        horizontalLayout_21->addLayout(horizontalLayout_14);

        horizontalLayout_21->setStretch(2, 2);
        horizontalLayout_21->setStretch(3, 1);

        verticalLayout->addLayout(horizontalLayout_21);

        verticalLayout->setStretch(0, 1);

        retranslateUi(nodePropEdit);

        QMetaObject::connectSlotsByName(nodePropEdit);
    } // setupUi

    void retranslateUi(QDialog *nodePropEdit)
    {
        nodePropEdit->setWindowTitle(QApplication::translate("nodePropEdit", "nodePropEdit", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("nodePropEdit", "Passed Station", Q_NULLPTR));
        label->setText(QApplication::translate("nodePropEdit", "Pos X", Q_NULLPTR));
        label_2->setText(QApplication::translate("nodePropEdit", "Pos Y", Q_NULLPTR));
        label_3->setText(QApplication::translate("nodePropEdit", "Angle", Q_NULLPTR));
        label_5->setText(QApplication::translate("nodePropEdit", "Pivot Point", Q_NULLPTR));
        label_4->setText(QApplication::translate("nodePropEdit", "Item Type", Q_NULLPTR));
        label_6->setText(QApplication::translate("nodePropEdit", "Display Pool Index", Q_NULLPTR));
        label_22->setText(QApplication::translate("nodePropEdit", "Image List Pool Index", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("nodePropEdit", "Target Station", Q_NULLPTR));
        label_7->setText(QApplication::translate("nodePropEdit", "Pos X", Q_NULLPTR));
        label_8->setText(QApplication::translate("nodePropEdit", "Pos Y", Q_NULLPTR));
        label_9->setText(QApplication::translate("nodePropEdit", "Angle", Q_NULLPTR));
        label_10->setText(QApplication::translate("nodePropEdit", "Pivot Point", Q_NULLPTR));
        label_11->setText(QApplication::translate("nodePropEdit", "Item Type", Q_NULLPTR));
        label_12->setText(QApplication::translate("nodePropEdit", "Display Pool Index", Q_NULLPTR));
        label_23->setText(QApplication::translate("nodePropEdit", "Image List Pool Index", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("nodePropEdit", "Remain Station", Q_NULLPTR));
        label_13->setText(QApplication::translate("nodePropEdit", "Pos X", Q_NULLPTR));
        label_14->setText(QApplication::translate("nodePropEdit", "Pos Y", Q_NULLPTR));
        label_15->setText(QApplication::translate("nodePropEdit", "Angle", Q_NULLPTR));
        label_16->setText(QApplication::translate("nodePropEdit", "Pivot Point", Q_NULLPTR));
        label_17->setText(QApplication::translate("nodePropEdit", "Item Type", Q_NULLPTR));
        label_18->setText(QApplication::translate("nodePropEdit", "Display Pool Index", Q_NULLPTR));
        label_24->setText(QApplication::translate("nodePropEdit", "Image List Pool Index", Q_NULLPTR));
        btnCopyAll->setText(QApplication::translate("nodePropEdit", "Copy All", Q_NULLPTR));
        label_25->setText(QApplication::translate("nodePropEdit", "Related Station", Q_NULLPTR));
        pushButton->setText(QApplication::translate("nodePropEdit", "Apply", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class nodePropEdit: public Ui_nodePropEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NODEPROPEDIT_H
