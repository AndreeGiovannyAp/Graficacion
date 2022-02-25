#include <glut.h>
#include <stdlib.h>
#include "iostream"
//Ctrl+K+D
bool bandera=true;
bool toroide=true;
bool tort=false;
bool tort2=false;
void dibujarEjes()
{

	//Dibujar ejes
	glBegin(GL_LINES);

	//Eje X
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);

	//Eje Y
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	//Eje Z
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);

	glEnd();
}
void init(void) 
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_FLAT);
}
void drawTurtle(){  

	GLdouble x[] = { 0.0, 1.0, 2.0, 2.0, 2.0, 2.0, 1.0, 2.0, 3.0, 4.0, 5.0, 5.0, 4.0, 2.0, 3.0, 3.0,  3.0,  2.0,  3.0,  4.0,  5.0,  5.0,  4.0,  3.0,  2.0,  1.0,  0.0};
	GLdouble z[] = { 9.0, 9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 4.0, 5.0, 5.0, 4.0, 3.0, 2.0, 2.0, 1.0, 0.0, -1.0, -2.0, -2.0, -2.0, -3.0, -4.0, -5.0, -5.0, -4.0, -4.0, -4.0};
	GLint i;
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_LOOP);
	for (i=0;i<28;i++){
		glVertex3f((x[i]+1)*0.15,0.0,-.15*(1+z[i]));
	}
	for (i=26;i>=0;i--){
		glVertex3f(-.15*(x[i]+1),0.0,-.15*(z[i]+1));
	}
	glEnd();    

}

void drawSphereTurtle(){

	GLdouble valx[] = { 0.0, 4.0, -8.0, 0.0, 8.0,-4.0};
	GLdouble valz[] = { -6.0, 2.0, 0.0, 8.0, 0.0,-4.0};
	GLdouble r[] = { 6.0, 3.0, 2.0, 2.0, 2.0, 2.0};
	GLint i;
	glColor3f(0.0,0.0,1.0);
	for (i=0;i<6;i++){
		glutWireSphere(r[i]*0.1, 10.0, 10.0);
		glTranslatef(valx[i]*0.1,0.0,valz[i]*0.1);
	}   

}
void display(void) {

	/*

	if(toroide){*/
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(toroide){
		glColor3f(1.0,0.0,0.0);
		glutWireTorus(0.25,0.75, 28, 28);
		glColor3f(0.0,0.0,1.0) ;
		glutWireCube(.60) ;
	}
	if(bandera)
		dibujarEjes();
	if(tort)
		drawTurtle();
	if(tort2)
		drawSphereTurtle();

	glutSwapBuffers();

}

void tasten (unsigned  char key, int x, int y) {
	//printf("help %c", key );
	switch (key) {
	case 'h':
		printf("help\n\n");
		printf("c - Toggle culling\n");
		printf("q/escape - Quit\n\n");
		break;
	case 'c':
		if (glIsEnabled(GL_CULL_FACE))
			glDisable(GL_CULL_FACE);
		else
			glEnable(GL_CULL_FACE);
		break;
	case '1':
		glRotatef(1.0,1.,0.,0.);
		break;
	case '2':
		glRotatef(1.0,0.,1.,0.);
		break;
	case 'q':
		exit(0);
		break;
	case 'a':
		if(bandera)
			bandera=false;
		else
			bandera=true;
		break;
	case 'u':
		//Vista arrba 
		glLoadIdentity();
		gluLookAt(0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0);
		break;
	case 'd':
		//Vista abajo
		glLoadIdentity();
		gluLookAt(0.0, -3.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0);
		break;
	case 'r':
		//vista derecha
		glLoadIdentity();
		gluLookAt(3.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0);		
		break;
	case 'l':
		//vista derecha
		glLoadIdentity();
		gluLookAt(-3.0, 0.0,0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0);		
		break;
	case 't':
		tort = true;
		toroide = false;
		tort2 = false;
		break;
	case 'e':
		tort2 = true;         
		toroide = false;
		tort = false;
		break;  
	case 'i':
		toroide = true;
		tort2 = false;            
		tort = false;
	}
	glutPostRedisplay();
}

void reshape(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)height / (GLfloat)height, 1.0, 128.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 1.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}



//dibujar lineas :3 xyz rgb
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(512, 512);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("tecnunLogo");
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(tasten);
	glutMainLoop();
	return 0;
}