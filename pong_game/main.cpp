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

struct Vertices{
	int x;
	int y;
};

struct Player{
	int score;
	float paddlePos;
};

struct Player p1;
struct Player p2;
struct Vertices v1;

//Variables for circle drawing
GLfloat circ_pnt = 10;
GLfloat ang, ballAxis=10;

//Paddle variables;
float paddleXsize;
float paddleYsize;
float paddlelX = -(windowW/2)+30;
float paddlerX = (windowW/2)-30;
float paddleYlimit = (windowH/2)-95;
float paddleSpeed = 1.5;

//Colors
float black = 0.0f;
float white = 1.0f;
float ballColor = white;

//Variables for ball colision
float ballXDir=-1.0f;
float ballYDir=0.0f;
float ballSpeed=2;

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
	glutCreateWindow("Circle Events");
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

void keyPressed(unsigned char key, int x, int y){
	if(key == 'w') keyStates[key] = true;
	if(key == 's') keyStates[key] = true;
	if(key == 'o') keyStates[key] = true;
	if(key == 'l') keyStates[key] = true;
	if(key == 'z') keyStates[key] = true;
	if(key == 'q') keyStates[key] = true;	
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
	if(key == 'z') keyStates[key] = false;
	if(key == 'q') keyStates[key] = false;
}

void keyOperations(void){
	if((keyStates['w'])&&((p1.paddlePos<=paddleYlimit+paddleSpeed)&&(p1.paddlePos>=-(paddleYlimit+paddleSpeed)))){
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
	}
	if(keyStates['z']){
		ballColor=black;
	}
	if(keyStates['q']){
		p1.paddlePos = v1.y;
	}
}

void drawText(float x, float y, std::string text) {
    glRasterPos2f(x, y);
    glColor3f(white,white,white);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)text.c_str());
}

std::string int2str(int x){
	std::stringstream ss;
	ss << x;
	return ss.str( );
}

void scoreText(){
	drawText(-22,-420, int2str(p1.score) + " : " + int2str(p2.score));
}

void centerLine(float x, float y){
	glLineWidth(5);
	glColor3f(white,white,white);
	glBegin(GL_LINES);
		glVertex2f(x,-(y-30));
		glVertex2f(x,y);
	glEnd();
}

void paddle(float x, float y, float trans, float pos){
	glColor3f(white,white,white);
	glBegin(GL_QUADS);
		glVertex2f(-x+trans,y+pos);
		glVertex2f(x+trans,y+pos);
		glVertex2f(x+trans,-y+pos);
		glVertex2f(-x+trans,-y+pos);
	glEnd();
	paddleXsize = x;
	paddleYsize = y;
}

void ball(){
	glColor3f(ballColor,ballColor,ballColor);
	glBegin(GL_POLYGON);
		for(int i=0;i<circ_pnt;i++){
			ang=(2*PI*i)/circ_pnt;
			glVertex2f(cos(ang)*ballAxis,sin(ang)*ballAxis);
		}
	glEnd();
}

void updateBall(){
	v1.x += ballXDir * ballSpeed;
	v1.y += ballYDir * ballSpeed;

	if(ballYDir < 0.5f && ballYDir > -0.5f){
		ballYDir = (rand() % 10 + 5)/10;
	}

	if(v1.x == paddlelX+paddleXsize+ballAxis && v1.y >= p1.paddlePos - paddleYsize && v1.y <= p1.paddlePos + paddleYsize){
		ballXDir*=-1;
		printf("\a\n");
		if(v1.y < p1.paddlePos && v1.y < p1.paddlePos-paddleYsize){
			ballYDir = (rand() % 10 + 5)/10;
		}
		if (v1.y > p1.paddlePos && v1.y > p1.paddlePos+paddleYsize){
			ballYDir = -((rand() % 10 + 5)/10);
		}

		
	}

	if(v1.x == paddlerX-paddleXsize-ballAxis && v1.y >= p2.paddlePos - paddleYsize && v1.y <= p2.paddlePos + paddleYsize){
		ballXDir*=-1;
		printf("\a\n");
		if(v1.y < p2.paddlePos && v1.y < p2.paddlePos-paddleYsize){
			ballYDir = (rand() % 10 + 5)/10;
		}
		if (v1.y > p2.paddlePos && v1.y > p2.paddlePos+paddleYsize){
			ballYDir = -((rand() % 10 + 5)/10);
		}
	}

	if(v1.y > windowH/2-ballAxis){
		ballYDir = ballYDir*(-1);
		printf("\a\n");
	}

	if(v1.y < -(windowH/2-ballAxis)){
		ballYDir = ballYDir*(-1);
		printf("\a\n");
	}

	if (v1.x < -(windowW/2-ballAxis)){
		p2.score+=1;
		v1.x = 0;
		v1.y = 0;
		usleep(200000);
		ballXDir = ballXDir*(-1);
		ballColor=white;
	}

	if (v1.x > windowW/2-ballAxis){
		p1.score+=1;
		v1.x = 0;
		v1.y = 0;
		usleep(200000);
		ballXDir = ballXDir*(-1);
		ballColor=white;
	}
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
		glScalef(scaleTV,-(scaleTV),scaleTV);
		scoreText();
		centerLine(0,440);
		glPushMatrix();
			glTranslatef(v1.x,v1.y,0);
			ball();
		glPopMatrix();
		paddle(10,60,paddlelX,p1.paddlePos);
		paddle(10,60,paddlerX,p2.paddlePos);

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