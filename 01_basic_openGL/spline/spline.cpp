#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <cstdio>

#define TAMANHO_JANELA 500
#define WIDTH TAMANHO_JANELA*2
#define HEIGHT TAMANHO_JANELA

float size = 5.0;
int mouseStatus = 0;
int idx = 0;

//Pontos de controle da Spline
GLfloat ctrlpoints[4][3] = {
        {-4.0, -4.0, 0.0}, 
        {-2.0,  4.0, 0.0}, 
        { 2.0, -4.0, 0.0}, 
        { 4.0,  4.0, 0.0}};

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_MAP1_VERTEX_3);

    //Definicao do polinomio com os pontos de controle
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]); 
    
    //Muda para a matriz de projecao (aulas futuras)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //Define a area/volume de visualizacao. Os objetos desenhados devem estar dentro desta area
    glOrtho(-size, size, -size, size, -size, size);
}

void display(void) {
    int i;

    glClear(GL_COLOR_BUFFER_BIT);
    
    /* Desenha a curva aproximada por n+1 pontos. */
    int n = 30;
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);
        for (i = 0; i <= n; i++){
            //Avaliacao do polinomio, retorna um vertice (equivalente a um glVertex3fv) 
            glEvalCoord1f((GLfloat) i/(GLfloat)n);
        }
    glEnd();
    
    /* Desenha os pontos de controle. */
    glPointSize(5.0);
    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_POINTS);
        for (i = 0; i < 4; i++) 
            glVertex3fv(&ctrlpoints[i][0]);
    glEnd();
    
    glutSwapBuffers();
}

void reshape(int w, int h) {
    //Define a porcao visivel da janela
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    
    //Muda para a matriz de projecao (aulas futuras)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //Controla o redimensionamento da janela mantendo o aspect ration do objeto
    if (w <= h)
        glOrtho(-size, size, -size*(GLfloat)h/(GLfloat)w, 
                size*(GLfloat)h/(GLfloat)w, -size, size);
    else
        glOrtho(-size*(GLfloat)w/(GLfloat)h, 
                size*(GLfloat)w/(GLfloat)h, -size, size, -size, size);
    
    //Muda para a matriz de trasformacoes (aulas futuras)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        for(int i = 0; i < 4; i++) {
            if (x >= ctrlpoints[i][0]-30 && 
                x <= ctrlpoints[i][0]+30 && 
                y >= ctrlpoints[i][1]-30 && 
                y <= ctrlpoints[i][1]+30) 
            {
                if (button == GLUT_LEFT_BUTTON) {
                    mouseStatus = 1;
                    idx = i;
                    ctrlpoints[i][0] = (float)x/WIDTH;
                    ctrlpoints[i][1] = (float)y/HEIGHT;
                    break;
                }
            }
        }
    } else mouseStatus = 0;
}

void motion(int x, int y) {
    if (mouseStatus == 1) {
        ctrlpoints[idx][0] = (float)x/WIDTH;
        ctrlpoints[idx][1] = (float)y/HEIGHT;
        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(TAMANHO_JANELA*2, TAMANHO_JANELA);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    // glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
    }

