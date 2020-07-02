/********************************************************************************
** Form generated from reading UI file 'ledindicatoredit.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEDINDICATOREDIT_H
#define UI_LEDINDICATOREDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_LEDIndicatorEdit
{
public:
    QGridLayout *gridLayout_4;
    QGridLayout *m_layoutLED;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *m_pbAccept;
    QPushButton *m_pbCancel;
    QHBoxLayout *horizontalLayout;
    QGroupBox *m_grpButton;
    QGridLayout *gridLayout;
    QRadioButton *m_rbSelectArea;
    QRadioButton *m_rbPreview;
    QSpacerItem *verticalSpacer;
    QRadioButton *m_rbEdit;
    QLabel *m_tlSelectArea;
    QGroupBox *m_grpPageSettings;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_9;
    QSpinBox *m_spPages;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_10;
    QSpinBox *m_spUnitWidth;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_11;
    QSpinBox *m_spUnitHeight;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_8;
    QComboBox *m_cbPagingMode;
    QSpacerItem *verticalSpacer_2;
    QGroupBox *m_grpMsgSettings;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QPlainTextEdit *m_teVMIMS;
    QHBoxLayout *horizontalLayout_12;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_5;
    QComboBox *m_cbHAIMS;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_7;
    QComboBox *m_cbVAIMS;
    QPushButton *m_pbLoadBitmap;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_13;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QFontComboBox *m_cbFontIMS;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QSpinBox *m_spFontSizeIMS;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *m_pbClrBkGnd;
    QPushButton *m_pbClrFrGnd;
    QPushButton *m_pbSetImage;

    void setupUi(QDialog *LEDIndicatorEdit)
    {
        if (LEDIndicatorEdit->objectName().isEmpty())
            LEDIndicatorEdit->setObjectName(QStringLiteral("LEDIndicatorEdit"));
        LEDIndicatorEdit->resize(1340, 514);
        gridLayout_4 = new QGridLayout(LEDIndicatorEdit);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        m_layoutLED = new QGridLayout();
        m_layoutLED->setSpacing(6);
        m_layoutLED->setObjectName(QStringLiteral("m_layoutLED"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        m_pbAccept = new QPushButton(LEDIndicatorEdit);
        m_pbAccept->setObjectName(QStringLiteral("m_pbAccept"));

        horizontalLayout_2->addWidget(m_pbAccept);

        m_pbCancel = new QPushButton(LEDIndicatorEdit);
        m_pbCancel->setObjectName(QStringLiteral("m_pbCancel"));

        horizontalLayout_2->addWidget(m_pbCancel);


        m_layoutLED->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        m_grpButton = new QGroupBox(LEDIndicatorEdit);
        m_grpButton->setObjectName(QStringLiteral("m_grpButton"));
        m_grpButton->setMaximumSize(QSize(16777215, 160));
        gridLayout = new QGridLayout(m_grpButton);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        m_rbSelectArea = new QRadioButton(m_grpButton);
        m_rbSelectArea->setObjectName(QStringLiteral("m_rbSelectArea"));

        gridLayout->addWidget(m_rbSelectArea, 1, 0, 1, 1);

        m_rbPreview = new QRadioButton(m_grpButton);
        m_rbPreview->setObjectName(QStringLiteral("m_rbPreview"));

        gridLayout->addWidget(m_rbPreview, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 4, 0, 1, 1);

        m_rbEdit = new QRadioButton(m_grpButton);
        m_rbEdit->setObjectName(QStringLiteral("m_rbEdit"));

        gridLayout->addWidget(m_rbEdit, 2, 0, 1, 1);

        m_tlSelectArea = new QLabel(m_grpButton);
        m_tlSelectArea->setObjectName(QStringLiteral("m_tlSelectArea"));

        gridLayout->addWidget(m_tlSelectArea, 3, 0, 1, 1);


        horizontalLayout->addWidget(m_grpButton);

        m_grpPageSettings = new QGroupBox(LEDIndicatorEdit);
        m_grpPageSettings->setObjectName(QStringLiteral("m_grpPageSettings"));
        m_grpPageSettings->setMaximumSize(QSize(16777215, 160));
        gridLayout_2 = new QGridLayout(m_grpPageSettings);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        label_9 = new QLabel(m_grpPageSettings);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_15->addWidget(label_9);

        m_spPages = new QSpinBox(m_grpPageSettings);
        m_spPages->setObjectName(QStringLiteral("m_spPages"));

        horizontalLayout_15->addWidget(m_spPages);


        gridLayout_2->addLayout(horizontalLayout_15, 0, 0, 1, 1);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        label_10 = new QLabel(m_grpPageSettings);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_16->addWidget(label_10);

        m_spUnitWidth = new QSpinBox(m_grpPageSettings);
        m_spUnitWidth->setObjectName(QStringLiteral("m_spUnitWidth"));

        horizontalLayout_16->addWidget(m_spUnitWidth);


        gridLayout_2->addLayout(horizontalLayout_16, 1, 0, 1, 1);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        label_11 = new QLabel(m_grpPageSettings);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_17->addWidget(label_11);

        m_spUnitHeight = new QSpinBox(m_grpPageSettings);
        m_spUnitHeight->setObjectName(QStringLiteral("m_spUnitHeight"));

        horizontalLayout_17->addWidget(m_spUnitHeight);


        gridLayout_2->addLayout(horizontalLayout_17, 2, 0, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_8 = new QLabel(m_grpPageSettings);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_10->addWidget(label_8);

        m_cbPagingMode = new QComboBox(m_grpPageSettings);
        m_cbPagingMode->setObjectName(QStringLiteral("m_cbPagingMode"));

        horizontalLayout_10->addWidget(m_cbPagingMode);


        gridLayout_2->addLayout(horizontalLayout_10, 3, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 4, 0, 1, 1);


        horizontalLayout->addWidget(m_grpPageSettings);

        m_grpMsgSettings = new QGroupBox(LEDIndicatorEdit);
        m_grpMsgSettings->setObjectName(QStringLiteral("m_grpMsgSettings"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_grpMsgSettings->sizePolicy().hasHeightForWidth());
        m_grpMsgSettings->setSizePolicy(sizePolicy);
        m_grpMsgSettings->setMaximumSize(QSize(16777215, 160));
        gridLayout_3 = new QGridLayout(m_grpMsgSettings);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setSizeConstraint(QLayout::SetFixedSize);
        label_3 = new QLabel(m_grpMsgSettings);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMaximumSize(QSize(16777215, 20));

        horizontalLayout_5->addWidget(label_3);

        m_teVMIMS = new QPlainTextEdit(m_grpMsgSettings);
        m_teVMIMS->setObjectName(QStringLiteral("m_teVMIMS"));
        m_teVMIMS->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_5->addWidget(m_teVMIMS);


        gridLayout_3->addLayout(horizontalLayout_5, 0, 0, 1, 1);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_5 = new QLabel(m_grpMsgSettings);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_11->addWidget(label_5);

        m_cbHAIMS = new QComboBox(m_grpMsgSettings);
        m_cbHAIMS->setObjectName(QStringLiteral("m_cbHAIMS"));

        horizontalLayout_11->addWidget(m_cbHAIMS);


        horizontalLayout_12->addLayout(horizontalLayout_11);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        label_7 = new QLabel(m_grpMsgSettings);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_14->addWidget(label_7);

        m_cbVAIMS = new QComboBox(m_grpMsgSettings);
        m_cbVAIMS->setObjectName(QStringLiteral("m_cbVAIMS"));

        horizontalLayout_14->addWidget(m_cbVAIMS);


        horizontalLayout_12->addLayout(horizontalLayout_14);

        m_pbLoadBitmap = new QPushButton(m_grpMsgSettings);
        m_pbLoadBitmap->setObjectName(QStringLiteral("m_pbLoadBitmap"));

        horizontalLayout_12->addWidget(m_pbLoadBitmap);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_6);


        gridLayout_3->addLayout(horizontalLayout_12, 1, 0, 1, 1);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_2 = new QLabel(m_grpMsgSettings);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_4->addWidget(label_2);

        m_cbFontIMS = new QFontComboBox(m_grpMsgSettings);
        m_cbFontIMS->setObjectName(QStringLiteral("m_cbFontIMS"));

        horizontalLayout_4->addWidget(m_cbFontIMS);


        horizontalLayout_13->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_4 = new QLabel(m_grpMsgSettings);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_6->addWidget(label_4);

        m_spFontSizeIMS = new QSpinBox(m_grpMsgSettings);
        m_spFontSizeIMS->setObjectName(QStringLiteral("m_spFontSizeIMS"));

        horizontalLayout_6->addWidget(m_spFontSizeIMS);


        horizontalLayout_13->addLayout(horizontalLayout_6);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        m_pbClrBkGnd = new QPushButton(m_grpMsgSettings);
        m_pbClrBkGnd->setObjectName(QStringLiteral("m_pbClrBkGnd"));

        horizontalLayout_3->addWidget(m_pbClrBkGnd);

        m_pbClrFrGnd = new QPushButton(m_grpMsgSettings);
        m_pbClrFrGnd->setObjectName(QStringLiteral("m_pbClrFrGnd"));

        horizontalLayout_3->addWidget(m_pbClrFrGnd);


        horizontalLayout_13->addLayout(horizontalLayout_3);

        m_pbSetImage = new QPushButton(m_grpMsgSettings);
        m_pbSetImage->setObjectName(QStringLiteral("m_pbSetImage"));

        horizontalLayout_13->addWidget(m_pbSetImage);


        gridLayout_3->addLayout(horizontalLayout_13, 2, 0, 1, 1);


        horizontalLayout->addWidget(m_grpMsgSettings);


        m_layoutLED->addLayout(horizontalLayout, 0, 0, 1, 1);


        gridLayout_4->addLayout(m_layoutLED, 0, 0, 1, 1);


        retranslateUi(LEDIndicatorEdit);

        QMetaObject::connectSlotsByName(LEDIndicatorEdit);
    } // setupUi

    void retranslateUi(QDialog *LEDIndicatorEdit)
    {
        LEDIndicatorEdit->setWindowTitle(QApplication::translate("LEDIndicatorEdit", "LEDIndicatorEdit", Q_NULLPTR));
        m_pbAccept->setText(QApplication::translate("LEDIndicatorEdit", "Accept", Q_NULLPTR));
        m_pbCancel->setText(QApplication::translate("LEDIndicatorEdit", "Cancel", Q_NULLPTR));
        m_grpButton->setTitle(QApplication::translate("LEDIndicatorEdit", "Select Mode", Q_NULLPTR));
        m_rbSelectArea->setText(QApplication::translate("LEDIndicatorEdit", "Select Area", Q_NULLPTR));
        m_rbPreview->setText(QApplication::translate("LEDIndicatorEdit", "Preview", Q_NULLPTR));
        m_rbEdit->setText(QApplication::translate("LEDIndicatorEdit", "Edit", Q_NULLPTR));
        m_tlSelectArea->setText(QString());
        m_grpPageSettings->setTitle(QApplication::translate("LEDIndicatorEdit", "Page settings", Q_NULLPTR));
        label_9->setText(QApplication::translate("LEDIndicatorEdit", "Total Pages", Q_NULLPTR));
        label_10->setText(QApplication::translate("LEDIndicatorEdit", "Unit Width", Q_NULLPTR));
        label_11->setText(QApplication::translate("LEDIndicatorEdit", "Unit Height", Q_NULLPTR));
        label_8->setText(QApplication::translate("LEDIndicatorEdit", "Paging Mode", Q_NULLPTR));
        m_grpMsgSettings->setTitle(QApplication::translate("LEDIndicatorEdit", "Message Settings", Q_NULLPTR));
        label_3->setText(QApplication::translate("LEDIndicatorEdit", "Visual Message", Q_NULLPTR));
        label_5->setText(QApplication::translate("LEDIndicatorEdit", "Horizontal Align", Q_NULLPTR));
        label_7->setText(QApplication::translate("LEDIndicatorEdit", "Vertical Align", Q_NULLPTR));
        m_pbLoadBitmap->setText(QApplication::translate("LEDIndicatorEdit", "Load Image", Q_NULLPTR));
        label_2->setText(QApplication::translate("LEDIndicatorEdit", "Font Name", Q_NULLPTR));
        label_4->setText(QApplication::translate("LEDIndicatorEdit", "Size", Q_NULLPTR));
        m_pbClrBkGnd->setText(QApplication::translate("LEDIndicatorEdit", "Background", Q_NULLPTR));
        m_pbClrFrGnd->setText(QApplication::translate("LEDIndicatorEdit", "Foreground", Q_NULLPTR));
        m_pbSetImage->setText(QApplication::translate("LEDIndicatorEdit", "Set current Text", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LEDIndicatorEdit: public Ui_LEDIndicatorEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEDINDICATOREDIT_H
