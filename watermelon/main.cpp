#include<GL/glew.h>
#include<GL/glut.h>
#include<math.h>

#define PI 3.1315926535898
#define janela_altura 800
#define janela_largura 800

void display(void);
void tela(GLsizei w, GLsizei h);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);  // controla se o sistema operacional tem suporte a janelas.

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // quantidade de buffer de cores e que o padrao de cores é RGB ou RGBA

	glutInitWindowSize(janela_largura, janela_altura);  // tamanho da janela
	glutInitWindowPosition(300, 300); // posicao inicial da janela

	glutCreateWindow("Watermelon slice - OpenGL Exercise");   /// cria a janela

	glutReshapeFunc(tela); // configura tela
	glutDisplayFunc(display);
	glutMainLoop(); // Redesenhar

	return(0);
}

void desenhar() {
	GLfloat circ_pnt = 500;
	GLfloat ang, raioX = 300.0f, raioY = 300.0f;
	glPushMatrix();
	glRotatef(180,0,0,1);
	
	glColor3f(0.1, 0.5, 0.1);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = ((2 * PI * i) / circ_pnt)/2;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);
	}
	glEnd();

	//White part
	raioX=280;
	raioY=280;

	glColor3f(0.7, 0.7, 0.7);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = ((2 * PI * i) / circ_pnt)/2;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);
	}
	glEnd();

	//Red part
	raioX=270;
	raioY=270;

	glColor3f(0.8, 0.2, 0.2);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = ((2 * PI * i) / circ_pnt)/2;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);
	}
	glEnd();

	glPopMatrix();

	glPointSize(5);
	
	glColor3f(0,0,0);
	glBegin(GL_POINTS);
	for (int i = 0; i < 50; i++) {
		int randomX = rand() % 400;
		int randomY = rand() % 200;
		glVertex2f(randomX - 200, randomY - 220);
	}

	glEnd();
}

void display() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);  // cor do fundo

	glClear(GL_COLOR_BUFFER_BIT);  // limpa a tela com a cor do fundo

	// Especificar o local onde o desenho acontece: bem no centro da janela
	glTranslatef(janela_largura / 2, janela_altura / 2, 0.0f);

	glViewport(0, 0, janela_largura, janela_altura);
	desenhar();

	glFlush(); // executa o desenho
}

void tela(GLsizei w, GLsizei h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// cria a janela ( esq, dir, baixo, cima)
	gluOrtho2D(0, janela_largura, 0, janela_altura);

	glMatrixMode(GL_MODELVIEW);
}
