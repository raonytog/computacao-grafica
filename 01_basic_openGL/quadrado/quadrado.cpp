#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>

#define WINDOW_SIZE 600
#define WIDTH 1024
#define HEIGHT 600

#define JUMP 0.005

float gX = 0;
float gY = 0;
int keyStatus[256];
int mouseStatus = 0;

void keyPress(unsigned char key, int x, int y) {
    if      (key == 'a') keyStatus[(int)'a'] = 1;
    else if (key == 'w') keyStatus[(int)'w'] = 1;
    else if (key == 's') keyStatus[(int)'s'] = 1;
    else if (key == 'd') keyStatus[(int)'d'] = 1;

    glutPostRedisplay();
}

void keyUp(unsigned char key, int x, int y) {
    if      (key == 'a') keyStatus[(int)'a'] = 0;
    else if (key == 'w') keyStatus[(int)'w'] = 0;
    else if (key == 's') keyStatus[(int)'s'] = 0;
    else if (key == 'd') keyStatus[(int)'d'] = 0;

    glutPostRedisplay();
}

void idle(void) {
    if      (keyStatus[(int)('a')]) gX -= JUMP;
    else if (keyStatus[(int)('w')]) gY += JUMP;
    else if (keyStatus[(int)('s')]) gY -= JUMP;
    else if (keyStatus[(int)('d')]) gX += JUMP;

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) mouseStatus = 1;
        
    } else mouseStatus = 0;
}

void motion(int x, int y) {
    if (mouseStatus != 1) return;

    gX = (float)x / WIDTH;
    gY = (HEIGHT - (float)y) / HEIGHT;

    glutPostRedisplay();
}

void random_drawing(void) {
    glBegin(GL_TRIANGLES);
        glVertex3f(0.1, 0.2, 0.0);
        glVertex3f(0.1, 0.1, 0.0);
        glVertex3f(0.2, 0.1, 0.0);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex3f(0.5, 0.5, 0.0);
        glVertex3f(0.6, 0.6, 0.0);
        glVertex3f(0.7, 0.3, 0.0);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(1, 1);
        glVertex2f(1, 0.3);
        glVertex2f(0.3, 0.7);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3f(0.1, 0.2, 0.0);
        glVertex3f(0.1, 0.1, 0.0);
        glVertex3f(0.2, 0.1, 0.0);
        glVertex3f(0.5, 0.5, 0.0);
        glVertex3f(0.6, 0.6, 0.0);
        glVertex3f(0.7, 0.3, 0.0);
        glVertex2f(1, 0.8);
        glVertex2f(1, 0.3);
        glVertex2f(0.3, 0.7);
    glEnd();
}

void display(void) {
    /* Limpar todos os pixels  */
    glClear (GL_COLOR_BUFFER_BIT);

    /* Define cor dos vértices com os valores R, G e B variando de 0.0 a 1.0 */
    glColor3f (1, 0.2, 1.0);

    /* Desenhar um polígono branco (retângulo) */
    glBegin(GL_POLYGON);
        glVertex2f(0.25+gX, 0.50+gY);
        glVertex2f(0.25+gX, 0.25+gY);
        glVertex2f(0.50+gX, 0.25+gY);
        glVertex2f(0.50+gX, 0.50+gY);
    glEnd();

    /* Desenhar no frame buffer! */
    glutSwapBuffers(); //Funcao apropriada para janela double buffer
}

void init(void) {
    /* selecionar cor de fundo (preto) */
    glClearColor (0.0, 0.0, 0.0, 0.0);

    /* inicializar sistema de visualizacao */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0 * WIDTH/HEIGHT, 0.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT); 
    glutInitWindowPosition(200, 0);
    glutCreateWindow("hello world");
    
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyUp);
    glutIdleFunc(idle);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);


    glutMainLoop();

    return 0;
}
