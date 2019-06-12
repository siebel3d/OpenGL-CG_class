#include<GL/glew.h>
#include<GL/glut.h>
#include<GLFW/glfw3.h>
#include<GL/freeglut.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<sstream>
#include<unistd.h>

//Window size
#define windowH 900
#define windowW 1600

float PI = atanf(1.0f)*4.0f;

struct Car{
	int posX;
	int posY;
	int speed;
	int sizeX;
	int sizeY;
};

struct Player{
	int score;
	int playerPosX;
	int playerPosY;
	int sizeX;
	int sizeY;
	int laneFlag;
};

struct Player p1;
struct Player p2;
struct Car c1;
struct Car c2;
struct Car c3;
struct Car c4;
struct Car c5;
struct Car c6;
struct Car c7;
struct Car c8;
struct Car c9;
struct Car c10;

//Variables for circle drawing
GLfloat circ_pnt = 10;
GLfloat ang, ballAxis=10;

//Colors
float black = 0.0f;
float white = 1.0f;

//Variables for game scale
float scaleTV = 1;
int intervalT= 1000/500;

void display(void);
void screen(GLsizei w, GLsizei h);
void keyPressed(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void keyOperations(void);
void mouseMovement(int x, int y);
void update(int value);
void updateBall();
bool* keyStates = new bool[256];

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(windowW, windowH);
	glutInitWindowPosition(0,0);
	glutCreateWindow("OpenGL Free Way");
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glutFullScreen();
	glutReshapeFunc(screen);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
	glutTimerFunc(intervalT, update, 0);
	glutMainLoop();
	return(0);
}

void laneStrip(int posX, int posY, int sizeX, int sizeY, int r, int g, int b){
	glPushMatrix();
		glTranslatef(posX, posY, 0);
		glColor3ub(r,g,b);
		glBegin(GL_QUADS);
			glVertex2f(-(sizeX/4), -(sizeY/16));
			glVertex2f(-(sizeX/4), sizeY/16);
			glVertex2f(sizeX/4, sizeY/16);
			glVertex2f(sizeX/4, -(sizeY/16));
		glEnd();
	glPopMatrix();
}

void laneSection(int sizeX, int sizeY, int laneNum){
	int posY= laneNum*(sizeY-1);
	glPushMatrix();
		glTranslatef(0, posY, 0);
		glColor3ub(80,80,80);
		glBegin(GL_QUADS);
			glVertex2f(-(sizeX/2), -(sizeY/2));
			glVertex2f(-(sizeX/2), sizeY/2);
			glVertex2f(sizeX/2, sizeY/2);
			glVertex2f(sizeX/2, -(sizeY/2));
		glEnd();
		if((laneNum!=5)&&(laneNum!=10)){
			laneStrip((sizeX/4), (sizeY/2)-4, sizeX, sizeY, 255, 255, 255);
		}
		if(laneNum==5){
			laneStrip((sizeX/4), (sizeY/2)-4, sizeX, sizeY, 226, 165, 9);
		}
		
	glPopMatrix();
}

void roadLanes(int sizeX, int sizeY, int totalLanes, int sectionNum){
	int posX=sectionNum*sizeX;
	int auxPos=(totalLanes*sizeY)/2;
	glPushMatrix();
	glTranslatef(posX, -auxPos,0);
		for(int i=1; i<=totalLanes; i++){
			laneSection(sizeX,sizeY,i);
		}
	glPopMatrix();
}

void roadSections(int sizeX, int sizeY, int totalSections){
	int auxPos=(totalSections*sizeX)/2;
	glPushMatrix();
	glTranslatef(-auxPos,0,0);
		for(int i=1; i<=totalSections; i++){
			roadLanes(sizeX,sizeY,10,i);
		}
	glPopMatrix();
}

void map(){
	roadSections(80,65,22);
}

void keyPressed(unsigned char key, int x, int y){
	if(key == 'w') keyStates[key] = true;
	if(key == 's') keyStates[key] = true;
	if(key == 'o') keyStates[key] = true;
	if(key == 'l') keyStates[key] = true;
	switch(key){
		case 27:
			glutDestroyWindow (0);
			exit(0);
			break;
	}
}

void keyUp(unsigned char key, int x, int y){
	if(key == 'w') keyStates[key] = false;
	if(key == 's') keyStates[key] = false;
	if(key == 'o') keyStates[key] = false;
	if(key == 'l') keyStates[key] = false;
}

void keyOperations(void){
	/*if((keyStates['w'])&&((p1.paddlePos<=paddleYlimit+paddleSpeed)&&(p1.paddlePos>=-(paddleYlimit+paddleSpeed)))){
		p1.paddlePos-=paddleSpeed;
	}
	if((keyStates['s'])&&((p1.paddlePos<=paddleYlimit-paddleSpeed)&&(p1.paddlePos<=(paddleYlimit+paddleSpeed)))){
		p1.paddlePos+=paddleSpeed;
	}
	if((keyStates['o'])&&((p2.paddlePos<=paddleYlimit+paddleSpeed)&&(p2.paddlePos>=-(paddleYlimit+paddleSpeed)))){
		p2.paddlePos-=paddleSpeed;
	}
	if((keyStates['l'])&&((p2.paddlePos<=paddleYlimit-paddleSpeed)&&(p2.paddlePos<=(paddleYlimit+paddleSpeed)))){
		p2.paddlePos+=paddleSpeed;
	}*/
}

void drawText(float x, float y, int font, std::string text, int r, int g, int b) {
    glColor3ub(r,g,b);
    glRasterPos2f(x, y);
    if(font==1){
    	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)text.c_str());
    }
    if(font==2){
    	glutBitmapString(GLUT_BITMAP_HELVETICA_12, (const unsigned char*)text.c_str());
    }    
}

std::string int2str(int x){
	std::stringstream ss;
	ss << x;
	return ss.str( );
}

void screenText(){
	drawText(-(windowW/4),-420, 1, int2str(p1.score), 255, 255, 255);
	drawText(windowW/4,-420, 1, int2str(p2.score), 255, 255, 255);
	drawText(-(windowW/2)+200, 420, 2, "S3D", 226,114,9);
}


void updateBall(){
	
}

void update(int value){
	updateBall();
	glutPostRedisplay();
	glutTimerFunc(intervalT, update, 0);
}

void draw_elements(){
	glLoadIdentity();
	glPushMatrix();
		glTranslatef((windowW)/2,(windowH)/2,0);
		glScalef(scaleTV,-scaleTV,scaleTV);
		screenText();
		map();
		if((p1.score==10)||(p2.score==10)){
			glutDestroyWindow(0);
			exit(0);
		}
		glutPostRedisplay();
	glPopMatrix();
}

void display(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	keyOperations();
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