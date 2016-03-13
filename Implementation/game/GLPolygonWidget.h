// Khen Cruzat - sc13kvc - 200760716
#include <QGLWidget>
#include <QWidget>
#include <vector>
#include "GL/glu.h"
#include <GL/glut.h>
#include "Vector.h"
#include "Point.h"
#include <QWheelEvent>

#ifndef __GL_POLYGON_WIDGET_H__
#define __GL_POLYGON_WIDGET_H__ 1

/**
 * Class definition for OpenGL widget
 */
class GLPolygonWidget: public QGLWidget {

	Q_OBJECT

	public:
		GLPolygonWidget(QWidget *parent=0);
		void simulateKey(std::string key);

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
		void moveTree();
		void setLight(bool);
		void setShading(bool);
		void setLeaves(bool);
		void setSeasons(int nSeasons);

		void move();

	private:
		void wheelEvent ( QWheelEvent * event );
		float xChange, yChange, zChange, xAngle, yAngle, zAngle, scaleChange;
		GLUquadricObj *baseQuad;
		GLUquadricObj *baseQuad2;
		GLuint texture_id;
		int numSeasons;
		bool leavesEnabled, lightEnabled;
		std::vector<float> seedVector;
		std::vector<float> tempSeedVector;
		std::vector<float> seedCoordVector;
		void leafGen(bool);
		void treeGen(int);
		void growBranch(int,double,double,bool);
		std::vector<float> genRand(int);
		int currentTime, previousTime;
		int frameCount, qImageCount;

		Point eye; Point center; Vector upVec; // For Look at
		Vector right; Vector up; Vector forward; // For the movement
		int goRight; int goUp; int goForward; int doRoll;
		Point currentPosition; // Store where currently I am
		float speed; // Speed of movement

		void roll(double);
		void pitch(double);
		void yaw(double);

		void keyPressEvent(QKeyEvent*);
		void keyReleaseEvent(QKeyEvent*);
		void pickMovement();
		void updateCurrent();

};

#endif