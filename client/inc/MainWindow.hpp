#ifndef MAINWINDOW_HPP_
# define MAINWINDOW_HPP_

# include <iostream>
# include <map>
# include <list>
# include <algorithm>

# include <QWidget>
# include <QMainWindow>
# include <QTimer>
# include <QTime>
# include <QList>
# include <QMessageBox>
# include <QPixmap>

# include "ClientCore.hpp"
# include "ui_mainwindow.h"

class MainWindow : public QMainWindow, public Ui_MainWindow {
    Q_OBJECT;

    ClientCore *_client;
    QTime *_callingTime;

 public:
    explicit MainWindow(QMainWindow *parent, ClientCore *client) : QMainWindow(parent), _client(client) {
        // Timers
        QTimer *pingServer = new QTimer(this);
        QTimer *refreshAll = new QTimer(this);
        this->_callingTime = new QTime();

        pingServer->start(3000);
        refreshAll->start(500);
        this->_callingTime->start();

        // Stylesheets
        this->setupUi(this);
        this->setWindowTitle(this->_client->getName().c_str());
        this->mainLabel->setText(this->_client->getName().c_str());
        this->ping();
        this->refresh();
        this->changeView();

        QTabBar *tb;
        tb = this->tabSidebar->findChild<QTabBar *>(QLatin1String("qt_tabwidget_tabbar"));
        tb->setStyleSheet("background-color: rgb(228, 238, 242); color: #12A5F4; border: none; font-weight: bold;");

        // Connect
        QObject::connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(quitWindow()));
        QObject::connect(pingServer, SIGNAL(timeout()), SLOT(ping()));
        QObject::connect(refreshAll, SIGNAL(timeout()), SLOT(refresh()));
        
        QObject::connect(this->sidebarList, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), SLOT(notImplemented()));

        QObject::connect(this->researchLine, SIGNAL(returnPressed()), this->researchLine, SLOT(clear()));
        QObject::connect(this->researchLine, SIGNAL(returnPressed()), SLOT(notImplemented()));

        QObject::connect(this->onlineList, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), SLOT(changeView(QListWidgetItem *, QListWidgetItem *)));
        QObject::connect(this->friendList, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), SLOT(changeView(QListWidgetItem *, QListWidgetItem *)));

        QObject::connect(this->callButton, SIGNAL(clicked()), SLOT(callUser()));
        QObject::connect(this->hangOutButton, SIGNAL(clicked()), SLOT(hangOut()));
        QObject::connect(this->videoButton, SIGNAL(clicked()), SLOT(notImplemented()));
        QObject::connect(this->addFriendButton, SIGNAL(clicked()), SLOT(addFriend()));        
        QObject::connect(this->removeFriendButton, SIGNAL(clicked()), SLOT(removeFriend()));        

        QObject::connect(this->sendButton, SIGNAL(clicked()), SLOT(sendMessage()));        
        QObject::connect(this->sendText, SIGNAL(returnPressed()), SLOT(sendMessage()));
    };

    ~MainWindow(void) {}

    void toggleFriend(bool flag) {
        this->addFriendButton->setEnabled(flag);
        this->addFriendButton->setVisible(flag);

        this->removeFriendButton->setEnabled(!flag);
        this->removeFriendButton->setVisible(!flag);
    }

    void toggleCall(bool flag) {
        this->callButton->setEnabled(flag);
        this->callButton->setVisible(flag);

        this->hangOutButton->setEnabled(!flag);
        this->hangOutButton->setVisible(!flag);

        this->callTimer->setVisible(!flag);
    }

    void refreshOnline(void) {
        MainMutex::mutex().lock();
        std::map<unsigned short, std::string> map = this->_client->getContactList();
        MainMutex::mutex().unlock();

        this->onlineList->clear();
        for (std::map<unsigned short, std::string>::iterator it = map.begin(); it != map.end(); it++) {
            QString itemName(it->second.c_str());
            QListWidgetItem *item = new QListWidgetItem(itemName);

            this->onlineList->addItem(item);
        }
    }

    void refreshHistory(QString username) {
        MainMutex::mutex().lock();
        unsigned short id = this->getKeyOfMap(this->_client->getContactList(), username.toStdString());
        std::map<unsigned short, std::vector<std::pair<messageType, std::string> > > history = this->_client->getMessagesList();
        MainMutex::mutex().unlock();

        this->historyList->clear();
        if (history[id].empty()) {
            QString content(QString::fromUtf8("Vous n'avez encore rien envoyé à votre correspondant ! N'hésitez pas à lui envoyer un petit message pour lui dire bonjour ! :)"));
            QListWidgetItem *item = new QListWidgetItem(content);

            item->setTextAlignment(Qt::AlignCenter);
            this->historyList->addItem(item);
        } else {
            for (std::vector<std::pair<messageType, std::string> >::iterator it = history[id].begin(); it != history[id].end(); it++) {
                QString itemName(it->second.c_str());
                QListWidgetItem *item = new QListWidgetItem(itemName);
                if (it->first == FROM_ME)
                    item->setTextAlignment(Qt::AlignRight);
                else if (it->first == FROM_OTHER)
                    item->setTextAlignment(Qt::AlignLeft);
                else
                    item->setTextAlignment(Qt::AlignCenter);
                this->historyList->addItem(item);
            }
        }
    }

    void refreshStatus(QString username) {
        std::string name = username.toStdString();

        MainMutex::mutex().lock();
        unsigned short id = this->getKeyOfMap(this->_client->getContactList(), name);
        MainMutex::mutex().unlock();

        if (id != 0) {
            QPixmap pix(":/images/online.png");

            this->statusPix->setPixmap(pix);
            this->statusUser->setText("en ligne");
            this->callButton->setEnabled(true);
            this->videoButton->setEnabled(true);
            this->sendText->setEnabled(true);
            this->sendButton->setEnabled(true);
        } else {
            QPixmap pix(":/images/offline.png");

            this->statusPix->setPixmap(pix);
            this->statusUser->setText("hors ligne");
            this->callButton->setEnabled(false);
            this->videoButton->setEnabled(false);
            this->sendText->setEnabled(false);
            this->sendButton->setEnabled(false);
        }        
    }

    void refreshCalling(QString username) {
        std::string name = username.toStdString();

        MainMutex::mutex().lock();
        unsigned short id = this->getKeyOfMap(this->_client->getContactList(), name);
        MainMutex::mutex().unlock();

        MainMutex::mutex().lock();
        unsigned short callingId = this->_client->getCallingFriend().first;
        MainMutex::mutex().unlock();

        if (id != callingId) {
            this->toggleCall(true);
        } else {
            this->toggleCall(false);
        }
    }

    unsigned short getKeyOfMap(const std::map<unsigned short, std::string> &map, const std::string &username) {
        for (std::map<unsigned short, std::string>::const_iterator it = map.begin(); it != map.end(); ++it ) {
            if (it->second == username) {
                return it->first;
            }
        }

        return 0;
    }

 public slots:

    void quitWindow(void) {
        qApp->quit();
    }

    void ping(void) {
        this->_client->sendComListRequest();
    }

    void refresh(void) {
        std::string username = this->userLabel->text().toStdString();

        // Contacts update
        MainMutex::mutex().lock();
        if (this->_client->getContactsUpdate()) {
            this->_client->setContactsUpdate(false);
            MainMutex::mutex().unlock();

            this->refreshOnline();
        } else {
            MainMutex::mutex().unlock();
        }

        // Messages update
        MainMutex::mutex().lock();
        if (this->_client->getMessagesUpdate()) {
            this->_client->setMessagesUpdate(false);
            MainMutex::mutex().unlock();

            this->changeView();
        } else {
            MainMutex::mutex().unlock();
        }

        // Incomming call update
        MainMutex::mutex().lock();
        if (this->_client->getCallingUpdate()) {
            this->_client->setCallingUpdate(false);
            unsigned short id = this->_client->getCallingList().back().first;
            MainMutex::mutex().unlock();

            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Quelqu'un vous appelle", "Répondre ?", QMessageBox::No|QMessageBox::Yes);

            if (reply == QMessageBox::Yes) {
                this->_client->sendComCallResponse(id, "Y");
                this->stopCurrentCall();
                this->_client->setHangUpId(id);
                this->_client->setHangUpAddr(this->_client->getCallingList().back().second);
                this->_client->setCurrentCallUpdate(true);
            } else {
                this->_client->sendComCallResponse(id, "N");
            }
        } else {
            MainMutex::mutex().unlock();
        }

        // Call cancelling update
        MainMutex::mutex().lock();
        if (this->_client->getCancellingUpdate()) {
            this->_client->setCancellingUpdate(false);
            unsigned short id = this->_client->getCancellingList().back();
            MainMutex::mutex().unlock();
 
            if (this->_client->getCallingFriend().first == id) {
                this->_client->setHangOutId(id);
                this->_client->setCurrentCallUpdate(true);
            }
        } else {
            MainMutex::mutex().unlock();
        }

        // Current call update
        MainMutex::mutex().lock();
        if (this->_client->getCurrentCallUpdate()) {
            MainMutex::mutex().unlock();
            this->_client->setCurrentCallUpdate(false);

            if (this->_client->getHangOutId() != -1)
                this->handleHangOut();
            if (this->_client->getHangUpId() != -1)
                this->handleHangUp();
        } else {
            MainMutex::mutex().unlock();
        }

        // Current call display (useless, will be deleted)
        if (this->_client->getCallingFriend().first != -1) {
            std::cout << "Appel en cours vers Client " << this->_client->getCallingFriend().first << " (" << this->_client->getCallingFriend().second << ")." << std::endl;
        }

        this->callTimer->display(this->_callingTime->elapsed());
    }

    void stopCurrentCall()
    {
        if (this->_client->getCallingFriend().first != -1)
        {
            this->_client->sendComCallCancel(this->_client->getCallingFriend().first);
            this->_client->setHangOutId(this->_client->getCallingFriend().first);
            this->_client->setCurrentCallUpdate(true);
        }
    }

    void handleHangUp()
    {
        this->_callingTime->restart();
        this->_client->setCallingFriend(this->_client->getHangUpId(), this->_client->getHangUpAddr());
        this->_client->setHangUpId(-1);
        this->changeView();
    }

    void handleHangOut()
    {
        this->_client->setCallingFriend(-1, "");
        this->_client->setHangOutId(-1);
        this->changeView();
    }

    void changeView(QListWidgetItem *current = NULL, QListWidgetItem *previous = NULL) {
        (void)previous;

        if (current != NULL and current->text() != "Aucun ami") {
            this->userLabel->setText(current->text());
        }

        QString username = this->userLabel->text();
        QList<QListWidgetItem *> items = this->friendList->findItems(username, Qt::MatchExactly);

        if (items.count() > 0) {
            this->toggleFriend(false);
        } else {
            this->toggleFriend(true);
        }

        this->refreshHistory(username);
        this->refreshCalling(username);
        this->refreshStatus(username);
    }

    void callUser(void) {
        std::string username = this->userLabel->text().toStdString();

        MainMutex::mutex().lock();        
        unsigned short id = this->getKeyOfMap(this->_client->getContactList(), username);
        MainMutex::mutex().unlock();

        if (id != 0) {
            this->stopCurrentCall();
            this->_client->sendComCallRequest(id);
        }
    }

    void hangOut(void) {
        std::string username = this->userLabel->text().toStdString();

        MainMutex::mutex().lock();
        unsigned short id = this->getKeyOfMap(this->_client->getContactList(), username);
        MainMutex::mutex().unlock();

        if (id != 0) {
            this->_client->sendComCallCancel(id);
            this->_client->setHangOutId(id);
            this->_client->setCurrentCallUpdate(true);
        }
    }

    void sendMessage(void) {
        std::string username = this->userLabel->text().toStdString();
        std::string content = this->sendText->text().toStdString();

        MainMutex::mutex().lock();
        unsigned short id = this->getKeyOfMap(this->_client->getContactList(), username);
        this->_client->getMessagesList()[id].push_back(std::pair<messageType, std::string>(FROM_ME, content));
        this->_client->setMessagesUpdate(true);
        MainMutex::mutex().unlock();

        if (id != 0) {
            this->_client->sendComMessageSend(id, content);
        }

        this->sendText->clear();
        this->changeView();
    }

    void addFriend(void) {
        QString username = this->userLabel->text();
        QList<QListWidgetItem *> items = this->friendList->findItems(username, Qt::MatchExactly);

        if (items.count() == 0) {        
            if (this->friendList->item(0) and this->friendList->item(0)->text() == "Aucun ami") {
                this->friendList->clear();
            }

            QString username = this->userLabel->text();

            QListWidgetItem *item = new QListWidgetItem(username);
            this->friendList->addItem(item);
        }

        this->changeView();
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

        this->changeView();
    }

    void notImplemented(void) {
        QMessageBox::critical(this, QString::fromUtf8("Pas encore implémenté"), QString::fromUtf8("Patience, je développe la feature :)"));
    }
};

#endif /* MAINWINDOW_HPP_ */
