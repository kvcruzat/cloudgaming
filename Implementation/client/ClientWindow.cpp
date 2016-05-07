// Khen Cruzat - sc13kvc - 200760716

#include <QKeyEvent>
#include <QtNetwork>
#include <QDebug>
#include <iostream>

#include "ClientWindow.h"

using std::string;

/**
 * Class implementation of Client
 */
ClientWindow::ClientWindow()
{	
    this->setFocusPolicy(Qt::StrongFocus);

 	pressedKey = "";

    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readData()));

    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        networkSession = new QNetworkSession(config, this);
        connect(networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));
// 
        networkSession->open();
    }

}

void ClientWindow::keyPressEvent(QKeyEvent* event)
{
    //Pick the key that has been pressed and assign the relevant variables.
    if (!event->isAutoRepeat()){
        switch ( event->key()) {
            case Qt::Key_Up:
                pressedKey = "Up";
                break;
            case Qt::Key_Down:
                pressedKey = "Down";
                break;
            case Qt::Key_Right:
                pressedKey = "Right";
                break;
            case Qt::Key_Left:
                pressedKey = "Left";
                break;
            case Qt::Key_Q:
                pressedKey = "Q";
                break;
            case Qt::Key_E:
                pressedKey = "E";
                break;
            case Qt::Key_W:
                pressedKey = "W";
                break;
            case Qt::Key_S:
                pressedKey = "S";
                break;
            case Qt::Key_Space:
                pressedKey = "Space";
            default:
                event->ignore();
                break;
        }

        sendData();
    }
    pressedKey = "";    
}
void ClientWindow::keyReleaseEvent( QKeyEvent* event )
{
    if (!event->isAutoRepeat()){
        switch ( event->key()) {
            case Qt::Key_Up:
                pressedKey = "-Up";
                break;
            case Qt::Key_Down:
                pressedKey = "-Down";
                break;
            case Qt::Key_Right:
                pressedKey = "-Right";
                break;
            case Qt::Key_Left:
                pressedKey = "-Left";
                break;
            case Qt::Key_Q:
                pressedKey = "-Q";
                break;
            case Qt::Key_E:
                pressedKey = "-E";
                break;
            case Qt::Key_W:
                pressedKey = "-W";
                break;
            case Qt::Key_S:
                pressedKey = "-S";
                break;
            case Qt::Key_F:
                pressedKey = "-F";
                break;
            case Qt::Key_Space:
                break;
            default:
                event->ignore();
                break;
        }

        sendData();
    }
    pressedKey = "";
}

void ClientWindow::sendData(){

    if (pressedKey != "") {
        // tcpSocket->write(QString::fromStdString(pressedKey).toLatin1().data());
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_0);
        out << (quint16)0;
        out << QString::fromStdString(pressedKey);
        out.device()->seek(0);
        out << (quint16)(block.size() - sizeof(quint16));

        tcpSocket->write(block);
        qDebug() << QString::fromStdString(pressedKey);
    }
   
}

void ClientWindow::connectServer(string hostname, string port){

    blockSize = 0;
    tcpSocket->abort();
    tcpSocket->connectToHost(QString::fromStdString(hostname), 
                atoi(port.c_str()));

}

void ClientWindow::sessionOpened()
{
    // Save the used configuration
    QNetworkConfiguration config = networkSession->configuration();
    QString id;
    if (config.type() == QNetworkConfiguration::UserChoice)
        id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
    else
        id = config.identifier();

    QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
    settings.beginGroup(QLatin1String("QtNetwork"));
    settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
    settings.endGroup();
}

void ClientWindow::readData()
{   
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);

    if (blockSize == 0) {
        if (tcpSocket->bytesAvailable() < (int)sizeof(quint16)){
            return;
        } 
        in >> blockSize;
    }

    if (tcpSocket->bytesAvailable() < blockSize){
        return;
    }

    QString message;
    in >> message;

    qDebug() << "From Server:" << message;
}