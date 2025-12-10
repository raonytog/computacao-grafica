#include "includes/tiro.h"
#include <math.h>
#define DISTANCIA_MAX 500

void Tiro::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B) {
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

void Tiro::DesenhaTiro(GLfloat x, GLfloat y) {
    glPushMatrix();

    glTranslatef(x, y, 0);
    DesenhaCirc(radiusTiro, 1, 0, 0);

    glPopMatrix();
}

void Tiro::Move() {
    this->gX += this->gVel * cos(gDirectionAng) * 100;
    this->gY += this->gVel * sin(gDirectionAng) * 100;
}

bool Tiro::Valido() {
    /** falso se a distancia for maior q distmax */
    return sqrt( pow((gXInit-gX), 2) ) <= DISTANCIA_MAX;
}
