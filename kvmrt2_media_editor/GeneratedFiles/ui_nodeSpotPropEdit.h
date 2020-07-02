/********************************************************************************
** Form generated from reading UI file 'nodeSpotPropEdit.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NODESPOTPROPEDIT_H
#define UI_NODESPOTPROPEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include "qindexcombobox.h"

QT_BEGIN_NAMESPACE

class Ui_nodeSpotPropEdit
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QDoubleSpinBox *m_ctlX;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QDoubleSpinBox *m_ctlY;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QComboBox *m_cboType;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QComboBox *m_cboCenter;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_6;
    QIndexComboBox *m_cboIndex;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_22;
    QIndexComboBox *m_cboImageListIndex;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QCheckBox *m_ckColoring;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_8;
    QDoubleSpinBox *m_ctlX_2;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_9;
    QDoubleSpinBox *m_ctlY_2;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_10;
    QComboBox *m_cboType_2;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_12;
    QComboBox *m_cboCenter_2;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_13;
    QIndexComboBox *m_cboIndex_2;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_23;
    QIndexComboBox *m_cboImageListIndex_2;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_14;
    QCheckBox *m_ckColoring_2;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_15;
    QDoubleSpinBox *m_ctlX_3;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_16;
    QDoubleSpinBox *m_ctlY_3;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_11;
    QComboBox *m_cboType_3;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_19;
    QComboBox *m_cboCenter_3;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_20;
    QIndexComboBox *m_cboIndex_3;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_24;
    QIndexComboBox *m_cboImageListIndex_3;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_21;
    QCheckBox *m_ckColoring_3;
    QHBoxLayout *horizontalLayout_22;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *nodeSpotPropEdit)
    {
        if (nodeSpotPropEdit->objectName().isEmpty())
            nodeSpotPropEdit->setObjectName(QStringLiteral("nodeSpotPropEdit"));
        nodeSpotPropEdit->resize(812, 296);
        gridLayout = new QGridLayout(nodeSpotPropEdit);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox = new QGroupBox(nodeSpotPropEdit);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        m_ctlX = new QDoubleSpinBox(groupBox);
        m_ctlX->setObjectName(QStringLiteral("m_ctlX"));

        horizontalLayout->addWidget(m_ctlX);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        m_ctlY = new QDoubleSpinBox(groupBox);
        m_ctlY->setObjectName(QStringLiteral("m_ctlY"));

        horizontalLayout_2->addWidget(m_ctlY);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_5->addWidget(label_4);

        m_cboType = new QComboBox(groupBox);
        m_cboType->setObjectName(QStringLiteral("m_cboType"));

        horizontalLayout_5->addWidget(m_cboType);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_4->addWidget(label_5);

        m_cboCenter = new QComboBox(groupBox);
        m_cboCenter->setObjectName(QStringLiteral("m_cboCenter"));

        horizontalLayout_4->addWidget(m_cboCenter);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setSpacing(6);
        horizontalLayout_23->setObjectName(QStringLiteral("horizontalLayout_23"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_23->addWidget(label_6);

        m_cboIndex = new QIndexComboBox(groupBox);
        m_cboIndex->setObjectName(QStringLiteral("m_cboIndex"));

        horizontalLayout_23->addWidget(m_cboIndex);


        verticalLayout_3->addLayout(horizontalLayout_23);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_22 = new QLabel(groupBox);
        label_22->setObjectName(QStringLiteral("label_22"));

        horizontalLayout_11->addWidget(label_22);

        m_cboImageListIndex = new QIndexComboBox(groupBox);
        m_cboImageListIndex->setObjectName(QStringLiteral("m_cboImageListIndex"));

        horizontalLayout_11->addWidget(m_cboImageListIndex);


        verticalLayout_3->addLayout(horizontalLayout_11);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_7->addWidget(label_7);

        m_ckColoring = new QCheckBox(groupBox);
        m_ckColoring->setObjectName(QStringLiteral("m_ckColoring"));

        horizontalLayout_7->addWidget(m_ckColoring);


        verticalLayout_3->addLayout(horizontalLayout_7);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(nodeSpotPropEdit);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_8->addWidget(label_8);

        m_ctlX_2 = new QDoubleSpinBox(groupBox_2);
        m_ctlX_2->setObjectName(QStringLiteral("m_ctlX_2"));

        horizontalLayout_8->addWidget(m_ctlX_2);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_9->addWidget(label_9);

        m_ctlY_2 = new QDoubleSpinBox(groupBox_2);
        m_ctlY_2->setObjectName(QStringLiteral("m_ctlY_2"));

        horizontalLayout_9->addWidget(m_ctlY_2);


        verticalLayout_2->addLayout(horizontalLayout_9);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_6->addWidget(label_10);

        m_cboType_2 = new QComboBox(groupBox_2);
        m_cboType_2->setObjectName(QStringLiteral("m_cboType_2"));

        horizontalLayout_6->addWidget(m_cboType_2);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_12->addWidget(label_12);

        m_cboCenter_2 = new QComboBox(groupBox_2);
        m_cboCenter_2->setObjectName(QStringLiteral("m_cboCenter_2"));

        horizontalLayout_12->addWidget(m_cboCenter_2);


        verticalLayout_2->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QStringLiteral("label_13"));

        horizontalLayout_13->addWidget(label_13);

        m_cboIndex_2 = new QIndexComboBox(groupBox_2);
        m_cboIndex_2->setObjectName(QStringLiteral("m_cboIndex_2"));

        horizontalLayout_13->addWidget(m_cboIndex_2);


        verticalLayout_2->addLayout(horizontalLayout_13);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        label_23 = new QLabel(groupBox_2);
        label_23->setObjectName(QStringLiteral("label_23"));

        horizontalLayout_17->addWidget(label_23);

        m_cboImageListIndex_2 = new QIndexComboBox(groupBox_2);
        m_cboImageListIndex_2->setObjectName(QStringLiteral("m_cboImageListIndex_2"));

        horizontalLayout_17->addWidget(m_cboImageListIndex_2);


        verticalLayout_2->addLayout(horizontalLayout_17);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName(QStringLiteral("label_14"));

        horizontalLayout_14->addWidget(label_14);

        m_ckColoring_2 = new QCheckBox(groupBox_2);
        m_ckColoring_2->setObjectName(QStringLiteral("m_ckColoring_2"));

        horizontalLayout_14->addWidget(m_ckColoring_2);


        verticalLayout_2->addLayout(horizontalLayout_14);


        gridLayout->addWidget(groupBox_2, 0, 1, 1, 1);

        groupBox_3 = new QGroupBox(nodeSpotPropEdit);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout = new QVBoxLayout(groupBox_3);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        label_15 = new QLabel(groupBox_3);
        label_15->setObjectName(QStringLiteral("label_15"));

        horizontalLayout_15->addWidget(label_15);

        m_ctlX_3 = new QDoubleSpinBox(groupBox_3);
        m_ctlX_3->setObjectName(QStringLiteral("m_ctlX_3"));

        horizontalLayout_15->addWidget(m_ctlX_3);


        verticalLayout->addLayout(horizontalLayout_15);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        label_16 = new QLabel(groupBox_3);
        label_16->setObjectName(QStringLiteral("label_16"));

        horizontalLayout_16->addWidget(label_16);

        m_ctlY_3 = new QDoubleSpinBox(groupBox_3);
        m_ctlY_3->setObjectName(QStringLiteral("m_ctlY_3"));

        horizontalLayout_16->addWidget(m_ctlY_3);


        verticalLayout->addLayout(horizontalLayout_16);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_11 = new QLabel(groupBox_3);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_10->addWidget(label_11);

        m_cboType_3 = new QComboBox(groupBox_3);
        m_cboType_3->setObjectName(QStringLiteral("m_cboType_3"));

        horizontalLayout_10->addWidget(m_cboType_3);


        verticalLayout->addLayout(horizontalLayout_10);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
        label_19 = new QLabel(groupBox_3);
        label_19->setObjectName(QStringLiteral("label_19"));

        horizontalLayout_19->addWidget(label_19);

        m_cboCenter_3 = new QComboBox(groupBox_3);
        m_cboCenter_3->setObjectName(QStringLiteral("m_cboCenter_3"));

        horizontalLayout_19->addWidget(m_cboCenter_3);


        verticalLayout->addLayout(horizontalLayout_19);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
        label_20 = new QLabel(groupBox_3);
        label_20->setObjectName(QStringLiteral("label_20"));

        horizontalLayout_20->addWidget(label_20);

        m_cboIndex_3 = new QIndexComboBox(groupBox_3);
        m_cboIndex_3->setObjectName(QStringLiteral("m_cboIndex_3"));

        horizontalLayout_20->addWidget(m_cboIndex_3);


        verticalLayout->addLayout(horizontalLayout_20);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        label_24 = new QLabel(groupBox_3);
        label_24->setObjectName(QStringLiteral("label_24"));

        horizontalLayout_18->addWidget(label_24);

        m_cboImageListIndex_3 = new QIndexComboBox(groupBox_3);
        m_cboImageListIndex_3->setObjectName(QStringLiteral("m_cboImageListIndex_3"));

        horizontalLayout_18->addWidget(m_cboImageListIndex_3);


        verticalLayout->addLayout(horizontalLayout_18);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setObjectName(QStringLiteral("horizontalLayout_21"));
        label_21 = new QLabel(groupBox_3);
        label_21->setObjectName(QStringLiteral("label_21"));

        horizontalLayout_21->addWidget(label_21);

        m_ckColoring_3 = new QCheckBox(groupBox_3);
        m_ckColoring_3->setObjectName(QStringLiteral("m_ckColoring_3"));

        horizontalLayout_21->addWidget(m_ckColoring_3);


        verticalLayout->addLayout(horizontalLayout_21);


        gridLayout->addWidget(groupBox_3, 0, 2, 1, 1);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setSpacing(6);
        horizontalLayout_22->setObjectName(QStringLiteral("horizontalLayout_22"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_22->addItem(horizontalSpacer);

        buttonBox = new QDialogButtonBox(nodeSpotPropEdit);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_22->addWidget(buttonBox);


        gridLayout->addLayout(horizontalLayout_22, 1, 0, 1, 3);


        retranslateUi(nodeSpotPropEdit);

        QMetaObject::connectSlotsByName(nodeSpotPropEdit);
    } // setupUi

    void retranslateUi(QDialog *nodeSpotPropEdit)
    {
        nodeSpotPropEdit->setWindowTitle(QApplication::translate("nodeSpotPropEdit", "nodeSpotPropEdit", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("nodeSpotPropEdit", "When this station passed", Q_NULLPTR));
        label->setText(QApplication::translate("nodeSpotPropEdit", "Offset from origin X", Q_NULLPTR));
        label_2->setText(QApplication::translate("nodeSpotPropEdit", "Offset from origin Y", Q_NULLPTR));
        label_4->setText(QApplication::translate("nodeSpotPropEdit", "Type", Q_NULLPTR));
        label_5->setText(QApplication::translate("nodeSpotPropEdit", "Pivot Point", Q_NULLPTR));
        label_6->setText(QApplication::translate("nodeSpotPropEdit", "DisplayItem index", Q_NULLPTR));
        label_22->setText(QApplication::translate("nodeSpotPropEdit", "ImageList index", Q_NULLPTR));
        label_7->setText(QApplication::translate("nodeSpotPropEdit", "Color", Q_NULLPTR));
        m_ckColoring->setText(QString());
        groupBox_2->setTitle(QApplication::translate("nodeSpotPropEdit", "When this station focused", Q_NULLPTR));
        label_8->setText(QApplication::translate("nodeSpotPropEdit", "Offset from origin X", Q_NULLPTR));
        label_9->setText(QApplication::translate("nodeSpotPropEdit", "Offset from origin Y", Q_NULLPTR));
        label_10->setText(QApplication::translate("nodeSpotPropEdit", "Type", Q_NULLPTR));
        label_12->setText(QApplication::translate("nodeSpotPropEdit", "Pivot Point", Q_NULLPTR));
        label_13->setText(QApplication::translate("nodeSpotPropEdit", "DisplayItem index", Q_NULLPTR));
        label_23->setText(QApplication::translate("nodeSpotPropEdit", "ImageList index", Q_NULLPTR));
        label_14->setText(QApplication::translate("nodeSpotPropEdit", "Color", Q_NULLPTR));
        m_ckColoring_2->setText(QString());
        groupBox_3->setTitle(QApplication::translate("nodeSpotPropEdit", "When this station is left to go", Q_NULLPTR));
        label_15->setText(QApplication::translate("nodeSpotPropEdit", "Offset from origin X", Q_NULLPTR));
        label_16->setText(QApplication::translate("nodeSpotPropEdit", "Offset from origin Y", Q_NULLPTR));
        label_11->setText(QApplication::translate("nodeSpotPropEdit", "Type", Q_NULLPTR));
        label_19->setText(QApplication::translate("nodeSpotPropEdit", "Pivot Point", Q_NULLPTR));
        label_20->setText(QApplication::translate("nodeSpotPropEdit", "DisplayItem index", Q_NULLPTR));
        label_24->setText(QApplication::translate("nodeSpotPropEdit", "ImageList index", Q_NULLPTR));
        label_21->setText(QApplication::translate("nodeSpotPropEdit", "Color", Q_NULLPTR));
        m_ckColoring_3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class nodeSpotPropEdit: public Ui_nodeSpotPropEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NODESPOTPROPEDIT_H
