#ifndef MAINWINDOW_HPP_
# define MAINWINDOW_HPP_

# include <iostream>

# include <QWidget>
# include <QMainWindow>
# include <QTimer>
# include <QList>
# include <QMessageBox>

# include "ui_mainwindow.h"

class MainWindow : public QMainWindow, public Ui_MainWindow {
    Q_OBJECT;

 public:
    explicit MainWindow(QMainWindow *parent, QString username) : QMainWindow(parent) {
        // Stylesheets
        this->setupUi(this);
        this->setWindowTitle(username);
        this->mainLabel->setText(username);
        this->removeFriendButton->setVisible(false);

        QTabBar *tb;
        tb = this->tabSidebar->findChild<QTabBar *>(QLatin1String("qt_tabwidget_tabbar"));
        tb->setStyleSheet("background-color: rgb(228, 238, 242); color: #12A5F4; border: none; font-weight: bold;");

        // Connect
        QTimer *timer = new QTimer(this);
        timer->start(500);

        QObject::connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(quitWindow()));
        QObject::connect(timer, SIGNAL(timeout()), SLOT(ping()));

        QObject::connect(this->onlineList, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), SLOT(changeView(QListWidgetItem *, QListWidgetItem *)));
        QObject::connect(this->friendList, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), SLOT(changeView(QListWidgetItem *, QListWidgetItem *)));
        
        QObject::connect(this->sidebarList, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), SLOT(notImplemented()));

        QObject::connect(this->researchLine, SIGNAL(returnPressed()), this->researchLine, SLOT(clear()));
        QObject::connect(this->researchLine, SIGNAL(returnPressed()), SLOT(notImplemented()));

        QObject::connect(this->callButton, SIGNAL(clicked()), SLOT(notImplemented()));
        QObject::connect(this->videoButton, SIGNAL(clicked()), SLOT(notImplemented()));
        QObject::connect(this->addFriendButton, SIGNAL(clicked()), SLOT(addFriend()));        
        QObject::connect(this->removeFriendButton, SIGNAL(clicked()), SLOT(removeFriend()));        
        QObject::connect(this->sendButton, SIGNAL(clicked()), SLOT(notImplemented()));        

        QObject::connect(this->sendText, SIGNAL(returnPressed()), this->sendText, SLOT(clear()));
        QObject::connect(this->sendText, SIGNAL(returnPressed()), SLOT(notImplemented()));        
    };

    ~MainWindow(void) {}

    void toggleAddFriend(void) {
        this->addFriendButton->setEnabled(true);
        this->addFriendButton->setVisible(true);

        this->removeFriendButton->setEnabled(false);
        this->removeFriendButton->setVisible(false);
    }

    void toggleRemoveFriend(void) {
        this->addFriendButton->setEnabled(false);
        this->addFriendButton->setVisible(false);

        this->removeFriendButton->setEnabled(true);
        this->removeFriendButton->setVisible(true);
    }

 public slots:

    void quitWindow(void) {
        qApp->quit();
    }

    void ping(void) {
        // PING SERVER TO GET ONLINE USERS LIST

        // QListWidgetItem *item = new QListWidgetItem("Babel Echo Test");
        // this->onlineList->clear();
        // this->onlineList->addItem(item);

        // for (responseFromServer as reponse) {
        //     QListWidgetItem *item = QListWidgetItem(reponse);
        //     this->onlineList->addItem(item);
        // }
    }

    void addFriend(void) {
        if (this->friendList->item(0) and this->friendList->item(0)->text() == "Aucun ami") {
            this->friendList->clear();
        }

        QString username = this->userLabel->text();

        QListWidgetItem *item = new QListWidgetItem(username);
        this->friendList->addItem(item);

        this->toggleRemoveFriend();
    }

    void removeFriend(void) {
        QString username = this->userLabel->text();
        QList<QListWidgetItem *> items = this->friendList->findItems(username, Qt::MatchExactly);

        for (QList<QListWidgetItem *>::iterator i = items.begin(); i != items.end(); i++) {
            int index = this->friendList->row(*i);

            this->friendList->takeItem(index);
        }

        if (this->friendList->count() == 0) {
            QListWidgetItem *item = new QListWidgetItem("Aucun ami");
            this->friendList->addItem(item);
        }

        this->toggleAddFriend();
    }

    void changeView(QListWidgetItem *current, QListWidgetItem *previous) {
        (void)previous;

        if (current != NULL and current->text() != "Aucun ami") {
            this->userLabel->setText(current->text());
        }

        QString username = this->userLabel->text();
        QList<QListWidgetItem *> items = this->friendList->findItems(username, Qt::MatchExactly);

        if (items.count() > 0) {
            this->toggleRemoveFriend();
        } else {
            this->toggleAddFriend();
        }
    }

    void notImplemented(void) {
        QMessageBox::critical(this, QString::fromUtf8("Pas encore implémenté"), QString::fromUtf8("Patience, je développe la feature :)"));
    }
};

#endif /* MAINWINDOW_HPP_ */
