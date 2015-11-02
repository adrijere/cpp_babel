/* 
* @Author: gicque_p
* @Date:   2015-04-14 10:59:05
* @Last Modified by:   gicque_p
* @Last Modified time: 2015-11-02 15:46:42
*/

#include <iostream>

#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>

#include "Login.hpp"
#include "MainWindow.hpp"

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;

    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&translator);

    Login *window = new Login(NULL);
	window->show();

    return app.exec();
}
