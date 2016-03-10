// Khen Cruzat - sc13kvc - 200760716

#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QWidget>
#include <QTcpSocket>

class QTcpSocket;
class QNetworkSession;

/**
 * Class definition for Qt window config
 */
class ClientWindow : public QWidget {

	Q_OBJECT

	public:
		ClientWindow();
		void connectServer(std::string hostname, std::string port);

	public slots:
		void sessionOpened();
		void readData();

	private:
		std::string pressedKey;
		void keyPressEvent(QKeyEvent*);
		

		QTcpSocket *tcpSocket;
		quint16 blockSize;
		QNetworkSession *networkSession;
};

#endif