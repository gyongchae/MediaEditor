/********************************************************************************
** Form generated from reading UI file 'editDisplayMetaItem.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITDISPLAYMETAITEM_H
#define UI_EDITDISPLAYMETAITEM_H

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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <qindexcombobox.h>
#include "qcolorpickerpushbutton.h"

QT_BEGIN_NAMESPACE

class Ui_editDisplayMetaItem
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QIndexComboBox *m_cboEditorTag;
    QPushButton *m_pbTagApply;
    QIndexComboBox *m_cboImageListIndex;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_9;
    QComboBox *m_cboCenter;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QDoubleSpinBox *m_ctlX;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QDoubleSpinBox *m_ctlY;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_12;
    QComboBox *m_cboEasing;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QDoubleSpinBox *m_ctlAngle;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_13;
    QComboBox *m_cboEasing_2;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QDoubleSpinBox *m_ctlHeight;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_8;
    QDoubleSpinBox *m_ctlWidth;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QColorPickerPushButton *m_ctlImageColor;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_14;
    QComboBox *m_cboEasing_3;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_11;
    QComboBox *m_cboHA;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_10;
    QComboBox *m_cboVA;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QSpinBox *m_ctlZOrder;
    QHBoxLayout *horizontalLayout_15;
    QCheckBox *m_cbLimitBound;
    QCheckBox *m_cbVisible;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *editDisplayMetaItem)
    {
        if (editDisplayMetaItem->objectName().isEmpty())
            editDisplayMetaItem->setObjectName(QStringLiteral("editDisplayMetaItem"));
        editDisplayMetaItem->resize(391, 591);
        gridLayout = new QGridLayout(editDisplayMetaItem);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(editDisplayMetaItem);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        m_cboEditorTag = new QIndexComboBox(editDisplayMetaItem);
        m_cboEditorTag->setObjectName(QStringLiteral("m_cboEditorTag"));

        horizontalLayout_4->addWidget(m_cboEditorTag);

        m_pbTagApply = new QPushButton(editDisplayMetaItem);
        m_pbTagApply->setObjectName(QStringLiteral("m_pbTagApply"));

        horizontalLayout_4->addWidget(m_pbTagApply);

        m_cboImageListIndex = new QIndexComboBox(editDisplayMetaItem);
        m_cboImageListIndex->setObjectName(QStringLiteral("m_cboImageListIndex"));

        horizontalLayout_4->addWidget(m_cboImageListIndex);


        gridLayout->addLayout(horizontalLayout_4, 0, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_9 = new QLabel(editDisplayMetaItem);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_9->addWidget(label_9);

        m_cboCenter = new QComboBox(editDisplayMetaItem);
        m_cboCenter->setObjectName(QStringLiteral("m_cboCenter"));

        horizontalLayout_9->addWidget(m_cboCenter);


        gridLayout->addLayout(horizontalLayout_9, 1, 0, 1, 1);

        groupBox = new QGroupBox(editDisplayMetaItem);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        m_ctlX = new QDoubleSpinBox(groupBox);
        m_ctlX->setObjectName(QStringLiteral("m_ctlX"));

        horizontalLayout->addWidget(m_ctlX);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        m_ctlY = new QDoubleSpinBox(groupBox);
        m_ctlY->setObjectName(QStringLiteral("m_ctlY"));

        horizontalLayout_2->addWidget(m_ctlY);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_12->addWidget(label_12);

        m_cboEasing = new QComboBox(groupBox);
        m_cboEasing->setObjectName(QStringLiteral("m_cboEasing"));

        horizontalLayout_12->addWidget(m_cboEasing);


        verticalLayout_2->addLayout(horizontalLayout_12);


        gridLayout->addWidget(groupBox, 2, 0, 1, 1);

        groupBox_2 = new QGroupBox(editDisplayMetaItem);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        m_ctlAngle = new QDoubleSpinBox(groupBox_2);
        m_ctlAngle->setObjectName(QStringLiteral("m_ctlAngle"));

        horizontalLayout_3->addWidget(m_ctlAngle);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QStringLiteral("label_13"));

        horizontalLayout_13->addWidget(label_13);

        m_cboEasing_2 = new QComboBox(groupBox_2);
        m_cboEasing_2->setObjectName(QStringLiteral("m_cboEasing_2"));

        horizontalLayout_13->addWidget(m_cboEasing_2);


        verticalLayout_3->addLayout(horizontalLayout_13);


        gridLayout->addWidget(groupBox_2, 3, 0, 1, 1);

        groupBox_4 = new QGroupBox(editDisplayMetaItem);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        verticalLayout = new QVBoxLayout(groupBox_4);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(groupBox_4);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_5->addWidget(label_5);

        m_ctlHeight = new QDoubleSpinBox(groupBox_4);
        m_ctlHeight->setObjectName(QStringLiteral("m_ctlHeight"));

        horizontalLayout_5->addWidget(m_ctlHeight);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_8->addWidget(label_8);

        m_ctlWidth = new QDoubleSpinBox(groupBox_4);
        m_ctlWidth->setObjectName(QStringLiteral("m_ctlWidth"));

        horizontalLayout_8->addWidget(m_ctlWidth);


        verticalLayout->addLayout(horizontalLayout_8);


        gridLayout->addWidget(groupBox_4, 4, 0, 1, 1);

        groupBox_3 = new QGroupBox(editDisplayMetaItem);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout_4 = new QVBoxLayout(groupBox_3);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_7->addWidget(label_7);

        m_ctlImageColor = new QColorPickerPushButton(groupBox_3);
        m_ctlImageColor->setObjectName(QStringLiteral("m_ctlImageColor"));

        horizontalLayout_7->addWidget(m_ctlImageColor);


        verticalLayout_4->addLayout(horizontalLayout_7);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        label_14 = new QLabel(groupBox_3);
        label_14->setObjectName(QStringLiteral("label_14"));

        horizontalLayout_14->addWidget(label_14);

        m_cboEasing_3 = new QComboBox(groupBox_3);
        m_cboEasing_3->setObjectName(QStringLiteral("m_cboEasing_3"));

        horizontalLayout_14->addWidget(m_cboEasing_3);


        verticalLayout_4->addLayout(horizontalLayout_14);


        gridLayout->addWidget(groupBox_3, 5, 0, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_11 = new QLabel(editDisplayMetaItem);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_11->addWidget(label_11);

        m_cboHA = new QComboBox(editDisplayMetaItem);
        m_cboHA->setObjectName(QStringLiteral("m_cboHA"));

        horizontalLayout_11->addWidget(m_cboHA);


        gridLayout->addLayout(horizontalLayout_11, 6, 0, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_10 = new QLabel(editDisplayMetaItem);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_10->addWidget(label_10);

        m_cboVA = new QComboBox(editDisplayMetaItem);
        m_cboVA->setObjectName(QStringLiteral("m_cboVA"));

        horizontalLayout_10->addWidget(m_cboVA);


        gridLayout->addLayout(horizontalLayout_10, 7, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_6 = new QLabel(editDisplayMetaItem);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_6->addWidget(label_6);

        m_ctlZOrder = new QSpinBox(editDisplayMetaItem);
        m_ctlZOrder->setObjectName(QStringLiteral("m_ctlZOrder"));

        horizontalLayout_6->addWidget(m_ctlZOrder);


        gridLayout->addLayout(horizontalLayout_6, 8, 0, 1, 1);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        m_cbLimitBound = new QCheckBox(editDisplayMetaItem);
        m_cbLimitBound->setObjectName(QStringLiteral("m_cbLimitBound"));

        horizontalLayout_15->addWidget(m_cbLimitBound);

        m_cbVisible = new QCheckBox(editDisplayMetaItem);
        m_cbVisible->setObjectName(QStringLiteral("m_cbVisible"));

        horizontalLayout_15->addWidget(m_cbVisible);


        gridLayout->addLayout(horizontalLayout_15, 9, 0, 1, 1);

        buttonBox = new QDialogButtonBox(editDisplayMetaItem);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 10, 0, 1, 1);

        buttonBox->raise();
        groupBox->raise();
        groupBox_2->raise();
        groupBox_3->raise();
        groupBox_4->raise();

        retranslateUi(editDisplayMetaItem);

        QMetaObject::connectSlotsByName(editDisplayMetaItem);
    } // setupUi

    void retranslateUi(QDialog *editDisplayMetaItem)
    {
        editDisplayMetaItem->setWindowTitle(QApplication::translate("editDisplayMetaItem", "editDisplayMetaItem", Q_NULLPTR));
        label_4->setText(QApplication::translate("editDisplayMetaItem", "TAG", Q_NULLPTR));
        m_pbTagApply->setText(QApplication::translate("editDisplayMetaItem", "ApplyTag", Q_NULLPTR));
        label_9->setText(QApplication::translate("editDisplayMetaItem", "Pivot Point", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("editDisplayMetaItem", "Position", Q_NULLPTR));
        label->setText(QApplication::translate("editDisplayMetaItem", "X", Q_NULLPTR));
        label_2->setText(QApplication::translate("editDisplayMetaItem", "Y", Q_NULLPTR));
        label_12->setText(QApplication::translate("editDisplayMetaItem", "Position easing type", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("editDisplayMetaItem", "Rotation", Q_NULLPTR));
        label_3->setText(QApplication::translate("editDisplayMetaItem", "Angle", Q_NULLPTR));
        label_13->setText(QApplication::translate("editDisplayMetaItem", "Angle easing type", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("editDisplayMetaItem", "Size", Q_NULLPTR));
        label_5->setText(QApplication::translate("editDisplayMetaItem", "Height", Q_NULLPTR));
        label_8->setText(QApplication::translate("editDisplayMetaItem", "Width", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("editDisplayMetaItem", "Coloring", Q_NULLPTR));
        label_7->setText(QApplication::translate("editDisplayMetaItem", "Color", Q_NULLPTR));
        m_ctlImageColor->setText(QApplication::translate("editDisplayMetaItem", "PushButton", Q_NULLPTR));
        label_14->setText(QApplication::translate("editDisplayMetaItem", "Color easing type", Q_NULLPTR));
        label_11->setText(QApplication::translate("editDisplayMetaItem", "Horizontal Align", Q_NULLPTR));
        label_10->setText(QApplication::translate("editDisplayMetaItem", "Vertical Align", Q_NULLPTR));
        label_6->setText(QApplication::translate("editDisplayMetaItem", "Z-order", Q_NULLPTR));
        m_cbLimitBound->setText(QApplication::translate("editDisplayMetaItem", "Limit to boundary", Q_NULLPTR));
        m_cbVisible->setText(QApplication::translate("editDisplayMetaItem", "Visible", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class editDisplayMetaItem: public Ui_editDisplayMetaItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITDISPLAYMETAITEM_H
