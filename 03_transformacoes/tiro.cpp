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
<<<<<<< HEAD
    DesenhaCirc(radiusTiro, 1, 0, 0);
=======
    DesenhaCirc(radiusTiro, 1, 1, 1);
>>>>>>> 763e5976a8f4acc49e3bae5f51bc3434d5637790

    glPopMatrix();
}

void Tiro::Move() {
<<<<<<< HEAD
    this->gX += this->gVel * cos(gDirectionAng) * 100;
    this->gY += this->gVel * sin(gDirectionAng) * 100;
}

bool Tiro::Valido() {
    /** falso se a distancia for maior q distmax */
    return sqrt( pow((gXInit-gX), 2) ) <= DISTANCIA_MAX;
=======
    this->gX += this->gVel*50 * sin(this->gDirectionAng);
    this->gY += this->gVel*50 * cos(this->gDirectionAng);
}

float Tiro::DistPoints(GLfloat x1, GLfloat x2,GLfloat y1,GLfloat y2) {
    return sqrt( pow((this->gXInit - this->gX), 2) + pow((this->gYInit - this->gY), 2));
}

bool Tiro::Valido() {
    if (DistPoints(this->gXInit, this->gX, this->gYInit, this->gY) > DISTANCIA_MAX) return false;
    else return true;
>>>>>>> 763e5976a8f4acc49e3bae5f51bc3434d5637790
}
