#include<GL/glew.h>
#include<GL/glut.h>
#include<GLFW/glfw3.h>
#include<GL/freeglut.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sstream>
#include<unistd.h>

//Window size
#define windowH 900
#define windowW 1600

float PI = atanf(1.0f)*4.0f;

struct Car{
	int posX;
	int posY;
	float speed;
	int sizeX;
	int sizeY;
	int laneNum;
};

struct Player{
	int score;
	int playerPosX;
	int playerPosY = windowH/2+170;
	int sizeX;
	int sizeY;
	int laneFlag;
	int r;
	int g;
	int b;

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

//Variables for animation
float stepR = 1.0f;
float stepL = -1.0f;
float chickenStep = 1.0f;
int legRotL = 15;
int legRotR = -15;

//Chicken movement
float chickenSpeed = 1.5;

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
	int posY= (laneNum*sizeY);
	glPushMatrix();
		glTranslatef(0, posY, 0);
		glColor3ub(80,80,80);
		glBegin(GL_QUADS);
			glVertex2f(-(sizeX/2), -(sizeY/2));
			glVertex2f(-(sizeX/2), sizeY/2);
			glVertex2f(sizeX/2, sizeY/2);
			glVertex2f(sizeX/2, -(sizeY/2));
		glEnd();

		if(laneNum==1){
			laneStrip((sizeX/4), sizeY/2, sizeX, sizeY/2, 255, 255, 255);
		}else if(laneNum==10){
			laneStrip((sizeX/4), -(sizeY/2), sizeX, sizeY/2, 255, 255, 255);
		}else if(laneNum==6){
			laneStrip((sizeX/4), -(sizeY/2), sizeX, sizeY/2, 226, 165, 9);
			laneStrip((sizeX/4), sizeY/2, sizeX, sizeY/2, 255, 255, 255);
		}else if(laneNum==7){
			laneStrip((sizeX/4), -(sizeY/2), sizeX, sizeY/2, 255, 255, 255);
			laneStrip((sizeX/4), sizeY/2, sizeX, sizeY/2, 226, 165, 9);
		}else{
			laneStrip((sizeX/4), -(sizeY/2), sizeX, sizeY/2, 255, 255, 255);
			laneStrip((sizeX/4), sizeY/2, sizeX, sizeY/2, 255, 255, 255);
		}		
		
	glPopMatrix();
}

void roadLanes(int sizeX, int sizeY, int totalLanes, int sectionNum){
	int posX=sectionNum*sizeX;
	int auxPos=((totalLanes*sizeY)/2)+sizeY/2;
	glPushMatrix();
		glTranslatef(posX, -auxPos,0);
		for(int i=1; i<=totalLanes; i++){
			laneSection(sizeX,sizeY,i);
		}
	glPopMatrix();
}

void roadSections(int sizeX, int sizeY, int totalLanes, int totalSections){
	int auxPos=(totalSections*sizeX)/2;
	glPushMatrix();
		glTranslatef(-auxPos,0,0);
		for(int i=1; i<=totalSections; i++){
			roadLanes(sizeX,sizeY,totalLanes,i);
		}
	glPopMatrix();
}

void sidewalk(int sizeX, int sizeY, int laneNum, int sectionNum){
	int posX=0, posY=0;
	if(laneNum<0){
		posY= (laneNum*sizeY)-sizeY/3;
	}
	if(laneNum>0){
		posY= (laneNum*sizeY)+sizeY/3;
	}
	posX=sectionNum*sizeX;
	
	glPushMatrix();
		glTranslatef(posX, posY, 0);
		glColor3ub(20,20,20);
		glBegin(GL_QUADS);
			glVertex2f(-(sizeX/2), -sizeY/3);
			glVertex2f(-(sizeX/2), sizeY/3);
			glVertex2f(sizeX/2, sizeY/3);
			glVertex2f(sizeX/2, -sizeY/3);
		glEnd();
		glColor3ub(181,174,157);
		glBegin(GL_QUADS);
			glVertex2f(-(sizeX/2), -((sizeY/3)-sizeY/16));
			glVertex2f(-(sizeX/2), (sizeY/3)-sizeY/16);
			glVertex2f(sizeX/2, (sizeY/3)-sizeY/16);
			glVertex2f(sizeX/2, -((sizeY/3)-sizeY/16));
		glEnd();
	glPopMatrix();
}

void sidewalkSections(int sizeX, int sizeY, int laneNumA, int laneNumB, int totalSections){
	int auxPos=(totalSections*sizeX)/2;
	glPushMatrix();
		glTranslatef(-auxPos,0,0);
		for(int i=1; i<=totalSections; i++){
			sidewalk(sizeX,sizeY,laneNumA,i);
			sidewalk(sizeX,sizeY,laneNumB,i);
		}
	glPopMatrix();
}

void postSidewalk(int sizeY, int laneNumC){
	int posY=0;
	if(laneNumC<0){
		posY= ((laneNumC+1)*sizeY)-sizeY;
	}
	if(laneNumC>0){
		posY= ((laneNumC-1)*sizeY)+sizeY;
	}
	
	glPushMatrix();
		glTranslatef(0, posY, 0);
		glColor3ub(130,130,130);
		glBegin(GL_QUADS);
			glVertex2f(-(windowW/2), -sizeY/2);
			glVertex2f(-(windowW/2), sizeY/3);
			glVertex2f(windowW/2, sizeY/3);
			glVertex2f(windowW/2, -sizeY/2);
		glEnd();
	glPopMatrix();
}

void map(int sizeX, int sizeY, int totalLanes, int totalSections, int laneNumA, int laneNumB, int laneNumC){
	roadSections(sizeX,sizeY,totalLanes,totalSections);
	sidewalkSections(sizeX,sizeY,laneNumA,laneNumB,totalSections);
	postSidewalk(sizeY,laneNumC);
}

void carParts(int sizeX, int sizeY, int posX, int posY, int r, int g, int b){
	glColor3ub(r,g,b);
		glPushMatrix();
		glTranslatef(posX, posY, 0);
		glBegin(GL_QUADS);
			glVertex2f(-sizeX,-sizeY);
			glVertex2f(-sizeX,sizeY);
			glVertex2f(sizeX,sizeY);
			glVertex2f(sizeX,-sizeY);
		glEnd();
		glPopMatrix();
}

void carComplete(int sizeX, int sizeY, int r, int g, int b){
	glPushMatrix();
		glColor3ub(r,g,b);
		//body
		glBegin(GL_QUADS);
			glVertex2f(-(sizeX/2), -(sizeY/2));
			glVertex2f(-(sizeX/2), sizeY/2);
			glVertex2f(sizeX/2, sizeY/2);
			glVertex2f(sizeX/2, -(sizeY/2));
		glEnd();
		glBegin(GL_QUADS);
			glVertex2f(sizeX/2,-(sizeY/3));
			glVertex2f(sizeX/2,sizeY/3);
			glVertex2f(sizeX/2+sizeX/8,sizeY/3);
			glVertex2f(sizeX/2+sizeX/8,-sizeY/3);
		glEnd();
		//windows
		carParts(sizeX/8,sizeY/4,20,0,130,130,255);		//windshield
		carParts(sizeX/10,sizeY/4,-20,0,130,130,255);	//rear window
		carParts(sizeX/7,sizeY/14,-1,14,130,130,255);	//right window
		carParts(sizeX/7,sizeY/14,-1,-14,130,130,255);	//left window
		//Wheels
		carParts(sizeX/8,sizeY/15,27,25,20,20,20);
		carParts(sizeX/8,sizeY/15,27,-25,20,20,20);
		carParts(sizeX/8,sizeY/15,-27,25,20,20,20);
		carParts(sizeX/8,sizeY/15,-27,-25,20,20,20);
		//Collision Debug
		glColor3ub(255,0,0);
		glBegin(GL_QUADS);
			glVertex2f(-(sizeX/2), -(sizeY/2));
			glVertex2f(-(sizeX/2), sizeY/2);
			glVertex2f(sizeX/2+sizeX/8, sizeY/2);
			glVertex2f(sizeX/2+sizeX/8, -(sizeY/2));
		glEnd();


	glPopMatrix();
}

void carController(int sizeX, int sizeY, int laneSize, float speed, const char* carNumber){
	int rLimit = (windowW/2)+(sizeX*2);
	int lLimit = -rLimit;

	if(strcmp(carNumber,"c1")==0){
		c1.sizeX = sizeX;
		c1.sizeY = sizeY;
		c1.speed = speed;
		c1.posY = (5*laneSize)-(laneSize/2);

		glPushMatrix();
		if(c1.posX==rLimit)
			c1.posX=lLimit;
		glTranslatef(c1.posX,c1.posY,0);
		carComplete(sizeX, sizeY, 255, 50, 50);
		glPopMatrix();
	}

	if(strcmp(carNumber,"c2")==0){
		c2.sizeX = sizeX;
		c2.sizeY = sizeY;
		c2.speed = speed;
		c2.posY = (4*laneSize)-(laneSize/2);

		glPushMatrix();
		if(c2.posX==rLimit)
			c2.posX=lLimit;
		glTranslatef(c2.posX,c2.posY,0);
		carComplete(sizeX, sizeY, 244, 206, 66);
		glPopMatrix();
	}

	if(strcmp(carNumber,"c3")==0){
		c3.sizeX = sizeX;
		c3.sizeY = sizeY;
		c3.speed = speed;
		c3.posY = (3*laneSize)-(laneSize/2);

		glPushMatrix();
		if(c3.posX==rLimit)
			c3.posX=lLimit;
		glTranslatef(c3.posX,c3.posY,0);
		carComplete(sizeX, sizeY, 66, 244, 80);
		glPopMatrix();
	}

	if(strcmp(carNumber,"c4")==0){
		c4.sizeX = sizeX;
		c4.sizeY = sizeY;
		c4.speed = speed;
		c4.posY = (2*laneSize)-(laneSize/2);

		glPushMatrix();
		if(c4.posX==rLimit)
			c4.posX=lLimit;
		glTranslatef(c4.posX,c4.posY,0);
		carComplete(sizeX, sizeY, 66, 244, 134);
		glPopMatrix();
	}

	if(strcmp(carNumber,"c5")==0){
		c5.sizeX = sizeX;
		c5.sizeY = sizeY;
		c5.speed = speed;
		c5.posY = (1*laneSize)-(laneSize/2);

		glPushMatrix();
		if(c5.posX==rLimit)
			c5.posX=lLimit;
		glTranslatef(c5.posX,c5.posY,0);
		carComplete(sizeX, sizeY, 150, 66, 190);
		glPopMatrix();
	}

	if(strcmp(carNumber,"c6")==0){
		c6.sizeX = sizeX;
		c6.sizeY = sizeY;
		c6.speed = speed;
		c6.posY = (0*laneSize)-(laneSize/2);

		glPushMatrix();
		glScalef(-1,1,1);
		if(c6.posX==lLimit)
			c6.posX=rLimit;
		glTranslatef(-c6.posX,c6.posY,0);
		carComplete(sizeX, sizeY, 244, 149, 66);
		glPopMatrix();
	}

	if(strcmp(carNumber,"c7")==0){
		c7.sizeX = sizeX;
		c7.sizeY = sizeY;
		c7.speed = speed;
		c7.posY = ((-1)*laneSize)-(laneSize/2);

		glPushMatrix();
		glScalef(-1,1,1);
		if(c7.posX==lLimit)
			c7.posX=rLimit;
		glTranslatef(-c7.posX,c7.posY,0);
		carComplete(sizeX, sizeY, 255, 130, 255);
		glPopMatrix();
	}

	if(strcmp(carNumber,"c8")==0){
		c8.sizeX = sizeX;
		c8.sizeY = sizeY;
		c8.speed = speed;
		c8.posY = ((-2)*laneSize)-(laneSize/2);

		glPushMatrix();
		glScalef(-1,1,1);
		if(c8.posX==lLimit)
			c8.posX=rLimit;
		glTranslatef(-c8.posX,c8.posY,0);
		carComplete(sizeX, sizeY, 130, 255, 255);
		glPopMatrix();
	}

	if(strcmp(carNumber,"c9")==0){
		c9.sizeX = sizeX;
		c9.sizeY = sizeY;
		c9.speed = speed;
		c9.posY = ((-3)*laneSize)-(laneSize/2);

		glPushMatrix();
		glScalef(-1,1,1);
		if(c9.posX==lLimit)
			c9.posX=rLimit;
		glTranslatef(-c9.posX,c9.posY,0);
		carComplete(sizeX, sizeY, 80, 100, 100);
		glPopMatrix();
	}

	if(strcmp(carNumber,"c10")==0){
		c10.sizeX = sizeX;
		c10.sizeY = sizeY;
		c10.speed = speed;
		c10.posY = ((-4)*laneSize)-(laneSize/2);

		glPushMatrix();
		glScalef(-1,1,1);
		if(c10.posX==lLimit)
			c10.posX=rLimit;
		glTranslatef(-c10.posX,c10.posY,0);
		carComplete(sizeX, sizeY, 130, 130, 130);
		glPopMatrix();
	}

}

void chickenHead(int size){
	glPushMatrix();
	glTranslatef(10,-20,0);
	glBegin(GL_POLYGON);
		glVertex2f(-size/8, -size/4);
		glVertex2f(-size/8, size/4);
		glVertex2f(size/8, size/4);
		glVertex2f(size/8, -size/4);
	glEnd();
	glPushMatrix();
	glTranslatef(10,0,0);
	glColor3ub(255,132,10);
	glBegin(GL_POLYGON);
		glVertex2f(-size/8, -size/8);
		glVertex2f(-size/8, size/8);
		glVertex2f(size/8, 0);
	glEnd();
	glPushMatrix();
	glColor3ub(10,10,10);
	glPointSize(5.0f);
	glTranslatef(-7,-2,0);
	glBegin(GL_POINTS);
		glVertex2f(0,0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void chickenLegs(int size, int angle, float offset){
	glColor3ub(10,10,10);
	glPushMatrix();
	glTranslatef(offset,15,0);
	glRotatef(angle,0,0,1);
	glLineWidth(3.0f);
	glBegin(GL_LINES);
		glVertex2f(0,0);
		glVertex2f(0,15);
	glEnd();
	glPopMatrix();
}

void chicken(int scale, int size, float movX, float movY){
	glPushMatrix();
	glScalef(0.6,0.6,0.6);
	glTranslatef(movX,movY,0);
	glColor3ub(244,223,66);
	glPushMatrix();
	glScalef(scale,scale,scale);
	glBegin(GL_POLYGON);
		glVertex2f(-size/3, 0);
		glVertex2f(-size/3, size/3);
		glVertex2f(size/3, size/3);
		glVertex2f(size/3, -size/3);
		glVertex2f(-size/1.5, -size/3);
	glEnd();

	chickenHead(size);
	chickenLegs(size,legRotL, -5);
	chickenLegs(size,legRotR, 5);

	//Chicken Collision Debug
	glColor3ub(255,0,0);
	glBegin(GL_QUADS);
		glVertex2f(-size/2, -size/1.7);
		glVertex2f(-size/2, size/1.7);
		glVertex2f(size/2, size/1.7);
		glVertex2f(size/2, -size/1.7);
	glEnd();

	glPopMatrix();
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
	if(keyStates['w']){
		p1.playerPosY-=chickenSpeed;
	}
	if(keyStates['s']){
		p1.playerPosY+=chickenSpeed;
	}

	if(keyStates['o']){
		p2.playerPosY-=chickenSpeed;
	}
	if(keyStates['l']){
		p2.playerPosY+=chickenSpeed;
	}
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
	drawText(-(windowW/4),-420, 1, int2str(p1.score), 255, 130, 130);
	drawText(windowW/4,-420, 1, int2str(p2.score), 255, 130, 130);
	drawText(-(windowW/2)+200, 420, 2, "SIEBEL3D", 226,114,9);
}


void updateCars(){
	c1.posX += stepR*c1.speed;
	c2.posX += stepR*c2.speed;
	c3.posX += stepR*c3.speed;
	c4.posX += stepR*c4.speed;
	c5.posX += stepR*c5.speed;
	c6.posX += stepL*c6.speed;
	c7.posX += stepL*c7.speed;
	c8.posX += stepL*c8.speed;
	c9.posX += stepL*c9.speed;
	c10.posX += stepL*c10.speed;
}

void updateChicken(){
	if(p1.playerPosY==-windowH/2-170){
		p1.playerPosY=windowH/2+170;
		p1.score++;
	}

	if(p2.playerPosY==-windowH/2-170){
		p2.playerPosY=windowH/2+170;
		p2.score++;
	}
}

void update(int value){
	updateCars();
	updateChicken();
	glutPostRedisplay();
	glutTimerFunc(intervalT, update, 1);
}

void draw_elements(){
	p1.playerPosX = -windowW/2;
	p2.playerPosX = windowW/2;

	glLoadIdentity();
	glPushMatrix();
		glTranslatef((windowW)/2,(windowH)/2,0);
		glScalef(scaleTV,-scaleTV,scaleTV);
		map(80,70,10,22,5,-5,-6);
		screenText();
		//chicken(1, 50, p1.playerPosX, p1.playerPosY);
		chicken(1,50,p1.playerPosX, 280);
		chicken(1, 50, p2.playerPosX, p2.playerPosY);
		carController(80,45,70,1,"c1");
		carController(80,45,70,2,"c2");
		carController(80,45,70,3,"c3");
		carController(80,45,70,4,"c4");
		carController(80,45,70,5,"c5");
		carController(80,45,70,5,"c6");
		carController(80,45,70,4,"c7");
		carController(80,45,70,3,"c8");
		carController(80,45,70,2,"c9");
		carController(80,45,70,1,"c10");
		glColor3ub(255,0,0);
		//Center line debug
		glBegin(GL_LINES);
    		glVertex2f(-windowW/2,0);
    		glVertex2f(windowW/2,0);
		glEnd();

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
	glClearColor(0.0f,0.0f,0.0f,1.0f);
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
