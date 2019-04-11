#include <stdlib.h>
#include <GL/glut.h>

void keyboard(unsigned char key, int x, int y);
void resize(GLsizei w, GLsizei h);
void display(void);

int main(int argc, char** argv) {
	glutInit(&argc, argv);  // controla se o sistema operacional tem suporte a janelas.

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  // quantidade de buffer de cores e que o padrao de cores é RGB ou RGBA

	glutInitWindowSize(600, 600);  // tamanho da janela

								   //glutFullScreen();  // full screen

	glutInitWindowPosition(400, 150); // posicao inicial da janela

	glutCreateWindow("GLUT tela do Natao ---- exercicio de glut");   /// cria a janela

	glutKeyboardFunc(&keyboard); // Comandos de teclado

	glutReshapeFunc(&resize); // 

	glutDisplayFunc(display);

	glutMainLoop();

	return EXIT_SUCCESS;
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case '\x1B':
		exit(EXIT_SUCCESS);
		break;
	}
}

void resize(GLsizei w, GLsizei h) {
	if (h == 0) h = 1;  // Evita a divisao por zero

	glViewport(0, 0, w, h);  // Especifica as dimensões da Viewport
							 // Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION); //Setar matrix de projeção
	glLoadIdentity(); // Limpar tudo

	// Estabelece a janela de seleção (left, right, bottom, top)
	if (w <= h) {
		gluOrtho2D(0.0f, 250.0f, 0.0f, 250.0f*h / w);
	}
	else {
		gluOrtho2D(0.0f, 250.0f*w / h, 0.0f, 250.0f);
	}
	glMatrixMode(GL_MODELVIEW);
}

void display() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0.31f, 0.7f, 1.0f, 0.0f);	// definir cor do fundo
	glClear(GL_COLOR_BUFFER_BIT);			// pintar a tela com a cor do fundo
	// ========================
	// Criando chão/grama
	// ========================
	glBegin(GL_QUADS);
	glColor3f(0.25f, 1.0f, 0.5f);//Green
	glVertex2f(0, 50);
	glVertex2f(250, 50);
	glVertex2f(250, 0);
	glVertex2f(0, 0);
	glEnd(); // Fim quadrado
	// ========================
	// Criando casa
	// ========================
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.25f);
	glVertex2f(50, 150);
	glVertex2f(200, 150);
	glVertex2f(200, 50);
	glVertex2f(50, 50);
	glEnd(); // Fim quadrado
	// ========================
	// Criando porta
	// ========================
	glBegin(GL_QUADS);
	glColor3f(0.65f, 0.4f, 0.25f);
	glVertex2f(150, 85);
	glVertex2f(180, 85);
	glVertex2f(180, 50);
	glVertex2f(150, 50);
	glEnd(); // Fim quadrado
	// ========================
	// Maçaneta
	// ========================
	// Deixar o ponto redondo
	glPointSize(15);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Desenhar o ponto
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(155, 68);
	glEnd();
	// ========================
	// Criando telhado
	// ========================
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.5f, 0.25f);	// Cor
	glVertex2f(25, 150);
	glVertex2f(125, 225);			// Vertice da ponta
	glVertex2f(225, 150);
	// OBS: a ordem dos pontos importa
	glEnd();
	// ========================
	// Criando janela com degrade
	// ========================
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(90, 100);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(90, 80);
	glColor3f(255.0f, 0.0f, 0.0f);
	glVertex2f(110, 80);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(110, 100);
	glEnd();
	glLineWidth(5.0);  // Largura das linhas da janela
	// ========================
	glFlush(); // executa o desenho
}
