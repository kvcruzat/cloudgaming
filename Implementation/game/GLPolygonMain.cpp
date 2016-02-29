// Khen Cruzat - sc13kvc - 200760716

#include <QApplication>
#include "GLWindow.h"
#include <GL/glut.h>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	glutInit(&argc, argv);

	GLWindow *window = new GLWindow();

	window -> show();

	return app.exec();

}
