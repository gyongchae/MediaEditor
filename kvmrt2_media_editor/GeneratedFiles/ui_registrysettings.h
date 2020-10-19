/********************************************************************************
** Form generated from reading UI file 'registrysettings.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRYSETTINGS_H
#define UI_REGISTRYSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_RegistrySettings
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QSpinBox *sbVer1;
    QLabel *label_6;
    QSpinBox *sbVer2;
    QLabel *label_7;
    QSpinBox *sbVer3;
    QTableView *m_tblOPDataVersion;
    QGroupBox *gbFilePath;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLineEdit *m_leFontFileSavePath;
    QPushButton *btnFont;
    QLabel *label_3;
    QLineEdit *m_leAudioFileSavePath;
    QPushButton *btnAudio;
    QLineEdit *m_leVideoFileSavePath;
    QPushButton *btnVideo;
    QLabel *label_2;
    QLabel *label;
    QLineEdit *m_leDBPath;
    QPushButton *btnDB;
    QLabel *label_4;
    QPushButton *btnOpenDBPath;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_pbApply;
    QPushButton *m_pbCancel;

    void setupUi(QDialog *RegistrySettings)
    {
        if (RegistrySettings->objectName().isEmpty())
            RegistrySettings->setObjectName(QStringLiteral("RegistrySettings"));
        RegistrySettings->setWindowModality(Qt::WindowModal);
        RegistrySettings->resize(443, 457);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RegistrySettings->sizePolicy().hasHeightForWidth());
        RegistrySettings->setSizePolicy(sizePolicy);
        RegistrySettings->setMinimumSize(QSize(349, 159));
        RegistrySettings->setBaseSize(QSize(349, 159));
        RegistrySettings->setContextMenuPolicy(Qt::NoContextMenu);
        verticalLayout_2 = new QVBoxLayout(RegistrySettings);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_5 = new QLabel(RegistrySettings);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_2->addWidget(label_5);

        sbVer1 = new QSpinBox(RegistrySettings);
        sbVer1->setObjectName(QStringLiteral("sbVer1"));

        horizontalLayout_2->addWidget(sbVer1);

        label_6 = new QLabel(RegistrySettings);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_6);

        sbVer2 = new QSpinBox(RegistrySettings);
        sbVer2->setObjectName(QStringLiteral("sbVer2"));

        horizontalLayout_2->addWidget(sbVer2);

        label_7 = new QLabel(RegistrySettings);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_7);

        sbVer3 = new QSpinBox(RegistrySettings);
        sbVer3->setObjectName(QStringLiteral("sbVer3"));

        horizontalLayout_2->addWidget(sbVer3);

        horizontalLayout_2->setStretch(1, 1);
        horizontalLayout_2->setStretch(3, 1);
        horizontalLayout_2->setStretch(5, 1);

        verticalLayout->addLayout(horizontalLayout_2);

        m_tblOPDataVersion = new QTableView(RegistrySettings);
        m_tblOPDataVersion->setObjectName(QStringLiteral("m_tblOPDataVersion"));

        verticalLayout->addWidget(m_tblOPDataVersion);


        verticalLayout_2->addLayout(verticalLayout);

        gbFilePath = new QGroupBox(RegistrySettings);
        gbFilePath->setObjectName(QStringLiteral("gbFilePath"));
        gridLayout_2 = new QGridLayout(gbFilePath);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        m_leFontFileSavePath = new QLineEdit(gbFilePath);
        m_leFontFileSavePath->setObjectName(QStringLiteral("m_leFontFileSavePath"));
        m_leFontFileSavePath->setEnabled(false);

        gridLayout->addWidget(m_leFontFileSavePath, 1, 1, 1, 1);

        btnFont = new QPushButton(gbFilePath);
        btnFont->setObjectName(QStringLiteral("btnFont"));

        gridLayout->addWidget(btnFont, 1, 2, 1, 1);

        label_3 = new QLabel(gbFilePath);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        m_leAudioFileSavePath = new QLineEdit(gbFilePath);
        m_leAudioFileSavePath->setObjectName(QStringLiteral("m_leAudioFileSavePath"));
        m_leAudioFileSavePath->setEnabled(false);

        gridLayout->addWidget(m_leAudioFileSavePath, 2, 1, 1, 1);

        btnAudio = new QPushButton(gbFilePath);
        btnAudio->setObjectName(QStringLiteral("btnAudio"));

        gridLayout->addWidget(btnAudio, 2, 2, 1, 1);

        m_leVideoFileSavePath = new QLineEdit(gbFilePath);
        m_leVideoFileSavePath->setObjectName(QStringLiteral("m_leVideoFileSavePath"));
        m_leVideoFileSavePath->setEnabled(false);

        gridLayout->addWidget(m_leVideoFileSavePath, 3, 1, 1, 1);

        btnVideo = new QPushButton(gbFilePath);
        btnVideo->setObjectName(QStringLiteral("btnVideo"));

        gridLayout->addWidget(btnVideo, 3, 2, 1, 1);

        label_2 = new QLabel(gbFilePath);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        label = new QLabel(gbFilePath);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        m_leDBPath = new QLineEdit(gbFilePath);
        m_leDBPath->setObjectName(QStringLiteral("m_leDBPath"));
        m_leDBPath->setEnabled(false);

        gridLayout->addWidget(m_leDBPath, 0, 1, 1, 1);

        btnDB = new QPushButton(gbFilePath);
        btnDB->setObjectName(QStringLiteral("btnDB"));

        gridLayout->addWidget(btnDB, 0, 2, 1, 1);

        label_4 = new QLabel(gbFilePath);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        btnOpenDBPath = new QPushButton(gbFilePath);
        btnOpenDBPath->setObjectName(QStringLiteral("btnOpenDBPath"));

        gridLayout->addWidget(btnOpenDBPath, 0, 3, 1, 1);

        gridLayout->setColumnStretch(1, 1);

        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        verticalLayout_2->addWidget(gbFilePath);

        verticalSpacer = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        m_pbApply = new QPushButton(RegistrySettings);
        m_pbApply->setObjectName(QStringLiteral("m_pbApply"));

        horizontalLayout->addWidget(m_pbApply);

        m_pbCancel = new QPushButton(RegistrySettings);
        m_pbCancel->setObjectName(QStringLiteral("m_pbCancel"));

        horizontalLayout->addWidget(m_pbCancel);


        verticalLayout_2->addLayout(horizontalLayout);

        QWidget::setTabOrder(m_pbApply, m_pbCancel);
        QWidget::setTabOrder(m_pbCancel, m_leVideoFileSavePath);
        QWidget::setTabOrder(m_leVideoFileSavePath, m_leDBPath);

        retranslateUi(RegistrySettings);

        QMetaObject::connectSlotsByName(RegistrySettings);
    } // setupUi

    void retranslateUi(QDialog *RegistrySettings)
    {
        RegistrySettings->setWindowTitle(QApplication::translate("RegistrySettings", "DB Version", Q_NULLPTR));
        label_5->setText(QApplication::translate("RegistrySettings", "Data Version:", Q_NULLPTR));
        label_6->setText(QApplication::translate("RegistrySettings", ".", Q_NULLPTR));
        label_7->setText(QApplication::translate("RegistrySettings", ".", Q_NULLPTR));
        gbFilePath->setTitle(QApplication::translate("RegistrySettings", "File Path", Q_NULLPTR));
        btnFont->setText(QApplication::translate("RegistrySettings", "Load", Q_NULLPTR));
        label_3->setText(QApplication::translate("RegistrySettings", "Audio File Path", Q_NULLPTR));
        btnAudio->setText(QApplication::translate("RegistrySettings", "Load", Q_NULLPTR));
        btnVideo->setText(QApplication::translate("RegistrySettings", "Load", Q_NULLPTR));
        label_2->setText(QApplication::translate("RegistrySettings", "Video File Path", Q_NULLPTR));
        label->setText(QApplication::translate("RegistrySettings", "DB Path", Q_NULLPTR));
        btnDB->setText(QApplication::translate("RegistrySettings", "Load", Q_NULLPTR));
        label_4->setText(QApplication::translate("RegistrySettings", "Font File Path", Q_NULLPTR));
        btnOpenDBPath->setText(QApplication::translate("RegistrySettings", "Open", Q_NULLPTR));
        m_pbApply->setText(QApplication::translate("RegistrySettings", "Apply", Q_NULLPTR));
        m_pbCancel->setText(QApplication::translate("RegistrySettings", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RegistrySettings: public Ui_RegistrySettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRYSETTINGS_H
