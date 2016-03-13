// Khen Cruzat - sc13kvc - 200760716

#include "GLPolygonWidget.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <QtDebug>
#include <QDebug>
#include <time.h>
#include <QTimer>
#include <QKeyEvent>

GLfloat light_position[4] = {0.0, 0.0, 40.0, 1.0};	// define some vectors
GLfloat ground_plane[4][4] = {{-100.0, 100.0, 0.0},
								{100.0, 100.0, 0.0},
								{100.0, -100.0, 0.0},
								{-100.0, -100.0, 0.0}};
const float speedChange = 0.001;
const float angle = 0.02;

/**
 * Implementation for OpenGL widget
 */
GLPolygonWidget::GLPolygonWidget(QWidget *parent) : QGLWidget(parent){
	this->setFocusPolicy(Qt::StrongFocus);
	goForward = 0; goUp = 0; goRight = 0; doRoll = 0;
	speed = 0.00;
	forward = Vector(0, 0, -1);
    right = Vector(1, 0, 0);
    up = Vector(0, 1, 0);
    currentPosition = Point(0, 10, 0);
    eye = currentPosition;
    center = currentPosition + forward;
    upVec = up;

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

	currentTime = 0;
	previousTime = 0;
	frameCount = 0;
	qImageCount = 0;

	QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(1000/60);
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

	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 3000.0);
    glMatrixMode(GL_MODELVIEW);

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
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 3000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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
	glPushMatrix();
	gluLookAt(eye.x, eye.y, eye.z,
		                    center.x, center.y, center.z,
		                    upVec.x, upVec.y, upVec.z);
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
			gluSphere(baseQuad2, 8, 20, 20);
		glPopMatrix();
	}

	treeGen( numSeasons);	// draw tree

	glPopMatrix();


	glFlush();

	frameCount++;

	currentTime = glutGet(GLUT_ELAPSED_TIME);
	int timeInterval = currentTime - previousTime;
	// std::cout << timeInterval << std::endl;

	if(timeInterval > 1000) {
		// std::cout << frameCount / (timeInterval/1000.0f) << std::endl;

		QImage image = this->grabFrameBuffer();
		srand(time(NULL));
		QString str = QString::number(qImageCount) + ".jpg";
		// image.save(str,"JPEG");
		qImageCount++;

		previousTime = currentTime;

		frameCount = 0;
	}


}

// creates a leaf
void GLPolygonWidget::leafGen(bool shadow){

	GLfloat scale = 2.0;

	GLfloat vertices[][3] = {{0.0,-0.6f/scale,0.0},{-0.5f/scale,-0.3f/scale,0.1f/scale},
	{-0.3f/scale,-0.3f/scale,0.0},{-0.5f/scale,0.2f/scale,-0.1f/scale}, {-0.2f/scale,0.0,0.0}, 
	{0.0,0.6f/scale,0.0}, {0.2f/scale,0.0,0.0}, {0.5f/scale,0.2f/scale,-0.1f/scale}, {0.3f/scale,-0.3f/scale,0.0}, 
	{0.5f/scale,-0.3f/scale,0.1f/scale}};

	GLfloat normals[][3] = {{0.0,-0.6f/scale,0.0},{-0.5f/scale,-0.3f/scale,0.1f/scale},
	{-0.3f/scale,-0.3f/scale,0.0},{-0.5f/scale,0.2f/scale,-0.1f/scale}, {-0.2f/scale,0.0,0.0}, 
	{0.0,0.6f/scale,0.0}, {0.2f/scale,0.0,0.0}, {0.5f/scale,0.2f/scale,-0.1f/scale}, {0.3f/scale,-0.3f/scale,0.0}, 
	{0.5f/scale,-0.3f/scale,0.1f/scale}};


	GLfloat colours[2][3] = {{0.0,0.3,0.1},{0.6,0.3,0.1}};

	if (shadow) {
		for (int i=0;i<2; ++i){
			for (int j=0;j<3;++j){
				colours[i][j] = 0.0;
			}
		}
	}

	// Draw veins in leaf
	glBegin(GL_LINES);
		glColor3fv(colours[1]);
		glVertex2fv(vertices[0]);
		glColor3fv(colours[1]);
		glVertex2fv(vertices[2]);
		glColor3fv(colours[1]);
		glVertex2fv(vertices[0]);
		glColor3fv(colours[1]);
		glVertex2fv(vertices[4]);
		glColor3fv(colours[1]);
		glVertex2fv(vertices[0]);
		glColor3fv(colours[1]);
		glVertex2fv(vertices[5]);
		glColor3fv(colours[1]);
		glVertex2fv(vertices[0]);
		glColor3fv(colours[1]);
		glVertex2fv(vertices[6]);
		glColor3fv(colours[1]);
		glVertex2fv(vertices[0]);
		glColor3fv(colours[1]);
		glVertex2fv(vertices[8]);
	glEnd();

	glBegin(GL_POLYGON);
		glColor3fv(colours[0]);
		glNormal3fv(normals[0]);
		glVertex3fv(vertices[0]);
		glNormal3fv(normals[1]);
		glVertex3fv(vertices[1]);
		glNormal3fv(normals[2]);
		glVertex3fv(vertices[2]);
		glNormal3fv(normals[3]);
		glVertex3fv(vertices[3]);
		glNormal3fv(normals[4]);
		glVertex3fv(vertices[4]);
		glNormal3fv(normals[5]);
		glVertex3fv(vertices[5]);
		glNormal3fv(normals[6]);
		glVertex3fv(vertices[6]);
		glNormal3fv(normals[7]);
		glVertex3fv(vertices[7]);
		glNormal3fv(normals[8]);
		glVertex3fv(vertices[8]);
		glNormal3fv(normals[9]);
		glVertex3fv(vertices[9]);
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

		glRotatef( 45, 0.0, 1.0, 0.0 );	// rotate to draw first leaf

		if (shadow){
			leafGen(true);
			glRotatef( 45, 1.0, 0.0, 0.0 );	// rotate again to draw second leaf
			leafGen(true);
			
		}
		else {
			leafGen(false);
			glRotatef( 45, 1.0, 0.0, 0.0 );	// rotate again to draw second leaf
			leafGen(false);
		}

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
			glTexCoord2f(0, 20);
			glVertex3fv(ground_plane[0]);
			glTexCoord2f(20, 20);
			glVertex3fv(ground_plane[1]);
			glTexCoord2f(20, 0);
			glVertex3fv(ground_plane[2]);
			glTexCoord2f(0, 0);
			glVertex3fv(ground_plane[3]);
		glEnd();

		glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	// create random coordinate for tree
	srand(seedCoordVector[0]);
	GLfloat randX = rand()%101+(-50);
	srand(seedCoordVector[1]);
	GLfloat randY = rand()%101+(-50);
	glTranslatef(randX,randY,0);

	// makes sure the lighting for tree is correct
	GLfloat light_position[] = {-randX, -randY, 40.0, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	
	baseQuad = gluNewQuadric();

	// shadow matrix using light position
	GLfloat shadowMatrix[16] = {light_position[2],0.0,0.0,0.0,
									0.0,light_position[2],0.0,0.0,
									randX,randY,0.0,-1.0,
									0.0,0.0,0.0,light_position[2]};

	glEnable(GL_LIGHTING);
			
	if (numSeasons > 1) tempSeedVector = seedVector; // makes a copy of seeds

	growBranch(nSeasons, 0.8, 4, false);	// render tree

	if (numSeasons > 1) tempSeedVector = seedVector;	// makes a copy of seeds

	if (lightEnabled){ 
		glMultMatrixf(shadowMatrix);	// apply shadow matrix and draw shadow
		growBranch(nSeasons, 0.8, 4, true);	
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

void GLPolygonWidget::move()
{
	pickMovement();
    updateCurrent();
    updateGL();
}

void GLPolygonWidget::roll(double angle)
{
    // To roll, I want to go right, by the amount of the angle, plus
    // up by this amount too.
    //I roll the other way by a negative angle.
    Vector tempRight = (right * cos(angle));
    Vector tempUp = (up * sin(angle));

    right = tempRight + tempUp;
    right = right.getUnitVector(right);
    up = right.crossProduct(forward);
}

void GLPolygonWidget::pitch(double angle)
{
    // To pitch, I want to go up, by the amount of the angle, plus
    // forward by this amount too.
    // Pitch down is done by a negative angle.
    Vector tempForward = (forward * cos(angle));
    Vector tempUp = (up * sin(angle));

    forward = tempForward + tempUp;
    forward = forward.getUnitVector(forward);
    up = right.crossProduct(forward);
}

void GLPolygonWidget::yaw(double angle)
{
    // To yaw, I want to go right, by the amount of the angle, plus
    // up by this amount too.
    // Left yaw is done by a negative angle.
    Vector tempRight = (right * cos(angle));
    Vector tempForward = (forward * sin(angle));

    right = tempRight + tempForward;
    right = right.getUnitVector(right);
    forward = up.crossProduct(right);
}

void GLPolygonWidget::keyPressEvent(QKeyEvent* event)
{
    // Pick the key that has been pressed and assign the
    // relevant variables.
    switch ( event->key()) {
        case Qt::Key_Up:
            goUp = -1;
            break;
        case Qt::Key_Down:
            goUp = 1;
            break;
        case Qt::Key_Right:
            goRight = -1;
            break;
        case Qt::Key_Left:
            goRight = 1;
            break;
        case Qt::Key_Q:
            doRoll = 1;
            break;
        case Qt::Key_E:
            doRoll = -1;
            break;
        case Qt::Key_W:
            goForward = 1;
            break;
        case Qt::Key_S:
            goForward = -1;
            break;
        case Qt::Key_Space:
            speed = 0;
        default:
            event->ignore();
            break;
    }
}

void GLPolygonWidget::keyReleaseEvent( QKeyEvent* event )
{
    switch ( event->key()) {
        case Qt::Key_Up:
            goUp = 0;
            break;
        case Qt::Key_Down:
            goUp = 0;
            break;
        case Qt::Key_Right:
            goRight = 0;
            break;
        case Qt::Key_Left:
            goRight = 0;
            break;
        case Qt::Key_Q:
            doRoll = 0;
            break;
        case Qt::Key_E:
            doRoll = 0;
            break;
        case Qt::Key_W:
            goForward = 0;
            break;
        case Qt::Key_S:
            goForward = 0;
            break;
        default:
            event->ignore();
            break;
    }
}

void GLPolygonWidget::updateCurrent()
{
    // The current position is the original position plus
    // the movement vector times by the speed
    Vector change = (forward * speed);
    currentPosition = currentPosition + change;

    // Eye is where I currently am
    eye = currentPosition;
    // Center (What I'm looking at) is the eye + what is infront of me
    center = currentPosition + forward;
    // Up vector is what is currently up relative to me
    upVec = up;

}

void GLPolygonWidget::pickMovement()
{
    // Move if required
    if(goUp != 0)
        pitch(goUp * angle);
    if(goRight != 0)
        yaw(goRight * angle);
    if(goForward != 0)
        speed = speed + (speedChange * goForward);
    if(doRoll != 0)
        roll(doRoll * angle);
}

void GLPolygonWidget::simulateKey(std::string key){

	if (key == "Up")
        goUp = -1;
    if (key == "Down")
        goUp = 1;
    if (key == "Right")
        goRight = -1;
    if (key == "Left")
        goRight = 1;
    if (key == "Q")
        doRoll = 1;
    if (key == "E")
        doRoll = -1;
    if (key == "W")
        goForward = 1;
    if (key == "S")
        goForward = -1;
    if (key == "Space")
        speed = 0;
    if (key == "-Up")
        goUp = 0;
    if (key == "-Down")
        goUp = 0;
    if (key == "-Right")
        goRight = 0;
    if (key == "-Left")
        goRight = 0;
    if (key == "-Q")
        doRoll = 0;
    if (key == "-E")
        doRoll = 0;
    if (key == "-W")
        goForward = 0;
    if (key == "-S")
        goForward = 0;
}