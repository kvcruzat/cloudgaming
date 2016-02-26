// Khen Cruzat - sc13kvc - 200760716
#include <QGLWidget>
#include <QWidget>
#include <vector>
#include "GL/glu.h"

#ifndef __GL_POLYGON_WIDGET_H__
#define __GL_POLYGON_WIDGET_H__ 1

/**
 * Class definition for OpenGL widget
 */
class GLPolygonWidget: public QGLWidget {

	Q_OBJECT

	public:
		GLPolygonWidget(QWidget *parent=0);

	protected:
		void initializeGL();
		void resizeGL(int w, int h);
		void paintGL();

	public slots:
		void translateX(int x);
		void translateY(int y);
		void translateZ(int z);		// custom slots
		void rotateX(int x);
		void rotateY(int y);
		void rotateZ(int z);
		void setScale(int s);
		void setLight(bool);
		void setShading(bool);
		void setLeaves(bool);
		void setSeasons(int nSeasons);

	private:
		float xChange, yChange, zChange, xAngle, yAngle, zAngle, scaleChange;
		GLUquadricObj *baseQuad;
		int numSeasons;
		bool leavesEnabled;
		std::vector<float> seedVector;
		std::vector<float> tempSeedVector;
		void leafGen();
		void treeGen(int);
		void growBranch(int,double,double);
		std::vector<float> genRand(int);


};

#endif