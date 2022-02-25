#include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
//  #include <windows.h>
#include <GL/glut.h>
#endif

#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <time.h>
#include "imageloader.h"
#include<windows.h>

float _angle = 0.0;
GLuint _textureBrick, _textureDoor, _textureGrass, _textureRoof, _textureWindow, _textureSky;

using namespace std;
/** Posiciones en X, Y, Z desde arriba*/
static float eyex = 0.0;
static float eyey = 0.2;
static float eyez = 10.0;

/** Rotacion Camara*/
static float centerx = 0.0;
static float centery = 0.2;
static float centerz = 0.0;
//

/** Como levantar la camara*/
static float upx = 0.0;
static float upy = 2.0;
static float upz = 1.0;

/** Variables de control de la velocidad  of rotacion/translacion/zoom */
#define DEGREES_PER_PIXEL	.8f
#define UNITS_PER_PIXEL		.1f
#define ZOOM_FACTOR		.04f

int xmatriz=20;
int ymatriz=39;

/** Matriz con las posiciones validas para el sujeto*/
int mapaPasillos[40][40] = {
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0},
{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,1,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,1,1,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,1,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0}};



/** Inician Elementos para la rotacion y el movimiento del mouse*/
#define UPPER_ARM_HEIGHT  3.0//3.0
#define LOWER_ARM_HEIGHT  2.0//2.0
#define UPPER_ARM_RADIUS  .5//.5
#define LOWER_ARM_RADIUS  .5//.5
const int AXIS_SIZE = 3000;
/** Structure to define the state of the mouse */
typedef struct {
  bool leftButton;
  bool rightButton;
  int x;
  int y;
} MouseState;

int moverZ=2;
int moverX=0;
int moverY=0;

MouseState mouseState = { false, false, 0, 0 };

/* Scene rotation angles to alter interactively */
float xRotate = 0, yRotate = 40;
/** Terminaa la declaracion de elementos para el movimiento de rotacion con el mouse*/

/****************************************************************************
 Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
****************************************************************************/
void draw_axis() {
  glBegin(GL_LINES);
  // eje X, color rojo
  glColor3f(1, 0, 0);
  glVertex3f(-AXIS_SIZE, 1, 0);
  glVertex3f(AXIS_SIZE, 0, 0);
  // eje Y, color verde
  glColor3f(0, 1, 0);
  glVertex3f(0, -AXIS_SIZE, 0);
  glVertex3f(0, AXIS_SIZE, 0);
  // eje Z, color azul
  glColor3f(0, 0, 1);
  glVertex3f(0, 1, -AXIS_SIZE);
  glVertex3f(0, 0, AXIS_SIZE);
  glEnd();
}

/** Declaracion de metodos para el manejo de las texturas BMP*/
/* Genera un ID unico para la Textura a partir de una imagen*/
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}
/** Matriz donde se cargan los edificios Grises segun el plano*/
 static void edificiosgrises(void){
    glColor3d(.6,.6,.6);

    //Edificio 1
    glPushMatrix();
        glTranslated(-8,0.5,7);
        glScalef(2,1,2);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio 2
    glPushMatrix();
        glTranslated(-8,0.5,4);
        glScalef(2,1,2);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio 3
    glPushMatrix();
        glTranslated(-13,0.5,3.5);
        glScalef(2,1,1);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio 5
    glPushMatrix();
        glTranslated(-11.5,0.5,0.5);
        glScalef(1,1,3);
        glutSolidCube(1);
    glPopMatrix();
     //Edificio 6
    glPushMatrix();
        glTranslated(-19.5,0.5,-3.5);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio 7
    glPushMatrix();
        glTranslated(-14,0.5,-5);
        glScalef(2,1,2);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio 8
    glPushMatrix();
        glTranslated(-11,0.5,-5.5);
        glScalef(2,1,3);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio 9
    glPushMatrix();
        glTranslated(-5.5,0.5,-10);
        glScalef(1,1,2);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio 10
    glPushMatrix();
        glTranslated(-3,0.5,-13.5);
        glScalef(4,2,1);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio 11
    glPushMatrix();
        glTranslated(-1,0.5,-10.5);
        glScalef(4,2,1);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio 12
    glPushMatrix();
        glTranslated(4,0.5,-11);
        glScalef(4,2,2);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio 13
    glPushMatrix();
        glTranslated(-3,0.5,-4.5);
        glScalef(2,2,1);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio 14
    glPushMatrix();
        glTranslated(-3,0.5,2.5);
        glScalef(2,1,1);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio 15
    glPushMatrix();
        glTranslated(1.5,0.5,1.5);
        glScalef(3,1,3);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio 16
    glPushMatrix();
        glTranslated(8.5,0.5,0);
        glScalef(3,1,4);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio 17
    glPushMatrix();
        glTranslated(5,0.5,5);
        glScalef(2,1,2);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio 18
    glPushMatrix();
        glTranslated(14.5,0.5,7);
        glScalef(1,1,2);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio 19
    glPushMatrix();
        glTranslated(10.5,0.5,11.5);
        glScalef(1,1,3);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio 20
    glPushMatrix();
        glTranslated(8,0.5,13.5);
        glScalef(2,1,1);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio 21
    glPushMatrix();
        glTranslated(7,0.5,15.5);
        glScalef(2,1,1);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio 22
    glPushMatrix();
        glTranslated(2.5,0.5,15.5);
        glScalef(3,1,1);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio 24
    glPushMatrix();
        glTranslated(1,0.5,11.5);
        glScalef(2,1,1);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio 25
    glPushMatrix();
        glTranslated(0,0.5,9.5);
        glScalef(4,1,1);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio 26
    glPushMatrix();
        glTranslated(1,0.5,17.5);
        glScalef(2,1,1);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio 27
    glPushMatrix();
        glTranslated(0,0.5,18.5);
        glScalef(2,1,1);
        glutSolidCube(1);
    glPopMatrix();

}
/**Matriz donde se cargan los edificios Naranjas segun el plano*/
static void edificiosnaranjas(void){
    glColor3d(1,.5,0);
    //Edificio I
    glPushMatrix();
        glTranslated(-11,0.5,-8);
        glScalef(2,1,2);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio II
    glPushMatrix();
        glTranslated(-11.5,0.5,-11.5);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio III
    glPushMatrix();
        glTranslated(-7,0.5,-4.95);
        glScalef(2,1,2);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio IV
    glPushMatrix();
        glTranslated(-7,0.5,-7);
        glScalef(2,1,2);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio V
    glPushMatrix();
        glTranslated(-3.5,0.5,-1);
        glScalef(1,1,4);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio VI
    glPushMatrix();
        glTranslated(-3,0.5,-7);
        glScalef(2,1,2);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio VII
    glPushMatrix();
        glTranslated(-6.5,0.5,-10);
        glScalef(1,1,2);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio VIII
    glPushMatrix();
        glTranslated(-3,0.5,-12.5);
        glScalef(4,2,1);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio IX
    glPushMatrix();
        glTranslated(3,0.5,-7.5);
        glScalef(2,2,1);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio X
    glPushMatrix();
        glTranslated(13,0.5,7);
        glScalef(2,1,2);
        glutSolidCube(1);
    glPopMatrix();
}
/**Matriz donde se cargan los edificios Azules segun el plano*/
static void edificiosazules(void){
    glColor3d(0,0,1);
    //Edificio SUM
    glPushMatrix();
         glTranslated(-14.5,0.5,3.5);
         glutSolidCube(1);
    glPopMatrix();
    //Edificio A
    glPushMatrix();
        glTranslated(-16,0.5,-1.5);
        glScalef(4,1,1);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio B
    glPushMatrix();
        glTranslated(-8,0.5,-1.5);
        glScalef(4,1,1);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio C
    glPushMatrix();
        glTranslated(-8,0.5,0.5);
        glScalef(4,1,1);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio D
    glPushMatrix();
        glTranslated(10.5,0.5,4.5);
        glScalef(3,1,1);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio E
    glPushMatrix();
        glTranslated(4,0.5,7.5);
        glScalef(4,1,1);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio F
    glPushMatrix();
        glTranslated(5,0.5,9.5);
        glScalef(4,1,1);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio G
    glPushMatrix();
        glTranslated(6,0.5,11.5);
        glScalef(4,1,1);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio H
    glPushMatrix();
        glTranslated(-1,0.5,11.5);
        glScalef(2,1,1);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio I
    glPushMatrix();
        glTranslated(3.5,0.5,18);
        glScalef(3,2.5,2);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio J
    glPushMatrix();
        glTranslated(4.5,0.5,15.5);
        glScalef(1,1,1);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio K
    glPushMatrix();
        glTranslated(10.5,0.5,13.5);
        glScalef(1,1,1);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio L
    glPushMatrix();
        glTranslated(1,0.5,-2.5);
        glScalef(2,2,1);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio M
    glPushMatrix();
        glTranslated(-2.5,0.5,-6.5);
        glutSolidCube(1.01);
    glPopMatrix();
    //Edificio N
    glPushMatrix();
        glTranslated(-1.5,0.5,-7.5);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio N*
    glPushMatrix();
        glTranslated(.5,0.5,-13.5);
        glutSolidCube(1);
    glPopMatrix();

}
/**Matriz donde se cargan los edificios Rojos segun el plano*/
static void edificiosrojos(void){
    glColor3d(1,0,0);
    //Edificio 4
    glPushMatrix();
        glTranslated(-17,0.5,0.5);
        glScalef(4,1,1);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio 23
    glPushMatrix();
        glTranslated(0,0.5,13.5);
        glScalef(4,1,1);
        glutSolidCube(1);
    glPopMatrix();

}
/**Matriz donde se cargan los edificios Amarillos segun el plano*/
static void edificiosamarillos(){
    glColor3d(1.1,1.5,.5);
    //Edificio O
    glPushMatrix();
        glTranslated(9,0.5,-3.5);
        glScaled(2,1,1);
        glutSolidCube(1);
    glPopMatrix();
}
/**Matriz donde se cargan los edificios Morados segun el plano*/
static void edificiosmorados(){
    glColor3d(1,0,1);
    //Edificio Morado 1
    glPushMatrix();
        glTranslated(-11.5,0.5,-1.5);
        glutSolidCube(1);
    glPopMatrix();
    //Edificio O
    glPushMatrix();
        glTranslated(8.5,0.5,-4.5);
        glutSolidCube(1);
    glPopMatrix();

}

static void areasverdes(){
    glColor3d(.3,1,.3);

    glPushMatrix();
        glTranslated(0,-.01,-17);
        glScalef(800,-.6,120);
        glutSolidCube(.05);
    glPopMatrix();
    glPushMatrix();
        glTranslated(-16,-.01,-9);
        glScalef(160,-.6,120);
        glutSolidCube(.05);
    glPopMatrix();
    glPushMatrix();
        glTranslated(15,-.01,-10);
        glScalef(200,-.6,160);
        glutSolidCube(.05);
    glPopMatrix();
    glPushMatrix();
        glTranslated(-18,-.01,4);
        glScalef(80,-.6,80);
        glutSolidCube(.05);
    glPopMatrix();
    glPushMatrix();
        glTranslated(-13,-.01,8);
        glScalef(80,-.6,40);
        glutSolidCube(.05);
    glPopMatrix();
    glPushMatrix();
        glTranslated(-8,-.01,2.5);
        glScalef(80,-.6,40);
        glutSolidCube(.05);
    glPopMatrix();
    glPushMatrix();
        glTranslated(-7,-.01,3.5);
        glScalef(40,-.6,60);
        glutSolidCube(.05);
    glPopMatrix();
    glPushMatrix();
        glTranslated(-10.5,-.01,4);
        glScalef(60,-.6,40);
        glutSolidCube(.05);
    glPopMatrix();
    glPushMatrix();
        glTranslated(-9.5,-.01,7.5);
        glScalef(20,-.6,60);
        glutSolidCube(.05);
    glPopMatrix();
    glPushMatrix();
        glTranslated(-6.5,-.01,9);
        glScalef(20,-.6,100);
        glutSolidCube(.05);
    glPopMatrix();
    glPushMatrix();
        glTranslated(-8,-.01,9.5);
        glScalef(80,-.6,60);
        glutSolidCube(.05);
    glPopMatrix();
    glPushMatrix();
        glTranslated(-1.5,-.01,16);
        glScalef(80,-.6,40);
        glutSolidCube(.05);
    glPopMatrix();
    glPushMatrix();
        glTranslated(1.5,-.01,18.5);
        glScalef(20,-.6,20);
        glutSolidCube(.05);
    glPopMatrix();
    glPushMatrix();
        glTranslated(5.5,-.01,18);
        glScalef(20,-.6,40);
        glutSolidCube(.05);
    glPopMatrix();
    glPushMatrix();
        glTranslated(4,-.01,15.5);
        glScalef(200,-.6,60);
        glutSolidCube(.05);
    glPopMatrix();
    glPushMatrix();
        glTranslated(14,-.01,12);
        glScalef(120,-.6,80);
        glutSolidCube(.05);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-.5,-.01,5);
        glScalef(20,-.6,20);
        glutSolidCube(.05);
    glPopMatrix();
    glPushMatrix();
        glTranslated(1.5,-.01,5);
        glScalef(20,-.6,20);
        glutSolidCube(.05);
    glPopMatrix();
    glPushMatrix();
        glTranslated(.5,-.01,7.5);
        glScalef(60,-.6,40);
        glutSolidCube(.05);
    glPopMatrix();
    glPushMatrix();
        glTranslated(-1,-.01,0);
        glScalef(40,-.6,120);
        glutSolidCube(.05);
    glPopMatrix();
    glPushMatrix();
        glTranslated(2,-.01,-1);
        glScalef(80,-.6,40);
        glutSolidCube(.05);
    glPopMatrix();
    glPushMatrix();
        glTranslated(3.5,-.01,1.5);
        glScalef(20,-.6,60);
        glutSolidCube(.05);
    glPopMatrix();
    glPushMatrix();
        glTranslated(3,-.01,-6);
        glScalef(40,-.6,40);
        glutSolidCube(.05);
    glPopMatrix();
    glPushMatrix();
        glTranslated(-2.5,-.01,10.5);
        glScalef(20,-.6,60);
        glutSolidCube(.05);
    glPopMatrix();
    glPushMatrix();
        glTranslated(11,-.01,7);
        glScalef(40,-.6,40);
        glutSolidCube(.05);
    glPopMatrix();
    glPushMatrix();
        glTranslated(6.5,-.01,7);
        glScalef(20,-.6,40);
        glutSolidCube(.05);
    glPopMatrix();
    glPushMatrix();
        glTranslated(4.5,-.01,6.5);
        glScalef(60,-.6,20);
        glutSolidCube(.05);
    glPopMatrix();
    glPushMatrix();
        glTranslated(3,-.01,-9);
        glScalef(40,-.6,40);
        glutSolidCube(.05);
    glPopMatrix();

}

void Display(void) {
    Image* image = loadBMP("roof.bmp");
	_textureRoof = loadTexture(image);

	image = loadBMP("bricks.bmp");
	_textureBrick = loadTexture(image);

	delete image;
  /* draw to the back buffer */
  //glDrawBuffer(GL_BACK);
  /* clear the display */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* (Re)position the camera */
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
    gluLookAt(eyex,eyey,eyez,0,0,0 ,0,1,0);
    glTranslated(eyex, 0, eyez);
    glRotatef(xRotate, 0, 1, 0);
    glTranslated(-eyex, 0, -eyez);

  /* Rotate the scene in the x and y directions */
    //SUELO
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);


    glColor3d(.8,.8,.8);
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureRoof);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        /*glTranslated(0,-.04,0);
        glScalef(1000,-.6,1000);
        glutSolidCube(.04);*/
        glBegin(GL_QUADS);
            glTexCoord3f(0.0,1.0,0.1);  glVertex3f(-20,0,20);
            glTexCoord3f(1.0,1.0,0.1);  glVertex3f(20,0,20);
            glTexCoord3f(1.0,0.0,0.1);  glVertex3f(20,0,-20);
            glTexCoord3f(0.0,0.0,0.1);  glVertex3f(-20,0,-20);
        glEnd();
    glPopMatrix();

    //ATRIO
    glColor3d(0,0,0);
    glPushMatrix();
        glTranslated(-3,0.5,4.5);
        glScalef(2,1,1);
        glutSolidCube(1);
    glPopMatrix();
    //cargamos los edificios definidos por sus colores
    edificiosgrises();
    edificiosnaranjas();
    edificiosazules();
    edificiosrojos();
    edificiosamarillos();
    edificiosmorados();
    areasverdes();
   draw_axis();
  glutSwapBuffers();
}

static void key(unsigned char key, int x, int y){

    switch (key)
    {
        case 27 :
        case 'p':
            exit(0);
            break;

        case 'w':
            //std::cout << "Matriz en x-1:" << mapaPasillos[xmatriz-1][ymatriz]<< "\n";
            if(ymatriz>0){
            if(mapaPasillos[ymatriz-1][xmatriz]==1){
            eyez=eyez-1;
            centerz=centerz-1;
            ymatriz--;
            }
            }
            break;

        case 'a':
            if(xmatriz>0){
                if(mapaPasillos[ymatriz][xmatriz-1]==1){
                 eyex=eyex-1;
                 centerx=centerx-1;
                 xmatriz--;
            }
            }
            break;
        case 's':
            if(ymatriz<39){
                if(mapaPasillos[ymatriz+1][xmatriz]==1){
                 eyez=eyez+1;
                 centerz=centerz+1;
                 ymatriz++;;
                }
            }
        break;
        case 'd':
            if(xmatriz<39){
                if(mapaPasillos[ymatriz][xmatriz+1]==1){
                 eyex=eyex+1;
                 centerx=centerx+1;
                xmatriz++;
            }
            }
        break;

        case 'o':
                eyex = 0.5;
                eyey = 0.2;
                eyez = 19.5;
                centerx = 0.0;
                centery = 0.2;
                centerz = 1.0;
                upx = 0;
                upy = 2.0;
                upz = 1.0;
        break;
        case 'i':
                eyex = 0;
                eyey = 10;
                eyez = 26;
                centerx = 0;
                centery = 8;
                centerz = 0;
                upx = 0;
                upy = .2;
                upz = 1;

        break;
        case 'm':
                 std::cout << "Eye x:" << eyex << "\n";
                 std::cout << "Eye y:" << eyey << "\n";
                 std::cout << "Eye z:" << eyez << "\n";
                 std::cout << "Center x:" << centerx<< "\n";
                 std::cout << "Center y:" << centery<< "\n";
                 std::cout << "Center z:" << centerx<< "\n";
                 std::cout << "Up x:" << upx<< "\n";
                 std::cout << "Up y:" << upy<< "\n";
                 std::cout << "Up z:" << upz<< "\n";
                 std::cout << "Matriz x:" << xmatriz<< "\n";
                 std::cout << "Matriz y:" << ymatriz<< "\n";
        break;
    }


    glutPostRedisplay();
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

void myInit() {
  glClearColor(109,183,247,1);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(120.0f, 1.0f, 0.1f, -10.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnable(GL_DEPTH_TEST);


    //delete image;
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(3120,4160);
  glutCreateWindow("ITO");

  /* register callback functions */
  glutDisplayFunc(Display);
  glutMouseFunc(Mouse);
  glutMotionFunc(MouseMove);

  /* set window attributes */
  myInit();
    glutKeyboardFunc(key);

  /* start event processing */
  glutMainLoop();
}
