CONFIG			+=	qt
QT				+=	core gui

greaterThan(QT_MAJOR_VERSION, 4):
QT				+=	widgets

TARGET			=	babel
TEMPLATE		=	app

QMAKE_CXXFLAGS	+=	-Wno-unused-result -I headers/

SOURCES			+=	sources/main.cpp

HEADERS			+= 	headers/MainWindow.hpp

FORMS			+=	mainwindow.ui

RESOURCES		+=	resources.qrc
