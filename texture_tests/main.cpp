#include<GL/glew.h>
#include<GL/glut.h>
#include<GLFW/glfw3.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<SOIL/SOIL.h>

#define windowH 900
#define windowW 1600

float PI = atanf(1.0f)*4.0f;

struct Vertices{
	int x;
	int y;
};

//Variables for circle drawing
GLfloat circ_pnt = 200;
GLfloat ang, Xaxis, Yaxis, ballAxis;

//position variables
struct Vertices v1;
struct Vertices v2 = {.x=50, .y=150};

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


void display(void);
void screen(GLsizei w, GLsizei h);
void keyboard(unsigned char key, int x, int y);
void mouseMovement(int x, int y);

int main(int argc, char** argv){
	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
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

	return(0);
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

	if(c_value < (ballAxis*2)){
		touch=true;
		glEnable(GL_TEXTURE_2D);
	}else{
		touch=false;
		glDisable(GL_TEXTURE_2D);
	}

	printf("\nX: %i", v1.x);
	printf("\nY: %i", v1.y);
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

void gameOverScreen(){
	GLuint tex_2d = SOIL_load_OGL_texture
	(
		"src/jequiti.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	if( 0 == tex_2d ){
	printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
	}

	glBindTexture(GL_TEXTURE_2D, tex_2d);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f,0.0f);        glVertex2f(20, 10);
	glTexCoord2f(1.0f,1.0f);        glVertex2f(20, -10);
	glTexCoord2f(0.0f,1.0f);        glVertex2f(-20, -10);
	glTexCoord2f(0.0f,0.0f);        glVertex2f(-20, 10);
	glEnd();
}

void draw_elements(){
	glLoadIdentity();
	glPushMatrix();
	glTranslatef((windowW)/2,(windowH)/2,0);
	glScalef(1,-1,1);
	glPushMatrix();
	glTranslatef(v2.x,v2.y,0);
	ballColor=grey;
	ball();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(v1.x,v1.y,0);
	ballColor=white;
	ball();
	glPopMatrix();

	if(touch==true){
		gameOverScreen();
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

	glutSwapBuffers();
}

void screen(GLsizei w, GLsizei h){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, windowW, 0, windowH);
	glMatrixMode(GL_MODELVIEW);

}
