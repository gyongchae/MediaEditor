/********************************************************************************
** Form generated from reading UI file 'linemappreset.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LINEMAPPRESET_H
#define UI_LINEMAPPRESET_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LineMapPreset
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label_5;
    QLineEdit *editTitle;
    QLabel *label;
    QComboBox *m_cbTileSize;
    QLabel *label_2;
    QComboBox *m_cbLineThick;
    QLabel *label_3;
    QComboBox *m_cbMapWidth;
    QLabel *label_4;
    QComboBox *m_cbMapHeight;
    QLabel *label_6;
    QComboBox *m_cbMapBound;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *LineMapPreset)
    {
        if (LineMapPreset->objectName().isEmpty())
            LineMapPreset->setObjectName(QStringLiteral("LineMapPreset"));
        LineMapPreset->resize(263, 217);
        verticalLayout = new QVBoxLayout(LineMapPreset);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label_5 = new QLabel(LineMapPreset);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_5);

        editTitle = new QLineEdit(LineMapPreset);
        editTitle->setObjectName(QStringLiteral("editTitle"));

        formLayout->setWidget(0, QFormLayout::FieldRole, editTitle);

        label = new QLabel(LineMapPreset);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        m_cbTileSize = new QComboBox(LineMapPreset);
        m_cbTileSize->setObjectName(QStringLiteral("m_cbTileSize"));
        m_cbTileSize->setEditable(true);

        formLayout->setWidget(1, QFormLayout::FieldRole, m_cbTileSize);

        label_2 = new QLabel(LineMapPreset);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        m_cbLineThick = new QComboBox(LineMapPreset);
        m_cbLineThick->setObjectName(QStringLiteral("m_cbLineThick"));
        m_cbLineThick->setEditable(true);

        formLayout->setWidget(2, QFormLayout::FieldRole, m_cbLineThick);

        label_3 = new QLabel(LineMapPreset);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_3);

        m_cbMapWidth = new QComboBox(LineMapPreset);
        m_cbMapWidth->setObjectName(QStringLiteral("m_cbMapWidth"));
        m_cbMapWidth->setEditable(true);

        formLayout->setWidget(3, QFormLayout::FieldRole, m_cbMapWidth);

        label_4 = new QLabel(LineMapPreset);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_4);

        m_cbMapHeight = new QComboBox(LineMapPreset);
        m_cbMapHeight->setObjectName(QStringLiteral("m_cbMapHeight"));
        m_cbMapHeight->setEditable(true);

        formLayout->setWidget(4, QFormLayout::FieldRole, m_cbMapHeight);

        label_6 = new QLabel(LineMapPreset);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_6);

        m_cbMapBound = new QComboBox(LineMapPreset);
        m_cbMapBound->setObjectName(QStringLiteral("m_cbMapBound"));
        m_cbMapBound->setEditable(false);

        formLayout->setWidget(5, QFormLayout::FieldRole, m_cbMapBound);


        verticalLayout->addLayout(formLayout);

        verticalSpacer = new QSpacerItem(20, 2, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        buttonBox = new QDialogButtonBox(LineMapPreset);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_2->addWidget(buttonBox);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(LineMapPreset);

        QMetaObject::connectSlotsByName(LineMapPreset);
    } // setupUi

    void retranslateUi(QDialog *LineMapPreset)
    {
        LineMapPreset->setWindowTitle(QApplication::translate("LineMapPreset", "Preset", Q_NULLPTR));
        label_5->setText(QApplication::translate("LineMapPreset", "Title", Q_NULLPTR));
        editTitle->setPlaceholderText(QApplication::translate("LineMapPreset", "Title goes here...", Q_NULLPTR));
        label->setText(QApplication::translate("LineMapPreset", "Tile Size", Q_NULLPTR));
        m_cbTileSize->clear();
        m_cbTileSize->insertItems(0, QStringList()
         << QApplication::translate("LineMapPreset", "36", Q_NULLPTR)
        );
        label_2->setText(QApplication::translate("LineMapPreset", "Line Thickness", Q_NULLPTR));
        m_cbLineThick->clear();
        m_cbLineThick->insertItems(0, QStringList()
         << QApplication::translate("LineMapPreset", "10", Q_NULLPTR)
        );
        label_3->setText(QApplication::translate("LineMapPreset", "Width", Q_NULLPTR));
        m_cbMapWidth->clear();
        m_cbMapWidth->insertItems(0, QStringList()
         << QApplication::translate("LineMapPreset", "1920", Q_NULLPTR)
        );
        label_4->setText(QApplication::translate("LineMapPreset", "Height", Q_NULLPTR));
        m_cbMapHeight->clear();
        m_cbMapHeight->insertItems(0, QStringList()
         << QApplication::translate("LineMapPreset", "360", Q_NULLPTR)
        );
        label_6->setText(QApplication::translate("LineMapPreset", "Bound", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LineMapPreset: public Ui_LineMapPreset {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LINEMAPPRESET_H
