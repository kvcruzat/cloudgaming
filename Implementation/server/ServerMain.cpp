#include <QApplication>
#include "Server.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

	Server *server = new Server();

	server -> show();

	return app.exec();

}