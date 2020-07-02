/********************************************************************************
** Form generated from reading UI file 'displayItemPreset.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISPLAYITEMPRESET_H
#define UI_DISPLAYITEMPRESET_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_displayItemPreset
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *m_leDescription;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_5;
    QSpinBox *m_spWidth;
    QLabel *label_3;
    QSpinBox *m_spHeight;
    QSpinBox *m_spDuration;
    QLabel *label_4;
    QLabel *label_6;
    QComboBox *comboDisplayType;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *displayItemPreset)
    {
        if (displayItemPreset->objectName().isEmpty())
            displayItemPreset->setObjectName(QStringLiteral("displayItemPreset"));
        displayItemPreset->resize(280, 218);
        displayItemPreset->setSizeIncrement(QSize(0, 0));
        verticalLayout = new QVBoxLayout(displayItemPreset);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(displayItemPreset);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        m_leDescription = new QLineEdit(displayItemPreset);
        m_leDescription->setObjectName(QStringLiteral("m_leDescription"));

        gridLayout->addWidget(m_leDescription, 0, 1, 1, 1);

        label_2 = new QLabel(displayItemPreset);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_5 = new QLabel(displayItemPreset);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout->addWidget(label_5);

        m_spWidth = new QSpinBox(displayItemPreset);
        m_spWidth->setObjectName(QStringLiteral("m_spWidth"));

        horizontalLayout->addWidget(m_spWidth);

        label_3 = new QLabel(displayItemPreset);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        m_spHeight = new QSpinBox(displayItemPreset);
        m_spHeight->setObjectName(QStringLiteral("m_spHeight"));

        horizontalLayout->addWidget(m_spHeight);

        horizontalLayout->setStretch(1, 1);
        horizontalLayout->setStretch(3, 1);

        gridLayout->addLayout(horizontalLayout, 1, 1, 1, 1);

        m_spDuration = new QSpinBox(displayItemPreset);
        m_spDuration->setObjectName(QStringLiteral("m_spDuration"));

        gridLayout->addWidget(m_spDuration, 2, 1, 1, 1);

        label_4 = new QLabel(displayItemPreset);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        label_6 = new QLabel(displayItemPreset);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 3, 0, 1, 1);

        comboDisplayType = new QComboBox(displayItemPreset);
        comboDisplayType->setObjectName(QStringLiteral("comboDisplayType"));

        gridLayout->addWidget(comboDisplayType, 3, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        buttonBox = new QDialogButtonBox(displayItemPreset);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_2->addWidget(buttonBox);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(displayItemPreset);

        QMetaObject::connectSlotsByName(displayItemPreset);
    } // setupUi

    void retranslateUi(QDialog *displayItemPreset)
    {
        displayItemPreset->setWindowTitle(QApplication::translate("displayItemPreset", "Preset", Q_NULLPTR));
        label->setText(QApplication::translate("displayItemPreset", "Title", Q_NULLPTR));
        m_leDescription->setPlaceholderText(QApplication::translate("displayItemPreset", "Title goes here...", Q_NULLPTR));
        label_2->setText(QApplication::translate("displayItemPreset", "Size", Q_NULLPTR));
        label_5->setText(QApplication::translate("displayItemPreset", "Width:", Q_NULLPTR));
        label_3->setText(QApplication::translate("displayItemPreset", "Height:", Q_NULLPTR));
        label_4->setText(QApplication::translate("displayItemPreset", "Duration", Q_NULLPTR));
        label_6->setText(QApplication::translate("displayItemPreset", "Display Type", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class displayItemPreset: public Ui_displayItemPreset {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPLAYITEMPRESET_H
