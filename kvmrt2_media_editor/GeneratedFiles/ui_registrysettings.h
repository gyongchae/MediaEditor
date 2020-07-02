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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_RegistrySettings
{
public:
    QVBoxLayout *verticalLayout;
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
        RegistrySettings->resize(349, 159);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RegistrySettings->sizePolicy().hasHeightForWidth());
        RegistrySettings->setSizePolicy(sizePolicy);
        RegistrySettings->setMinimumSize(QSize(349, 159));
        RegistrySettings->setBaseSize(QSize(349, 159));
        RegistrySettings->setContextMenuPolicy(Qt::NoContextMenu);
        verticalLayout = new QVBoxLayout(RegistrySettings);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        m_leFontFileSavePath = new QLineEdit(RegistrySettings);
        m_leFontFileSavePath->setObjectName(QStringLiteral("m_leFontFileSavePath"));
        m_leFontFileSavePath->setEnabled(false);

        gridLayout->addWidget(m_leFontFileSavePath, 1, 1, 1, 1);

        btnFont = new QPushButton(RegistrySettings);
        btnFont->setObjectName(QStringLiteral("btnFont"));

        gridLayout->addWidget(btnFont, 1, 2, 1, 1);

        label_3 = new QLabel(RegistrySettings);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        m_leAudioFileSavePath = new QLineEdit(RegistrySettings);
        m_leAudioFileSavePath->setObjectName(QStringLiteral("m_leAudioFileSavePath"));
        m_leAudioFileSavePath->setEnabled(false);

        gridLayout->addWidget(m_leAudioFileSavePath, 2, 1, 1, 1);

        btnAudio = new QPushButton(RegistrySettings);
        btnAudio->setObjectName(QStringLiteral("btnAudio"));

        gridLayout->addWidget(btnAudio, 2, 2, 1, 1);

        m_leVideoFileSavePath = new QLineEdit(RegistrySettings);
        m_leVideoFileSavePath->setObjectName(QStringLiteral("m_leVideoFileSavePath"));
        m_leVideoFileSavePath->setEnabled(false);

        gridLayout->addWidget(m_leVideoFileSavePath, 3, 1, 1, 1);

        btnVideo = new QPushButton(RegistrySettings);
        btnVideo->setObjectName(QStringLiteral("btnVideo"));

        gridLayout->addWidget(btnVideo, 3, 2, 1, 1);

        label_2 = new QLabel(RegistrySettings);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        label = new QLabel(RegistrySettings);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        m_leDBPath = new QLineEdit(RegistrySettings);
        m_leDBPath->setObjectName(QStringLiteral("m_leDBPath"));
        m_leDBPath->setEnabled(false);

        gridLayout->addWidget(m_leDBPath, 0, 1, 1, 1);

        btnDB = new QPushButton(RegistrySettings);
        btnDB->setObjectName(QStringLiteral("btnDB"));

        gridLayout->addWidget(btnDB, 0, 2, 1, 1);

        label_4 = new QLabel(RegistrySettings);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        btnOpenDBPath = new QPushButton(RegistrySettings);
        btnOpenDBPath->setObjectName(QStringLiteral("btnOpenDBPath"));

        gridLayout->addWidget(btnOpenDBPath, 0, 3, 1, 1);

        gridLayout->setColumnStretch(1, 1);

        verticalLayout->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

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


        verticalLayout->addLayout(horizontalLayout);

        QWidget::setTabOrder(m_pbApply, m_pbCancel);
        QWidget::setTabOrder(m_pbCancel, m_leVideoFileSavePath);
        QWidget::setTabOrder(m_leVideoFileSavePath, m_leDBPath);

        retranslateUi(RegistrySettings);

        QMetaObject::connectSlotsByName(RegistrySettings);
    } // setupUi

    void retranslateUi(QDialog *RegistrySettings)
    {
        RegistrySettings->setWindowTitle(QApplication::translate("RegistrySettings", "Path Settings", Q_NULLPTR));
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
