#include<GL/glew.h>
#include<GL/glut.h>
#include<GLFW/glfw3.h>
#include<GL/freeglut.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<sstream>
#include<SOIL/SOIL.h>

#define windowH 900
#define windowW 1600
#define interval 16,666666667

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

//Variables for circle drawing
GLfloat circ_pnt = 200;
GLfloat ang, Xaxis, Yaxis, ballAxis;

//position variables
struct Vertices v1;
struct Vertices v2 = {.x=50, .y=150};

//Paddle X position;
float paddlelX = -(windowW/2)+30;
float paddlerX = (windowW/2)-30;
float paddleYlimit = (windowH/2)-95;
float paddleSpeed = 5;
//Colors
float black = 0.0f;
float white = 1.0f;
float ballColor = white;
float grey = 0.5f;

//Variables for ball colision
float a_value;
float b_value;
float c_value;
bool touch=false;

//Variables for game scale
float scaleTV = 1;
int intervalT=50;

void display(void);
void screen(GLsizei w, GLsizei h);
void keyboard(unsigned char key, int x, int y);
void mouseMovement(int x, int y);
void update(int value);

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
	glutMainLoop();
	glutTimerFunc(intervalT, update, 0);

	return(0);
}

void keyboard(unsigned char key, int x, int y){
	if(key == 'w'&&((p1.paddlePos<=paddleYlimit+paddleSpeed)&&(p1.paddlePos>=-(paddleYlimit+paddleSpeed)))){
		p1.paddlePos-=paddleSpeed;
		printf("paddle pos: %f\n",p1.paddlePos);
		printf("paddle limit + speed: %f\n",paddleYlimit+paddleSpeed);

	} 
	if(key == 's'&&((p1.paddlePos<=paddleYlimit-paddleSpeed)&&(p1.paddlePos<=(paddleYlimit+paddleSpeed)))){
		p1.paddlePos+=paddleSpeed;
		printf("paddle pos: %f\n",p1.paddlePos);
		printf("paddle limit + speed: %f\n",-(paddleYlimit+paddleSpeed));
	} 

	if(key == 'o'&&((p2.paddlePos<=paddleYlimit+paddleSpeed)&&(p2.paddlePos>=-paddleYlimit+paddleSpeed))) p2.paddlePos-=paddleSpeed;
	if(key == 'l'&&((p2.paddlePos<=paddleYlimit+paddleSpeed)&&(p2.paddlePos>=-paddleYlimit+paddleSpeed))) p2.paddlePos+=paddleSpeed;
	
	switch(key){
		case 'b':
			ballColor = black;
			break;
		case 27:
			glutDestroyWindow (0);
			exit(0);
			break;
	}
}

void mouseMovement(int x, int y){
	v1.x = x-(windowW/2);
	v1.y = y-(windowH/2);

	float a_value=v1.x-v2.x;
	float b_value=v1.y-v2.y;
	float c_value=sqrt((a_value*a_value)+(b_value*b_value));

	if(v1.x < paddlelX){
		p1.score+=1;
	}

	if(v1.x > paddlerX){
		p1.score+=1;
	}
}

void update(int value){
	//keyboard();
	glutTimerFunc(intervalT, update, 0);
	glutPostRedisplay();
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

void centerLine(float x, float y){
	glLineWidth(5);
	glColor3f(white,white,white);
	glBegin(GL_LINES);
		glVertex2f(x,-(y-30));
		glVertex2f(x,y);
	glEnd();
}

void ball(){
	glColor3f(ballColor,ballColor,ballColor);
	ballAxis = 30;
	glBegin(GL_POLYGON);
		for(int i=0;i<circ_pnt;i++){
			ang=(2*PI*i)/circ_pnt;
			glVertex2f(cos(ang)*ballAxis,sin(ang)*ballAxis);
		}
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
}

void gameOverScreen(){
	GLuint tex_2d = SOIL_load_OGL_texture
	(
		"tv_mask_bezel.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

		if(0==tex_2d){
		printf("Error: '%s'\n", SOIL_last_result() );
		}
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, tex_2d);
		glBegin(GL_QUADS);
		glTexCoord2f(1,1);	glVertex2f(800,450);
		glTexCoord2f(1,0);	glVertex2f(800,-450);
		glTexCoord2f(0,0);	glVertex2f(-800,-450);
		glTexCoord2f(0,1);	glVertex2f(-800,450);
		glEnd();
		glDisable(GL_TEXTURE_2D);
}

void scoreText(){
	drawText(-22,-420, int2str(p1.score) + " : " + int2str(p2.score));
}

void draw_elements(){
	glLoadIdentity();
	glPushMatrix();
		glTranslatef((windowW)/2,(windowH)/2,0);
		//gameOverScreen();
		glScalef(scaleTV,-(scaleTV),scaleTV);
		scoreText();
		centerLine(0,440);
		glPushMatrix();
			glTranslatef(v1.x,v1.y,0);
			ballColor=white;
			ball();
		glPopMatrix();

		paddle(10,60,paddlelX,p1.paddlePos);
		paddle(10,60,paddlerX,p2.paddlePos);

		if((p1.score==10)||(p2.score==10)){
			gameOverScreen();
			glutDestroyWindow(0);
			exit(0);
		}

		glutPostRedisplay();
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
