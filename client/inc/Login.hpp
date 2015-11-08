#ifndef LOGIN_HPP_
# define LOGIN_HPP_

# include <iostream>

# include <QWidget>
# include <QMessageBox>

# include "ClientCore.hpp"
# include "MainWindow.hpp"
# include "ui_login.h"

class Login : public QWidget, public Ui_Login {
    Q_OBJECT;

 public:

    explicit Login(QWidget *parent) : QWidget(parent) {
        // Stylesheets
        this->setupUi(this);
        this->setWindowTitle("BABEL - Connexion");

        // Connect
        QObject::connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(quitWindow()));

        QObject::connect(this->usernameEdit, SIGNAL(returnPressed()), SLOT(signIn()));
        QObject::connect(this->passwordEdit, SIGNAL(returnPressed()), SLOT(signIn()));

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

        if (this->usernameEdit->text().isEmpty()) {
            QMessageBox::warning(this, QString::fromUtf8("Erreur à la connexion"), QString::fromUtf8("Vous devez entrer un username"));
        } else if (this->passwordEdit->text().isEmpty()) {
            QMessageBox::warning(this, QString::fromUtf8("Erreur à la connexion"), QString::fromUtf8("Vous devez entrer l'adresse ip du serveur"));
        } else {
            ClientCore *client = new ClientCore(this->usernameEdit->text().toStdString(), this->passwordEdit->text().toStdString());
            client->sendComCoRequest();

            MainWindow *window = new MainWindow(NULL, client);

            this->hide();
            window->show();
        }
    }
};

#endif /* LOGIN_HPP_ */
