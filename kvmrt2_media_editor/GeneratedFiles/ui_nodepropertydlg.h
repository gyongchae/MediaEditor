/********************************************************************************
** Form generated from reading UI file 'nodepropertydlg.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NODEPROPERTYDLG_H
#define UI_NODEPROPERTYDLG_H

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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include "qindexcombobox.h"

QT_BEGIN_NAMESPACE

class Ui_NodePropertyDlg
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QIndexComboBox *comboImgListPool_P;
    QDoubleSpinBox *spPosX_P;
    QLabel *label;
    QLabel *labelAngle_P;
    QLabel *label_2;
    QDoubleSpinBox *spPosY_P;
    QComboBox *comboPivot_P;
    QComboBox *comboType_P;
    QLabel *label_5;
    QLabel *label_4;
    QDoubleSpinBox *spAngle_P;
    QLabel *label_22;
    QIndexComboBox *comboDisplayPool_P;
    QLabel *label_6;
    QCheckBox *chkUseDefaultSpot_P;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_4;
    QLabel *label_7;
    QDoubleSpinBox *spPosX_T;
    QDoubleSpinBox *spPosY_T;
    QLabel *labelAngle_T;
    QLabel *label_8;
    QComboBox *comboType_T;
    QLabel *label_10;
    QComboBox *comboPivot_T;
    QLabel *label_11;
    QDoubleSpinBox *spAngle_T;
    QLabel *label_23;
    QIndexComboBox *comboImgListPool_T;
    QIndexComboBox *comboDisplayPool_T;
    QLabel *label_12;
    QCheckBox *chkUseDefaultSpot_T;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_6;
    QIndexComboBox *comboImgListPool_R;
    QIndexComboBox *comboDisplayPool_R;
    QLabel *label_24;
    QDoubleSpinBox *spPosX_R;
    QLabel *label_14;
    QLabel *label_13;
    QDoubleSpinBox *spPosY_R;
    QLabel *label_16;
    QDoubleSpinBox *spAngle_R;
    QLabel *labelAngle_R;
    QComboBox *comboPivot_R;
    QComboBox *comboType_R;
    QLabel *label_17;
    QLabel *label_18;
    QCheckBox *chkUseDefaultSpot_R;
    QHBoxLayout *horizontalLayout_21;
    QLabel *labelStationInfo;
    QIndexComboBox *comboStationInfo;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_14;
    QPushButton *btnCopyAll;
    QPushButton *btnApply;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *NodePropertyDlg)
    {
        if (NodePropertyDlg->objectName().isEmpty())
            NodePropertyDlg->setObjectName(QStringLiteral("NodePropertyDlg"));
        NodePropertyDlg->resize(641, 285);
        verticalLayout_3 = new QVBoxLayout(NodePropertyDlg);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        groupBox = new QGroupBox(NodePropertyDlg);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        comboImgListPool_P = new QIndexComboBox(groupBox);
        comboImgListPool_P->setObjectName(QStringLiteral("comboImgListPool_P"));

        gridLayout->addWidget(comboImgListPool_P, 6, 1, 1, 1);

        spPosX_P = new QDoubleSpinBox(groupBox);
        spPosX_P->setObjectName(QStringLiteral("spPosX_P"));
        spPosX_P->setDecimals(1);
        spPosX_P->setMinimum(-9999);
        spPosX_P->setMaximum(9999);

        gridLayout->addWidget(spPosX_P, 0, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        labelAngle_P = new QLabel(groupBox);
        labelAngle_P->setObjectName(QStringLiteral("labelAngle_P"));

        gridLayout->addWidget(labelAngle_P, 2, 0, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        spPosY_P = new QDoubleSpinBox(groupBox);
        spPosY_P->setObjectName(QStringLiteral("spPosY_P"));
        spPosY_P->setDecimals(1);
        spPosY_P->setMinimum(-9999);
        spPosY_P->setMaximum(9999);

        gridLayout->addWidget(spPosY_P, 1, 1, 1, 1);

        comboPivot_P = new QComboBox(groupBox);
        comboPivot_P->setObjectName(QStringLiteral("comboPivot_P"));

        gridLayout->addWidget(comboPivot_P, 3, 1, 1, 1);

        comboType_P = new QComboBox(groupBox);
        comboType_P->setObjectName(QStringLiteral("comboType_P"));

        gridLayout->addWidget(comboType_P, 4, 1, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 4, 0, 1, 1);

        spAngle_P = new QDoubleSpinBox(groupBox);
        spAngle_P->setObjectName(QStringLiteral("spAngle_P"));
        spAngle_P->setDecimals(0);
        spAngle_P->setMaximum(360);

        gridLayout->addWidget(spAngle_P, 2, 1, 1, 1);

        label_22 = new QLabel(groupBox);
        label_22->setObjectName(QStringLiteral("label_22"));

        gridLayout->addWidget(label_22, 6, 0, 1, 1);

        comboDisplayPool_P = new QIndexComboBox(groupBox);
        comboDisplayPool_P->setObjectName(QStringLiteral("comboDisplayPool_P"));

        gridLayout->addWidget(comboDisplayPool_P, 5, 1, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        chkUseDefaultSpot_P = new QCheckBox(groupBox);
        chkUseDefaultSpot_P->setObjectName(QStringLiteral("chkUseDefaultSpot_P"));

        gridLayout->addWidget(chkUseDefaultSpot_P, 7, 0, 1, 2);

        gridLayout->setColumnStretch(1, 1);

        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        horizontalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(NodePropertyDlg);
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

        spPosX_T = new QDoubleSpinBox(groupBox_2);
        spPosX_T->setObjectName(QStringLiteral("spPosX_T"));
        spPosX_T->setDecimals(1);
        spPosX_T->setMinimum(-9999);
        spPosX_T->setMaximum(9999);

        gridLayout_4->addWidget(spPosX_T, 0, 1, 1, 1);

        spPosY_T = new QDoubleSpinBox(groupBox_2);
        spPosY_T->setObjectName(QStringLiteral("spPosY_T"));
        spPosY_T->setDecimals(1);
        spPosY_T->setMinimum(-9999);
        spPosY_T->setMaximum(9999);

        gridLayout_4->addWidget(spPosY_T, 1, 1, 1, 1);

        labelAngle_T = new QLabel(groupBox_2);
        labelAngle_T->setObjectName(QStringLiteral("labelAngle_T"));

        gridLayout_4->addWidget(labelAngle_T, 2, 0, 1, 1);

        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_4->addWidget(label_8, 1, 0, 1, 1);

        comboType_T = new QComboBox(groupBox_2);
        comboType_T->setObjectName(QStringLiteral("comboType_T"));

        gridLayout_4->addWidget(comboType_T, 4, 1, 1, 1);

        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_4->addWidget(label_10, 3, 0, 1, 1);

        comboPivot_T = new QComboBox(groupBox_2);
        comboPivot_T->setObjectName(QStringLiteral("comboPivot_T"));

        gridLayout_4->addWidget(comboPivot_T, 3, 1, 1, 1);

        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_4->addWidget(label_11, 4, 0, 1, 1);

        spAngle_T = new QDoubleSpinBox(groupBox_2);
        spAngle_T->setObjectName(QStringLiteral("spAngle_T"));
        spAngle_T->setDecimals(0);
        spAngle_T->setMaximum(360);

        gridLayout_4->addWidget(spAngle_T, 2, 1, 1, 1);

        label_23 = new QLabel(groupBox_2);
        label_23->setObjectName(QStringLiteral("label_23"));

        gridLayout_4->addWidget(label_23, 6, 0, 1, 1);

        comboImgListPool_T = new QIndexComboBox(groupBox_2);
        comboImgListPool_T->setObjectName(QStringLiteral("comboImgListPool_T"));

        gridLayout_4->addWidget(comboImgListPool_T, 6, 1, 1, 1);

        comboDisplayPool_T = new QIndexComboBox(groupBox_2);
        comboDisplayPool_T->setObjectName(QStringLiteral("comboDisplayPool_T"));

        gridLayout_4->addWidget(comboDisplayPool_T, 5, 1, 1, 1);

        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_4->addWidget(label_12, 5, 0, 1, 1);

        chkUseDefaultSpot_T = new QCheckBox(groupBox_2);
        chkUseDefaultSpot_T->setObjectName(QStringLiteral("chkUseDefaultSpot_T"));

        gridLayout_4->addWidget(chkUseDefaultSpot_T, 7, 0, 1, 2);

        gridLayout_4->setColumnStretch(1, 1);

        gridLayout_3->addLayout(gridLayout_4, 0, 0, 1, 1);


        horizontalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(NodePropertyDlg);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_5 = new QGridLayout(groupBox_3);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setSpacing(6);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        comboImgListPool_R = new QIndexComboBox(groupBox_3);
        comboImgListPool_R->setObjectName(QStringLiteral("comboImgListPool_R"));

        gridLayout_6->addWidget(comboImgListPool_R, 6, 1, 1, 1);

        comboDisplayPool_R = new QIndexComboBox(groupBox_3);
        comboDisplayPool_R->setObjectName(QStringLiteral("comboDisplayPool_R"));

        gridLayout_6->addWidget(comboDisplayPool_R, 5, 1, 1, 1);

        label_24 = new QLabel(groupBox_3);
        label_24->setObjectName(QStringLiteral("label_24"));

        gridLayout_6->addWidget(label_24, 6, 0, 1, 1);

        spPosX_R = new QDoubleSpinBox(groupBox_3);
        spPosX_R->setObjectName(QStringLiteral("spPosX_R"));
        spPosX_R->setDecimals(1);
        spPosX_R->setMinimum(-9999);
        spPosX_R->setMaximum(9999);

        gridLayout_6->addWidget(spPosX_R, 0, 1, 1, 1);

        label_14 = new QLabel(groupBox_3);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout_6->addWidget(label_14, 1, 0, 1, 1);

        label_13 = new QLabel(groupBox_3);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_6->addWidget(label_13, 0, 0, 1, 1);

        spPosY_R = new QDoubleSpinBox(groupBox_3);
        spPosY_R->setObjectName(QStringLiteral("spPosY_R"));
        spPosY_R->setDecimals(1);
        spPosY_R->setMinimum(-9999);
        spPosY_R->setMaximum(9999);

        gridLayout_6->addWidget(spPosY_R, 1, 1, 1, 1);

        label_16 = new QLabel(groupBox_3);
        label_16->setObjectName(QStringLiteral("label_16"));

        gridLayout_6->addWidget(label_16, 3, 0, 1, 1);

        spAngle_R = new QDoubleSpinBox(groupBox_3);
        spAngle_R->setObjectName(QStringLiteral("spAngle_R"));
        spAngle_R->setDecimals(0);
        spAngle_R->setMaximum(360);

        gridLayout_6->addWidget(spAngle_R, 2, 1, 1, 1);

        labelAngle_R = new QLabel(groupBox_3);
        labelAngle_R->setObjectName(QStringLiteral("labelAngle_R"));

        gridLayout_6->addWidget(labelAngle_R, 2, 0, 1, 1);

        comboPivot_R = new QComboBox(groupBox_3);
        comboPivot_R->setObjectName(QStringLiteral("comboPivot_R"));

        gridLayout_6->addWidget(comboPivot_R, 3, 1, 1, 1);

        comboType_R = new QComboBox(groupBox_3);
        comboType_R->setObjectName(QStringLiteral("comboType_R"));

        gridLayout_6->addWidget(comboType_R, 4, 1, 1, 1);

        label_17 = new QLabel(groupBox_3);
        label_17->setObjectName(QStringLiteral("label_17"));

        gridLayout_6->addWidget(label_17, 4, 0, 1, 1);

        label_18 = new QLabel(groupBox_3);
        label_18->setObjectName(QStringLiteral("label_18"));

        gridLayout_6->addWidget(label_18, 5, 0, 1, 1);

        chkUseDefaultSpot_R = new QCheckBox(groupBox_3);
        chkUseDefaultSpot_R->setObjectName(QStringLiteral("chkUseDefaultSpot_R"));

        gridLayout_6->addWidget(chkUseDefaultSpot_R, 7, 0, 1, 2);

        gridLayout_6->setColumnStretch(1, 1);

        gridLayout_5->addLayout(gridLayout_6, 0, 0, 1, 1);


        horizontalLayout->addWidget(groupBox_3);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setObjectName(QStringLiteral("horizontalLayout_21"));
        labelStationInfo = new QLabel(NodePropertyDlg);
        labelStationInfo->setObjectName(QStringLiteral("labelStationInfo"));

        horizontalLayout_21->addWidget(labelStationInfo);

        comboStationInfo = new QIndexComboBox(NodePropertyDlg);
        comboStationInfo->setObjectName(QStringLiteral("comboStationInfo"));

        horizontalLayout_21->addWidget(comboStationInfo);

        horizontalSpacer_2 = new QSpacerItem(37, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_21->addItem(horizontalSpacer_2);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        btnCopyAll = new QPushButton(NodePropertyDlg);
        btnCopyAll->setObjectName(QStringLiteral("btnCopyAll"));

        horizontalLayout_14->addWidget(btnCopyAll);

        btnApply = new QPushButton(NodePropertyDlg);
        btnApply->setObjectName(QStringLiteral("btnApply"));

        horizontalLayout_14->addWidget(btnApply);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer);

        buttonBox = new QDialogButtonBox(NodePropertyDlg);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_14->addWidget(buttonBox);


        horizontalLayout_21->addLayout(horizontalLayout_14);

        horizontalLayout_21->setStretch(1, 1);
        horizontalLayout_21->setStretch(3, 3);

        verticalLayout_3->addLayout(horizontalLayout_21);

        verticalLayout_3->setStretch(0, 1);
#ifndef QT_NO_SHORTCUT
        label->setBuddy(spPosX_P);
        labelAngle_P->setBuddy(spAngle_P);
        label_2->setBuddy(spPosY_P);
        label_5->setBuddy(comboPivot_P);
        label_4->setBuddy(comboType_P);
        label_22->setBuddy(comboImgListPool_P);
        label_6->setBuddy(comboDisplayPool_P);
        label_7->setBuddy(spPosX_T);
        labelAngle_T->setBuddy(spAngle_T);
        label_8->setBuddy(spPosY_T);
        label_10->setBuddy(comboPivot_T);
        label_11->setBuddy(comboType_T);
        label_23->setBuddy(comboImgListPool_T);
        label_12->setBuddy(comboDisplayPool_T);
        label_24->setBuddy(comboImgListPool_R);
        label_14->setBuddy(spPosY_R);
        label_13->setBuddy(spPosX_R);
        label_16->setBuddy(comboPivot_R);
        labelAngle_R->setBuddy(spAngle_R);
        label_17->setBuddy(comboType_R);
        label_18->setBuddy(comboDisplayPool_R);
        labelStationInfo->setBuddy(comboStationInfo);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(spPosX_P, spPosY_P);
        QWidget::setTabOrder(spPosY_P, spAngle_P);
        QWidget::setTabOrder(spAngle_P, comboPivot_P);
        QWidget::setTabOrder(comboPivot_P, comboType_P);
        QWidget::setTabOrder(comboType_P, comboDisplayPool_P);
        QWidget::setTabOrder(comboDisplayPool_P, comboImgListPool_P);
        QWidget::setTabOrder(comboImgListPool_P, chkUseDefaultSpot_P);
        QWidget::setTabOrder(chkUseDefaultSpot_P, spPosX_T);
        QWidget::setTabOrder(spPosX_T, spPosY_T);
        QWidget::setTabOrder(spPosY_T, spAngle_T);
        QWidget::setTabOrder(spAngle_T, comboPivot_T);
        QWidget::setTabOrder(comboPivot_T, comboType_T);
        QWidget::setTabOrder(comboType_T, comboDisplayPool_T);
        QWidget::setTabOrder(comboDisplayPool_T, comboImgListPool_T);
        QWidget::setTabOrder(comboImgListPool_T, chkUseDefaultSpot_T);
        QWidget::setTabOrder(chkUseDefaultSpot_T, spPosX_R);
        QWidget::setTabOrder(spPosX_R, spPosY_R);
        QWidget::setTabOrder(spPosY_R, spAngle_R);
        QWidget::setTabOrder(spAngle_R, comboPivot_R);
        QWidget::setTabOrder(comboPivot_R, comboType_R);
        QWidget::setTabOrder(comboType_R, comboDisplayPool_R);
        QWidget::setTabOrder(comboDisplayPool_R, comboImgListPool_R);
        QWidget::setTabOrder(comboImgListPool_R, chkUseDefaultSpot_R);
        QWidget::setTabOrder(chkUseDefaultSpot_R, comboStationInfo);
        QWidget::setTabOrder(comboStationInfo, btnCopyAll);
        QWidget::setTabOrder(btnCopyAll, btnApply);

        retranslateUi(NodePropertyDlg);

        QMetaObject::connectSlotsByName(NodePropertyDlg);
    } // setupUi

    void retranslateUi(QDialog *NodePropertyDlg)
    {
        NodePropertyDlg->setWindowTitle(QApplication::translate("NodePropertyDlg", "Property", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("NodePropertyDlg", "Passed Station", Q_NULLPTR));
        label->setText(QApplication::translate("NodePropertyDlg", "Pos X", Q_NULLPTR));
        labelAngle_P->setText(QApplication::translate("NodePropertyDlg", "Angle", Q_NULLPTR));
        label_2->setText(QApplication::translate("NodePropertyDlg", "Pos Y", Q_NULLPTR));
        label_5->setText(QApplication::translate("NodePropertyDlg", "Pivot Point", Q_NULLPTR));
        label_4->setText(QApplication::translate("NodePropertyDlg", "Image Refer to", Q_NULLPTR));
        label_22->setText(QApplication::translate("NodePropertyDlg", "Image List Item", Q_NULLPTR));
        label_6->setText(QApplication::translate("NodePropertyDlg", "Display Pool Item", Q_NULLPTR));
        chkUseDefaultSpot_P->setText(QApplication::translate("NodePropertyDlg", "Using Default Node Icon", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("NodePropertyDlg", "Target Station", Q_NULLPTR));
        label_7->setText(QApplication::translate("NodePropertyDlg", "Pos X", Q_NULLPTR));
        labelAngle_T->setText(QApplication::translate("NodePropertyDlg", "Angle", Q_NULLPTR));
        label_8->setText(QApplication::translate("NodePropertyDlg", "Pos Y", Q_NULLPTR));
        label_10->setText(QApplication::translate("NodePropertyDlg", "Pivot Point", Q_NULLPTR));
        label_11->setText(QApplication::translate("NodePropertyDlg", "Image Refer to", Q_NULLPTR));
        label_23->setText(QApplication::translate("NodePropertyDlg", "Image List Item", Q_NULLPTR));
        label_12->setText(QApplication::translate("NodePropertyDlg", "Display Pool Item", Q_NULLPTR));
        chkUseDefaultSpot_T->setText(QApplication::translate("NodePropertyDlg", "Using Default Node Icon", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("NodePropertyDlg", "Remain Station", Q_NULLPTR));
        label_24->setText(QApplication::translate("NodePropertyDlg", "Image List Item", Q_NULLPTR));
        label_14->setText(QApplication::translate("NodePropertyDlg", "Pos Y", Q_NULLPTR));
        label_13->setText(QApplication::translate("NodePropertyDlg", "Pos X", Q_NULLPTR));
        label_16->setText(QApplication::translate("NodePropertyDlg", "Pivot Point", Q_NULLPTR));
        labelAngle_R->setText(QApplication::translate("NodePropertyDlg", "Angle", Q_NULLPTR));
        label_17->setText(QApplication::translate("NodePropertyDlg", "Image Refer to", Q_NULLPTR));
        label_18->setText(QApplication::translate("NodePropertyDlg", "Display Pool Item", Q_NULLPTR));
        chkUseDefaultSpot_R->setText(QApplication::translate("NodePropertyDlg", "Using Default Node Icon", Q_NULLPTR));
        labelStationInfo->setText(QApplication::translate("NodePropertyDlg", "Related Station", Q_NULLPTR));
        btnCopyAll->setText(QApplication::translate("NodePropertyDlg", "Copy All", Q_NULLPTR));
        btnApply->setText(QApplication::translate("NodePropertyDlg", "Apply", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NodePropertyDlg: public Ui_NodePropertyDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NODEPROPERTYDLG_H
