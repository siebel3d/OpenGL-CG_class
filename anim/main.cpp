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
float xStep=4;
float yStep=4;

void display(void);
void screen(GLsizei w, GLsizei h);
void keyboard(unsigned char key, int x, int y);
void anim(int value);

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(windowW, windowH);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Animation Test");
	glutFullScreen();
	glutReshapeFunc(screen);
	glutDisplayFunc(display);
	glutKeyboardFunc(&keyboard);
	glutTimerFunc(1500,anim,1);
	glutMainLoop();

	return(0);
}

void anim(int value){
	if ((tx)>(300) || (tx) < (-300)){
		xStep= -xStep;
	}
	if ((ty)>(150) || (ty) < (-150)){
		yStep= -yStep;
	}
	tx += xStep;
	ty += yStep;

	//printf("\n Top %.2f \t Bottom %.2f \t Right %.2f \t Left %.2f",((windowH)/2),(((windowH)/2)*-1),((windowW)/2),(((windowW)/2)*-1));
	//printf("\n Step X %.2f Step Y %.2f", xStep, yStep);
	//printf("\n TX %.2f TY %.2f", tx, ty);

	glutPostRedisplay();
	glutTimerFunc(150,anim,1);
}

void keyboard(unsigned char key, int x, int y){
	printf("\n Key %c", key);
	printf("\n1-Translate X\n2-Translate Y\nEnter: ");
	printf("\nKey %c", key);
	printf("\n Mouse position: %d x %d", x,y);
}

void draw(){
	glLoadIdentity();
	glTranslatef((windowW)/2, (windowH)/2, 0);

	glBegin(GL_TRIANGLES);
		glColor3f(1,0,0);
		glVertex2f(-100, -100);
		glVertex2f(0,0);
		glVertex2f(100,-100);
	glEnd();

	glTranslatef(tx, ty, 0);

	glBegin(GL_QUADS);
		glColor3f(1,1,0);
		glVertex2f(-30,30);
		glVertex2f(-10,30);
		glVertex2f(-10,50);
		glVertex2f(-30,50);
	glEnd();
}

void display(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0,0,1,1);
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0,0, windowW, windowH);
	draw();

	glFlush();
}

void screen(GLsizei w, GLsizei h){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, windowW, 0, windowH);
	glMatrixMode(GL_MODELVIEW);
}
