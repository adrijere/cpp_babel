#ifndef MAINWINDOW_HPP_
# define MAINWINDOW_HPP_

# include <iostream>

# include <QWidget>
# include <QMainWindow>
# include <QMessageBox>

# include "ui_mainwindow.h"

class MainWindow : public QMainWindow, public Ui_MainWindow {
    Q_OBJECT;

 public:
    explicit MainWindow(QMainWindow *parent) : QMainWindow(parent) {
        // Stylesheets
        this->setupUi(this);
        this->setWindowTitle("BABEL - Username");

        QTabBar *tb;
        tb = this->tabSidebar->findChild<QTabBar *>(QLatin1String("qt_tabwidget_tabbar"));
        tb->setStyleSheet("background-color: rgb(228, 238, 242); color: #12A5F4; border: none; font-weight: bold;");

        // Connect
        QObject::connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(quitWindow()));

        QObject::connect(this->onlineList, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), SLOT(changeNickname(QListWidgetItem *, QListWidgetItem *)));
        
        QObject::connect(this->sidebarList, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), SLOT(notImplemented()));

        QObject::connect(this->researchLine, SIGNAL(returnPressed()), this->researchLine, SLOT(clear()));
        QObject::connect(this->researchLine, SIGNAL(returnPressed()), SLOT(notImplemented()));

        QObject::connect(this->callButton, SIGNAL(clicked()), SLOT(notImplemented()));
        QObject::connect(this->videoButton, SIGNAL(clicked()), SLOT(notImplemented()));
        QObject::connect(this->friendButton, SIGNAL(clicked()), SLOT(notImplemented()));        
        QObject::connect(this->sendButton, SIGNAL(clicked()), SLOT(notImplemented()));        

        QObject::connect(this->sendText, SIGNAL(returnPressed()), this->sendText, SLOT(clear()));
        QObject::connect(this->sendText, SIGNAL(returnPressed()), SLOT(notImplemented()));        
    };

    ~MainWindow(void) {}


 public slots:

    void quitWindow(void) {
        qApp->quit();
    }

    void changeNickname(QListWidgetItem *current, QListWidgetItem *previous) {
        (void)previous;

        if (current != NULL) {
            this->userLabel->setText(current->text());
        }

    }

    void notImplemented(void) {
        QMessageBox::critical(this, QString::fromUtf8("Pas encore implémenté"), QString::fromUtf8("Patience, je développe la feature :)"));
    }
};

#endif /* MAINWINDOW_HPP_ */
