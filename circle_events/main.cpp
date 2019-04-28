#include<GL/glew.h>
#include<GL/glut.h>
#include<GLFW/glfw3.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>

#define windowH 900
#define windowW 1600

float PI = atanf(1.0f)*4.0f;

struct Vertices{
	int x;
	int y;
};

Vertices v1;

//Variables for circle drawing
GLfloat circ_pnt = 200;
GLfloat ang, Xaxis, Yaxis;

//Movement variable

//Colors
float black = 0.0f;
float white = 1.0f;
float ballColor = white;

void display(void);
void screen(GLsizei w, GLsizei h);
void keyboard(unsigned char key, int x, int y);
void mouseMovement(int x, int y);
void anim(int value);

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(windowW, windowH);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Circle Events");
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glutFullScreen();
	glutReshapeFunc(screen);
	glutDisplayFunc(display);
	glutKeyboardFunc(&keyboard);
	glutPassiveMotionFunc(mouseMovement);
	glutTimerFunc(100,anim,1);
	glutMainLoop();

	return(0);
}

void anim(int value){
	glutPostRedisplay();
	glutTimerFunc(10,anim,1);
}

void keyboard(unsigned char key, int x, int y){
	switch(key){
		case 'b':
			ballColor = black;
			break;
		case 'w':
			break;
		case 's':
			break;
		case 'o':
			break;
		case 'l':
			break;
	}
}

void mouseMovement(int x, int y){
	v1.x = x-(windowW/2);
	v1.y = y-(windowH/2);
}

void ball(){
	glColor3f(1.0f,1.0,1.0f);
	Xaxis = 30;
	glBegin(GL_POLYGON);
		for(int i=0;i<circ_pnt;i++){
			ang=(2*PI*i)/circ_pnt;
			glVertex2f(cos(ang)*Xaxis,sin(ang)*Xaxis);
		}
	glEnd();
}

void draw_elements(){
	glLoadIdentity();
	glPushMatrix();
	glTranslatef((windowW)/2,(windowH)/2,0);
	glScalef(1,-1,1);
	glPushMatrix();
	glTranslatef(v1.x,v1.y,0);
	ball();
	glPopMatrix();
	glPopMatrix();
}

void display(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(black,black,black,white);
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0,0,windowW, windowH);
	draw_elements();

	glFlush();
}

void screen(GLsizei w, GLsizei h){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, windowW, 0, windowH);
	glMatrixMode(GL_MODELVIEW);

}

