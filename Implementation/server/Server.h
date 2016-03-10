
#ifndef SERVER_H
#define SERVER_H

#include <QWidget>

class QTcpServer;
class QNetworkSession;

class Server : public QWidget {

	Q_OBJECT

	public:
	    Server(QWidget *parent = 0);

	private slots:
	    void sessionOpened();
	    void sendData();

	private:
	    QTcpServer *tcpServer;
	    QNetworkSession *networkSession;

};

#endif