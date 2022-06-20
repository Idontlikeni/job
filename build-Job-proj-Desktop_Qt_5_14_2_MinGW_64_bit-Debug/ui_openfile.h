/********************************************************************************
** Form generated from reading UI file 'openfile.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPENFILE_H
#define UI_OPENFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_OpenFile
{
public:

    void setupUi(QDialog *OpenFile)
    {
        if (OpenFile->objectName().isEmpty())
            OpenFile->setObjectName(QString::fromUtf8("OpenFile"));
        OpenFile->resize(400, 300);

        retranslateUi(OpenFile);

        QMetaObject::connectSlotsByName(OpenFile);
    } // setupUi

    void retranslateUi(QDialog *OpenFile)
    {
        OpenFile->setWindowTitle(QCoreApplication::translate("OpenFile", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OpenFile: public Ui_OpenFile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPENFILE_H
