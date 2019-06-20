#include <iostream>
#include <GL/glut.h>
using namespace std;

int cx=0, cy=0, cz=0;
int cn;

struct Quads{
	int x1,y1,z1;
	int x2,y2,z2;
	int x3,y3,z3;
	int x4,y4,z4;
	int r,g,b;
	int state;
	int total;
};
Quads Q[100];

void addQuad(){
	Q[0].state++;
	if(Q[0].state>4) Q[0].state=1;
	int st=Q[0].state;

	if(st==1){
		Q[0].total++;
		cn=Q[0].total;
	}

	if(st==1){
		Q[cn].x1=cx;
		Q[cn].y1=cy;
		Q[cn].z1=cz;
	}

	if(st==1||st==2){
		Q[cn].x2=cx;
		Q[cn].y2=cy;
		Q[cn].z2=cz;
	}

	if(st==1||st==2||st==3){
		Q[cn].x3=cx;
		Q[cn].y3=cy;
		Q[cn].z3=cz;
	}

	if(st==1||st==2||st==3||st==4){
		Q[cn].x4=cx;
		Q[cn].y4=cy;
		Q[cn].z4=cz;
	}
}

void drawQuads(){
	int i;
	for(i=0;i<Q[0].total+1;i++){
		glColor3ub(Q[i].r,Q[i].g,Q[i].b);
		glBegin(GL_QUADS);
			glVertex3f(Q[i].x1,Q[i].y1,Q[i].z1);
			glVertex3f(Q[i].x2,Q[i].y2,Q[i].z2);
			glVertex3f(Q[i].x3,Q[i].y3,Q[i].z3);
			glVertex3f(Q[i].x4,Q[i].y4,Q[i].z4);
		glEnd();
	}
}

void theCube(float x, int r, int g, int b){
	glPushMatrix();
		glColor3ub(r,g,b);
		glTranslatef(cx,cy,cz);
		glutSolidCube(x);
	glPopMatrix();
}

void drawGrid(){
	int i;
	for(i=0;i<40;i++){
		glPushMatrix();
		if(i<20){
			 glTranslatef(0,0,i);
		}
		if(i>=20){
			 glTranslatef(i-20,0,0); 
			 glRotatef(-90,0,1,0);
		}
		glColor3ub(255,255,255);
		glLineWidth(1);
		glBegin(GL_LINES);
			glVertex3f(0,-0.1,0);
			glVertex3f(19,-0.1,0);
		glEnd();
		glPopMatrix();
	}
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(-13,0,-45);
	glRotatef(40,1,1,0);
	drawGrid();
	drawQuads();
	theCube(0.4, 255, 130, 90);
	glutSwapBuffers();
}

void init(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(35,1.0f,0.1f,1000);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1f,0.1f,0.1f,1.0f);
}

void keyboard(unsigned char key, int x, int y){
	if(key=='w') cz+=1;
	if(key=='s') cz-=1;

	if(key=='d') cx+=1;
	if(key=='a') cx-=1;

	if(key=='q') cy+=1;
	if(key=='z') cy-=1;

	if(key==32) addQuad();

	if(key=='c'){
		Q[cn].r = rand() % 255;
		Q[cn].g = rand() % 255;
		Q[cn].b = rand() % 255;
	}
	glutPostRedisplay();
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(800,600);
	glutCreateWindow("Test Window");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	init();
	glutMainLoop();
	return 0;
}

