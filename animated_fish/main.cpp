#include<GL/glew.h>
#include<GL/glut.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>

#define windowH 400
#define windowW 600

//translation variables
float tx=0.0;
float ty=0.0;

//variables incrementation
float xStep=1;
float yStep=0.25;

float PI = atanf(1.0f)*4.0f;

void display(void);
void screen(GLsizei w, GLsizei h);
void keyboard(unsigned char key, int x, int y);
void anim(int value);

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(windowW, windowH);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Animation Test");

	glutReshapeFunc(screen);
	glutDisplayFunc(display);
	glutKeyboardFunc(&keyboard);
	glutTimerFunc(150,anim,1);
	glutMainLoop();

	return(0);
}

void anim(int value){
	if ((tx)>(70) || (tx) < (-70)){
		xStep= -xStep;
	}
	if ((ty)>(10) || (ty) < (-10)){
		yStep= -yStep;
	}
	tx += xStep;
	ty += yStep;

	printf("\n Top %.2f \t Bottom %.2f \t Right %.2f \t Left %.2f",((windowH)/2),(((windowH)/2)*-1),((windowW)/2),(((windowW)/2)*-1));
	printf("\n Step X %.2f Step Y %.2f", xStep, yStep);
	printf("\n TX %.2f TY %.2f", tx, ty);

	glutPostRedisplay();
	glutTimerFunc(40,anim,1);
}

void keyboard(unsigned char key, int x, int y){
	printf("\n Key %c", key);
	printf("\n1-Translate X\n2-Translate Y\nEnter: ");
	printf("\n Step X %.2f Step Y %.2f", xStep, yStep);
	printf("\nKey %c", key);
	printf("\n Mouse position: %d x %d", x,y);

	switch(key){
		case'1':
			glColor3ub(252,146,47);
			break;
		case'2':
			glColor3ub(100,100,255);
			break;
		case'3':
			glColor3ub(100,255,100);
			break;
	}
}

void fish(){
	glPushMatrix();
	if(xStep==1){
		glScaled(1,1,1);		
	}

	if(xStep==-1){
		glScaled(-1,1,1);
	}
	
	glColor3ub(252,146,47);
	//upper part
	glBegin(GL_POLYGON);
		glVertex2f(5, 5);
		glColor3ub(252,146,47);
		glVertex2f(10, 7.5);		
		glVertex2f(15, 8);
		glColor3ub(255,255,255);
		glVertex2f(14, 11);
		glVertex2f(9, 9);
	glEnd();
	//lower part
	glColor3ub(252,146,47);
	glBegin(GL_POLYGON);
		glVertex2f(15, -8);
		glColor3ub(255,255,255);
		glVertex2f(13, -9.5);
		glVertex2f(9, -9);
		glColor3ub(252,146,47);
		glVertex2f(10, -7.5);
	glEnd();
	//tail
	glBegin(GL_POLYGON);
		glColor3ub(255,255,255);
		glVertex2f(0, 0);
		glColor3ub(252,146,47);
		glVertex2f(-10, 10);
		glVertex2f(-5, 0);
		glVertex2f(-10, -10);
	glEnd();
	//body
	glBegin(GL_POLYGON);
		glColor3ub(255,255,255);
		glVertex2f(0, 0);
		glColor3ub(252,146,47);
		glVertex2f(5, 5);
		glVertex2f(10, 7.5);
		glVertex2f(15, 8);
		glVertex2f(20, 6);
		glVertex2f(23, 3);
		glVertex2f(24, 0);
		glVertex2f(23, -3);
		glVertex2f(20, -6);
		glVertex2f(15, -8);
		glVertex2f(10, -7.5);
		glVertex2f(5, -5);
	glEnd();
	glPopMatrix();
}

void aquarium(){
	GLfloat circ_pnt = 500;
	GLfloat ang, raioX = 100.0f, raioY = 80.0f;

	glLineWidth(3.0);
	glColor3ub(60,60,100);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < circ_pnt; i++) {
		if(i<=250){
			raioY=90;
		}else if(i>250){
			raioY=70;
		}

		ang = (2 * PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);
		printf("%f		%f\n", cos(ang) * raioX, sin(ang) * raioY);
	}
	glEnd();

	glColor4ub(70,70,255, 0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		if(i<=250){
			raioY=90;
		}else if(i>250){
			raioY=70;
		}

		ang = (2 * PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);
		printf("%f		%f\n", cos(ang) * raioX, sin(ang) * raioY);
	}
	glEnd();

	glPushMatrix();
	glTranslatef(0,82,0);
	raioX=30;
	raioY=10;

	glColor3ub(60,60,100);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);
		printf("%f		%f\n", cos(ang) * raioX, sin(ang) * raioY);
	}
	glEnd();

	glColor4ub(70,70,255, 0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);
		printf("%f		%f\n", cos(ang) * raioX, sin(ang) * raioY);
	}
	glEnd();

	glPopMatrix();


}

void draw_elements(){
	glLoadIdentity();
	glPushMatrix();	
	//Unanimated
	glTranslatef((windowW)/2, (windowH)/2, 0);
	glScaled(2,2,2);
	aquarium();

	//Animated
	glTranslatef(tx, ty, 0);
	fish();
	glPopMatrix();
}

void display(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(255,255,255,1);
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0,0, windowW, windowH);
	draw_elements();

	glFlush();
}

void screen(GLsizei w, GLsizei h){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, windowW, 0, windowH);
	glMatrixMode(GL_MODELVIEW);
}
