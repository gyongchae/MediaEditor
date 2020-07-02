/********************************************************************************
** Form generated from reading UI file 'QLineMapPreview.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QLINEMAPPREVIEW_H
#define UI_QLINEMAPPREVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_QLineMapPreview
{
public:
    QGroupBox *m_grpTrainNum;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *m_leTrainNumber;
    QPushButton *m_pbTNInput;
    QGroupBox *m_grpDistList;
    QGridLayout *gridLayout_2;
    QTableView *m_tblStopPtnRoutes;
    QGroupBox *m_grpProgBar;
    QGridLayout *gridLayout_3;
    QSlider *m_ctlProgress;

    void setupUi(QDialog *QLineMapPreview)
    {
        if (QLineMapPreview->objectName().isEmpty())
            QLineMapPreview->setObjectName(QStringLiteral("QLineMapPreview"));
        QLineMapPreview->resize(1102, 868);
        m_grpTrainNum = new QGroupBox(QLineMapPreview);
        m_grpTrainNum->setObjectName(QStringLiteral("m_grpTrainNum"));
        m_grpTrainNum->setGeometry(QRect(200, 70, 314, 69));
        gridLayout = new QGridLayout(m_grpTrainNum);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        m_leTrainNumber = new QLineEdit(m_grpTrainNum);
        m_leTrainNumber->setObjectName(QStringLiteral("m_leTrainNumber"));

        horizontalLayout->addWidget(m_leTrainNumber);

        m_pbTNInput = new QPushButton(m_grpTrainNum);
        m_pbTNInput->setObjectName(QStringLiteral("m_pbTNInput"));

        horizontalLayout->addWidget(m_pbTNInput);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        m_grpDistList = new QGroupBox(QLineMapPreview);
        m_grpDistList->setObjectName(QStringLiteral("m_grpDistList"));
        m_grpDistList->setGeometry(QRect(390, 150, 280, 231));
        gridLayout_2 = new QGridLayout(m_grpDistList);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        m_tblStopPtnRoutes = new QTableView(m_grpDistList);
        m_tblStopPtnRoutes->setObjectName(QStringLiteral("m_tblStopPtnRoutes"));

        gridLayout_2->addWidget(m_tblStopPtnRoutes, 0, 0, 1, 1);

        m_grpProgBar = new QGroupBox(QLineMapPreview);
        m_grpProgBar->setObjectName(QStringLiteral("m_grpProgBar"));
        m_grpProgBar->setGeometry(QRect(220, 400, 108, 61));
        gridLayout_3 = new QGridLayout(m_grpProgBar);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        m_ctlProgress = new QSlider(m_grpProgBar);
        m_ctlProgress->setObjectName(QStringLiteral("m_ctlProgress"));
        m_ctlProgress->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(m_ctlProgress, 0, 0, 1, 1);


        retranslateUi(QLineMapPreview);

        QMetaObject::connectSlotsByName(QLineMapPreview);
    } // setupUi

    void retranslateUi(QDialog *QLineMapPreview)
    {
        QLineMapPreview->setWindowTitle(QApplication::translate("QLineMapPreview", "QLineMapPreview", Q_NULLPTR));
        m_grpTrainNum->setTitle(QApplication::translate("QLineMapPreview", "Train Number", Q_NULLPTR));
        m_pbTNInput->setText(QApplication::translate("QLineMapPreview", "Input", Q_NULLPTR));
        m_grpDistList->setTitle(QApplication::translate("QLineMapPreview", "DistanceList", Q_NULLPTR));
        m_grpProgBar->setTitle(QApplication::translate("QLineMapPreview", "Progress bar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QLineMapPreview: public Ui_QLineMapPreview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QLINEMAPPREVIEW_H
