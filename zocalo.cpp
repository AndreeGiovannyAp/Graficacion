#include <glut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <time.h>
#include<windows.h>
float eyex = -25;
float eyey = 2;
float eyez = -25;
float centerx = 0.0f;
float centery = 0.2f;
float centerz = 0.0f;
float upx = 0.0f;
float upy = 2.0f;
float upz = 1.0f;
int moverZ=2;
int moverX=0;
int moverY=0;
#define DEGREES_PER_PIXEL	.8f
#define UNITS_PER_PIXEL		.1f
#define ZOOM_FACTOR		.04f
typedef struct {
	bool leftButton;
	bool rightButton;
	int x;
	int y;
} MouseState;
MouseState mouseState = { false, false, 0, 0 };
/* Scene rotation angles to alter interactively */
float xRotate = 0, yRotate = 40;
int xmatriz=0;
int ymatriz=0;
int mapaPasillos[50][50] = {
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
void myInit() {
	glClearColor(109,183,247,1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(120.0, 1.0, 0.1, -10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
}
void hacerKiosco(){
	glColor3d(0,0,0);
	glPushMatrix();
	glTranslated(0,4,-1);
	glScalef(3,5,1);
	glutSolidCube(3);
	glPopMatrix();
}

void dibujaCuadros(double x, double y, double z,double ancho, double alto,double largo,double r,double g, double b){
	glColor3d(r,g,b);
	glPushMatrix();
	glTranslated(x,y,z);	//x, y ,z 
	glScalef(ancho,alto,largo);	// ancho alto y largo 
	glutSolidCube(1);	// hace el cubo
	glPopMatrix();
	glColor3d(1,1,0);
}
void edificios(void){
	//EdiFICIOS
	dibujaCuadros(-27,2,-1,2,8,20,0,0,0);
	dibujaCuadros(27,2,-1,2,8,20,0,0,0);
	dibujaCuadros(-1,2,27,20,8,2,0,0,0);
	dibujaCuadros(-1,2,-27,20,8,2,0,0,0);
	//TECHOS
	dibujaCuadros(-24,6,-1,4,1,20,1,1,0);
	dibujaCuadros(24 ,6,-1,4,1,20,1,1,0);
	dibujaCuadros(-1,6,24,20,1,4,1,1,0);
	dibujaCuadros(-1,6,-24,20,1,4,1,1,0);
	//Pilares Edificios 
	for (int i = -10.5; i < 9.5;)
	{
		dibujaCuadros(-23,0.5,i,1,10,1,1,0,0);
		dibujaCuadros(23,0.5,i,.3,10,1,1,0,0);
		dibujaCuadros(i,0.5,23,.3,10,1,1,0,0);
		dibujaCuadros(i,0.5,-23,.3,10,1,1,0,0);
		i+=3;
	}
}
void partesverdes(double x, double y, double z,double ancho, double alto,double largo,double r,double g, double b){
    glColor3d(r,g,b);
    glPushMatrix();
        glTranslated(x,y,z);
        glScalef(ancho,alto,largo);
        glutSolidCube(.05);
    glPopMatrix();
}
void areasverdes(){
	//jardin arriba
  dibujaCuadros(-14,0,-16,14,-.6,4,.3,1,.3);
  dibujaCuadros(-1  ,0 ,-16,6 ,-.6,4,.3,1,.3);
  dibujaCuadros(7.5 ,0,-16,6 ,-.6,4,.3,1,.3);
  dibujaCuadros(16 ,0,-16,6 ,-.6,4,.3,1,.3);
  //jardin2
  dibujaCuadros(-18,0,-3,4,-.6,12,.3,1,.3);
 //palitos lineas derecha
  dibujaCuadros(-4,0,-6,2,-.6,7,.3,1,.3);
  dibujaCuadros(-4,0,8,2,-.6,7,.3,1,.3);
  dibujaCuadros(-13,0,-6,2,-.6,7,.3,1,.3);
  dibujaCuadros(-13,0,8,2,-.6,7,.3,1,.3);
  //lineas abajo
  dibujaCuadros(-7,0,5,5,-.6,1,.3,1,.3);
  dibujaCuadros(-10,0,11,5,-.6,1,.3,1,.3);
  dibujaCuadros(7,0,5,5,-.6,1,.3,1,.3);
  dibujaCuadros(10,0,11,5,-.6,1,.3,1,.3);
 //lienas arriba 
  dibujaCuadros(-7,0,-3,5,-.6,1,.3,1,.3);
  dibujaCuadros(7,0,-3,5,-.6,1,.3,1,.3);
  dibujaCuadros(-10,0,-9,5,-.6,1,.3,1,.3);
  dibujaCuadros(10,0,-9,5,-.6,1,.3,1,.3);
  //palitos izquierda
  dibujaCuadros(4,0,-6,2,-.6,7,.3,1,.3);
  dibujaCuadros(4,0,8,2,-.6,7,.3,1,.3);
  dibujaCuadros(13,0,-6,2,-.6,7,.3,1,.3);
  dibujaCuadros(13,0,8,2,-.6,7,.3,1,.3);

  //jardin
  dibujaCuadros(-14,0,17,15,-.6,3,.3,1,.3);
  dibujaCuadros(0,0,17,5,-.6,3,.3,1,.3);
  dibujaCuadros(9,0,17,5,-.6,3,.3,1,.3);
  dibujaCuadros(18,0,17,8,-.6,3,.3,1,.3);
  
}


void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyex,eyey,eyez,0,0,0 ,0,1,0);
	glTranslated(eyex, 0, eyez);
	glRotatef(xRotate, 0, 1, 0);
	glTranslated(-eyex, 0, -eyez);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glColor3d(.8,.8,.8);
	glPushMatrix();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	glTexCoord3f(0.0,1.0,0.1);  glVertex3f(-28,0,28);
	glTexCoord3f(1.0,1.0,0.1);  glVertex3f(28,0,28);
	glTexCoord3f(1.0,0.0,0.1);  glVertex3f(28,0,-28);
	glTexCoord3f(0.0,0.0,0.1);  glVertex3f(-28,0,-28);
	glEnd();
	edificios();
	areasverdes();
	glutSwapBuffers();
}
void Mouse(int button, int state, int x, int y) {
	// update the button state
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN)
			mouseState.leftButton = true;
		else
			mouseState.leftButton = false;
	}
	if (button == GLUT_RIGHT_BUTTON) {
		if (state == GLUT_DOWN)
			mouseState.rightButton = true;
		else
			mouseState.rightButton = false;
	}
	// update the mouse position, so we can track the mouse move
	mouseState.x = x;
	mouseState.y = y;
}
void MouseMove(int x, int y) {
	/* Calculate the displacement in movement */
	int xDelta = mouseState.x - x;
	int yDelta = mouseState.y - y;
	/* Commit the mouse position */
	mouseState.x = x;
	mouseState.y = y;

	/* If left button is down, rotate when mouse is moved */
	if (mouseState.leftButton) {
		xRotate -= xDelta * DEGREES_PER_PIXEL;
		yRotate -= yDelta * DEGREES_PER_PIXEL;
	}
	glutPostRedisplay();
}
void key(unsigned char key, int x, int y){
	switch (key)
	{
	case 27 :
	case 'p':
		exit(0);
		break;
        case 's':
            if(ymatriz>0){
            if(mapaPasillos[ymatriz-1][xmatriz]==1){
            eyez=eyez-1;
            centerz=centerz-1;
            ymatriz--;
            }
            }
            break;

        case 'd':
            if(xmatriz>0){
                if(mapaPasillos[ymatriz][xmatriz-1]==1){
                 eyex=eyex-1;
                 centerx=centerx-1;
                 xmatriz--;
            }
            }
            break;
        case 'w':
            if(ymatriz<50){
                if(mapaPasillos[ymatriz+1][xmatriz]==1){
                 eyez=eyez+1;
                 centerz=centerz+1;
                 ymatriz++;;
                }
            }
        break;
        case 'a':
            if(xmatriz<50){
                if(mapaPasillos[ymatriz][xmatriz+1]==1){
                 eyex=eyex+1;
                 centerx=centerx+1;
                xmatriz++;
            }
            }
        break;
	case 'o':
		eyex = -25;
		eyey = 2;
		eyez = -25;
		centerx = 0.0;
		centery = 0.2;
		centerz = 1.0;
		upx = 0;
		upy = 2.0;
		upz = 1.0;
		break;
	case 'h':
		eyex = 0.5;
		eyey = 2.2;
		eyez = 0.5;
		centerx = 0.0;
		centery = 0.2;
		centerz = 1.0;
		upx = 0;
		upy = 5.0;
		upz = 1.0;
		break;
	case 'i':
		eyex = 0;
		eyey = 25;
		eyez = -30;
		centerx = 0;
		centery = 8;
		centerz = 0;
		upx = 0;
		upy = .2;
		upz = 1;
		break;
	}
	glutPostRedisplay();
}
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(3000,4000);
	glutCreateWindow("ITO");
	/* register callback functions */
	glutDisplayFunc(Display);
	/* set window attributes */
	myInit();
	glutKeyboardFunc(key);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMove);
	/* start event processing */
	glutMainLoop();
}