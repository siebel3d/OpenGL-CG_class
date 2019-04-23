#include<GL/glew.h>
#include<GL/glut.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>

#define windowH 900
#define windowW 1600

//Scales
float fScale = 3.5;
float sScale = 1;

//translation variables
float tx=0.0;
float ty=0.0;

//variables incrementation
float xStep=1;
float yStep=0.25;

//PI value
float PI = atanf(1.0f)*4.0f;

//Primary variable colors
float cr = 70;
float cg = 96;
float cb = 72;
//Secondary variable colors
float cr2 = 253;
float cg2 = 196;
float cb2 = 255;

//
GLfloat circ_pnt = 500;
GLfloat ang, raioX, raioY;

void display(void);
void screen(GLsizei w, GLsizei h);
void keyboard(unsigned char key, int x, int y);
void anim(int value);

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(windowW, windowH);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Animated Fish");
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_BLEND );

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

	printf("\n Top %i \t Bottom %i \t Right %i \t Left %i",((windowH)/2),(((windowH)/2)*-1),((windowW)/2),(((windowW)/2)*-1));
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
		case '1':
			cr = 252;
			cg = 146;
			cb = 41;

			cr2 = 255;
			cg2 = 255;
			cb2 = 255;
			break;
		case '2':
			cr = 66;
			cg = 244;
			cb = 203;

			cr2 = 244;
			cg2 = 66;
			cb2 = 66;
			break;
		case '3':
			cr = 244;
			cg = 217;
			cb = 66;

			cr2 = 70;
			cg2 = 96;
			cb2 = 72;
			break;
		case '4':
			cr = 70;
			cg = 96;
			cb = 72;

			cr2 = 253;
			cg2 = 196;
			cb2 = 255;
			break;
		case 'c':
			xStep = -xStep;
			break;
	}
}

void fish(){
	glPushMatrix();
	if(xStep==1){
		glScaled(sScale,sScale,sScale);
	}

	if(xStep==-1){
		glScaled(-(sScale),sScale,sScale);
	}

	glColor3ub(cr,cg,cb);
	//upper part
	glBegin(GL_POLYGON);
		glVertex2f(5, 5);
		glColor3ub(cr,cg,cb);
		glVertex2f(10, 7.5);
		glVertex2f(15, 8);
		glColor3ub(cr2,cg2,cb2);
		glVertex2f(14, 11);
		glVertex2f(9, 9);
	glEnd();
	//lower part
	glColor3ub(cr,cg,cb);
	glBegin(GL_POLYGON);
		glVertex2f(15, -8);
		glColor3ub(cr2,cg2,cb2);
		glVertex2f(13, -9.5);
		glVertex2f(9, -9);
		glColor3ub(cr,cg,cb);
		glVertex2f(10, -7.5);
	glEnd();
	//tail
	glBegin(GL_POLYGON);
		glColor3ub(cr2,cg2,cb2);
		glVertex2f(0, 0);
		glColor3ub(cr,cg,cb);
		glVertex2f(-10, 10);
		glVertex2f(-5, 0);
		glVertex2f(-10, -10);
	glEnd();
	//body
	glBegin(GL_POLYGON);
		glColor3ub(cr2,cg2,cb2);
		glVertex2f(0, 0);
		glColor3ub(cr,cg,cb);
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
	//Eyes
	raioX=1.2f;
	raioY=2.5;
	glPushMatrix();
	glTranslatef(20,0,0);
	glBegin(GL_POLYGON);
		glColor3ub(100,142,99);
		for(int i=0;i<100; i++){
			ang=(2*PI*i)/100;
			glVertex2f(cos(ang)*raioY,sin(ang)*raioY);
		}
	glEnd();
	glBegin(GL_POLYGON);
		glColor3ub(90,50,50);
		for(int i=0;i<100; i++){
			ang=(2*PI*i)/100;
			glVertex2f(cos(ang)*raioX,sin(ang)*raioX);
		}
	glEnd();
	glPopMatrix();
	glPopMatrix();
}

void aquarium(){
	raioX=100;
	raioY=80;

	glLineWidth(4.0);
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

	glColor4ub(70,120,185,100);
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
	glTranslatef(0,80,0);
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

	glColor4ub(220,220,220,130);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);
		printf("%f		%f\n", cos(ang) * raioX, sin(ang) * raioY);
	}
	glEnd();

	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,-70,0);
	glBegin(GL_QUADS);
		glColor3ub(96,48,36);
		glVertex2f(-230,0);
		glVertex2f(230,0);
		glColor3ub(86,38,26);
		glVertex2f(230,-15);
		glVertex2f(-230,-15);
	glEnd();
	glBegin(GL_QUADS);
		glColor3ub(76,28,16);
		glVertex2f(-220,-15);
		glVertex2f(220,-15);
		glColor3ub(66,18,12);
		glVertex2f(220,-45);
		glVertex2f(-220,-45);
	glEnd();
	glBegin(GL_QUADS);
		glColor3ub(56,8,6);
		glVertex2f(-190,-45);
		glVertex2f(-215,-45);
		glVertex2f(-215,-60);
		glVertex2f(-190,-60);
	glEnd();
	glBegin(GL_QUADS);
		glVertex2f(190,-45);
		glVertex2f(215,-45);
		glVertex2f(215,-60);
		glVertex2f(190,-60);
	glEnd();
	glPopMatrix();
}

void draw_elements(){
	glLoadIdentity();
	glPushMatrix();
	glTranslatef((windowW)/2, (windowH)/2,0);
	glScalef(fScale,fScale,fScale);

	//Animated
	glPushMatrix();
	glTranslatef(tx, ty, 0);
	fish();
	glPopMatrix();
	//Unanimated
	aquarium();
	glPopMatrix();
}

void display(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0.97,1,0.62,1);
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
