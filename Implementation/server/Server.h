
#ifndef SERVER_H
#define SERVER_H

#include <QWidget>

class QTcpServer;
class QTcpSocket;
class QNetworkSession;

class Server : public QWidget {

	Q_OBJECT

	public:
	    Server(QWidget *parent = 0);

	private slots:
	    void sessionOpened();
	    void sendData();
	    void readData();

	private:
	    QTcpServer *tcpServer;
	    QTcpSocket *clientConnection;
	    quint16 blockSize;
	    QNetworkSession *networkSession;

};

#endif