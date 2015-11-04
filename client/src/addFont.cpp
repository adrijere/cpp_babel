/* 
* @Author: gicque_p
* @Date:   2015-11-03 13:02:01
* @Last Modified by:   gicque_p
* @Last Modified time: 2015-11-03 13:04:45
*/

#include <iostream>

#include <QWidget>
#include <QLocale>
#include <QLibraryInfo>
#include <QFile>
#include <QFontDatabase>
#include <QMessageBox>

void addFont(void) {
    QStringList list;
    list << "Roboto-Thin.ttf" << "Roboto-Regular.ttf" << "Roboto-Medium.ttf" << "Roboto-Light.ttf" << "Roboto-Bold.ttf";
    int fontID(-1);
    bool fontWarningShown(false);
    for (QStringList::const_iterator constIterator = list.constBegin(); constIterator != list.constEnd(); ++constIterator) {
        QFile res(":/fonts/" + *constIterator);
        if (res.open(QIODevice::ReadOnly) == false) {
            if (fontWarningShown == false) {
                QMessageBox::warning(0, "Application", (QString)"Impossible d'ouvrir la police " + QChar(0x00AB) + " Roboto " + QChar(0x00BB) + ".");
                fontWarningShown = true;
            }
        } else {
            fontID = QFontDatabase::addApplicationFontFromData(res.readAll());
            if (fontID == -1 && fontWarningShown == false) {
                QMessageBox::warning(0, "Application", (QString)"Impossible d'ouvrir la police " + QChar(0x00AB) + " Roboto " + QChar(0x00BB) + ".");
                fontWarningShown = true;
            }
        }
    }
}
