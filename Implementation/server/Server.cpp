// Khen Cruzat - sc13kvc - 200760716

#include <QtWidgets>
#include <QtNetwork>
#include <QHBoxLayout>
#include <QDebug>
#include <iostream>

#include "Server.h"

Server::Server(QWidget *parent) :QWidget(parent), tcpServer(0), networkSession(0)
{

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

        networkSession->open();
    } else {
        sessionOpened();
    }

    QHBoxLayout* mainLayout = new QHBoxLayout;
	setLayout(mainLayout);

	connect(tcpServer, SIGNAL(newConnection()), this, SLOT( sendData()) );

}

void Server::sendData()
{
	std::cout << "1" << std::endl;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    out << QString::fromStdString("Connected to Server");
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    clientConnection = tcpServer->nextPendingConnection();
    connect(clientConnection, SIGNAL(disconnected()),
            clientConnection, SLOT(deleteLater()));

    clientConnection->write(block);
    std::cout<< "2" << std::endl;
    blockSize = 0;
    connect(clientConnection, SIGNAL(readyRead()), this, SLOT(readData()));
}

void Server::sessionOpened()
{
    // Save the used configuration
    if (networkSession) {
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

    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen()) {
        QMessageBox::critical(this, tr("Fortune Server"),
                              tr("Unable to start the server: %1.")
                              .arg(tcpServer->errorString()));
        close();
        return;
    }
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    qDebug() << ipAddress << tcpServer->serverPort();

}

void Server::readData()
{	
	// QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
    QDataStream in(clientConnection);
    in.setVersion(QDataStream::Qt_4_0);

    if (blockSize == 0) {
        if (clientConnection->bytesAvailable() < (int)sizeof(quint16)){
            return;
        }  
        in >> blockSize;
    }

    if (clientConnection->bytesAvailable() < blockSize){
        return;
    }

    QString message;
    in >> message;

    qDebug() << message;
    blockSize = 0;
}  