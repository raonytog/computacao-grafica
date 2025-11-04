#include "includes/alvo.h"
#include <math.h>

void Alvo::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B) {
    glPointSize(1.0);
    glColor3f(R, G, B);
    
    glBegin(GL_POLYGON);
        for(double i = 0; i < 2*M_PI; i+= M_PI/24) {
            float x = radius * cos(i);
            float y = radius * sin(i);
                glVertex3f(x, y, 0);
            }
    glEnd();
}

void Alvo::DesenhaAlvo(GLfloat x, GLfloat y) {
    glPushMatrix();

    glTranslatef(x, y, 0);
    switch (this->gColor) {
    case 0:
        DesenhaCirc(radiusAlvo, 1,0,0);

    case 1:
        DesenhaCirc(radiusAlvo, 0,1,0);

    case 2:
        DesenhaCirc(radiusAlvo, 0,0,1);
        break;
    }

    glPopMatrix();
}

void Alvo::Recria(GLfloat x, GLfloat y) {

}

float Alvo::DistPoints(GLfloat x1, GLfloat x2,GLfloat y1,GLfloat y2) {
    return sqrt( pow((x1 - x2), 2) + pow((y1 - y2), 2));
}

bool Alvo::Atingido(Tiro *tiro) {
    GLfloat alvoX = 0, alvoY = 0;
    tiro->GetPos(alvoX, alvoY);

    return DistPoints(alvoX, this->gX, alvoY, this->gY) <= radiusAlvo;
}
