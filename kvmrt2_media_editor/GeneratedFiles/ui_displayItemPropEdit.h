/********************************************************************************
** Form generated from reading UI file 'displayItemPropEdit.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISPLAYITEMPROPEDIT_H
#define UI_DISPLAYITEMPROPEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include "qcolorpickerpushbutton.h"

QT_BEGIN_NAMESPACE

class Ui_displayItemPropEdit
{
public:
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
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
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QDoubleSpinBox *m_ctlAngle;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_13;
    QComboBox *m_cboEasing_2;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QDoubleSpinBox *m_ctlScalingX;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QDoubleSpinBox *m_ctlScalingY;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_16;
    QComboBox *m_cboEasing_5;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QSpinBox *m_ctlZOrder;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QColorPickerPushButton *m_ctlImageColor;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_14;
    QComboBox *m_cboEasing_3;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_9;
    QComboBox *m_cboCenter;
    QCheckBox *m_cbVisible;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *displayItemPropEdit)
    {
        if (displayItemPropEdit->objectName().isEmpty())
            displayItemPropEdit->setObjectName(QStringLiteral("displayItemPropEdit"));
        displayItemPropEdit->resize(424, 599);
        verticalLayout_5 = new QVBoxLayout(displayItemPropEdit);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        groupBox = new QGroupBox(displayItemPropEdit);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        m_ctlX = new QDoubleSpinBox(groupBox);
        m_ctlX->setObjectName(QStringLiteral("m_ctlX"));
        m_ctlX->setDecimals(1);
        m_ctlX->setMinimum(-9999);
        m_ctlX->setMaximum(9999);

        horizontalLayout->addWidget(m_ctlX);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        m_ctlY = new QDoubleSpinBox(groupBox);
        m_ctlY->setObjectName(QStringLiteral("m_ctlY"));
        m_ctlY->setDecimals(1);
        m_ctlY->setMinimum(-9999);
        m_ctlY->setMaximum(9999);

        horizontalLayout_2->addWidget(m_ctlY);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_12->addWidget(label_12);

        m_cboEasing = new QComboBox(groupBox);
        m_cboEasing->setObjectName(QStringLiteral("m_cboEasing"));

        horizontalLayout_12->addWidget(m_cboEasing);


        verticalLayout->addLayout(horizontalLayout_12);


        verticalLayout_5->addWidget(groupBox);

        groupBox_2 = new QGroupBox(displayItemPropEdit);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        m_ctlAngle = new QDoubleSpinBox(groupBox_2);
        m_ctlAngle->setObjectName(QStringLiteral("m_ctlAngle"));
        m_ctlAngle->setDecimals(0);
        m_ctlAngle->setMaximum(360);

        horizontalLayout_3->addWidget(m_ctlAngle);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QStringLiteral("label_13"));

        horizontalLayout_13->addWidget(label_13);

        m_cboEasing_2 = new QComboBox(groupBox_2);
        m_cboEasing_2->setObjectName(QStringLiteral("m_cboEasing_2"));

        horizontalLayout_13->addWidget(m_cboEasing_2);


        verticalLayout_2->addLayout(horizontalLayout_13);


        verticalLayout_5->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(displayItemPropEdit);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout_3 = new QVBoxLayout(groupBox_3);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        m_ctlScalingX = new QDoubleSpinBox(groupBox_3);
        m_ctlScalingX->setObjectName(QStringLiteral("m_ctlScalingX"));
        m_ctlScalingX->setDecimals(1);
        m_ctlScalingX->setMaximum(999);
        m_ctlScalingX->setSingleStep(0.1);
        m_ctlScalingX->setValue(1);

        horizontalLayout_4->addWidget(m_ctlScalingX);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_5->addWidget(label_5);

        m_ctlScalingY = new QDoubleSpinBox(groupBox_3);
        m_ctlScalingY->setObjectName(QStringLiteral("m_ctlScalingY"));
        m_ctlScalingY->setDecimals(1);
        m_ctlScalingY->setMaximum(999);
        m_ctlScalingY->setSingleStep(0.1);
        m_ctlScalingY->setValue(1);

        horizontalLayout_5->addWidget(m_ctlScalingY);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        label_16 = new QLabel(groupBox_3);
        label_16->setObjectName(QStringLiteral("label_16"));

        horizontalLayout_16->addWidget(label_16);

        m_cboEasing_5 = new QComboBox(groupBox_3);
        m_cboEasing_5->setObjectName(QStringLiteral("m_cboEasing_5"));

        horizontalLayout_16->addWidget(m_cboEasing_5);


        verticalLayout_3->addLayout(horizontalLayout_16);


        verticalLayout_5->addWidget(groupBox_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_6 = new QLabel(displayItemPropEdit);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_6->addWidget(label_6);

        m_ctlZOrder = new QSpinBox(displayItemPropEdit);
        m_ctlZOrder->setObjectName(QStringLiteral("m_ctlZOrder"));

        horizontalLayout_6->addWidget(m_ctlZOrder);


        verticalLayout_5->addLayout(horizontalLayout_6);

        groupBox_4 = new QGroupBox(displayItemPropEdit);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        verticalLayout_4 = new QVBoxLayout(groupBox_4);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_7->addWidget(label_7);

        m_ctlImageColor = new QColorPickerPushButton(groupBox_4);
        m_ctlImageColor->setObjectName(QStringLiteral("m_ctlImageColor"));

        horizontalLayout_7->addWidget(m_ctlImageColor);


        verticalLayout_4->addLayout(horizontalLayout_7);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        label_14 = new QLabel(groupBox_4);
        label_14->setObjectName(QStringLiteral("label_14"));

        horizontalLayout_14->addWidget(label_14);

        m_cboEasing_3 = new QComboBox(groupBox_4);
        m_cboEasing_3->setObjectName(QStringLiteral("m_cboEasing_3"));

        horizontalLayout_14->addWidget(m_cboEasing_3);


        verticalLayout_4->addLayout(horizontalLayout_14);


        verticalLayout_5->addWidget(groupBox_4);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_9 = new QLabel(displayItemPropEdit);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_9->addWidget(label_9);

        m_cboCenter = new QComboBox(displayItemPropEdit);
        m_cboCenter->setObjectName(QStringLiteral("m_cboCenter"));

        horizontalLayout_9->addWidget(m_cboCenter);


        verticalLayout_5->addLayout(horizontalLayout_9);

        m_cbVisible = new QCheckBox(displayItemPropEdit);
        m_cbVisible->setObjectName(QStringLiteral("m_cbVisible"));

        verticalLayout_5->addWidget(m_cbVisible);

        buttonBox = new QDialogButtonBox(displayItemPropEdit);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_5->addWidget(buttonBox);


        retranslateUi(displayItemPropEdit);

        QMetaObject::connectSlotsByName(displayItemPropEdit);
    } // setupUi

    void retranslateUi(QDialog *displayItemPropEdit)
    {
        displayItemPropEdit->setWindowTitle(QApplication::translate("displayItemPropEdit", "displayItemPropEdit", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("displayItemPropEdit", "Position", Q_NULLPTR));
        label->setText(QApplication::translate("displayItemPropEdit", "X", Q_NULLPTR));
        label_2->setText(QApplication::translate("displayItemPropEdit", "Y", Q_NULLPTR));
        label_12->setText(QApplication::translate("displayItemPropEdit", "Position easing type", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("displayItemPropEdit", "Rotation", Q_NULLPTR));
        label_3->setText(QApplication::translate("displayItemPropEdit", "Angle", Q_NULLPTR));
        label_13->setText(QApplication::translate("displayItemPropEdit", "Angle easing type", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("displayItemPropEdit", "Scaling", Q_NULLPTR));
        label_4->setText(QApplication::translate("displayItemPropEdit", "H-Scale ratio", Q_NULLPTR));
        label_5->setText(QApplication::translate("displayItemPropEdit", "V-Scale ratio", Q_NULLPTR));
        label_16->setText(QApplication::translate("displayItemPropEdit", "Scale easing type", Q_NULLPTR));
        label_6->setText(QApplication::translate("displayItemPropEdit", "Z-order", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("displayItemPropEdit", "Coloring", Q_NULLPTR));
        label_7->setText(QApplication::translate("displayItemPropEdit", "Color", Q_NULLPTR));
        m_ctlImageColor->setText(QApplication::translate("displayItemPropEdit", "PushButton", Q_NULLPTR));
        label_14->setText(QApplication::translate("displayItemPropEdit", "Color easing type", Q_NULLPTR));
        label_9->setText(QApplication::translate("displayItemPropEdit", "Pivot Point", Q_NULLPTR));
        m_cbVisible->setText(QApplication::translate("displayItemPropEdit", "Visible", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class displayItemPropEdit: public Ui_displayItemPropEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPLAYITEMPROPEDIT_H
