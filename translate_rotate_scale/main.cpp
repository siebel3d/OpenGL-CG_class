#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#define janela_altura 400
#define janela_largura 600
float rotacao = 1;
float zoom = 1;
float trans = 1;

void display(void);
void tela(GLsizei w, GLsizei h);
void keyboard(unsigned char tecla, int x, int y);

int main(int argc, char** argv){
	glutInit(&argc, argv);  // controla se o sistema operacional tem suporte a janelas.

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // quantidade de buffer de cores e que o padrao de cores é RGB ou RGBA

	glutInitWindowSize(janela_largura, janela_altura);  // tamanho da janela
	glutInitWindowPosition(300, 300); // posicao inicial da janela

	glutCreateWindow("GLUT Rotacao/Zoom/Translacao ---- exercicio de glut");   /// cria a janela

	glutReshapeFunc(tela); // configura tela
	glutDisplayFunc(display);
	glutKeyboardFunc(&keyboard); // chama o teclado
	glutMainLoop(); // Redesenhar

	return(0);
}

void keyboard(unsigned char tecla, int x, int y) {
	printf("\n tecla %c \n", tecla);
	printf("\n \n Digite 1 para esquerda, 2 para direita: ");
	printf("\n tecla %c \n", tecla);
	printf("\n o mouse estava em %d x %d \n", x, y);

	if (tecla == '1') {
		rotacao = rotacao + 0.05;
	}
	if (tecla == '2') {
		rotacao = rotacao - 0.05;
	}
	if (tecla == '3') {
		zoom = zoom + 0.05;
	}
	if (tecla == '4') {
		trans = trans + 0.05;
	}
	if (tecla == '5') {
		trans = trans - 0.05;
	}

	glutPostRedisplay();
}

void desenhar() {
	// rotacao (angulo, eixo x, eixo y, eixo z)
	glRotated(rotacao, 0, 0, 1);

	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0); // Cor
	glVertex2f(-100, -100);
	glVertex2f(0, 0);
	glVertex2f(100, -100);
	glEnd();

	glRotated(-rotacao, 0, 0, 1); // sem rotacao

	glScalef(zoom, zoom, 0);
	glTranslatef(trans, trans, 0);

	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0); // Cor
	glVertex2f(-30, 30);
	glVertex2f(-10, 30);
	glVertex2f(-10, 50);
	glVertex2f(-30, 50);
	glEnd();

	glScalef(1, 1, 0);
	glTranslatef(1, 1, 0);
}

void display() {
	glMatrixMode(GL_MODELVIEW); // coordernadas do desenho
	glLoadIdentity();

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // cor do fundo
	glClear(GL_COLOR_BUFFER_BIT);

	// especifica o local onde o desenho acontece
	glTranslatef(janela_largura / 2, janela_altura / 2, 0.0f);

	glViewport(0, 0, janela_largura, janela_altura);
	desenhar();

	glFlush(); // execute o desenho
}

void tela(GLsizei w, GLsizei h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// cria a janela (esq, dir, baixo, cima)
	gluOrtho2D(0, janela_largura, 0, janela_altura);

	glMatrixMode(GL_MODELVIEW);
}
