// Khen Cruzat - sc13kvc - 200760716

#include <QApplication>

#include "ClientWindow.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	ClientWindow *window = new ClientWindow();

	if (argc > 1) {
		window -> connectServer(argv[1], argv[2]);
	}

	window -> show();

	return app.exec();

}
