#include<GL/glew.h>
#include<GL/glut.h>
#include<math.h>

#define PI 3.1315926535898
#define winH 600
#define winW 600

void display(void);
void tela(GLsizei w, GLsizei h);

int main(int argc, char** argv)
{
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

void draw_body() {
	GLfloat circ_pnt = 400;
	GLfloat ang, raioX = 80.0f, raioY = 100.0f;

	glColor3f(0.98, 0.98, 0.98);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);	}
	glEnd();

	//dark part of the body
	raioX = 50.0f;
	raioY = 70.0f;

	glColor3f(1, 0.72941, 0.99215);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);	}
	glEnd();
}

void draw_left_foot(){
	glPushMatrix();
	glTranslatef(-70,-60,0);
	glRotatef(30,0,0,1);

	GLfloat circ_pnt = 400;
	GLfloat ang, raioX = 40.0f, raioY = 50.0f;

	glColor3f(0.98, 0.98, 0.98);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);	}
	glEnd();

	//inner part
	glPushMatrix();
	glTranslatef(0,-10,0);
	
	raioX = 20.0f;
	raioY = 25.0f;

	glColor3f(1, 0.72941, 0.99215);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);	}
	glEnd();
	glPopMatrix();

	//toe 1
	glPushMatrix();
	glTranslatef(0,30,0);
	
	raioX = 5.0f;
	raioY = 5.0f;

	glColor3f(1, 0.72941, 0.99215);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);	}
	glEnd();
	glPopMatrix();

	//toe 2
	glPushMatrix();
	glTranslatef(-20,23,0);
	
	raioX = 5.0f;
	raioY = 5.0f;

	glColor3f(1, 0.72941, 0.99215);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);	}
	glEnd();
	glPopMatrix();

	//toe 3
	glPushMatrix();
	glTranslatef(20,23,0);
	
	raioX = 5.0f;
	raioY = 5.0f;

	glColor3f(1, 0.72941, 0.99215);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2* PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);	}
	glEnd();
	glPopMatrix();


	glPopMatrix();
}

void draw_right_foot(){
	glPushMatrix();
	glTranslatef(70,-60,0);
	glRotatef(-30,0,0,1);

	GLfloat circ_pnt = 400;
	GLfloat ang, raioX = 40.0f, raioY = 50.0f;

	glColor3f(0.98, 0.98, 0.98);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);	}
	glEnd();

	//inner part
	glPushMatrix();
	glTranslatef(0,-10,0);
	
	raioX = 20.0f;
	raioY = 25.0f;

	glColor3f(1, 0.72941, 0.99215);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);	}
	glEnd();
	glPopMatrix();

	//toe 1
	glPushMatrix();
	glTranslatef(0,30,0);
	
	raioX = 5.0f;
	raioY = 5.0f;

	glColor3f(1, 0.72941, 0.99215);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);	}
	glEnd();
	glPopMatrix();

	//toe 2
	glPushMatrix();
	glTranslatef(-20,23,0);
	
	raioX = 5.0f;
	raioY = 5.0f;

	glColor3f(1, 0.72941, 0.99215);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);	}
	glEnd();
	glPopMatrix();

	//toe 3
	glPushMatrix();
	glTranslatef(20,23,0);
	
	raioX = 5.0f;
	raioY = 5.0f;

	glColor3f(1, 0.72941, 0.99215);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2* PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);	}
	glEnd();
	glPopMatrix();


	glPopMatrix();
}


void draw_left_hand(){
	glPushMatrix();

	glTranslatef(-75,60,0);
	glRotatef(120,0,0,1);

	GLfloat circ_pnt = 400;
	GLfloat ang, raioX = 20.0f, raioY = 40.0f;

	glColor3f(0.98, 0.98, 0.98);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);	}
	glEnd();
	glEnd();

	//inner part
	glPushMatrix();
	glTranslatef(0,15,0);
	
	raioX = 9.0f;
	raioY = 4.5f;

	glColor3f(1, 0.72941, 0.99215);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);	}
	glEnd();
	glPopMatrix();

	//toe 1
	glPushMatrix();
	glTranslatef(0,30,0);
	
	raioX = 3.0f;
	raioY = 4.0f;

	glColor3f(1, 0.72941, 0.99215);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);	}
	glEnd();
	glPopMatrix();

	//toe 2
	glPushMatrix();
	glTranslatef(-7,25,0);

	glColor3f(1, 0.72941, 0.99215);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);	}
	glEnd();
	glPopMatrix();

	//toe 3
	glPushMatrix();
	glTranslatef(7,25,0);

	glColor3f(1, 0.72941, 0.99215);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2* PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);	}
	glEnd();
	glPopMatrix();


	glPopMatrix();
}

void draw_right_hand(){
	glPushMatrix();

	glTranslatef(75,60,0);
	glRotatef(-120,0,0,1);

	GLfloat circ_pnt = 400;
	GLfloat ang, raioX = 20.0f, raioY = 40.0f;

	glColor3f(0.98, 0.98, 0.98);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);	}
	glEnd();

	//inner part
	glPushMatrix();
	glTranslatef(0,15,0);
	
	raioX = 9.0f;
	raioY = 4.5f;

	glColor3f(1, 0.72941, 0.99215);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);	}
	glEnd();
	glPopMatrix();

	//toe 1	
	glPushMatrix();
	glTranslatef(0,30,0);

	raioX = 3.0f;
	raioY = 4.0f;

	glColor3f(1, 0.72941, 0.99215);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);	}
	glEnd();
	glPopMatrix();

	//toe 2
	glPushMatrix();
	glTranslatef(-7,25,0);

	glColor3f(1, 0.72941, 0.99215);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);	}
	glEnd();
	glPopMatrix();

	//toe 3
	glTranslatef(7,25,0);

	glColor3f(1, 0.72941, 0.99215);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2* PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);	}
	glEnd();
	glPopMatrix();
	glPopMatrix();
}

void draw_head() {
	GLfloat circ_pnt = 400;
	GLfloat ang, raioX = 60.0f, raioY = 50.0f;

	glPushMatrix();
	glTranslatef(0,130,0);

	glColor3f(0.98, 0.98, 0.98);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);	}
	glEnd();

	//Nose
	glPushMatrix();
	glTranslatef(0,-10,0);

	glColor3f(1, 0.72941, 0.99215);
	glBegin(GL_POLYGON);
	glVertex2d(0,-10);//low
	glVertex2d(-10,0);
	//glVertex2d(-5,5);
	//glVertex2d(5,5);
	glVertex2d(10,0);
	glEnd();

	//Mustache
	glPointSize(3);
	glBegin(GL_POINTS);
	glVertex2d(-25,-10);
	glVertex2d(-28,-5);
	glVertex2d(-26,0);

	glVertex2d(25,-10);
	glVertex2d(28,-5);
	glVertex2d(26,0);

	glEnd();

	glColor3f(0,0,0);
	glLineWidth(1.0);
	glBegin(GL_LINE_STRIP);
	glVertex2d(-25,-10);
	glVertex2d(-35,-12);
	glVertex2d(-40,-14);
	glVertex2d(-50,-18);
	glVertex2d(-60,-25);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex2d(-28,-5);
	glVertex2d(-38,-7);
	glVertex2d(-43,-9);
	glVertex2d(-53,-13);
	glVertex2d(-63,-20);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2d(-26,0);
	glVertex2d(-36,-2);
	glVertex2d(-41,-4);
	glVertex2d(-51,-8);
	glVertex2d(-61,-15);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex2d(25,-10);
	glVertex2d(35,-12);
	glVertex2d(40,-14);
	glVertex2d(50,-18);
	glVertex2d(60,-25);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex2d(28,-5);
	glVertex2d(38,-7);
	glVertex2d(43,-9);
	glVertex2d(53,-13);
	glVertex2d(63,-20);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex2d(26,0);
	glVertex2d(36,-2);
	glVertex2d(41,-4);
	glVertex2d(51,-8);
	glVertex2d(61,-15);
	glEnd();

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

	glBegin(GL_LINE_STRIP);
	glVertex2d(0,-10);
	glVertex2d(5,-13);
	glVertex2d(10,-15);
	glVertex2d(15,-16);
	glVertex2d(20,-16);
	glVertex2d(25,-15);
	glVertex2d(30,-13);
	glEnd();

	glPopMatrix();

	glPushMatrix();
	//Eyes

	//Left Eye
	glTranslatef(-20,15,0);
	glRotatef(5,0,0,1);
	glLineWidth(1.0);
	glColor3f(0.2,0.2,0.2);

	raioX= 7;
	raioY= 14;

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2* PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);	}
	glEnd();

	//Pupil
	glTranslatef(0,-2,0);
	raioX= 4;
	raioY= 9;

	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2* PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);	}
	glEnd();

	glPopMatrix();

	//Right Eye
	glPushMatrix();
	glTranslatef(20,15,0);
	glRotatef(-5,0,0,1);

	raioX= 7;
	raioY= 14;	

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2* PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);	}
	glEnd();

	//Pupil
	glTranslatef(0,-2,0);
	raioX= 4;
	raioY= 9;

	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2* PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);	}
	glEnd();


	glPopMatrix();

	//Pupils



	glPopMatrix();
}

void draw_left_ear() {
	GLfloat circ_pnt = 400;
	GLfloat ang, raioX = 15.0f, raioY = 60.0f;

	glPushMatrix();
	glTranslatef(-60,200,0);
	glRotatef(45,0,0,1);

	glColor3f(0.98, 0.98, 0.98);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);	}
	glEnd();

	raioX = 10;
	raioY = 40;

	glColor3f(1, 0.72941, 0.99215);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);	}
	glEnd();

	glPopMatrix();
}

void draw_right_ear() {
	GLfloat circ_pnt = 400;
	GLfloat ang, raioX = 15.0f, raioY = 60.0f;

	glPushMatrix();
	glTranslatef(60,200,0);
	glRotatef(-45,0,0,1);

	glColor3f(0.98, 0.98, 0.98);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);	}
	glEnd();

	raioX = 10;
	raioY = 40;

	glColor3f(1, 0.72941, 0.99215);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);	}
	glEnd();

	glPopMatrix();
}

void display() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.9f, 0.9f, 1.0f, 1.0f);  // cor do fundo

	glClear(GL_COLOR_BUFFER_BIT);  // limpa a tela com a cor do fundo

	// Especificar o local onde o desenho acontece: bem no centro da janela
	glTranslatef(winW / 2, winH / 2, 0.0f);

	glViewport(0, 0, winW, winH);
	
	draw_body();
	draw_left_foot();
	draw_right_foot();
	draw_left_hand();
	draw_right_hand();
	draw_left_ear();
	draw_right_ear();
	draw_head();

	glFlush(); // executa o desenho
}

void tela(GLsizei w, GLsizei h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// cria a janela ( esq, dir, baixo, cima)
	gluOrtho2D(0, winW, 0, winH);

	glMatrixMode(GL_MODELVIEW);
}

