/* 
* @Author: gicque_p
* @Date:   2015-04-14 10:59:05
* @Last Modified by:   gicque_p
* @Last Modified time: 2015-10-20 10:22:14
*/

#include <iostream>

#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>

#include "MainWindow.hpp"

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;

    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&translator);

    MainWindow window(NULL);
    window.show();

    return app.exec();
}
