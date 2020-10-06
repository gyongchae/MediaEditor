/********************************************************************************
** Form generated from reading UI file 'QLineMapEdit.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QLINEMAPEDIT_H
#define UI_QLINEMAPEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QGLESLineMapCanvas.h"
#include "qcolorpickerpushbutton.h"

QT_BEGIN_NAMESPACE

class Ui_QLineMapEdit
{
public:
    QVBoxLayout *verticalLayout_4;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_9;
    QGLESLineMapCanvas *openGLWidget;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *gbBasicMenu;
    QGridLayout *gridLayout_8;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_13;
    QLineEdit *editTitle;
    QLabel *label_14;
    QLineEdit *editTileSize;
    QLabel *label_15;
    QLineEdit *editLineThick;
    QLabel *label_16;
    QLineEdit *editWidth;
    QLabel *label_17;
    QLineEdit *editHeight;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *m_grpEditMode;
    QGridLayout *gridLayout;
    QRadioButton *m_ctlTile;
    QRadioButton *m_ctlArrow;
    QRadioButton *m_ctlDisplayItem;
    QRadioButton *m_ctlNode;
    QRadioButton *m_ctlImageList;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_6;
    QFormLayout *formLayout_2;
    QLabel *label;
    QColorPickerPushButton *m_ctlBackgroundColor;
    QLabel *label_2;
    QColorPickerPushButton *m_ctlForegroundColor;
    QPushButton *m_pbApplyColor;
    QStackedWidget *m_ctlStackedWidget;
    QWidget *page;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_4;
    QColorPickerPushButton *m_ctlPassedColor;
    QLabel *label_3;
    QColorPickerPushButton *m_ctlFocusedColor;
    QLabel *label_4;
    QColorPickerPushButton *m_ctlLeftColor;
    QLabel *label_5;
    QColorPickerPushButton *m_ctlArrowPassedColor;
    QLabel *label_9;
    QColorPickerPushButton *m_ctlArrowFocusedColor;
    QLabel *label_10;
    QColorPickerPushButton *m_ctlArrowSecondFocusedColor;
    QLabel *label_11;
    QColorPickerPushButton *m_ctlArrowRemainedColor;
    QLabel *label_12;
    QWidget *pageTileEdit;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_4;
    QTableView *m_tblLineMapLink;
    QWidget *pageNodeEdit;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *btnCopyProp;
    QPushButton *btnPasteNode;
    QPushButton *btnPasteSpot;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *btnShowSpotDefault;
    QPushButton *btnShowSpotCustom;
    QSpacerItem *horizontalSpacer_6;
    QTableView *m_tblLineMapNode;
    QWidget *pageArrowEdit;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label_6;
    QSpinBox *m_spForwardArrowOffset;
    QLabel *label_7;
    QSpinBox *m_spBackwardArrowOffset;
    QLabel *label_8;
    QSpinBox *m_spArrowPenWidth;
    QPushButton *m_pbApplyArrowOffset;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QWidget *pageDisplayEdit;
    QGridLayout *gridLayout_7;
    QHBoxLayout *horizontalLayout_2;
    QTableView *m_tblDisplayItemPool;
    QWidget *pageImageList;
    QGridLayout *gridLayout_10;
    QTableView *m_tblImageIndexList;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btnClose;

    void setupUi(QDialog *QLineMapEdit)
    {
        if (QLineMapEdit->objectName().isEmpty())
            QLineMapEdit->setObjectName(QStringLiteral("QLineMapEdit"));
        QLineMapEdit->resize(1121, 607);
        verticalLayout_4 = new QVBoxLayout(QLineMapEdit);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        scrollArea = new QScrollArea(QLineMapEdit);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1101, 276));
        gridLayout_9 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        openGLWidget = new QGLESLineMapCanvas(scrollAreaWidgetContents);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));

        gridLayout_9->addWidget(openGLWidget, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_4->addWidget(scrollArea);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        gbBasicMenu = new QGroupBox(QLineMapEdit);
        gbBasicMenu->setObjectName(QStringLiteral("gbBasicMenu"));
        gridLayout_8 = new QGridLayout(gbBasicMenu);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_13 = new QLabel(gbBasicMenu);
        label_13->setObjectName(QStringLiteral("label_13"));

        verticalLayout_2->addWidget(label_13);

        editTitle = new QLineEdit(gbBasicMenu);
        editTitle->setObjectName(QStringLiteral("editTitle"));

        verticalLayout_2->addWidget(editTitle);

        label_14 = new QLabel(gbBasicMenu);
        label_14->setObjectName(QStringLiteral("label_14"));

        verticalLayout_2->addWidget(label_14);

        editTileSize = new QLineEdit(gbBasicMenu);
        editTileSize->setObjectName(QStringLiteral("editTileSize"));

        verticalLayout_2->addWidget(editTileSize);

        label_15 = new QLabel(gbBasicMenu);
        label_15->setObjectName(QStringLiteral("label_15"));

        verticalLayout_2->addWidget(label_15);

        editLineThick = new QLineEdit(gbBasicMenu);
        editLineThick->setObjectName(QStringLiteral("editLineThick"));

        verticalLayout_2->addWidget(editLineThick);

        label_16 = new QLabel(gbBasicMenu);
        label_16->setObjectName(QStringLiteral("label_16"));

        verticalLayout_2->addWidget(label_16);

        editWidth = new QLineEdit(gbBasicMenu);
        editWidth->setObjectName(QStringLiteral("editWidth"));

        verticalLayout_2->addWidget(editWidth);

        label_17 = new QLabel(gbBasicMenu);
        label_17->setObjectName(QStringLiteral("label_17"));

        verticalLayout_2->addWidget(label_17);

        editHeight = new QLineEdit(gbBasicMenu);
        editHeight->setObjectName(QStringLiteral("editHeight"));

        verticalLayout_2->addWidget(editHeight);


        gridLayout_8->addLayout(verticalLayout_2, 0, 0, 1, 1);


        horizontalLayout_3->addWidget(gbBasicMenu);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        m_grpEditMode = new QGroupBox(QLineMapEdit);
        m_grpEditMode->setObjectName(QStringLiteral("m_grpEditMode"));
        gridLayout = new QGridLayout(m_grpEditMode);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        m_ctlTile = new QRadioButton(m_grpEditMode);
        m_ctlTile->setObjectName(QStringLiteral("m_ctlTile"));

        gridLayout->addWidget(m_ctlTile, 0, 0, 1, 1);

        m_ctlArrow = new QRadioButton(m_grpEditMode);
        m_ctlArrow->setObjectName(QStringLiteral("m_ctlArrow"));

        gridLayout->addWidget(m_ctlArrow, 2, 0, 1, 1);

        m_ctlDisplayItem = new QRadioButton(m_grpEditMode);
        m_ctlDisplayItem->setObjectName(QStringLiteral("m_ctlDisplayItem"));

        gridLayout->addWidget(m_ctlDisplayItem, 4, 0, 1, 1);

        m_ctlNode = new QRadioButton(m_grpEditMode);
        m_ctlNode->setObjectName(QStringLiteral("m_ctlNode"));

        gridLayout->addWidget(m_ctlNode, 1, 0, 1, 1);

        m_ctlImageList = new QRadioButton(m_grpEditMode);
        m_ctlImageList->setObjectName(QStringLiteral("m_ctlImageList"));

        gridLayout->addWidget(m_ctlImageList, 3, 0, 1, 1);


        verticalLayout_3->addWidget(m_grpEditMode);

        groupBox_2 = new QGroupBox(QLineMapEdit);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_6 = new QGridLayout(groupBox_2);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label);

        m_ctlBackgroundColor = new QColorPickerPushButton(groupBox_2);
        m_ctlBackgroundColor->setObjectName(QStringLiteral("m_ctlBackgroundColor"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, m_ctlBackgroundColor);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_2);

        m_ctlForegroundColor = new QColorPickerPushButton(groupBox_2);
        m_ctlForegroundColor->setObjectName(QStringLiteral("m_ctlForegroundColor"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, m_ctlForegroundColor);

        m_pbApplyColor = new QPushButton(groupBox_2);
        m_pbApplyColor->setObjectName(QStringLiteral("m_pbApplyColor"));

        formLayout_2->setWidget(2, QFormLayout::SpanningRole, m_pbApplyColor);


        gridLayout_6->addLayout(formLayout_2, 0, 0, 1, 1);


        verticalLayout_3->addWidget(groupBox_2);


        horizontalLayout_3->addLayout(verticalLayout_3);

        m_ctlStackedWidget = new QStackedWidget(QLineMapEdit);
        m_ctlStackedWidget->setObjectName(QStringLiteral("m_ctlStackedWidget"));
        m_ctlStackedWidget->setFrameShadow(QFrame::Plain);
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        gridLayout_3 = new QGridLayout(page);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        m_ctlPassedColor = new QColorPickerPushButton(page);
        m_ctlPassedColor->setObjectName(QStringLiteral("m_ctlPassedColor"));

        gridLayout_4->addWidget(m_ctlPassedColor, 0, 0, 1, 1);

        label_3 = new QLabel(page);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_4->addWidget(label_3, 0, 1, 1, 1);

        m_ctlFocusedColor = new QColorPickerPushButton(page);
        m_ctlFocusedColor->setObjectName(QStringLiteral("m_ctlFocusedColor"));

        gridLayout_4->addWidget(m_ctlFocusedColor, 1, 0, 1, 1);

        label_4 = new QLabel(page);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_4->addWidget(label_4, 1, 1, 1, 1);

        m_ctlLeftColor = new QColorPickerPushButton(page);
        m_ctlLeftColor->setObjectName(QStringLiteral("m_ctlLeftColor"));

        gridLayout_4->addWidget(m_ctlLeftColor, 2, 0, 1, 1);

        label_5 = new QLabel(page);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_4->addWidget(label_5, 2, 1, 1, 1);

        m_ctlArrowPassedColor = new QColorPickerPushButton(page);
        m_ctlArrowPassedColor->setObjectName(QStringLiteral("m_ctlArrowPassedColor"));

        gridLayout_4->addWidget(m_ctlArrowPassedColor, 3, 0, 1, 1);

        label_9 = new QLabel(page);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_4->addWidget(label_9, 3, 1, 1, 1);

        m_ctlArrowFocusedColor = new QColorPickerPushButton(page);
        m_ctlArrowFocusedColor->setObjectName(QStringLiteral("m_ctlArrowFocusedColor"));

        gridLayout_4->addWidget(m_ctlArrowFocusedColor, 4, 0, 1, 1);

        label_10 = new QLabel(page);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_4->addWidget(label_10, 4, 1, 1, 1);

        m_ctlArrowSecondFocusedColor = new QColorPickerPushButton(page);
        m_ctlArrowSecondFocusedColor->setObjectName(QStringLiteral("m_ctlArrowSecondFocusedColor"));

        gridLayout_4->addWidget(m_ctlArrowSecondFocusedColor, 5, 0, 1, 1);

        label_11 = new QLabel(page);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_4->addWidget(label_11, 5, 1, 1, 1);

        m_ctlArrowRemainedColor = new QColorPickerPushButton(page);
        m_ctlArrowRemainedColor->setObjectName(QStringLiteral("m_ctlArrowRemainedColor"));

        gridLayout_4->addWidget(m_ctlArrowRemainedColor, 6, 0, 1, 1);

        label_12 = new QLabel(page);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_4->addWidget(label_12, 6, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout_4, 0, 0, 1, 1);

        m_ctlStackedWidget->addWidget(page);
        pageTileEdit = new QWidget();
        pageTileEdit->setObjectName(QStringLiteral("pageTileEdit"));
        gridLayout_2 = new QGridLayout(pageTileEdit);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        pushButton = new QPushButton(pageTileEdit);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_6->addWidget(pushButton);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);

        pushButton_2 = new QPushButton(pageTileEdit);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_6->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(pageTileEdit);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_6->addWidget(pushButton_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);

        pushButton_4 = new QPushButton(pageTileEdit);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        horizontalLayout_6->addWidget(pushButton_4);


        verticalLayout_6->addLayout(horizontalLayout_6);

        m_tblLineMapLink = new QTableView(pageTileEdit);
        m_tblLineMapLink->setObjectName(QStringLiteral("m_tblLineMapLink"));

        verticalLayout_6->addWidget(m_tblLineMapLink);

        verticalLayout_6->setStretch(1, 1);

        gridLayout_2->addLayout(verticalLayout_6, 0, 0, 1, 1);

        m_ctlStackedWidget->addWidget(pageTileEdit);
        pageNodeEdit = new QWidget();
        pageNodeEdit->setObjectName(QStringLiteral("pageNodeEdit"));
        verticalLayout_5 = new QVBoxLayout(pageNodeEdit);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        btnCopyProp = new QPushButton(pageNodeEdit);
        btnCopyProp->setObjectName(QStringLiteral("btnCopyProp"));

        horizontalLayout_5->addWidget(btnCopyProp);

        btnPasteNode = new QPushButton(pageNodeEdit);
        btnPasteNode->setObjectName(QStringLiteral("btnPasteNode"));

        horizontalLayout_5->addWidget(btnPasteNode);

        btnPasteSpot = new QPushButton(pageNodeEdit);
        btnPasteSpot->setObjectName(QStringLiteral("btnPasteSpot"));

        horizontalLayout_5->addWidget(btnPasteSpot);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);


        verticalLayout_5->addLayout(horizontalLayout_5);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        btnShowSpotDefault = new QPushButton(pageNodeEdit);
        btnShowSpotDefault->setObjectName(QStringLiteral("btnShowSpotDefault"));

        horizontalLayout_7->addWidget(btnShowSpotDefault);

        btnShowSpotCustom = new QPushButton(pageNodeEdit);
        btnShowSpotCustom->setObjectName(QStringLiteral("btnShowSpotCustom"));

        horizontalLayout_7->addWidget(btnShowSpotCustom);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_6);


        verticalLayout_5->addLayout(horizontalLayout_7);

        m_tblLineMapNode = new QTableView(pageNodeEdit);
        m_tblLineMapNode->setObjectName(QStringLiteral("m_tblLineMapNode"));

        verticalLayout_5->addWidget(m_tblLineMapNode);

        m_ctlStackedWidget->addWidget(pageNodeEdit);
        pageArrowEdit = new QWidget();
        pageArrowEdit->setObjectName(QStringLiteral("pageArrowEdit"));
        gridLayout_5 = new QGridLayout(pageArrowEdit);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label_6 = new QLabel(pageArrowEdit);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_6);

        m_spForwardArrowOffset = new QSpinBox(pageArrowEdit);
        m_spForwardArrowOffset->setObjectName(QStringLiteral("m_spForwardArrowOffset"));
        m_spForwardArrowOffset->setMinimumSize(QSize(110, 0));
        m_spForwardArrowOffset->setValue(10);

        formLayout->setWidget(0, QFormLayout::FieldRole, m_spForwardArrowOffset);

        label_7 = new QLabel(pageArrowEdit);
        label_7->setObjectName(QStringLiteral("label_7"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_7);

        m_spBackwardArrowOffset = new QSpinBox(pageArrowEdit);
        m_spBackwardArrowOffset->setObjectName(QStringLiteral("m_spBackwardArrowOffset"));
        m_spBackwardArrowOffset->setMinimumSize(QSize(110, 0));
        m_spBackwardArrowOffset->setValue(10);

        formLayout->setWidget(1, QFormLayout::FieldRole, m_spBackwardArrowOffset);

        label_8 = new QLabel(pageArrowEdit);
        label_8->setObjectName(QStringLiteral("label_8"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_8);

        m_spArrowPenWidth = new QSpinBox(pageArrowEdit);
        m_spArrowPenWidth->setObjectName(QStringLiteral("m_spArrowPenWidth"));
        m_spArrowPenWidth->setMinimumSize(QSize(110, 0));
        m_spArrowPenWidth->setValue(10);

        formLayout->setWidget(2, QFormLayout::FieldRole, m_spArrowPenWidth);


        verticalLayout->addLayout(formLayout);

        m_pbApplyArrowOffset = new QPushButton(pageArrowEdit);
        m_pbApplyArrowOffset->setObjectName(QStringLiteral("m_pbApplyArrowOffset"));

        verticalLayout->addWidget(m_pbApplyArrowOffset);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout_5->addLayout(horizontalLayout, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 112, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer, 1, 0, 1, 1);

        m_ctlStackedWidget->addWidget(pageArrowEdit);
        pageDisplayEdit = new QWidget();
        pageDisplayEdit->setObjectName(QStringLiteral("pageDisplayEdit"));
        gridLayout_7 = new QGridLayout(pageDisplayEdit);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        m_tblDisplayItemPool = new QTableView(pageDisplayEdit);
        m_tblDisplayItemPool->setObjectName(QStringLiteral("m_tblDisplayItemPool"));

        horizontalLayout_2->addWidget(m_tblDisplayItemPool);


        gridLayout_7->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        m_ctlStackedWidget->addWidget(pageDisplayEdit);
        pageImageList = new QWidget();
        pageImageList->setObjectName(QStringLiteral("pageImageList"));
        gridLayout_10 = new QGridLayout(pageImageList);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        m_tblImageIndexList = new QTableView(pageImageList);
        m_tblImageIndexList->setObjectName(QStringLiteral("m_tblImageIndexList"));

        gridLayout_10->addWidget(m_tblImageIndexList, 0, 0, 1, 1);

        m_ctlStackedWidget->addWidget(pageImageList);

        horizontalLayout_3->addWidget(m_ctlStackedWidget);

        horizontalLayout_3->setStretch(1, 1);
        horizontalLayout_3->setStretch(2, 2);

        verticalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        btnClose = new QPushButton(QLineMapEdit);
        btnClose->setObjectName(QStringLiteral("btnClose"));

        horizontalLayout_4->addWidget(btnClose);


        verticalLayout_4->addLayout(horizontalLayout_4);

        verticalLayout_4->setStretch(0, 2);

        retranslateUi(QLineMapEdit);

        m_ctlStackedWidget->setCurrentIndex(5);


        QMetaObject::connectSlotsByName(QLineMapEdit);
    } // setupUi

    void retranslateUi(QDialog *QLineMapEdit)
    {
        QLineMapEdit->setWindowTitle(QApplication::translate("QLineMapEdit", "Route Map Editor", Q_NULLPTR));
        gbBasicMenu->setTitle(QApplication::translate("QLineMapEdit", "Property", Q_NULLPTR));
        label_13->setText(QApplication::translate("QLineMapEdit", "Title", Q_NULLPTR));
        label_14->setText(QApplication::translate("QLineMapEdit", "Tile Size", Q_NULLPTR));
        label_15->setText(QApplication::translate("QLineMapEdit", "Line Thickness", Q_NULLPTR));
        label_16->setText(QApplication::translate("QLineMapEdit", "Width", Q_NULLPTR));
        label_17->setText(QApplication::translate("QLineMapEdit", "Height", Q_NULLPTR));
        m_grpEditMode->setTitle(QApplication::translate("QLineMapEdit", "Edit Mode", Q_NULLPTR));
        m_ctlTile->setText(QApplication::translate("QLineMapEdit", "Tile (Line)", Q_NULLPTR));
        m_ctlArrow->setText(QApplication::translate("QLineMapEdit", "Arrow (No Use)", Q_NULLPTR));
<<<<<<< Updated upstream
        m_ctlDisplayItem->setText(QApplication::translate("QLineMapEdit", "Display Pool", Q_NULLPTR));
=======
>>>>>>> Stashed changes
        m_ctlNode->setText(QApplication::translate("QLineMapEdit", "Node (Station Name / Icon)", Q_NULLPTR));
        m_ctlImageList->setText(QApplication::translate("QLineMapEdit", "Image List (No Use)", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("QLineMapEdit", "Colour", Q_NULLPTR));
        label->setText(QApplication::translate("QLineMapEdit", "Background", Q_NULLPTR));
        m_ctlBackgroundColor->setText(QApplication::translate("QLineMapEdit", "Change Colour", Q_NULLPTR));
        label_2->setText(QApplication::translate("QLineMapEdit", "Line", Q_NULLPTR));
        m_ctlForegroundColor->setText(QApplication::translate("QLineMapEdit", "Change Colour", Q_NULLPTR));
        m_pbApplyColor->setText(QApplication::translate("QLineMapEdit", "Apply", Q_NULLPTR));
        m_ctlPassedColor->setText(QApplication::translate("QLineMapEdit", "Passed Station Color", Q_NULLPTR));
        label_3->setText(QApplication::translate("QLineMapEdit", "Passed Station Color", Q_NULLPTR));
        m_ctlFocusedColor->setText(QApplication::translate("QLineMapEdit", "Focused Station Color", Q_NULLPTR));
        label_4->setText(QApplication::translate("QLineMapEdit", "Focused Station Color", Q_NULLPTR));
        m_ctlLeftColor->setText(QApplication::translate("QLineMapEdit", "Remained Station Color", Q_NULLPTR));
        label_5->setText(QApplication::translate("QLineMapEdit", "Remained Station Color", Q_NULLPTR));
        m_ctlArrowPassedColor->setText(QApplication::translate("QLineMapEdit", "Arrow Color for Passed Area", Q_NULLPTR));
        label_9->setText(QApplication::translate("QLineMapEdit", "Arrow Color for Passed Area", Q_NULLPTR));
        m_ctlArrowFocusedColor->setText(QApplication::translate("QLineMapEdit", "Arrow Color for Focused Area", Q_NULLPTR));
        label_10->setText(QApplication::translate("QLineMapEdit", "Arrow Color for Focused Area", Q_NULLPTR));
        m_ctlArrowSecondFocusedColor->setText(QApplication::translate("QLineMapEdit", "Second Arrow Color for Focused Area", Q_NULLPTR));
        label_11->setText(QApplication::translate("QLineMapEdit", "Second Arrow Color for Focused Area", Q_NULLPTR));
        m_ctlArrowRemainedColor->setText(QApplication::translate("QLineMapEdit", "Arrow Color for Remained area", Q_NULLPTR));
        label_12->setText(QApplication::translate("QLineMapEdit", "Arrow Color for Remained area", Q_NULLPTR));
        pushButton->setText(QApplication::translate("QLineMapEdit", "Line (Link)", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("QLineMapEdit", "Spare", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("QLineMapEdit", "Spare", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("QLineMapEdit", "Spare", Q_NULLPTR));
        btnCopyProp->setText(QApplication::translate("QLineMapEdit", "Copy Selected Node Property", Q_NULLPTR));
        btnPasteNode->setText(QApplication::translate("QLineMapEdit", "Paste Node Name Property", Q_NULLPTR));
        btnPasteSpot->setText(QApplication::translate("QLineMapEdit", "Paste Node Icon Property", Q_NULLPTR));
        btnShowSpotDefault->setText(QApplication::translate("QLineMapEdit", "Set All Nodes Icon Default", Q_NULLPTR));
        btnShowSpotCustom->setText(QApplication::translate("QLineMapEdit", "Set All Nodes Icon Custom", Q_NULLPTR));
        label_6->setText(QApplication::translate("QLineMapEdit", "Forward ", Q_NULLPTR));
        label_7->setText(QApplication::translate("QLineMapEdit", "Backward", Q_NULLPTR));
        label_8->setText(QApplication::translate("QLineMapEdit", "Width", Q_NULLPTR));
        m_pbApplyArrowOffset->setText(QApplication::translate("QLineMapEdit", "Apply", Q_NULLPTR));
        btnClose->setText(QApplication::translate("QLineMapEdit", "Close", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QLineMapEdit: public Ui_QLineMapEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QLINEMAPEDIT_H
