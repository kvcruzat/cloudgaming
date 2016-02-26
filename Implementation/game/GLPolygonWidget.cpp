// Khen Cruzat - sc13kvc - 200760716

#include "GLPolygonWidget.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <QtDebug>
#include <time.h>

double PI = M_PI;

GLfloat light_position[4] = {0.0, 0.0, 8.0, 1.0};	// define some vectors
GLfloat ground_plane[4][4] = {{-10.0, 10.0, 0.0},
								{10.0, 10.0, 0.0},
								{10.0, -10.0, 0.0},
								{-10.0, -10.0, 0.0}};

/**
 * Implementation for OpenGL widget
 */
GLPolygonWidget::GLPolygonWidget(QWidget *parent) : QGLWidget(parent){
	xChange = 0;
	yChange = 0;		// intializes translation values
	zChange = 0;
	xAngle = 30;
	yAngle = 30;		// intializes rotation values
	zAngle = 0;
	scaleChange = 1;	// initializes scale value to 1
	setSeasons(1);		// 1 branch by default
	moveTree();			// create the random coordinate for tree
	leavesEnabled = false;	// leaves turned off by default
	lightEnabled = true;	// lights and shadow turned on by default
}

void GLPolygonWidget::initializeGL(){
	static const GLfloat whiteColour[4] = {1.0, 1.0, 1.0, 1.0};
	static const GLfloat greyColour[4] = {0.2, 0.2, 0.2, 0.0};

	baseQuad2 = gluNewQuadric();

	glClearColor(0.53, 0.81, 0.92, 0.0);
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

    QImage grassTex;	// load jpeg image of grass in to QImage
	grassTex.load("grass.jpg");
	QImage gl_grassTex=convertToGLFormat(grassTex);	// converts to a format that OpenGL uses

	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, gl_grassTex.width(), gl_grassTex.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, gl_grassTex.bits());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
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
	// change background "sky" colour depending if shadow is turned on
	if (lightEnabled) {
		glClearColor(0.53, 0.81, 0.92, 0.0);
	}
	else {
		glClearColor(0.1, 0.1, 0.1, 0.0);
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(xChange,yChange,zChange);		// Applies transformation
	glRotatef(zAngle, 0.0, 0.0, 1.0);
	glRotatef(xAngle, 1.0, 0.0, 0.0);
	glRotatef(yAngle, 0.0, 1.0, 0.0);

	glTranslatef( 0.0, -1.2, 0.0);			// move the scene down
	glRotatef( -90.0, 1.0, 0.0, 0.0 );		// rotate to correct orientation
	glScalef(scaleChange, scaleChange, scaleChange);	// perform scaling

	// draw sphere as sun as light source if enabled
	if (lightEnabled) {
		glPushMatrix();
			// position sun to light source position
			glTranslatef(light_position[0],light_position[1],light_position[2]);
			glColor3f(1.0,0.72,0.07);
			gluSphere(baseQuad2, 0.8, 25, 25);
		glPopMatrix();
	}

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

	GLfloat faceNormal[4];
	faceNormal[0] = (u[1]*v[2]) - (u[2]*v[1]);	// calculate face normal since onl1 using 1 triangle for each leaf
	faceNormal[1] = (u[2]*v[0]) - (u[0]*v[2]);
	faceNormal[2] = (u[0]*v[1]) - (u[1]*v[0]);
	faceNormal[3] = 1.0;

	glBegin(GL_TRIANGLES);
		glNormal3f(faceNormal[0],faceNormal[1],faceNormal[2]);	// draw triangle leaf
		glVertex3f(vertex1[0], vertex1[1], vertex1[2]);
		glVertex3f(vertex2[0], vertex2[1], vertex2[2]);
		glVertex3f(vertex3[0], vertex3[1], vertex3[2]);
	glEnd();
}

// recursive branch growing
void GLPolygonWidget::growBranch( int nSeasons, double diam, double length, bool shadow){
	if (nSeasons > 0)	// only grow if not in last recursion
  {

   glPushMatrix();
  		
  		// draw shadow version of tree
  		if (shadow){
		    glDisable(GL_LIGHTING);
		    glEnable(GL_BLEND);
		    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		    glColor4f(0.0, 0.0, 0.0, 0.5);
  		}
  		else{ 
  			glColor3f(0.6,0.3,0.0);	// normal tree colour
  		}
		
		gluCylinder( baseQuad, diam,diam/1.5 , length, 40, 40 );	// draws branch and translate to end of branch
		glTranslatef( 0.0, 0.0, length );

	
	if(nSeasons == 1 && leavesEnabled){	// check  for last branch and if leaves should be drawn option is on

		if (shadow){
			glColor3f(0.0,0.0,0.0);
		}
		else {
			glColor3f(0.0,0.5,0.0);
		}
		
		glRotatef( 45, 0.0, 1.0, 0.0 );	// rotate to draw first leaf
		leafGen();
		
		glRotatef( 45, 1.0, 0.0, 0.0 );	// rotate again to draw second leaf
		leafGen();

		glTranslatef( 0.0, 0.0, length );	// moves leaf to end of branch

	 }

	if (nSeasons == 1){
			glPopMatrix();
			return;
	}
	
	length = length/1.2;	// make length and diameter of branches smaller every recursion
    diam = diam/1.5;

    srand(tempSeedVector[tempSeedVector.size()-1]);	// load a seed to use and remove this from temporar1 seed vector
    tempSeedVector.pop_back();

	float num = rand() % 70;	// random number generator for angle of branch
	num = num * -1;

     glPushMatrix();
        glRotatef( num, 0.3, 0.0,  0.5 );	// rotate and draw first branch
        growBranch(nSeasons - 1, diam, length, shadow);
     glPopMatrix();
	srand(tempSeedVector[tempSeedVector.size()-1]); // use up another seed
    tempSeedVector.pop_back();
	num = rand() % 70;
	num = num * -1;

     glPushMatrix();
        glRotatef( num, -0.7, 0.0, 1.0 );	// rotate again and draw second branch
        growBranch(nSeasons - 1, diam, length, shadow);
     glPopMatrix();
  glPopMatrix();
   }

}

// Create tree using number of seasons
void GLPolygonWidget::treeGen( int nSeasons) {

	glPushMatrix();

		glEnable(GL_TEXTURE_2D);	// draw grass texture
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPEAT);
		glBindTexture(GL_TEXTURE_2D, texture_id);	

		glTranslatef(0,0,-0.0001);
		glBegin(GL_QUADS);
			glColor3f(0.0,0.36,0.04);
			glTexCoord2f(0, 10);
			glVertex3fv(ground_plane[0]);
			glTexCoord2f(10, 10);
			glVertex3fv(ground_plane[1]);
			glTexCoord2f(10, 0);
			glVertex3fv(ground_plane[2]);
			glTexCoord2f(0, 0);
			glVertex3fv(ground_plane[3]);
		glEnd();

		glDisable(GL_TEXTURE_2D);
		
	glPopMatrix();

	// create random coordinate for tree
	srand(seedCoordVector[0]);
	GLfloat randX = rand()%11+(-5);
	srand(seedCoordVector[1]);
	GLfloat randY = rand()%11+(-5);
	glTranslatef(randX,randY,0);

	// makes sure the lighting for tree is correct
	GLfloat light_position[] = {-randX, -randY, 8.0, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	
	baseQuad = gluNewQuadric();

	// shadow matrix using light position
	GLfloat shadowMatrix[16] = {light_position[2],0.0,0.0,0.0,
									0.0,light_position[2],0.0,0.0,
									randX,randY,0.0,-1.0,
									0.0,0.0,0.0,light_position[2]};

	glEnable(GL_LIGHTING);
			
	if (numSeasons > 1) tempSeedVector = seedVector; // makes a copy of seeds

	growBranch(nSeasons, 0.08, 0.8, false);	// render tree

	if (numSeasons > 1) tempSeedVector = seedVector;	// makes a copy of seeds

	if (lightEnabled){ 
		glMultMatrixf(shadowMatrix);	// apply shadow matrix and draw shadow
		growBranch(nSeasons, 0.08, 0.8, true);	
	}

  return;
}

// generate seeds for random number generators for tree branches
std::vector<float> GLPolygonWidget::genRand(int height) {
	std::vector<float> seeds;
	srand (time(NULL));
	for (int i = 0 ; i < pow(2.0,height)-2; ++i){	// create as man1 seeds as there are branches
		seeds.push_back(rand());
	}
	return seeds;
}

// Change seasons using spinnerbox UI
void GLPolygonWidget::setSeasons(int depth){
	numSeasons = depth;
	if (numSeasons > 1 ){
		seedVector = genRand(numSeasons);	// create seeds using number of seasons
	}
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
	if (checked) {
		glEnable(GL_LIGHT0);
		lightEnabled = true;
	}
	else {
		glDisable(GL_LIGHT0);
		lightEnabled = false;
	}
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

// handles moving tree to random position using seeds
void GLPolygonWidget::moveTree(){
	srand (time(NULL));
	seedCoordVector.clear();
	seedCoordVector.push_back(rand());
	seedCoordVector.push_back(rand());
	updateGL();
}

// scroll wheel zoom
void GLPolygonWidget::wheelEvent ( QWheelEvent* event )
{
    scaleChange+= ((event->delta()/120)*0.05); 
    updateGL();
}