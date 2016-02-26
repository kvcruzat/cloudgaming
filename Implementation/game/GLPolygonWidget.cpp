// Khen Cruzat - sc13kvc - 200760716

#include "GLPolygonWidget.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <QtDebug>

double PI = M_PI;

/**
 * Implementation for OpenGL widget
 */
GLPolygonWidget::GLPolygonWidget(QWidget *parent) : QGLWidget(parent){
	xChange = 0;
	yChange = 0;		// intializes translation values to 0
	zChange = 0;
	xAngle = 0;
	yAngle = 0;			// intializes rotation values to 0
	zAngle = 0;
	scaleChange = 1;	// initializes scale value to 1
	setSeasons(1);		// 1 branch by default
	leavesEnabled = false;
}

void GLPolygonWidget::initializeGL(){

	static const GLfloat whiteColour[4] = {1.0, 1.0, 1.0, 1.0};
	static const GLfloat greyColour[4] = {0.2, 0.2, 0.2, 0.0};
	float light_position[] = {5.0, 5.0, 0.0, 1.0};
	glClearColor(0.3, 0.3, 0.3, 0.0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    //Set and enable lights
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteColour);
	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteColour);
	glLightfv(GL_LIGHT0, GL_AMBIENT, greyColour);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
}

// Changes viewport upon resize of window
void GLPolygonWidget::resizeGL(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

	glOrtho(-2.0 * (GLfloat) w / (GLfloat) h,
	    2.0 * (GLfloat) w / (GLfloat) h, -2.0, 2.0, -10.0, 10.0);

	glMatrixMode(GL_MODELVIEW);
}

// Draw method
void GLPolygonWidget::paintGL(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	tempSeedVector = seedVector;	// makes a copy of seeds
	glLoadIdentity();
	glTranslatef(xChange,yChange,zChange);		// Applies transformation to tree model
	glRotatef(zAngle, 0.0, 0.0, 1.0);
	glRotatef(xAngle, 1.0, 0.0, 0.0);
	glRotatef(yAngle, 0.0, 1.0, 0.0);
	glScalef(scaleChange, scaleChange, scaleChange);
	treeGen( numSeasons);	// draw tree
	glFlush();
}

// creates a leaf
void GLPolygonWidget::leafGen(){

	GLfloat vertex1[3] = {0.0,-0.1,0.0};	// vertices for triangle leaf
	GLfloat vertex2[3] = {-0.07,-0.04,0.01};
	GLfloat vertex3[3] = {0.07,-0.04,0.0};

	GLfloat u[3];
	GLfloat v[3];
	for (int i = 0; i < 3; ++i) {
		u[i] = vertex2[i] - vertex1[i];
		v[i] = vertex3[i] - vertex1[i];
	}

	GLfloat faceNormal[3];
	faceNormal[0] = (u[1]*v[2]) - (u[2]*v[1]);	// calculate face normal since only using 1 triangle for each leaf
	faceNormal[1] = (u[2]*v[0]) - (u[0]*v[2]);
	faceNormal[2] = (u[0]*v[1]) - (u[1]*v[0]);


	glBegin(GL_TRIANGLES);
		glNormal3f(faceNormal[0],faceNormal[1],faceNormal[2]);	// draw triangle leaf
		glVertex3f(vertex1[0], vertex1[1], vertex1[2]);
		glVertex3f(vertex2[0], vertex2[1], vertex2[2]);
		glVertex3f(vertex3[0], vertex3[1], vertex3[2]);
	glEnd();
}

// recursive branch growing
void GLPolygonWidget::growBranch( int nSeasons, double diam, double length){
	if (nSeasons > 0)	// only grow if not in last recursion
  {

   glPushMatrix();
  
		glColor3f(0.6,0.3,0.0);
		gluCylinder( baseQuad, diam,diam/1.5 , length, 40, 40 );	// draws branch and translate to end of branch
		glTranslatef( 0.0, 0.0, length );
	
	
	if(nSeasons == 1 && leavesEnabled){	// check  for last branch and if leaves should be drawn option is on

		glColor3f(0.0,0.5,0.0);
		glRotatef( 45, 0.0, 1.0, 0.0 );	// rotate to draw first leaf
		leafGen();
		
		glRotatef( 45, 1.0, 0.0, 0.0 );	// rotate again to draw second leaf
		leafGen();

		glTranslatef( 0.0, 0.0, length );	// moves leaf to end of branch

	 }
	
	length = length/1.2;	// make length and diameter of branches smaller every recursion
    diam = diam/1.5;

    srand(tempSeedVector[tempSeedVector.size()-1]);	// load a seed to use and remove this from temporary seed vector
    tempSeedVector.pop_back();

	float num = rand() % 70;	// random number generator for angle of branch
	num = num * -1;

     glPushMatrix();
        glRotatef( num, 0.3, 0.0,  0.5 );	// rotate and draw first branch
        growBranch(nSeasons - 1, diam, length);
     glPopMatrix();
	
	srand(tempSeedVector[tempSeedVector.size()-1]); // use up another seed
    tempSeedVector.pop_back();
	num = rand() % 70;
	num = num * -1;

     glPushMatrix();
        glRotatef( num, -0.7, 0.0, 1.0 );	// rotate again and draw second branch
        growBranch(nSeasons - 1, diam, length);
     glPopMatrix();
  glPopMatrix();
   }

}

// Create tree using number of seasons
void GLPolygonWidget::treeGen( int nSeasons) {
	
	baseQuad = gluNewQuadric();

	glPushMatrix();
		glRotatef( 90.0, 1.0, 0.0, 0.0 );	// Transform tree to correct orientation and position
		glScalef( 1.0, 1.0, -1.0 );
		glTranslatef( 0.0, 0.0, -1.8 );
		growBranch(nSeasons, 0.08, 0.8);	// Start growing tree
	glPopMatrix();
  return;
}

// generate seeds for random number generators
std::vector<float> GLPolygonWidget::genRand(int height) {
	std::vector<float> seeds;
	for (int i = 0 ; i < pow(2.0,height - 1); ++i){	// create as many seeds as there are branches
		seeds.push_back(rand());
	}
	return seeds;
}

// Change seasons using spinnerbox UI
void GLPolygonWidget::setSeasons(int depth){
	numSeasons = depth;
	seedVector = genRand(numSeasons);	// create seeds using number of seasons
	updateGL();
}

// changes the value to change x by with slider value
void GLPolygonWidget::translateX(int x){
	xChange = x*0.01;
	updateGL();
}

// slot for y translation
void GLPolygonWidget::translateY(int y){
	yChange = y*0.01;
	updateGL();
}

// slot for z translation
void GLPolygonWidget::translateZ(int z){
	zChange = z*0.01;
	updateGL();
}

// slot for x rotation
void GLPolygonWidget::rotateX(int x){
	xAngle = x;
	updateGL();
}

// slot for y rotation
void GLPolygonWidget::rotateY(int y){
	yAngle = y;
	updateGL();
}

// slot for z rotation
void GLPolygonWidget::rotateZ(int z){
	zAngle = z;
	updateGL();
}

// slot to turn on and off lighting
void GLPolygonWidget::setLight(bool checked){
	if (checked) glEnable(GL_LIGHT0);
	else glDisable(GL_LIGHT0);
	updateGL();
}

// slot for scale transformation
void GLPolygonWidget::setScale(int s){
	scaleChange = 1+(s*0.01);
	updateGL();
}

// slot to turn on and off shading
void GLPolygonWidget::setShading(bool checked){
	if (checked) glShadeModel(GL_SMOOTH);
	else glShadeModel(GL_FLAT);
	updateGL();
}

// slot to turn on and off leaves
void GLPolygonWidget::setLeaves(bool checked){
	if (checked) leavesEnabled = true;
	else leavesEnabled = false;
	updateGL();
}

