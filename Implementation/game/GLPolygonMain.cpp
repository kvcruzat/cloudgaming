// Khen Cruzat - sc13kvc - 200760716

#include <QApplication>
#include "GLWindow.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	GLWindow *window = new GLWindow();

	window -> show();

	return app.exec();

}
