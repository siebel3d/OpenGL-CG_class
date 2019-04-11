#include<stdio.h>
#include<stdlib.h>
#include<GL/glew.h>
#include<GL/glu.h>
#include<GL/gl.h>
#include<GL/glut.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<math.h>

#define PI 3.14159
#define width 600
#define height 400

int windowW=600;
int windowH=400;

void display(void);
void tela(GLsizei w, GLsizei h);

int main(int argc, char** argv){
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(windowW, windowH);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Teste OpenGL");

	glutReshapeFunc(tela);
	glutDisplayFunc(display);
	glutMainLoop();

	return(0);
}

void draw(){
	GLfloat circ_pnt = 100;
	GLfloat ang, raioX=80.0f, raioY=80.0f;

	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
	for(int i=0; i<circ_pnt; i++){
		ang=(2*PI*i)/circ_pnt;
		glVertex2f(cos(ang)*raioX, sin(ang)*raioY);
		printf("%f   %f\n", cos(ang)*raioX, sin(ang)*raioY);
	}
	glEnd();

	glPushMatrix();
	glTranslatef(150, 0, 0);

	glColor3f(0, 1, 0);
	glBegin(GL_QUADS);
		glVertex3f(40, 40, 0);
		glVertex3f(-40, 40, 0);
		glVertex3f(-40, -40, 0);
		glVertex3f(40, -40, 0);
	glEnd();

	glPopMatrix();

	glColor3f(255, 255, 0);
	glBegin(GL_QUADS);
		glVertex3f(20, 20, 0);
		glVertex3f(-20, 20, 0);
		glVertex3f(-20, -20, 0);
		glVertex3f(20, -20, 0);
	glEnd();
}

void display(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0,0,1,1);
	glClear(GL_COLOR_BUFFER_BIT);

	glTranslatef(windowW/2, windowH/2, 0);

	glViewport(0,0,windowW, windowH);
	draw();

	glFlush();
}

void tela(GLsizei w, GLsizei h){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, windowW, 0, windowH);

	glMatrixMode(GL_MODELVIEW);
}