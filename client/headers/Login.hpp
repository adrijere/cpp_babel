#ifndef LOGIN_HPP_
# define LOGIN_HPP_

# include <iostream>

# include <QWidget>
# include <QMessageBox>

# include "MainWindow.hpp"
# include "ui_login.h"

class Login : public QWidget, public Ui_Login {
    Q_OBJECT;

 public:

    explicit Login(QWidget *parent) : QWidget(parent) {
        // Stylesheets
        this->setupUi(this);
        this->setWindowTitle("Bienvenu sur Babel");

        // Connect
        QObject::connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(quitWindow()));

        QObject::connect(this->usernameEdit, SIGNAL(returnPressed()), SLOT(notImplemented()));
        QObject::connect(this->passwordEdit, SIGNAL(returnPressed()), SLOT(notImplemented()));

        QObject::connect(this->connexionButton, SIGNAL(clicked()), SLOT(signIn()));
    }

    ~Login(void) {}

 public slots:

    void quitWindow(void) {
        qApp->quit();
    }

    void notImplemented(void) {
        QMessageBox::critical(this, QString::fromUtf8("Pas encore implémenté"), QString::fromUtf8("Patience, je développe la feature :)"));
    }

    void signIn(void) {
        MainWindow *window = new MainWindow(NULL);

        this->hide();
        window->show();
    }
};

#endif /* LOGIN_HPP_ */
