#include<GL/glew.h>
#include<GL/glut.h>
#include<math.h>

#define PI 3.1315926535898
#define winH 600
#define winW 600

GLfloat circ_pnt=400, ang, raioX, raioY;

void display(void);
void tela(GLsizei w, GLsizei h);

int main(int argc, char** argv){
	glutInit(&argc, argv);  // controla se o sistema operacional tem suporte a janelas.

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // quantidade de buffer de cores e que o padrao de cores é RGB ou RGBA

	glutInitWindowSize(winW, winH);  // tamanho da janela
	glutInitWindowPosition(300, 300); // posicao inicial da janela

	glutCreateWindow("Easter bunny");   /// cria a janela

	glutReshapeFunc(tela); // configura tela
	glutDisplayFunc(display);
	glutMainLoop(); // Redesenhar

	return(0);
}

void circle_func(){
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);	
	}
}

void draw_body() {
	raioX = 80.0f;
	raioY = 100.0f;

	glColor3f(0.98, 0.98, 0.98);
	glBegin(GL_POLYGON);
	circle_func();
	glEnd();

	//dark part of the body
	raioX = 50.0f;
	raioY = 70.0f;

	glColor3f(1, 0.72941, 0.99215);
	glBegin(GL_POLYGON);
	circle_func();
	glEnd();
}

void toes(){	
	raioX = 5.0f;
	raioY = 5.0f;

	glColor3f(1, 0.72941, 0.99215);
	glBegin(GL_POLYGON);
	circle_func();
	glEnd();
}

void foot(){
	raioX = 40.0f;
	raioY = 50.0f;

	glColor3f(0.98, 0.98, 0.98);
	glBegin(GL_POLYGON);
	circle_func();
	glEnd();

	//inner part
	glPushMatrix();
	glTranslatef(0,-10,0);
	
	raioX = 20.0f;
	raioY = 25.0f;

	glColor3f(1, 0.72941, 0.99215);
	glBegin(GL_POLYGON);
	circle_func();
	glEnd();
	glPopMatrix();

	//toe 1
	glPushMatrix();
	glTranslatef(0,30,0);
	toes();
	glPopMatrix();
	//toe 2
	glPushMatrix();
	glTranslatef(-20,23,0);
	toes();
	glPopMatrix();
	//toe 3
	glPushMatrix();
	glTranslatef(20,23,0);
	toes();
	glPopMatrix();
}

void draw_feet(){
	//left_foot
	glPushMatrix();
		glTranslatef(-70,-60,0);
		glRotatef(30,0,0,1);
		foot();
	glPopMatrix();

	//right_foot
	glPushMatrix();
		glTranslatef(70,-60,0);
		glRotatef(-30,0,0,1);
		foot();
	glPopMatrix();
}

void hand_toes(){
	raioX = 3.0f;
	raioY = 4.0f;
	glColor3f(1, 0.72941, 0.99215);
	glBegin(GL_POLYGON);
	circle_func();
	glEnd();
}

void hand(){
	raioX = 20.0f;
	raioY = 40.0f;

	glColor3f(0.98, 0.98, 0.98);
	glBegin(GL_POLYGON);
	circle_func();
	glEnd();

	//inner part
	glPushMatrix();
	glTranslatef(0,15,0);
	
	raioX = 9.0f;
	raioY = 4.5f;

	glColor3f(1, 0.72941, 0.99215);
	glBegin(GL_POLYGON);
	circle_func();
	glEnd();
	glPopMatrix();

	//toe 1
	glPushMatrix();
	glTranslatef(0,30,0);
	hand_toes();
	glPopMatrix();

	//toe 2
	glPushMatrix();
	glTranslatef(-7,25,0);
	hand_toes();
	glPopMatrix();

	//toe 3
	glPushMatrix();
	glTranslatef(7,25,0);
	hand_toes();
	glPopMatrix();
}

void draw_hands(){
	glPushMatrix();
	glTranslatef(-75,60,0);
	glRotatef(120,0,0,1);
	hand();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(75,60,0);
	glRotatef(-120,0,0,1);
	hand();
	glPopMatrix();
}

void mustache_hair(){
	glColor3f(0,0,0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
		glVertex2d(0,0);
		glVertex2d(-10,-2);
		glVertex2d(-15,-4);
		glVertex2d(-25,-8);
		glVertex2d(-35,-15);
	glEnd();
}

void mustache(){
	glColor3f(1, 0.72941, 0.99215);
	glPointSize(3);
	glBegin(GL_POINTS);
		glVertex2d(-25,-10);
		glVertex2d(-28, -5);
		glVertex2d(-25, 0);
	glEnd();

	glPushMatrix();
	glTranslatef(-25,-10,0);
		mustache_hair();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-28,-5,0);
		mustache_hair();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-25,0,0);
		mustache_hair();
	glPopMatrix();

}

void cheeks(){
	glColor3f(0.5,0.5,0.5);
	glLineWidth(2.0);
	glBegin(GL_LINE_STRIP);
		glVertex2d(0,-10);
		glVertex2d(-5,-13);
		glVertex2d(-10,-15);
		glVertex2d(-15,-16);
		glVertex2d(-20,-16);
		glVertex2d(-25,-15);
		glVertex2d(-30,-13);
	glEnd();
}

void eye(){
	glLineWidth(1.0);
	glColor3f(0.2,0.2,0.2);
	raioX= 7;
	raioY= 14;

	glBegin(GL_LINE_LOOP);
	circle_func();
	glEnd();

	//Pupil
	glPushMatrix();
	glTranslatef(0,-2,0);
	raioX= 4;
	raioY= 9;

	glBegin(GL_POLYGON);
	circle_func();
	glEnd();
	glPopMatrix();
}

void draw_head() {
	raioX = 60.0f;
	raioY = 50.0f;

	glPushMatrix();
	glTranslatef(0,130,0);
	glColor3f(0.98, 0.98, 0.98);
	glBegin(GL_POLYGON);
	circle_func();
	glEnd();
	//Nose
	glPushMatrix();
	glTranslatef(0,-10,0);
	glColor3f(1, 0.72941, 0.99215);
	glBegin(GL_POLYGON);
	glVertex2d(0,-10);
	glVertex2d(-10,0);
	glVertex2d(10,0);
	glEnd();
	//Mustache
	//left
	mustache();
	//right
	glPushMatrix();
	glScalef(-1,1,1);
	mustache();
	glPopMatrix();
	//Teeth
	glColor3f(0,0,0);
	glBegin(GL_LINE_STRIP);
	glVertex2d(-1,-10);
	glVertex2d(-1,-25);
	glVertex2d(-8,-25);
	glVertex2d(-8,-13);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex2d(1,-10);
	glVertex2d(1,-27);
	glVertex2d(8,-27);
	glVertex2d(8,-13);
	glEnd();
	//Cheeks
	//left
	cheeks();
	//right
	glPushMatrix();
	glScalef(-1,1,1);
	cheeks();
	glPopMatrix();
	glPopMatrix();	
	//Eyes
	//Left Eye
	glPushMatrix();
	glTranslatef(-20,15,0);
	glRotatef(5,0,0,1);
	eye();
	glPopMatrix();
	//Right Eye
	glPushMatrix();
	glTranslatef(20,15,0);
	glRotatef(-5,0,0,1);
	eye();
	glPopMatrix();
	glPopMatrix();
}

void ear(){
	raioX = 15.0f;
	raioY = 60.0f;
	glColor3f(0.98, 0.98, 0.98);
	glBegin(GL_POLYGON);
	circle_func();
	glEnd();
	raioX = 10;
	raioY = 40;
	glColor3f(1, 0.72941, 0.99215);
	glBegin(GL_POLYGON);
	circle_func();
	glEnd();
}

void draw_ears(){
	//left
	glPushMatrix();
	glTranslatef(-60,200,0);
	glRotatef(45,0,0,1);	
	ear();
	glPopMatrix();

	//right
	glPushMatrix();
	glTranslatef(60,200,0);
	glRotatef(-45,0,0,1);	
	ear();
	glPopMatrix();
}

void draw_ground(){
	glPushMatrix();
	glTranslatef(0,-90,0);

	
	glBegin(GL_QUADS);
		glColor3f(0.1,0.5,0.1);
		glVertex2f(-500, 0);
		glVertex2f(500, 0);
		glColor3f(0.4,0.3,0.3);
		glVertex2f(500, -300);
		glVertex2f(-500,-300);
	glEnd();

	glPopMatrix();
}

void tie(){
	glBegin(GL_TRIANGLES);
		glColor3f(0.8,0,0);
		glVertex2d(0,0);
		glColor3f(0.5,0,0);
		glVertex2d(-25,45);
		glVertex2d(25,45);
	glEnd();
}

void egg(){
	raioX=40;
	raioY=50;
	glColor3f(0.19, 0.05, 0.05);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		if(i<200){
			raioY=70;
		}
		else{
			raioY=45;
		}
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);	}
	glEnd();

	glPushMatrix();
	glRotatef(90,0,0,1);
	tie();
	glPopMatrix();
	glPushMatrix();
	glRotatef(-90,0,0,1);
	tie();
	glPopMatrix();
}

void draw_eggs(){
	glPushMatrix();
	glTranslatef(-258,-45,0);
	glRotatef(13,0,0,1);
	egg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(258,-45,0);
	glRotatef(-13,0,0,1);
	egg();
	glPopMatrix();
}

void display() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.9f, 0.9f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glTranslatef(winW / 2, winH / 2, 0.0f);
	glViewport(0, 0, winW, winH);
	
	draw_body();
	draw_ground();
	draw_feet();
	draw_hands();
	draw_ears();
	draw_head();
	draw_eggs();

	glFlush(); // executa o desenho
}

void tela(GLsizei w, GLsizei h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, winW, 0, winH);
	glMatrixMode(GL_MODELVIEW);
}