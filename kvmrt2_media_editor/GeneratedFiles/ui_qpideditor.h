/********************************************************************************
** Form generated from reading UI file 'qpideditor.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QPIDEDITOR_H
#define UI_QPIDEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_QPIDEditor
{
public:

    void setupUi(QDialog *QPIDEditor)
    {
        if (QPIDEditor->objectName().isEmpty())
            QPIDEditor->setObjectName(QStringLiteral("QPIDEditor"));
        QPIDEditor->resize(533, 520);

        retranslateUi(QPIDEditor);

        QMetaObject::connectSlotsByName(QPIDEditor);
    } // setupUi

    void retranslateUi(QDialog *QPIDEditor)
    {
        QPIDEditor->setWindowTitle(QApplication::translate("QPIDEditor", "Display Editor", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QPIDEditor: public Ui_QPIDEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QPIDEDITOR_H
